#ifndef STUDENT_H_
#define STUDENT_H_

#include <iostream>
using namespace std;

enum Faculty {ENGINEERING, MEDICINE, HUMANITIES, MANAGEMENT, GENERAL};
typedef enum Faculty eFaculty;

static int defID = 100;

class Student
{

private:

	int _id;
	char* _name;
	eFaculty _faculty;
	ostream & Show(ostream & out)const;
	bool SetName(char* other);
	bool ConstructorSetName(char* other);

public:

	Student(int id, char *name, eFaculty faculty);
	Student();
	Student (const Student& other);
	~Student();
	int getID() const;
	char* getName() const;
	Faculty getFaculty() const;
	const Student& operator=(const Student& other);
	friend ostream & operator<<(ostream & out, const Student & stu);

};

#endif /* STUDENT_H_ */
