//
// $Id: twoPagePerMonthDrawOneDay.cpp,v 1.4 2009/12/18 03:20:11 igor Exp $
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

void RenderArea::twoPagePerMonthDrawOneDay ( QRectF theRect, QDate drawDay, QPainter* painter, bool thisMonth )
{	painter->save() ;
		
	QFont foo = painter->font() ;
	QPen thePen = painter->pen() ;
	QBrush theBrush = painter->brush() ;
	
	QRectF daySquare = QRectF (  theRect.x(), theRect.y(), theRect.width() / 5.0, theRect.height() / 5.0 ) ;
	
	if ( daySquare.height() > daySquare.width() )
	{
		daySquare.setWidth ( daySquare.height() ) ;
	}

	thePen.setColor ( lineColors[5] ) ;
	theBrush.setColor ( lineColors[5] ) ;
	painter->setPen ( thePen ) ;
	theBrush.setStyle ( Qt::SolidPattern ) ;
	painter->setBrush ( theBrush  ) ;
	
	painter->drawRect ( QRectF ( theRect.x(), theRect.y(), theRect.width(), theRect.height() / 5. ) ) ;

	if ( thisMonth )
	{	thePen.setColor ( lineColors[2] ) ;
		theBrush.setColor ( lineColors[2] ) ;
	}
	else
	{	thePen.setColor ( lineColors[4] ) ;
		theBrush.setColor ( lineColors[4] ) ;
	}
	painter->setPen ( thePen ) ;
	theBrush.setStyle ( Qt::SolidPattern ) ;
	painter->setBrush ( theBrush  ) ;
	
	
	painter->drawRect ( QRectF ( daySquare.x() + (daySquare.width() / 15.0 ), daySquare.y() + (daySquare.height() / 15.0 ), daySquare.width(), daySquare.height() ) ) ;
	painter->eraseRect ( daySquare ) ;

	if ( thisMonth )
	{	thePen.setColor ( lineColors[1] ) ;
		theBrush.setColor ( lineColors[1] ) ;
		painter->setPen ( thePen ) ;
	}
	theBrush.setColor ( Qt::white ) ;
	theBrush.setStyle ( Qt::SolidPattern ) ;
	painter->setBrush ( theBrush ) ;
	
	painter->drawRect ( daySquare ) ;
	
	fitStringInRect
		(	daySquare, 
			QString::number ( drawDay.day() ), 
			painter, 
			Qt::AlignCenter,
			0.95
		) ;
	
	theBrush.setStyle ( Qt::NoBrush ) ;
	painter->setBrush ( theBrush ) ;
	painter->drawRect ( theRect ) ;

	painter->restore() ;
}


