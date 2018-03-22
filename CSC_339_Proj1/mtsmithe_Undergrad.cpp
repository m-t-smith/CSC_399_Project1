/*
Matt Smitherman
CSC 339 Project 1
3/15/2018

ctrl k c --comment, ctrl k q --uncomment

This program defines a parent class: Student, and three subclasses: Undergrad, Grad, and GradAsst;
implements STL and i/o functions to write to files, and defines a sort function (overloading "<" operator)
*/

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <stdlib.h>
#include <list>

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
			
			cout << "Name: " << name << " SSN: " << ssn << " Credits: " << credits << " GPA: " << gpa;
		}
		virtual float tuition() = 0;

		void set_GPA(int gpa) {
			this-> gpa = gpa;
		}

		void set_Credits(int credits) {
			this-> credits = credits;
		}
		void display_Head() {
			cout << "Name:	             " << "SSN:     " << "Year     " << "Credits: "
				 << "Tuition: " << "GPA:     "  << endl;
		}
		string get_name() {
			return name;
		}
		string get_ssn() {
			return ssn;
		}
		int get_cred() {
			return credits;
		}
		float get_gpa() {
			return gpa;
		}

};

class Mtsmithe_Undergrad : public Student {

	protected:
		float undergrad_rate = 380.0;
		char yearArray[10];
		char (*year)[10] = &yearArray;
		float * mytuition;
		

	public:
		Mtsmithe_Undergrad(const char name[21], const char ssn[10],
			float gpa, int credits, char parYear[]) : Student(name, ssn, gpa, credits) {
			tuition();
			strcpy_s(*year, parYear);

		};

		char * get_year() {
			return *year;
		}

		float get_rate() {
			return undergrad_rate;
		}


		float tuition() {
			*mytuition = undergrad_rate * credits;
			return *mytuition;
		};
		void print() {
			cout << endl;
			Student::print();
			cout << " Year: " << *year << " Tuition: $" << tuition();
		}
		float get_tuition() {
			return *mytuition;
		}
		

};

class Grad : public Student {
	protected:
		float grad_rate = 500.0;
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
			float tuition = grad_rate * credits;
			return tuition;
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
			cout << " Title: graduate " << *title << " Tutition: $" << tuition() << " Thesis: " << *thesis;
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
			cout << " Pay: $"<<  hourPay << " Supervisor: " << supervisor << " Task: " << task << endl;
		}
};

class utilityPack {


public:
	utilityPack(int i) {};

	void tell(char b, char f, string in) {
		string call;
		switch (b) {
			case 's':
				call = "static";
				break;

			case 'd':
				call = "dynamic";
				break;
			}

			if (f == 'p') {
				cout << " \n " << call << " call of print() in " << in << ":";
			}
			else if (f == 't') {
				cout << "\n " << call << " call of tuition() in " << in << ": $";
			}
	}
	vector<string> get_tokens(string in) {
		istringstream iss(in);
		vector<string> tokens{ istream_iterator<string>{iss}, istream_iterator<string>{} };
		return tokens;
	}


	
};



	//main function executes program
	int main() {

		utilityPack util(1);
		Mtsmithe_Undergrad student("Mary", "000111222", 4.0, 12, "Junior"), *ugradPtr;

		ugradPtr = &student;

		
		util.tell('s', 'p', "_undergrad");
		student.print();
		util.tell('s', 't', "_undergrad");
		cout  << student.tuition() << endl;
		util.tell('d', 'p', "_undergrad");
		ugradPtr->print();
		util.tell('d', 't', "_undergrad");
		cout << ugradPtr->tuition() << endl;

		Grad gStudent("David", "111222333", 3.7, 9, "How to learn data structures using C++/STL", "student"), *gradPtr;
		
		gradPtr = &gStudent;
		
		util.tell('s', 'p', "Grad");
		gStudent.print();
		util.tell('s', 't', "Grad");
		cout << gStudent.tuition() << endl;
		util.tell('d', 'p', "Grad");
		gradPtr->print();
		util.tell('d', 't', "Grad");
		cout << gradPtr->tuition() << endl;

		GradAsst gradAss("Jason", "222333444", 3.9, 9, "Design of efficient algorithms", 20.0, "Dr. Fu",
			"Grading 330 projects and implementing a data mining algorithm", "assistant"), *gradAssPtr;
		
		gradAssPtr = &gradAss;

		util.tell('s', 'p', "GradAsst");
		gradAss.print();
		util.tell('s', 't', "GradAsst");
		cout << gradAss.tuition() << endl;
		util.tell('d', 'p', "GradAsst");
		gradAssPtr->print();
		util.tell('d', 't', "GradAsst");
		cout<< gradAssPtr->tuition() << endl;

		ifstream file("student.txt");
		string line;
		list<Mtsmithe_Undergrad> student_list;
		vector<Mtsmithe_Undergrad*> students;

		while (getline(file, line)) {
			vector <string> e = util.get_tokens(line);
			char name[21];
			char ssn[10];
			char year[10];
			float cred;
			int gpa;

			strcpy_s(name, e[0].c_str());
			strcpy_s(ssn, e[1].c_str());
			strcpy_s(year, e[2].c_str());
			cred = atof(e[3].c_str());
			gpa = atoi(e[4].c_str());

			student_list.push_back(Mtsmithe_Undergrad(name, ssn, gpa, cred, year));
		}

		student_list.push_front(student_list.back());
		student_list.pop_back();

		cout << endl << endl;
		list <Mtsmithe_Undergrad> ::iterator it;
		
		student.display_Head();
		/*for (auto it = student_list.begin(); it != student_list.end(); it++ ) {
			cout << it->get_name() << "  " << it->get_ssn() << "  " << it->get_year() << "  "
				<< it->get_cred() << "  " << it->get_tuition() << endl;
		}*/
		
		

		return 0;
	}



