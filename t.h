#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "util.h"

using namespace std;
//change std;

class Task {
		string taskName, taskSlots, taskPass, taskFail;
	public:
		std::vector<std::string> itemList;
		Task();

		Task(std::vector< std::string > row);
		string& getTaskName() {return taskName;}
		string& getTaskPass() {return taskPass;}
		string& getTaskfail() {return taskFail;}

		void print();
		void graph(std::fstream& os);

};

class TaskManager{
	std::vector< Task > taskList;

	public:
	TaskManager();
	TaskManager(std::vector< std::vector< std::string >> &csvData);
	Task* FindTask(std::string& name);
	void print();
	void graph(string& filename);
	void IntegrityCheck();
	size_t size() { return taskList.size(); }
	Task * getTask(size_t t) { return &taskList[t]; }


};
//Do the same thing for item.

//order is different because of item list. Item list is private to item. To Acesss item neeed getter for size . Getter for each item .Write order validate . Can't order item if doesn't exist.
//bool validate() you need to check the vector.Setter,getter,for order class. return number of items for order and a number that returns each getter. Order validate has to pass itemmanager.
