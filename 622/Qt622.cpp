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
#include "QFile"
#include "QTextStream"
#include "QFileDialog"
#include "fstream"

//菜单设置
void Qt622::MenuBarSetting(void) {
    QMenuBar* menuBar = ui.menuBar;
    QMenu* fileMenu = menuBar->addMenu("文件");
    QAction* newAction = fileMenu->addAction("新建");
    QAction* openAction = fileMenu->addAction("打开");
    QAction* saveAction = fileMenu->addAction("保存");
    fileMenu->addSeparator();
    QAction* closeAction = fileMenu->addAction("关闭");

    //new open save close
    connect(newAction, &QAction::triggered, this, &Qt622::OnNewFileAction);
    connect(openAction, &QAction::triggered, this, &Qt622::OnOpenFileAction);
    connect(saveAction, &QAction::triggered, this, &Qt622::SaveOrNot);
    connect(closeAction, &QAction::triggered, this, [=]() {
        this->close();
        });
}

//工具栏设置
void Qt622::ToolBarSetting(void) {
    ui.mainToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    QAction* addToolAction = new QAction(QIcon(":/new/prefix1/icon/add.png"), "添加", this);
    QAction* deleteToolAction = new QAction(QIcon(":/new/prefix1/icon/delete.png"), "删除", this);
    QAction* viewToolAction = new QAction(QIcon(":/new/prefix1/icon/view.png"), "查看", this);
    QAction* modifyToolAction = new QAction(QIcon(":/new/prefix1/icon/modify.png"), "修改", this);
    undoRedo.undoAction = new QAction(QIcon(":/new/prefix1/icon/undo.png"), "撤销", this);
    undoRedo.redoAction = new QAction(QIcon(":/new/prefix1/icon/redo.png"), "重做", this);
    
    ui.mainToolBar->addAction(addToolAction);
    ui.mainToolBar->addAction(deleteToolAction);
    ui.mainToolBar->addAction(viewToolAction);
    ui.mainToolBar->addAction(modifyToolAction);
    ui.mainToolBar->addAction(undoRedo.undoAction);
    ui.mainToolBar->addAction(undoRedo.redoAction);
    
    //add,delete,view,modify
    connect(addToolAction, &QAction::triggered, this, &Qt622::OnAddPersonAction);
    connect(deleteToolAction, &QAction::triggered, this, &Qt622::OnDeletePersonAction);
    connect(viewToolAction, &QAction::triggered, this, [=]() {
        QList<QTableWidgetItem*>selectedItems = ui.personTable->selectedItems();
        if (selectedItems.isEmpty())
            QMessageBox::warning(this, "警告", "未选择成员！");
        else
            OnDisplaySelectedPerson(selectedItems.at(0));
        });
    connect(modifyToolAction, &QAction::triggered, this, [=]() {
        QList<QTableWidgetItem*>selectedItems = ui.personTable->selectedItems(); //获得选中项
        if (selectedItems.isEmpty())
            QMessageBox::warning(this, "警告", "未选择成员！");
        else {
            QString id = selectedItems.at(0)[0].text(); //获得选中项的第一行第一列
            OnUpdatePersonAction(id);
        }
        });

    //undoRedo
    undoRedo.undoAction->setEnabled(false);
    undoRedo.redoAction->setEnabled(false);
    connect(undoRedo.undoAction, &QAction::triggered, this, [=]() {
        undoRedo.UndoAction();
        RefreshTable(m_pPersonSet);
        });
    connect(undoRedo.redoAction, &QAction::triggered, this, [=]() {
        undoRedo.RedoAction();
        RefreshTable(m_pPersonSet);
        });
}

