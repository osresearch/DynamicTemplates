//
// $Id: twoPagePerWeekDrawOneDay.cpp,v 1.6 2010/01/01 20:22:33 igor Exp $
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
#include <QtDebug>  // this is here for debugging 
#include <math.h>
#include "RenderArea.h"


void RenderArea::twoPagePerWeekDrawOneDay ( QRectF theRect, QDate drawDay, QPainter* painter, bool notez )
{
	QFont foo ( "Blue Highway" ) ;
	
	QPen thePen(lineColors[1] , penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
	QBrush theBrush ( Qt::white, Qt::NoBrush ) ;
	
	painter->setPen ( thePen ) ;
	painter->setBrush ( theBrush ) ;
	
	QRectF justAbox = theRect ;
	justAbox.setHeight ( ( floor ( justAbox.height() / displayLineSpacing ) ) * displayLineSpacing ) ;
	
	qreal howMany = justAbox.height() / displayLineSpacing ;
	int bloxToDraw = (int)(howMany) - 1 ;
	

	int thePixelSize = (int)( ( justAbox.height() / (howMany + 1.0) ) ) ;
	foo.setPixelSize ( thePixelSize ) ;
	painter->setFont ( foo ) ;

	QRectF innerBox
	(	theRect.x() + (2. * theRect.width() / 100.),
		theRect.y() + ( justAbox.height() / howMany ),
		96. * theRect.width() / 100.,
		justAbox.height() / howMany
	) ;
	
	QRectF outerBox
	(	innerBox.x() - penWidth,
		innerBox.y() - penWidth,
		innerBox.width() + ( 2. * penWidth ),
		bloxToDraw * innerBox.height() + ( 2. * penWidth )
	) ;
	
	if ( notez )
	{	painter->drawText
		(	QRectF ( theRect.x() + (5. * theRect.width() / 100.),
			theRect.y(),
			theRect.width(),
			justAbox.height() / howMany ),		
			Qt::AlignVCenter,
			tr("* Notes *")
		) ;
	}
	else
	{	painter->drawText
		(	QRectF ( theRect.x() + (5. * theRect.width() / 100.),
			theRect.y(),
			theRect.width(),
			justAbox.height() / howMany ),
			Qt::AlignVCenter,
			drawDay.toString ( "dddd d MMM" )
		) ;
	}

	painter->drawRect ( outerBox ) ;
	
	QTime apptHour = firstAppt ;
	
	for ( int index = 0 ; index < bloxToDraw ; index++ )
	{	innerBox.moveTop ( theRect.y() + ( justAbox.height() / howMany ) + ( index * innerBox.height() ) );
		
		QRectF littleBox ( innerBox.x(), innerBox.y(), 3. * innerBox.height() / 4., 3. * innerBox.height() / 4. ) ;
		QRectF littleBoxShadow
		(	littleBox.x() + ( littleBox.width() / 15. ),
			littleBox.y() + ( littleBox.width() / 15.),
			littleBox.width(),
			littleBox.height()
		) ;
		
		thePen.setColor ( lineColors[1] ) ;
		painter->setPen ( thePen ) ;
		
		if ( !notez)
		{	
			thePen.setColor ( lineColors[2] ) ;
			painter->setPen ( thePen ) ;
			theBrush.setColor ( lineColors[2] ) ;
			theBrush.setStyle ( Qt::SolidPattern ) ;
			painter->setBrush ( theBrush  ) ;
			painter->drawRect ( littleBoxShadow ) ;

			theBrush.setColor ( Qt::white ) ;
			painter->setBrush ( theBrush  ) ;
			painter->drawRect ( littleBox ) ;
			theBrush.setStyle ( Qt::NoBrush ) ;
			painter->setBrush ( theBrush  ) ;
			
			if ( index > 0 && index < (bloxToDraw - 1) )
			{	QString timeString ;
				switch  ( clockType )
				{	case 1: // 12 hour clock	
						timeString = apptHour.toString("h a").section(' ', 0, 0) ;
						break ;
					case 2: // 24 hour clock	
						timeString = apptHour.toString("H") ;
						break ;
					default:
						timeString = "" ;
				}
				
				fitStringInRect ( littleBox, timeString, painter, Qt::AlignCenter, 0.90 ) ;
				apptHour = apptHour.addSecs ( 3600 ) ;
			}
		}
		else
		{	theBrush.setColor ( lineColors[6] ) ;
			theBrush.setStyle ( Qt::SolidPattern ) ;
			painter->setBrush ( theBrush  ) ;
		}
		
		painter->drawRect ( innerBox ) ;
		theBrush.setStyle ( Qt::NoBrush ) ;
		painter->setBrush ( theBrush  ) ;

	}
	
}

