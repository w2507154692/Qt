#include "Detail.h"
#include "QLineEdit"


Detail::Detail(Person* psn, QWidget* parent)
	:QMainWindow() {
	ui.setupUi(this);

	ui.lineName->setText(QString::fromLocal8Bit(psn->GetName()));
	ui.lineSex->setText(QString::fromLocal8Bit(psn->GetSex()));
	ui.linePhoneNo->setText(QString::fromLocal8Bit(psn->GetPhoneNo()));
	ui.lineId->setText(QString::fromLocal8Bit(psn->GetId()));
	ui.lineAddress->setText(QString::fromLocal8Bit(psn->GetAddress()));
	ui.lineYear->setText(QString::number(psn->GetBirthday().GetYear()));
	ui.lineMonth->setText(QString::number(psn->GetBirthday().GetMonth()));
	ui.lineDay->setText(QString::number(psn->GetBirthday().GetDay()));
	ui.lineEmployeeNo->setText(QString::fromLocal8Bit(psn->GetEmployeeNo()));
	ui.linePost->setText(QString::fromLocal8Bit(psn->GetPost()));
	ui.lineDepartment->setText(QString::fromLocal8Bit(psn->GetDepartment()));
	ui.lineSalary->setText(QString::number(psn->GetSalary(), 'f', 2));
}

Detail::~Detail() {}