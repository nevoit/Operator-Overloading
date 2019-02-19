//============================================================================
// Name        : Main.cpp
// Author      : ise
// Version     :
// Copyright   :
// Description :
//============================================================================

#include <iostream>
#include "StudentSet.h"
using namespace std;

int main() {

	//============================================================================

	Student *s1 = new Student(199, "Yossi", GENERAL);
	Student *s2 = new Student(200, "Carmel", ENGINEERING);
	Student *s3 = new Student(201, "Ofer", MEDICINE);
	Student *s4 = new Student(202, "Noam", MANAGEMENT);
	Student *s5 = new Student(203, "Dolores", MEDICINE);
	Student *s6 = new Student(204, "Bernard", GENERAL);
	Student *s7 = new Student(930, "hnevetz", ENGINEERING);
	Student *s8 = new Student(950, "YMCA", MEDICINE);

	Student SA1[3];
	SA1[0]= *s4;
	SA1[1]= *s5;
	SA1[2]= *s6;


	Student SA2[4];
	SA2[0]= *s1;
	SA2[1]= *s2;
	SA2[2]= *s6;
	SA2[3]= *s4;



	Student SA3[3];
	SA3[0]= *s4;
	SA3[1]= *s5;
	SA3[2]= *s6;



	cout<<endl<<"========  Before the tests: ==========="<<endl;
	StudentSet* SS1 = new StudentSet(SA1, 3);//200,300
	cout << *SS1 <<endl;
	StudentSet* SS2 = new StudentSet(SA2, 4);//200,300,500,940
	cout << *SS2 <<endl;
	StudentSet* SS3 = new StudentSet(SA3, 3);
	cout << *SS3 <<endl;


	cout<<endl<<"========  Before the tests: ==========="<<endl;
	StudentSet::printAll();
	cout<<endl <<"========  Test details: (*SS1)+(*SS3); Print:(*SS1)==========="<<endl;
	((*SS1)+=(*SS2))+=(*SS3);
	StudentSet::printAll();

delete SS1;
delete SS2;
delete SS3;
delete (s1);
delete (s2);
delete (s3);
delete (s4);
delete (s5);
delete (s6);
delete (s7);
delete (s8);


	//============================================================================
/*
	Student* array = new Student[5];
	for (int i = 0 ; i < 5 ; i++)
	{
		if (array[i].getID() == 100+i && array[i].getFaculty() == GENERAL && strcmp(array[i].getName(),"NONE")==0)
			cout << "success" << endl;
		else
			cout << "failed: default constructor for Student" << endl;
	}
	//Should be {100, NONE, General}
	cout << array[0] << endl;
	//Should be {101, NONE, General}
	cout << array[1] << endl;
	delete[] array;


	Student *s1 = new Student(200, "Yossi", GENERAL);
	Student *s2 = new Student(300, "Carmel", ENGINEERING);
	Student *s3 = new Student(400, "Ofer", MEDICINE);
	Student *s4 = new Student(500, "Noam", MANAGEMENT);
	Student s6(600, "Tal", ENGINEERING);
	Student s5 = *s3;

	if (s5.getID() == s3->getID())
		cout << "success" << endl;
	else
		cout << "failed assignment" << endl;


	StudentSet emptySet;
	if (+emptySet == 0)
		cout << "success" << endl;
	else
		cout << "Failed: wrong default ctr or wrong operator overloading" << endl;
	Student studentArray[] = {*s1, *s2, *s3, *s4, s5};
	StudentSet* studentSet1 = new StudentSet(studentArray, 5);
	StudentSet* studentSet2 = new StudentSet(studentArray, 3);

	//Should be: {4, {200, Yossi, General}, {300, Carmel, Engineering}, {400, Ofer, Medicine}, {500, Noam, Management}}
	cout << *studentSet1 << endl;

	//Should be: {3, {200, Yossi, General}, {300, Carmel, Engineering}, {400, Ofer, Medicine}}
	cout << *studentSet2 << endl;
	(*studentSet1)[0] = s6;

	//Sould be: {4, {600, Tal, Engineering}, {300, Carmel, Engineering}, {400, Ofer, Medicine}, {500, Noam, Management}}
	cout << *studentSet1 << endl;

	///** should print:
	///** 3
	///** {0}
	///** {4, {600, Tal, Engineering}, {300, Carmel, Engineering}, {400, Ofer, Medicine}, {500, Noam, Management}}
	///** {3, {200, Yossi, General}, {300, Carmel, Engineering}, {400, Ofer, Medicine}}
	///**

	delete studentSet1;
	delete studentSet2;

	studentSet1 = new StudentSet(studentArray, 2);
	studentSet2 = new StudentSet(studentArray, 2);

	StudentSet::printAll();

	if (*studentSet1 == *studentSet2)
		cout << "success" << endl;
	else
		cout << "failed: wrong group or compare operator";
	(*studentSet1)[0] = s5;

	cout << *studentSet1 << endl;
	*studentSet1 += *studentSet2;

	cout << *studentSet2 << endl;
	//Should be: {3, {400, Ofer, Medicine}, {300, Carmel, Engineering}, {200, Yossi, General}}

	StudentSet::printAll();

	cout << *studentSet1 << endl;

	Student student = (*studentSet2)[0];
	cout << student << endl;


	delete studentSet1;
	delete studentSet2;
	delete(s1);
	delete(s2);
	delete(s3);
	delete(s4);
*/
	return 0;

}
