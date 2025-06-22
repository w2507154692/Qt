#pragma once
#include "deque"
#include "Person.h"

class PersonSet : 
    public std::deque<Person>
{
public:
    PersonSet(void);
    virtual ~PersonSet(void);

    // Overloaded deque::push_back for adding a new Person object at the end of the collection.
    bool push_back(const Person& person);

    // Overloaded deque::push_front for adding a new Person object at the beginning of the collection.
    bool push_front(const Person& person);

    // Overloaded deque::insert for adding a new Person object at the specified position in the collection.
    std::deque<Person>::iterator insert(std::deque<Person>::iterator i, const Person& person = Person());

    // Reads sequentially from the specified file, constructs Person class objects, and adds them to the collection.
    int ReadFromFile(const char filename[]);

    // Writes the Person class objects in the collection sequentially into the specified file.
    int WriteToFile(const char filename[]);
};
