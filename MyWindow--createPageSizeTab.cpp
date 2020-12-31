//
// $Id: MyWindow--createPageSizeTab.cpp,v 1.9 2010/01/01 20:22:32 igor Exp $
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

#include <QtGui>

#include "MyWindow.h"

QWidget* MyWindow::createPageTab ( QWidget* grandParent)
{
	QWidget* parent = new QWidget( grandParent ) ;
	
	orientationCombo = new QComboBox ( parent ) ;
	orientationCombo->addItem( tr( "Landscape" ), 0 ) ;
	orientationCombo->addItem( tr( "Portrait" ), 1 ) ;

	connect 
	(	orientationCombo,
		SIGNAL(	currentIndexChanged(int)  ),
		this,
		SLOT( orientationComboChanged ( int )  )
	) ;
		
	majorTypeSizeCombo = new QComboBox ( parent ) ;
	majorTypeSizeCombo->addItem( tr( "US Sizes" ) ) ;
	majorTypeSizeCombo->addItem( tr( "Euro Sizes" ) ) ;
	majorTypeSizeCombo->addItem( tr( "Custom" ) ) ;
	
	connect 
	(	majorTypeSizeCombo,
		SIGNAL(	currentIndexChanged(int)  ),
		this,
		SLOT( majorTypeSizeComboChanged ( int )  )
	) ;
	
	fcSizeCombo = new QComboBox ( parent ) ;
	fcSizeCombo->addItem( tr( "Pocket" ) ) ;
	fcSizeCombo->addItem( tr( "Compact" ) ) ;
	fcSizeCombo->addItem( tr( "Classic" ) ) ;
	fcSizeCombo->addItem( tr( "A5" ) ) ;
	fcSizeCombo->addItem( tr( "Monarch" ) ) ;

	connect 
	(	fcSizeCombo,
		SIGNAL(	currentIndexChanged(int)  ),
		this,
		SLOT( fcSizeComboChanged ( int )  )
	) ;

	filofaxSizeCombo = new QComboBox ( parent ) ;
	filofaxSizeCombo->addItem ( tr( "Mini" ) ) ;
	filofaxSizeCombo->addItem ( tr( "Compact" ) ) ;
	filofaxSizeCombo->addItem ( tr( "Slimline" ) ) ;
	filofaxSizeCombo->addItem ( tr( "Personal" ) ) ;
	filofaxSizeCombo->addItem ( tr( "Pocket" ) ) ;
	filofaxSizeCombo->addItem ( tr( "A5" ) ) ;
	filofaxSizeCombo->addItem ( tr( "A4" ) ) ;

	connect 
	(	filofaxSizeCombo,
		SIGNAL(	currentIndexChanged(int)  ),
		this,
		SLOT( filofaxSizeComboChanged ( int )  )
	) ;

	circaSizeCombo = new QComboBox ( parent ) ;
	circaSizeCombo->addItem ( tr( "Three-by-Five" ) ) ;
	circaSizeCombo->addItem ( tr( "Compact" ) ) ;
	circaSizeCombo->addItem ( tr( "Junior" ) ) ;
	circaSizeCombo->addItem ( tr( "Letter" ) ) ;

	connect 
	(	circaSizeCombo,
		SIGNAL(	currentIndexChanged(int)  ),
		this,
		SLOT( circaSizeComboChanged ( int )  )
	) ;

	usSizeCombo = new QComboBox ( parent ) ;
	usSizeCombo->addItem ( tr( "Business Card" ) ) ;
	usSizeCombo->addItem ( tr( "Credit Card" ) ) ;
	usSizeCombo->addItem ( tr( "3x5" ) ) ;
	usSizeCombo->addItem ( tr( "4x6 Postcard" ) ) ;
	usSizeCombo->addItem ( tr( "5x8" ) ) ;
	usSizeCombo->addItem ( tr( "Statement" ) ) ;
	usSizeCombo->addItem ( tr( "Letter" ) ) ;
	usSizeCombo->addItem ( tr( "Legal" ) ) ;
	usSizeCombo->addItem ( tr( "Tabloid" ) ) ;

	connect 
	(	usSizeCombo,
		SIGNAL(	currentIndexChanged(int)  ),
		this,
		SLOT( usSizeComboChanged ( int )  )
	) ;

	euroSizeCombo = new QComboBox ( parent ) ;
	euroSizeCombo->addItem ( tr( "A8" ) ) ;
	euroSizeCombo->addItem ( tr( "Business Card" ) ) ;
	euroSizeCombo->addItem ( tr( "A7" ) ) ;
	euroSizeCombo->addItem ( tr( "A6 Postcard" ) ) ;
	euroSizeCombo->addItem ( tr( "A5" ) ) ;
	euroSizeCombo->addItem ( tr( "A4" ) ) ;

	connect 
	(	euroSizeCombo,
		SIGNAL(	currentIndexChanged(int)  ),
		this,
		SLOT( euroSizeComboChanged ( int )  )
	) ;

	customHeight = new QDoubleSpinBox() ;
	
	connect 
	(	customHeight,
		SIGNAL(	valueChanged ( double ) ),
		this,
		SLOT( customHeightChanged ( double )  )
	) ;
	
	customWidth  = new QDoubleSpinBox() ;
	
	connect 
	(	customWidth,
		SIGNAL(	valueChanged ( double ) ),
		this,
		SLOT( customWidthChanged ( double )  )
	) ;

	customHeight->setDecimals ( 4 ) ; 
	customWidth->setDecimals ( 4 ) ; 
	customHeight->setMaximum ( 99.9999 ) ; 
	customWidth->setMaximum ( 99.9999 ) ; 
	
	customHeight->setSuffix ( " x " ) ;
	customWidth->setSuffix ( " x " ) ;
							
	topMargin = new QDoubleSpinBox() ;
	bottomMargin = new QDoubleSpinBox() ;
	innerMargin = new QDoubleSpinBox() ;
	outerMargin = new QDoubleSpinBox() ;
	
	topMargin->setDecimals ( 4 ) ;
	bottomMargin->setDecimals ( 4 ) ;
	innerMargin->setDecimals ( 4 ) ;
	outerMargin->setDecimals ( 4 ) ;
	
	topMargin->setSingleStep ( 0.100 ) ;
	bottomMargin->setSingleStep ( 0.100 ) ;
	innerMargin->setSingleStep ( 0.100 ) ;
	outerMargin->setSingleStep ( 0.100 ) ;

	topMarginValue    = topMargin->value() ;
	bottomMarginValue = bottomMargin->value() ;
	innerMarginValue  = innerMargin->value() ;
	outerMarginValue  = outerMargin->value() ;
	// this works here 'cause they are all zero

	topMargin->setSuffix ( " x " ) ;
	bottomMargin->setSuffix ( " x " ) ;
	innerMargin->setSuffix ( " x " ) ;
	outerMargin->setSuffix ( " x " ) ;
	
	connect ( topMargin,    SIGNAL( valueChanged ( double ) ), this, SLOT( topMarginChanged ( double ) ) ) ;
	connect ( bottomMargin, SIGNAL( valueChanged ( double ) ), this, SLOT( bottomMarginChanged ( double ) ) ) ;
	connect ( innerMargin,  SIGNAL( valueChanged ( double ) ), this, SLOT( innerMarginChanged ( double ) ) ) ;
	connect ( outerMargin,  SIGNAL( valueChanged ( double ) ), this, SLOT( outerMarginChanged ( double ) ) ) ;
	
	unitComboBox = new QComboBox ( parent ) ;
	unitComboBox->addItem(tr("Centimeters"));
	unitComboBox->addItem(tr("Inches"));
	
	connect
		( 	unitComboBox,
			SIGNAL ( activated ( int ) ),
			this,
			SLOT ( unitComboBoxChanged ( int ) )
			) ;
	
	isItInches = 1 ;
	unitComboBox->setCurrentIndex ( 1 ) ;
	
	QVBoxLayout* layoutv01 = new QVBoxLayout ( parent ) ;

	QHBoxLayout* layouth01 = new QHBoxLayout () ;
	QHBoxLayout* layouth02 = new QHBoxLayout () ;
	QHBoxLayout* layouth03 = new QHBoxLayout () ;
	QHBoxLayout* layouth04 = new QHBoxLayout () ;
	QHBoxLayout* layouth05 = new QHBoxLayout () ;

	QGridLayout* layoutg01 = new QGridLayout () ;

	QLabel* label1 = new QLabel ( tr("Page Type") ) ;
	pageSizeLabel = new QLabel ( tr("Page Size") ) ;
	sizeDisplayLabel= new QLabel ( tr("one by two") ) ;						 
		 							 
	layouth05->addStretch ( 999 ) ;
	layouth05->addWidget ( orientationCombo, Qt::AlignCenter ) ;
	layouth05->addStretch ( 999 ) ;
	layoutv01->addLayout ( layouth05, 0 ) ;
		
	layouth01->addStretch ( 999 ) ;
	layouth01->addWidget ( label1,             Qt::AlignVCenter ) ;
	layouth01->addWidget ( majorTypeSizeCombo, Qt::AlignVCenter ) ;
	layouth01->addStretch ( 999 ) ;
	
	layouth04->addStretch ( 999 ) ;
	layouth04->addWidget ( sizeDisplayLabel, Qt::AlignCenter ) ;
	layouth04->addWidget ( unitComboBox, Qt::AlignCenter ) ;
	layouth04->addStretch ( 999 ) ;
	
	layoutv01->addLayout ( layouth04, 0 ) ;
	layoutv01->addLayout ( layouth01, 0 ) ;
	
	layouth02->addStretch ( 999 ) ;
	layouth02->addWidget ( pageSizeLabel, Qt::AlignVCenter ) ;
	
							 
	layoutg01->addWidget ( fcSizeCombo,      0, 0, Qt::AlignHCenter | Qt::AlignTop ) ;
	layoutg01->addWidget ( filofaxSizeCombo, 0, 0, Qt::AlignHCenter | Qt::AlignTop ) ;
	layoutg01->addWidget ( circaSizeCombo,   0, 0, Qt::AlignHCenter | Qt::AlignTop ) ;
	layoutg01->addWidget ( usSizeCombo,      0, 0, Qt::AlignHCenter | Qt::AlignTop ) ;
	layoutg01->addWidget ( euroSizeCombo,    0, 0, Qt::AlignHCenter | Qt::AlignTop ) ;

	layouth02->addLayout ( layoutg01, 0 ) ;
	layouth02->addStretch ( 999 ) ;
	layoutv01->addLayout ( layouth02, 0 ) ;
			
	
	dimLabel = new QLabel ( tr("by") ) ;
							 
	layouth03->addStretch ( 999 ) ;
	layouth03->addWidget ( customWidth,  Qt::AlignVCenter ) ;
	layouth03->addWidget ( dimLabel,       Qt::AlignVCenter ) ;
	layouth03->addWidget ( customHeight, Qt::AlignVCenter ) ;
	layouth03->addStretch ( 999 ) ;

	layoutv01->addLayout ( layouth03, 0 ) ;
	
	QGroupBox* groupBox = new QGroupBox(tr("Margins:"));

	QFormLayout* formLayout = new QFormLayout ( groupBox ) ;

	formLayout->addRow ( tr("Top"), topMargin ) ;
	formLayout->addRow ( tr("Bottom"), bottomMargin ) ;
	formLayout->addRow ( tr("Inner"), innerMargin ) ;
	formLayout->addRow ( tr("Outer"), outerMargin ) ;

	layoutv01->addWidget ( groupBox, Qt::AlignCenter ) ;
	
	layoutv01->addStretch ( 999 ) ;

	customWidth->hide() ;
	dimLabel->hide() ;
	customHeight->hide() ;
	
	majorTypeSizeCombo->setCurrentIndex ( 0 ) ;
	majorTypeSizeComboChanged ( 0 ) ;
	
//	fcSizeCombo->setCurrentIndex ( 2 ) ;
//	fcSizeComboChanged ( 2 ) ;
	usSizeCombo->setCurrentIndex ( 5 ) ;
	usSizeComboChanged ( 5 ) ;
	
	orientationCombo->setCurrentIndex ( 1 ) ;
	orientationComboChanged ( 1 ) ;

	// default quarter inch margins
	topMargin->setValue ( 0.25 ) ;
	bottomMargin->setValue ( 0.25 ) ;
	innerMargin->setValue ( 0.25 ) ;
	outerMargin->setValue ( 0.25 ) ;	
		
	return parent ;
} ;

