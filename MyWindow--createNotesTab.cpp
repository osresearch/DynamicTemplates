//
// $Id: MyWindow--createNotesTab.cpp,v 1.2 2009/01/12 03:52:59 igor Exp $
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

QWidget* MyWindow::createNotesTab ( QWidget* grandParent )
//  : QWidget(parent)
{
	QWidget* parent = new QWidget ( grandParent ) ;

	QVBoxLayout* layoutv01 = new QVBoxLayout ( parent ) ;
	QHBoxLayout* layouth02 = new QHBoxLayout () ;
	QHBoxLayout* layouth03 = new QHBoxLayout () ;
	//------------------------------------------------------------------------------------
//	QLabel* daLabel = new QLabel ( "Notes Dynamic Templates are coming" ) ;
	
	
	notesComboBox = new QComboBox;
	notesComboBox->addItem(tr("Plain Lined"));
	notesComboBox->addItem(tr("Plain Lined w/Grey Column"));
	notesComboBox->addItem(tr("Grey Lined w/Grey Column"));
	notesComboBox->addItem(tr("Cornell Plain"));
	notesComboBox->addItem(tr("Cornell w/Grid & Lines"));
	notesComboBox->addItem(tr("Grid"));
	notesComboBox->addItem(tr("Dots"));
	
	connect ( notesComboBox, SIGNAL ( activated ( int ) ), this, SLOT ( notesComboBoxChanged ( int ) ) ) ;
	
	QComboBox *notesAlignmentComboBox = new QComboBox;
	notesAlignmentComboBox->addItem(tr("Align Left"));
	notesAlignmentComboBox->addItem(tr("Centered"));
	notesAlignmentComboBox->addItem(tr("Align Right"));

	connect ( notesAlignmentComboBox, SIGNAL ( activated ( int ) ), this, SLOT ( notesAlignmentComboBoxChanged ( int ) ) ) ;
	
	alignmentLineEdit = new QLineEdit ( renderArea->getText() ) ;
	connect ( alignmentLineEdit, SIGNAL ( textChanged ( QString ) ), renderArea, SLOT ( setText ( QString ) ) ) ;


	layouth02->addStretch( 999 ) ;
//	layouth02->addWidget ( daLabel,  Qt::AlignHCenter | Qt::AlignTop ) ;
	layouth02->addWidget ( notesComboBox,  Qt::AlignHCenter | Qt::AlignTop ) ;
	layouth02->addStretch( 999 ) ;

	layouth03->addStretch( 999 ) ;
	layouth03->addWidget ( notesAlignmentComboBox,  Qt::AlignHCenter | Qt::AlignTop ) ;
	layouth03->addStretch( 999 ) ;
	
	layoutv01->addLayout ( layouth02, 0 ) ;
	layoutv01->addLayout ( layouth03, 0 ) ;
	layoutv01->addWidget ( alignmentLineEdit, Qt::AlignHCenter | Qt::AlignTop ) ;
	//====================================================================================
	layoutv01->addStretch( 999 ) ;
	
	return parent ;
}

void MyWindow::notesComboBoxChanged ( int which ) 
{
	emit templateNumber ( 40 + which ) ;
}

void MyWindow::notesAlignmentComboBoxChanged(int index)
{
	//	qDebug() << "MyWindow::alignmentChanged " << index ;
	
	switch (index) {
		case 0:
			alignmentLineEdit->setAlignment ( Qt::AlignLeft ) ;
			renderArea->setAlignment ( Qt::AlignLeft ) ;
			break;
		case 1:
			alignmentLineEdit->setAlignment ( Qt::AlignCenter ) ;
			renderArea->setAlignment ( Qt::AlignCenter ) ;
			break;
		case 2:
			alignmentLineEdit->setAlignment ( Qt::AlignRight ) ;
			renderArea->setAlignment ( Qt::AlignRight ) ;
	}
}
