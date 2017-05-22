#pragma once

#include<queue>
#include"t.h"
#include"job.h"

class Machine : public Task {

	int coming;
	std::queue<Job>input;
	bool Installer1;
	bool Remover1;

	public:
	Machine()
	{
		coming = 0;
	}
	Machine(Task* t) : Task(*t)
	{
		coming = 0;
	}
	void incComing()
	{
		coming++;
	}
	bool isSource() const{return coming ==0;};
	bool isSink() {return getTaskPass().empty();};
	bool isSingleton(){return isSource() && isSink();};

	void addJob(Job j){input.push(move(j));};
	size_t inputSize() const {return input.size();};

	Job getJob()
	{
		Job j1 = move(input.front());
		input.pop();
		return j1;
	}

	void Classify(ItemManager& im)
	{
		Installer1 = false;
		Remover1 = false;
		
		for(int i = 0; i < im.getSize(); i++){
			if(getTaskName() == im.getItem(i)->getItemInstallerTask()){
				Installer1 = true;
			}
			if(getTaskName() == im.getItem(i)->getItemRemoverTask()){
				Remover1 = true;
			}
		}
		if(Installer1){cout<<getTaskName()<<" is an Installer"<<endl;}
		if(Remover1){cout<<getTaskName()<<" is an Remover"<< endl;}
		if(Installer1 && Remover1){
			throw getTaskName() + " is both an Installer and a Remover";
		}
	}

	bool getInstaller() const{return Installer1;};
	bool getRemover() const{return Remover1;};
};
