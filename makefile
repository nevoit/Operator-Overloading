myStudentSet: StudentSet.o Student.o main.o
	g++ StudentSet.o Student.o main.o -o myStudentSet

StudentSet.o: StudentSet.h StudentSet.cpp
	g++ -c StudentSet.cpp

Student.o: Student.h Student.cpp
	g++ -c Student.cpp

main.o: main.cpp
	g++ -c main.cpp

clean:
	rm -f *.o