void MyWindow::unitComboBoxChanged ( int what )
{
	isItInches = what ;
	
	QString suffix ;
	
	if ( isItInches )
	{
		suffix = QString(" in ") ;
	}
	else
	{
		suffix = QString(" cm ") ;
	}
		
	customHeight->setSuffix ( suffix ) ;
	customWidth->setSuffix ( suffix ) ;
	customLine->setSuffix ( suffix ) ;
	topMargin->setSuffix ( suffix ) ;
	bottomMargin->setSuffix ( suffix ) ;
	innerMargin->setSuffix ( suffix ) ;
	outerMargin->setSuffix ( suffix ) ;
	
	updateSize () ;
}

void MyWindow::orientationComboChanged ( int which )
{
	portrait = which ;
	updateSize () ;
}

void MyWindow::majorTypeSizeComboChanged ( int which )
{
	fcSizeCombo->hide() ;
	filofaxSizeCombo->hide() ;
	circaSizeCombo->hide() ;
	usSizeCombo->hide() ;
	euroSizeCombo->hide() ;
	if ( pageSizeLabel->isHidden() )
	{	pageSizeLabel->show() ;
	}
	
	customWidth->hide() ;
	dimLabel->hide() ;
	customHeight->hide() ;
	isItCustom = false ;
	
	switch ( which )
	{
		case 0:
			usSizeCombo->show() ;
			usSizeComboChanged ( usSizeCombo->currentIndex()  ) ;
			break ;
		case 1:
			euroSizeCombo->show() ;
			euroSizeComboChanged ( euroSizeCombo->currentIndex()  ) ;
			break ;
		case 2:
			isItCustom = true ;
			pageSizeLabel->hide() ;
			dimLabel->show() ;
			customWidth->show() ;
			customHeight->show() ;
			
			qreal conv ; 
			
			if ( isItInches ) 
			{	conv = MM_TO_INCHES ;
			}
			else
			{	conv = MM_TO_CM ;
			}
				
			customWidth->setValue( theSize.width() * conv ) ;
			customHeight->setValue( theSize.height() * conv ) ;
			break ;
		default:
			break ;
	}
} ;

