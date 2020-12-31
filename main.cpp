//
// $Id: main.cpp,v 1.4 2009/01/06 03:35:31 igor Exp $
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


#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QDir>

#include <QtDebug>  // this is here for debugging 

#include "MyWindow.h"

int main(int argc, char *argv[])
{
	QTranslator appTrans ;
	QApplication app(argc, argv);
	
#if defined(Q_OS_MAC)
	appTrans.load ( QObject::tr("DIY_Dynamic_Templates_") + QLocale::system().name(), QDir::cleanPath( qApp->applicationDirPath() + "../../../../" ) ) ;
#else
	appTrans.load ( QObject::tr("DIY_Dynamic_Templates_") + QLocale::system().name(), qApp->applicationDirPath() ) ;
#endif
	
	app.installTranslator ( &appTrans ) ;
	
	MyWindow window;
    window.show();
    return app.exec();
}

