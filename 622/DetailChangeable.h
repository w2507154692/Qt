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
	DetailChangeable(Person* psn, QWidget* parent = nullptr);
	~DetailChangeable();
	
	void CalendarSetting(void);
	void PushButtonSettingOfAdd(void);
	void PushButtonSettingOfModify(void);
	void LineEditSetting(void);

private:
	Ui::DetailChangeableClass ui;

	PersonSet* personSet;
	Person* person;
	bool calendarVisible;
};

