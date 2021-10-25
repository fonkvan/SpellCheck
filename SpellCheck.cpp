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
	std::string Response;
	std::cin >> Word;
	std::locale loc;
	float dT = 0.f;
	for (int i = 0; i < Word.length(); ++i)
	{
		Word[i] = std::tolower(Word[i], loc);
	}
	t.Start();
	bool WordFound = d.SearchDictionary(Word);
	if (!WordFound)
	{
		std::string PossibleMatch = d.FindPossibleMatch(Word);
		if (PossibleMatch == "")
		{
			std::cout << "There are no similar words in the dictionary" << std::endl;
		}
		else
		{
			//The reason for this stop is to not account for how long it takes the user to type
			//this interval gets stored and added back in later though
			t.Stop();
			dT = t.GetInterval();
			std::cout << "Did you mean " << PossibleMatch << "?" << std::endl;
			std::cin >> Response;
			for (int i = 0; i < Response.length(); ++i)
			{
				Response[i] = std::tolower(Response[i], loc);
			}
			t.Start();
			if (Response == "no")
			{
				std::cout << "False" << std::endl;
				return(0);
			}
			if (Response == "yes")
			{
				Word = PossibleMatch;
			}
		}
	}
	d.PrintAllSimilarWords(Word);
	t.Stop();
	std::cout << "This process took " << t.GetInterval() + dT << " micro-seconds" << std::endl;
}