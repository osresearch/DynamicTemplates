//
// $Id: onePagePerTwoYearsDrawPage.cpp,v 1.4 2009/12/18 03:20:11 igor Exp $
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

void RenderArea::onePagePerTwoYearsDrawPage ( QPainter* painter )
{
	QFont foo ( "Blue Highway" ) ;
	QPen thePen(Qt::white, penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
	QBrush theBrush ( Qt::white, Qt::SolidPattern ) ;
	
	
	QRectF paper = thePaper ;
	QRectF page = thePage ;	
	// --- "erase" the page ------------------------------------------------------
	painter->setBrush ( theBrush  ) ;
	painter->setPen ( thePen ) ;
	painter->drawRect ( paper ) ;
	
	//-------- Page Top Title ----------------------------------------------------
	
	int thePixelSize = ( (int)( 3. * page.height() / 55. ) ) ;
	
	foo.setPixelSize ( thePixelSize ) ;
	
	painter->setFont ( foo ) ;
	
	thePen.setColor ( Qt::black ) ;
	theBrush.setColor ( Qt::black ) ;
	painter->setPen ( thePen ) ;
	theBrush.setStyle ( Qt::NoBrush ) ;
	painter->setBrush ( theBrush  ) ;
	
	QRectF textRect ;
	
	painter->drawText
	(	QRectF ( page.x(),
		page.y(),
		page.width(),
		thePixelSize ),
		Qt::AlignLeft | Qt::AlignVCenter,
		QString( today.toString ( "yyyy" ) + "-" + today.addYears( 1 ).toString ( "yyyy" ) ),
		&textRect
	) ;
		
	QRectF barRect ( page.x(), textRect.bottom() + ( textRect.height() / 20. ), page.width(),	page.height() / 44. ) ;
	
	drawGradientBox ( painter, barRect, lineColors[1], lineColors[6], GRAD_DOWN, BAR_RECT ) ;
	
	theBrush.setStyle ( Qt::NoBrush ) ;
	
	painter->setBrush ( theBrush  ) ;
	
	//-------------------------------------------------------------------------------------------
	
	barRect.moveTop ( barRect.bottom() + ( displayLineSpacing / 2.0 ) ) ;
	
	QRectF bodyRect = barRect ;
	
	
	QRectF littleRect ;
	QRectF monthRect ;
	QDate daMonth ( today.year(), 1, 1 ) ;
	
	bodyRect.setBottom ( page.bottom() ) ;

	int howManyTall = (int)( floor ( bodyRect.height() / displayLineSpacing ) ) ;
	
	bodyRect.setHeight ( howManyTall * displayLineSpacing ) ;
	
	
	barRect.moveLeft ( barRect.left() + ( 2.0 *  barRect.width() / 3.0 ) ) ;
	barRect.setWidth ( barRect.width() / 3.0 ) ;
	barRect.setHeight ( displayLineSpacing ) ;
	
	drawSubHeader ( painter, barRect, 0.750, tr("Special Dates") ) ;
	barRect.moveTop ( barRect.bottom() + ( 0.50 * barRect.height() ) ) ;
	
	do
	{	drawRow ( painter, barRect, ROW_GREY_STRIPE, false ) ;
		barRect.moveTop ( barRect.bottom() ) ;
	} while ( barRect.bottom() <= page.bottom() ) ;
	
	//-------------------------------------------------------------------------------------------
	bodyRect.setWidth ( 0.95 * 2.0 * bodyRect.width() / 3.0 ) ;
	bodyRect.setHeight ( bodyRect.height() / 2.0 ) ;
	
	barRect.setRect ( bodyRect.x(), bodyRect.y(), bodyRect.width(), displayLineSpacing ) ;
	drawSubHeader ( painter, barRect, 0.40, today.toString ( "yyyy" ) ) ;
	
	barRect.moveTop ( barRect.bottom() + ( 0.1250 * barRect.height() ) ) ;
	littleRect.setRect ( barRect.x(), barRect.y(), bodyRect.width() / 3.0, ( bodyRect.bottom() - barRect.top() ) / 4.0 ) ;
	
	monthRect.setRect ( littleRect.x(), littleRect.y(), 0.98 * littleRect.width(), littleRect.height() ) ;
	drawLittleMonth ( painter, daMonth, monthRect, false )  ;    
	daMonth = daMonth.addMonths ( 1 ) ;
	
	littleRect.moveLeft ( littleRect.right() ) ;	
	monthRect.setRect ( littleRect.x() + ( 0.01 * littleRect.width() ), littleRect.y(), 0.98 * littleRect.width(), littleRect.height() ) ;
	drawLittleMonth ( painter, daMonth, monthRect, false )  ;  
	daMonth = daMonth.addMonths ( 1 ) ;
	
	littleRect.moveLeft ( littleRect.right() ) ;
	monthRect.setRect ( littleRect.x() + ( 0.02 * littleRect.width() ), littleRect.y(), 0.98 * littleRect.width(), littleRect.height() ) ;
	drawLittleMonth ( painter, daMonth, monthRect, false )  ;   
	daMonth = daMonth.addMonths ( 1 ) ;
	
	
	littleRect.moveTop ( littleRect.bottom() ) ;
	littleRect.moveLeft ( barRect.x() ) ;
	
	monthRect.setRect ( littleRect.x(), littleRect.y(), 0.98 * littleRect.width(), littleRect.height() ) ;
	drawLittleMonth ( painter, daMonth, monthRect, false )  ;    
	daMonth = daMonth.addMonths ( 1 ) ;
	
	littleRect.moveLeft ( littleRect.right() ) ;	
	monthRect.setRect ( littleRect.x() + ( 0.01 * littleRect.width() ), littleRect.y(), 0.98 * littleRect.width(), littleRect.height() ) ;
	drawLittleMonth ( painter, daMonth, monthRect, false )  ;  
	daMonth = daMonth.addMonths ( 1 ) ;
	
	littleRect.moveLeft ( littleRect.right() ) ;
	monthRect.setRect ( littleRect.x() + ( 0.02 * littleRect.width() ), littleRect.y(), 0.98 * littleRect.width(), littleRect.height() ) ;
	drawLittleMonth ( painter, daMonth, monthRect, false )  ;   
	daMonth = daMonth.addMonths ( 1 ) ;
	
	
	littleRect.moveTop ( littleRect.bottom() ) ;
	littleRect.moveLeft ( barRect.x() ) ;
	
	monthRect.setRect ( littleRect.x(), littleRect.y(), 0.98 * littleRect.width(), littleRect.height() ) ;
	drawLittleMonth ( painter, daMonth, monthRect, false )  ;    
	daMonth = daMonth.addMonths ( 1 ) ;
	
	littleRect.moveLeft ( littleRect.right() ) ;	
	monthRect.setRect ( littleRect.x() + ( 0.01 * littleRect.width() ), littleRect.y(), 0.98 * littleRect.width(), littleRect.height() ) ;
	drawLittleMonth ( painter, daMonth, monthRect, false )  ;  
	daMonth = daMonth.addMonths ( 1 ) ;
	
	littleRect.moveLeft ( littleRect.right() ) ;
	monthRect.setRect ( littleRect.x() + ( 0.02 * littleRect.width() ), littleRect.y(), 0.98 * littleRect.width(), littleRect.height() ) ;
	drawLittleMonth ( painter, daMonth, monthRect, false )  ;   
	daMonth = daMonth.addMonths ( 1 ) ;
	
	
	littleRect.moveTop ( littleRect.bottom() ) ;
	littleRect.moveLeft ( barRect.x() ) ;
	
	monthRect.setRect ( littleRect.x(), littleRect.y(), 0.98 * littleRect.width(), littleRect.height() ) ;
	drawLittleMonth ( painter, daMonth, monthRect, false )  ;    
	daMonth = daMonth.addMonths ( 1 ) ;
	
	littleRect.moveLeft ( littleRect.right() ) ;	
	monthRect.setRect ( littleRect.x() + ( 0.01 * littleRect.width() ), littleRect.y(), 0.98 * littleRect.width(), littleRect.height() ) ;
	drawLittleMonth ( painter, daMonth, monthRect, false )  ;  
	daMonth = daMonth.addMonths ( 1 ) ;
	
	littleRect.moveLeft ( littleRect.right() ) ;
	monthRect.setRect ( littleRect.x() + ( 0.02 * littleRect.width() ), littleRect.y(), 0.98 * littleRect.width(), littleRect.height() ) ;
	drawLittleMonth ( painter, daMonth, monthRect, false )  ;   
	daMonth = daMonth.addMonths ( 1 ) ;
	
	//-------------------------------------------------------------------------------------------
	bodyRect.moveTop ( bodyRect.bottom() ) ;
	barRect.setRect ( bodyRect.x(), bodyRect.y(), bodyRect.width(), displayLineSpacing ) ;
	barRect.setHeight ( displayLineSpacing ) ;
	drawSubHeader ( painter, barRect, 0.250, today.addYears( 1 ).toString ( "yyyy" ) ) ;
	
	barRect.moveTop ( barRect.bottom() + ( 0.1250 * barRect.height() ) ) ;
	
	littleRect.setRect ( barRect.x(), barRect.y(), bodyRect.width() / 3.0, ( bodyRect.bottom() - barRect.top() ) / 4.0 ) ;
	monthRect.setRect ( littleRect.x(), littleRect.y(), 0.98 * littleRect.width(), littleRect.height() ) ;
	drawLittleMonth ( painter, daMonth, monthRect, false )  ;    
	daMonth = daMonth.addMonths ( 1 ) ;
	
	littleRect.moveLeft ( littleRect.right() ) ;	
	monthRect.setRect ( littleRect.x() + ( 0.01 * littleRect.width() ), littleRect.y(), 0.98 * littleRect.width(), littleRect.height() ) ;
	drawLittleMonth ( painter, daMonth, monthRect, false )  ;  
	daMonth = daMonth.addMonths ( 1 ) ;
	
	littleRect.moveLeft ( littleRect.right() ) ;
	monthRect.setRect ( littleRect.x() + ( 0.02 * littleRect.width() ), littleRect.y(), 0.98 * littleRect.width(), littleRect.height() ) ;
	drawLittleMonth ( painter, daMonth, monthRect, false )  ;   
	daMonth = daMonth.addMonths ( 1 ) ;
	
	
	littleRect.moveTop ( littleRect.bottom() ) ;
	littleRect.moveLeft ( barRect.x() ) ;
	
	monthRect.setRect ( littleRect.x(), littleRect.y(), 0.98 * littleRect.width(), littleRect.height() ) ;
	drawLittleMonth ( painter, daMonth, monthRect, false )  ;    
	daMonth = daMonth.addMonths ( 1 ) ;
	
	littleRect.moveLeft ( littleRect.right() ) ;	
	monthRect.setRect ( littleRect.x() + ( 0.01 * littleRect.width() ), littleRect.y(), 0.98 * littleRect.width(), littleRect.height() ) ;
	drawLittleMonth ( painter, daMonth, monthRect, false )  ;  
	daMonth = daMonth.addMonths ( 1 ) ;
	
	littleRect.moveLeft ( littleRect.right() ) ;
	monthRect.setRect ( littleRect.x() + ( 0.02 * littleRect.width() ), littleRect.y(), 0.98 * littleRect.width(), littleRect.height() ) ;
	drawLittleMonth ( painter, daMonth, monthRect, false )  ;   
	daMonth = daMonth.addMonths ( 1 ) ;
	
	
	littleRect.moveTop ( littleRect.bottom() ) ;
	littleRect.moveLeft ( barRect.x() ) ;
	
	monthRect.setRect ( littleRect.x(), littleRect.y(), 0.98 * littleRect.width(), littleRect.height() ) ;
	drawLittleMonth ( painter, daMonth, monthRect, false )  ;    
	daMonth = daMonth.addMonths ( 1 ) ;
	
	littleRect.moveLeft ( littleRect.right() ) ;	
	monthRect.setRect ( littleRect.x() + ( 0.01 * littleRect.width() ), littleRect.y(), 0.98 * littleRect.width(), littleRect.height() ) ;
	drawLittleMonth ( painter, daMonth, monthRect, false )  ;  
	daMonth = daMonth.addMonths ( 1 ) ;
	
	littleRect.moveLeft ( littleRect.right() ) ;
	monthRect.setRect ( littleRect.x() + ( 0.02 * littleRect.width() ), littleRect.y(), 0.98 * littleRect.width(), littleRect.height() ) ;
	drawLittleMonth ( painter, daMonth, monthRect, false )  ;   
	daMonth = daMonth.addMonths ( 1 ) ;
	
	
	littleRect.moveTop ( littleRect.bottom() ) ;
	littleRect.moveLeft ( barRect.x() ) ;
	
	monthRect.setRect ( littleRect.x(), littleRect.y(), 0.98 * littleRect.width(), littleRect.height() ) ;
	drawLittleMonth ( painter, daMonth, monthRect, false )  ;    
	daMonth = daMonth.addMonths ( 1 ) ;
	
	littleRect.moveLeft ( littleRect.right() ) ;	
	monthRect.setRect ( littleRect.x() + ( 0.01 * littleRect.width() ), littleRect.y(), 0.98 * littleRect.width(), littleRect.height() ) ;
	drawLittleMonth ( painter, daMonth, monthRect, false )  ;  
	daMonth = daMonth.addMonths ( 1 ) ;
	
	littleRect.moveLeft ( littleRect.right() ) ;
	monthRect.setRect ( littleRect.x() + ( 0.02 * littleRect.width() ), littleRect.y(), 0.98 * littleRect.width(), littleRect.height() ) ;
	drawLittleMonth ( painter, daMonth, monthRect, false )  ;   
	daMonth = daMonth.addMonths ( 1 ) ;
	
}	
