#pragma once
#include <QMainWindow>
#include "ui_DetailChangeable.h"
#include "PersonSet.h"

class DetailChangeable 
	:public QMainWindow
{
	Q_OBJECT
public:
	DetailChangeable(PersonSet* set, QWidget *parent = nullptr);
	~DetailChangeable();
	
	void calendarSetting(void);
	void pushButtonSetting(void);
	void lineEditSetting(void);

private:
	Ui::DetailChangeableClass ui;

	PersonSet* psnSet;
	bool calendarVisible;
};

