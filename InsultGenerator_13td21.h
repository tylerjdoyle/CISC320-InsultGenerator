/*
 * Assignment 1 by Tyler Doyle (10129777)
 *
 * The declaration file for the InsultGenerator class.
 */
#pragma once

#include <string>
#include <vector>
using namespace std;

class InsultGenerator {
public:
	InsultGenerator(); // Creates an instance of an InsultGenerator
	void initialize(); // Loads all the source phrases from the InsultsSource.txt file into the attributes.
					   // If the file cannot be read, throws an exception.
	string talkToMe() const; // Returns a single insult, generated at random.
	vector<string> generate(const int& bound) const; // Generates the requested number of unique insults.
	void generateAndSave(const string& filename, const int& number) const; // generates the given number of
																		   // insults and saves them to a file
private:
	int numLines; // number of lines in the text file
	vector<string> contentsOne; // contents of the first column
	vector<string> contentsTwo; // contents of the second column
	vector<string> contentsThree; // contents of the third column
	int generateRandom(int limit) const; // Generates a random int to be used to select words for insults
	string findInsult(int& one, int& two, int& three) const; // Creates an insult from given indices
};

class FileException { // Exception to be thrown when a file cannot be read or opened
public:
	FileException(const string& message);
	string& what();
private:
	string message;
};

class NumInsultsOutOfBounds { // Exception to be throw when the number of insults to generate are out of the bounds
public:
	NumInsultsOutOfBounds(const string& message);
	string& what();
private:
	string message;
};

