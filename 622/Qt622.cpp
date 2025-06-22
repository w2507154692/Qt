#include "Qt622.h"
#include "QPushButton"
#include "QMessageBox"
#include "Date.h"
#include "Person.h"
#include "PersonSet.h"

Qt622::Qt622(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    ui.testButton1->setIcon(QIcon("Icon.jpg"));

    connect(ui.testButton1, &QPushButton::clicked, [=]() {
        QMessageBox::information(this, "提示", "按钮被点击了！");
        });

    connect(ui.textReadButton, &QPushButton::clicked, [=]() {
        const QString str = ui.textEdit->toPlainText();
        QMessageBox::information(this, "提示", str);
        });

    connect(ui.textSetButton, &QPushButton::clicked, [=]() {
        ui.textEdit->setText("你好");
        });

    connect(ui.testDate, &QPushButton::clicked, [=]() {
        Date date;
        qDebug() << date.Format();  
        });

    connect(ui.testPerson, &QPushButton::clicked, [=]() {
        Person person;
        qDebug() << person.GetBirthday().GetDay();
        });

    connect(ui.testPersonSet, &QPushButton::clicked, [=]() {
        PersonSet psnset;
        int len = psnset.ReadFromFile("personnel.dat");
        qDebug() << len;
        psnset.WriteToFile("new.dat");
        });
}

Qt622::~Qt622()
{}