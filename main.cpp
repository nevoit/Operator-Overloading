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


	Student *s1 = new Student(200, "Yossi", GENERAL);
	Student *s2 = new Student(300, "Carmel", ENGINEERING);
	Student *s3 = new Student(400, "Ofer", MEDICINE);
	Student *s4 = new Student(500, "Noam", MANAGEMENT);
	Student *s5 = new Student(940, "Piss", MANAGEMENT);
	Student *s6 = new Student(940, "hairyArms", ENGINEERING);
	Student *s7 = new Student(930, "hnevetz", ENGINEERING);
	Student *s8 = new Student(950, "YMCA", MEDICINE);

	Student SA1[5];
	SA1[0]= *s1;
	SA1[1]= *s2;
	SA1[2]= *s3;
	SA1[3]= *s4;
	SA1[4]= *s5;

	Student SA2[4];
	SA2[0]= *s1;
	SA2[1]= *s2;
	SA1[2]= *s6;
	SA1[3]= *s4;

	Student SA3[3];
	SA3[0]= *s1;
	SA3[1]= *s5;
	SA3[2]= *s6;

	Student SA4[3];
	SA4[0]= *s7;
	SA4[1]= *s8;
	SA4[2]= *s8;

	StudentSet* SS1 = new StudentSet(SA1, 5);
	StudentSet* SS2 = new StudentSet(SA2, 4);
	StudentSet* SS3 = new StudentSet(SA3, 3);
	StudentSet* SS4 = new StudentSet(SA4, 3);
//	StudentSet* SS5 = new StudentSet(SA4, 7);

	cout<<endl<<"========  Before the tests: ==========="<<endl;
	(*SS1).printAll();
	cout<<endl <<"========  Test details: (((*SS1)-=(*SS2))/=(*SS3))+=(*SS4); Print:(*SS1)==========="<<endl;
	(((*SS1)-=(*SS2))/=(*SS3))+=(*SS4);
	cout<<(*SS1)<<endl;

delete (s1);
delete (s2);
delete (s3);
delete (s4);
delete (s5);
delete (s6);
delete (s7);
delete (s8);
delete SS1;
delete SS2;
delete SS3;
delete SS4;

	//============================================================================

}
