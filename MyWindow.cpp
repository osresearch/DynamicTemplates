//
// $Id: MyWindow.cpp,v 1.11 2010/01/01 20:22:32 igor Exp $
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

MyWindow::MyWindow()
{
	this->setWindowTitle ( "DIY Dynamic Templates (" + QLocale::system().name() + ")" ) ;
	renderArea = new RenderArea ( this ) ;
	
	QScrollArea *scrollArea = new QScrollArea ( this ) ;

	scrollArea->setWidget(renderArea);
	scrollArea->setFrameStyle ( QFrame::Box ) ;

	lineSpaceValue = 7.10 ;	
	isItCustom = false ;

	setCentralWidget(scrollArea) ;
	createActions() ;
    createMenus();
	createToolBars();
    createStatusBar();
    createDockWindows();
}

void MyWindow::about()
{
	QMessageBox::about
	(	this,
		tr("About Dynamic Templates"),
		tr("This is the Do-It-Yourself Dynamic Template application")
	) ;
}

void MyWindow::createActions()
{
	saveAct = new QAction( tr("&Save PDF"), this);
	saveAct->setShortcut(tr("Ctrl+S"));
    saveAct->setStatusTip(tr("Save the current template as PDF"));
    connect(saveAct, SIGNAL(triggered()), renderArea, SLOT(outputPDF()));
	
	drawAct = new QAction( tr("&Save SVG"), this);
	drawAct->setShortcut(tr("Ctrl+P"));
    drawAct->setStatusTip(tr("Save the current template as SVG"));
    connect(drawAct, SIGNAL(triggered()), renderArea, SLOT(outputSVG()));
	
	aboutAct = new QAction(tr("&About"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));
	
	aboutQtAct = new QAction(tr("About &Qt"), this);
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
	
	quitAct = new QAction(tr("&Quit"), this);
    quitAct->setShortcut(tr("Ctrl+Q"));
    quitAct->setStatusTip(tr("Quit the application"));
    connect(quitAct, SIGNAL(triggered()), this, SLOT(close()));
}

void MyWindow::createMenus()
{
	fileMenu = menuBar()->addMenu(tr("&File"));
	fileMenu->addAction(saveAct);
	fileMenu->addAction(drawAct);
	fileMenu->addSeparator();
    fileMenu->addAction(quitAct);

	viewMenu = menuBar()->addMenu(tr("&View"));
	
	helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);
	
}

void MyWindow::createToolBars()
{
	theToolBar = addToolBar( tr("Scale") );
	
	scaleWidget = new QDoubleSpinBox() ;

	QLabel* x = new QLabel ( tr("Scale: ") ) ;
	theToolBar->addWidget ( x ) ;
	theToolBar->addWidget ( scaleWidget ) ;
	connect ( scaleWidget, SIGNAL ( valueChanged ( double ) ), renderArea, SLOT( setScale ( double ) ) ) ;
	scaleWidget->setValue ( 25.00 ) ;
}

void MyWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"), 5000 );
}

void MyWindow::createDockWindows()
{
	QDockWidget *dock = new QDockWidget(tr("Controls"), this);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	dock->setFeatures ( QDockWidget::AllDockWidgetFeatures ) ;
    	
    toolWidget = new QToolBox (dock);

	toolWidget->addItem( createLinesTab( toolWidget), tr("Line Spacing and Thickness") ) ;

	toolWidget->addItem( createPageTab ( toolWidget ), tr("Page Size") ) ;

	toolWidget->addItem( createTemplateTab( toolWidget), tr("Template") ) ;
	
    dock->setWidget(toolWidget);
	addDockWidget(Qt::RightDockWidgetArea, dock);
	viewMenu->addAction(dock->toggleViewAction());
	
	connect ( this, SIGNAL ( pageSizeChanged ( QRectF ) ), renderArea, SLOT( setPageSize ( QRectF ) )	) ;
	connect ( this, SIGNAL ( pageMarginsChanged ( QRectF ) ), renderArea, SLOT( setMarginSize ( QRectF ) ) ) ;
	connect ( this, SIGNAL ( linesChanged ( qreal ) ), renderArea, SLOT( setLineSpacing ( qreal ) ) ) ;
	connect ( this, SIGNAL ( penWidthChanged ( int ) ), renderArea, SLOT( setPenWidth ( int ) ) ) ;
	
	linesComboBoxChanged ( 1 ) ;
	updateSize () ;
	
	toolWidget->setCurrentIndex ( 2 ) ;
}
