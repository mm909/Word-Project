// Mikian Musser, Word project, V6.0

#include "Word.h"
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iomanip>
#include <unistd.h>

using namespace std;

 ToBeOrNotToBe::ToBeOrNotToBe(string Target, int Pop, int Mute, int CharC) {
	TargetWord = Target;
	Popluation = Pop;
	Mutation = Mute;
  CharCount = CharC;
  TotalGenerations = 1;
  AverageFitness = 0;
  firstTime = true;

  if(TargetWord.length() > 44){
    Border = 44 + (TargetWord.length() - 44);
  }
  else {
    Border = 44;
  }

}

void ToBeOrNotToBe::Simulation () {
  PrintStartingData();
  BreakUpSentence();
  for(int i = 0; i < NumberOfParts; i++){
    CurrentString = PartsOfSentence[i];
    RunSimPart(PartsOfSentence[i]);
  }
  PrintMetaData();
}

void ToBeOrNotToBe::BreakUpSentence(){
  if(TargetWord.length() % CharCount == 0)
	{
    NumberOfParts = (TargetWord.length() / CharCount);
    for(int i = 0; i < NumberOfParts; i++){
      PartsOfSentence[i].resize(CharCount);
    }
	}
  else
  {
    NumberOfParts = (TargetWord.length() / CharCount) + 1;
    for(int i = 0; i < NumberOfParts - 1; i++){
      PartsOfSentence[i].resize(CharCount);
    }
    PartsOfSentence[NumberOfParts - 1].resize(TargetWord.length() % CharCount);
  }

	int Index = 0;
	int Part = 0;

	for(int i = 0; i < TargetWord.length(); i++){
		PartsOfSentence[Part][Index] = TargetWord[i];
		Index++;
		if(Index == CharCount){
			Index = 0;
			Part++;
		}
	}
}

string ToBeOrNotToBe::RunSimPart (string Part){
  int PrintCount = 0;
  SetStringLength(Part);
	PopluateSentences(Part);
	while(MaxFitness != Part.length() + 1){
		GetFitness(Part);
		Sort();
		PrintTheBest(Part);
    PrintCount++;
    if(PrintCount == 50 && firstTime){
      cin >> stall;
    }
		PopluateGenePool();
		ChooseParents(Part);
		NewGen();
	}
  PrintData(Part);
  ResetPartVars();
  return Part;
}

void ToBeOrNotToBe::SetStringLength(string Part){
	for (int i = 0; i < 10000; i++){
		Sentences[i].Words.resize(Part.length());
    Children[i].Words.resize(Part.length());
	}
}

void ToBeOrNotToBe::PopluateSentences(string Part){
	int NumberOfChars = Part.length();
	for(int i = 0; i < Popluation; i++){
		for(int j = 0; j < NumberOfChars; j++){
			int Index = ((rand()%58));
			char Letter = Options[Index];
			Sentences[i].Words[j] = Letter;
		}
	}

  for(int i  = 0; i < 10; i++){
    First10[i] = Sentences[i];
  }
}

string ToBeOrNotToBe::RandomizeString(string Part){
  int NumberOfChars = Part.length();
  for(int i = 0; i < NumberOfChars; i++){
    int Index = ((rand()%58));
    char Letter = Options[Index];
    Part[i] = Letter;
  }
  return Part;
}

void ToBeOrNotToBe::GetFitness(string Part){
	for(int i = 0; i < Popluation; i++){ // "Word"
		int Fitness = 1; // Everything has at least 1 fitness (For existing)
		for (int j = 0; j < Part.length(); j++){ // Chars
			if(Sentences[i].Words[j] == Part[j]){
				Fitness++;
			}
      if (Fitness > MaxFitness){
        MaxFitness = Fitness;
      }
		}
		Sentences[i].Fitness = Fitness;
    FitnessSum += Fitness;
    Part_FitnessSum += Fitness;
    Part_FitnessCalcs++;
    FitnessCalcs++;
	}
}

void ToBeOrNotToBe::Sort(){
	for(int j = 0; j < Popluation; j++){
		for (int i = 0; i < Popluation - j; i++) {
			if (Sentences[i].Fitness < Sentences[i + 1].Fitness) {
						int tmp = Sentences[i].Fitness;
						Sentences[i].Fitness = Sentences[i + 1].Fitness;
						Sentences[i + 1].Fitness = tmp;
						string tmp2 = Sentences[i].Words;
						Sentences[i].Words = Sentences[i + 1].Words;
						Sentences[i + 1].Words = tmp2;
			}
		}
	}
}

void ToBeOrNotToBe::PrintSentences(string Part){
	cout << endl;
	for(int i = Popluation - 1; i >= 0; i--){
		cout << setw(Part.length() + 5) << left << Sentences[i].Words
    << "Correct: " << Sentences[i].Fitness << endl;
	}
}