//浮动菜单设置
void Qt622::OnRightClickShowMenuTable(QPoint qp) {
    QTableWidgetItem* item = ui.personTable->itemAt(qp);

    if (item != nullptr) {
        QMenu* menu = new QMenu(this);
        QAction* addAction = new QAction(QIcon(":/new/prefix1/add.png"), "添加", this);
        QAction* deleteAction = new QAction(QIcon(":/new/prefix1/delete.png"), "删除", this);
        QAction* viewAction = new QAction(QIcon(":/new/prefix1/view.png"), "查看", this);
        QAction* modifyAction = new QAction(QIcon(":/new/prefix1/modify.png"), "修改", this);

        menu->addAction(addAction);
        menu->addAction(deleteAction);
        menu->addAction(viewAction);
        menu->addAction(modifyAction);

        //add,delete,view,modify
        connect(addAction, &QAction::triggered, this, &Qt622::OnAddPersonAction);
        connect(deleteAction, &QAction::triggered, this, &Qt622::OnDeletePersonAction);
        connect(viewAction, &QAction::triggered, this, [=]() {
            QList<QTableWidgetItem*>selectedItems = ui.personTable->selectedItems();
            if (selectedItems.isEmpty())
                QMessageBox::warning(this, "警告", "未选择成员！");
            else
                OnDisplaySelectedPerson(selectedItems.at(0));
            });
        connect(modifyAction, &QAction::triggered, this, [=]() {
            QList<QTableWidgetItem*>selectedItems = ui.personTable->selectedItems(); //获得选中项
            if (selectedItems.isEmpty())
                QMessageBox::warning(this, "警告", "未选择成员！");
            else {
                QString id = selectedItems.at(0)[0].text(); //获得选中项的第一行第一列
                OnUpdatePersonAction(id);
            }
            });

        menu->popup(ui.personTable->viewport()->mapToGlobal(qp));
    }
}

void Qt622::OnRightClickShowMenuWindow(QPoint qp) {
    QTableWidgetItem* item = ui.personTable->itemAt(qp);

    QMenu* menu = new QMenu(this);
    QAction* newAction = new QAction("新建", this);
    QAction* openAction = new QAction("打开", this);
    QAction* saveAction = new QAction("保存", this);

    menu->addAction(newAction);
    menu->addAction(openAction);
    menu->addAction(saveAction);

    //new open save
    connect(newAction, &QAction::triggered, this, &Qt622::OnNewFileAction);
    connect(openAction, &QAction::triggered, this, &Qt622::OnOpenFileAction);
    connect(saveAction, &QAction::triggered, this, &Qt622::SaveOrNot);

    menu->popup(this->mapToGlobal(qp));
}

//底部状态栏设置
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

//点击删除按钮
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

    operation op;
    op.type = 2;

    for (int i = 0; i < selectedItems.size() / 5; i++) {
        row = selectedItems.at(i * 5)->row(); //取出选择的第i行
        QTableWidgetItem* firstItem = ui.personTable->item(row, 0); //取出第i行的第一项（身份证号）
        m_PID = firstItem->text();
        person.SetId(m_PID.toStdString()); //用于查找的对象，只有一个身份证号信息
        it = std::find(m_pPersonSet->begin(), m_pPersonSet->end(), person);

        if (it != m_pPersonSet->end()) {
            //undoRedo
            op.personList.push_back(*it);
            op.indexList.push_back(it - m_pPersonSet->begin());

            m_pPersonSet->erase(it);
        }
    }
    undoRedo.RecordOp(op);
    RefreshTable(m_pPersonSet);
}

//排序设置
void Qt622::SortPersonInfo(void) {
    ui.personTable->setSortingEnabled(true);
}

//搜索设置
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
        else
            SearchPersonInfo(lineSearch->text());
        });
    connect(lineSearch, &QLineEdit::returnPressed, this, [=]() {
        SearchPersonInfo(lineSearch->text());
        });
    connect(buttonSearch, &QPushButton::pressed, this, [=]() {
        SearchPersonInfo(lineSearch->text());
        });

}

