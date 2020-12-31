//
// $Id: RenderArea--drawRow.cpp,v 1.1.1.1 2008/11/29 01:25:55 igor Exp $
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

void RenderArea::drawRow ( QPainter* painter, QRectF theRect, RowType whatKind, bool addCheckBox )
{	painter->save() ;
	
	QPen thePen = painter->pen() ;
	QBrush theBrush = painter->brush() ;

	QRectF checkBox ( theRect ) ;
	checkBox.setWidth ( .6 * checkBox.height() ) ;
	checkBox.setHeight ( .6 * checkBox.height() ) ;
	checkBox.moveTop ( checkBox.top() + ( .5 * theRect.height() )  - ( .5 * checkBox.height() ) ) ;
	
	QRectF otherBox ( theRect ) ;
	
	if ( addCheckBox )
	{	otherBox.setWidth ( otherBox.width() - ( checkBox.width() / 2.0 ) ) ;
		otherBox.moveLeft ( checkBox.left() + ( checkBox.width() / 2.0 ) ) ;
	}
		
	QRectF leftGrey ( otherBox ) ;
	leftGrey.setRight ( theRect.left() + ( theRect.width() / 8.0 ) ) ;

	QRectF rightGrey ( otherBox ) ;
	rightGrey.setWidth ( theRect.width() / 8.0 ) ;
	rightGrey.moveRight ( otherBox.right() ) ;				

	switch ( (int)whatKind )
	{	case ROW_PLAIN:
			painter->drawRect ( otherBox ) ;
			if ( addCheckBox )
			{	drawShadowedRect ( painter, checkBox, lineColors[0], lineColors[1] ) ;
			}
			break ;
		case ROW_GREY:
			thePen.setColor ( lineColors[3] ) ;
			painter->setPen ( thePen ) ;
			
			theBrush.setColor ( lineColors[5] ) ;
			theBrush.setStyle ( Qt::SolidPattern ) ;
			painter->setBrush ( theBrush ) ;
			
			painter->drawRect ( otherBox ) ;
			if ( addCheckBox )
			{	drawShadowedRect ( painter, checkBox, lineColors[2], lineColors[3] ) ;
			}
			break ;
		case ROW_GREY_STRIPE:
			
			thePen.setColor ( lineColors[5] ) ;
			painter->setPen ( thePen ) ;
			
			theBrush.setColor ( lineColors[5] ) ;
			theBrush.setStyle ( Qt::SolidPattern ) ;
			painter->setBrush ( theBrush ) ;
			painter->drawRect ( leftGrey ) ;
						
			thePen.setColor ( lineColors[3] ) ;
			painter->setPen ( thePen ) ;
			
			theBrush.setStyle ( Qt::NoBrush ) ;
			painter->setBrush ( theBrush ) ;
					
			painter->drawRect ( otherBox ) ;
			if ( addCheckBox )
			{	drawShadowedRect ( painter, checkBox, lineColors[0], lineColors[1] ) ;
			}
			break ;
			
		case ROW_GREY_TWO_STRIPE:
			thePen.setColor ( lineColors[5] ) ;
			painter->setPen ( thePen ) ;
			
			theBrush.setColor ( lineColors[5] ) ;
			theBrush.setStyle ( Qt::SolidPattern ) ;
			painter->setBrush ( theBrush ) ;
			painter->drawRect ( leftGrey ) ;
			painter->drawRect ( rightGrey ) ;

			
			
			thePen.setColor ( lineColors[3] ) ;
			painter->setPen ( thePen ) ;
			
			theBrush.setStyle ( Qt::NoBrush ) ;
			painter->setBrush ( theBrush ) ;
			

			painter->drawRect ( otherBox ) ;
			if ( addCheckBox )
			{	drawShadowedRect ( painter, checkBox, lineColors[0], lineColors[1] ) ;
			}
			break ;
	}

	painter->restore() ;
}

