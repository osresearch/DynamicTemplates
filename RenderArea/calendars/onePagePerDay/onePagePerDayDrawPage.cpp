//
// $Id: onePagePerDayDrawPage.cpp,v 1.4 2010/01/01 20:22:33 igor Exp $
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
#include <QLinearGradient>
#include <QLineF>
#include <QTime>
#include <math.h>

#include <QtDebug>  // this is here for debugging 
#include "RenderArea.h"

void RenderArea::onePagePerDayDrawPage ( QPainter* painter, bool leftPage, int whatKind )
{
	QFont foo ( "Blue Highway" ) ;
	QPen thePen(Qt::white, penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
	QBrush theBrush ( Qt::white, Qt::SolidPattern ) ;
	qreal whereToDraw ;
	QLineF lineToDraw ;
	QRectF barRect ; 
	
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
	{	page = QRectF
		(	thePaper.width() - thePage.width() - thePage.x(),
			thePage.y(),
			thePage.width(),
			thePage.height()
		) ;
	}
	
	QRectF justAbox = QRectF( thePage.x(), thePage.y() + ( 1.5 * displayLineSpacing ), thePage.width(), thePage.height() - ( 1.5 * displayLineSpacing ) ) ;
	
	switch ( whatKind )
	{
		case 0: // lined
			justAbox.setHeight ( ( floor ( justAbox.height() / displayLineSpacing ) ) * displayLineSpacing ) ;
			break;
		case 1: // grid
			justAbox.setHeight ( ( floor ( justAbox.height() / displayLineSpacing ) ) * displayLineSpacing ) ;
			justAbox.setWidth ( ( floor ( justAbox.width() / displayLineSpacing ) ) * displayLineSpacing ) ;
			justAbox.moveLeft ( thePage.x() + ( ( thePage.width() - justAbox.width() ) / 2.0 ) ) ;
			break;
		case 2: // plain
			break;
		default:
			break ;
	}
	
	barRect = QRectF( justAbox.x(), thePage.y(), justAbox.width(), displayLineSpacing ) ;
	
	thePen.setColor ( Qt::black ) ;
	painter->setPen ( thePen ) ;
	painter->setFont ( foo ) ;
	
	if ( leftPage )
	{	drawSubHeader ( painter, barRect, 0.50, today.toString ( "dddd d MMMM yyyy" ) ) ;
	}
	else
	{	drawRightHandSubHeader ( painter, barRect, 0.50, today.toString ( "dddd d MMMM yyyy" ) ) ;
	}

	barRect.moveTop ( barRect.bottom() + ( 0.50 * barRect.height() ) ) ;
	
	switch ( whatKind )
	{
		case 0: // lined
			do
			{	drawRow ( painter, barRect, ROW_GREY_TWO_STRIPE, false ) ;
				barRect.moveTop ( barRect.bottom() ) ;
			} while ( barRect.bottom() <= page.bottom() ) ;
			break;
		case 1: // grid
			painter->drawRect ( justAbox ) ;

			whereToDraw = justAbox.top() ;
			
			do
			{	lineToDraw = QLineF ( justAbox.left(), whereToDraw, justAbox.right(), whereToDraw ) ;
				painter->drawLine ( lineToDraw ) ;
				whereToDraw += displayLineSpacing ;
			} while ( whereToDraw < justAbox.bottom() ) ;
			
			whereToDraw = justAbox.left() ;
				
			do
			{	lineToDraw = QLineF ( whereToDraw, justAbox.top(), whereToDraw, justAbox.bottom() ) ;
				painter->drawLine ( lineToDraw ) ;
				whereToDraw += displayLineSpacing ;
			} while ( whereToDraw < justAbox.right() ) ;

			break;

		case 2: // plain
			barRect.moveBottom ( justAbox.bottom() ) ;
			painter->drawRect ( barRect ) ;
			break;
		default:
			break ;
	}
	
	
	theBrush.setStyle ( Qt::NoBrush ) ;
	painter->setBrush ( theBrush  ) ;
	
}	
