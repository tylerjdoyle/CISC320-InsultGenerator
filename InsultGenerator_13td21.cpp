/*
 * Assignment 1 by Tyler Doyle (10129777)
 *
 * The implementation of the InsultGenerator object.
 */
#include "InsultGenerator_13td21.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <time.h>

using namespace std;

FileException::FileException(const string& message) : message(message) {}
string& FileException::what() { return message; }

NumInsultsOutOfBounds::NumInsultsOutOfBounds(const string& message) : message(message) {}
string& NumInsultsOutOfBounds::what() { return message; }

InsultGenerator::InsultGenerator() : numLines(0) {}

void InsultGenerator::initialize() {
	ifstream fileIn("InsultsSource.txt");
	string word;
	int count(1);
	if (fileIn.fail())
		throw FileException("File cannot be read.");
	while (fileIn >> word) {
		if (count == 1)
			contentsOne.push_back(word);
		else if (count == 2)
			contentsTwo.push_back(word);
		else {
			contentsThree.push_back(word);
			count = 0;
			numLines++;
		}
		count++;
	}
	srand(time(NULL)); // seeds random number generation
}

int InsultGenerator::generateRandom(int limit) const {
	return rand() % limit;
}

string InsultGenerator::talkToMe() const {
	string insult("Thou ");
	int one = generateRandom(numLines);
	int two = generateRandom(numLines);
	int three = generateRandom(numLines);
	return findInsult(one, two, three);
}

string InsultGenerator::findInsult(int& one, int& two, int& three) const {
	return "Thou " + contentsOne.at(one) + " " + contentsTwo.at(two) + " " + contentsThree.at(three) + "!";
}

vector<string> InsultGenerator::generate(const int& bound) const {
	if (bound < 1 || bound > 10000)
		throw NumInsultsOutOfBounds("The requested number of insults is out of the bounds. (1 - 10 000 inclusive)");
	vector<string> insults;
	bool insultOrder[numLines][numLines][numLines]; // used to have insults appear alphabetically
	int i,j,k;
		for (i = 0; i < numLines; i++)
			for (j = 0; j < numLines; j++)
				for (k = 0; k < numLines; k++)
					insultOrder[i][j][k] = 1; // initialize the array to true
	int numGenerated(0);
	int one, two, three;
	while (numGenerated < bound) {
		one = generateRandom(numLines);
		two = generateRandom(numLines);
		three = generateRandom(numLines);
		//cout << numGenerated << endl;
		if (insultOrder[one][two][three]) {
			insultOrder[one][two][three] = false;
			numGenerated++;
		}
	}
	//int i,j,k;
	for (i = 0; i < numLines; i++)
		for (j = 0; j < numLines; j++)
			for (k = 0; k < numLines; k++)
				if (!insultOrder[i][j][k])
					insults.push_back(findInsult(i, j, k));
	return insults;
}

void InsultGenerator::generateAndSave(const string& filename, const int& numInsults) const {
	vector<string> insults;
	insults = generate(numInsults); // will check the bounds in generate()
	ofstream outFile(filename.c_str());
	if (outFile.fail())
		throw FileException("Output file cannot be written.");
	for (int i = 0; i < numInsults; i++)
		outFile << insults.at(i) << endl;
	outFile.close();
}

