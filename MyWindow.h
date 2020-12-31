//
// $Id: MyWindow.h,v 1.11 2009/08/16 22:35:58 igor Exp $
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


#ifndef MY_WINDOW_H
#define MY_WINDOW_H


#include <QWidget>
#include <QtGui>
#include <QtDebug>

#include "RenderArea.h"

#define INCHES_TO_MM (25.40)
#define MM_TO_INCHES (1.00 / 25.40)
#define CM_TO_MM (10.0)
#define MM_TO_CM (1.00 / 10.0)

class MyWindow : public QMainWindow
{
	Q_OBJECT
	
	public:
		MyWindow() ;

		int currentUnits () ;
		void updateSize () ;
		int getStyle () ;

		RenderArea* renderArea ;
		QSizeF size () ;
		qreal lines () ;

	public slots:
		void linesComboBoxChanged ( int  ) ;
		void penWidthSliderChanged ( int ) ;
		void setPenWidthLabel ( int ) ;
		void calClicked       ( const QDate & ) ;
		void calActivated     ( const QDate & ) ;
		void calPaged         ( int, int ) ;
		void calChanged       ( void ) ;
		void notesAlignmentComboBoxChanged( int ) ;

		
	signals:
		void pageSizeChanged ( QRectF ) ;
		void pageMarginsChanged ( QRectF ) ;
		void linesChanged ( qreal ) ;		
		void penWidthChanged ( int ) ;
		void templateNumber ( int ) ;	
		void firstDayOfWeek ( Qt::DayOfWeek ) ;
		void startDateChanged ( QDate ) ;
		void stopDateChanged ( QDate ) ;
		void dateChanged ( QDate today ) ;
	
	private slots:
	    void about();

	private:
	    void createActions();
	    void createMenus();
	    void createToolBars();
	    void createStatusBar();
	    void createDockWindows();
		QWidget* createCalendarTab ( QWidget* ) ;
		QWidget* createLinesTab ( QWidget* ) ;
		QWidget* createPageTab ( QWidget* ) ;
		QWidget* createTemplateTab ( QWidget* ) ;
		
		QWidget* createNotesTab ( QWidget* );
		QWidget* createChecklistsTab ( QWidget* );
		QWidget* createChartsTab ( QWidget* );
		QLineEdit* alignmentLineEdit ;
	
		void hideAllOptions ( void ) ;

		QDoubleSpinBox* scaleWidget ;

	    QMenu*		fileMenu ;
	    QMenu*		viewMenu ;
	    QMenu*		helpMenu ;
		
		QToolBox*   toolWidget ;
		
	    QToolBar*	theToolBar ;
	    QAction*	saveAct ;
	    QAction*	drawAct ;
	    QAction*	aboutAct ;
	    QAction*	aboutQtAct ;
	    QAction*	quitAct ;

//--------------------------------------------------------------------------------------------
		enum calendarSpanType
		{	CAL_DAY,
			CAL_WEEK,
			CAL_MONTH,
			CAL_YEAR
		}  ;
		
		calendarSpanType whatKind ;
		int              pagesPer ;
		int              thePageStyle ;
		Qt::DayOfWeek    firstDay ;
		QDate            startDate ;
		QDate            stopDate ;
		QDate            today ;
		QCalendarWidget* theCal ;
		
		void showEvent ( QShowEvent* ) ;

		QDateEdit*       startDateWidget ;
		QDateEdit*       stopDateWidget ;
		QLabel*       startDateLabel ;
		QLabel*       stopDateLabel ;
		QTimeEdit*       firstApptTimeWidget ;
		QLabel*          firstApptLabel ;
		QComboBox*       clockType ;
		QLabel*          clockTypeLabel ;
		QComboBox* firstDayCombo ;
		QComboBox* pagesCombo ;
		QComboBox* spanCombo ;
		QComboBox* onePageDayVariantsCombo ;
		QComboBox* onePageWeekVariantsCombo ;
		QComboBox* onePageMonthVariantsCombo ;
		QComboBox* onePageYearVariantsCombo ;
		QComboBox* twoPageDayVariantsCombo ;
		QComboBox* twoPageWeekVariantsCombo ;
		QComboBox* twoPageMonthVariantsCombo ;
		QComboBox* twoPageYearVariantsCombo ;
		QStackedLayout* layoutst1 ;
		
//--------------------------------------------------------------------------------------------
		QComboBox* templateCombo ;
//--------------------------------------------------------------------------------------------
		QComboBox* linesComboBox ;
		QLabel*    linesThickLabel ;
//-------------------------------------------------------------------------------------------
		QComboBox* notesComboBox ;
//--------------------------------------------------------------------------------------------
		QScrollArea*     scrollArea ;
		
		QSizeF theSize ;
		bool isItCustom ;
		bool isItInches ;
		bool portrait ;
		qreal lineSpaceValue ;
		qreal topMarginValue ;
		qreal bottomMarginValue ;
		qreal innerMarginValue ;
		qreal outerMarginValue ;
		
		QComboBox* unitComboBox ;
		
		QComboBox* orientationCombo ;
		QComboBox* majorTypeSizeCombo ;
		QComboBox* fcSizeCombo ;
		QComboBox* filofaxSizeCombo ;
		QComboBox* circaSizeCombo ;
		QComboBox* usSizeCombo ;
		QComboBox* euroSizeCombo ;
		QDoubleSpinBox* customHeight ;
		QDoubleSpinBox* customWidth ;
		QDoubleSpinBox* customLine ;
		QLabel* dimLabel ;
		QLabel* pageSizeLabel ;
		QLabel* sizeDisplayLabel ;
		
		QDoubleSpinBox* topMargin ;
		QDoubleSpinBox* bottomMargin ;
		QDoubleSpinBox* innerMargin ;
		QDoubleSpinBox* outerMargin ;

	private slots:
		void orientationComboChanged ( int  ) ;
		void majorTypeSizeComboChanged ( int  ) ;
		void fcSizeComboChanged ( int  ) ;
		void filofaxSizeComboChanged ( int  ) ;
		void circaSizeComboChanged ( int  ) ;
		void usSizeComboChanged ( int  ) ;
		void euroSizeComboChanged ( int  ) ;
		void customHeightChanged ( double ) ;
		void customWidthChanged ( double ) ;
		void customLineChanged ( double ) ;
		void topMarginChanged ( double ) ;
		void bottomMarginChanged ( double ) ;
		void innerMarginChanged ( double ) ;
		void outerMarginChanged ( double ) ;
		void unitComboBoxChanged ( int  ) ;
		void notesComboBoxChanged ( int  ) ;
		
		void templateComboChanged ( int  ) ;
		
		void onePageDayVariantsChanged ( int  ) ;
		void onePageWeekVariantsChanged ( int  ) ;
		void onePageMonthVariantsChanged ( int  ) ;
		void onePageYearVariantsChanged ( int  ) ;
		void twoPageDayVariantsChanged ( int  ) ;
		void twoPageWeekVariantsChanged ( int  ) ;
		void twoPageMonthVariantsChanged ( int  ) ;
		void twoPageYearVariantsChanged ( int  ) ;
		
		void pagesComboChanged ( int ) ;
		void spanComboChanged ( int ) ;
		void firstDayComboChanged ( int ) ;
		void startDateWidgetChanged ( QDate ) ;
		void stopDateWidgetChanged ( QDate ) ;
		void updateDates ( QDate ) ;
} ;

#endif
	
	
