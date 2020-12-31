//
// $Id: twoPagePerDayDrawOtherPage.cpp,v 1.4 2009/01/06 03:35:31 igor Exp $
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
#include <math.h>
// #include <QtDebug>  // this is here for debugging 
#include "RenderArea.h"

void RenderArea::twoPagePerDayDrawOtherPage ( QPainter* painter, bool leftPage )
{
	QFont foo ( "Blue Highway" ) ;
	QPen thePen(Qt::white, penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
	QBrush theBrush ( Qt::white, Qt::SolidPattern ) ;
	
	// --- "erase" the page ------------------------------------------------------
	QRectF paper = thePaper ;
	painter->setBrush ( theBrush  ) ;
	painter->setPen ( thePen ) ;
	painter->drawRect ( paper ) ;
	
	QRectF page ;
	
	if ( leftPage )
	{	page = thePage ;
	}
	else
	{
		page = QRectF
		(	thePaper.width() - thePage.width() - thePage.x(),
			thePage.y(),
			thePage.width(),
			thePage.height()
		) ;
	}
	
	QRectF justAbox = page ;
	
	justAbox.setBottom ( ( floor ( justAbox.height() / displayLineSpacing ) ) * displayLineSpacing ) ;
	
	QRectF barRect ( justAbox.x(), justAbox.y(), justAbox.width(), displayLineSpacing ) ;
	
	thePen.setColor ( Qt::black ) ;
	painter->setPen ( thePen ) ;
	painter->setFont ( foo ) ;

	drawSubHeader ( painter, barRect, 0.35, tr("Daily Journal") ) ;
	barRect.moveTop ( barRect.bottom() + ( 0.50 * barRect.height() ) ) ;
	
	do
	{	drawRow ( painter, barRect, ROW_GREY_TWO_STRIPE, false ) ;
		barRect.moveTop ( barRect.bottom() ) ;
	} while ( barRect.bottom() <= page.bottom() ) ;
	
	theBrush.setStyle ( Qt::NoBrush ) ;
	painter->setBrush ( theBrush  ) ;
}

