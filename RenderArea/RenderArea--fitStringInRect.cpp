//
// $Id: RenderArea--fitStringInRect.cpp,v 1.3 2009/12/17 03:46:59 igor Exp $
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

void RenderArea::fitStringInRect ( QRectF theRect, QString theString, QPainter* painter, Qt::Alignment flagz, qreal margin )
{
	painter->save() ;
	QFont foo = painter->font() ;
	
	foo.setPixelSize ( (int)(margin * theRect.height() ) ) ;
	
	QFontMetrics fm ( foo ) ;
	int textWidthInPixels = fm.width( theString );

	if ( textWidthInPixels > ( margin * theRect.width() ) )
	{	foo.setStretch	( (int)( ( margin * theRect.width() * 100 ) / textWidthInPixels ) ) ;			
	}

	painter->setFont ( foo ) ;
	painter->drawText ( theRect, flagz, theString ) ;
	
	painter->restore() ;
}

