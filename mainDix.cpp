#include <iomanip> 
#include <ctime>
#include <cstdlib>

#include "bin_functions.h"
#include "AlgoritmFunctions.h"

#define u unsigned


using namespace std;


//// ZMIENNE INTERFEJSU ////
	
	char arg = '_'; // Argument konsolki
	bool marked = false; // Stan obliczenia grafu (Obliczony / nie obliczony)
	
	char bcgC = '0';
	char charC = '7';
	
	string shl_cmd = "color "; // Komenda windows shell
	
	fstream config; //Strumieñ konfiguracji
	
	string patch; //bufor configu
	string cData; //dane configu
	
	string defGetDir = "GRAPHS/"; //Domyœlna lokalizacja pobierania grafów
	string defSaveDir = "PATHS/"; // Domyœlna lokalizacja zapisywania obliczonej œcie¿ki
	




void setIColor(string item){
	
	char opt;
	char setter;
	
	cout << "\n\n   (1) BLACK     (2) RED";
	cout << "\n   (3) GREEN     (4) BLUE";
	cout << "\n   (5) AQUA      (6) YELLOW";
	cout << "\n   (7) WHITE     (8) GRAY\n";
	cin >> opt;
				  
	switch(opt){
		case '1': setter = '0'; break;
		case '2': setter = 'C'; break;
		case '3': setter = 'A'; break;
		case '4': setter = '9'; break;
		case '5': setter = 'B'; break;
		case '6': setter = 'E'; break;
		case '7': setter = '7'; break;
		case '8': setter = '8'; break;
		}
		
		if(item == "bcg") bcgC = setter;
		else if(item == "char") charC = setter;
		
		shl_cmd = "color "; 
		shl_cmd += bcgC;
		shl_cmd += charC;
}


