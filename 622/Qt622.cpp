#include "Qt622.h"
#include "QMessageBox"
#include "QTableWidget"
#include "QMenuBar"
#include "QMenu"
#include "QAction"
#include "QLabel"
#include "QTimer"
#include "QDateTime"
#include "Date.h"
#include "QLineEdit"
#include "QCheckBox"
#include "Person.h"
#include "PersonSet.h"
#include "Detail.h"
#include "DetailChangeable.h"
#include "DoubleTableWidgetItem.h"

void Qt622::MenuBarSetting(void) {
    QMenuBar* menuBar = ui.menuBar;
    QMenu* fileMenu = menuBar->addMenu("文件");
    QAction* newAction = fileMenu->addAction("新建");
    QAction* openAction = fileMenu->addAction("打开");
    fileMenu->addSeparator();
    QAction* closeAction = fileMenu->addAction("关闭");
}

void Qt622::ToolBarSetting(void) {
    ui.mainToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    QAction* addToolAction = new QAction(QIcon(":/new/prefix1/icon/add.png"), "添加", this);
    QAction* deleteToolAction = new QAction(QIcon(":/new/prefix1/icon/delete.png"), "删除", this);
    QAction* viewToolAction = new QAction(QIcon(":/new/prefix1/icon/view.png"), "查看", this);
    QAction* modifyToolAction = new QAction(QIcon(":/new/prefix1/icon/modify.png"), "修改", this);
    
    ui.mainToolBar->addAction(addToolAction);
    ui.mainToolBar->addAction(deleteToolAction);
    ui.mainToolBar->addAction(viewToolAction);
    ui.mainToolBar->addAction(modifyToolAction);
    
    connect(addToolAction, &QAction::triggered, this, &Qt622::OnAddPersonAction);
    connect(deleteToolAction, &QAction::triggered, this, &Qt622::OnDeletePersonAction);
    connect(viewToolAction, &QAction::triggered, this, [=]() {
        QList<QTableWidgetItem*>selectedItems = ui.personTable->selectedItems();
        if (selectedItems.isEmpty())
            QMessageBox::warning(this, "警告", "未选择成员！");
        else
            OnDisplaySelectedPerson(selectedItems.at(0));
        });
    connect(modifyToolAction, &QAction::triggered, [=]() {
        QMessageBox::information(this, "提示", "修改成员信息！");
        });
}

void Qt622::StatusBarSetting(void) {
    ui.statusBar->addPermanentWidget(new QLabel("首都师范大学", this));
    QLabel* timeLabel = new QLabel;
    ui.statusBar->addWidget(timeLabel);
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [timeLabel]() {
        QDateTime dateTime = QDateTime::currentDateTime();
        timeLabel->setText(dateTime.toString("yyyy-MM-dd hh:mm:ss"));
        });
    timer->start(1000);
}

void Qt622::OnDeletePersonAction(void) {
    QList<QTableWidgetItem*> selectedItems = ui.personTable->selectedItems();
    QString m_PID;
    if (!selectedItems.isEmpty()) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(nullptr, "删除该成员", "确定删除？", QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::No)
            return;
    }
    else {
        QMessageBox::warning(this, "警告", "未选择成员！");
        return;
    }

    Person person;
    PersonSet::iterator it;
    int row;

    for (int i = 0; i < selectedItems.size(); i++) {
        row = selectedItems.at(i)->row();
        QTableWidgetItem* firstItem = ui.personTable->item(row, 0);
        m_PID = firstItem->text();
        person.SetId(m_PID.toStdString());
        it = std::find(m_pPersonSet->begin(), m_pPersonSet->end(), person);
        if (it != m_pPersonSet->end())
            m_pPersonSet->erase(it);
    }
    RefreshTable(m_pPersonSet);
}

void Qt622::SortPersonInfo(void) {
    ui.personTable->setSortingEnabled(true);
}

