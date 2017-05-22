#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "util.cpp"

using namespace std;

int main(int argc,char* argv[])
{
	try{
	if(argc != 3)
	throw string("Usage: ") + argv[0] + " csv-date-file csv=separator-character";
	
	string fileName = argv[1];
	char seperator = argv[2][0];

	vector< vector<string> > csvData;
	csvRead(fileName,seperator,csvData);
	csvPrint(csvData);
	}catch(const string& e){
		cerr << e << "\n";
	}
}
