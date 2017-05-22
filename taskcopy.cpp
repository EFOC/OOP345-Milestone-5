#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "util.h"

using namespace std;
class Task;
class TaskManager;


class Task {

public:
	string taskName, taskSlots, taskPass, taskFail;

      Task() : taskSlots("1") {

		}

	  Task(std::vector< std::string > &row) : taskSlots("1") {

		  switch (row.size()) {
		  case 4:
			  if (validTaskName(row[3]))
				  taskFail = row[3];
			  else
				  throw string("Expected a default task name, found '") + row[3] + "'";
			  //taskFail = row[3];
		  case 3:
			  if (validTaskName(row[2]))
				  taskPass = row[2];
			  else
				  throw string("Expected default task name, found '") + row[2] + "'";
		  case 2:
			 // taskSlots = row[1];
			  if (validTaskSlots(row[1]))
				  taskSlots = row[1];
			  else
				  throw string("Expected default task name, found '") + row[1] + "'";

		  case 1:
			  if (validTaskName(row[0]))
				  taskName = row[0];
			  else
				  throw string("Expected a default task name, found '") + row[0] + "'";
			  break;

		  default:
			  throw string("Expected 1,2,3,4 fields - found") + to_string(row.size());

		  }

	  }


	void print() {
		  cout << "task /name/slots/pass/fail/ ="
			  << "/" << taskName
			  << "/" << taskSlots
			  << "/" << taskPass
			  << "/" << taskFail;
	  }

	  void graph(ostream& os) {
		
		  char q = '"';
		  if (!taskPass.empty()) {
		  os << q << taskName << q << " -> "  << q << taskPass <<  q << " [color=green];\n";
		  }
		  if (!taskFail.empty()) {
			   os << q << taskName << q << " -> " << q <<  taskFail << q << " [color=red];\n";
		  }

		   if (taskPass.empty() && taskFail.empty()) {

			  os << q  <<  taskName  << q <<  "[shape=Box] ;\n";
		  }
	  }

};

class TaskManager : public vector<Task>{
	vector<Task> taskList;

public:
	TaskManager() {}
	TaskManager(std::vector<std::vector<std::string>> &csvData) {


		for (auto row : csvData) {
			try {
				taskList.push_back(move(Task(row)));
			}
			catch (std::string& e) {
				cerr << e << "\n";

			}
		}
	}
	void print() {
		for (auto t : taskList)
			t.print();

	}

	void graph(string &filename) {
		string f = filename + ".gv";
		fstream os(f, ios::out | ios::trunc);//??
		
		//ofstream os(f, ios::out);
		os << "digraph taskGraph{\n";
		for (auto t : taskList)
			t.graph(os);
		os << "}\n";
		os.close();
		string cmd = string ("dot -Tpng ") + filename + ".gv > " + filename + ".gv.png";
		cout << cmd << " returned " << system(cmd.c_str()) << "\n";
	}

};

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
		
		tm.graph(fileName);	

	}
	catch (const string& e) {
		cerr << e << "\n";
	}
}


