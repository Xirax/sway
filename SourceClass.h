#include <iostream>
#include <string>

using namespace std;

class DPOINT{
	
	unsigned int nghsCount;			
	string * nghs;
	unsigned int * nghsCost;
	
	
	unsigned int sm_cost;
	string last_ID;
	


	
	public:
		string name;
		bool isSet;
	
	DPOINT(){}
	
	void initPoint(string nm, unsigned int neighbors, string nghsTab[], unsigned int nghsCostTab[]){
		
		nghsCount = neighbors;
		name = nm;
		nghs = new string[nghsCount];
		nghsCost = new unsigned int[nghsCount];
		sm_cost = 4294967294;
		isSet = false;
		
		for(int i=0; i<nghsCount; i++){
			
			nghs[i] = nghsTab[i];
			nghsCost[i] = nghsCostTab[i];
		}
		
	}
	
	unsigned int getNumOfNghs(){
		return nghsCount;
	}
	
	string getNameOfNghs(unsigned int index){
		if(index < nghsCount) return nghs[index];
		else return "";
	}
	
	unsigned int getNghsCost(unsigned int index){
		if(index < nghsCount) return nghsCost[index];
		else return -1;
	}
	

	unsigned int searchByName(string nm, DPOINT tab[], unsigned int tabS){
		for(unsigned int i=0; i<tabS; i++){
			if(nm == tab[i].name) return i;	
			else if(i == (tabS - 1)) return 0;		
		}
	}
	
	void setPrev(string last, unsigned int cost){
		last_ID = last;
		sm_cost = cost;
	}
	
	string getPrev(){
		return last_ID;
	}
	
	unsigned int wayCost(){
		return sm_cost;
	}
	
	void stage(){
		isSet = true;
	}
	
	bool staged(){
		return isSet;
	}
	
	void clear(){
		sm_cost = 4294967294;
		isSet = false;
		last_ID = "_";
	}
	
		
};
