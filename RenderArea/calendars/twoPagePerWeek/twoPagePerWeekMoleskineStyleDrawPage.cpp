 //
 // $Id: twoPagePerWeekMoleskineStyleDrawPage.cpp,v 1.3 2010/01/01 20:22:33 igor Exp $
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

#include <QPrinter>
#include <QPainter>
#include <QtDebug>  // this is here for debugging 
#include <math.h>
#include "RenderArea.h"

void RenderArea:: drawMoleVerticalLeft ( QPainter* painter, QRectF page, QDate date )
{
	Q_UNUSED ( date ) ;
	Q_UNUSED ( page ) ;
	Q_UNUSED ( painter ) ;
}

void RenderArea:: drawMoleVerticalRight ( QPainter* painter, QRectF page, QDate date )
{
	Q_UNUSED ( date ) ;
	Q_UNUSED ( page ) ;
	Q_UNUSED ( painter ) ;
}

void RenderArea:: drawMoleHorizontalLeft ( QPainter* painter, QRectF page, QDate date )
{
	Q_UNUSED ( date ) ;
	Q_UNUSED ( page ) ;
	Q_UNUSED ( painter ) ;
}

void RenderArea:: drawMoleHorizontalRight ( QPainter* painter, QRectF page, QDate date )
{
	Q_UNUSED ( date ) ;
	Q_UNUSED ( page ) ;
	Q_UNUSED ( painter ) ;
}

void RenderArea:: drawMoleNotebookLeft ( QPainter* painter, QRectF page, QDate date )
{
	QRectF textRect ;
	QDate dateToDraw = date ;
	QPen thePen = painter->pen() ;
	QBrush theBrush = painter->brush() ;
	
	int howManyTall = (int)(floor ( page.height() / displayLineSpacing ) ) ;
	int howManyPer = howManyTall / 7 ;
	QRectF dayBlock ( page.x(),  page.y(), page.width(),  (qreal)(howManyPer) * displayLineSpacing ) ;

	thePen.setColor ( lineColors[0] ) ;
	theBrush.setColor ( lineColors[0] ) ;
	painter->setPen ( thePen ) ;
	theBrush.setStyle ( Qt::NoBrush ) ;
	painter->setBrush ( theBrush  ) ;

	// center it vertically
	dayBlock.moveTop ( page.top() + ( ( page.height() - ( (qreal)(howManyPer * 7) * displayLineSpacing) ) ) / 2.0 ) ;
	textRect = QRectF ( dayBlock.x(), dayBlock.y(), dayBlock.width(), displayLineSpacing / 2.0 ) ;
	
	if ( dateToDraw.month() == dateToDraw.addDays(6).month() )
	{	fitStringInRect ( textRect, dateToDraw.toString ( " MMMM" ), painter, Qt::AlignLeft | Qt::AlignVCenter, 0.750 ) ;
	}
	else
	{	fitStringInRect ( textRect, dateToDraw.toString ( " MMMM -" ) + dateToDraw.addDays(6).toString ( " MMMM" ), painter, Qt::AlignLeft | Qt::AlignVCenter, 0.750 ) ;
	}
	fitStringInRect ( textRect, QString ( tr("Week %1") ).arg( dateToDraw.weekNumber(NULL) ), painter, Qt::AlignRight | Qt::AlignVCenter, 0.750 ) ;
	
	
	dayBlock.moveTop ( dayBlock.bottom() ) ;

	for ( int row = 0 ; row < 6 ; row++ )
	{	textRect = QRectF ( dayBlock.x(), dayBlock.y(), dayBlock.width(), displayLineSpacing / 2.0 ) ;
		fitStringInRect ( textRect, dateToDraw.toString ( " dddd" ), painter, Qt::AlignLeft | Qt::AlignVCenter, 0.750 ) ;
		textRect.moveTop ( textRect.bottom() ) ;
		fitStringInRect ( textRect, dateToDraw.toString ( " d" ), painter, Qt::AlignLeft | Qt::AlignVCenter, 0.750 ) ;

		painter->drawLine ( QLineF ( dayBlock.left(), dayBlock.top(), dayBlock.right(), dayBlock.top() ) ) ;
		if ( row != 5)
		{	painter->drawLine ( QLineF ( dayBlock.left(), dayBlock.bottom(), dayBlock.right(), dayBlock.bottom() ) ) ;
		}

		dateToDraw = dateToDraw.addDays ( 1 ) ;
		dayBlock.moveTop ( dayBlock.bottom() ) ;
	}
	textRect.moveBottom ( textRect.top() ) ;
	fitStringInRect ( textRect, dateToDraw.toString ( "dddd " ), painter, Qt::AlignRight | Qt::AlignVCenter, 0.750 ) ;
	textRect.moveTop ( textRect.bottom() ) ;
	fitStringInRect ( textRect, dateToDraw.toString ( "d " ), painter, Qt::AlignRight | Qt::AlignVCenter, 0.750 ) ;
}

