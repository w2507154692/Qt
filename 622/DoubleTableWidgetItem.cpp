#include "DoubleTableWidgetItem.h"

bool DoubleTableWidgetItem::operator<(const QTableWidgetItem& other) const {
	return this->text().toDouble() < other.text().toDouble();
}

bool DoubleTableWidgetItem::operator>(const QTableWidgetItem& other) const{
	return this->text().toDouble() > other.text().toDouble();
}