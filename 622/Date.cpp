#include "Date.h"
#include "time.h"

Date::Date(void) {
	time_t now = time(NULL);
	struct tm t;
	localtime_s(&t, &now);

	this->year = t.tm_year + 1900;
	this->month = t.tm_mon + 1;
	this->day = t.tm_mday;
}

Date::Date(int y, int m, int d) {
	this->year = y;
	this->month = m;
	this->day = d;
}

Date::~Date(void) {

}

void Date::SetYear(int y) {
	this->year = y;
}

void Date::SetMonth(int m) {
	this->month = m;
}

void Date::SetDay(int d) {
	this->day = d;
}

int Date::GetYear() {
	return this->year;
}

int Date::GetMonth() {
	return this->month;
}

int Date::GetDay() {
	return this->day;
}

Date& Date::operator()(int y, int m, int d) {
	this->year = y;
	this->month = m;
	this->day = d;
	return *this;
}

string Date::Format() {
	string str = to_string(this->year) + "-";
	if (this->month < 10) str += "0";
	str += to_string(this->month) + "-";
	if (this->day < 10) str += "0";
	str += to_string(this->day);
	return str;
}

bool operator==(Date date1, Date date2) {
	if (date1.year != date2.year) return false;
	if (date1.month != date2.month) return false;
	if (date1.day != date2.day) return false;
	return true;
}

bool operator!=(Date date1, Date date2) {
	if (date1.year != date2.year) return true;
	if (date1.month != date2.month) return true;
	if (date1.day != date2.day) return true;
	return false;
}

std::istream& operator>>(std::istream& in, Date& date) {
	in >> date.year >> date.month >> date.day;
	return in;
}

std::ostream& operator<<(std::ostream& out, Date& date) {
	out << date.year << " " <<  date.month << " " << date.day;
	return out;
}
