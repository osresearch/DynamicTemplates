//
// $Id: twoPagePerWeekDrawPage.cpp,v 1.2 2009/01/06 03:35:31 igor Exp $
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

#include "RenderArea.h"

void RenderArea::twoPagePerWeekDrawPage ( QPainter* painter, bool leftPage )
{	QFont foo ( "Blue Highway" ) ;
	painter->setFont ( foo ) ;

	QDate dateToDraw ;
	QString pageLabel ;
	QRectF paper = thePaper ;
	QRectF page  = thePage ;
	
	if ( leftPage )
	{	dateToDraw = today ;
		pageLabel = tr("Weekly Planning:") ;
		page  = thePage ;
	}
	else
	{	dateToDraw = today.addDays ( 4 ) ;
		if ( today.year() == today.addDays ( 6 ).year() )
		{	pageLabel = today.toString ( "yyyy" ) ;
		}
		else
		{	pageLabel = today.toString ( "yyyy" ) + " - " + today.addDays ( 6 ).toString ( "yyyy" ) ;
		}
		page = QRectF ( thePaper.width() - thePage.width() - thePage.x(), thePage.y(), thePage.width(), thePage.height() ) ;
	}
	
	QPen thePen(Qt::white, penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
	QBrush theBrush ( Qt::white, Qt::SolidPattern ) ;
	

	QRectF dayBlock ( page.x(),  page.y(), page.width() / 2.0,  26.0 * page.height() / 55.0 ) ;

	// --- "erase" the page ------------------------------------------------------
	painter->setBrush ( theBrush  ) ;
	painter->setPen ( thePen ) ;
	painter->drawRect ( paper ) ;

	//-------- Page Top Title ----------------------------------------------------
	thePen.setColor ( lineColors[0] ) ;
	theBrush.setColor ( lineColors[0] ) ;
	painter->setPen ( thePen ) ;
	theBrush.setStyle ( Qt::NoBrush ) ;
	painter->setBrush ( theBrush  ) ;
	
	QRectF textRect = QRectF ( page.x(), page.y(), page.width(), 3.0 * page.height() / 55.0 ) ;
	
	if ( leftPage )
	{	fitStringInRect ( textRect, pageLabel, painter, Qt::AlignLeft | Qt::AlignVCenter, 1.0 ) ;
	}
	else
	{	fitStringInRect ( textRect, pageLabel, painter, Qt::AlignRight | Qt::AlignVCenter, 1.0 ) ;
	}

	for ( int row = 0 ; row < 2 ; row++ )
	{	dayBlock.moveTop ( page.y() + ( 3 * page.height() / 55 ) + ( row * dayBlock.height() ) ) ;		
		for ( int column = 0 ; column < 2 ; column++ )
		{	dayBlock.moveLeft ( page.x() + ( column * dayBlock.width() ) ) ;		
			twoPagePerWeekDrawOneDay ( dayBlock, dateToDraw, painter, (today.daysTo(dateToDraw) > 6) ) ;
			dateToDraw = dateToDraw.addDays ( 1 ) ;
		}
	}

	theBrush.setStyle ( Qt::NoBrush ) ;
	painter->setBrush ( theBrush  ) ;
}
       