void Qt622::SearchSetting(void) {
    QLineEdit* lineSearch = ui.lineSearch;
    QPushButton* buttonSearch = ui.buttonSearch;
    QCheckBox* checkSearch = ui.checkSearch;

    lineSearch->setEnabled(false);
    buttonSearch->setEnabled(false);
   
    connect(checkSearch, &QCheckBox::stateChanged, this, [=](int state) {
        bool enabled = checkSearch->isChecked();
        lineSearch->setEnabled(enabled);
        buttonSearch->setEnabled(enabled);

        if (!checkSearch->isChecked()) {
            for (int row = 0; row < int(m_pPersonSet->size()); row++)
                ui.personTable->setRowHidden(row, false);
        }
        });
    connect(lineSearch, &QLineEdit::returnPressed, this, [=]() {
        SearchPersonInfo(lineSearch->text());
        });
    connect(buttonSearch, &QPushButton::pressed, this, [=]() {
        SearchPersonInfo(lineSearch->text());
        });

}

void Qt622::SearchPersonInfo(QString key) {
    QTableWidget* table = ui.personTable;
    for (int row = 0; row < int(m_pPersonSet->size()); row++) //将所有行隐藏
        table->setRowHidden(row, true);
    
    QList<QTableWidgetItem*> foundItems = table->findItems(key, Qt::MatchContains); //模糊匹配
    for (int row = 0; row < foundItems.size(); row++) //将匹配到的表项设置为不隐藏
        table->setRowHidden(foundItems.at(row)->row(), false);
}

void Qt622::OnDisplaySelectedPerson(QString m_pId) {
    Person psn;
    psn.SetId(m_pId.toStdString());
    PersonSet::iterator it = std::find(m_pPersonSet->begin(), m_pPersonSet->end(), psn);
    psn = *it;

    Detail* detail = new Detail(&psn, this);
    detail->setAttribute(Qt::WA_DeleteOnClose); // 关闭时自动释放
    detail->show();
}

void Qt622::OnDisplaySelectedPerson(QTableWidgetItem* item) {
    OnDisplaySelectedPerson(item[0].text());
}

void Qt622::OnAddPersonAction(void) {
    DetailChangeable* detailChangeable = new DetailChangeable(m_pPersonSet, this);
    detailChangeable->setAttribute(Qt::WA_DeleteOnClose); // 关闭时自动释放

    connect(detailChangeable, &QObject::destroyed, this, [=]() {
        RefreshTable(m_pPersonSet);
        });

    detailChangeable->show(); 
}

void Qt622::OnRightClickShowMenu(QPoint qp) {}
void Qt622::OnUpdatePersonAction(QString m_pID) {}

void Qt622::RefreshTable(PersonSet* psnSet) {
    QTableWidget* table = ui.personTable;
    int len = psnSet->size();
    table->setRowCount(len);
    auto it = psnSet->begin();
    for (int row = 0; row < len && it != psnSet->end(); row++, it++) {
        table->setItem(row, 0, new QTableWidgetItem(QString::fromLocal8Bit(it->GetId())));
        table->setItem(row, 1, new QTableWidgetItem(QString::fromLocal8Bit(it->GetName())));
        table->setItem(row, 2, new QTableWidgetItem(QString::fromLocal8Bit(it->GetSex())));
        table->setItem(row, 3, new QTableWidgetItem(QString::fromLocal8Bit((it->GetBirthday()).Format())));
        table->setItem(row, 4, new DoubleTableWidgetItem(QString::number(it->GetSalary(), 'f', 2)));
    }
}

void Qt622::PersonTableSetting(void) {
    QTableWidget* table = ui.personTable;
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setColumnCount(5);
    table->setHorizontalHeaderLabels(QStringList() << "身份证" << "姓名" << "性别" << "出生日期" << "薪水");

    QFont font = table->horizontalHeader()->font();
    font.setBold(true); //表头加粗
    table->horizontalHeader()->setFont(font);
    for (int i = 0; i < table->columnCount(); i++) {
        int width = table->columnWidth(i);
        table->setColumnWidth(i, width + 50);
    }

    RefreshTable(m_pPersonSet); //刷新表格
    SortPersonInfo(); //设置排序属性
    SearchSetting(); //设置搜索属性
}


Qt622::Qt622(PersonSet* set, QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    m_pPersonSet = set;

    MenuBarSetting();
    ToolBarSetting();
    StatusBarSetting();
    PersonTableSetting();
}
    
Qt622::~Qt622() {}