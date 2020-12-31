//
// $Id: MyWindow--createCalendarTab.cpp,v 1.13 2010/01/01 20:22:32 igor Exp $
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

QWidget* MyWindow::createCalendarTab ( QWidget* grandParent )
//  : QWidget(parent)
{
	QWidget* parent = new QWidget ( grandParent ) ;
	
	pagesCombo = new QComboBox ( parent ) ;
	
	whatKind = CAL_DAY ;
	
	pagesCombo->addItem( tr("One Page"), 1 );
	pagesCombo->addItem( tr("Two Pages"), 2 );
	
	connect 
	(	pagesCombo,
		SIGNAL(	currentIndexChanged(int)  ),
		this,
		SLOT( pagesComboChanged ( int )  )
	) ;
	
	connect
	(	pagesCombo,
		SIGNAL( activated(int)  ),
		this,
		SLOT ( pagesComboChanged ( int )  )
	) ;
	
	spanCombo = new QComboBox ( parent ) ;
	
	spanCombo->addItem( tr("Day") );
	spanCombo->addItem( tr("Week") );
	spanCombo->addItem( tr("Month") );
	spanCombo->addItem( tr("Year") );
	
	connect ( spanCombo, SIGNAL( currentIndexChanged(int) ), this, SLOT( spanComboChanged ( int ) ) ) ;
	connect ( spanCombo, SIGNAL( activated(int) ), this, SLOT ( spanComboChanged ( int ) ) ) ;
	
	firstDayCombo = new QComboBox ( parent ) ;
	
	firstDayCombo->addItem( tr("Sunday"),		Qt::Sunday		);
	firstDayCombo->addItem( tr("Monday"),		Qt::Monday		);
	firstDayCombo->addItem( tr("Tuesday"),		Qt::Tuesday		);
	firstDayCombo->addItem( tr("Wednesday"),	Qt::Wednesday	);
	firstDayCombo->addItem( tr("Thursday"),		Qt::Thursday	);
	firstDayCombo->addItem( tr("Friday"),		Qt::Friday		);
	firstDayCombo->addItem( tr("Saturday"),		Qt::Saturday	);
	
	connect 
	(	firstDayCombo,
		SIGNAL(	currentIndexChanged(int)  ),
		this,
		SLOT( firstDayComboChanged ( int )  )
	) ;
	
	connect
	(	this,
		SIGNAL( firstDayOfWeek ( Qt::DayOfWeek )  ),
		renderArea,
		SLOT ( setFirstDayOfWeek ( Qt::DayOfWeek )  )
	) ;
	
	onePageDayVariantsCombo = new QComboBox ( parent ) ;
	
	onePageDayVariantsCombo->addItem( tr("DIY3 Left Hand Style") );
	onePageDayVariantsCombo->addItem( tr("DIY3 Right Hand Style") );
	onePageDayVariantsCombo->addItem( tr("DIY3 Alternate Left/Right") );
	onePageDayVariantsCombo->addItem( tr("Dated Journal - Lined") );
	onePageDayVariantsCombo->addItem( tr("Dated Journal - Grid") );
	onePageDayVariantsCombo->addItem( tr("Dated Journal - Plain") );
	
	connect 
	(	onePageDayVariantsCombo,
		SIGNAL(	currentIndexChanged(int)  ),
		this,
		SLOT( onePageDayVariantsChanged ( int )  )
	) ;
	
	connect
	(	onePageDayVariantsCombo,
		SIGNAL( activated(int)  ),
		this,
		SLOT ( onePageDayVariantsChanged ( int )  )
	) ;
	
	onePageWeekVariantsCombo = new QComboBox ( parent ) ;
	
	onePageWeekVariantsCombo->addItem( tr("Lines") );
	onePageWeekVariantsCombo->addItem( tr("Block") );
	
	connect
	(	onePageWeekVariantsCombo,
		SIGNAL(	currentIndexChanged(int)  ),
		this,
		SLOT( onePageWeekVariantsChanged ( int )  )
	) ;
	
	connect
	(	onePageWeekVariantsCombo,
		SIGNAL( activated(int)  ),
		this,
		SLOT ( onePageWeekVariantsChanged ( int )  )
	) ;
	
	onePageMonthVariantsCombo = new QComboBox ( parent ) ;
	
	onePageMonthVariantsCombo->addItem( tr("Block") );
//	onePageMonthVariantsCombo->addItem( tr("1pm Style Two") );
	
	connect 
	(	onePageMonthVariantsCombo,
		SIGNAL(	currentIndexChanged(int)  ),
		this,
		SLOT( onePageMonthVariantsChanged ( int )  )
	) ;
	
	connect
	(	onePageMonthVariantsCombo,
		SIGNAL( activated(int)  ),
		this,
		SLOT ( onePageMonthVariantsChanged ( int )  )
	) ;
	
	onePageYearVariantsCombo = new QComboBox ( parent ) ;
	
	onePageYearVariantsCombo->addItem( tr("One Year Page") );
	onePageYearVariantsCombo->addItem( tr("Two Years Page") );
	
	connect 
	(	onePageYearVariantsCombo,
		SIGNAL(	currentIndexChanged(int)  ),
		this,
		SLOT( onePageYearVariantsChanged ( int )  )
	) ;
	
	connect
	(	onePageYearVariantsCombo,
		SIGNAL( activated(int)  ),
		this,
		SLOT ( onePageYearVariantsChanged ( int )  )
	) ;
	
	twoPageDayVariantsCombo = new QComboBox ( parent ) ;
	
	twoPageDayVariantsCombo->addItem( tr("DIY3 Journal Right") );
	twoPageDayVariantsCombo->addItem( tr("DIY3 Journal Left") );
	
	connect 
	(	twoPageDayVariantsCombo,
		SIGNAL(	currentIndexChanged(int)  ),
		this,
		SLOT( twoPageDayVariantsChanged ( int )  )
	) ;
	
	connect
	(	twoPageDayVariantsCombo,
		SIGNAL( activated(int)  ),
		this,
		SLOT ( twoPageDayVariantsChanged ( int )  )
	) ;
	
	twoPageWeekVariantsCombo = new QComboBox ( parent ) ;
	
	twoPageWeekVariantsCombo->addItem( tr("4 blocks on a page") );
	twoPageWeekVariantsCombo->addItem( tr("Moleskine-like Horizontal") );
	twoPageWeekVariantsCombo->addItem( tr("Moleskine-like Vertical") );
	twoPageWeekVariantsCombo->addItem( tr("Moleskine-like Notebook") );
	twoPageWeekVariantsCombo->addItem( tr("Moleskine-like Landscape") );
	twoPageWeekVariantsCombo->addItem( tr("Columns") );
	
	connect 
	(	twoPageWeekVariantsCombo,
		SIGNAL(	currentIndexChanged(int)  ),
		this,
		SLOT( twoPageWeekVariantsChanged ( int )  )
	) ;
	
	connect
	(	twoPageWeekVariantsCombo,
		SIGNAL( activated(int)  ),
		this,
		SLOT ( twoPageWeekVariantsChanged ( int )  )
	) ;
	
	twoPageMonthVariantsCombo = new QComboBox ( parent ) ;
	
	twoPageMonthVariantsCombo->addItem( tr("DIY3 Portrait") );
	twoPageMonthVariantsCombo->addItem( tr("DIY3 Landscape") );
	
	connect 
	(	twoPageMonthVariantsCombo,
		SIGNAL(	currentIndexChanged(int)  ),
		this,
		SLOT( twoPageMonthVariantsChanged ( int )  )
	) ;
	
	connect
	(	twoPageMonthVariantsCombo,
		SIGNAL( activated(int)  ),
		this,
		SLOT ( twoPageMonthVariantsChanged ( int )  )
	) ;
	
	twoPageYearVariantsCombo = new QComboBox ( parent ) ;
	
	twoPageYearVariantsCombo->addItem( tr("Academic Calendar") );
//	twoPageYearVariantsCombo->addItem( tr("2py Style Two") );
	
	connect 
	(	twoPageYearVariantsCombo,
		SIGNAL(	currentIndexChanged(int)  ),
		this,
		SLOT( twoPageYearVariantsChanged ( int )  )
	) ;
	
	connect
	(	twoPageYearVariantsCombo,
		SIGNAL( activated(int)  ),
		this,
		SLOT ( twoPageYearVariantsChanged ( int )  )
	) ;
	
	//====================================================================================
	QVBoxLayout* layoutv01 = new QVBoxLayout ( parent ) ;
	//====================================================================================
	QFormLayout* form1 = new QFormLayout ( ) ;
	//------------------------------------------------------------------------------------
	form1->addRow ( tr("Week Starts on"), firstDayCombo ) ;
	startDate = QDate::currentDate () ;
	stopDate = QDate::currentDate () ;
	//------------------------------------------------------------------------------------
	startDateWidget = new QDateEdit ( startDate, parent ) ;
	startDateLabel = new QLabel ( tr("First Day:") ) ;

	form1->addRow ( startDateLabel, startDateWidget ) ;
	//------------------------------------------------------------------------------------
	theCal = new QCalendarWidget ( parent ) ;
	today = startDate ;
	theCal->setSelectedDate ( today ) ;
	form1->addRow ( theCal ) ;
	connect ( theCal, SIGNAL ( clicked(const QDate&) ),        this,       SLOT ( calClicked ( const QDate& ) )   ) ;
	connect ( theCal, SIGNAL ( activated(const QDate&) ),      this,       SLOT ( calActivated ( const QDate& ) ) ) ;
	connect ( theCal, SIGNAL ( currentPageChanged(int, int) ), this,       SLOT ( calPaged ( int, int) )          ) ;
	connect ( theCal, SIGNAL ( selectionChanged() ),           this,       SLOT ( calChanged() )                  ) ; 
	connect ( this,   SIGNAL ( dateChanged ( QDate ) ),        renderArea, SLOT ( setDate ( QDate ) )             ) ; 
	connect ( this,   SIGNAL ( dateChanged ( QDate ) ),        this,       SLOT ( updateDates ( QDate ) )         ) ; 
	
	//------------------------------------------------------------------------------------
	stopDateWidget = new QDateEdit ( stopDate, parent ) ;
	stopDateLabel = new QLabel ( tr("Last Day:") ) ;
	form1->addRow ( stopDateLabel, stopDateWidget ) ;
	//------------------------------------------------------------------------------------
	startDateWidget->setDisplayFormat ( "d MMMM yyyy" ) ;
	startDateWidget->setMaximumDate ( stopDate ) ;
	
	stopDateWidget->setDisplayFormat ( "d MMMM yyyy" ) ;
	stopDateWidget->setMinimumDate ( startDate ) ;
	
	connect ( this, SIGNAL ( startDateChanged (QDate) ), renderArea, SLOT ( startDateChanged (QDate) ) ) ; 
	connect	( this, SIGNAL (  stopDateChanged (QDate) ), renderArea, SLOT (  stopDateChanged (QDate) ) ) ;

	connect ( startDateWidget, SIGNAL ( dateChanged (QDate) ), this, SLOT ( startDateWidgetChanged (QDate) ) ) ;
	connect	( stopDateWidget,  SIGNAL ( dateChanged (QDate) ), this, SLOT (  stopDateWidgetChanged (QDate) ) ) ;
	
	renderArea->startDateChanged ( startDate ) ;
	renderArea->stopDateChanged ( stopDate ) ;
	renderArea->firstApptTimeChanged ( QTime ( 8, 0 ) ) ;
	//------------------------------------------------------------------------------------
	firstDayCombo->setCurrentIndex ( 1 ) ;  
	connect ( this, SIGNAL (  dateChanged (QDate) ), renderArea, SLOT ( setDate (QDate) ) ) ; 
	//------------------------------------------------------------------------------------
	layoutv01->addLayout ( form1, 0 ) ;
	//====================================================================================
	QHBoxLayout* layouth02 = new QHBoxLayout () ;
	//------------------------------------------------------------------------------------
	QLabel* dayLabel1 = new QLabel ( tr("per") ) ;
	
	layouth02->addStretch( 999 ) ;
	layouth02->addWidget ( pagesCombo, Qt::AlignHCenter | Qt::AlignTop ) ;
	layouth02->addWidget ( dayLabel1,  Qt::AlignHCenter | Qt::AlignTop ) ;
	layouth02->addWidget ( spanCombo,  Qt::AlignHCenter | Qt::AlignTop ) ;
	layouth02->addStretch( 999 ) ;
	//------------------------------------------------------------------------------------
	layoutv01->addLayout ( layouth02, 0 ) ;
	//====================================================================================
	layoutst1 = new QStackedLayout() ;
	//------------------------------------------------------------------------------------
	layoutst1->addWidget ( onePageDayVariantsCombo ) ;
	layoutst1->addWidget ( onePageWeekVariantsCombo ) ;
	layoutst1->addWidget ( onePageMonthVariantsCombo ) ;
	layoutst1->addWidget ( onePageYearVariantsCombo ) ;
	layoutst1->addWidget ( twoPageDayVariantsCombo ) ;
	layoutst1->addWidget ( twoPageWeekVariantsCombo ) ;
	layoutst1->addWidget ( twoPageMonthVariantsCombo ) ;
	layoutst1->addWidget ( twoPageYearVariantsCombo ) ;
	//------------------------------------------------------------------------------------
	layoutv01->addLayout ( layoutst1, 0 ) ;
	//====================================================================================
	QFormLayout* form2 = new QFormLayout () ;
	//------------------------------------------------------------------------------------
	firstApptTimeWidget = new QTimeEdit ( QTime ( 8, 0 ), parent ) ;
	firstApptLabel = new QLabel ( tr("First Appt Time:") ) ;
	
	firstApptTimeWidget->setDisplayFormat ( "h ap" ) ;
	
	connect
	(	firstApptTimeWidget,
		SIGNAL ( timeChanged (QTime) ),
		renderArea,
		SLOT ( firstApptTimeChanged (QTime) ) 
	) ;
	
	form2->addRow ( firstApptLabel, firstApptTimeWidget ) ;
	//------------------------------------------------------------------------------------
	clockType = new QComboBox ( parent ) ;
	clockTypeLabel = new QLabel ( tr("Appt Clock Type:") ) ;
	
	clockType->addItem( tr("None") );
	clockType->addItem( tr("12 hour") );
	clockType->addItem( tr("24 hour") );
	
	connect 
	(	clockType,
		SIGNAL(	currentIndexChanged(int)  ),
		renderArea,
		SLOT( apptTimeTypeChanged ( int )  )
	) ;
	
	clockType->setCurrentIndex ( 1 ) ;
	form2->addRow ( clockTypeLabel, clockType ) ;
	//------------------------------------------------------------------------------------
	layoutv01->addLayout ( form2, 0 ) ;
	//====================================================================================
	layoutv01->addStretch( 999 ) ;
	
	connect ( this, SIGNAL ( templateNumber (int) ), renderArea, SLOT ( setTemplate (int) ) ) ;
	
	pagesComboChanged ( 0 ) ;
	spanComboChanged ( 0 ) ;
	firstDay = Qt::Monday ;
	
	emit firstDayOfWeek( firstDay ) ;
	emit startDateChanged ( startDate ) ;
	emit stopDateChanged ( stopDate ) ;
	emit dateChanged ( today ) ;
	
	return parent ;
}

