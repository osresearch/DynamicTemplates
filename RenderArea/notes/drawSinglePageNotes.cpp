//
// $Id: drawSinglePageNotes.cpp,v 1.5 2010/01/01 20:22:33 igor Exp $
//
// This file is part of DIY_Notes.
// 
// DIY_Notes is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3 of the License, or
// (at your option) any later version.
// 
// DIY_Notes is distributed in the hope that it will be useful,
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
#include <math.h>

#include <QtDebug>  // this is here for debugging 

#include "RenderArea.h"

void RenderArea::drawSinglePageNotes ( QPainter* painter )
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
// qDebug() << "RenderArea::drawSinglePageNotes -- Page: x = " <<  page.x() << ", y = " << page.y() << ", width = " << page.width() << ", height =" << page.height() ;

	
	int thePixelSize = (  (int)(page.height() / 27.5) ) ;

// qDebug() << "RenderArea::drawSinglePageNotes -- thePixelSize = " <<  thePixelSize ;

	foo.setPixelSize ( thePixelSize ) ;
	
	painter->setFont ( foo ) ;
	
	thePen.setColor ( Qt::black ) ;
	theBrush.setColor ( Qt::black ) ;
	painter->setPen ( thePen ) ;
	theBrush.setStyle ( Qt::NoBrush ) ;
	painter->setBrush ( theBrush  ) ;

	QRectF textRect ;
	
	painter->drawText
	(	QRectF ( page.x(), page.y(), page.width(), thePixelSize ),
		theAlignment | Qt::AlignVCenter,
		titleString,
		&textRect
	) ;
// qDebug() << "RenderArea::drawSinglePageNotes -- textRect: x = " <<  textRect.x() << ", y = " << textRect.y() << ", width = " << textRect.width() << ", height =" << textRect.height() ;
	
	QRectF barRect ( page.x(), textRect.bottom() + ( textRect.height() / 20. ), page.width(),	page.height() / 44. ) ;
	