//搜索方法
void Qt622::SearchPersonInfo(QString key) {
    QTableWidget* table = ui.personTable;
    for (int row = 0; row < int(m_pPersonSet->size()); row++) //将所有行隐藏
        table->setRowHidden(row, true);
    
    QList<QTableWidgetItem*> foundItems = table->findItems(key, Qt::MatchContains); //模糊匹配
    for (int row = 0; row < foundItems.size(); row++) //将匹配到的表项设置为不隐藏
        table->setRowHidden(foundItems.at(row)->row(), false);
}

//详细信息
void Qt622::OnDisplaySelectedPerson(QString m_pId) {
    Person psn;
    psn.SetId(m_pId.toStdString());
    PersonSet::iterator it = std::find(m_pPersonSet->begin(), m_pPersonSet->end(), psn);
    psn = *it;

    Detail* detail = new Detail(&psn, this);
    detail->setAttribute(Qt::WA_DeleteOnClose); // 关闭时自动释放
    detail->show();
}

//详细信息
void Qt622::OnDisplaySelectedPerson(QTableWidgetItem* item) {
    OnDisplaySelectedPerson(item[0].text());
}

//点击添加按钮
void Qt622::OnAddPersonAction(void) {
    DetailChangeable* detailChangeable = new DetailChangeable(&undoRedo, m_pPersonSet, this);
    detailChangeable->setAttribute(Qt::WA_DeleteOnClose); //关闭时自动释放

    //检测到窗口关闭时才调用Refresh函数，防止过早调用，刷新过早
    connect(detailChangeable, &QObject::destroyed, this, [=]() { 
        RefreshTable(m_pPersonSet);
        });

    detailChangeable->show(); 
}

//点击修改按钮
void Qt622::OnUpdatePersonAction(QString m_pID) {
    Person person;
    person.SetId(m_pID.toStdString());
    PersonSet::iterator it = std::find(m_pPersonSet->begin(), m_pPersonSet->end(), person); //找到Id对应的Person

    DetailChangeable* detailChangeable = new DetailChangeable(&undoRedo, &(*it), this);
    detailChangeable->setAttribute(Qt::WA_DeleteOnClose); //关闭时自动释放

    //检测到窗口关闭时才调用Refresh函数，防止过早调用，刷新过早
    connect(detailChangeable, &QObject::destroyed, this, [=]() {
        RefreshTable(m_pPersonSet);
        });

    detailChangeable->show();
}

//保存
void Qt622::SaveOrNot(void) {
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(nullptr, "保存文件", "是否保存？", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::No)
        return;
    else {
        ofstream fout(currentFileName, ios::out);
        if (fout) {
            m_pPersonSet->WriteToFile(currentFileName);
            QMessageBox::information(this, "提示", "保存成功！");
        }
        else
            QMessageBox::warning(this, "警告", "保存失败！");
    }

}

//点击打开文件
void Qt622::OnOpenFileAction(void) {
    if (!undoRedo.undoStack.empty())
        SaveOrNot();

    QString fileNameQString = QFileDialog::getOpenFileName(this, "选择文件", "", "数据文件 (*.dat);;所有文件 (*.*)");
    char fileName[50];
    strcpy_s(fileName, fileNameQString.toStdString().c_str());
    
    ifstream fin(fileName, ios::in);
    if (fin) {
        QMessageBox::information(this, "提示", "文件打开成功！");
        strcpy_s(currentFileName, fileName);
        m_pPersonSet->clear();
        m_pPersonSet->ReadFromFile(currentFileName);

        //UndoRedo
        undoRedo.undoAction->setEnabled(false);
        undoRedo.undoAction->setEnabled(false);
        while (!undoRedo.undoStack.empty()) undoRedo.undoStack.pop();
        while (!undoRedo.redoStack.empty()) undoRedo.redoStack.pop();
    }
    else
        QMessageBox::warning(this, "警告", "文件打开失败！");

    RefreshTable(m_pPersonSet);
}

