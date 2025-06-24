#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_Detail.h"
#include "PersonSet.h"

class Detail
	:public QMainWindow
{
	Q_OBJECT
public:
	Detail(Person* psn, QWidget* parent = nullptr);
	~Detail();

private:
	Ui::DetailClass ui;
};