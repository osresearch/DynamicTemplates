//
// $Id: RenderArea--draw.cpp,v 1.21 2010/01/01 20:22:32 igor Exp $
//
// This file is part of DIY_Dynamic_Templates_V2
// 
// DIY_Dynamic_Templates_V2 is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3 of the License, or
// (at your option) any later version.
// 
// DIY_Dynamic_Templates_V2 is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// Refer to the GNU General Public License in file "license.txt"
// Otherwise, see <http://www.gnu.org/licenses/>.


#include <QtDebug>  // this is here for debugging 

#include "RenderArea.h"
#include <QFileDialog>
#include <QProgressDialog>
#include <QApplication>
#include <QDir>

void RenderArea::outputPDF ( )
{
	QPainter* painter = new QPainter() ;
	
	printer->setOutputFormat ( QPrinter::PdfFormat ) ;
//	printer->setPaperSize ( QPrinter::Custom ) ;
	printer->setPaperSize ( QSizeF( thePaper.width(), thePaper.height() ), QPrinter::DevicePixel ) ;
	
	QRect printerRect = printer->paperRect () ;
	QString path ;

#if defined(Q_OS_MAC)
	path = QDir::cleanPath ( qApp->applicationDirPath() + "/../../DynamicTemplate.pdf" ) ;
#else
	path = QDir::cleanPath ( qApp->applicationDirPath() + "/DynamicTemplate.pdf" ) ;
#endif
	
	QString fileName = QFileDialog::getSaveFileName	( this, tr("Save PDF File"), path, tr("Images (*.pdf)" ) ) ;	
	
	if ( !( fileName.isEmpty() || fileName.isNull() ) )
	{	printer->setOutputFileName ( fileName ) ;
		QDate saveDate = today ;
		printer->setFullPage( true ) ;
		painter->begin ( printer ) ;
		today = startDate ;
		
		QProgressDialog chug ( tr("Making PDF"), tr("Cancel"), 0, startDate.daysTo ( stopDate ), this ) ;
		chug.setWindowModality(Qt::WindowModal);
				
		do 
		{	setDate ( today ) ;
			
			chug.setValue ( startDate.daysTo ( today ) ) ;
			
			if ( chug.wasCanceled() )
			{	break ;
			}
			
			draw ( theStyle, DRAW_TO_PDF, painter ) ;
			
			switch ( whatKind )
			{	case CAL_DAY:
					today = today.addDays ( 1 ) ;
					break ;
				case CAL_WEEK:
					today = today.addDays ( 7 ) ;
					break ;
				case CAL_MONTH:
					today = today.addMonths ( 1 ) ;
					break ;
				case CAL_YEAR:
					today = today.addYears ( 1 ) ;
					break ;
			}

			if ( today <= stopDate )
			{	printer->newPage() ;
			}
		} while ( today <= stopDate ) ;

		chug.setValue ( startDate.daysTo ( stopDate ) ) ;

		painter->end () ;
		today = saveDate ;
		setDate ( today ) ;
	}
	
//	thePaper = tempPaper ;
//	thePage = tempPage ;
	
}

void RenderArea::outputSVG ( )
{
	//	QString saveDir   
	//	QString saveDir = QFileDialog::getExistingDirectory ( this, tr("Select or Create a folder to save to"), "", QFileDialog::ShowDirsOnly ) ;  
	
	svgFileName = QFileDialog::getSaveFileName 	( this, tr("Select or Create a folder to save to"), "", tr("Images (*.svg)"), 0, QFileDialog::ShowDirsOnly ) ;
	
	svgFileCount = 0 ;
	
	if ( svgFileName.isNull() )
	{	return ;
	}
	
	//	svgFileName + QString(".%1.svg").arg ( svgFileCount, 3, 10, QChar('0') )
	
	gen = new QSvgGenerator() ;
	
//	qDebug() << "QSvgGenerator resolution = " << gen->resolution()  ;
	
//	gen->setResolution( 300 ) ;
//	gen->setResolution( resolution ) ;
	gen->setResolution( 1200 ) ;

	gen->setSize ( thePaper.size().toSize() ) ;
	gen->setViewBox ( thePaper ) ;
	
//	qDebug() << "QSvgGenerator resolution = " << gen->resolution()  ;
	
	gen->setFileName ( svgFileName + QString(".%1.svg").arg ( svgFileCount, 3, 10, QChar('0') ) ) ;
	
	QPainter* painter = new QPainter() ;
	QDate saveDate = today ;
	
	today = startDate ;
//	qDebug() << "today = " << today.toString ( "dddd d MMM" ) ;
	painter->begin ( gen ) ;
	
	do 
	{	
		
		setDate ( today ) ;
		
		draw ( theStyle, DRAW_TO_SVG, painter ) ;
		
		switch ( whatKind )
		{	case CAL_DAY:
			today = today.addDays ( 1 ) ;
			break ;
		case CAL_WEEK:
			today = today.addDays ( 7 ) ;
			break ;
		case CAL_MONTH:
			today = today.addMonths ( 1 ) ;
			break ;
		case CAL_YEAR:
			today = today.addYears ( 1 ) ;
			break ;
		}
		
//		qDebug() << "today (" << today.toString ( "dddd d MMM" ) << ") ?? stopDate(" << stopDate.toString ( "dddd d MMM" ) << ")" ;
		
		if ( today <= stopDate )
		{	incrementFileName( painter ) ;	// qDebug() << "newpage" ;
		}
	} while ( today <= stopDate ) ;
	
	painter->end () ;
	delete ( gen ) ;
	
	today = saveDate ;
	setDate ( today ) ;
}

