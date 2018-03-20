/*
Matt Smitherman
CSC 339 Project 1
3/15/2018

ctrl k c --comment, ctrl k q --uncomment

This program defines a parent class: Student, and three subclasses: Undergrad, Grad, and GradAsst;
implements STL and i/o functions to write to files, and defines a sort function (overloading "<" operator)
*/

#include<iostream>
#include<string.h>
#include<stdio.h>
using namespace std;

class Student {

	protected: 
		char name[21];
		char ssn[10];
		float gpa;
		int credits;

	public:
		Student(const char parName[], const char parSsn[], float gpa, int credits) 
			: gpa(gpa), credits(credits) {
			/*
			cout << "Enter student name" << endl;
			std::cin.getline(name, sizeof name);
			cout << "Enter student social security number" << endl;
			std::cin.getline(ssn, sizeof ssn);
			*/
			strcpy_s(name, sizeof name, parName);
			strcpy_s(ssn, sizeof ssn, parSsn);

		};

		virtual void print() {
			
			cout << name << "	" << ssn << "	 " << gpa << "	 " << credits;
		}
		virtual float tuition() = 0;

		void set_GPA(int gpa) {
			this-> gpa = gpa;
		}

		void set_Credits(int credits) {
			this-> credits = credits;
		}
		void display_Head() {
			cout << "Name:	" << "SSN:		" << "GPA:	" << "Credits:   "
				<< "Year/Title:	" << "	Tuition:	" << "Thesis:		"
				<< "Hourly Pay:	" << "Supervisor:" << "Task:" << endl;
		}

};

class Mtsmithe_Undergrad : public Student {

	protected:
		float undergrad_rate = 380.0;
		char yearArray[10];
		char (*year)[10] = &yearArray;
		

	public:
		Mtsmithe_Undergrad(const char name[21], const char ssn[10],
			float gpa, int credits, char parYear[]) : Student(name, ssn, gpa, credits) {
			tuition();
			strcpy_s(*year, sizeof yearArray, parYear);

		};

		char * get_year() {
			return *year;
		}

		float get_rate() {
			return undergrad_rate;
		}


		float tuition() {
			return undergrad_rate;
		};
		void print() {
			cout << endl;
			Student::print();
			cout << "       " << *year << "		" << undergrad_rate;
		}

};

class Grad : public Student {
	protected:
		float grad_rate;
		char thesisArray[70];
		char (*thesis)[70] = &thesisArray;
		char *thesisPtr;
		char titleArr[13];
		char(*title)[13] = &titleArr;

	public:
		Grad(const char name[21], const char ssn[10], float gpa, int credits,
			char parThesis[], char parTitle[]) : Student(name, ssn, gpa, credits) {

			tuition();
			strcpy_s(*thesis, sizeof thesisArray, parThesis);
			strcpy_s(*title, sizeof titleArr, parTitle);
				
		};

		float get_rate() {
			return grad_rate;
		}

		float tuition() {
			this->grad_rate = 500;
			return grad_rate;
		}
		char * get_thesis() {
			return thesisPtr;
		}
		void set_thesis(char * newPointer) {
			thesisPtr = newPointer;
		}
		void print() {
			cout << endl;
			Student::print();
			cout << "	  graduate " << *title << "	" << grad_rate << "		 " << *thesis;
		}

};

class GradAsst : public Grad {
	protected:
		float hourPay;
		char * supervisor;
		char * task;
		char titleArr[13];
		char(*title)[13] = &titleArr;

	public:
		GradAsst(const char name[21], const char ssn[10], float gpa, int credits,
			char parThesis[], float hourPay, char supervisor[21], char task[40], char parTitle[])
				: Grad(name, ssn, gpa, credits, parThesis, parTitle), hourPay(hourPay),
					supervisor(supervisor), task(task) {

			strcpy_s(*title, sizeof titleArr, parTitle);
		};

		char * get_supervisor() {
			return supervisor;
		}

		float get_hourPay() {
			return hourPay;
		}

		void set_supervisor(char * mySupervisor) {
			delete supervisor;
			supervisor = mySupervisor;
		}

		void set_hourPay(float pay) {
			hourPay = pay;
		}

		char * get_task() {
			return task;
		}

		void set_task(char * myTask) {
			delete task;
			task = myTask;
		}

		void print() {
			Grad::print();
			cout << "	"<<  hourPay << "   " << supervisor << "   " << task << endl;
		}
};


//main function executes program
int main() {


	Mtsmithe_Undergrad student("Mary", "000111222", 4.0, 12, "Junior");
	student.display_Head();
	student.print();
	
	Grad gStudent("David", "111222333", 3.7, 9, "How to learn data structures using C++/STL", "student");
	gStudent.print();

	GradAsst gradAss("Jason", "222333444", 3.7, 9, "Design of efficient algorithms", 20.0, "Dr. Fu", "Grading 330 projects and implementing a data mining algorithm", "assistant");
	gradAss.print();

	return 0;
}

