// Mikian Musser, Word project, V6.0

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include "Word.h"

using namespace std;

int ToBeOrNotToBe::Options[60] = {32,33,39,44,46,63,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122};
unsigned int ToBeOrNotToBe::microseconds = 2000000;

int main(){
	srand(int(time(0)));

	string Target;
	int Popluation;
	int Mutation;
	int CharAmount;
	cout << "Would you like to make your own input? y/n: ";
	char Answer;
	cin >> Answer;

	if (Answer == 'y' || Answer == 'Y'){
		cin.ignore();
		cout << "Target Sentence: ";
		getline(cin,Target);
		cout << "Starting Popluation: ";
		cin >> Popluation;
		cout << "Mutation Rate: ";
		cin >> Mutation;
		cout << "Block Rate: ";
		cin >> CharAmount;
	}
	else
	{
		Target = "We The People Of The United States Of America"; // To be replaced with user input
		Popluation = 250;
		Mutation = 10;
		CharAmount = 15;
	}
	ToBeOrNotToBe G1(Target, Popluation, Mutation, CharAmount);
	G1.Simulation();
	usleep(200000);
	return 0;
}
