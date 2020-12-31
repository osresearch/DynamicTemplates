//
// $Id: RenderArea--sets.cpp,v 1.14 2009/12/17 03:46:59 igor Exp $
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

void RenderArea::setFirstDayOfWeek ( Qt::DayOfWeek which )
{
	weekStart = which ;
	update() ;
}

void RenderArea::setLineSpacing ( qreal theLineSize )
{
	lineSpacing = theLineSize ;
	displayLineSpacing = lineSpacing * resolution ;

//	qDebug() << "RenderArea::setLineSpacing: displayLineSpacing = " << displayLineSpacing ;	

	update() ;
}

void RenderArea::setMarginSize ( QRectF theSize )
{	
	thePage.setX ( theSize.x() * resolution ) ;
	thePage.setY ( theSize.y() * resolution ) ;
	thePage.setHeight ( theSize.height() * resolution ) ;
	thePage.setWidth ( theSize.width() * resolution ) ;
	
	update() ;
}

void RenderArea::setPageSize ( QRectF theSize )
{	
	thePaper.setX ( theSize.x() * resolution ) ;
	thePaper.setY ( theSize.y() * resolution ) ;
	thePaper.setHeight ( theSize.height() * resolution ) ;
	thePaper.setWidth ( theSize.width() * resolution ) ;
	
	displayHeight = thePaper.height() * scale ;
	displayWidth = thePaper.width()  * scale ;
	
	// theStyle indicates single page (00 - 99) or double page (100 - 199) templates
	if ( theStyle >= 100 )
	{
		displayWidth *= 2.0 ;
	}
	
	this->resize( (int)displayWidth, (int)displayHeight ) ;
	update() ;
}

void RenderArea::setPenWidth(int value)
{	penWidth = (float) value / 10.0 ;
	update();
}

void RenderArea::setSpan ( int which )
{
	whatKind = (RenderArea::calendarSpanType)which ;
}


void RenderArea::setTemplate ( int which )
{	theStyle = which ;
	displayHeight = thePaper.height() * scale ;
	displayWidth = thePaper.width()  * scale ;
	
	// theStyle indicates single page (00 - 99) or double page (100 - 199) templates
	if ( theStyle >= 100 )
	{
		displayWidth *= 2.0 ;
	}
	
	this->resize( (int)displayWidth, (int)displayHeight ) ;

	update() ;
}

void RenderArea::setScale( double value)
{	scale = value / 100.0 ;
	
	displayHeight = thePaper.height() * scale ;
	displayWidth = thePaper.width()  * scale ;
	
	// theStyle indicates single page (00 - 99) or double page (100 - 199) templates
	if ( theStyle >= 100 )
	{
		displayWidth *= 2.0 ;
	}

	this->resize( (int)displayWidth, (int)displayHeight ) ;
	
    update();
}

QDate RenderArea::getStartDate ( void )
{	return startDate ;
}

QDate RenderArea::getStopDate ( void )
{	return stopDate ;
}

void RenderArea::setDate ( const QDate& theDate )
{	today = theDate ;
	
	QDate localDay ;
	QDate anotherLocalDay ;
	
	localDay.setDate ( theDate.year(), theDate.month(), 1 ) ; // I want the first of the month
	
	while ( localDay.dayOfWeek() != weekStart )
	{	localDay = localDay.addDays ( -1 ) ;
	}
	
	anotherLocalDay = localDay ;
	
	// OK, I should now have the date of the upper left of the cal
	for ( int week = 0 ; week < 6 ; week++ )
	{	for ( int dow = 0 ; dow < 7 ; dow++ )
		{	thisMonth[dow][week] = localDay ;
			localDay = localDay.addDays ( 1 ) ;
		}
	}
	
	localDay = anotherLocalDay ;
	
	for ( int week = 0 ; week < 54 ; week++ )
	{	for ( int dow = 0 ; dow < 7 ; dow++ )
		{	theYear[dow][week] = localDay ;
			localDay = localDay.addDays ( 1 ) ;
		}
	}
	
	
	update() ;
}

void RenderArea::startDateChanged ( const QDate& theDate )
{	startDate = theDate ;
//	qDebug() << "RenderArea::startDateChanged to " << startDate.toString ( "dddd d MMMM yyyy" ) ;
	update() ;
}

void RenderArea::stopDateChanged ( const QDate& theDate )
{	stopDate = theDate ;
	update() ;
}

void RenderArea::firstApptTimeChanged ( const QTime& theTime )
{	firstAppt = theTime ;
	update();
}

void RenderArea::apptTimeTypeChanged ( int which )
{	clockType = which ;
	update();
}

QSize RenderArea::minimumSize() const
{	return QSize( (int)(thePaper.width()) / 10, (int)(thePaper.height()) / 10 );
}

QSize RenderArea::sizeHint() const
{	return QSize( (int)thePaper.width(), (int)thePaper.height() );
}

void RenderArea::setText ( QString theString )
{	titleString = theString ;
	update();
}

QString RenderArea::getText ( void )
{	return titleString ;
}

void RenderArea::setAlignment (Qt::Alignment value)
{
	theAlignment = value ;
	update();
}

