#include "StudentSet.h"
#include <iostream>
#define SUCCESSFUL_ALOCCATION(var) if(NULL==var) {cout << "Failed to allocate memory! \n"; exit(1);}

int StudentSet:: _setSize=0;
StudentSet** StudentSet:: _setArray=NULL;

StudentSet::StudentSet()
{
	_array=NULL;
	_size=0;
	AddSet();
}

StudentSet::StudentSet(Student stuArray [],int size)
{
	int& r_size=size;
	_array=NULL;
	_array = UniqueStudents(stuArray, r_size); //Here we allocate memory on the heap
	_size = r_size; //free index will also contain the numbers of unique IDs
	AddSet();

}

StudentSet::StudentSet (const StudentSet& other)
{

	_array=NULL;
	_size=other._size;

	Student tmp_studentArray[_size];

	int i;
	for (i = 0; i <_size; i++)
		tmp_studentArray[i] =(*(other._array[i]));

	Student** studentHeapArray = new Student*[_size];
	SUCCESSFUL_ALOCCATION(studentHeapArray);

	for (i = 0; i <_size; i++)
		studentHeapArray[i]= new Student(tmp_studentArray[i]);

	_array=studentHeapArray;

	AddSet();
}

void StudentSet::AddSet()
{

	if(_setSize==0)
	{
		_setArray = new StudentSet*[1];
		SUCCESSFUL_ALOCCATION(_setArray);
		(_setArray[0]) = this;
		_setSize++;
	}
	else
	{
		StudentSet** studentHeapArray = new StudentSet*[_setSize+1];
		SUCCESSFUL_ALOCCATION(studentHeapArray);
		int i;
		for (i = 0; i <_setSize; i++)
			studentHeapArray[i] = _setArray[i];

		delete [] _setArray;
		_setArray= NULL;

		(studentHeapArray[_setSize])= this;
		_setSize++;
		_setArray=studentHeapArray;
	}
}

void StudentSet::deleteSet(const StudentSet& other)
{
	StudentSet** studentHeapArray = new StudentSet*[_setSize-1];
	SUCCESSFUL_ALOCCATION(studentHeapArray);
	int i,freeIndex=0;
	for (i = 0; i <_setSize; i++)
		if(*(_setArray[i])!=*this) //if the set at setArray[i] doesn't equal the one we're destroying, add it
		{
			studentHeapArray[freeIndex] = _setArray[i];
			freeIndex++;
		}

	delete [] _setArray;
	_setArray= NULL;
	_setSize--;
	_setArray = studentHeapArray;
}

void StudentSet::printAll()
{
	cout << _setSize << endl;
	int i;
	for (i = 0; i < _setSize; i++)
		cout << *(_setArray[i]) << endl ;
}

StudentSet::~StudentSet()
{

	deleteSet(*this); //remove the given set from setArray

	if(NULL!=_array)
		delete[]_array;

}

Student** StudentSet:: UniqueStudents(const Student stuArray [], int& size)
{

	Student studentUniqueID [size];

	int i,j,freeIndex=0;
	bool contains;

	for (i = 0; i < size; i++)
	{
		contains = false;
		for (j = 0; j < size; j++)
		{
			if(stuArray[i].getID()==studentUniqueID[j].getID())
			{
				contains=true;
				continue;
			}
		}
		if(!contains)
		{
			studentUniqueID[freeIndex]=stuArray[i];
			freeIndex++;
		}
	}

	size=freeIndex;

	Student** studentHeapArray = new Student*[freeIndex];

	SUCCESSFUL_ALOCCATION(studentHeapArray);

	for (i = 0; i <freeIndex; i++)
		studentHeapArray[i]= new Student(studentUniqueID[i]);

	return studentHeapArray;
}

ostream & operator<<(ostream & out, const StudentSet & stu)
{
		return stu.Show(out);
}

ostream & StudentSet::Show(ostream & out)const
{

	if(_size!=0)
	{
		out << "{" << _size << ",";
		int i;
		for (i = 0; i < _size; i++)
		{
			out << *_array[i];
			if(i!=_size-1)
				cout<<",";
		}
			out << "}";
	}
	else
	{
		out<<"{0}";
	}

	return out;
}

