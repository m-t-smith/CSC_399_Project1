/*
Matt Smitherman
CSC 339-01 
Project 1
Start Date: 3/15/2018 Last Update: 3/23/2018

This program defines a parent class: Student, and three subclasses: Undergrad, Grad, and GradAsst;
implements various i/o functions to read from files, store data in list and vector data-structures,
print to console, and implements STL sort function (overloading "<" operator)

*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <list>
#include <iomanip>

using namespace std;

//define abstract base class student
class Student {
//declare student class data members
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
		//allocate space for a char array 
		char yearArray[10];
		//create a pointer and point it at the front of the char array
		char (*year)[10] = &yearArray;
		
		
	//public functionos
	public:
		//constructor (calls BCL constructor)
		Mtsmithe_Undergrad(const char name[21], const char ssn[10],
			float gpa, int credits, char parYear[]) : Student(name, ssn, gpa, credits) {
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
		//overriding abstract print() function of student
		void print() {
			Student::print();
			cout << " Year: " << *year << endl << " Tuition: $" << tuition() << endl;
		}
		//overloading STL less than '<' operator
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

			strcpy_s(*thesis, sizeof thesisArray, parThesis);
			strcpy_s(*title, sizeof titleArr, parTitle);	
		};

		float get_rate() {
			return grad_rate;
		}
		//overriding abstract tuition function in base class
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
			//calls student class print function
			Student::print();
			cout << " Title: graduate " << *title  <<endl << " Tuition: $" << tuition()  
				<< endl << " Thesis: " << *thesis << endl;
		}
		

};
//define class GradAsst as derived class of Grad
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
		//returns pointer to beginning of supervisor char array
		char * get_supervisor() {
			return supervisor;
		}

		float get_hourPay() {
			return hourPay;
		}
		
		void set_supervisor(char * mySupervisor) {
			//at first I thought I needed to deallocate the memory at supervisor
			//but I think that it happens automatically unless I use the new keyword,
			//am I wrong?
			supervisor = mySupervisor;
		}

		void set_hourPay(float pay) {
			hourPay = pay;
		}

		char * get_task() {
			return task;
		}

		void set_task(char * myTask) {
			task = myTask;
		}

		void print() {
			//call grad print function
			Grad::print();
			//print the variables in gradAsst that grad doesn't have
			cout << " Pay: $" <<  hourPay << endl << " Supervisor: " << supervisor 
				<< endl << " Task: " << task << endl;
		}
};
//utility class to consolidate helper functions
class utilityPack {

public:
	//not 100% sure why I can't have a constructor without parameters
	//but this is the constructor
	utilityPack(int i) {};
	//function to provide context for the required console output
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
	//string tokenizer function, stores tokens (delimited by ' ') in a vector 
	//and returns that vector
	vector<string> get_tokens(string in) {
		istringstream iss(in);
		vector<string> tokens{ istream_iterator<string>{iss}, istream_iterator<string>{} };
		return tokens;
	}
	//function to seperate console output by an empty line
	void linebreak() {
		cout << endl << endl;
	}


	
};



	//main function executes program
	int main() {
		//instantiate utilityPack and Mtsmithe_Undergrad objects
		//and a pointer to the later 
		utilityPack util(1);
		Mtsmithe_Undergrad student("Mary", "000111222", 4.0, 12, "Junior"), *ugradPtr;
		//point pointer at _undergrad object address for dynamic function calls
		ugradPtr = &student;

		//call print function in _undergrad statically and say that's what
		//happening in the console with util.tell
		util.tell('s', 'p', "_undergrad");
		student.print();
		//do the same thing for tuition function
		util.tell('s', 't', "_undergrad");
		cout  << student.tuition() << endl;
		//now call both functions again dynamically with the pointer and arrow operator
		util.tell('d', 'p', "_undergrad");
		ugradPtr->print();
		util.tell('d', 't', "_undergrad");
		cout << ugradPtr->tuition() << endl;

		//instantiate Grad object/pointer and repeat what we did for the _undergrad object
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
		
		//instantiate gradAsst object and do the whole process again with it
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

		//create an input-file-stream named file from a text file named 'student' 
		//stored in the local directory  
		ifstream file("student.txt");
		//declare a string variable called line to store lines from the file
		string line;
		//declare a list object named student_list of type Mtsmithe_Undergrad 
		list<Mtsmithe_Undergrad> student_list;
		//declare a vector object named student_vector of the same type
		vector<Mtsmithe_Undergrad> student_vector;
		
		//loop that executes once per line in the student file until it hits
		//and empty line and returns false
		while (getline(file, line)) {
			//create a vector of type string and feed it the tokens of the current line
			vector <string> e = util.get_tokens(line);
			//declare variables that match our class's constructor parameters
			char name[21];
			char ssn[10];
			char year[10];
			int cred;
			float gpa;
			//convert the tokens in the vector from string type to the types the constructor needs
			//and store them in the appropriate variables
			strcpy_s(name, e[0].c_str());
			strcpy_s(ssn, e[1].c_str());
			strcpy_s(year, e[2].c_str());
			cred = atoi(e[3].c_str());
			gpa = atof(e[4].c_str());
			//instantiate an *_Undergrad object with those variables and put them in
			//the list object we declared earlier
			student_list.push_back(Mtsmithe_Undergrad(name, ssn, gpa, cred, year));
		}
		//get a copy of the _Undergrad object at the end of the list and insert it at the front
		student_list.push_front(student_list.back());
		//delete the object in the back of the list that we just copied to the front  
		student_list.pop_back();

		util.linebreak();
		//declare an iterator that can deal with our *_Undergrad type list
		list <Mtsmithe_Undergrad> ::iterator it;
		//provide context for the following output in the console
		cout << "Students printed from list data structure after moving last student to front:";
		
		util.linebreak();
		//print header of data table to console
		student.display_Head();
		//step through the list from the beginning to the end executing the following
		for (auto it = student_list.begin(); it != student_list.end(); it++ ) {
			//put *_Undergrad object currently pointed to by iterator in the back of our vector
			student_vector.push_back( *it);
			//display object data in console using various manipulators as required
			std::cout.width(20); cout << std::left << it->get_name();
			std::cout.width(10); cout << std::left << it->get_ssn();
			cout << std::setw(10) << left << it->get_year(); 
			cout << std::setw(10) << left << it->get_cred();
			cout << std::setw(10) << setfill('$') << right << it->tuition();
			std::cout.fill(' '); cout << setw(10) << right << setprecision(2) << it->get_gpa() 
				<< setprecision(0) <<endl;
		}
		//create and name a boolean function pointer that defines the expected parameters/parameter types for a generic function call
		typedef bool(*mts_UndgrdGPACompFunc)(Mtsmithe_Undergrad const&, Mtsmithe_Undergrad const&);
		//call the STL generic function sort, passing the front and back indicies of our vector as its parameters, along with 
		//a reference to the function that we wrote to override the '<' operator, cast to the boolean function pointer we just defined
		sort(begin(student_vector), end(student_vector), static_cast<mts_UndgrdGPACompFunc>(&Mtsmithe_Undergrad::sortByGPA));
		//print context for the console output
		cout << endl << "Students printed from vector in ascending order of GPA (if A's GPA < B's GPA then A is printed first): " << endl;
		//call the print function of each object stored in the sorted vector to show it's been sorted 
		for (auto  e : student_vector) {
			e.print();
		}

		util.linebreak();
		//end of the program
		return 0;
	}