// qDebug() << "RenderArea::drawSinglePageNotes -- barRect: x = " <<  barRect.x() << ", y = " << barRect.y() << ", width = " << barRect.width() << ", height =" << barRect.height() ;

	
	QLinearGradient theGrad ( barRect.left(), barRect.top(), barRect.left(), barRect.bottom() ) ;
	theGrad.setColorAt(0, lineColors[4] );
	theGrad.setColorAt(1, lineColors[0] );

	painter->fillRect ( barRect, theGrad ) ;
	painter->drawRect ( barRect ) ;
	
	theBrush.setStyle ( Qt::NoBrush ) ;

	painter->setBrush ( theBrush  ) ;
	
	//-------------------------------------------------------------------------------------------
	QRectF greyRectf ;
	QLineF lineToDraw ;
	qreal whereToDraw ;
	qreal howManyTall ;
	qreal howManyWide ;
	QString tempString ;
	QPointF point1 ;
	QPointF point2 ;
	QVector<qreal> dashes ;

	
	// now to draw the lines
	thePen.setColor ( lineColors[2] ) ;
	theBrush.setColor ( Qt::black ) ;
	painter->setPen ( thePen ) ;
	theBrush.setStyle ( Qt::NoBrush ) ;
	painter->setBrush ( theBrush  ) ;
	
	QRectF bodyRect = page ;
	
	bodyRect.setTop ( barRect.bottom() + ( barRect.height() / 4.0 ) ) ;
	
	switch ( theStyle )
	{
		case 40: // Plain Lined
			howManyTall = floor ( bodyRect.height() / displayLineSpacing ) ;
			bodyRect.setHeight ( howManyTall * displayLineSpacing ) ;

			painter->drawRect ( bodyRect ) ;

			lineToDraw = QLineF( bodyRect.top(), bodyRect.left(), bodyRect.top(), bodyRect.right() ) ;
			
			whereToDraw = bodyRect.top() + displayLineSpacing ;
	
			do
			{	lineToDraw = QLineF ( bodyRect.left(), whereToDraw, bodyRect.right(), whereToDraw ) ;
				painter->drawLine ( lineToDraw ) ;
				whereToDraw += displayLineSpacing ;
			} while ( whereToDraw < page.bottom() ) ;
	
			break ;
			
		case 41: // Plain Lined w/Grey Column
			howManyTall = floor ( bodyRect.height() / displayLineSpacing ) ;
			
			bodyRect.setHeight ( howManyTall * displayLineSpacing ) ;
			
			greyRectf = QRectF ( bodyRect.x(), bodyRect.y(), bodyRect.width() / 6, bodyRect.height() ) ;
			
			painter->fillRect ( greyRectf, lineColors[5] ) ;
			
			lineToDraw = QLineF ( bodyRect.top(), bodyRect.left(), bodyRect.top(), bodyRect.right() ) ;
			
			whereToDraw = bodyRect.top() + displayLineSpacing ;
			
			do
			{	lineToDraw = QLineF ( bodyRect.left(), whereToDraw, bodyRect.right(), whereToDraw ) ;
				painter->drawLine ( lineToDraw ) ;
				whereToDraw += displayLineSpacing ;
			} while ( whereToDraw < page.bottom() ) ;
				
			painter->drawRect ( bodyRect ) ;
			break ;
		
		case 42: // Grey Lined w/Grey Column

			howManyTall = floor ( bodyRect.height() / displayLineSpacing ) ;
			
			bodyRect.setHeight ( howManyTall * displayLineSpacing ) ;
			
			greyRectf = QRectF ( bodyRect.x(), bodyRect.y(), bodyRect.width() / 6, bodyRect.height() ) ;
			
			painter->fillRect ( bodyRect, lineColors[6] ) ;
			painter->fillRect ( greyRectf, lineColors[4] ) ;
			
			lineToDraw = QLineF ( bodyRect.top(), bodyRect.left(), bodyRect.top(), bodyRect.right() ) ;
			
			whereToDraw = bodyRect.top() + displayLineSpacing ;
			
			do
			{	lineToDraw = QLineF ( bodyRect.left(), whereToDraw, bodyRect.right(), whereToDraw ) ;
				painter->drawLine ( lineToDraw ) ;
				whereToDraw += displayLineSpacing ;
			} while ( whereToDraw < page.bottom() ) ;
				
			painter->drawRect ( bodyRect ) ;
			break ;
			
		case 43: // Cornell Plain
			
			barRect.moveTop ( bodyRect.top() ) ;
			painter->fillRect ( barRect, lineColors[2] ) ;
			painter->drawRect ( barRect ) ;
			
			painter->drawRect ( QRectF ( page.x(), barRect.top(), 0.3 * page.width(), 0.8 * bodyRect.height() ) ) ;
			
			thePen.setColor ( Qt::white ) ;
			painter->setPen ( thePen ) ;
			
			fitStringInRect
			(	QRectF ( barRect.x() + ( barRect.height() / 3. ), barRect.y(), barRect.width(), barRect.height() ),
				tr("Cues"),
				painter,
				Qt::AlignVCenter | Qt::AlignLeft,
				0.90
			) ;
			
			fitStringInRect
			(	QRectF ( barRect.x() + ( barRect.height() / 3. ) + (0.30 * barRect.width()), barRect.y(), 0.70 * barRect.width(), barRect.height() ),
				tr("Notes"),
				painter,
				Qt::AlignVCenter | Qt::AlignLeft,
				0.90
			) ;
			
			barRect.moveTop ( bodyRect.top() + ( .8 * bodyRect.height() ) ) ;
			painter->fillRect ( barRect, lineColors[2] ) ;
			
			fitStringInRect
			(	QRectF ( barRect.x() + ( barRect.height() / 3. ), barRect.y(), barRect.width(), barRect.height() ),
				tr("Summary"),
				painter,
				Qt::AlignVCenter | Qt::AlignLeft,
				0.90
			) ;

			painter->drawRect ( barRect ) ;

			painter->drawRect ( bodyRect ) ;
			break ;

		case 44: // Cornell w/Grid & Lines
			barRect.moveTop ( bodyRect.top() ) ;
			painter->fillRect ( barRect, lineColors[2] ) ;
			painter->drawRect ( barRect ) ;
			
			painter->drawRect
			(	QRectF ( page.x(),
				barRect.top(),
				0.3 * page.width(),
				0.8 * bodyRect.height() )
			) ;
			
			thePen.setColor ( Qt::white ) ;
			painter->setPen ( thePen ) ;
			
			fitStringInRect
			(	QRectF ( barRect.x() + ( barRect.height() / 3. ), barRect.y(), barRect.width(), barRect.height() ),
				tr("Cues"),
				painter,
				Qt::AlignVCenter | Qt::AlignLeft,
				0.90
			) ;
			
			fitStringInRect
			(	QRectF ( barRect.x() + ( barRect.height() / 3. ) + (0.30 * barRect.width()), barRect.y(), 0.70 * barRect.width(), barRect.height() ),
				tr("Notes"),
				painter,
				Qt::AlignVCenter | Qt::AlignLeft,
				0.90
			) ;
			
			thePen.setColor ( lineColors[2] ) ;
			theBrush.setColor ( Qt::black ) ;
			painter->setPen ( thePen ) ;
			theBrush.setStyle ( Qt::NoBrush ) ;
			painter->setBrush ( theBrush  ) ;
		
			painter->save() ;
			thePen.setWidthF ( 0.50 * (qreal)(thePen.width()) ) ;
			painter->setPen ( thePen ) ;
			
			point1 = QPointF ( displayLineSpacing + barRect.x() + ( 0.30 * barRect.width() ), barRect.bottom() ) ;
			point2 = QPointF ( displayLineSpacing + barRect.x() + ( 0.30 * barRect.width() ), barRect.y() + ( 0.80 * bodyRect.height() ) ) ;
			
			do
			{	lineToDraw = QLineF ( point1, point2 ) ;
				painter->drawLine ( lineToDraw ) ;
				point1.rx() += displayLineSpacing ;
				point2.rx() += displayLineSpacing ;
			} while ( point1.x() < page.right() ) ;
				
			point1 = QPointF ( barRect.x() + ( 0.30 * barRect.width() ), barRect.bottom() + displayLineSpacing ) ;
			point2 = QPointF ( bodyRect.right(), barRect.bottom() + displayLineSpacing ) ;
			
			do
			{	lineToDraw = QLineF ( point1, point2 ) ;
				painter->drawLine ( lineToDraw ) ;
				point1.ry() += displayLineSpacing ;
				point2.ry() += displayLineSpacing ;
			} while ( point1.y() < (barRect.y() + ( 0.80 * bodyRect.height() )) ) ;
				
			painter->restore() ;
			
			barRect.moveTop ( bodyRect.top() + ( .8 * bodyRect.height() ) ) ;
			painter->fillRect ( barRect, QColor(0, 0, 0, 120) ) ;
			
			thePen.setColor ( Qt::white ) ;
			painter->setPen ( thePen ) ;

			fitStringInRect
			(	QRectF ( barRect.x() + ( barRect.height() / 3 ), barRect.y(), barRect.width(), barRect.height() ),
				tr("Summary"),
				painter,
				Qt::AlignVCenter | Qt::AlignLeft,
				0.90
			) ;
			
			painter->drawRect ( barRect ) ;

			painter->save() ;
			
			thePen.setColor ( lineColors[2] ) ;
			theBrush.setColor ( Qt::black ) ;
			painter->setPen ( thePen ) ;
			theBrush.setStyle ( Qt::NoBrush ) ;
			painter->setBrush ( theBrush  ) ;

			dashes << 4 << 4 << 4 << 4 ;

			thePen.setDashPattern ( dashes ) ;
			thePen.setWidthF ( 0.50 * (qreal)(thePen.width()) ) ;
			painter->setPen ( thePen ) ;
			
			point1 = QPointF ( barRect.x(), barRect.bottom() + displayLineSpacing ) ;
			point2 = QPointF ( bodyRect.right(), barRect.bottom() + displayLineSpacing ) ;
			
			do
			{	lineToDraw = QLineF ( point1, point2 ) ;
				painter->drawLine ( lineToDraw ) ;
				point1.ry() += displayLineSpacing ;
				point2.ry() += displayLineSpacing ;
			} while ( point1.y() < bodyRect.bottom() ) ;
				

			painter->restore() ;
			
			painter->drawRect ( bodyRect ) ;
			break ;
			
		case 45: // Grid
			howManyTall = floor ( bodyRect.height() / displayLineSpacing ) ;
			bodyRect.setHeight ( howManyTall * displayLineSpacing ) ;
			
			howManyWide = floor ( bodyRect.width() / displayLineSpacing ) ;
			bodyRect.setWidth ( howManyWide * displayLineSpacing ) ;
			
			bodyRect.moveLeft ( bodyRect.x() + ( ( page.width() - bodyRect.width() ) / 2 ) ) ;

			lineToDraw = QLineF( bodyRect.top(), bodyRect.left(), bodyRect.top(), bodyRect.right() ) ;
			
			whereToDraw = bodyRect.top() + displayLineSpacing ;
			
			do
			{	lineToDraw = QLineF ( bodyRect.left(), whereToDraw, bodyRect.right(), whereToDraw ) ;
				painter->drawLine ( lineToDraw ) ;
				whereToDraw += displayLineSpacing ;
			} while ( whereToDraw < page.bottom() ) ;
				
			
			lineToDraw = QLineF( bodyRect.top(), bodyRect.left(), bodyRect.top(), bodyRect.right() ) ;
			
			whereToDraw = bodyRect.left() + displayLineSpacing ;
			
			do
			{	lineToDraw = QLineF ( whereToDraw, bodyRect.top(), whereToDraw, bodyRect.bottom() ) ;
				painter->drawLine ( lineToDraw ) ;
				whereToDraw += displayLineSpacing ;
			} while ( whereToDraw < page.right() ) ;
				
			painter->drawRect ( bodyRect ) ;
			break ;
			
		case 46: // Dots
			howManyTall = floor ( bodyRect.height() / displayLineSpacing ) ;
			bodyRect.setHeight ( howManyTall * displayLineSpacing ) ;
			
			howManyWide = floor ( bodyRect.width() / displayLineSpacing ) ;
			bodyRect.setWidth ( howManyWide * displayLineSpacing ) ;
			
			bodyRect.moveLeft ( bodyRect.x() + ( ( page.width() - bodyRect.width() ) / 2 ) ) ;
			
			lineToDraw = QLineF( bodyRect.top(), bodyRect.left(), bodyRect.top(), bodyRect.right() ) ;
			
			whereToDraw = bodyRect.top() + displayLineSpacing ;
			
			for ( qreal rows = 1.0 ; rows <= howManyTall ; rows++ )
			{	for ( qreal cols = 0.0 ; cols <= howManyWide ; cols++ )
				{	painter->drawPoint ( QPointF ( bodyRect.x() + ( cols * displayLineSpacing ), bodyRect.y() + ( rows * displayLineSpacing ) ) ) ;
				}
			}
			break ;
			
	}
}	
          
