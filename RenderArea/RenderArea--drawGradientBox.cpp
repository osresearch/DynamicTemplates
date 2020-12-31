//
// $Id: RenderArea--drawGradientBox.cpp,v 1.1.1.1 2008/11/29 01:25:55 igor Exp $
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

/*
void RenderArea::drawGradientBox
(	QPainter*	painter,
	QRectF		theRect,
	QColor		theColor,
	BarType		whatKind
)
{
	painter->save() ;
	painter->setBrush ( theColor ) ;
	drawBar ( painter, theRect, whatKind ) ;	
	painter->restore() ;
}
*/

void RenderArea::drawGradientBox ( QPainter* painter, QRectF theRect, QColor theFirstColor, QColor theSecondColor, GradType whichWay, BarType whatKind )
{
	painter->save() ;
	QLinearGradient theGrad ;

	switch ( (int)whichWay )
	{
		case GRAD_UP:
			theGrad.setStart ( theRect.left(), theRect.bottom() ) ;
			theGrad.setFinalStop ( theRect.left(), theRect.top() ) ;
			break ;
		case GRAD_DOWN:
			theGrad.setStart ( theRect.left(), theRect.top() ) ;
			theGrad.setFinalStop ( theRect.left(), theRect.bottom() ) ;
			break ;
		case GRAD_LEFT:
			theGrad.setStart (theRect.right(), theRect.top() ) ;
			theGrad.setFinalStop ( theRect.left(), theRect.top() ) ;
			break ;
		case GRAD_RIGHT:
			theGrad.setStart ( theRect.left(), theRect.top() ) ;
			theGrad.setFinalStop ( theRect.right(), theRect.top() ) ;
			break ;

	}

	theGrad.setColorAt ( 0, theFirstColor ) ;
	theGrad.setColorAt ( 1, theSecondColor ) ;
	
	painter->setBrush ( theGrad ) ;
	drawBar ( painter, theRect, whatKind ) ;	
	painter->restore() ;
}

