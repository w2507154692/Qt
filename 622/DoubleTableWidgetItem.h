#pragma once
#include "QTableWidgetItem"
class DoubleTableWidgetItem :
    public QTableWidgetItem
{
public:
    using QTableWidgetItem::QTableWidgetItem;
    bool operator<(const QTableWidgetItem& other) const override;
    bool operator>(const QTableWidgetItem& other) const;
};

