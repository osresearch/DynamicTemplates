//
// $Id: MyWindow--createLinesTab.cpp,v 1.4 2009/01/29 02:47:51 igor Exp $
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


#include "MyWindow.h"

QWidget* MyWindow::createLinesTab ( QWidget* grandParent )
//  : QWidget(parent)
{
	QWidget* parent = new QWidget( grandParent ) ;
	
	customLine  = new QDoubleSpinBox() ;
	
	
	customLine->setDecimals ( 4 ) ; 
	customLine->setMinimum ( 0.0010 ) ; 
	customLine->setMaximum ( 99.9999 ) ; 
	customLine->setSingleStep ( 0.0100 ) ;
	
	customLine->setSuffix ( " x " ) ;
	
	linesComboBox = new QComboBox ( parent ) ;
	linesComboBox->addItem( tr("Wide Ruled")    ) ;
	linesComboBox->addItem( tr("College Ruled") ) ;
	linesComboBox->addItem( tr("Narrow Ruled")  ) ;
	linesComboBox->addItem( tr( "Custom" )      ) ;

	connect ( customLine, SIGNAL( valueChanged ( double ) ), this, SLOT( customLineChanged ( double ) ) ) ;
	connect
	( 	linesComboBox,
		SIGNAL ( activated ( int ) ),
		this,
		SLOT ( linesComboBoxChanged ( int ) )
	) ;
	
	QSlider *penSlider = new QSlider ( Qt::Horizontal, parent ) ;
	penSlider->setMaximum ( 100 ) ;
	penSlider->setMinimum ( 1 ) ;
	
			
	QFormLayout* formLayout = new QFormLayout ( parent ) ;

	formLayout->addRow ( tr("Line Spacing:"), linesComboBox ) ;
	formLayout->addRow ( customLine ) ;

	linesThickLabel = new QLabel ( tr("Line Width - 0.10 - 10.0") ) ;
	formLayout->addRow ( linesThickLabel, penSlider ) ;

	linesComboBox->setCurrentIndex ( 1 ) ;
	linesComboBoxChanged ( 1 ) ;
	
	connect ( penSlider, SIGNAL ( valueChanged(int) ), this, SLOT ( penWidthSliderChanged(int) ) ) ;
	connect ( penSlider, SIGNAL ( valueChanged(int) ), this, SLOT ( setPenWidthLabel(int) ) ) ;


	penSlider->setValue ( 55 ) ;
	emit penWidthChanged ( 55 ) ;
	
	customLine->hide() ;

	
	return parent ;
} ;

void MyWindow::linesComboBoxChanged ( int which )
{
	switch ( which )
	{
		case 0:
			lineSpaceValue = 8.70 ; // Wide
			customLine->hide() ;
			break ;
		
		case 1:
			lineSpaceValue = 7.10 ; // College or medium
			customLine->hide() ;
			break ;
			
		case 2:
			lineSpaceValue = 6.35 ; // Narrow or Legal
			customLine->hide() ;
			break ;

		case 3: // Custom
			qreal conv ; 
			
			if ( isItInches ) 
			{	conv = MM_TO_INCHES ;
			}
			else
			{	conv = MM_TO_CM ;
			}
				customLine->setValue( lineSpaceValue * conv ) ;
			customLine->show() ;
			break ;

		default:
			break ;
	}
	
	emit linesChanged ( lineSpaceValue ) ;
} ;

void MyWindow::penWidthSliderChanged ( int which )
{
	emit penWidthChanged ( which ) ;
} ;

void MyWindow::setPenWidthLabel ( int value )
{
	QString text = 
		tr("Line Width - 0.10 - 10.0")
		+ " ("
		+ QString("%1").arg( (float) value / 10.0, 2, 'f', 1 )
		+ ")" ;
	
	linesThickLabel->setText ( tr( text.toAscii().constData() ) ) ;
}
