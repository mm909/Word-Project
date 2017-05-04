// Mikian Musser, Word project, V6.0

#include <string>
using namespace std;
/*
class Stopwatch {
public:
	Stopwatch(){ Start = time(0); }
	void Stop(){ End   = time(0); }
	double ElapsedTime(){ return (End - Start); }
private:
	clock_t Start;
	clock_t End;
	double Difference;
};
*/
struct Phrase {
public:
		string Words;
		int Fitness;
};

class ToBeOrNotToBe {

public:
	ToBeOrNotToBe(string, int, int, int);
	void Simulation();

private:
	void BreakUpSentence();
	string RunSimPart(string);

	void SetStringLength(string);
	void PopluateSentences(string);
	void GetFitness(string);
	void Sort();
	void PrintSentences(string);
	void PrintTheBest(string);
	void PrintChars(string);
	void PopluateGenePool();
	void ChooseParents(string);
	void Reproduse(int, int, string);
	void Mutate(int);
	void NewGen();

	void PrintData(string);
	void ResetPartVars();
	void PrintMetaData();
	void PrintStartingData();

	string RandomizeString(string);

	static int Options[60];
	static unsigned int microseconds;

	int Border;

	string TargetWord;
	string CurrentString;

	int Mutation;
	int Popluation;
	int NumberOfParts;
	int CharCount;
	int MaxFitness;
	int TotalGenerations;
	double AverageFitness;
	double FitnessSum;
	double FitnessCalcs;

	string PartsOfSentence[50];
	double Part_AverageFitness;
	double Part_FitnessCalcs;
	double Part_FitnessSum;
	int Part_Generations;
	int col;
	bool firstTime;
	string stall;

	Phrase First10[10];
	int GeneCount;
	int GenePool[10000];
	Phrase Children[10000];
	Phrase Sentences[10000];
};
