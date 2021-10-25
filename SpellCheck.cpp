#include <iostream>
#include <locale>
#include <string>
#include "Dictionary.h"
#include "TimeInterval.h"

int main()
{
	TimeInterval t = TimeInterval();
	Dictionary d = Dictionary();
	d.BuildDictionary("Dictionary.txt");
	//d.PrintDictionary();
	std::cout << "What word would you like to search for?" << std::endl;
	std::string Word;
	std::cin >> Word;
	std::locale loc;
	t.Start();
	for (int i = 0; i < Word.length(); ++i)
	{
		Word[i] = std::tolower(Word[i], loc);
	}
	bool WordFound = d.SearchDictionary(Word);
	if (!WordFound)
	{
		std::string PossibleMatch = d.FindPossibleMatch(Word);
		std::cout << "Did you mean " << PossibleMatch << "?" << std::endl;
	}
	t.Stop();
	std::cout << "This process took " << t.GetInterval() << " micro-seconds" << std::endl;
}