void MyWindow::pagesComboChanged ( int howMany )
{
	pagesPer = pagesCombo->itemData(howMany).toInt() ;
	spanComboChanged ( spanCombo->currentIndex () ) ;
	update() ;
}
;
void MyWindow::spanComboChanged ( int which )
{	QDate now ;
	
	renderArea->setSpan ( which ) ;
	
	startDateWidget->setEnabled ( true ) ;
	stopDateWidget->setEnabled ( true ) ;
	
	switch ( which )
	{
		case 0: // day
			whatKind = CAL_DAY ;
			startDateWidget->setDisplayFormat ( "d MMMM yyyy" ) ;
			stopDateWidget->setDisplayFormat ( "d MMMM yyyy" ) ;
			theCal->setDateEditEnabled ( true ) ;
			stopDateLabel->setText( tr("Last Day:") ) ;
			startDateLabel->setText( tr("First Day:") ) ;
			
			if ( pagesPer == 1 )
			{	layoutst1->setCurrentWidget ( onePageDayVariantsCombo ) ;
				onePageDayVariantsChanged ( onePageDayVariantsCombo->currentIndex() ) ;
			}
			else
			{	layoutst1->setCurrentWidget ( twoPageDayVariantsCombo ) ;
				twoPageDayVariantsChanged ( twoPageDayVariantsCombo->currentIndex() ) ;
			}
			break ;
		case 1: //week
			whatKind = CAL_WEEK ;
			startDateWidget->setDisplayFormat ( "d MMMM yyyy" ) ;
			stopDateWidget->setDisplayFormat ( "d MMMM yyyy" ) ;
			theCal->setDateEditEnabled ( true ) ;
			stopDateLabel->setText( tr("Last Week Starts:") ) ;
			startDateLabel->setText( tr("First Week Starts:") ) ;

			calChanged() ;
					
			if ( pagesPer == 1 )
			{	layoutst1->setCurrentWidget ( onePageWeekVariantsCombo ) ;
				onePageWeekVariantsChanged ( onePageWeekVariantsCombo->currentIndex() ) ;
			}
			else
			{	layoutst1->setCurrentWidget ( twoPageWeekVariantsCombo ) ;
				twoPageWeekVariantsChanged ( twoPageWeekVariantsCombo->currentIndex() ) ;
			}
			break ;
		case 2: //month
			whatKind = CAL_MONTH ;
			startDateWidget->setDisplayFormat ( "MMMM yyyy" ) ;
			stopDateWidget->setDisplayFormat ( "MMMM yyyy" ) ;
			theCal->setDateEditEnabled ( false ) ;
			
			stopDateLabel->setText( tr("Last Month:") ) ;
			startDateLabel->setText( tr("First Month:") ) ;
			
			calChanged() ;
		
			if ( pagesPer == 1 )
			{	layoutst1->setCurrentWidget ( onePageMonthVariantsCombo ) ;
				onePageMonthVariantsChanged ( onePageMonthVariantsCombo->currentIndex() ) ;
			}
			else
			{	layoutst1->setCurrentWidget ( twoPageMonthVariantsCombo ) ;
				twoPageMonthVariantsChanged ( twoPageMonthVariantsCombo->currentIndex() ) ;
			}
			break ;
		case 3: //year
			whatKind = CAL_YEAR ;
			
			startDateWidget->setDisplayFormat ( "MMMM yyyy" ) ;
			stopDateWidget->setDisplayFormat ( "MMMM yyyy" ) ;
			startDateWidget->setEnabled ( false ) ;
			stopDateWidget->setEnabled ( false ) ;

			calChanged() ;

			if ( pagesPer == 1 )
			{	layoutst1->setCurrentWidget ( onePageYearVariantsCombo ) ;
				onePageYearVariantsChanged ( onePageYearVariantsCombo->currentIndex() ) ;
			}
			else
			{	layoutst1->setCurrentWidget ( twoPageYearVariantsCombo ) ;
				twoPageYearVariantsChanged ( twoPageYearVariantsCombo->currentIndex() ) ;
			}
			break ;
		default: // use day
			whatKind = CAL_DAY ;
			startDateWidget->setDisplayFormat ( "d MMMM yyyy" ) ;
			stopDateWidget->setDisplayFormat ( "d MMMM yyyy" ) ;
			theCal->setDateEditEnabled ( true ) ;
			stopDateLabel->setText( tr("Last Day:") ) ;
			startDateLabel->setText( tr("First Day:") ) ;
			
			if ( pagesPer == 1 )
			{	layoutst1->setCurrentWidget ( onePageDayVariantsCombo ) ;
				onePageDayVariantsChanged ( onePageDayVariantsCombo->currentIndex() ) ;
			}
			else
			{	layoutst1->setCurrentWidget ( twoPageDayVariantsCombo ) ;
				twoPageDayVariantsChanged ( twoPageDayVariantsCombo->currentIndex() ) ;
			}
			break ;
	}
}
void MyWindow::firstDayComboChanged ( int index )
{	
	firstDay = Qt::DayOfWeek(firstDayCombo->itemData(index).toInt()) ;

	theCal->setFirstDayOfWeek( firstDay ) ;
	
	QDate now = theCal->selectedDate() ;
	
	if ( whatKind == CAL_WEEK )
	{	if ( now.dayOfWeek() != firstDay ) 
		{	while ( now.dayOfWeek() != firstDay )
			{	now = now.addDays ( -1 ) ;
			}
		}
	}

	theCal->setSelectedDate ( now ) ;
	emit dateChanged ( now ) ;	
	emit firstDayOfWeek( firstDay ) ;
}

