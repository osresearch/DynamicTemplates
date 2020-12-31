//
// $Id: RenderArea--drawOneShortDay.cpp,v 1.2 2009/12/17 03:46:59 igor Exp $
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

void RenderArea::drawOneShortDay ( QRectF theRect, QDate drawDay, QPainter* painter, bool thisMonth )
{	painter->save() ;
	
	QFont foo = painter->font() ;
	QPen thePen = painter->pen() ;
	QBrush theBrush = painter->brush() ;
	
	thePen.setColor ( lineColors[5] ) ;
	theBrush.setColor ( lineColors[5] ) ;
	painter->setPen ( thePen ) ;
	theBrush.setStyle ( Qt::SolidPattern ) ;
	painter->setBrush ( theBrush  ) ;
	
	painter->drawRect ( QRectF ( theRect.x(), theRect.y() + (theRect.height() / 2.0), theRect.width(), theRect.height() / 5.0 ) ) ;
	
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
	
	painter->drawRect ( QRectF ( theRect.x() + (theRect.width() / 75.), theRect.y() + (theRect.height() / 75.) + (theRect.height() / 2.0), theRect.width() / 5., theRect.height() / 5. ) ) ;
	painter->eraseRect ( QRectF ( theRect.x(), theRect.y() + (theRect.height() / 2.0), theRect.width() / 5., theRect.height() / 5. ) ) ;
	
	if ( thisMonth )
	{	thePen.setColor ( lineColors[1] ) ;
		theBrush.setColor ( lineColors[1] ) ;
		painter->setPen ( thePen ) ;
	}
	theBrush.setColor ( Qt::white ) ;
	theBrush.setStyle ( Qt::SolidPattern ) ;
	painter->setBrush ( theBrush ) ;
	
	painter->drawRect ( QRectF ( theRect.x(), theRect.y() + (theRect.height() / 2.0), theRect.width() / 5., theRect.height() / 5. ) ) ;
	
	fitStringInRect
	(	QRectF	( theRect.x(), theRect.y() + (theRect.height() / 2.0), theRect.width() / 5, theRect.height() / 5 ), 
		QString::number ( drawDay.day() ), 
		painter, 
		Qt::AlignCenter,
		0.95
	) ;
	
	theBrush.setStyle ( Qt::NoBrush ) ;
	painter->setBrush ( theBrush ) ;
	painter->drawLine ( QLineF ( theRect.left(), theRect.top() + (theRect.height() / 2.0), theRect.right(), theRect.top() + (theRect.height() / 2.0) ) ) ;
	
	painter->restore() ;
}