void RenderArea:: drawMoleNotebookRight ( QPainter* painter, QRectF page )
{
	QPen thePen = painter->pen() ;
	QBrush theBrush = painter->brush() ;
	
	thePen.setColor ( lineColors[2] ) ;
	theBrush.setColor ( lineColors[2] ) ;
	painter->setPen ( thePen ) ;
	theBrush.setStyle ( Qt::NoBrush ) ;
	painter->setBrush ( theBrush  ) ;
	
	int howManyTall = (int)(floor ( page.height() / displayLineSpacing ) ) ;
	int howManyPer = howManyTall / 7 ;
	
	qreal centering = ( page.height() - ( (qreal)(howManyPer * 7) * displayLineSpacing) ) / 2.0 ;

	while ( centering > displayLineSpacing )
	{
		centering -= displayLineSpacing ;
	}

	qreal whereToDraw = page.top() + centering ;
	QLineF lineToDraw = QLineF( whereToDraw, page.left(), whereToDraw, page.right() ) ;
	
	
	do
	{	lineToDraw = QLineF ( page.left(), whereToDraw, page.right(), whereToDraw ) ;
		painter->drawLine ( lineToDraw ) ;
		whereToDraw += displayLineSpacing ;
	} while ( whereToDraw < ( page.bottom() + centering ) ) ;
}

void RenderArea:: drawMoleLandscapeTop ( QPainter* painter, QRectF page, QString daLabel, QDate date )
{
	QRectF textRect = QRectF ( page.x(), page.y(), page.width(), displayLineSpacing ) ;

	textRect.moveTop ( textRect.bottom() ) ;
	textRect.setWidth ( textRect.width() / 4.0 ) ;
	textRect.moveLeft ( page.x() ) ;
	
	for ( int column = 0 ; column < 3 ; column++ )
	{	fitStringInRect ( textRect, date.addDays(column).toString ( "dddd" ), painter, Qt::AlignLeft | Qt::AlignVCenter, 0.750 ) ;
		textRect.moveLeft ( textRect.right() ) ;
	}
	
	textRect.moveTop ( textRect.bottom() ) ;
	textRect.moveLeft ( page.x() ) ;
	
	
	for ( int column = 0 ; column < 3 ; column++ )
	{	fitStringInRect ( textRect, date.addDays(column).toString ( "d" ), painter, Qt::AlignLeft | Qt::AlignVCenter, 0.750 ) ;
		textRect.moveLeft ( textRect.right() ) ;
	}
	
	textRect.moveTop ( textRect.bottom() ) ;
	
	painter->drawLine ( QLineF ( page.left(), textRect.top(), page.left() + ( 0.73 * page.width() ), textRect.top() ) ) ;
	painter->drawLine ( QLineF ( page.left() + ( 0.75 * page.width() ), textRect.top(), page.right(), textRect.top() ) ) ;
	
	textRect.moveLeft ( page.left() + ( 0.75 * page.width() ) ) ;
	fitStringInRect ( textRect, daLabel, painter, Qt::AlignLeft | Qt::AlignVCenter, 0.500 ) ;
	
	textRect.moveTop ( textRect.bottom() ) ;
	
	painter->drawLine ( QLineF ( page.left(), textRect.top(), page.left() + ( 0.73 * page.width() ), textRect.top() ) ) ;
	painter->drawLine ( QLineF ( page.left() + ( 0.75 * page.width() ), textRect.top(), page.right(), textRect.top() ) ) ;
}

