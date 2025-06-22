#pragma once
#include "Date.h"

class Person
{
public:
    // Constructor
    Person(void);

    // Destructor
    virtual ~Person(void);

    // Overloaded operator() for setting properties of Person object
    void operator()(std::string id, std::string name, std::string sex,
        std::string phoneNo, std::string address, Date& birthday,
        std::string employeeNo, std::string department, std::string post, double salary);

    // Overloaded comparison operators for comparison operations of Person objects
    friend bool operator!=(Person person1, Person person2);
    friend bool operator==(Person person1, Person person2);
    friend bool operator<(Person person1, Person person2);
    friend bool operator>(Person person1, Person person2);
    friend bool operator<=(Person person1, Person person2);
    friend bool operator>=(Person person1, Person person2);

    // Property setting operations
    void SetId(std::string Id);
    void SetName(std::string Name);
    void SetSex(std::string Sex);
    void SetPhoneNo(std::string PhoneNo);
    void SetAddress(std::string Address);
    void SetBirthday(const Date& Birthday);
    void SetEmployeeNo(std::string EmployeeNo);
    void SetDepartment(std::string Department);
    void SetPost(std::string Post);
    void SetSalary(double Salary);

    // Property getting operations
    std::string GetId();
    std::string GetName();
    std::string GetSex();
    std::string GetPhoneNo();
    std::string GetAddress();
    Date GetBirthday();
    std::string GetEmployeeNo();
    std::string GetDepartment();
    std::string GetPost();
    double GetSalary();

    // Overloaded standard input operator >> and operator << for I/O operations of Person object
    friend std::istream& operator>>(std::istream& in, Person& person);
    friend std::ostream& operator<<(std::ostream& out, Person& person);

protected:
    std::string id;          // ID number
    std::string name;        // Name
    std::string sex;         // Sex
    std::string phoneNo;     // Phone number
    std::string address;     // Home address
    Date birthday;           // Date of birth
    std::string employeeNo;  // Employee number
    std::string department;  // Department
    std::string post;        // Position
    double salary;           // Salary
};
