#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "util.h"

using namespace std;
class Order;
class OrderManager;

//replace orders with order
class Order {

public:
	string orderCustomer,orderProduct;
	vector <string> orderList;

      Order(){

	}

      Order(std::vector< std::string > &row){
		  		
	  if(row.size() < 3){
		  throw string("Expected at least 3 fields - found ") + to_string(row.size());
	  //		orderDescription =row[4];
	  }
	 	  if(validCustomerName(row[0]))
			orderCustomer = row[0];
			else
				throw string("Expected a customer name, found'") + row[0] + "'";
				
			if(validOrderName(row[1]))
			orderProduct = row[1];
			else
				throw string("Expected a product name, found'") + row[1] + "'";

			for(size_t i = 2 ; i < row.size() ; i++)
					if(validItemName(row[i]))
						orderList.push_back(row[i]);
					else
						throw string("Syntax Error");
	   }//end Order(...)

	void print() {
		  cout << "order /customer/product/items .../ ="
			  << "/" << orderCustomer
			  << "/" << orderProduct;
		
		for(auto item : orderList) 
		       	cout << "/" << item;
		cout << "/\n";	  
	
	}

	  void graph(ostream& os) {
		char q = '"';
	for(auto item : orderList)  
	os << q << orderCustomer << ":" << orderProduct << q << "->" << q << item << q << "[color=blue];\n";
	//os << q + orderCustomer + ":" + orderProduct + q +  "->" + q + item + q + "[color=blue];\n";
  	}

};

class OrderManager{
	vector<Order> orderList;
public:
	OrderManager() {}
	OrderManager(std::vector<std::vector<std::string>> &csvData) {

		for (auto row : csvData) {
			try {
				orderList.push_back(move(Order(row)));
			}
			catch (std::string& e) {
				cerr << e << "\n";
			}
		}
	}

	void print() {
		for (auto t : orderList)
			t.print();
	}

	void graph(string &filename) {

		string f = filename + ".gv";
		fstream os(f, ios::out | ios::trunc);//??
		
		//ofstream os(f, ios::out);
		os << "digraph taskGraph{\n";
		for (auto t : orderList)
			t.graph(os);
		os << "}\n";
		os.close();
		string cmd = string ("dot -Tpng ") + filename + ".gv > " + filename + ".gv.png";
		cout << cmd << " returned " << system(cmd.c_str()) << "\n";
	
	}

};//ordermanager
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

		OrderManager tm(csvData);
		tm.print();	
		tm.graph(fileName);	
	}
	catch (const string& e) {
		cerr << e << "\n";
	}
}


