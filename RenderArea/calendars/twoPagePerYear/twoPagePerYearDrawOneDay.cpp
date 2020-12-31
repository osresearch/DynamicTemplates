//
// $Id: twoPagePerYearDrawOneDay.cpp,v 1.3 2009/12/17 03:47:00 igor Exp $
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


void RenderArea::twoPagePerYearDrawOneDay ( QRectF theRect, QDate drawDay, QPainter* painter, bool greyOut )
{	painter->save() ;

	QFont foo ( tr("Blue Highway") ) ;
	QColor tempColor ;
	QColor c2 ;

	painter->setFont ( foo ) ;

	
	QRectF dayBox ( theRect.x(), theRect.y(), theRect.width() / 8., theRect.height() / 4. ) ;
	QRectF outerBox = theRect ;
	
	QPen thePen ( lineColors[0], penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
	if ( !greyOut )
	{	c2 = lineColors[4] ;
	}
	else
	{	c2 = lineColors[6] ;
	}
	
	QBrush theBrush ( c2, Qt::SolidPattern ) ;
	
	painter->setPen ( thePen ) ;
	painter->setBrush ( theBrush ) ;
	painter->drawRect ( outerBox ) ;

	fitStringInRect ( dayBox, QString::number ( drawDay.day() ), painter, Qt::AlignCenter, 0.90 ) ;
		
	theBrush.setStyle ( Qt::NoBrush ) ;
	painter->setBrush ( theBrush ) ;
	
	
	painter->restore() ;
}
   