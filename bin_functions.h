#include <string>
#include <iostream>


std::string decToBin(int num){
	
	if(num == 1) return "1";
	if(num == 0) return "0";
	
	if((num % 2) == 0) return decToBin((num / 2)) + "0";
	else return decToBin((num / 2)) + "1";	
}

int binToDec(std::string bin){
	
	int res = 0;
	int pow = 1;
	
	for(int i = bin.length() - 1; i >= 0; i--){
		res += (int) (bin[i] - '0') * pow;
		pow *= 2;	
	}
	
	return res;
}
