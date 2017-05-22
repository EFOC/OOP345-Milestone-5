#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "util.h"

void trim(std::string& s){
	while(!s.empty() && s[0] == ' ')
		s.erase(0,1);//delete 1st character

	while(!s.empty() && s[s.size() - 1] == ' ')
		s.erase(s.size() - 1,1);//delete last character

}

void csvRead(std::string& fileName,char seperator,std::vector<std::vector<std::string> >  &csvData){
std::fstream is(fileName,std::ios::in);
	if(!is.is_open())
		throw std::string("Cannot open file '") + fileName + "'";

	std::string line;

	while(getline(is,line)){
		//cout << line <<"-->\n";
		auto cr = line.find('\r');
			if(cr != std::string::npos)
				line.erase(cr);
	      	std::cout << line << "\n";//can delete this to remove empty line

		size_t index=0;
		std::vector<std::string> fields;
		std::string field;

		while(index < line.size()){
			while(index < line.size() && line[index] != seperator){
				field += line[index];
				index++;
			}
			//cout << field << "\n";
			index++;
			trim(field);
			std::cout << field << "\n";
			fields.push_back(move(field));
		}
		csvData.push_back(move(fields));		
	}
	is.close();
}

void csvPrint(std::vector<std::vector<std::string>> &csvData){
	std::cout << "CsvPrint start\n";
	//cout << "csvData-->" <<  csvData << "\n";
	for(auto row : csvData){
		for(auto column : row){
			std::cout << "<" << column << "> ";
		}
		std::cout << "\n";

	}

	for(auto row = csvData.begin() ; row != csvData.end(); row++){
			for(auto column = row->begin();column != row->end();column++){
				std::cout << "[" << *column << "] ";
		
			}
			std::cout << "\n";
	}

	for(size_t row=0; row < csvData.size();row++){
			for(size_t column = 0;column < csvData[row].size(); column++){
				std::cout << "{" << csvData[row][column] << "} ";
		
			}
			std::cout << "\n";
	}

}

bool validTaskName(std::string &s) {
	for (auto c : s)
		if ( !(isalnum(c) || c == ' '))
			return false;
		else
			return true;

}

bool validTaskSlots(std::string &s) {
	for (auto c : s)
		if (!(isdigit(c) || c == ' '))
			return false;
		else
			return true;

}

bool validSlots(std::string &s) {
	for (auto c : s)
		if (!(isdigit(c)))
			return false;
		else
			return true;
}

bool validItemName(std::string &s) {
	for (auto c : s)
		if ( !(isalnum(c) || c == ' '|| c == '#'))
			return false;
		else
			return true;


}

bool validSequence(std::string &s) {
	for (auto c : s)
		if (!(isdigit(c)))
			return false;
		else
			return true;
}

bool validCustomerName(std::string &s) {
	for (auto c : s)
		if ( !(isalnum(c) || c == ' '|| c == '#'))
			return false;
		else
			return true;
}

bool validOrderName(std::string &s) {
	for (auto c : s)
		if ( !(isalnum(c) || c == ' '|| c == '#'))
			return false;
		else
			return true;

}









