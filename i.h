#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "util.h"
#include "t.h"
using namespace std;
//take away namespace stdsl
//item() properties need to be initialized to zero
class Item {
		string itemName, itemInstaller, itemRemover, itemSequence,itemDescription;
	public:

		Item();
		Item(std::vector< std::string > &row);

		string& getItemName() {return itemName;}
		string& getItemInstallerTask() {return itemInstaller;}
		string& getItemRemoverTask() {return itemRemover;}

		void print();
		void graph(fstream& os);
};

class ItemManager {
	std::vector< Item > itemList;

	public:
	ItemManager();
	ItemManager(std::vector<std::vector<std::string>> &csvData);

	Item* FindItem(std::string& name);

	void print();
	void graph(string& filename);

	size_t getSize(){return itemList.size();}
	Item* getItem(size_t i){ return& itemList[i]; }
	void IntegrityCheck(TaskManager& tm);


};

