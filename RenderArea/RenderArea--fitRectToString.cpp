//
// $Id: RenderArea--fitRectToString.cpp,v 1.2 2009/12/17 03:46:59 igor Exp $
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

QRectF RenderArea::fitRectToString ( QRectF theRect, QString theString, QPainter* painter, qreal margin )
{
	QRectF theNewRect = theRect ;
	
	painter->save() ;
	QFont foo = painter->font() ;
	
	foo.setPixelSize ( (int)(margin * theRect.height() ) ) ;
	
	QFontMetrics fm ( foo ) ;
	int textWidthInPixels = fm.width( theString ) ;
	
	theNewRect.setWidth ( (qreal)(textWidthInPixels) + ( theRect.height() / 2.0 ) ) ;
	
	painter->restore() ;
	
	return theNewRect ;
}

