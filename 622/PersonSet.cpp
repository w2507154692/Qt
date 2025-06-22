#include "PersonSet.h"
#include <fstream>
#include "iostream"

PersonSet::PersonSet(void) :deque() {

}

PersonSet::~PersonSet(void) {

}

bool PersonSet::push_back(const Person& person) {
	for (auto it = begin(); it != end(); it++)
		if (person == *it)
			return false;
	std::deque<Person>::push_back(person);
	return true;
}

bool PersonSet::push_front(const Person& person) {
	for (auto it = begin(); it != end(); it++)
		if (person == *it)
			return false;
	std::deque<Person>::push_front(person);
	return true;
}

std::deque<Person>::iterator PersonSet::insert(std::deque<Person>::iterator i, const Person& person) {
	return std::deque<Person>::insert(i, person);
}

int PersonSet::ReadFromFile(const char filename[]) {
	fstream fin(filename, ios::in);
	if (!fin) return 0;

	Person person;
	int i = 0;
	while (fin >> person) {
		std::deque<Person>::push_back(person);
		i++;
	}

	fin.close();
	return i;
}

int PersonSet::WriteToFile(const char filename[]) {
	fstream fout(filename, ios::out);
	if (!fout) return 0;

	int i = 0;
	for (auto it = begin(); it != end(); it++) {
		fout << *it << endl;
		i++;
	}

	fout.close();
	return i;
}
