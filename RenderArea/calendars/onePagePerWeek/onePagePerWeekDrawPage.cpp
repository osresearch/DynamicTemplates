//
// $Id: onePagePerWeekDrawPage.cpp,v 1.3 2009/01/06 03:35:31 igor Exp $
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

void RenderArea::onePagePerWeekDrawPage ( QPainter* painter, bool leftPage, bool linez )
{
	QFont foo ( "Blue Highway" ) ;
	painter->setFont ( foo ) ;
	
	QDate dateToDraw = today ;
	QString pageLabel = tr(" Weekly Planning: ") ;
	QRectF paper = thePaper ;
	QRectF page ;
	
	if ( leftPage )
	{	page  = thePage ;
	}
	else
	{	page = QRectF ( thePaper.width() - thePage.width() - thePage.x(), thePage.y(), thePage.width(), thePage.height() ) ;
	}
	
	if ( today.year() == today.addDays ( 6 ).year() )
	{	pageLabel += today.toString ( "yyyy" ) + " ";
	}
	else
	{	pageLabel += today.toString ( "yyyy" ) + " - " + today.addDays ( 6 ).toString ( "yyyy" ) + " " ;
	}

	int howManyTall = (int)(floor ( page.height() / displayLineSpacing ) ) ;
	int howManyPer = ( howManyTall - 1 ) / 7 ;
	
	QPen thePen(Qt::white, penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
	QBrush theBrush ( Qt::white, Qt::SolidPattern ) ;
	
	QRectF dayBlock ( page.x(),  page.y(), page.width(),  (qreal)(howManyPer) * displayLineSpacing ) ;
	
	// --- "erase" the page ------------------------------------------------------
	painter->setBrush ( theBrush  ) ;
	painter->setPen ( thePen ) ;
	painter->drawRect ( paper ) ;
	
	//-------- Page Top Title ----------------------------------------------------
	
	QRectF textRect = QRectF ( page.x(), page.y(), page.width(), displayLineSpacing ) ;
	
	dayBlock.moveTop ( textRect.bottom() ) ;

	//-----------------------------------------------------------
	theBrush.setStyle ( Qt::SolidPattern ) ;
	theBrush.setColor ( lineColors[1] ) ;
	painter->setBrush ( theBrush  ) ;
	
	painter->drawRect ( textRect ) ;
	
	thePen.setColor ( Qt::white ) ;
	thePen.setStyle ( Qt::SolidLine ) ;
	
	painter->setPen ( thePen ) ;
	
	theBrush.setStyle ( Qt::SolidPattern ) ;
	theBrush.setColor ( Qt::white ) ;
	painter->setBrush ( theBrush  ) ;

	//-----------------------------------------------------------
	if ( leftPage )
	{	fitStringInRect ( textRect, pageLabel, painter, Qt::AlignLeft | Qt::AlignVCenter, 1.0 ) ;
	}
	else
	{	fitStringInRect ( textRect, pageLabel, painter, Qt::AlignRight | Qt::AlignVCenter, 1.0 ) ;
	}
	
	thePen.setColor ( lineColors[0] ) ;
	theBrush.setColor ( lineColors[0] ) ;
	painter->setPen ( thePen ) ;
	theBrush.setStyle ( Qt::NoBrush ) ;
	painter->setBrush ( theBrush  ) ;
	
	for ( int row = 0 ; row < 7 ; row++ )
	{	textRect.moveTop ( dayBlock.top() ) ;

		if ( leftPage )
		{	fitStringInRect ( textRect, dateToDraw.toString ( " ddd d MMM" ), painter, Qt::AlignLeft | Qt::AlignVCenter, 1.0 ) ;
		}
		else
		{	fitStringInRect ( textRect, dateToDraw.toString ( " ddd d MMM" ), painter, Qt::AlignRight | Qt::AlignVCenter, 1.0 ) ;
		}
		
		dateToDraw = dateToDraw.addDays ( 1 ) ;
	
		if ( linez )
		{	for ( int fill = 1 ; fill < howManyPer ; fill++ )
			{	textRect.moveTop ( textRect.bottom() ) ;
				drawRow ( painter, textRect, ROW_PLAIN, false ) ;
			}			
		}
		else
		{	painter->drawRect ( dayBlock ) ;
		}

		
		dayBlock.moveTop ( dayBlock.bottom() ) ;
	}

	theBrush.setStyle ( Qt::NoBrush ) ;
	painter->setBrush ( theBrush  ) ;
}	
