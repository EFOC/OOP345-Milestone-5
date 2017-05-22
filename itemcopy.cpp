#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "util.h"

using namespace std;
class Item;
class ItemManager;


class Item {

public:
	string itemName, itemInstaller, itemRemover, itemSequence,itemDescription;

      Item(){

		}

      Item(std::vector< std::string > &row){

		  switch (row.size()) {
		  case 5:
				  itemDescription = row[4];
		  case 4:

			  if (validSequence(row[3]))
				  itemSequence = row[3];
			  else
				  throw string("Expected sequential number, found '") + row[3] + "'";
			 // taskSlots = row[1];
			  if (validTaskName(row[2]))
				  itemRemover = row[2];
			  else
				  throw string("Expected a remover, found '") + row[2] + "'";

			  if (validTaskName(row[1]))
				  itemInstaller = row[1];
			  else
				  throw string("Expected a installer, found '") + row[1] + "'";
			  if (validItemName(row[0]))
				  itemName = row[0];
			  else
				  throw string("Expected a sequence number, found '") + row[0] + "'";
			  break;

		  default:
			  throw string("Expected 4 or 5  fields - found") + to_string(row.size());

		  }

	  }//end Item(...)

	void print() {
		  cout << "task /name/installer/remover/sequence/description/ ="
			  << "/" << itemName
			  << "/" << itemInstaller
			  << "/" << itemRemover
			  << "/" << itemSequence 
			  << "/" << itemDescription << "\n";
	  }

	  void graph(ostream& os) {
		char q = '"';
		  os << q << "Item" << itemName << q << " -> "  << q << "installer" << itemInstaller <<  q << " [color=green];\n";
		   os << q << "Item" <<itemName << q << " -> " << q << "Remover" << itemRemover << q << " [color=red];\n";

	  }

};

class ItemManager : public vector<Item>{
	vector<Item> itemList;

public:
	ItemManager() {}
	ItemManager(std::vector<std::vector<std::string>> &csvData) {

		for (auto row : csvData) {
			try {
				itemList.push_back(move(Item(row)));
			}
			catch (std::string& e) {
				cerr << e << "\n";
			}
		}
	}
	void print() {
		for (auto t : itemList)
			t.print();
	}
	void graph(string &filename) {
		
		string f = filename + ".gv";
		fstream os(f, ios::out | ios::trunc);//??
		
		//ofstream os(f, ios::out);
		os << "digraph taskGraph{\n";
		for (auto t : itemList)
			t.graph(os);
		os << "}\n";
		os.close();
		string cmd = string ("dot -Tpng ") + filename + ".gv > " + filename + ".gv.png";
		cout << cmd << " returned " << system(cmd.c_str()) << "\n";
	
	}

};//itemmanager
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
	
		ItemManager tm(csvData);
		tm.print();	
		tm.graph(fileName);	

	}
	catch (const string& e) {
		cerr << e << "\n";
	}
}


