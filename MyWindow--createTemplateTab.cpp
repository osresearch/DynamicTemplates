//
// $Id: MyWindow--createTemplateTab.cpp,v 1.3 2009/01/12 03:52:59 igor Exp $
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

QWidget* MyWindow::createTemplateTab ( QWidget* grandParent )
//  : QWidget(parent)
{
	QWidget* parent = new QWidget ( grandParent ) ;
	templateCombo = new QComboBox ( parent ) ;
	
	templateCombo->addItem( tr("Calendars") ) ;
	templateCombo->addItem( tr("Notes") ) ;
	templateCombo->addItem( tr("Checklists") ) ;
	templateCombo->addItem( tr("Charts") ) ;
//	templateCombo->addItem( tr("Foo") ) ;
//	templateCombo->addItem( tr("Bar") ) ;

	connect ( templateCombo, SIGNAL( activated(int) ), this, SLOT( templateComboChanged ( int ) ) ) ;
	
	QVBoxLayout* layoutv01 = new QVBoxLayout ( parent ) ;
	QHBoxLayout* layouth01 = new QHBoxLayout () ;
	
	layouth01->addStretch( 999 ) ;
	layouth01->addWidget ( templateCombo,  Qt::AlignHCenter | Qt::AlignTop ) ;
	layouth01->addStretch( 999 ) ;

	layoutv01->addLayout ( layouth01, 0 ) ;
	
	QStackedLayout *stackedLayout = new QStackedLayout() ;
	
	stackedLayout->addWidget( createCalendarTab( parent ) );
	stackedLayout->addWidget( createNotesTab( parent ) );
	stackedLayout->addWidget( createChecklistsTab( parent ) );
	stackedLayout->addWidget( createChartsTab( parent ) );
	
	connect(templateCombo, SIGNAL(activated(int)), stackedLayout, SLOT(setCurrentIndex(int)));

	layoutv01->addLayout ( stackedLayout, 0 ) ;
	templateComboChanged ( 0 ) ;

	return parent ;
}

void MyWindow::templateComboChanged ( int which )
{
	switch ( which )
	{
		case 0: // Calendars
			spanComboChanged ( spanCombo->currentIndex() ) ;
			break ;
		case 1: // Notes
			notesComboBoxChanged ( notesComboBox->currentIndex() ) ;
			break ;
		case 2: // Checklists
			break ;
		case 3: // Charts
			break ;
		case 4: // Foo
			break ;
		case 5: // Bar
			break ;
		default:
			break ;
	}

	update() ;
}