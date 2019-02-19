#include "Student.h"
#include <iostream>
#include <string.h>
#include <cstdlib>


Student::Student(int id, char* name, eFaculty faculty)
{
	if(id==defID) /*** ? What if the id happens to be defID ***/
	{
		_id=id;
		defID++;
	}
	else
		_id=id;

	_name=NULL;
	ConstructorSetName(name);
	_faculty=faculty;
}

Student::Student()
{
	_id=defID++;
	_name=NULL;
	ConstructorSetName("NONE");
	_faculty=GENERAL;
}

Student::Student (const Student& other)
{
	_id=other._id;
	ConstructorSetName(other._name);
	_faculty=other._faculty;
}

Student::~Student()
{
	if(NULL!=_name)
		delete [] _name;
}
bool Student::ConstructorSetName(char* other)
{
	if(NULL==other)
		return false;

	char* temp;
	temp = new char[strlen(other)+1];

	if(NULL==temp)
		return false;

	_name=temp;
	strcpy(_name,other);

	return true;
}

bool Student::SetName(char* other)
{
	if(NULL==other)
		return false;

	char* temp;
	temp = new char[strlen(other)+1];

	if(NULL==temp)
		return false;

	if(_name!=NULL)
		delete[]_name;


	_name=temp;
	strcpy(_name,other);

	return true;
}

int Student::getID() const
{
	return _id;
}

char* Student:: getName() const
{
	return _name;
}

Faculty Student:: getFaculty() const
{
	return _faculty;
}

const Student& Student:: operator=(const Student& other)
{
	_id = other._id;
	SetName(other._name);
	_faculty=other._faculty;

	return *this;
}

ostream & operator<<(ostream & out, const Student & stu)
{
		return stu.Show(out);
}

ostream & Student::Show(ostream & out)const
{
	char* sFaculty = NULL;

		switch(_faculty){
			case 0:
				sFaculty = "Engineering";
				break;

			case 1:
				sFaculty = "Medicine";
				break;

			case 2:
				sFaculty = "Humanities";
				break;

			case 3:
				sFaculty = "Management";
				break;

			case 4:
				sFaculty = "General";
				break;

			default:
				break;

		}
		out << "{"<<_id<<", "<<_name<<", "<<sFaculty << "}" ;
		return out;
}
