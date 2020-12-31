//
// $Id: MyWindow--createChecklistsTab.cpp,v 1.3 2010/01/01 20:22:32 igor Exp $
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

QWidget* MyWindow::createChecklistsTab ( QWidget* grandParent )
//  : QWidget(parent)
{
	QWidget* parent = new QWidget ( grandParent ) ;

	QVBoxLayout* layoutv01 = new QVBoxLayout ( parent ) ;
	QHBoxLayout* layouth02 = new QHBoxLayout () ;
	//------------------------------------------------------------------------------------
	QLabel* daLabel = new QLabel ( tr("Checklist Dynamic Templates are coming") ) ;
	layouth02->addStretch( 999 ) ;
	layouth02->addWidget ( daLabel,  Qt::AlignHCenter | Qt::AlignTop ) ;
	layouth02->addStretch( 999 ) ;
	
	layoutv01->addLayout ( layouth02, 0 ) ;
	//====================================================================================
	layoutv01->addStretch( 999 ) ;
	
	return parent ;
}