//点击新建文件
void Qt622::OnNewFileAction(void) {
    if (!undoRedo.undoStack.empty())
        SaveOrNot();

    QString fileNameQString = QFileDialog::getSaveFileName(this, "新建文件", "", "数据文件 (*.dat);;所有文件 (*.*)");
    char fileName[50];
    strcpy_s(fileName, fileNameQString.toStdString().c_str());

    ofstream fout(fileName, ios::out);
    if (fout) {
        QMessageBox::information(this, "提示", "新建文件成功！");
        strcpy_s(currentFileName, fileName);
        m_pPersonSet->clear();
        m_pPersonSet->WriteToFile(currentFileName);
        RefreshTable(m_pPersonSet);

        //UndoRedo
        undoRedo.undoAction->setEnabled(false);
        undoRedo.undoAction->setEnabled(false);
        while (!undoRedo.undoStack.empty()) undoRedo.undoStack.pop();
        while (!undoRedo.redoStack.empty()) undoRedo.redoStack.pop();
    }
    else
        QMessageBox::warning(this, "警告", "新建文件失败！");
}

//加载默认文件
void Qt622::LoadFile(void) {
    fstream fin(currentFileName);
    if (fin) {
        m_pPersonSet->ReadFromFile(currentFileName);
        QMessageBox::information(this, "提示", "文件读取成功！");
    }
    else
        QMessageBox::warning(this, "警告", "文件读取失败！请新建或打开文件。");
}

//刷新表格
void Qt622::RefreshTable(PersonSet* psnSet) {
    QTableWidget* table = ui.personTable;

    //取消排序
    table->setSortingEnabled(false);

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

    //激活排序
    table->setSortingEnabled(true);

    //取消搜索状态
    ui.checkSearch->setChecked(false);
}

//表格设置
void Qt622::PersonTableSetting(void) {
    //格式
    QTableWidget* table = ui.personTable;
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setColumnCount(5);
    table->setHorizontalHeaderLabels(QStringList() << "身份证" << "姓名" << "性别" << "出生日期" << "薪水");

    //外观
    QFont font = table->horizontalHeader()->font();
    font.setBold(true); //表头加粗
    table->horizontalHeader()->setFont(font);
    for (int i = 0; i < table->columnCount(); i++) {
        int width = table->columnWidth(i);
        table->setColumnWidth(i, width + 50);
    }
    QFile styleFile(":/new/prefix1/QTableWidgetStyle.qss");
    if (styleFile.open(QFile::ReadOnly)) {
        QString styleSheet = QLatin1String(styleFile.readAll());
        ui.personTable->setStyleSheet(styleSheet);  // 只应用于personTable
        // 如果要应用到整个窗口，改为 this->setStyleSheet(styleSheet);
        styleFile.close();
    }

    //浮动菜单
    table->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(table, &QTableWidget::customContextMenuRequested, this, &Qt622::OnRightClickShowMenuTable);
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, &QMainWindow::customContextMenuRequested, this, &Qt622::OnRightClickShowMenuWindow);

    //刷新表格
    RefreshTable(m_pPersonSet);
    //设置排序属性
    SortPersonInfo();
    //设置搜索属性
    SearchSetting();
}

//构造函数
Qt622::Qt622(const char* fileName, PersonSet* set, QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    m_pPersonSet = set;
    undoRedo.set = set;
    strcpy_s(currentFileName, fileName);

    QFile styleFile(":/new/prefix1/QMainWindowStyle.qss");
    if (styleFile.open(QFile::ReadOnly)) {
        QString styleSheet = QLatin1String(styleFile.readAll());
        this->setStyleSheet(styleSheet);
        styleFile.close();
    }

    LoadFile();
    MenuBarSetting();
    ToolBarSetting();
    StatusBarSetting();
    PersonTableSetting();
}
    
Qt622::~Qt622() {
    if(!undoRedo.undoStack.empty())
        SaveOrNot();
}