void RenderArea:: drawMoleLandscapeColumn ( QPainter* painter, QRectF box )
{
	QTime apptHour = firstAppt ;
	
	box.setHeight ( floor ( box.height() / displayLineSpacing ) * displayLineSpacing ) ;
	int howMany = (int)( box.height() / displayLineSpacing ) ;
	
	QRectF littleBox = QRectF ( box.x(), box.y(), box.width(), displayLineSpacing ) ;
	
	for ( int row = 1 ; row < howMany ; row++ )
	{	QString timeString ;
		switch  ( clockType )
		{	case 1: // 12 hour clock	
			timeString = apptHour.toString("h a").section(' ', 0, 0) ;
			break ;
		case 2: // 24 hour clock	
			timeString = apptHour.toString("H") ;
			break ;
		default:
			timeString = "" ;
		}
		
		fitStringInRect ( littleBox, timeString, painter, Qt::AlignLeft | Qt::AlignVCenter, 0.50 ) ;
		painter->drawLine ( QLineF ( box.left(), littleBox.bottom(), box.left() + ( 0.92 * box.width() ), littleBox.bottom() ) ) ;
		littleBox.moveTop ( littleBox.bottom() ) ;
		apptHour = apptHour.addSecs ( 3600 ) ;
	}
	painter->drawLine ( QLineF ( box.left(), littleBox.bottom(), box.left() + ( 0.92 * box.width() ), littleBox.bottom() ) ) ;
}

void RenderArea:: drawMoleLandscapeLeft ( QPainter* painter, QRectF page, QDate date )
{

	QDate dateToDraw = date ;
	QPen thePen = painter->pen() ;
	QBrush theBrush = painter->brush() ;
	
	thePen.setColor ( lineColors[2] ) ;
	theBrush.setColor ( lineColors[2] ) ;
	painter->setPen ( thePen ) ;
	theBrush.setStyle ( Qt::NoBrush ) ;
	painter->setBrush ( theBrush  ) ;

	QRectF textRect = QRectF ( page.x(), page.y(), page.width(), displayLineSpacing ) ;
	
	if ( dateToDraw.month() == dateToDraw.addDays(6).month() )
	{	fitStringInRect ( textRect, dateToDraw.toString ( " MMMM" ), painter, Qt::AlignRight | Qt::AlignVCenter, 0.750 ) ;
	}
	else
	{	fitStringInRect ( textRect, dateToDraw.toString ( " MMMM -" ) + dateToDraw.addDays(6).toString ( " MMMM" ), painter, Qt::AlignRight | Qt::AlignVCenter, 0.750 ) ;
	}
	
	drawMoleLandscapeTop ( painter, page, tr("To Do"), dateToDraw ) ;

	textRect = QRectF ( page.x(), page.y() + ( 4.0 * displayLineSpacing ), page.width() / 4.0, page.height() - ( 4.0 * displayLineSpacing ) ) ;
	
	for (int col = 0 ; col < 3 ; col++ )
	{	drawMoleLandscapeColumn ( painter, textRect ) ;
		textRect.moveLeft ( textRect.right() ) ;
	}

	textRect.setHeight ( floor ( textRect.height() / displayLineSpacing ) * displayLineSpacing ) ;
	
	int howMany = ( (int)( textRect.height() / displayLineSpacing ) / 2 ) - 1 ;
	
	QRectF littleBox = QRectF ( textRect.x(), textRect.y() + ( (qreal)(howMany) * displayLineSpacing ), textRect.width(), displayLineSpacing ) ;

	painter->drawLine ( QLineF ( textRect.left(), littleBox.bottom(), textRect.left() + ( 0.92 * textRect.width() ), littleBox.bottom() ) ) ;
	littleBox.moveTop ( littleBox.bottom() ) ;
	fitStringInRect ( littleBox, tr("Errands"), painter, Qt::AlignLeft | Qt::AlignVCenter, 0.500 ) ;
	painter->drawLine ( QLineF ( textRect.left(), littleBox.bottom(), textRect.left() + ( 0.92 * textRect.width() ), littleBox.bottom() ) ) ;
	painter->drawLine ( QLineF ( textRect.left(), textRect.bottom(), textRect.left() + ( 0.92 * textRect.width() ), textRect.bottom() ) ) ;
}