void RenderArea::incrementFileName( QPainter* painter )
{
	painter->end () ;
	delete ( gen ) ;
	
	gen = new QSvgGenerator() ;
	svgFileCount++ ;
	gen->setResolution( 1200 ) ;
	gen->setSize ( thePaper.size().toSize() ) ;
	gen->setViewBox ( thePaper ) ;
	gen->setFileName ( svgFileName + QString(".%1.svg").arg ( svgFileCount, 3, 10, QChar('0') ) ) ;
	painter->begin ( gen ) ;
	
}

void RenderArea::draw( int style, DrawType where, QPainter* painter )
{	
	switch ( style )
	{
		case 00: // one page per day, DIY3 Left Hand Style
			twoPagePerDayDrawDay ( painter, true ) ;
			break ;

		case 01: // one page per day, DIY3 Right Hand Style
			twoPagePerDayDrawDay ( painter, false ) ;
			break ;

		case 02: // one page per day, DIY3 Alternate Left/Right
			twoPagePerDayDrawDay ( painter, !( startDate.daysTo (today) % 2 ) ) ;
			break ;
			
		case 03: // one page per day, Dated Journal - Lined
			onePagePerDayDrawPage ( painter, !( startDate.daysTo (today) % 2 ), 0 ) ;
			break ;
			
		case 04: // one page per day, Dated Journal - Grid
			onePagePerDayDrawPage ( painter, !( startDate.daysTo (today) % 2 ), 1 ) ;
			break ;
			
		case 05: // one page per day, Dated Journal - Plain
			onePagePerDayDrawPage ( painter, !( startDate.daysTo (today) % 2 ), 2 ) ;
			break ;
			
		case 10: // one page per week, style 1
			onePagePerWeekDrawPage ( painter, !( ( startDate.daysTo (today) / 7 ) % 2 ), true ) ;
			break ;

		case 11: // one page per week, style 2
			onePagePerWeekDrawPage ( painter, !( ( startDate.daysTo (today) / 7 ) % 2 ), false ) ;
			break ;
			
		case 20: // one page per month, style 1
			onePagePerMonthDrawPage ( painter, !( (today.month() - startDate.month()) % 2 ) ) ;
			break ;

//		case 21: // one page per month, style 2
//			break ;
			
		case 30: // one page per year, style 1
			onePagePerYearDrawPage ( painter ) ;
			break ;

		case 31: // one page per year, style 2
			onePagePerTwoYearsDrawPage ( painter ) ;
			break ;
			
		case 40: // Plain Lined
		case 41: // Plain Lined w/Grey Column
		case 42: // Grey Lined w/Grey Column
		case 43: // Cornell Plain
		case 44: // Cornell w/Grid & Lines
		case 45: // Grid
		case 46: // Dots
			drawSinglePageNotes ( painter ) ;
			break ;

			
		case 100: // two page per day , DIY3 Journal Right
			twoPagePerDayDrawDay ( painter, true ) ;
			switch ( where )
			{	case DRAW_TO_SCREEN:
					painter->translate ( QPointF ( thePaper.width(), 0.0 ) ) ;
					break ;
				case DRAW_TO_PDF:
					printer->newPage() ;
					break ;
				case DRAW_TO_SVG:
					incrementFileName( painter ) ;
					break ;
				default:
					break ;
			}
			twoPagePerDayDrawOtherPage ( painter, false ) ;
			credits ( painter ) ;
			switch ( where )
			{	case DRAW_TO_SCREEN:
					painter->translate( -1.0 * thePaper.width(), 0.0 ) ;
					break ;
				default:
					break ;
			}
			break ;

		case 101: // two page per day , DIY3 Journal Left
			twoPagePerDayDrawOtherPage ( painter, true ) ;
			switch ( where )
			{	case DRAW_TO_SCREEN:
					painter->translate ( QPointF ( thePaper.width(), 0.0 ) ) ;
					break ;
				case DRAW_TO_PDF:
					printer->newPage() ;
					break ;
				case DRAW_TO_SVG:
					incrementFileName( painter ) ;
					break ;
				default:
					break ;
			}
			twoPagePerDayDrawDay ( painter, false ) ;
			credits ( painter ) ;
			switch ( where )
			{	case DRAW_TO_SCREEN:
					painter->translate( -1.0 * thePaper.width(), 0.0 ) ;
					break ;
				default:
					break ;
			}
			break ;

		case 110: // two page per week, 4 blocks on a page
			twoPagePerWeekDrawPage ( painter, true ) ;
			switch ( where )
			{	case DRAW_TO_SCREEN:
					painter->translate ( QPointF ( thePaper.width(), 0.0 ) ) ;
					break ;
				case DRAW_TO_PDF:
					printer->newPage() ;
					break ;
				case DRAW_TO_SVG:
					incrementFileName( painter ) ;
					break ;
				default:
					break ;

			}
				
			twoPagePerWeekDrawPage ( painter, false ) ;
			credits ( painter ) ;
			switch ( where )
			{	case DRAW_TO_SCREEN:
				painter->translate( -1.0 * thePaper.width(), 0.0 ) ;
				break ;
			default:
				break ;

			}
			break ;
		
		case 111: // two page per week, Moleskine-like Horizontal
			TBD ( painter ) ;
			break ;

		case 112: // two page per week, Moleskine-like Vertical
			TBD ( painter ) ;
			break ;
			
		case 113: // two page per week, Moleskine-like Notebook
			
			twoPagePerWeekMoleskineStyleDrawPage ( painter, MOLE_NOTEBOOK, true ) ;
			
			switch ( where )
			{	case DRAW_TO_SCREEN:
					painter->translate ( QPointF ( thePaper.width(), 0.0 ) ) ;
					break ;
				case DRAW_TO_PDF:
					printer->newPage() ;
					break ;
				case DRAW_TO_SVG:
					incrementFileName( painter ) ;
					break ;
				default:
					break ;
			}
				
			twoPagePerWeekMoleskineStyleDrawPage ( painter, MOLE_NOTEBOOK, false ) ;
			credits ( painter ) ;
			
			switch ( where )
			{	case DRAW_TO_SCREEN:
					painter->translate( -1.0 * thePaper.width(), 0.0 ) ;
					break ;
				default:
					break ;
			}
			
			break ;

		case 114: // two page per week, Moleskine-like Landscape
			TBD ( painter ) ;
			twoPagePerWeekMoleskineStyleDrawPage ( painter, MOLE_LANDSCAPE, true ) ;
			
			switch ( where )
			{	case DRAW_TO_SCREEN:
//					painter->translate ( 0.0, thePaper.height() ) ;
					painter->translate ( thePaper.width(), 0.0 ) ;

					break ;
				case DRAW_TO_PDF:
					printer->newPage() ;
					break ;
				case DRAW_TO_SVG:
					incrementFileName( painter ) ;
					break ;
				default:
					break ;
			}
				
			twoPagePerWeekMoleskineStyleDrawPage ( painter, MOLE_LANDSCAPE, false ) ;
			credits ( painter ) ;
			
			switch ( where )
			{	case DRAW_TO_SCREEN:
//	     			painter->translate( 0.0, -1.0 * thePaper.height() ) ;
					painter->translate( -1.0 * thePaper.width(), 0.0 ) ;

					break ;
				default:
					break ;
			}
				break ;

		case 115: // two page per week, Columns
			TBD ( painter ) ;
			break ;
			
		case 120: // two page per month, DIY3 Portrait
			twoPagePerMonthDrawPage ( painter, true ) ;
			switch ( where )
			{	case DRAW_TO_SCREEN:
					painter->translate ( QPointF ( thePaper.width(), 0.0 ) ) ;
					break ;
				case DRAW_TO_PDF:
					printer->newPage() ;
					break ;
				case DRAW_TO_SVG:
					incrementFileName( painter ) ;
					break ;
				default:
					break ;
			}
				
			twoPagePerMonthDrawPage ( painter, false ) ;
			credits ( painter ) ;
			switch ( where )
			{	case DRAW_TO_SCREEN:
					painter->translate( -1.0 * thePaper.width(), 0.0 ) ;
					break ;
				default:
					break ;
			}
			break ;

		case 121: // two page per month, DIY3 Landscape
			twoPagePerMonthDrawLandscapePage ( painter, true ) ;
			switch ( where )
			{	case DRAW_TO_SCREEN:
				painter->translate ( QPointF ( thePaper.width(), 0.0 ) ) ;
					break ;
				case DRAW_TO_PDF:
					printer->newPage() ;
					break ;
				case DRAW_TO_SVG:
					incrementFileName( painter ) ;
					break ;
				default:
					break ;
			}
				
			twoPagePerMonthDrawLandscapePage ( painter, false ) ;
			credits ( painter ) ;
			switch ( where )
			{	case DRAW_TO_SCREEN:
				painter->translate( -1.0 * thePaper.width(), 0.0 ) ;
					break ;
				default:
					break ;
			}
			break ;
			
		case 130: // two page per year, style 1
			twoPagePerYearDrawPage ( painter, true ) ;
			switch ( where )
			{	case DRAW_TO_SCREEN:
					painter->translate ( QPointF ( thePaper.width(), 0.0 ) ) ;
					break ;
				case DRAW_TO_PDF:
					printer->newPage() ;
					break ;
				case DRAW_TO_SVG:
					incrementFileName( painter ) ;
					break ;
				default:
					break ;
			}
			twoPagePerYearDrawPage ( painter, false ) ;
			credits ( painter ) ;
			switch ( where )
			{	case DRAW_TO_SCREEN:
					painter->translate( -1.0 * thePaper.width(), 0.0 ) ;
					break ;
				default:
					break ;
			}
			break ;
			
		case 131: // two page per year, style 2
			TBD ( painter ) ;
			break ;
			
		default:
			TBD ( painter ) ;
			break ;
	}
	credits ( painter ) ;
}

