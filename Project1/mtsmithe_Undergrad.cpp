/*
Matt Smitherman
CSC 339 Project 1
3/15/2018

This program defines a parent class: Student, and three subclasses: Undergrad, Grad, and GradAsst;
implements STL and i/o functions to write to files, and defines a sort function (overloading "<" operator)
*/

#include<iostream>;
using namespace std;

class Student {

	protected: 
		char name[21];
		char ssn[10];
		float gpa;
		int credits;

	public:
		virtual void print() {
			printf("a string \n \n");
		}
		virtual void tuition() = 0;


};



//main function executes program
int main() {
	cout << "I know how to print things \n\n";
	print();

	return 0;
}