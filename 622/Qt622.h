#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_Qt622.h"
#include "PersonSet.h"

class Qt622 : public QMainWindow
{
    Q_OBJECT
public:
    Qt622(PersonSet* set, QWidget* parent = nullptr);
    ~Qt622();

public slots:
    void PersonTableSetting(void);
    void StatusBarSetting(void);
    void ToolBarSetting(void);
    void MenuBarSetting(void);
    void SearchSetting(void);
    void RefreshTable(PersonSet* psnSet);
    void SortPersonInfo(void);
    void SearchPersonInfo(QString key);
    void OnRightClickShowMenu(QPoint);
    void OnDisplaySelectedPerson(QString m_pID);
    void OnDisplaySelectedPerson(QTableWidgetItem* item);
    void OnDeletePersonAction(void);
    void OnUpdatePersonAction(QString m_pID);
    void OnAddPersonAction(void);

public:
    PersonSet* m_pPersonSet;

private:
    Ui::Qt622Class ui;
};

