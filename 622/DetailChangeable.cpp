#include "DetailChangeable.h"
#include "QLineEdit"
#include "QComboBox"
#include "QCalendarWidget"
#include "QMessageBox"

void DetailChangeable::calendarSetting(void) {
	calendarVisible = false;
	ui.calendarBirthday->setVisible(calendarVisible);
	ui.calendarBirthday->setMinimumDate(QDate(1900, 1, 1));
	ui.calendarBirthday->setMaximumDate(QDate(9999, 12, 31));

	connect(ui.buttonCalendar, &QPushButton::clicked, [&]() {
		if (calendarVisible) {
			ui.calendarBirthday->setVisible(!calendarVisible);
			ui.buttonCalendar->setText(QString::fromUtf8("选择"));
		}
		else {
			ui.calendarBirthday->setVisible(!calendarVisible);
			ui.buttonCalendar->setText(QString::fromUtf8("关闭"));
		}
		calendarVisible = !calendarVisible;
		});
	connect(ui.calendarBirthday, &QCalendarWidget::clicked, [&](const QDate& date) {
		int year = date.year(), month = date.month(), day = date.day();
		ui.lineYearChangeable->setText(QString::number(year));
		ui.lineMonthChangeable->setText(QString::number(month));
		ui.lineDayChangeable->setText(QString::number(day));
		});
}

void DetailChangeable::pushButtonSetting(void) {
	connect(ui.buttonOK, &QPushButton::clicked, [&]() {
		if (ui.lineNameChangeable->text().isEmpty()) {
			QMessageBox::warning(this, "警告", "姓名不能为空！");
			return;
		}
		if (ui.linePhoneNoChangeable->text().isEmpty()) {
			QMessageBox::warning(this, "警告", "手机号不能为空！");
			return;
		}
		if (ui.lineIdChangeable->text().isEmpty()) {
			QMessageBox::warning(this, "警告", "身份证号不能为空！");
			return;
		}
		if (ui.lineAddressChangeable->text().isEmpty()) {
			QMessageBox::warning(this, "警告", "地址不能为空！");
			return;
		}
		if (ui.lineEmployeeNoChangeable->text().isEmpty()) {
			QMessageBox::warning(this, "警告", "工号不能为空！");
			return;
		}
		if (ui.lineSalaryChangeable->text().isEmpty()) {
			QMessageBox::warning(this, "警告", "薪水不能为空！");
			return;
		}
		if (ui.lineDepartmentChangeable->text().isEmpty()) {
			QMessageBox::warning(this, "警告", "部门不能为空！");
			return;
		}
		if (ui.linePostChangeable->text().isEmpty()) {
			QMessageBox::warning(this, "警告", "职位不能为空！");
			return;
		}

		string id = ui.lineIdChangeable->text().toStdString();
		if (int(id.size()) != 18) {
			QMessageBox::warning(this, "警告", "身份证号不合法！");
			return;
		}
		if (((id[16] - '0') % 2 == 0 && ui.comboSex->currentIndex() == 0) || ((id[16] - '0') % 2 != 0 && ui.comboSex->currentIndex() == 1)) {
			QMessageBox::warning(this, "警告", "身份证号与性别不符！");
			return;
		}

		int year = 1000 * (id[6] - '0') + 100 * (id[7] - '0') + 10 * (id[8] - '0') + id[9] - '0';
		int month = 10 * (id[10] - '0') + id[11] - '0';
		int day = 10 * (id[12] - '0') + id[13] - '0';
		if (year != ui.lineYearChangeable->text().toInt() || month != ui.lineMonthChangeable->text().toInt() || day != ui.lineDayChangeable->text().toInt()) {
			QMessageBox::warning(this, "警告", "身份证号与出生日期不符！");
			return;
		}

		Person person;
		person.SetName(ui.lineNameChangeable->text().toLocal8Bit().toStdString());
		person.SetPhoneNo(ui.linePhoneNoChangeable->text().toLocal8Bit().toStdString());
		person.SetId(ui.lineIdChangeable->text().toLocal8Bit().toStdString());
		person.SetAddress(ui.lineAddressChangeable->text().toLocal8Bit().toStdString());
		person.SetPost(ui.linePostChangeable->text().toLocal8Bit().toStdString());
		person.SetEmployeeNo(ui.lineEmployeeNoChangeable->text().toLocal8Bit().toStdString());
		person.SetSalary(ui.lineSalaryChangeable->text().toDouble());
		person.SetDepartment(ui.lineDepartmentChangeable->text().toLocal8Bit().toStdString());
		person.SetSex(ui.comboSex->currentText().toLocal8Bit().toStdString());
		person.SetBirthday(Date(year, month, day));

		psnSet->push_front(person);
		QMessageBox::information(this, "提示", "添加成功！");
		this->close();
		});

	connect(ui.buttonCancel, &QPushButton::clicked, [=]() {
		this->close();
		});
}

void DetailChangeable::lineEditSetting(void) {
	connect(ui.lineIdChangeable, &QLineEdit::textChanged, [=](const QString& text) {
		string id = text.toStdString();
		if (int(id.size()) == 18) {
			if ((id[16] - '0') % 2 == 0)
				ui.comboSex->setCurrentIndex(1);
			else
				ui.comboSex->setCurrentIndex(0);

			int year = 1000 * (id[6] - '0') + 100 * (id[7] - '0') + 10 * (id[8] - '0') + id[9] - '0';
			int month = 10 * (id[10] - '0') + id[11] - '0';
			int day = 10 * (id[12] - '0') + id[13] - '0';
			ui.lineYearChangeable->setText(QString::number(year));
			ui.lineMonthChangeable->setText(QString::number(month));
			ui.lineDayChangeable->setText(QString::number(day));
		}
		});
}

DetailChangeable::DetailChangeable(PersonSet* set, QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	psnSet = set;

	//CalendarWidget
	calendarSetting();

	//PushButton
	pushButtonSetting();

	//LineEdit
	lineEditSetting();
}

DetailChangeable::~DetailChangeable()
{}