void MyWindow::customHeightChanged ( double value ) 
{
	qreal conv ; 
	
	if ( isItInches ) 
	{	conv = INCHES_TO_MM ;
	}
	else
	{	conv = CM_TO_MM ;
	}
	theSize.setHeight ( value * conv ) ;
	updateSize() ;
}

void MyWindow::customWidthChanged ( double value ) 
{
	qreal conv ; 
	
	if ( isItInches ) 
	{	conv = INCHES_TO_MM ;
	}
	else
	{	conv = CM_TO_MM ;
	}
	theSize.setWidth ( value * conv ) ;
	updateSize() ;
}

void MyWindow::customLineChanged ( double value )
{
	qreal conv ; 
	
	// all internal units are in millimeters
	if ( isItInches ) 
	{	conv = INCHES_TO_MM ;
	}
	else
	{	conv = CM_TO_MM ;
	}
	lineSpaceValue = ( value * conv ) ; 
	updateSize() ;
}

void MyWindow::topMarginChanged ( double value ) 
{
	qreal conv ;
	
	// all internal units are in millimeters
	if ( isItInches ) 
	{	conv = INCHES_TO_MM ;
	}
	else
	{	conv = CM_TO_MM ;
	}
	
	topMarginValue  = conv * value ;
	updateSize() ;
}
void MyWindow::bottomMarginChanged ( double value ) 
{
	qreal conv ;
	
	// all internal units are in millimeters
	if ( isItInches ) 
	{	conv = INCHES_TO_MM ;
	}
	else
	{	conv = CM_TO_MM ;
	}
	
	bottomMarginValue  = conv * value ;
	updateSize() ;
}
void MyWindow::innerMarginChanged ( double value ) 
{
	qreal conv ;
	
	// all internal units are in millimeters
	if ( isItInches ) 
	{	conv = INCHES_TO_MM ;
	}
	else
	{	conv = CM_TO_MM ;
	}
	
	innerMarginValue  = conv * value ;
	updateSize() ;
}
void MyWindow::outerMarginChanged ( double value ) 
{
	qreal conv ;
	
	// all internal units are in millimeters
	if ( isItInches ) 
	{	conv = INCHES_TO_MM ;
	}
	else
	{	conv = CM_TO_MM ;
	}
	
	outerMarginValue  = conv * value ;
	updateSize() ;
}

