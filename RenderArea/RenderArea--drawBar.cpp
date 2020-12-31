//
// $Id: RenderArea--drawBar.cpp,v 1.5 2008/12/30 02:56:41 igor Exp $
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


void RenderArea::drawBar ( QPainter* painter, QRectF theRect, BarType whatKind )
{	QPainterPath path;
		
	switch ( (int)whatKind )
	{	case BAR_RECT:
			painter->drawRect ( theRect ) ;
			break ;
		case BAR_ROUND:
			path.moveTo ( theRect.left(), theRect.top() ) ;
			path.lineTo ( theRect.right() - theRect.height(), theRect.top() ) ;
			
			path.arcTo
			(	theRect.right() - theRect.height() - theRect.height(),
				theRect.top(), 
				2* theRect.height(),
				2*theRect.height(), 
				90.0, 
				-88.0
			) ;
			
			path.lineTo ( theRect.right(), theRect.bottom() ) ;
			path.lineTo ( theRect.left(), theRect.bottom() ) ;
			path.closeSubpath ( ) ;
			painter->drawPath( path );
			break ;
		case BAR_ROUND_RIGHT:
			path.moveTo ( theRect.right(), theRect.top() ) ;
			path.lineTo ( theRect.left() + theRect.height(), theRect.top() ) ;
			
			path.arcTo
				(	theRect.left() + theRect.height() - theRect.height(),
					theRect.top(), 
					2* theRect.height(),
					2*theRect.height(), 
					90.0, 
					88.0
				) ;
			
			path.lineTo ( theRect.left(), theRect.bottom() ) ;
			path.lineTo ( theRect.right(), theRect.bottom() ) ;
			path.closeSubpath ( ) ;
			painter->drawPath( path );
			break ;
		case BAR_TRIANGLE_LEFT:
			painter->drawRect ( theRect ) ;
			painter->setBrush( painter->pen().color() ) ;
			path.moveTo ( theRect.left(), theRect.top() ) ;
			
			path.lineTo
			(	theRect.left() - ( theRect.height() / 2 ),
				theRect.top() + ( theRect.height() / 2 ) 
			) ;
			
			path.lineTo ( theRect.left(), theRect.bottom() ) ;
			path.closeSubpath ( ) ;
			painter->drawPath( path );
			break ;
		case BAR_TRIANGLE_RIGHT:
			painter->drawRect ( theRect ) ;
			painter->setBrush( painter->pen().color() ) ;
			path.moveTo ( theRect.right(), theRect.top() ) ;
			
			path.lineTo
			(	theRect.right() + ( theRect.height() / 2 ), 
				theRect.top() + ( theRect.height() / 2 ) 
			) ;
			
			path.lineTo ( theRect.right(), theRect.bottom() ) ;
			path.closeSubpath ( ) ;
			painter->drawPath( path );
			break ;
	}
}

