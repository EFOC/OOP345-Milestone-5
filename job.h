#include "o.h"

class Job: public Order{
	vector<bool> installed;
	public:
	Job();
	Job(Order* o) : Order(*o){
		installed.resize(getItemSize());
		for(size_t i = 0; i < getItemSize(); i++){
			installed[i] = false;
		}
	};
	bool Installed(size_t i){return installed[i];};
	void Installed(size_t i, bool value){installed[i]==value;};

};