void MyWindow::updateSize ( void  )
{
	qreal temp ;
	
	if ( !isItCustom )
	{	if ( portrait )
		{	if ( theSize.width() > theSize.height() )
			{	temp = theSize.height() ;
				theSize.setHeight ( theSize.width() ) ;
				theSize.setWidth ( temp ) ;
			}
		}
		else // landscape
		{	if ( theSize.width() < theSize.height() )
			{	temp = theSize.height() ;
				theSize.setHeight ( theSize.width() ) ;
				theSize.setWidth ( temp ) ;
			}
		}
	}

	qreal conv ;

	if ( isItInches ) 
	{	conv = MM_TO_INCHES ;
	}
	else
	{	conv = MM_TO_CM ;
	}
	
	QString tempHeight, tempWidth ;
	tempHeight.setNum ( (conv * theSize.height() ),'f', 2) ;
	tempWidth.setNum ( (conv * theSize.width()  ),'f', 2) ;
		
	sizeDisplayLabel->setText ( tempWidth + tr(" by ") + tempHeight ) ;
	
//	sizeDisplayLabel->setText
//		(	QString("%1 by %2 ")
//			.arg( (conv * theSize.width()  ), 0, 'f', 2)
//			.arg( (conv * theSize.height() ), 0, 'f', 2)
//			) ;
	
	customWidth->setValue( theSize.width() * conv ) ;
	customHeight->setValue( theSize.height() * conv ) ;
	
	if (customLine)	customLine->setValue( lineSpaceValue * conv ) ;
	
	outerMargin->setValue( outerMarginValue * conv ) ;
	innerMargin->setValue( innerMarginValue * conv ) ;
	topMargin->setValue( topMarginValue * conv ) ;
	bottomMargin->setValue( bottomMarginValue * conv ) ;

	QString suffix ;
	
	if ( isItInches )
	{
		suffix = QString(" in ") ;
	}
	else
	{
		suffix = QString(" cm ") ;
	}
	
	customHeight->setSuffix ( suffix ) ;
	customWidth->setSuffix ( suffix ) ;
	if (customLine)	customLine->setSuffix ( suffix ) ;

	topMargin->setSuffix ( suffix ) ;
	bottomMargin->setSuffix ( suffix ) ;
	innerMargin->setSuffix ( suffix ) ;
	outerMargin->setSuffix ( suffix ) ;

	QRectF theMargins = QRectF
	(       outerMarginValue,
			topMarginValue,
			theSize.width() - outerMarginValue - innerMarginValue,
			theSize.height() - topMarginValue - bottomMarginValue
	) ;
	
	emit linesChanged ( lineSpaceValue ) ;

	emit pageSizeChanged
	(	QRectF
		(	0.0,
			0.0,
			theSize.width(),
			theSize.height()
		)
	) ;
	
	emit pageMarginsChanged
	(	QRectF
		(	outerMarginValue,
			topMarginValue,
			theSize.width() - outerMarginValue - innerMarginValue,
			theSize.height() - topMarginValue - bottomMarginValue
		)
	) ;
} ;