void MyWindow::onePageDayVariantsChanged ( int style )
{
	hideAllOptions () ;
	firstApptTimeWidget->show() ;
	firstApptLabel->show() ;
	clockTypeLabel->show() ;
	clockType->show() ;
	thePageStyle = style ;
	emit templateNumber ( thePageStyle ) ;
}
void MyWindow::onePageWeekVariantsChanged ( int style )
{
	hideAllOptions () ;
	firstApptTimeWidget->show() ;
	firstApptLabel->show() ;
	clockTypeLabel->show() ;
	clockType->show() ;
	thePageStyle = 10 + style ;
	emit templateNumber ( thePageStyle ) ;
}
void MyWindow::onePageMonthVariantsChanged ( int style )
{
	hideAllOptions () ;
	thePageStyle = 20 + style ;
	emit templateNumber ( thePageStyle ) ;
}
void MyWindow::onePageYearVariantsChanged ( int style )
{
	hideAllOptions () ;
	thePageStyle = 30 + style ;
	emit templateNumber ( thePageStyle ) ;
}
void MyWindow::twoPageDayVariantsChanged ( int style )
{
	hideAllOptions () ;
	firstApptTimeWidget->show() ;
	firstApptLabel->show() ;
	clockTypeLabel->show() ;
	clockType->show() ;
	thePageStyle = 100 + style ;
	emit templateNumber ( thePageStyle ) ;
}
void MyWindow::twoPageWeekVariantsChanged ( int style )
{
	hideAllOptions () ;
	firstApptTimeWidget->show() ;
	firstApptLabel->show() ;
	clockTypeLabel->show() ;
	clockType->show() ;
	thePageStyle = 110 + style ;
	emit templateNumber ( thePageStyle ) ;
}
void MyWindow::twoPageMonthVariantsChanged ( int style )
{	hideAllOptions () ;
	thePageStyle = 120 + style ;
	emit templateNumber ( thePageStyle ) ;
}
void MyWindow::twoPageYearVariantsChanged ( int style )
{	hideAllOptions () ;
	thePageStyle = 130 + style ;
	emit templateNumber ( thePageStyle ) ;
}

