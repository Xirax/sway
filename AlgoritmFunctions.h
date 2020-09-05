#include <windows.h>
#include <fstream>
#include <iostream>
#include <string>

#include "SourceClass.h"

#define UINT_LAST 4294967294


	DPOINT * graph; // tablica punktów klasy DPOINT	
	unsigned int graphSize; // Rozmiar grafu



bool getGraphFile(string graphs_path, char &arg, string fileNm){ // £ADOWANIE GRAFU Z PLIKU
													   
	
	string fileName; // Nazwa pliku
	string filePath = graphs_path; // Œcie¿ka dostêpu
	
	unsigned int nghsCountTemp; // Tymczasowa zmienna liczby s¹siadów 
	string * nghsTemp; // Tymczasowa tablica s¹siadów 
	unsigned int * nghsCostTemp; // Tymczasowa zmienna kosztu dojœcia
	
	unsigned int II; // Zewnêtrzny iterator pêtli I
	unsigned int JJ; // Zewnêtrzny iterator pêtli J
	
	
	//// ZMIENNE STREAM READERA ////
	
	fstream reader; // Czytnik danych z pliku
	
	string graphSizeStr; // Rozmiar grafu tekstowo
	string nghsCountStr; // Licznik s¹siadów tekstowo
	string pCost = ""; // Koszt dojœcia tekstowo
	
	string pName; // Nazwa pojedynczego punktu 
	string nghName; // Nazwa pojedynczego s¹siada
	char get_next; // Bufor readera	
	

	filePath += fileNm;
	reader.open(filePath.c_str());
				
	if(reader){
				
	try{
					
		getline(reader, graphSizeStr); // Pobranie rozmiaru grafu
		graphSize = std::stoul(graphSizeStr); // Zamiana string na int 	
		graph = new DPOINT[graphSize]; // Utworzenie tablicy z grafem
				
																	
		for(unsigned int i=0; i<graphSize; i++){
					
			II = i+1;
					
			getline(reader, nghsCountStr); // Pobranie liczby s¹siaduj¹cych punktów						
			nghsCountTemp = stoul(nghsCountStr); // Konwersja na liczbê
								
			nghsTemp = new string[nghsCountTemp];
			nghsCostTemp = new unsigned int[nghsCountTemp];
						
			pName = "";
					
			reader >> get_next;
					
			do{
		
				pName += get_next;
				reader >> get_next;
						
			}while(get_next != '-');
					
					
			for(unsigned int j=0; j<nghsCountTemp; j++){
						
				JJ = j+1;
						
				while(get_next == '-') reader >> get_next; //Pomijamy separatory
				while(get_next != '-'){ pCost += get_next; reader >> get_next; } // Zbieramy Koszt dojœcia
				while(get_next == '-') reader >> get_next;  // Pomijamy sepraratory
						
				string buf = "";
						
				getline(reader, buf);
				nghName = get_next + buf; //Dla nazw d³u¿szych ni¿ jedna litera musimy doczytaæ ca³¹ liniê
		
				if(j<(nghsCountTemp-1)) while(get_next != '-') reader >> get_next; 	
				nghsTemp[j] = nghName;
				nghsCostTemp[j] = stoul(pCost);
												
				pCost = "";
				nghName = "";
			    
			}
						
			graph[i].initPoint(pName, nghsCountTemp, nghsTemp, nghsCostTemp); // Inicjalizacja punktu grafu
												
			delete [] nghsTemp; // Czyœcimy tymczasowych s¹siadów
			delete [] nghsCostTemp; // Czyœcimy tymczasowe koszty
		}
				
		reader.close();
	}catch(...){
		cout << "\n\n < Error > : Some incorrect data encountered while loading point [ " << II << " ] at neigbor [ " << JJ << " ]";
		cout << "\n Check the data before next run\n";
		system("Pause");
		arg = '5';
	}
							
	return false;
	
}
else{
	cout << "\n\n < Error > : Can't open the file, try again\n\n ";
	system("Pause");
				
}
}