// all internal units are in millimeters
void MyWindow::fcSizeComboChanged ( int which  )
{
	switch ( which )
	{	case 0: // Pocket
			theSize.setWidth ( 3.500 * INCHES_TO_MM ) ; 
			theSize.setHeight ( 6.000 * INCHES_TO_MM ) ;
			break ;
		case 1: // Compact
			theSize.setWidth ( 4.250 * INCHES_TO_MM ) ;
			theSize.setHeight ( 6.750 * INCHES_TO_MM ) ;
			break ;
		case 2: // Classic
			theSize.setWidth ( 5.500 * INCHES_TO_MM ) ;
			theSize.setHeight ( 8.500 * INCHES_TO_MM ) ;
			break ;
		case 3: // A5
			theSize.setWidth ( 148.00 ) ;
			theSize.setHeight ( 210.00 ) ;
			break ;
		case 4: // Monarch
			theSize.setWidth ( 8.500 * INCHES_TO_MM ) ;
			theSize.setHeight ( 11.00 * INCHES_TO_MM ) ; 
			break ;
		default: // it should never get here, but let's use Classic
			theSize.setWidth ( 5.500 * INCHES_TO_MM ) ;
			theSize.setHeight ( 8.500 * INCHES_TO_MM ) ;
			break ;
	}
	updateSize() ;
} ;

