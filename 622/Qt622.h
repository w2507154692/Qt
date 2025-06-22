#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Qt622.h"

class Qt622 : public QMainWindow
{
    Q_OBJECT

public:
    Qt622(QWidget *parent = nullptr);
    ~Qt622();

private:
    Ui::Qt622Class ui;
};

