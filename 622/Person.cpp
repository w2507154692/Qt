#include "Person.h"

Person::Person(void) {
	this->id = "Unknown";
	this->name = "Unknown";
	this->sex = "Unknown";
	this->phoneNo = "Unknown";
	this->address = "Unknown";
	this->birthday = Date();
	this->employeeNo = "Unknown";
	this->department = "Unknown";
	this->post = "Unknown";
	this->salary = 0.0;
}

Person::~Person(void) {

}

void Person::operator()(std::string id, std::string name, std::string sex,
	std::string phoneNo, std::string address, Date& birthday,
	std::string employeeNo, std::string department, std::string post, double salary) {
	this->id = id;
	this->name = name;
	this->sex = sex;
	this->phoneNo = phoneNo;
	this->address = address;
	this->birthday = birthday;
	this->employeeNo = employeeNo;
	this->department = department;
	this->post = post;
	this->salary = salary;
}

bool operator!=(Person person1, Person person2) {
	return person1.id != person2.id;
}

bool operator==(Person person1, Person person2) {
	return person1.id != person2.id;
}


bool operator<(Person person1, Person person2) {
	return person1.id < person2.id;
}

bool operator>(Person person1, Person person2) {
	return person1.id > person2.id;
}

bool operator<=(Person person1, Person person2) {
	return person1.id <= person2.id;
}

bool operator>=(Person person1, Person person2) {
	return person1.id >= person2.id;
}
 
void Person::SetId(std::string Id) {
	this->id = Id;
}

void Person::SetName(std::string Name) {
	this->name = Name;
}

void Person::SetSex(std::string Sex) {
	this->sex = Sex;
}

void Person::SetPhoneNo(std::string PhoneNo) {
	this->phoneNo = PhoneNo;
}

void Person::SetAddress(std::string Address) {
	this->address = Address;
}

void Person::SetBirthday(const Date& Birthday) {
	this->birthday = Birthday;
}

void Person::SetEmployeeNo(std::string EmployeeNo) {
	this->employeeNo = EmployeeNo;
}

void Person::SetDepartment(std::string Department) {
	this->department = Department;
}

void Person::SetPost(std::string Post) {
	this->post = Post;
}

void Person::SetSalary(double Salary) {
	this->salary = Salary;
}

std::string Person::GetId() {
    return this->id;
}

std::string Person::GetName() {
    return this->name;
}

std::string Person::GetSex() {
    return this->sex;
}

std::string Person::GetPhoneNo() {
    return this->phoneNo;
}

std::string Person::GetAddress() {
    return this->address;
}

Date Person::GetBirthday() {
    return this->birthday;
}

std::string Person::GetEmployeeNo() {
    return this->employeeNo;
}

std::string Person::GetDepartment() {
    return this->department;
}

std::string Person::GetPost() {
    return this->post;
}

double Person::GetSalary() {
    return this->salary;
}

std::istream& operator>>(std::istream& in, Person& person) {
    in >> person.id
       >> person.name
       >> person.sex
       >> person.birthday
       >> person.address
       >> person.phoneNo
       >> person.employeeNo
       >> person.department
       >> person.post
       >> person.salary;
    return in;
}

std::ostream& operator<<(std::ostream& out, Person& person) {
	out << person.id << endl
        << person.name << endl
        << person.sex << endl
        << person.birthday << endl
        << person.address << endl
        << person.phoneNo << endl
        << person.employeeNo << endl
        << person.department << endl
        << person.post << endl
        << person.salary;
    return out;
}