void MyWindow::showEvent(QShowEvent *event)
{	Q_UNUSED(event);
	emit templateNumber ( thePageStyle ) ;
}

void MyWindow::startDateWidgetChanged ( QDate when )
{	QDate now = when ;
	int increment ;
	
	if ( when < startDate )
	{	increment = -1 ;
	}
	else
	{	increment = 1 ;
	}

	switch ( whatKind )
	{
		case CAL_DAY:
			break ;
		case CAL_MONTH:
			break ;
		case CAL_YEAR:
			break ;
		case CAL_WEEK:
			if ( startDateWidget->date().dayOfWeek() != firstDay ) 
			{	while ( now.dayOfWeek() != firstDay )
				{	now = now.addDays ( increment ) ;
				}
				startDate = now ;
				startDateWidget->setDate ( now ) ;
			}
			break ;
	}
	emit startDateChanged ( now ) ;
}

void MyWindow::stopDateWidgetChanged ( QDate when )
{	QDate now = when ;
	int increment ;
	
	if ( when < stopDate )
	{	increment = -1 ;
	}
	else
	{	increment = 1 ;
	}

	switch ( whatKind )
	{
		case CAL_WEEK:
			if ( stopDateWidget->date().dayOfWeek() != firstDay ) 
			{	while ( now.dayOfWeek() != firstDay )
				{	now = now.addDays ( increment ) ;
				}
				stopDate = now ;
				stopDateWidget->setDate ( now ) ;
			}
			break ;
		case CAL_DAY:
			break ;
		case CAL_MONTH:
			break ;
		case CAL_YEAR:
			break ;
	}		
	emit stopDateChanged ( now ) ;
}

