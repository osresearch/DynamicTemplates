//
// $Id: RenderArea.h,v 1.21 2009/12/17 03:46:59 igor Exp $
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

#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QDate>
#include <QPen>
#include <QWidget>
#include <QPainter>
#include <QPrinter>
#include <QSvgGenerator>

class RenderArea : public QWidget
{
    Q_OBJECT

public:
    RenderArea(QWidget *parent = 0 ) ;
    QSize minimumSize () const;
    QSize sizeHint() const;
	QDate getStopDate ( void ) ;
	QDate getStartDate ( void ) ;
	void setSpan ( int ) ;
	
	QString	getText ( void ) ;
	void setAlignment ( Qt::Alignment ) ;
	
public slots:
	void setFirstDayOfWeek ( Qt::DayOfWeek ) ;
	void setMarginSize ( QRectF ) ;
	void setPageSize ( QRectF ) ;
	void setPenWidth (int value) ;
	void setScale ( double value ) ;
	void setTemplate ( int ) ;
	void setLineSpacing ( qreal ) ;
	void stopDateChanged ( const QDate& ) ;
	void setDate ( const QDate& ) ;
	void startDateChanged ( const QDate& ) ;
	void apptTimeTypeChanged ( int ) ;
	void firstApptTimeChanged ( const QTime& ) ;
	
	void outputPDF ( void ) ;
	void outputSVG ( void ) ;
	void setText ( QString ) ;
		
protected:
   	enum BarType { BAR_RECT, BAR_ROUND, BAR_ROUND_RIGHT, BAR_TRIANGLE_LEFT, BAR_TRIANGLE_RIGHT } ;
	enum GradType { GRAD_UP, GRAD_DOWN, GRAD_LEFT, GRAD_RIGHT } ;
	enum RowType { ROW_PLAIN, ROW_GREY, ROW_GREY_STRIPE, ROW_GREY_TWO_STRIPE } ;
	enum ApptBoxType { APPT_BOX_ZERO, APPT_BOX_SINGLE, APPT_BOX_DOUBLE, APPT_BOX_QUAD } ;
	enum DrawType { DRAW_TO_SCREEN, DRAW_TO_PRINTER, DRAW_TO_PDF, DRAW_TO_SVG } ;
	enum calendarSpanType
	{	CAL_DAY,
		CAL_WEEK,
		CAL_MONTH,
		CAL_YEAR
	}  ;
	enum moleskineType {MOLE_VERTICAL, MOLE_HORIZINTAL, MOLE_NOTEBOOK, MOLE_LANDSCAPE} ;

	
	calendarSpanType whatKind ;
		
	void paintEvent ( QPaintEvent* ) ;

	
	void draw ( int, DrawType, QPainter* ) ;
	void drawAppointmentRow ( QPainter*, QRectF, ApptBoxType, QString ) ;
	void drawBar ( QPainter*, QRectF, BarType ) ;
	void drawGradientBox ( QPainter*, QRectF, QColor, QColor, GradType, BarType ) ;
	void drawLittleMonth ( QPainter*, QDate, QRectF, bool ) ;
	void drawLittleMonthMoleskine ( QPainter*, QDate, QRectF ) ;
	void drawOneShortDay ( QRectF, QDate, QPainter*, bool ) ;
	void drawRow ( QPainter*, QRectF, RowType, bool ) ;
	void drawShadowedRect ( QPainter*, QRectF, QColor, QColor ) ;
	void drawSubHeader ( QPainter*, QRectF, qreal, QString ) ;
	void drawRightHandSubHeader ( QPainter*, QRectF, qreal, QString ) ;
	void drawSinglePageNotes ( QPainter* ) ;

	
	void incrementFileName( QPainter* painter ) ;


	QRectF fitRectToString ( QRectF, QString, QPainter*, qreal ) ;
	void fitStringInRect ( QRectF, QString, QPainter*, Qt::Alignment, qreal ) ;
	
	void onePagePerDayDrawPage ( QPainter*, bool, int ) ;
	void onePagePerWeekDrawPage ( QPainter*, bool, bool ) ;
	void onePagePerMonthDrawPage ( QPainter*, bool ) ;
	void onePagePerYearDrawPage ( QPainter* ) ;
	void onePagePerTwoYearsDrawPage ( QPainter* ) ;
	
	void twoPagePerDayDrawDay ( QPainter*, bool ) ;
	void twoPagePerDayDrawOtherPage ( QPainter*, bool ) ;
	
	void twoPagePerWeekDrawPage ( QPainter*, bool ) ;
	void twoPagePerWeekDrawOneDay ( QRectF, QDate, QPainter*, bool ) ;
	
	void twoPagePerWeekMoleskineStyleDrawPage ( QPainter*, moleskineType, bool ) ;
	
	void drawMoleVerticalLeft ( QPainter* , QRectF , QDate ) ;
	void drawMoleVerticalRight ( QPainter* , QRectF , QDate ) ;
	void drawMoleHorizontalLeft ( QPainter* , QRectF , QDate ) ;
	void drawMoleHorizontalRight ( QPainter* , QRectF , QDate ) ;
	void drawMoleNotebookLeft ( QPainter* , QRectF , QDate ) ;
	void drawMoleNotebookRight ( QPainter* , QRectF ) ;
	void drawMoleLandscapeLeft ( QPainter* , QRectF , QDate ) ;
	void drawMoleLandscapeRight ( QPainter* , QRectF , QDate ) ;
	void drawMoleLandscapeTop ( QPainter* , QRectF, QString , QDate ) ;
	void drawMoleLandscapeColumn ( QPainter* , QRectF ) ;



	void twoPagePerMonthDrawPage ( QPainter*, bool ) ;
	void twoPagePerMonthDrawLandscapePage ( QPainter*, bool ) ;
	void twoPagePerMonthDrawOneDay ( QRectF, QDate, QPainter*, bool ) ;

	void twoPagePerYearDrawPage ( QPainter*, bool ) ;
	void twoPagePerYearDrawOneDay ( QRectF, QDate, QPainter*, bool ) ;

	void credits ( QPainter* ) ;
	void TBD ( QPainter* ) ;

private:
	QDate today ;
	QDate startDate ;
	QDate stopDate ;
	QDate thisMonth[7][6] ;
	QDate theYear[7][54] ;
	QTime firstAppt ;

	Qt::DayOfWeek weekStart ;
	qreal scale ;
	qreal penWidth ;
	qreal lineSpacing ;
	qreal displayLineSpacing ;
	
	QRectF thePaper ;
	QRectF thePage ; // paper with margins
	QPrinter* printer ;
	QSvgGenerator* gen ;
	
	qreal displayHeight ;
	qreal displayWidth ;
	QColor lineColors[7] ;
	QString titleString ;
	QString svgFileName ;
	int svgFileCount ;

	Qt::Alignment theAlignment ;
	int linesPer ;
	bool itIsInches ;
	QFont theFont ;
	int theStyle ;
	int clockType ; // 0 = none, 1 = 12 hour, 2 = 24 hour
	qreal resolution ;
};

#endif

