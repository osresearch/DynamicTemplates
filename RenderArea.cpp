//
// $Id: RenderArea.cpp,v 1.11 2009/08/16 22:35:58 igor Exp $
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

RenderArea::RenderArea(QWidget *parent) : QWidget(parent)
{	scale = 25.0 ;
    setBackgroundRole(QPalette::Base);
	thePaper = QRectF ( 0.0, 0.0, 148.0, 210.0 ) ;
	thePage  = QRectF ( 0.0, 0.0, 148.0, 210.0 ) ;
	penWidth = 0.500 ;
	titleString = QString ( tr("Title") ) ;
	theAlignment = Qt::AlignLeft ;
	linesPer = 4 ;
	itIsInches = true ; // false means centimeters
	theStyle = 0 ;
	theFont = QFont ( "Blue Highway" ) ;
	weekStart = Qt::Sunday ;
	whatKind = CAL_DAY ;
	
	printer = new QPrinter ( QPrinter::HighResolution ) ;
	printer->setOutputFormat ( QPrinter::PdfFormat ) ;
	
//	resolution = 1.0 ;
//	resolution = 300.0 /* dots per inch */ * 0.039370079 /* inches per millimeter */ ;
	resolution = 1200.0 /* dots per inch */ * 0.039370079 /* inches per millimeter */ ;
	
	lineColors[0] = QColor (  20,  20,  20 ) ;
	lineColors[1] = QColor (  89,  89,  89 ) ;
	lineColors[2] = QColor ( 140, 140, 140 ) ;
	lineColors[3] = QColor ( 179, 179, 179 ) ;
	lineColors[4] = QColor ( 207, 207, 207 ) ;
	lineColors[5] = QColor ( 240, 240, 240 ) ;
	lineColors[6] = QColor ( 245, 245, 245 ) ;
	
}

void RenderArea::paintEvent(QPaintEvent *)
{	QPainter* painter = new QPainter() ;
	
	painter->begin ( this ) ;
	painter->scale( scale, scale );
	
	draw ( theStyle, DRAW_TO_SCREEN, painter ) ;
	
	painter->drawRect ( thePaper ) ;
	
	// theStyle indicates single page (00 - 99) or double page (100 - 199) templates
	if ( theStyle >= 100 )
	{	painter->translate ( QPointF ( thePaper.width(), 0.0 ) ) ;
		painter->drawRect ( thePaper ) ;
	}
	
	painter->end () ;
}
