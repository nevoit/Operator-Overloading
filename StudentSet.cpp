#include "StudentSet.h"
#include <iostream>
#define SUCCESSFUL_ALOCCATION(var) if(NULL==var) {cout << "Failed to allocate memory! \n"; exit(1);}

int StudentSet:: _setSize=0;
StudentSet** StudentSet:: _setArray=NULL;

StudentSet::StudentSet()
{
	_array=NULL;
	_size=0;
	position = -1;
	AddSet();
}

StudentSet::StudentSet(Student stuArray [],int size)
{
	int& r_size=size;
	_array=NULL;
	UniqueStudents(stuArray, r_size); //Here we allocate memory on the heap
	_size = r_size; //free index will also contain the numbers of unique IDs
	position = -1;
	AddSet();

}

StudentSet::StudentSet (const StudentSet& other)
{
	_array=NULL;
	_size=other._size;
	position = -1;
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
		this->position = 0;
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
		this->position = _setSize-1;
	}

}

void StudentSet::deleteSet()
{
	if(_setSize>1)
	{
		StudentSet* tmp = (_setArray[this->position]);
		_setArray[this->position] = (_setArray[_setSize-1]);
		_setArray[_setSize-1] = tmp;
		_setArray[_setSize-1]= NULL;
		_setSize--;
	}
	else
	{
		if(NULL!=_setArray)
			delete [] _setArray;
		_setArray= NULL;
		_setSize--;
	}
	this->position = -1;
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
	deleteSet(); //remove the given set from setArray
	int i;
	for (i = 0; i <_size; i++)
		if(NULL!=_array[i])
			delete _array[i];

	if(NULL!=_array)
		delete[]_array;
}

void StudentSet:: UniqueStudents(const Student stuArray [], int& size)
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

	_array = new Student*[freeIndex];
	SUCCESSFUL_ALOCCATION(_array);

	for (i = 0; i <freeIndex; i++)
		_array[i]= new Student(studentUniqueID[i]);

}

ostream & operator<<(ostream & out, const StudentSet & stu)
{
		return stu.Show(out);
}

ostream & StudentSet::Show(ostream & out)const
{

	if(_size!=0)
	{
		out << "{" << _size << ", ";
		int i;
		for (i = 0; i < _size; i++)
		{
			out << *_array[i];
			if(i!=_size-1)
				cout<<", ";
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
	for (i = 0; i <_size; i++)
		if(NULL!=_array[i])
			delete _array[i];

	if(NULL!=_array)
		delete[] _array;

	_array=NULL;
	_size=other._size;
	_array = new Student*[_size];
	SUCCESSFUL_ALOCCATION(_array);
	for (i = 0; i <_size; i++)
		_array[i]= new Student(other[i]);

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
	*this = (*this + other);
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
	if(_size != (other._size)) //if the size is different they are definitely not equal.
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
