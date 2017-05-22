#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

void trim(string& s){
	while(not s.empty() && s[0] == ' ')
		s.erase(0,1);//delete 1st character

	while(not s.empty() && s[s.size() - 1] == ' ')
		s.erase(s.size() - 1,1);//delete last character

}

void csvRead(string& fileName,char seperator,vector<vector<string>>csvData){
fstream is(fileName,ios::in);
if(not is.is_open())
	throw string("Cannot open file '") + fileName + "'";

is.close();
string line;

while(getline(is,line)){
	auto cr = line.find('\r');
		if(cr != string::npos)
			line.erase(cr);
	cout << line << "\n";

	size_t index=0;
	vector<string> fields;
	string field;

while(index < line.size()){
	while(index < line.size() && line[index] != seperator){
	field += line[index];
	index++;
	}
	cout << field << "\n";
	index++;
	fields.push_back(move(field));
	//cout << line << "\n";
	
}



}
is.close();
}

void csvPrint(vector<vector<string>> &csvData){

for(auto row: csvData){
	for(auto column : row){
	
	cout << "<" << column << ">";
	}
cout << "\n";

}


for(auto row = csvData.begin() ; row != csvData.end(); row++){
		for(auto column = row->begin();column != row->end();column++){
		cout << "[" << *column << "]";
	
		}
		cout << "\n";
}



for(size_t row=0; row < csvData.size();row++){
		for(size_t column = 0;column < csvData[row].size(); column++){
		cout << "{" << csvData[row][column] << "}";
	
		}
		cout << "\n";
	}

}

int main(int argc,char* argv[])
{
	try{
	if(argc != 3)
	throw string("Usage: ") + argv[0] + " csv-date-file csv=separator-character";
	string fileName = argv[1];
	char seperator = argv[2][0];

	vector<vector <string>> csvData;
	csvRead(fileName,seperator,csvData);
 
	}catch(const string& e){
		cerr << e << "\n";
	}
}
