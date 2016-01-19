#include <iostream>
#include "token.h"
#include <fstream>
#include <thread>

const int numThread = 8;

void compare(int threadNum, int step, int sz, std::vector<tokenList>& list, std::string outName){
	std::ofstream outFile(outName);
	for (int i = threadNum; i < sz; i += step){
		for (int j = i + 1; j < sz; j++){
			std::string tempStr = list[i].compare(list[j]);
			if (tempStr != ""){
				outFile << tempStr << std::endl;
			}
		}
	}
	//std::cout << "Done: " << threadNum << std::endl;
}
/*
void compare(int threadNum, int step, int sz, std::vector<tokenList> list, std::string outName){
	std::ofstream outFile(outName);
	for (int i = threadNum; i < sz; i += step){
		for (int j = i + 1; j < sz; j++){
			outFile << list[i].compare(list[j]) << std::endl;
		}
	}
}*/

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
		if(tokenTemp.sumCount > 50){
			list.push_back(tokenTemp);
		}
		inFileTemp.close();
	}
	hostList.close();
	int sz = list.size();

	//compare(0,1,sz,list,"rawResult");
 	
	std::vector<std::thread*> threads;
	//std::thread threads[numThread];
	for (int i = 0; i < numThread; i++){
		std::string outFileName = "result/" + std::to_string(i);
		threads.push_back(new std::thread(compare, i, numThread, sz, std::ref(list), outFileName));
		//threads[i] = std::thread(compare, i, numThread, sz, std::ref(list), outFileName);
	}
	
	//for (auto& th : threads){
	for (int i = 0; i < numThread; i++){
		threads[i]->join();
		//th.join();
	}
	/*for (auto& th : threads){
		delete th;
	}*/

	hostList.close();
	//outFile.close();
	return 0;
}