void MyWindow::updateDates ( QDate when )
{	QDate now ;
//	qDebug() << "MyWindow::updateDates" ;

	if ( stopDateWidget->date() < when )
	{	stopDateWidget->setDate ( when ) ;
		now = when ;
	}
	else
	{	now = stopDateWidget->date() ;
		stopDateWidget->setDate ( now ) ;
	}
	stopDateWidgetChanged ( now ) ;
	
	if ( startDateWidget->date() > when )
	{	startDateWidget->setDate ( when ) ;
		now = when ;
	}
	else
	{	now = startDateWidget->date() ;
		startDateWidget->setDate ( now ) ;
	}
	startDateWidgetChanged ( now ) ;

}

void MyWindow::calClicked ( const QDate & theDate )
{	QDate newDate = theDate ;

	switch ( whatKind )
	{	case CAL_WEEK:
			while ( newDate.dayOfWeek() != theCal->firstDayOfWeek() )
			{	newDate = newDate.addDays ( -1 ) ;
			}
			theCal->setSelectedDate ( newDate ) ;
			break ;
		case CAL_DAY:
			break ;
		case CAL_MONTH:
			newDate.setDate ( newDate.year(), newDate.month(), 1 ) ; // I want the first of the month

			break ;
		case CAL_YEAR:
			newDate.setDate ( newDate.year(), newDate.month(), 1 ) ; // I want the first of the month
			startDateWidget->setDate ( newDate ) ;
			stopDateWidget->setDate ( newDate.addMonths(11) ) ;

			break ;
	}		
	theCal->setSelectedDate ( newDate ) ;

	emit dateChanged ( newDate ) ;
	
	startDateWidget->setMaximumDate ( newDate ) ;
	stopDateWidget->setMinimumDate ( newDate ) ;

	today = newDate ;
}