void ToBeOrNotToBe::PrintTheBest(string Part){
//  PrintChars(Sentences[0].Words);
  cout << setw(Part.length() + 5) << left << Sentences[0].Words << setw(5) << left << Sentences[0].Fitness;
  col++;
  if(col == 1)
  {
    cout << endl;
    col = 0;
  }
}

void ToBeOrNotToBe::PrintChars(string Part){
  for(int i = 0; i < Part.length(); i++){
    if(Part[i] == CurrentString[i]){
      system("color 07");
      cout << Part[i];
    }
    else{
      system("color 04");
      cout << Part[i];
    }
  }
//  cout << endl;
}
/*
0 = Black       8 = Gray
1 = Blue        9 = Light Blue
2 = Green       A = Light Green
3 = Aqua        B = Light Aqua
4 = Red         C = Light Red
5 = Purple      D = Light Purple
6 = Yellow      E = Light Yellow
7 = White       F = Bright White
*/

void ToBeOrNotToBe::PopluateGenePool(){
	int GeneIndex = 0;
	for(int i = 0; i < Popluation; i++){
		for(int j = 0; j < Sentences[i].Fitness; j++){
			GenePool[GeneIndex] = i;
			GeneIndex++;
		}
	}
	GeneCount = GeneIndex;
}

void ToBeOrNotToBe::ChooseParents(string Part){
	int ParentOne;
	int ParentTwo;
	for(int i = 0; i < Popluation; i++){
		ParentOne = GenePool[(rand()%GeneCount)];
		ParentTwo = GenePool[(rand()%GeneCount)];
		Reproduse(ParentOne, ParentTwo, Part);
	}
}

void ToBeOrNotToBe::Reproduse(int One, int Two, string Part){
	string ParentOne = Sentences[One].Words;
	string ParentTwo = Sentences[Two].Words;

	static int ChildIndex = 0;

  for(int i = 0; i < Part.length(); i++){
    if(i%2 == 0)
    {
      Children[ChildIndex].Words[i] = ParentOne[i];
    }
    else
    {
      Children[ChildIndex].Words[i] = ParentTwo[i];
    }
  }

  Mutate(ChildIndex);

	ChildIndex++;
	if(ChildIndex == Popluation)
  {
		ChildIndex = 0;
	}
}

void ToBeOrNotToBe::Mutate(int Index){
	for(int i = 0; i < Children[Index].Words.length(); i++){ // Chars
		int MutationChance = (rand()%1000) + 1;
		if(MutationChance <= Mutation)
		{
			int AsciiIndex = ((rand()%58));
			char Letter = Options[AsciiIndex];
			Children[Index].Words[i] = Letter;
		}
	}
}

void ToBeOrNotToBe::NewGen(){
	for(int i = 0; i < Popluation; i++){
		Sentences[i] = Children[i];
	}
  TotalGenerations++;
  Part_Generations++;
}

void ToBeOrNotToBe::ResetPartVars(){
  MaxFitness = 0;
  Part_FitnessSum = 0;
  Part_FitnessCalcs = 0;
  Part_AverageFitness = 0;
  Part_Generations= 0;
}

void ToBeOrNotToBe::PrintStartingData(){
  cout << endl;
  for(int i = 0; i < 10; i++){
    cout << RandomizeString(TargetWord) << endl << endl;
  }
  cin >> stall;
}

void ToBeOrNotToBe::PrintData(string Part){
  Part_AverageFitness = Part_FitnessSum / Part_FitnessCalcs;

  cout << setfill('=') << setw(44) << "=" << setfill(' ') << endl;
  cout << setw(30) << "Average Fitness: " << Part_AverageFitness << endl;
  cout << setw(30) << "Number of Generations: " << Part_Generations << endl;
  cout << setw(30) << "Starting Sentence: " << First10[0].Words << endl;
  cout << setw(30) << "Ending Sentence: " << Part << endl;
  cout << setfill('=') << setw(44) << "=" << setfill(' ') << endl;

  cout << setw(30) << "First Ten:" << setw(30) << "Final Ten:" << endl;

  Sentences[9].Words = Part;
  for(int i = 0; i < 10; i++){
    cout << setw(30) << First10[i].Words << setw(30) << Sentences[i].Words << endl;
  }
  if(firstTime){
    cin >> stall;
    firstTime = false;
  } else {
  sleep(1);
  }
}

void ToBeOrNotToBe::PrintMetaData(){
  AverageFitness = FitnessSum / FitnessCalcs;
  //this->Stop();
  cout << setfill('=') << setw(44) << "=" << setfill(' ') << endl;
  cout << endl;
  cout << setw(30) << "Average Fitness: " << AverageFitness << endl;
  cout << setw(30) << "Number of Generations: " << TotalGenerations << endl;
//  cout << setw(30) << "Time Elapsed: " << ElapsedTime() << " Seconds." << endl;
  cout << endl;
  cout << "Starting Sentence: " << endl;
  cout << RandomizeString(TargetWord) << endl;
  cout << endl;
  cout << "Ending Sentence: " << endl;
  cout << TargetWord << endl;
}
