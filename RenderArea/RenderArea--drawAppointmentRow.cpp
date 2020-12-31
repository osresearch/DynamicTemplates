//
// $Id: RenderArea--drawAppointmentRow.cpp,v 1.6 2010/01/01 20:22:33 igor Exp $
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

void RenderArea::drawAppointmentRow ( QPainter* painter, QRectF theRect, ApptBoxType whichBox, QString hour )
{	painter->save() ;

	QFont foo = painter->font() ;
	
	qreal theSize = theRect.height() ;

	switch ( whichBox )
	{
		case APPT_BOX_SINGLE:
		case APPT_BOX_ZERO:
			theSize = theRect.height() ;
			break ;
		case APPT_BOX_DOUBLE:
			theSize = theRect.height() / 2.0 ;
			break ;
		case APPT_BOX_QUAD:
			theSize = theRect.height() / 4.0 ;
			break ;
	}
	
	foo.setPixelSize ( (int)theSize ) ;
	painter->setFont ( foo ) ;

	QPen thePen = painter->pen() ;
	QBrush theBrush = painter->brush() ;
	
	QVector<qreal> dashes;
	dashes << 4 << 4 << 4 << 4 ;

	QRectF checkBox ( theRect ) ;
	checkBox.setWidth ( theSize ) ;
	checkBox.setHeight ( theSize ) ;
	
	QRectF otherBox ( theRect ) ;
	otherBox.setWidth ( otherBox.width() - ( checkBox.width() / 8.0 ) ) ;
	otherBox.moveLeft ( checkBox.left() + ( checkBox.width() / 8.0 ) ) ;
	
	qreal lineY = ( otherBox.top() + checkBox.height() ) ;

	switch ( whichBox )
	{
		case APPT_BOX_SINGLE:
		case APPT_BOX_ZERO:
			break ;
		case APPT_BOX_DOUBLE:
			thePen.setDashPattern ( dashes ) ;
			painter->setPen ( thePen ) ;
			painter->drawLine ( QLineF ( otherBox.left() + checkBox.width(), lineY, otherBox.right(), lineY ) ) ;
			thePen.setStyle(Qt::SolidLine);
			painter->setPen ( thePen ) ;
			if ( ! hour.isNull() )
			{	fitStringInRect
				(	QRectF ( otherBox.left(), lineY, checkBox.width(), checkBox.height() ),
					tr(":30"),
					painter,
					Qt::AlignCenter,
					0.75 
				) ;				
			}
			break ;
		case APPT_BOX_QUAD:
			thePen.setDashPattern ( dashes ) ;
			painter->setPen ( thePen ) ;
			painter->drawLine ( QLineF ( otherBox.left() + checkBox.width(), lineY, otherBox.right(), lineY ) ) ;
			lineY += checkBox.height() ;
			lineY += checkBox.height() ;
			painter->drawLine ( QLineF ( otherBox.left() + checkBox.width(), lineY, otherBox.right(), lineY ) ) ;
			lineY -= checkBox.height() ;
			thePen.setStyle(Qt::SolidLine);
			painter->setPen ( thePen ) ;
			painter->drawLine ( QLineF ( otherBox.left(), lineY, otherBox.right(), lineY ) ) ;
			if ( ! hour.isNull() )
			{	fitStringInRect
				(	QRectF
					(	otherBox.left(),
						otherBox.top() + ( 2.0 * checkBox.height() ),
						checkBox.width(),
						checkBox.height() 
					),
					tr(":30"),
					painter,
					Qt::AlignCenter,
					0.75
				) ;				
			}
			break ;
	}
	
	thePen.setStyle(Qt::SolidLine);
	painter->setPen ( thePen ) ;
	painter->drawRect ( otherBox ) ;

	if ( whichBox != APPT_BOX_ZERO )
	{	drawShadowedRect ( painter, checkBox, lineColors[0], lineColors[1] ) ;
		
		if ( ! hour.isNull() )
		{	thePen.setColor ( lineColors[0] ) ;
			painter->setPen ( thePen ) ;
			fitStringInRect ( checkBox, hour, painter, Qt::AlignCenter, 0.90 ) ;		
		}
	}

	painter->restore() ;
}