void seeGraph(){ // WYŒWIETLANIE GRAFU
	
	system("cls");
	for(unsigned int i=0; i<graphSize; i++){
		cout << " \n";
						
	    for(unsigned int j=0; j<graph[i].getNumOfNghs(); j++){
			cout << " \n";
			cout << graph[i].name << "---" << graph[i].getNameOfNghs(j) 
			     << " ( " << graph[i].getNghsCost(j) << " )";
		}		
		}					
		cout << "\n\n\n ";
		system("Pause");
}



void setWayPoint(string locName, unsigned int &point){
	
	system("cls");
	string newNm = "";
					
	cout << "\n\n Write the correct name of new " << locName << " item: ";
	cin >> newNm;
    point = graph[0].searchByName(newNm, graph, graphSize); //Wyszukuje index nowego punktu pocz¹tkowego
	cout << "\n > Now the " << locName << " point is " << graph[point].name << "\n\n\n ";
	system("Pause");
		
}


void saveCalculated(unsigned int start, unsigned int end, string flName, bool flag){
				
	unsigned int x = end;
	
	fstream fl;
	
	if(flag) fl.open(flName.c_str(), ios::out | ios::app);
	else fl.open(flName.c_str(), ios::out | ios::trunc);
	
		
	if(fl){		
		if(flag) fl << endl;
		while(graph[x].name != graph[start].name){
		fl << graph[x].name << " ---> ";
		x = graph[x].searchByName(graph[x].getPrev(), graph, graphSize);
	}

	fl << graph[x].name;
	fl << " ( " << graph[end].wayCost() << " )";
	}
	else{
		cout << "\n\n < Error > : Can't save the data, try again... \n\n";
		system("Pause");
	}
	
	fl.close();						
}

void showCalculated(unsigned int start, unsigned int end){
	
	system("cls");
	cout << "\n\n\n  ";						
	unsigned int x = end;
				
	while(graph[x].name != graph[start].name){
	cout << graph[x].name << " ---> ";
	x = graph[x].searchByName(graph[x].getPrev(), graph, graphSize);
	}
	cout << graph[x].name;
	cout << " ( " << graph[end].wayCost() << " )";
				
	cout << "\n\n\n ";
	system("Pause"); 	
}


bool calculatePath(unsigned int &idx, unsigned int start, unsigned int end){
	
		idx = start; // Index na pierwszy punkt
					
		graph[idx].setPrev(graph[idx].name, 0);
		graph[idx].stage();
			
		float per = 0;
		float perJ = (float) (100 / graphSize);
					
		unsigned int new_way;
		unsigned int act_way;
		unsigned int sml = UINT_LAST;			
		unsigned int nghsPlace;
			
		for(unsigned int i=0; i<graphSize; i++){
						
			system("cls");
			per += perJ;
			cout << "\n\n  PROGRESS: " << per << "%";
		
			for(unsigned int j=0; j<graph[idx].getNumOfNghs(); j++){
					
				nghsPlace = graph[idx].searchByName(graph[idx].getNameOfNghs(j), graph, graphSize); // Miejsce s¹siada w tablicy sprawdzane po jego nazwie
					
				if(graph[nghsPlace].staged()) continue;
					
				new_way = graph[idx].getNghsCost(j) + graph[idx].wayCost(); // Nowa œcie¿ka do Punktu
				act_way = graph[nghsPlace].wayCost(); // Obecna œcie¿ka do punktu
										
				if(new_way < act_way){ graph[nghsPlace].setPrev(graph[idx].name, new_way); }					
			}
						
				
			for(unsigned int k=0; k<graphSize; k++){ //Ustalenie najmniejszego po³¹czenia
				if(sml > graph[k].wayCost() && !graph[k].staged()){
					sml = graph[k].wayCost();
					idx = k;
			}
		}
										
		sml = UINT_LAST; // Przywrócenie wartoœci zmiennej tymczasowej sml
		graph[idx].stage();	// Zatwierdzenie punktu i wy¿ucenie go z obiegu															
	}			
	return true;
}

