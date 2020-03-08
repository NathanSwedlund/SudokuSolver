#include <iostream>
#include "SudokuSolver.h"
#include "Timer.h"
using namespace std;

int main()
{
	cout<<"Enter board file name: ";
	string fileName;
	cin>>fileName;

	// Ending program if file doesn't exist
	ifstream fin;
	fin.open(fileName.c_str());
	if(!fin.is_open())
	{
		cout<<"Error: file not found\n";
		return 0;
	}

	// Output stream to solve file
	ofstream fout;
	fout.open("Solved_"+fileName);

	// Creating board
	cout<<"Reading board...\n";
	Board b(fileName);

	// Printing unsolved board to file and console
	cout<<"\nUnsolved Board\n";
	cout<<"------------------\n";
	cout<<b;

	fout<<"Unsolved Board\n";
	fout<<"------------------\n";
	fout<<b;

	// Starting timer
	Timer t;
	t.start();

	// Solving board
	b.solve();

	// Getting solve time
	long double time = t.getTime();

	// Printing solved board and time to file and consol
	cout<<"\nSolved Board\n";
	cout<<"------------------\n";
	cout<<b;
	cout<<"------------------\n";
	cout<<"\nSolved in "<<time<<" seconds\n\n";

	fout<<"\nSolved Board\n";
	fout<<"------------------\n";
	fout<<b;
	fout<<"------------------\n";
	fout<<"\nSolved in "<<time<<" seconds\n\n";
}
