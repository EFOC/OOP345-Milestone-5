#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "util.h"
#include "o.h"

  using namespace std;
  
  Order::Order(vector<string> &row){
	if(row.size() < 3){
		throw string("need at least 3 fields, found ") + to_string(row.size());
	}
	if(validCustomerName( row[0] )){
		orderCustomer = row[0];
	}else{
		throw string("expected customer name, found [") + row[0] + "]";
	}
	if(validOrderName(row[1])){
		orderProduct = row[1];
	}else{
		throw string("expected product name, found [") + row[1] + "]";
	}
	for(size_t i = 2; i < row.size(); i++){
		if(validItemName(row[i])){
			orderItems.push_back(row[i]);
		}else{
			throw string("expected item name, found [") + row[i] + "]";
		}
	}

  }
  
 void Order::print()
 {
   std::cout << "order: /customer/product/ items ... /"
        << orderCustomer << "/"
        << orderProduct << "/";
   for(auto i : orderItems)
        std::cout << i << "/";
   std::cout << "\n";
 }

 void Order::graph(std::fstream &os)
 {
   std::string q("\"");

   for(auto item : orderItems) {
     os << q + orderCustomer + "/" + orderProduct + q + " -> " + q + item + q + "[color=blue];\n";
   }
 }

 OrderManager::OrderManager() {}
 OrderManager::OrderManager( std::vector< std::vector<std::string> > &csvData )
 {
	 int lineNumber = 0;
   for(auto row : csvData) {
     try {
	     lineNumber++;
       orders.push_back( std::move(Order(row)) );
     } catch (const std::string& e) {
       std::cerr << "OrderManager: problem with line " << lineNumber << ": " << e << "\n";
     }
   }
 }

 void OrderManager::print()
 {
	 int lineNumber = 0;
   for(auto t : orders){
    	   lineNumber++;
	   cout << lineNumber << ": ";
	   t.print();
   }
 }

 void OrderManager::graph(std::string& orderFilename)
 {
   std::fstream os(orderFilename + ".gv", std::ios::out); // NOTE single | not ||
	if(os.is_open()){
   os << "digraph orderGraph {\n";
   for(auto t : orders){
     t.graph( os );
   }
   os << "}\n";
   os.close();

   string cmd;
#ifdef __MSVC
	cmd = "C:/\"Program Files (x86)\"/Graphviz2.38/bin/dot/exe"
#else
		cmd = "dot";
#endif
	cmd += string(" .Tpng ") + orderFilename + " .gv >" + orderFilename + ".gv.png";
	cout << "running " << cmd << endl;
	cout << "returned " << system(cmd.c_str()) << " <--- 0 is good because it means dot worked!\n";
	} 
}

void OrderManager::IntegrityCheck(ItemManager& im){
	for(auto o : orders){
		for(size_t count = 0; count < o.getItemSize(); count++){
			if(im.FindItem(o.getItemNumber(count)) == nullptr){
				throw string("Order '") + o.getCustomer() + "/" + o.getProduct() + "' references item '" + o.getItemNumber(count) + "' but it does not exist!";
			}
		}
	}
}
