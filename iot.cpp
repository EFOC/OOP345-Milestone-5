#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "util.h"

using namespace std;
#include "i.h"
#include "o.h"
#include "t.h"

//beautiful code
int main(int argc, char* argv[])
{
	try {
		if (argc != 3)
			throw string("Usage: ") + argv[0] + " item-csv-file order-csv-file task-csv-file csv-separator-character";

		string fileItemName  = argv[1];
		string fileOrderName = argv[2];
		string fileTaskName  = argv[3];
		//string fileName = argv[1];
	
		//string fileName = ""
		char seperator      = argv[4][0];

		vector< vector<string> > csvItemData;
		vector< vector<string> > csvOrderData;
		vector< vector<string> > csvTaskData;

		csvRead(fileItemName,  seperator, csvItemData);
		csvRead(fileOrderName, seperator, csvOrderData);
		csvRead(fileTaskName,  seperator, csvTaskData);

		csvPrint(csvItemData);
		csvPrint(csvOrderData);
		csvPrint(csvTaskData);

		ItemManager  im(csvItemData);
		OrderManager om(csvOrderData);
		TaskManager  tm(csvTaskData);

		im.print();	
		im.graph(fileItemName);	
		om.print();	
		om.graph(fileOrderName);	
		tm.print();	
		tm.graph(fileTaskName);
		tm.graph(fileTaskName);

	}
	catch (const string& e) {
		cerr << e << "\n";
	}
}


