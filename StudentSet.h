#ifndef STUDENTSET_H_
#define STUDENTSET_H_

#include <iostream>
#include <string.h>
#include <cstdlib>
#include "Student.h"

using namespace std;

class StudentSet {
private:
	static int _setSize;
	static StudentSet**_setArray;
	int position;
	int _size;
	Student** _array;

	void UniqueStudents(const Student stuArray [], int& size);
	ostream & Show(ostream & out)const;
	bool Contains(const Student& other) const;
	void AddSet();
	void deleteSet();

public:
	StudentSet(); //empty constructor
	StudentSet(Student stuArray [],int size);
	StudentSet (const StudentSet& other);
	~StudentSet();

	StudentSet& operator=(const StudentSet& other);
	StudentSet operator+(const StudentSet& other) const;
	StudentSet& operator+=(const StudentSet& other);
	StudentSet operator/(const StudentSet& other) const;
	StudentSet&  operator/=(const StudentSet& other);
	StudentSet operator-(const StudentSet& other) const;
	StudentSet&  operator-=(const StudentSet& other);

	bool operator==(const StudentSet& other) const;
	bool operator!=(const StudentSet& other) const;

	Student& operator[](const int index);
	const Student& operator[](const int index)const;

	int operator+() const;
	int getSize() const; //why public

	friend ostream & operator<<(ostream & out, const StudentSet & stu);
	static void printAll();
};

#endif /* STUDENTSET_H_ */
