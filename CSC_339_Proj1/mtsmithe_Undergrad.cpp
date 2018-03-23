/*
Matt Smitherman
CSC 339-01 
Project 1
3/15/2018

This program defines a parent class: Student, and three subclasses: Undergrad, Grad, and GradAsst;
implements various i/o functions to read from files, store data in list and vector data-structures,
print to console, and implements STL sort function (overloading "<" operator)

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
#include <iomanip>

using namespace std;

//define abstract base class student
class Student {
//declare student data members
	protected: 
		char name[21];
		char ssn[10];
		float gpa;
		int credits;
//define public functions of student
	public:
		//constructor
		Student(const char parName[], const char parSsn[], float gpa, int credits) 
			: gpa(gpa), credits(credits) {
			//there has to be a better way to handle character array data
			strcpy_s(name, sizeof name, parName);
			strcpy_s(ssn, sizeof ssn, parSsn);

		};
		//abstract function to be overloaded in derived classes so BCL pointers can use derived class version
		virtual void print() {
			
			cout << endl << " Name: " << name << endl << " SSN: " << ssn  << endl << " Credits: " << credits  << endl << " GPA: " << gpa << endl;
		}
		//pure abstract function (making Student class abstract and uninstantiable)
		virtual float tuition() = 0;

		void set_GPA(float gpa) {
			this-> gpa = gpa;
		}

		void set_Credits(int credits) {
			this-> credits = credits;
		}
		//header for table of student data to be used later
		void display_Head() {
			std::cout.width(20); cout << std::left << "Name:";
			cout << std::setw(10) << std::left << "SSN:";
			cout << std::setw(10) << std::left << "Year:";
			cout << std::setw(10) << std::left << "Credits:";
			cout << std::setw(10) << std::right << "Tuition:";
			cout << std::setw(10) << std::right << " GPA:";
			cout << endl;
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
//define Mtsmithe_Undergrad as a derived class of student
class Mtsmithe_Undergrad : public Student {
	//data members
	protected:
		float undergrad_rate = 380.0;
		char yearArray[10];
		char (*year)[10] = &yearArray;
		
		
	//public functionos
	public:
		//constructor (calls BCL constructor)
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
		//overriding pure virtual function (must be done)
		float tuition() {
			float tuition = undergrad_rate * credits;
			return tuition;
		}
		//overriding abstract function of student
		void print() {
			Student::print();
			cout << " Year: " << *year << endl << " Tuition: $" << tuition() << endl;
		}
		//function to use when overloading STL less than '<' operator
		static bool sortByGPA(Mtsmithe_Undergrad const & a, Mtsmithe_Undergrad const & b) {
			return a.gpa < b.gpa;

		}
		

};
//define Grad class as derived from student class
class Grad : public Student {
	protected:
		float grad_rate = 500.0;
		char thesisArray[70];
		char (*thesis)[70] = &thesisArray;
		char *thesisPtr;
		char titleArr[13];
		char(*title)[13] = &titleArr;

	public:
		//constructor
		Grad(const char name[21], const char ssn[10], float gpa, int credits,
			char parThesis[], char parTitle[]) : Student(name, ssn, gpa, credits) {
			//calls tuition which creates and sets tuiton variable 
			tuition();
			strcpy_s(*thesis, sizeof thesisArray, parThesis);
			strcpy_s(*title, sizeof titleArr, parTitle);
				
		};

		float get_rate() {
			return grad_rate;
		}
		//overriding abstract function in base class
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
		//overriding abstract print function
		void print() {
			cout << endl;
			//calls student print function
			Student::print();
			cout << " Title: graduate " << *title  <<endl << " Tuition: $" << tuition()  
				<< endl << " Thesis: " << *thesis << endl;
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
			cout << " Pay: $"<<  hourPay << endl << " Supervisor: " << supervisor 
				<< endl << " Task: " << task << endl;
		}
};

class utilityPack {

public:
	utilityPack(int i) {};

	void tell(char b, char f, string in) {
		string call;
		switch (b) {
			case 's':
				call = "Static";
				break;

			case 'd':
				call = "Dynamic";
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

	void linebreak() {
		cout << endl << endl;
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
		vector<Mtsmithe_Undergrad> student_vector;

		while (getline(file, line)) {
			vector <string> e = util.get_tokens(line);
			char name[21];
			char ssn[10];
			char year[10];
			int cred;
			float gpa;

			strcpy_s(name, e[0].c_str());
			strcpy_s(ssn, e[1].c_str());
			strcpy_s(year, e[2].c_str());
			cred = atoi(e[3].c_str());
			gpa = atof(e[4].c_str());

			student_list.push_back(Mtsmithe_Undergrad(name, ssn, gpa, cred, year));
		}

		student_list.push_front(student_list.back());
		student_list.pop_back();

		util.linebreak();

		list <Mtsmithe_Undergrad> ::iterator it;
		
		cout << "Students printed from list data structure after moving last student to front:";
		
		util.linebreak();

		student.display_Head();
		for (auto it = student_list.begin(); it != student_list.end(); it++ ) {

			student_vector.push_back( *it);

			std::cout.width(20); cout << std::left << it->get_name();
			std::cout.width(10); cout << std::left << it->get_ssn();
			cout << std::setw(10) << left << it->get_year(); 
			cout << std::setw(10) << left << it->get_cred();
			cout << std::setw(10) << setfill('$') << right << it->tuition();
			std::cout.fill(' '); cout << setw(10) << right << setprecision(2) << it->get_gpa() 
				<< setprecision(0) <<endl;
		}

		typedef bool(*mts_UdgrdGPACompFunc)(Mtsmithe_Undergrad const&, Mtsmithe_Undergrad const&);
		
		sort(begin(student_vector), end(student_vector), static_cast<mts_UdgrdGPACompFunc>(&Mtsmithe_Undergrad::sortByGPA));

		cout << endl << "Students by GPA in ascending order (if A's GPA < B's GPA then A is printed first): " << endl;

		for (auto  e : student_vector) {
			e.print();
		}

		util.linebreak();

		return 0;
	}



