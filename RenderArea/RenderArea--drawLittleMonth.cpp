//
// $Id: RenderArea--drawLittleMonth.cpp,v 1.6 2009/12/17 03:46:59 igor Exp $
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

void RenderArea::drawLittleMonth ( QPainter* painter, QDate when, QRectF where, bool markToday )
{
	QDate refMonth[7][6] ;
	QDate localDay ;
	QFont foo ( "Blue Highway" ) ;
	QFont dayz ( "Monaco" ) ;
	
	localDay.setDate ( when.year(), when.month(), 1 ) ;
	
	while ( localDay.dayOfWeek() != weekStart )
	{	localDay = localDay.addDays ( -1 ) ;
	}
	
	for ( int week = 0 ; week < 6 ; week++ )
	{	for ( int dow = 0 ; dow < 7 ; dow++ )
	{	refMonth[dow][week] = localDay ;
		localDay = localDay.addDays ( 1 ) ;
	}
	}
	
	QPen thePen(Qt::white, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
	QBrush theBrush ( Qt::white, Qt::SolidPattern ) ;
	
	while ( localDay.dayOfWeek() != weekStart )
	{	localDay = localDay.addDays ( -1 ) ;
	}
	
	painter->save() ;
	painter->translate ( where.x(), where.y() ) ;
	
	foo.setPixelSize ( (int)(where.height() / 6.0) ) ;
	painter->setFont ( foo ) ;
	
	thePen.setColor ( lineColors[1] ) ;
	thePen.setStyle ( Qt::SolidLine ) ;
	
	painter->setPen ( thePen ) ;
	
	theBrush.setStyle ( Qt::SolidPattern ) ;
	theBrush.setColor ( lineColors[1] ) ;
	painter->setBrush ( theBrush  ) ;
	
	painter->drawRect ( QRectF ( 0., 0., where.width(), where.height() / 6. ) ) ;
	
	thePen.setColor ( Qt::white ) ;
	thePen.setStyle ( Qt::SolidLine ) ;
	
	painter->setPen ( thePen ) ;
	
	theBrush.setStyle ( Qt::SolidPattern ) ;
	theBrush.setColor ( Qt::white ) ;
	painter->setBrush ( theBrush  ) ;
	
	QRectF theBox ;
	QString littleDayString ;
	
	painter->drawText
	(	QRectF ( 0., 0., where.width(), where.height() / 6. ),
		Qt::AlignCenter,
		when.toString ( "MMMM" )
	) ;
	
	thePen.setColor ( lineColors[4] ) ;
	painter->setPen ( thePen ) ;
	
	theBrush.setColor ( lineColors[4] ) ;
	painter->setBrush ( theBrush  ) ;
	
	painter->drawRect ( QRectF ( 0., where.height() / 6., where.width(), where.height() / 12. ) ) ;
	
	thePen.setColor ( lineColors[0] ) ;
	painter->setPen ( thePen ) ;
	
	theBrush.setColor ( lineColors[1] ) ;
	painter->setBrush ( theBrush  ) ;
	
	
	for ( int dow = 0 ; dow < 7 ; dow++ )
	{	theBox.setRect
		(	dow * where.width() / 7,
			where.height() / 6.,
			where.width() / 7,
			where.height() / 12.
		) ;
		
		littleDayString = refMonth[dow][0].toString ( "ddd" ) ;
		fitStringInRect ( theBox, littleDayString, painter, Qt::AlignCenter, 0.95 ) ;

	}

	painter->setFont ( dayz ) ;
	
	thePen.setColor ( lineColors[0] ) ;
	painter->setPen ( thePen ) ;
	
	for ( int week = 0 ; week < 6 ; week++ )
	{	for ( int dow = 0 ; dow < 7 ; dow++ )
		{	if ( refMonth[dow][week].month() == when.month() )
			{	
				
				littleDayString = QString::number
				(	refMonth[dow][week].day() 
				) ;
				
				theBox.setRect
				(	dow * where.width() / 7,
					(2 + week) * where.height() / 8,
					where.width() / 7,
					where.height() / 8
				) ;
				
				if ( markToday )
				{
					if ( today == refMonth[dow][week] )
					{	painter->save() ;
						theBrush.setColor ( lineColors[4] ) ;
						painter->setBrush ( Qt::SolidPattern  ) ;
						painter->setBrush ( theBrush  ) ;
						thePen.setColor ( lineColors[4] ) ;
						painter->setPen ( thePen ) ;
						painter->drawRect ( theBox ) ;
						painter->restore() ;
					}
				}
				
				fitStringInRect
				(	theBox,
					littleDayString, 
					painter, 
					Qt::AlignCenter,
					0.80					
				) ;
			}
		}
		if ( refMonth[6][week].month() != when.month() ) break ;
	}
	painter->restore() ;
}

void RenderArea::drawLittleMonthMoleskine ( QPainter* painter, QDate when, QRectF where )
{
	QDate refMonth[7][6] ;
	QDate localDay ;
	QFont foo ( "Blue Highway" ) ;
	QFont dayz ( "Monaco" ) ;
	
	localDay.setDate ( when.year(), when.month(), 1 ) ;
	
	while ( localDay.dayOfWeek() != weekStart )
	{	localDay = localDay.addDays ( -1 ) ;
	}
	
	for ( int week = 0 ; week < 6 ; week++ )
	{	for ( int dow = 0 ; dow < 7 ; dow++ )
		{	refMonth[dow][week] = localDay ;
			localDay = localDay.addDays ( 1 ) ;
		}
	}
	
	while ( localDay.dayOfWeek() != weekStart )
	{	localDay = localDay.addDays ( -1 ) ;
	}
	
	painter->save() ;
	painter->translate ( where.x(), where.y() ) ;
	
	foo.setPixelSize ( (int)(where.height() / 6.0 ) ) ;
	painter->setFont ( foo ) ;
	
	QRectF theBox ;
	QString littleDayString ;
	
	theBox.setRect ( 0.0, 0.0, where.width(),where.height() / 6. ) ;	
	
	fitStringInRect ( theBox, when.toString ( "MMMM" ), painter, Qt::AlignLeft | Qt::AlignVCenter, 0.50 ) ;
		
	for ( int dow = 0 ; dow < 7 ; dow++ )
	{	theBox.setRect
		(	dow * where.width() / 7,
			where.height() / 6.,
			where.width() / 7,
			where.height() / 12.
			) ;
		
		littleDayString = refMonth[dow][0].toString ( "ddd" ) ;
		fitStringInRect ( theBox, littleDayString, painter, Qt::AlignCenter, 0.50 ) ;
		
	}
	
	painter->setFont ( dayz ) ;
	
	for ( int week = 0 ; week < 6 ; week++ )
	{	for ( int dow = 0 ; dow < 7 ; dow++ )
	{	if ( refMonth[dow][week].month() == when.month() )
	{	
		
		littleDayString = QString::number
		(	refMonth[dow][week].day() 
			) ;
		
		theBox.setRect
			(	dow * where.width() / 7,
				(2 + week) * where.height() / 8,
				where.width() / 7,
				where.height() / 8
				) ;
				
		fitStringInRect
			(	theBox,
				littleDayString, 
				painter, 
				Qt::AlignCenter,
				0.40					
				) ;
	}
	}
		if ( refMonth[6][week].month() != when.month() ) break ;
	}
	painter->restore() ;
}

