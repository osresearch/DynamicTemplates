//
// $Id: onePagePerMonthDrawPage.cpp,v 1.7 2010/01/01 20:22:33 igor Exp $
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
#include <QLineF>
#include <QTime>
#include <math.h>

#include <QtDebug>  // this is here for debugging 
#include "RenderArea.h"

void RenderArea::onePagePerMonthDrawPage ( QPainter* painter, bool leftPage )
{
	QFont foo ( "Blue Highway" ) ;
		
	QPen thePen ( Qt::white, penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
	QBrush theBrush ( Qt::white, Qt::SolidPattern ) ;
	QRectF paper = thePaper ;
	QRectF page = thePage ;
	
	// --- "erase" the page ------------------------------------------------------
	painter->setBrush ( theBrush  ) ;
	painter->setPen ( thePen ) ;
	painter->drawRect ( paper ) ;
	
	//-------- Page Top Title ----------------------------------------------------

	QRectF dayBlock ;
	bool canAddLines = true ;

	if ( 5.50 * page.width() / 7.0 > page.height() )
	{
		dayBlock = QRectF( page.x(),  page.y(), page.width() / 7.0,  2.0 * page.height() / 11.0 ) ;
		canAddLines = false ;
	}
	else
	{
		dayBlock = QRectF( page.x(),  page.y(), page.width() / 7.0,  page.width() / 7.0 ) ;
	}
		
	int thePixelSize = (int) ( ( page.height() / 11. ) - dayBlock.height() / 8. ) ;
	foo.setPixelSize ( thePixelSize ) ;
	painter->setFont ( foo ) ;	
	
	thePen.setColor ( Qt::black ) ;
	painter->setPen ( thePen ) ;
	theBrush.setStyle ( Qt::NoBrush ) ;
	painter->setBrush ( theBrush  ) ;
	
	if ( leftPage )
	{	painter->drawText ( QRectF ( page.x(), page.y(), page.width(), thePixelSize ), Qt::AlignLeft | Qt::AlignVCenter, today.toString ( "MMMM yyyy" )) ;
	}
	else
	{	painter->drawText ( QRectF ( page.x(), page.y(), page.width(), thePixelSize ), Qt::AlignRight | Qt::AlignVCenter, today.toString ( "MMMM yyyy" ) ) ;
	}
	
	//------------- bar with weekdays ------------------------------------------------------------
	thePen.setColor ( lineColors[2]  ) ;
	painter->setPen ( thePen ) ;
	
	theBrush.setColor ( lineColors[2]  ) ;
	theBrush.setStyle ( Qt::SolidPattern ) ;
	painter->setBrush ( theBrush  ) ;
	
	painter->drawRect
	( 	QRectF ( page.x(),
		page.y() + ( page.height() / 11 ) - (dayBlock.height() / 7.0) ,
		page.width(),
		dayBlock.height() / 8.0 )
	) ;
	
	qreal x = page.x() ;
	foo.setPixelSize ( (int)(dayBlock.height() / 8.0 ) ) ;
	painter->setFont ( foo ) ;
	
	thePen.setColor ( Qt::white ) ;
	painter->setPen ( thePen ) ;
	
	theBrush.setColor ( Qt::white ) ;
	painter->setBrush ( theBrush  ) ;
			
	for ( int loop = 0 ; loop < 7 ; loop++ )
	{	painter->drawText ( QRectF ( x, page.y() + ( page.height() / 11. ) -  (dayBlock.height() / 7.), dayBlock.width(), dayBlock.height() / 8. ), Qt::AlignCenter, thisMonth[loop][0].toString ( "dddd" ) ) ;
		x += dayBlock.width() ;
	}
	
	//-------- Notes column ------------------------------------------------------------------
	
	thePen.setColor ( Qt::black ) ;
	thePen.setStyle ( Qt::SolidLine ) ;
	painter->setPen ( thePen ) ;
	
	theBrush.setColor ( Qt::black ) ;
	painter->setBrush ( theBrush  ) ;
	
	// it is easier to first draw blocks from the next/previous month FIRST
	// That way, the outllines of THIS MONTH's blocks are always on top
	//
	// do the blocks NOT in this month
	
	for ( int column = 0 ; column < 7 ; column++ )
	{	for ( int row = 0 ; row < 5 ; row++ )
		{	if ( (thisMonth[column][row].month()) != today.month() )
			{	dayBlock.moveLeft ( page.x() + ( column * dayBlock.width() ) ) ;
				dayBlock.moveTop ( page.y() + (page.height() / 11.0) + ( row * dayBlock.height() ) ) ;		
				twoPagePerMonthDrawOneDay ( dayBlock, thisMonth[column][row], painter, false ) ;
			}
		}
	}
	
	// now do this month's blocks
	for ( int column = 0 ; column < 7 ; column++ )
	{	for ( int row = 0 ; row < 5 ; row++ )
		{	if ( (thisMonth[column][row].month()) == today.month() )
			{	dayBlock.moveLeft ( page.x() + ( column * dayBlock.width() ) ) ;
				dayBlock.moveTop ( page.y() + (page.height() / 11.0) + ( row * dayBlock.height() ) ) ;		
				twoPagePerMonthDrawOneDay ( dayBlock, thisMonth[column][row], painter, true ) ;
			}
		}
		if (thisMonth[column][5].month() == today.month() )
		{	drawOneShortDay ( dayBlock, thisMonth[column][5], painter, true ) ;
		}
	}
	
	if ( canAddLines )
	{
		QRectF justAbox = page ;
		
		justAbox.setTop ( ( page.y() + (page.height() / 11.0) + ( 5.0 * dayBlock.height() ) ) + ( displayLineSpacing / 2.0 ) ) ;
		justAbox.setBottom ( ( floor ( justAbox.height() / displayLineSpacing ) ) * displayLineSpacing ) ;


		QRectF barRect ( justAbox.x(), justAbox.y(), justAbox.width(), displayLineSpacing ) ;
		thePen.setColor ( Qt::black ) ;
		painter->setPen ( thePen ) ;
		painter->setFont ( foo ) ;
		
		if ( leftPage)
		{	drawSubHeader ( painter, barRect, 0.35, tr("Monthly Notes") ) ;			
		}
		else
		{	drawRightHandSubHeader ( painter, barRect, 0.35, tr("Monthly Notes") ) ;			
		}
		barRect.moveTop ( barRect.bottom() + ( 0.50 * barRect.height() ) ) ;
		
		do
		{	drawRow ( painter, barRect, ROW_GREY_TWO_STRIPE, false ) ;
			barRect.moveTop ( barRect.bottom() ) ;
		} while ( barRect.bottom() <= page.bottom() ) ;
		

	}
	
	theBrush.setStyle ( Qt::NoBrush ) ;	painter->setBrush ( theBrush  ) ;
	return ;
}	
