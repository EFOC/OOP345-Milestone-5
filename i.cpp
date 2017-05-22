#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "util.h"
#include "i.h"
using namespace std;

      Item::Item(){}

      Item::Item(std::vector< std::string > &row){

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

	void Item::print() {
		  cout << "task /name/installer/remover/sequence/description/ ="
			  << "/" << itemName
			  << "/" << itemInstaller
			  << "/" << itemRemover
			  << "/" << itemSequence 
			  << "/" << itemDescription << "\n";
	  }

	  void Item::graph(fstream& os) {
		char q = '"';
		  os << q << "Item " << itemName << q << " -> "  << q << "installer" << itemInstaller <<  q << " [color=green];\n";
		   os << q << "Item " <<itemName << q << " -> " << q << "Remover" << itemRemover << q << " [color=red];\n";

		os << q << "Item" << itemName << q << "[shape=box];\n";

	  }

	ItemManager::ItemManager() {}
	ItemManager::ItemManager(std::vector<std::vector<std::string>> &csvData) {
		int lineNumber = 0;
		for (auto row : csvData) {
			try {
				lineNumber++;
				itemList.push_back(move(Item(row)));
			}
			catch (std::string& e) {
				cerr <<"Problem with line " << lineNumber << ": " << e << "\n";
			}
		}
	}

	void ItemManager::print() {
		int lineNumber = 0;
		for (auto t : itemList){
			lineNumber++;
			cout << lineNumber <<": ";
			t.print();
		}
	}

	void ItemManager::graph(string &filename) {
		
		fstream os(filename + ".gv", ios::out);
		//ofstream os(f, ios::out);

		if(os.is_open()){
			os << "digraph taskGraph{\n";
			for (auto t : itemList){
				t.graph(os);
			}
			os << "}\n";
			os.close();
			string cmd;
			#ifdef __MSVC
			cmd = "C:/\"Program Files (x86)\"/Graphviz2.38/bin/dot.exe"
			#else
			cmd = "dot";
			#endif
			
			cmd += string (" .Tpng ") + filename + ".gv > " + filename + ".gv.png";
			cout << " running " << cmd << endl;
			cout << " returned " << system(cmd.c_str()) << " <-- 0 is good because it means dot worked!" << endl;
			
		}
	}

	void ItemManager::IntegrityCheck(TaskManager& tm){
		for(auto i : itemList){
			if(tm.FindTask(i.getItemInstallerTask()) == nullptr){
				throw string("Item '") + i.getItemName() + "' references installer task '" + i.getItemInstallerTask() + "' but it does not exist!";
			}
			if(tm.FindTask(i.getItemRemoverTask()) == nullptr){
				throw string("Item '") + i.getItemName() + "' references remover task '" + i.getItemRemoverTask() + "' but it does not exist!";
			}
		}
	}
	
	Item* ItemManager::FindItem(string& name){
		for(size_t i = 0; itemList.size(); i++){
			if(itemList[i].getItemName() == name){
				return &itemList[i];
			}
		}
		return nullptr;
	}
	

