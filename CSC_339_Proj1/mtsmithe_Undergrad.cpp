/*
Matt Smitherman
CSC 339 Project 1
3/15/2018

ctrl k c --comment, ctrl k q --uncomment

This program defines a parent class: Student, and three subclasses: Undergrad, Grad, and GradAsst;
implements STL and i/o functions to write to files, and defines a sort function (overloading "<" operator)
*/

#include<iostream>;
#include<string.h>;
#include<stdio.h>;
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

		virtual void print() {}
		virtual float tuition() = 0;

		void set_GPA(int gpa) {
			this-> gpa = gpa;
		}

		void set_Credits(int credits) {
			this-> credits = credits;
		}

};

class Mtsmithe_Undergrad : public Student {

	protected:
		float undergrad_rate;
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
			undergrad_rate = 380.0;
			return undergrad_rate;
		};
		void print() {
			cout << "Name: " << name << " SSN: " << ssn << " Year: " << *year
				<< " credits: " + credits  << " tuition rate: $" << undergrad_rate 
				<< " " << "GPA: " << gpa << endl;
		}

};

class Grad : public Student {
	protected:
		float grad_rate;
		char thesisArray[70];
		char (*thesis)[70] = &thesisArray;
		char *thesisPtr;

	public:
		Grad(const char name[21], const char ssn[10], float gpa, int credits, 
			char parThesis[]) : Student(name, ssn, gpa, credits){

			tuition();
			strcpy_s(*thesis, sizeof thesisArray, parThesis);
				
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
			delete thesisArray;
			thesisPtr = newPointer;
		}
		void print() {
			cout << "Name: " << name << " SSN: " << ssn << " Year: graduate student"
				<< " credits: " + credits << " tuition rate: $" << grad_rate
				<< " GPA: " << gpa << " Thesis: " << *thesis << endl;
		}

};

class GradAsst : public Grad {
	protected:
		float hourPay;
		char * supervisor;
		char * task;
	public:
		GradAsst(const char name[21], const char ssn[10], float gpa, int credits,
			char parThesis[]) : Grad(name, ssn, gpa, credits, parThesis) {
			/*
			*supervisorPtr = "Dr.Fu";
			set_hourPay(20.0);
			set_supervisor();
			*/
		};
};


//main function executes program
int main() {

	Mtsmithe_Undergrad student("Mary", "000111222", 4.0, 12, "Junior");
	student.print();
	
	Grad gStudent("David", "111222333", 3.7, 9, "How to learn data structures using C++/STL");
	gStudent.print();


	return 0;
}

