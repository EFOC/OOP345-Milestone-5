#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "util.h"

using namespace std;
class Task;
class TaskManager;

#include "util.h"
#include "t.h"


int main(int argc, char* argv[])
{
	try {
		if (argc != 3)
			throw string("Usage: ") + argv[0] + " csv-date-file csv=separator-character";

		string fileName = argv[1];
		//string fileName = ""
		char seperator = argv[2][0];

		vector< vector<string> > csvData;
		csvRead(fileName, seperator, csvData);
		csvPrint(csvData);
	
		TaskManager tm(csvData);
		tm.print();	
		tm.graph(fileName);	

	}
	catch (const string& e) {
		cerr << e << "\n";
	}
}


