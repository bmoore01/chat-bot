#include <ctime>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include "record.hpp"
#include "string_functions.hpp"

std::vector<std::string> readLinesIntoArr(std::ifstream &file) {
		std::string line;
		std::vector<std::string> fileLines;

		while(std::getline(file, line)) {
				fileLines.push_back(line);
		}

		return fileLines;
}

std::vector<Record> getRecords(std::string fileName) {
		const std::string phraseTag = "<phrase>";
		const std::string respTag = "<response>";
		std::vector<Record> records;
		std::vector<std::string> rawFile; 
		std::vector<std::string> splitString; 
		std::string line;
		char delim = '>';
		std::ifstream file("records.txt");
		rawFile = readLinesIntoArr(file);
		Record *curRec;


		for(int i = 0;i < rawFile.size();i++) {
				line = rawFile[i];
				if(line.find(phraseTag) != std::string::npos) { // if this line defines a phrase
						Record tempRec;
						splitString = split(line, delim);
						tempRec.phrase = splitString[1];
						trim(tempRec.phrase);
						records.push_back(tempRec);
						curRec = &records[records.size()-1];
				} else if (line.find(respTag) != std::string::npos) {
						splitString = split(line, delim);
						trim(splitString[1]);
						curRec->responses.push_back(splitString[1]);
				}
		}

		return records;
}

std::string getResponse(std::string input, std::vector<Record> records) {
		std::string response;
		std::vector<std::string> words = split(input, ' ');
		int total = levenshtein_distance(input, records[0].phrase);
		int index = 0;

		// go through each response and each word in the smalles levenshtien distance
		for (int i = 1; i < records.size(); i++) {
				int tempTotal = levenshtein_distance(input, records[i].phrase);
				if(tempTotal <= total) {
						total = tempTotal;
						index = i;
				}
		}

		int randIndex = rand() % records[index].responses.size();
		response = records[index].responses[randIndex];

		return response;
}
 

int main() {
		std::string sInput = "";
		std::string sResponse = "";
		std::ifstream myFile("records.txt");
		std::vector<Record> records;
		records = getRecords("records.txt");

		while(1) {
				std::cout << ">";
				getline(std::cin, sInput);
				if (sInput == "q") break;
				sResponse = getResponse(sInput, records);
				std::cout << sResponse << std::endl;
		}

		return 0;
}