void MyWindow::calActivated ( const QDate & theDate )
{	QDate newDate = theDate ;
		
	switch ( whatKind )
	{	case CAL_WEEK:
		while ( newDate.dayOfWeek() != theCal->firstDayOfWeek() )
		{	newDate = newDate.addDays ( -1 ) ;
		}
		theCal->setSelectedDate ( newDate ) ;
		break ;
	case CAL_DAY:
		break ;
	case CAL_MONTH:
		newDate.setDate ( newDate.year(), newDate.month(), 1 ) ; // I want the first of the month
		
		break ;
	case CAL_YEAR:
		newDate.setDate ( newDate.year(), newDate.month(), 1 ) ; // I want the first of the month
		startDateWidget->setDate ( newDate ) ;
		stopDateWidget->setDate ( newDate.addMonths(11) ) ;
		break ;
	}		
	
	theCal->setSelectedDate ( newDate ) ;

	emit dateChanged ( newDate ) ;

	startDateWidget->setMaximumDate ( newDate ) ;
	stopDateWidget->setMinimumDate ( newDate ) ;

	today = newDate ;
}

void MyWindow::calPaged ( int year, int month )
{	QDate now ( year, month, theCal->selectedDate().day() ) ;
		
	switch ( whatKind )
	{
		case CAL_WEEK:
			if ( now > today )
			{	while ( now.dayOfWeek() != theCal->firstDayOfWeek() )
				{	now = now.addDays ( 1 ) ;
				}
			}
			else
			{	while ( now.dayOfWeek() != theCal->firstDayOfWeek() )
				{	now = now.addDays ( -1 ) ;
				}
			}
			break ;
		case CAL_DAY:
			break ;
		case CAL_MONTH:
			now.setDate ( now.year(), now.month(), 1 ) ; // I want the first of the month

			break ;
		case CAL_YEAR:
			now.setDate ( now.year(), now.month(), 1 ) ; // I want the first of the month
			startDateWidget->setDate ( now ) ;
			stopDateWidget->setDate ( now.addMonths(11) ) ;
			
			break ;
	}		
	
	
	theCal->setSelectedDate ( now ) ;
	emit dateChanged ( now ) ;	
	today = now ;

	startDateWidget->setMaximumDate ( now ) ;
	stopDateWidget->setMinimumDate ( now ) ;
	
}

