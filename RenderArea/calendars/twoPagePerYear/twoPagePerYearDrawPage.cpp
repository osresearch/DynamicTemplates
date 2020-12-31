//
// $Id: twoPagePerYearDrawPage.cpp,v 1.3 2009/12/17 03:47:00 igor Exp $
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
#include <QLinearGradient>


#include <QtDebug>  // this is here for debugging 

#include "RenderArea.h"

void RenderArea::twoPagePerYearDrawPage ( QPainter* painter, bool leftPage )
{
	QFont foo ( tr("Blue Highway") ) ;
	painter->setFont ( foo ) ;
	
	QPen thePen(Qt::white, penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
	QBrush theBrush ( Qt::white, Qt::SolidPattern ) ;
	
	QRectF paper = thePaper ;
	
	QRectF page ;
	
	if ( leftPage )
	{	page = thePage ;
	}
	else
	{	page = QRectF
		(	thePaper.width() - thePage.width() - thePage.x(),
			thePage.y(),
			thePage.width(),
			thePage.height()
		) ;
	}
		
	// --- "erase" the page ------------------------------------------------------
	painter->setBrush ( theBrush  ) ;
	painter->setPen ( thePen ) ;
	painter->drawRect ( paper ) ;

	//-------- Page Top Title ----------------------------------------------------
	thePen.setColor ( Qt::black ) ;
	painter->setPen ( thePen ) ;
	QString leftLabel ;

	if ( theYear[6][0].year() == theYear[0][52].year() )
	{	leftLabel = QObject::tr("Calendar Year ") + theYear[6][0].toString ( tr("yyyy") ) ;		
	}
	else
	{	leftLabel = QObject::tr("Calendar Year ") + theYear[0][0].toString ( tr("yyyy") ) + tr(" - ") + theYear[6][52].toString ( tr("yyyy") ) ;
	}
	
	QRectF tempRect = QRectF ( page.x(), page.y(), page.width(), page.height() / 20.0 ) ;
		
	if ( leftPage )
	{	fitStringInRect ( tempRect, leftLabel, painter, Qt::AlignLeft | Qt::AlignVCenter, 0.90 ) ;
	}
	else
	{	fitStringInRect ( tempRect, leftLabel, painter, Qt::AlignRight | Qt::AlignVCenter, 0.90 ) ;
	}		

	theBrush.setStyle ( Qt::NoBrush ) ;
	painter->setBrush ( theBrush  ) ;
	//--------------------------------------------------------------------------
	QRectF barRect ( page.x(), tempRect.bottom() + ( tempRect.height() / 20. ), page.width(), page.height() / 50. ) ;

	QLinearGradient theGrad ( barRect.left(), barRect.top(), barRect.left(), barRect.bottom() ) ;
	theGrad.setColorAt(0, lineColors[5]);
	theGrad.setColorAt(1, lineColors[0] );

	painter->fillRect ( barRect, theGrad ) ;
	painter->drawRect ( barRect ) ;

	theBrush.setStyle ( Qt::NoBrush ) ;

	painter->setBrush ( theBrush  ) ;
	
	barRect.moveTop ( barRect.bottom() + (barRect.height() / 4) ) ;
	if ( leftPage )
	{	barRect.setLeft ( barRect.left() + (5 * barRect.height() / 4) ) ;
	}
	else
	{	barRect.setRight ( barRect.right() - (5 * barRect.height() / 4) ) ;
	}

	
	painter->fillRect ( barRect, lineColors[1] ) ;
	
	QPointF topLeft = QPointF ( barRect.left(), barRect.bottom() + (barRect.height() / 4.) ) ;

	QSizeF theSize ;
	
	if ( leftPage)
	{
		theSize = QSizeF ( page.right() - topLeft.x(), page.bottom() - topLeft.y() ) ;
	}
	else
	{
		theSize = QSizeF( barRect.width(), page.bottom() - topLeft.y() ) ;
		
	}

	QSizeF theBoxSize ( theSize.width() / 7., theSize.height() / 27. ) ;
	
	if ( leftPage )
	{	tempRect = QRectF ( page.x(), topLeft.y(), barRect.height(), page.height() ) ;
	}
	else
	{	tempRect = QRectF ( page.right() - barRect.height(), topLeft.y(), barRect.height(), page.height() ) ;
	}

	tempRect.setBottom ( page.bottom() ) ;
	
	painter->fillRect ( tempRect, lineColors[1] ) ;
	
	thePen.setColor ( Qt::white ) ;
	painter->setPen ( thePen ) ;
	
	theBrush.setColor ( Qt::white ) ;
	painter->setBrush ( theBrush  ) ;
	
	for ( int column = 0 ; column < 7 ; column++ )
	{	QRectF dowRect ( barRect.x() + (column * barRect.width() / 7.), barRect.y(), barRect.width() / 7., barRect.height() ) ;
		fitStringInRect ( dowRect, theYear[column][0].toString ( tr("dddd") ), painter, Qt::AlignCenter, 0.90 ) ;
	}

	for ( int row = 0 ; row < 6 ; row++ )
	{	painter->save() ;
		QRectF monthRect ;

		if ( leftPage )
		{	painter->translate ( tempRect.left(), tempRect.top() + ( (row + 1) * tempRect.height() / 6) ) ;
			painter->rotate ( -90 ) ;
			monthRect = QRectF( 0.0, 0.0, tempRect.height() / 6.0, barRect.height() ) ;
			fitStringInRect ( monthRect, today.addMonths(row).toString ( tr("MMMM") ), painter, Qt::AlignCenter, 0.90 ) ;
		}
		else
		{	painter->translate ( tempRect.right(), tempRect.top() + ( (row) * tempRect.height() / 6) ) ;
			painter->rotate ( 90 ) ;
			monthRect = QRectF( 0.0, 0.0, tempRect.height() / 6.0, barRect.height() ) ;
			fitStringInRect ( monthRect, today.addMonths(row + 6).toString ( tr("MMMM") ), painter, Qt::AlignCenter, 0.90 ) ;
		}

		painter->restore() ;
	}
	
	int rowStart, rowStop, rowMinus ;
	
	if ( leftPage )
	{	rowStart = 0 ;
		rowStop  = 27 ;
		rowMinus = 0 ;
	}
	else
	{	rowStart = 26 ;
		rowStop  = 53 ;
		rowMinus = 26 ;
	}
	
		
	for ( int column = 0 ; column < 7 ; column++ )
	{	for ( int row = rowStart ; row < rowStop ; row++ )
		{	QRectF dayBlock
			(	topLeft.x() + ( column * theBoxSize.width() ),
				topLeft.y() + ( (row - rowMinus) * theBoxSize.height() ),
				theBoxSize.width(),
				theBoxSize.height()
			) ;
			
			twoPagePerYearDrawOneDay ( dayBlock, theYear[column][row], painter, (theYear[column][row].month() % 2) ) ;
		}
	}

	theBrush.setStyle ( Qt::NoBrush ) ;
	painter->setBrush ( theBrush ) ;

}

