//
// $Id: twoPagePerMonthDrawPage.cpp,v 1.8 2010/01/01 20:22:33 igor Exp $
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
// #include <QtDebug>  // this is here for debugging 
#include <math.h>
#include "RenderArea.h"

void RenderArea::twoPagePerMonthDrawPage ( QPainter* painter, bool leftPage )
{
	
	QFont foo ( "Blue Highway" ) ;
	
	QPen thePen ( Qt::white, penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
	QBrush theBrush ( Qt::white, Qt::SolidPattern ) ;
		
	QRectF paper = thePaper ;
	
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

	QRectF dayBlock ( page.x(),  page.y(), page.width() / 4.0,  2.0 * page.height() / 11.0 ) ;
		
	// --- "erase" the page ------------------------------------------------------
	painter->setBrush ( theBrush  ) ;
	painter->setPen ( thePen ) ;
	painter->drawRect ( paper ) ;

	//-------- Page Top Title ----------------------------------------------------

	int thePixelSize = (int)(( page.height() / 11. ) - dayBlock.height() / 8. ) ;
	foo.setPixelSize ( thePixelSize ) ;
	painter->setFont ( foo ) ;	
	
	thePen.setColor ( Qt::black ) ;
	painter->setPen ( thePen ) ;
	theBrush.setStyle ( Qt::NoBrush ) ;
	painter->setBrush ( theBrush  ) ;
	
	if ( leftPage )
	{	painter->drawText ( QRectF ( page.x(), page.y(), page.width(), thePixelSize ), Qt::AlignLeft | Qt::AlignVCenter, tr("Monthly Planning:") ) ;		
	}
	else
	{	painter->drawText ( QRectF ( page.x(), page.y(), page.width(), thePixelSize ), Qt::AlignRight | Qt::AlignVCenter, today.toString ( "MMMM yyyy" ) ) ;
	}

	//------------- bar with weekdays ------------------------------------------------------------
	thePen.setColor ( lineColors[2]  ) ;
	painter->setPen ( thePen ) ;

	theBrush.setColor ( lineColors[2]  ) ;
	theBrush.setStyle ( Qt::SolidPattern ) ;
	painter->setBrush ( theBrush  ) ;

	painter->drawRect
	( 	QRectF ( page.x(),
		page.y() + ( page.height() / 11. ) - (dayBlock.height() / 7.) ,
		page.width(),
		dayBlock.height() / 8. )
	) ;

	if ( leftPage )
	{	painter->eraseRect
		( 	QRectF ( page.x() + ( 95. * dayBlock.width() / 100. ),
			page.y() + ( page.height() / 11. ) - (dayBlock.height() / 7.) - penWidth,
			dayBlock.width() - ( 95. * dayBlock.width() / 100. ),
			penWidth + penWidth + dayBlock.height() / 8. )
		) ;
	}
	
	qreal x = page.x() ;
	foo.setPixelSize ( (int)(dayBlock.height() / 8.) ) ;
	painter->setFont ( foo ) ;
	
	thePen.setColor ( Qt::white ) ;
	painter->setPen ( thePen ) ;

	theBrush.setColor ( Qt::white ) ;
	painter->setBrush ( theBrush  ) ;

	if ( leftPage )
	{	painter->drawText ( QRectF ( x, page.y() + ( page.height() / 11. ) - (dayBlock.height() / 7.), ( 95. * dayBlock.width() / 100. ), dayBlock.height() / 8. ), Qt::AlignCenter, tr("* Notes") ) ;

		for ( int loop = 0 ; loop < 3 ; loop++ )
		{	x += dayBlock.width() ;
			painter->drawText ( QRectF ( x, page.y() + ( page.height() / 11. ) -  (dayBlock.height() / 7.), dayBlock.width(), dayBlock.height() / 8. ), Qt::AlignCenter, thisMonth[loop][0].toString ( "dddd" ) ) ;
		}
	}
	else
	{	for ( int loop = 3 ; loop < 7 ; loop++ )
		{	painter->drawText ( QRectF ( x, page.y() + ( page.height() / 11. ) -  (dayBlock.height() / 7.), dayBlock.width(), dayBlock.height() / 8. ), Qt::AlignCenter, thisMonth[loop][0].toString ( "dddd" ) ) ;
			x += dayBlock.width() ;
		}
	}

	//-------- Notes column ------------------------------------------------------------------

	if ( leftPage )
	{
		QRectF dashBox
		(	page.x(),
			page.y() + page.height() / 11.0,
			95. * dayBlock.width() / 100. ,
			dayBlock.height() * 4.
		) ;
		
		dashBox.setHeight ( ( floor ( dashBox.height() / displayLineSpacing ) ) * displayLineSpacing ) ;
		int howMany = (int)(dashBox.height() / displayLineSpacing) ;
		
		theBrush.setColor ( lineColors[6] ) ;
		painter->setBrush ( theBrush  ) ;
		
		thePen.setColor ( lineColors[6] ) ;
		painter->setPen ( thePen ) ;
		
		painter->drawRect
		(	 QRectF ( dashBox.x(),
			 dashBox.y(),
			 dashBox.width() / 5.,
			 dashBox.height() )
		) ;
		
		thePen.setColor ( lineColors[3] ) ;
		painter->setPen ( thePen ) ;
			
		theBrush.setStyle ( Qt::NoBrush ) ;
		painter->setBrush ( theBrush  ) ;
		
		painter->drawRect ( dashBox ) ;
		
		QVector<qreal> dashes;
		dashes	<< 4 << 4 << 4 << 4 ;

		thePen.setDashPattern ( dashes ) ;
		thePen.setColor ( lineColors[3] ) ;
		painter->setPen ( thePen ) ;

		qreal y = page.y() + 
		((	(qreal)page.height()    ) / 11.0 ) + 
		( displayLineSpacing ) ;
		
		//--------------------------------------------------------------------------			
		for ( int row = 0 ; row < howMany ; row++ )
		{	painter->drawLine
			(	QLineF
				(	page.x(),
					y,
					page.x() + dashBox.width(),
					y 
				) 
			) ;

			y += displayLineSpacing ;
		}
		//--------------------------------------------------------------------------

		thePen.setColor ( Qt::black ) ;
		thePen.setStyle ( Qt::SolidLine ) ;
		painter->setPen ( thePen ) ;
		
		theBrush.setStyle ( Qt::SolidPattern ) ;
		theBrush.setColor ( Qt::black ) ;
		painter->setBrush ( theBrush  ) ;
		
		//--------------------------------------------------------------------------
		// draw thew two little months here
		QRectF littleMonthRect
		(	page.x() + ( dashBox.width() /3 ),
			page.y() + ( 9.0 * ((qreal) page.height()) / 11.0 ) + ( 5 * dayBlock.height() / 100 ),
			2 * dashBox.width() / 3,
			45 * dayBlock.height() / 100
		) ;

		drawLittleMonth ( painter, today.addMonths ( -1 ), littleMonthRect, false ) ;

		littleMonthRect.moveTop ( page.y() + ( 10.0 * ((qreal) page.height()) / 11.0 ) + ( 5. * dayBlock.height() / 100. ) ) ;

		drawLittleMonth ( painter, today.addMonths ( 1 ), littleMonthRect, false ) ;
		
		thePen.setColor ( lineColors[5] ) ;
		thePen.setStyle ( Qt::SolidLine ) ;
		painter->setPen ( thePen ) ;
	
		theBrush.setStyle ( Qt::SolidPattern ) ;
		theBrush.setColor ( lineColors[5] ) ;
		painter->setBrush ( theBrush  ) ;
		
		painter->drawRect
		(	QRectF ( page.x(),
			page.y() + ( 9.0 * ((qreal) page.height()) / 11.0 ) + ( 5. * dayBlock.height() / 100. ),
			90. * dashBox.width() / 300.,
			95. * dayBlock.height() / 100. ) 
		) ;
	}
	
	thePen.setColor ( Qt::black ) ;
	thePen.setStyle ( Qt::SolidLine ) ;
	painter->setPen ( thePen ) ;
	
	theBrush.setColor ( Qt::black ) ;
	painter->setBrush ( theBrush  ) ;

	// it is easier to first draw blocks from the next/previous month FIRST
	// That way, the outllines of THIS MONTH's blocks are always on top
	//
	// do the blocks NOT in this month
	
	int startColumn ;
	int columnToDraw ;
	
	if ( leftPage)
	{	startColumn = 1 ;
	}
	else
	{	startColumn = 0 ;
	}
	
	for ( int column = startColumn ; column < 4 ; column++ )
	{	for ( int row = 0 ; row < 5 ; row++ )
		{	if ( leftPage )
		{	columnToDraw = column - 1 ;
			}
			else
			{	columnToDraw = column + 3 ;
			}
				
			if ( (thisMonth[columnToDraw][row].month()) != today.month() )
			{	dayBlock.moveLeft ( page.x() + ( column * dayBlock.width() ) ) ;
				dayBlock.moveTop ( page.y() + (page.height() / 11.0) + ( row * dayBlock.height() ) ) ;		
				twoPagePerMonthDrawOneDay ( dayBlock, thisMonth[columnToDraw][row], painter, false ) ;
			}
		}
	}
	
	// now do this month's blocks
	for ( int column = startColumn ; column < 4 ; column++ )
	{	for ( int row = 0 ; row < 5 ; row++ )
		{	if ( leftPage )
		{	columnToDraw = column - 1 ;
			}
			else
			{	columnToDraw = column + 3 ;
			}
	
			if ( (thisMonth[columnToDraw][row].month()) == today.month() )
			{	dayBlock.moveLeft ( page.x() + ( column * dayBlock.width() ) ) ;
				dayBlock.moveTop ( page.y() + (page.height() / 11.0) + ( row * dayBlock.height() ) ) ;		
				twoPagePerMonthDrawOneDay ( dayBlock, thisMonth[columnToDraw][row], painter, true ) ;
			}
		}
		if ( leftPage && ( (thisMonth[columnToDraw][5].month()) == today.month() ) )
		{	drawOneShortDay ( dayBlock, thisMonth[column - 1][5], painter, true ) ;
		}
	}
		
	theBrush.setStyle ( Qt::NoBrush ) ;	painter->setBrush ( theBrush  ) ;
	return ;
}

void RenderArea::twoPagePerMonthDrawLandscapePage ( QPainter* painter, bool topPage )
{
	
	QFont foo ( "Blue Highway" ) ;
	
	QPen thePen ( Qt::white, penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
	QBrush theBrush ( Qt::white, Qt::SolidPattern ) ;
	
	QRectF paper = thePaper ;
	
	QRectF page ;
	
	if ( topPage )
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
	
	QRectF dayBlock ( page.x(),  page.y(), page.width() / 8.0,  page.height() / 3.25 ) ;
	QRectF dayBar   ( page.x(),  page.y(), page.width(),  dayBlock.height() / 8.0 ) ;
	
	// --- "erase" the page ------------------------------------------------------
	painter->setBrush ( theBrush  ) ;
	painter->setPen ( thePen ) ;
	painter->drawRect ( paper ) ;
	
	//-------- Page Top Title ----------------------------------------------------
	
	int thePixelSize = (int)( ( page.height() / 11. ) - dayBlock.height() / 8. ) ;
	foo.setPixelSize ( thePixelSize ) ;
	painter->setFont ( foo ) ;	
	
	thePen.setColor ( Qt::black ) ;
	painter->setPen ( thePen ) ;
	theBrush.setStyle ( Qt::NoBrush ) ;
	painter->setBrush ( theBrush  ) ;
	
	if ( topPage )
	{
		fitStringInRect ( dayBar, today.toString ( "MMMM yyyy" ), painter, Qt::AlignRight | Qt::AlignVCenter, 0.85 ) ;
		fitStringInRect ( dayBar, tr("Monthly Planning:"), painter, Qt::AlignLeft | Qt::AlignVCenter, 0.85 ) ;
	}
	
	//------------- bar with weekdays ------------------------------------------------------------
	thePen.setColor ( lineColors[2]  ) ;
	painter->setPen ( thePen ) ;

	theBrush.setColor ( lineColors[2]  ) ;
	theBrush.setStyle ( Qt::SolidPattern ) ;
	painter->setBrush ( theBrush  ) ;
	
	if ( topPage )
	{
		dayBar.moveTop ( dayBar.bottom() ) ;
	}
	
	painter->drawRect ( dayBar ) ;

	painter->eraseRect
	( 	QRectF ( dayBar.x() + ( 0.95 * dayBlock.width() ),
		dayBar.y(),
		dayBlock.width() * 0.05,
		penWidth + penWidth + dayBar.height() )
	) ;

	painter->setFont ( foo ) ;

	thePen.setColor ( Qt::white ) ;
	painter->setPen ( thePen ) ;

	theBrush.setColor ( Qt::white ) ;
	painter->setBrush ( theBrush  ) ;

	fitStringInRect ( QRectF( dayBar.x(), dayBar.y(), dayBlock.width(), dayBar.height() ), tr("* Notes"), painter, Qt::AlignCenter, 0.85 ) ;
	
	for ( int loop = 0 ; loop < 7 ; loop++ )
	{	fitStringInRect
		(	QRectF 
			(	dayBar.x() + ((loop + 1) * dayBlock.width()),
				dayBar.y(),
				dayBlock.width(),
				dayBar.height()
			),
			thisMonth[loop][0].toString ( "dddd" ),
			painter,
			Qt::AlignCenter,
			0.85 
		) ;
	}
	
	//-------- Notes column ------------------------------------------------------------------
	
	QRectF dashBox
	(	page.x(),
		dayBar.bottom(),
		0.95 * dayBlock.width(),
		dayBlock.height() * 3.0
	) ;
	
	if ( topPage )
	{	dashBox.setBottom ( page.bottom() ) ;
	}
	else
	{	dashBox.setBottom ( dayBar.bottom() + ( 2.0 * dayBlock.height() ) ) ;
	}
	
	dashBox.setHeight ( (int)(( floor ( dashBox.height() / displayLineSpacing ) ) * displayLineSpacing ) ) ;
	int howMany = (int)( dashBox.height() / displayLineSpacing ) ;
	
	theBrush.setColor ( lineColors[6] ) ;
	painter->setBrush ( theBrush  ) ;
	
	thePen.setColor ( lineColors[6] ) ;
	painter->setPen ( thePen ) ;
	
	painter->drawRect
		(	 QRectF ( dashBox.x(),
			 dashBox.y(),
			 dashBox.width() / 5.,
			 dashBox.height() )
			 ) ;
	
	thePen.setColor ( lineColors[3] ) ;
	painter->setPen ( thePen ) ;
	
	theBrush.setStyle ( Qt::NoBrush ) ;
	painter->setBrush ( theBrush  ) ;
	
	painter->drawRect ( dashBox ) ;
	
	QVector<qreal> dashes;
	dashes	<< 4 << 4 << 4 << 4 ;
	
	thePen.setDashPattern ( dashes ) ;
	thePen.setColor ( lineColors[3] ) ;
	painter->setPen ( thePen ) ;
	
	qreal y = dashBox.top() + displayLineSpacing ;
	
	//--------------------------------------------------------------------------			
	for ( int row = 0 ; row < howMany ; row++ )
	{	painter->drawLine
		(	QLineF
			(	page.x(),
				y,
				page.x() + dashBox.width(),
				y 
				) 
			) ;
		
		y += displayLineSpacing ;
	}
	//--------------------------------------------------------------------------
	
	thePen.setColor ( Qt::black ) ;
	thePen.setStyle ( Qt::SolidLine ) ;
	painter->setPen ( thePen ) ;
	
	theBrush.setStyle ( Qt::SolidPattern ) ;
	theBrush.setColor ( Qt::black ) ;
	painter->setBrush ( theBrush  ) ;
		
	if ( !topPage )
	{
		
		//--------------------------------------------------------------------------
		// draw thew two little months here
		QRectF littleMonthRect
			(	page.x() + ( dashBox.width() /3 ),
				dayBar.bottom() + ( 2.050 * dayBlock.height() ),
				2.0 * dashBox.width() / 3.0,
				0.45 * dayBlock.height()
			) ;
		
		drawLittleMonth ( painter, today.addMonths ( -1 ), littleMonthRect, false ) ;
		
		littleMonthRect.moveTop ( dayBar.bottom() + ( 2.50 * dayBlock.height() ) ) ;
		
		drawLittleMonth ( painter, today.addMonths ( 1 ), littleMonthRect, false ) ;
		
		thePen.setColor ( lineColors[5] ) ;
		thePen.setStyle ( Qt::SolidLine ) ;
		painter->setPen ( thePen ) ;
		
		theBrush.setStyle ( Qt::SolidPattern ) ;
		theBrush.setColor ( lineColors[5] ) ;
		painter->setBrush ( theBrush  ) ;
		
		painter->drawRect
			(	QRectF ( page.x(),
				dayBar.bottom() + ( 2.050 * dayBlock.height() ),
				90. * dashBox.width() / 300.,
				95. * dayBlock.height() / 100. )
			) ;
	}
	
	thePen.setColor ( Qt::black ) ;
	thePen.setStyle ( Qt::SolidLine ) ;
	painter->setPen ( thePen ) ;
	
	theBrush.setColor ( Qt::black ) ;
	painter->setBrush ( theBrush  ) ;
	
	// it is easier to first draw blocks from the next/previous month FIRST
	// That way, the outllines of THIS MONTH's blocks are always on top
	//
	// do the blocks NOT in this month
	
	int startRow ;
	int endRow ;
	
	if ( topPage )
	{
		startRow = 0 ;
		endRow = 3 ;
	}
	else
	{
		startRow = 3 ;
		endRow = 6 ;
	}

	for ( int column = 0 ; column < 7 ; column++ )
	{	
		for ( int row = startRow ; row < endRow ; row++ )
		{
			if ( (thisMonth[column][row].month()) != today.month() )
			{	dayBlock.moveLeft ( page.x() + ( ( column + 1 ) * dayBlock.width() ) ) ;
				
				if ( topPage )
				{
					dayBlock.moveTop (dayBar.bottom() + ( row * dayBlock.height() ) ) ;		
				}
				else
				{
					dayBlock.moveTop ( dayBar.bottom() + ( (row - 3) * dayBlock.height() ) ) ;
					if ( (thisMonth[0][row].month()) != today.month() ) continue ;
				}
				twoPagePerMonthDrawOneDay ( dayBlock, thisMonth[column][row], painter, false ) ;
			}
		}
	}
	
	if ( topPage )
	{
		startRow = 0 ;
		endRow = 3 ;
	}
	else
	{
		startRow = 3 ;
		endRow = 6 ;
	}
	// now do this month's blocks
	for ( int column = 0 ; column < 7 ; column++ )
	{
		for ( int row = startRow ; row < endRow ; row++ )
		{
			
			if ( (thisMonth[column][row].month()) == today.month() )
			{	dayBlock.moveLeft ( page.x() + ( ( column + 1 ) * dayBlock.width() ) ) ;
				if ( topPage )
				{
					dayBlock.moveTop ( dayBar.bottom() + ( row * dayBlock.height() ) ) ;		
				}
				else
				{
					dayBlock.moveTop ( dayBar.bottom() + ( (row - 3) * dayBlock.height() ) ) ;		
				}
				twoPagePerMonthDrawOneDay ( dayBlock, thisMonth[column][row], painter, true ) ;
			}
		}
	}
	
	theBrush.setStyle ( Qt::NoBrush ) ;	painter->setBrush ( theBrush  ) ;
	return ;
}