// all internal units are in millimeters
void MyWindow::filofaxSizeComboChanged ( int which  )
{
	switch ( which )
	{
		case 0: // Mini
			theSize.setHeight ( 105.00 ) ;
			theSize.setWidth ( 67.00 ) ; 
			break ;
		case 1: // Compact/Slimline/Personal
		case 2: // Compact/Slimline/Personal
		case 3: // Compact/Slimline/Personal
			theSize.setHeight ( 171.00 ) ;
			theSize.setWidth ( 95.00 ) ; 
			break ;
		case 4: // 	Pocket
			theSize.setHeight ( 120.00 ) ;
			theSize.setWidth ( 81.00 ) ; 
			break ;
		case 5: // 	A5
			theSize.setHeight ( 210.00 ) ;
			theSize.setWidth ( 148.00 ) ; 
			break ;
		case 6: // 	A4
			theSize.setHeight ( 297.00 ) ;
			theSize.setWidth ( 210.00 ) ; 
			break ;
		default: // it should never get here, but let's use A5
			theSize.setHeight ( 210.00 ) ;
			theSize.setWidth ( 148.00 ) ; 
			break ;
	}
	updateSize() ;
} ;

// all internal units are in millimeters
void MyWindow::circaSizeComboChanged ( int which  )
{
	switch ( which )
	{
		case 0: // Three-by-Five
			theSize.setHeight ( 5.000 * INCHES_TO_MM ) ;
			theSize.setWidth ( 3.000 * INCHES_TO_MM ) ; 
			break ;
		case 1: // Compact
			theSize.setHeight ( 6.750 * INCHES_TO_MM ) ;
			theSize.setWidth ( 3.750 * INCHES_TO_MM ) ; 
			break ;
		case 2: // Junior
			theSize.setHeight ( 8.500 * INCHES_TO_MM ) ;
			theSize.setWidth ( 5.500 * INCHES_TO_MM ) ; 
			break ;
		case 3: // Letter
			theSize.setHeight ( 11.000 * INCHES_TO_MM ) ;
			theSize.setWidth ( 8.500 * INCHES_TO_MM ) ; 
			break ;
		default: // it should never get here, but let's use Junior
			theSize.setHeight ( 5.500 * INCHES_TO_MM ) ;
			theSize.setWidth ( 8.500 * INCHES_TO_MM ) ; 
			break ;
	}
	updateSize() ;
} ;