void RenderArea::credits ( QPainter* painter )
{
	QFont werdz ( "Blue Highway" ) ;
	
	QPen thePen(lineColors[0], penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
	QBrush theBrush ( lineColors[0], Qt::SolidPattern ) ;
		
	painter->setPen ( thePen ) ;
	theBrush.setStyle ( Qt::NoBrush ) ;
	painter->setBrush ( theBrush  ) ;
	painter->setFont ( werdz ) ;
	
	qreal topMargin = thePage.y() - thePaper.y() ;
	
	
	QRectF textRect ( thePaper.x(), thePaper.y() + (topMargin / 2.0), thePaper.width(), topMargin / 4.0 ) ;
	textRect.moveTop ( thePage.bottom() ) ;
	
	fitStringInRect ( textRect, tr("This template was created with the D*I*Y Planner Dynamic Template application -- Available free at www.DIYPlanner.com."), painter, Qt::AlignBottom | Qt::AlignHCenter, 0.80 ) ;
}

void RenderArea::TBD ( QPainter* painter )
{
	QFont werdz ( "Blue Highway" ) ;
	
	QPen thePen(Qt::white, penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
	QBrush theBrush ( Qt::white, Qt::SolidPattern ) ;
	
	QRectF paper = thePaper ;
	QRectF page = thePage ;

	// --- "erase" the page ------------------------------------------------------
	painter->setBrush ( theBrush  ) ;
	painter->setPen ( thePen ) ;
	painter->drawRect ( paper ) ;
	
	thePen.setColor ( lineColors[0] ) ;
	theBrush.setColor ( lineColors[0] ) ;
	painter->setPen ( thePen ) ;
	theBrush.setStyle ( Qt::NoBrush ) ;
	painter->setBrush ( theBrush  ) ;
	painter->setFont ( werdz ) ;

	
	QRectF textRect ( page.x(), page.y(), page.width(), displayLineSpacing) ;
	
	fitStringInRect ( textRect, tr("Not yet"), painter, Qt::AlignVCenter | Qt::AlignLeft, 0.90 ) ;

	theBrush.setStyle ( Qt::NoBrush ) ;
	painter->setBrush ( theBrush  ) ;
}