void RenderArea:: drawMoleLandscapeRight ( QPainter* painter, QRectF page, QDate date )
{
	QDate dateToDraw = date ;
	QPen thePen = painter->pen() ;
	QBrush theBrush = painter->brush() ;
	
	thePen.setColor ( lineColors[2] ) ;
	theBrush.setColor ( lineColors[2] ) ;
	painter->setPen ( thePen ) ;
	theBrush.setStyle ( Qt::NoBrush ) ;
	painter->setBrush ( theBrush  ) ;
	
	QRectF textRect = QRectF ( page.x(), page.y(), page.width(), displayLineSpacing ) ;
	
	fitStringInRect ( textRect, QString ( tr("Week %1") ).arg( dateToDraw.addDays(-3).weekNumber(NULL) ), painter, Qt::AlignRight | Qt::AlignVCenter, 0.750 ) ;

	drawMoleLandscapeTop ( painter, page, tr("Notes"), dateToDraw ) ;

	textRect = QRectF ( page.x(), page.y() + ( 4.0 * displayLineSpacing ), page.width() / 4.0, page.height() - ( 4.0 * displayLineSpacing ) ) ;
	
	for (int col = 0 ; col < 2 ; col++ )
	{	drawMoleLandscapeColumn ( painter, textRect ) ;
		textRect.moveLeft ( textRect.right() ) ;
	}
	
	textRect.setHeight ( floor ( textRect.height() / displayLineSpacing ) * displayLineSpacing ) ;
	
	int howMany = (int)( textRect.height() / displayLineSpacing ) ;
	QRectF littleBox = QRectF ( textRect.x(), textRect.y(), textRect.width(), displayLineSpacing ) ;
	
	bool addSunday = true ;
	for ( int row = 0 ; row < howMany ; row++ )
	{	if ( ( row > ( howMany / 2 ) - 1 ) && addSunday )
		{   fitStringInRect ( littleBox, date.addDays(3).toString ( "dddd" ), painter, Qt::AlignLeft | Qt::AlignVCenter, 0.750 ) ;
			littleBox.moveTop ( littleBox.bottom() ) ;
			row++ ;
			fitStringInRect ( littleBox, date.addDays(3).toString ( "d" ), painter, Qt::AlignLeft | Qt::AlignVCenter, 0.750 ) ;
			addSunday = false ;
		}
		
		painter->drawLine ( QLineF ( textRect.left(), littleBox.bottom(), textRect.left() + ( 0.92 * textRect.width() ), littleBox.bottom() ) ) ;
		littleBox.moveTop ( littleBox.bottom() ) ;
	}
	
	textRect.moveLeft ( textRect.right() ) ;
	howMany = ((int)( textRect.height() / displayLineSpacing ) / 2 ) + 2 ;
	
	littleBox = QRectF ( textRect.x(), textRect.y() + ( (qreal)(howMany) * displayLineSpacing ), textRect.width(), displayLineSpacing ) ;
	littleBox.setBottom ( textRect.bottom() ) ;
	painter->drawLine ( QLineF ( textRect.left(), littleBox.top(), textRect.left() + ( 0.92 * textRect.width() ), littleBox.top() ) ) ;

	drawLittleMonthMoleskine ( painter, date.addDays(3), littleBox ) ;
	
	painter->drawLine ( QLineF ( textRect.left(), textRect.bottom(), textRect.left() + ( 0.92 * textRect.width() ), textRect.bottom() ) ) ;
}

void RenderArea::twoPagePerWeekMoleskineStyleDrawPage ( QPainter* painter, moleskineType which, bool leftPage )
{	QFont foo ( "Blue Highway" ) ;
	painter->setFont ( foo ) ;
	
	QDate dateToDraw = today ;
	QString pageLabel ;
	QRectF paper = thePaper ;
	QRectF page  = thePage ;
	
	if ( leftPage )
	{	page  = thePage ;
	}
	else
	{	dateToDraw = today.addDays ( 3 ) ;
		page = QRectF ( thePaper.width() - thePage.width() - thePage.x(), thePage.y(), thePage.width(), thePage.height() ) ;
	}

	QPen thePen(Qt::white, penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
	QBrush theBrush ( Qt::white, Qt::SolidPattern ) ;
	
	// --- "erase" the page ------------------------------------------------------
	painter->setBrush ( theBrush  ) ;
	painter->setPen ( thePen ) ;
	painter->drawRect ( paper ) ;
	
	switch ( which )
	{
		case MOLE_VERTICAL:
			if ( leftPage )
			{	drawMoleVerticalLeft ( painter, page, dateToDraw ) ;				
			}
			else
			{	drawMoleVerticalRight ( painter, page, dateToDraw ) ;
			}
			break ;
		case MOLE_HORIZINTAL:
			if ( leftPage )
			{	drawMoleHorizontalLeft ( painter, page, dateToDraw ) ;				
			}
			else
			{	drawMoleHorizontalRight ( painter, page, dateToDraw ) ;
			}
			break ;
		case MOLE_NOTEBOOK:
			if ( leftPage )
			{	drawMoleNotebookLeft ( painter, page, dateToDraw ) ;				
			}
			else
			{	drawMoleNotebookRight ( painter, page ) ;
			}
			break ;
		case MOLE_LANDSCAPE:
			if ( leftPage )
			{	drawMoleLandscapeLeft ( painter, page, dateToDraw ) ;				
			}
			else
			{	drawMoleLandscapeRight ( painter, page, dateToDraw ) ;
			}
			break ;
		default:
			break ;
	} ;

	
}