// all internal units are in millimeters
void MyWindow::usSizeComboChanged ( int which  )
{
	switch ( which )
	{
		case 0: // Business Card
			theSize.setHeight ( 2.000 * INCHES_TO_MM ) ;
			theSize.setWidth ( 3.500 * INCHES_TO_MM ) ;
			break ;
		case 1: // Credit Card
			theSize.setHeight ( 2.125 * INCHES_TO_MM ) ;
			theSize.setWidth ( 3.370 * INCHES_TO_MM ) ;
			break ;
		case 2: // 3x5
			theSize.setWidth ( 3.000 * INCHES_TO_MM ) ;
			theSize.setHeight ( 5.000 * INCHES_TO_MM ) ;
			break ;
		case 3: // 4x6 Postcard
			theSize.setWidth ( 4.000 * INCHES_TO_MM ) ;
			theSize.setHeight ( 6.000 * INCHES_TO_MM ) ;
			break ;
		case 4: // 5x8
			theSize.setWidth ( 5.000 * INCHES_TO_MM ) ;
			theSize.setHeight ( 8.000 * INCHES_TO_MM ) ;
			break ;
		case 5: // Statement
			theSize.setWidth ( 5.500 * INCHES_TO_MM ) ;
			theSize.setHeight ( 8.500 * INCHES_TO_MM ) ;
			break ;
		case 6: // Letter
			theSize.setWidth ( 8.500 * INCHES_TO_MM ) ;
			theSize.setHeight ( 11.000 * INCHES_TO_MM ) ;
			break ;
		case 7: // Legal
			theSize.setWidth ( 8.500 * INCHES_TO_MM ) ;
			theSize.setHeight ( 14.000 * INCHES_TO_MM ) ;
			break ;
		case 8: // Tabloid
			theSize.setWidth ( 11.00 * INCHES_TO_MM ) ;
			theSize.setHeight ( 17.000 * INCHES_TO_MM ) ;
			break ;
		default: // it should never get here, but let's use Statement
			theSize.setWidth ( 5.500 * INCHES_TO_MM ) ;
			theSize.setHeight ( 8.500 * INCHES_TO_MM ) ;
			break ;
	}
	updateSize() ;
} ;

// all internal units are in millimeters
void MyWindow::euroSizeComboChanged ( int which  )
{
	switch ( which )
	{
		case 0: // A8
			theSize.setWidth ( 52.00 ) ;
			theSize.setHeight ( 74.00 ) ;
			break ;
		case 1: // Business Card
			theSize.setHeight ( 53.980 ) ;
			theSize.setWidth ( 85.600 ) ;
			break ;
		case 2: // A7
			theSize.setWidth ( 74.00 ) ;
			theSize.setHeight ( 105.00 ) ;
			break ;
		case 3: // A6 Postcard
			theSize.setWidth ( 105.00 ) ;
			theSize.setHeight ( 148.00 ) ;
			break ;
		case 4: // A5
			theSize.setWidth ( 148.00 ) ;
			theSize.setHeight ( 210.00 ) ;
			break ;
		case 5: // A4
			theSize.setWidth ( 210.00 ) ;
			theSize.setHeight ( 297.00 ) ;
			break ;
		default: // it should never get here, but let's use A5
			theSize.setWidth ( 148.00 ) ;
			theSize.setHeight ( 210.00 ) ;
			break ;
	}
	updateSize() ;
} ;

int MyWindow::currentUnits ( void )
{
	return isItInches ;
}