StudentSet& StudentSet::operator=(const StudentSet& other)
{
	int i;
	bool contains = false;
	for (i = 0; i < _setSize && !contains; i++) //we'll check if the left operand is already in setArray:
		contains = *(_setArray[i]) == other;

	if(NULL!=_array)
		delete[]_array;

	_array=NULL;
	_size=other._size;

	Student tmp[_size];

	for (i = 0; i <_size; i++)
		tmp[i] =(*(other._array[i]));

	Student** tmp2 = new Student*[_size];
	SUCCESSFUL_ALOCCATION(tmp2);

	for (i = 0; i <_size; i++)
		tmp2[i]= new Student(tmp[i]);

	_array=tmp2;
	if(!contains)
	{
		_setSize++;
		AddSet();
	}
	return *this;
}

StudentSet StudentSet::operator+(const StudentSet& other) const
{
	int i,unique=0;
	for (i = 0; i < other._size; i++)
		if(!(Contains(other[i])))
			unique++; //the number of unique students


	Student tmp [unique+_size];

	for (i = 0; i < _size; i++)
		tmp[i] = (*this)[i];

	int freeIndex = _size;

	for (i = 0; i < other._size; i++)
		if(!(Contains(other[i])))
		{
			tmp[freeIndex] = other[i];
			freeIndex++;
		}
	StudentSet t_StudentSet(tmp,freeIndex);
	return t_StudentSet;
}

StudentSet& StudentSet:: operator+=(const StudentSet& other)
{
	*this =  ((*this + other));
	return *this;
}

StudentSet StudentSet:: operator/(const StudentSet& other) const
{

	int i,intersect=0;
	for (i = 0; i < other._size; i++)
		if(Contains(*(other._array[i])))
			intersect++; // the number of mutual students

	Student tmp [intersect];
	int freeIndex=0;
	for (i = 0; i < other._size; i++)
		if(Contains(*(other._array[i])))
		{
			tmp[freeIndex]=*(other._array[i]);
			freeIndex++;
		}

	StudentSet t_StudentSet(tmp,(freeIndex));
	return t_StudentSet;
}

StudentSet&  StudentSet:: operator/=(const StudentSet& other)
{
	*this=((*this / other));
	return *this;
}

StudentSet StudentSet:: operator-(const StudentSet& other) const
{
	int i,intersect=0;
	for (i = 0; i < _size; i++)
		if(!(other.Contains(*(_array[i]))))
			intersect++; //the number of mutual students

	Student tmp [intersect];

	int freeIndex=0;
	for (i = 0; i < _size; i++)
		if(!(other.Contains(*(_array[i]))))
		{
			tmp[freeIndex]=*(_array[i]);
			freeIndex++;
		}

	StudentSet t_StudentSet(tmp,(freeIndex));
	return t_StudentSet;
}

StudentSet&  StudentSet:: operator-=(const StudentSet& other)
{
	*this=((*this - other));
	return *this;
}

bool StudentSet::operator==(const StudentSet& other) const
{
	if(_size != other._size) //if the size is different they are definitely not equal.
		return false;
	int i;
	bool ans = true;
	for (i = 0; i < _size && ans; i++)      //if ans is false at least once it'll break the loop.
	{								        //notice that if both have a size of 0 we'll return true
		ans = Contains(*(other._array[i])); //because both are empty sets so they are equal.
	}
	return ans;
}

bool StudentSet::operator!=(const StudentSet& other) const
{
	return !((*this) == other);
}
int StudentSet::operator+() const
{
	return this->_size;
}
int StudentSet::getSize() const
{
	return this->_size;
}

Student& StudentSet::operator[](int index)
{
	return *(_array[index]);
}

const Student& StudentSet::operator[](int index)const
{
	return *(_array[index]);
}

bool StudentSet:: Contains(const Student& other) const
{
	int i;
	for (i = 0; i <_size; i++)
	{
		if(_array[i]->getID() == other.getID())
			return true;
	}
	return false;
}