void MyWindow::calChanged ( void )
{	QDate now = theCal->selectedDate() ;
	
	switch ( whatKind )
	{
		case CAL_WEEK:
			if ( now > today )
			{	while ( now.dayOfWeek() != theCal->firstDayOfWeek() )
				{	now = now.addDays ( 1 ) ;
				}
			}
			else
			{	while ( now.dayOfWeek() != theCal->firstDayOfWeek() )
				{	now = now.addDays ( -1 ) ;
				}
			}
			break ;
		case CAL_DAY:
			break ;
		case CAL_MONTH:
			now.setDate ( now.year(), now.month(), 1 ) ; // I want the first of the month
			break ;
		case CAL_YEAR:
			now.setDate ( now.year(), now.month(), 1 ) ; // I want the first of the month
			startDateWidget->setDate ( now) ;
			stopDateWidget->setDate ( now.addMonths(11) ) ;
			
			break ;
	}		
	
	theCal->setSelectedDate ( now ) ;
	
	emit dateChanged ( now ) ;
	today = now ;
	startDateWidget->setMaximumDate ( now ) ;
	stopDateWidget->setMinimumDate ( now ) ;
}

void MyWindow::hideAllOptions ( void )
{	firstApptTimeWidget->hide() ;
	firstApptLabel->hide() ;
	clockTypeLabel->hide() ;
	clockType->hide() ;
}