int main(int argc, char** argv) {
	
	
//// ZMIENNE GRAFU ////


		


	u int start = 0; // Punkt startowy
	u int end; // Punkt koñcowy
	u int idx = 0; // Aktualny index
	char get_next; // Bufor readera
	string fileName;	
	
////////// SPRAWDZENIE PARAMETRÓW //////////	
	
	bool flag = false;
	string saveName;
	bool toFile = false;
	
	
	string param;
	

	
	
	if(argc > 1){
		

		
		string fln = (string) argv[1];
		
		marked = getGraphFile("", arg, fln);
		end = graphSize - 1;
		
		for(int i=2; i<argc; i++){
			
			param = argv[i];
			
			if(param == "-e"){
				end = graph[0].searchByName(argv[(i+1)], graph, graphSize); 
			}
			else if(param == "-f"){
				saveName = (string) argv[(i+1)];
				toFile = true;
			}
			else if(param == "-app"){
				flag = true;
			}
			else if(param == "-q"){
				arg = '4';
			}
					
		}
		
		marked = calculatePath(idx, start, end);
		
		if(toFile) saveCalculated(start, end, saveName, flag);
		else if(arg != '4') showCalculated(start, end);
					
	}
			

////////// ODCZYTYWANIE KONFIGURACJI Z PLIKU //////////

	config.open("dt/config.txt", ios::in);
	
	if(config){
		
		getline(config, patch);
			
		getline(config, cData);		
		bcgC = (char) binToDec(cData);
		
		getline(config, cData);		
		charC = (char) binToDec(cData);	
	
		getline(config, cData);			
		defGetDir = cData;
		
		getline(config, cData);			
		defSaveDir = cData;

		config.close();	
	}
	else{
		cout << "\n < Error > : Cannot load config file... \n\n\n\n";
		system("Pause");
	}


	shl_cmd += bcgC;
	shl_cmd += charC;
	
	system(shl_cmd.c_str());
	shl_cmd = "color ";
	

	while(arg != '4'){
		
	system("cls");
	
	cout << "\n\n            S-WAY GRAPHZ  < BETA > v0.9";
	cout << "\n\n\n     (1) Load Graph         (2) User Manual";
	cout << "\n     (3) Interface Options  (4) Exit\n > ";
	
		cin >> arg;

		if(arg == '1'){ 
		
		////////// ANALIZA PLIKU Z GRAFEM //////////
				
				do {
					
				cout << "\n\n TIP: Type 'ls' to show graphs in default directory";
				cout << "\n\n Instert file name(File must be in the graph's default directory): ";			
				cin >> fileName;
				if(fileName == "ls"){
						string ls = "dir " + defGetDir;
					if(defGetDir[defGetDir.length() - 1] == '/'){
						ls.erase(ls.length() - 1);
					}
					
					cout << " \n\n\n";				
					system(ls.c_str()); 
				}
				else{
					marked = getGraphFile(defGetDir, arg, fileName);
					end = graphSize - 1;	
				}
		
				}while(fileName == "ls");
				
				while(arg != '5'){
					
				////////// PRACA NA GRAFIE //////////
					
				    system("cls");
				    cout << "\n\n     (1) See graph           (2) Set new end point";
				    cout << "\n\n     (3) Show the shortest path";
				    cout << "\n\n     (4) Save shortest path  (5) Exit\n > ";
				    
				  cin >> arg;
				  
				  if(arg == '1') seeGraph();
				  				  
				  else if(arg == '2') { setWayPoint("end", end); marked = false; } 
				  
				  else if(arg == '3' && !marked){
				  	
				  	marked = calculatePath(idx, start, end); 
					showCalculated(start, end);	
				  } 	
				  
				  else if(arg == '3' && marked) showCalculated(start, end);
				else if(arg == '4'){
					string fln;
					cout << "Write the path or file name: ";
					cin >> fln;
					fln = defSaveDir + fln;
					
					if(marked){
						saveCalculated(start, end, fln, false);
					}
					else{
						cout << "\n\n The path is not calculated already...\n\n ";
						system("Pause");
					}
					
				}
						  		  		
		}
		}else if(arg == '2'){
			system("dt\\Documentation.docx");
		}
		else if(arg == '3'){
			cout << "\n\n\n     (1) Set Background color               (2) Set Character color\n";
			      cout << "     (3) Change default graphs directory    (4) Change default paths directory\n";
			      cout << "     (5) Show default directories           (6) Exit\n > ";
			cin >> arg;
			system("cls");
			
			if(arg == '1'){ setIColor("bcg"); system(shl_cmd.c_str()); } 				  
		    else if(arg == '2'){ setIColor("char"); system(shl_cmd.c_str()); } 	
		    else if(arg == '3'){
		    	cout << "\n\n\n Write new Graphs directory: \n\n"
		    		 << " > Notice the directory shouldn't contain any white spaces\n"
		    		 << " > To set global directory leave the field with '/' \n > ";
		    	
		    	cin >> defGetDir;
		    	if(defGetDir == "/") defGetDir = "";
		    	arg = '_';
			}
			else if(arg == '4'){
		    	cout << "\n\n\n Write new Paths directory: \n"
		    		 << " > Notice the directory shouldn't contain any white spaces\n"
		    		 << " > To set global directory leave the field with '/' \n > ";
		    	
		    	cin >> defSaveDir;
		    	if(defSaveDir == "/") defSaveDir = "";
		    	arg = '_';
			}
			else if(arg == '5'){
				cout << "\n\n\n > GRAPHS DIRECTORY: " << defGetDir;
				cout << "\n > PATHS DIRECTORY: " << defSaveDir << " \n\n";
				system("Pause");
			}
		}
	}
		
		
	////////// ZAPIS KONFIGURACJI DO PLIKU //////////
		
		srand(time(0));
		int random;
		
		config.open("dt/config.txt", ios::out | ios::trunc);
		
		if(config){			

			random = rand() % 120;
			config << decToBin(random) << endl;
			
			
			int data = (int) bcgC;
			config << decToBin(data) << endl;
			
			data = (int) charC;
			config << decToBin(data) << endl;
			
			config << defGetDir << endl;
			config << defSaveDir << endl;
					
			random = rand() % 120;
			config << decToBin(random) << endl;		
		}
		

		return 0;
		
	}
	
	
	
	
	
	

