//
// $Id: RenderArea--drawSubHeader.cpp,v 1.5 2009/01/12 03:53:00 igor Exp $
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

/*----
void RenderArea::drawSubHeader ( QPainter* painter, QRectF theRect, qreal labelSize, QString theText )
{
	painter->save() ;
	
	QPen thePen = painter->pen() ;
	QBrush theBrush = painter->brush() ;
	
	
	QRectF smallerBar = theRect ;
	QRectF shorterBar = theRect ;
	QRectF shadowBar ;
	
	smallerBar.setTop ( smallerBar.top() + ( smallerBar.height() / 6 ) ) ;
	shorterBar.setWidth ( labelSize * smallerBar.width() ) ; 
	shadowBar = shorterBar ;
	shadowBar.moveTop ( shadowBar.top() + painter->pen().width()  + painter->pen().width() ) ;
	shadowBar.moveLeft ( shadowBar.left() + painter->pen().width() + painter->pen().width() ) ;
	
	drawGradientBox ( painter, smallerBar, lineColors[1], lineColors[6], GRAD_DOWN, BAR_ROUND ) ;
	
	painter->fillRect ( shadowBar, QBrush ( lineColors[4], Qt::SolidPattern ) ) ;
	
	painter->setBrush ( Qt::white ) ;
	painter->drawRect ( shorterBar ) ;
	
	shorterBar.setWidth ( shorterBar.width() - ( shorterBar.height() / 2.0 ) ) ; 
	shorterBar.setLeft ( shorterBar.left() + ( shorterBar.height() /4.0 ) ) ; 
	
	thePen.setColor ( lineColors[0] ) ;
	painter->setPen ( thePen ) ;
	
	fitStringInRect
		(	shorterBar,
			theText,
			painter,
			Qt::AlignLeft|Qt::AlignVCenter,
			0.90
			) ;
	
	painter->restore() ;
}
---*/


void RenderArea::drawSubHeader ( QPainter* painter, QRectF theRect, qreal labelSize, QString theText )
{	Q_UNUSED(labelSize);
	painter->save() ;
	
	QPen thePen = painter->pen() ;
	QBrush theBrush = painter->brush() ;

	
	QRectF smallerBar = theRect ;
	
	
	QRectF shorterBar = fitRectToString ( theRect, theText, painter, 1.0 ) ;

	QRectF shadowBar ;

	smallerBar.setTop ( smallerBar.top() + ( smallerBar.height() / 6 ) ) ;
	shadowBar = shorterBar ;
	shadowBar.moveTop ( shadowBar.top() + painter->pen().width()  + painter->pen().width() ) ;
	shadowBar.moveLeft ( shadowBar.left() + painter->pen().width() + painter->pen().width() ) ;

	drawGradientBox ( painter, smallerBar, lineColors[1], lineColors[6], GRAD_DOWN, BAR_ROUND ) ;
	
	painter->fillRect ( shadowBar, QBrush ( lineColors[4], Qt::SolidPattern ) ) ;
	
	painter->setBrush ( Qt::white ) ;
	painter->drawRect ( shorterBar ) ;
	
	shorterBar.setWidth ( shorterBar.width() - ( shorterBar.height() / 2.0 ) ) ; 
	shorterBar.setLeft ( shorterBar.left() + ( shorterBar.height() /4.0 ) ) ; 

	thePen.setColor ( lineColors[0] ) ;
	painter->setPen ( thePen ) ;

	fitStringInRect
	(	shorterBar,
		theText,
		painter,
		Qt::AlignLeft|Qt::AlignVCenter,
0.90	) ;

	painter->restore() ;
}

void RenderArea::drawRightHandSubHeader ( QPainter* painter, QRectF theRect, qreal labelSize, QString theText )
{	Q_UNUSED(labelSize);

	painter->save() ;
	
	QPen thePen = painter->pen() ;
	QBrush theBrush = painter->brush() ;
	
	
	QRectF smallerBar = theRect ;
	QRectF shorterBar = fitRectToString ( theRect, theText, painter, 1.0 ) ;
	QRectF shadowBar ;
	
	smallerBar.setTop ( smallerBar.top() + ( smallerBar.height() / 6 ) ) ;
	shorterBar.moveRight ( smallerBar.right() ) ; 
	shadowBar = shorterBar ;
	shadowBar.moveTop ( shadowBar.top() + painter->pen().width()  + painter->pen().width() ) ;
	shadowBar.moveLeft ( shadowBar.left() + painter->pen().width() + painter->pen().width() ) ;
	
	drawGradientBox ( painter, smallerBar, lineColors[1], lineColors[6], GRAD_DOWN, BAR_ROUND_RIGHT ) ;
	
	painter->fillRect ( shadowBar, QBrush ( lineColors[4], Qt::SolidPattern ) ) ;
	
	painter->setBrush ( Qt::white ) ;
	
	painter->drawRect ( shorterBar ) ;
	shorterBar.setWidth ( shorterBar.width() - ( shorterBar.height() / 2.0 ) ) ; 

	thePen.setColor ( lineColors[0] ) ;
	painter->setPen ( thePen ) ;
	
	fitStringInRect
		(	shorterBar,
			theText,
			painter,
			Qt::AlignRight|Qt::AlignVCenter,
			0.90
			) ;
	
	painter->restore() ;
}

