#pragma once
#include <QMainWindow>
#include "ui_DetailChangeable.h"
#include "PersonSet.h"
#include "UndoRedo.h"

class DetailChangeable 
	:public QMainWindow
{
	Q_OBJECT
public:
	DetailChangeable(UndoRedo* unRe, PersonSet* set, QWidget *parent = nullptr);
	DetailChangeable(UndoRedo* unRe, Person* psn, QWidget* parent = nullptr);
	~DetailChangeable();
	
	void CalendarSetting(void);
	void PushButtonSettingOfAdd(void);
	void PushButtonSettingOfModify(void);
	void LineEditSetting(void);

private:
	Ui::DetailChangeableClass ui;

	PersonSet* personSet;
	Person* person;
	UndoRedo* undoRedo;
	bool calendarVisible;
};

