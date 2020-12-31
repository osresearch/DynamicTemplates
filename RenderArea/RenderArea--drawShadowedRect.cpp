//
// $Id: RenderArea--drawShadowedRect.cpp,v 1.1.1.1 2008/11/29 01:25:55 igor Exp $
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

void RenderArea::drawShadowedRect ( QPainter* painter, QRectF theRect, QColor boxColor, QColor shadowColor )
{	painter->save() ;

	QPen thePen = painter->pen() ;
	QBrush theBrush = painter->brush() ;

	QRectF theBox = theRect ;
	QRectF theShadow = theRect ;
	theShadow.moveTop ( theShadow.top() + ( theShadow.height() / 20 ) ) ; 
	theShadow.moveLeft ( theShadow.left() + ( theShadow.height() / 20 ) ) ; 
	
	theBrush.setColor ( shadowColor ) ;
	theBrush.setStyle ( Qt::SolidPattern ) ;
	painter->setBrush ( theBrush  ) ;
	thePen.setColor ( shadowColor ) ;
	painter->setPen ( thePen ) ;
	
	painter->drawRect ( theShadow ) ;
			
	painter->eraseRect ( theBox ) ;
				
	thePen.setColor ( boxColor ) ;
	painter->setPen ( thePen ) ;
				
	theBrush.setColor ( Qt::white ) ;
	theBrush.setStyle ( Qt::SolidPattern ) ;
			
	painter->setBrush ( theBrush ) ;
				
	painter->drawRect ( theBox ) ;
	
	painter->restore() ;
}

