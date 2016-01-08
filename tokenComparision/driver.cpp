#include <iostream>
#include "token.h"
#include <fstream>


int main(int argc, char* argv[]){
	std::vector<tokenList> list;
	std::ifstream hostList(argv[1]);
	std::string str;
	while (std::getline(hostList, str)){
		std::ostringstream sstr;
		sstr << argv[2] << str;
		std::ifstream inFileTemp (sstr.str());
		tokenList tokenTemp(str);
		std::string strTemp;
		while (inFileTemp){
			inFileTemp >> tokenTemp;
		}
		list.push_back(tokenTemp);
		inFileTemp.close();
	}
	hostList.close();
	return 0;
}
