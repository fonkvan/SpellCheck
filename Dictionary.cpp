#include <iostream>
#include <fstream>
#include "Dictionary.h"

Dictionary::Dictionary()
{
	
}

void Dictionary::BuildDictionary(std::string FileName)
{
	std::ifstream File;
	std::string Word;
	try
	{
		File.open(FileName.c_str());
		while (std::getline(File, Word))
		{
			//modulo first char, find place in table, if head key is "" then make key word, else
			//look until the Next is nullptr, create new Node there, and store key into the new node
			int place = ((int)Word[0])%26;
			Word.erase(Word.find_last_not_of(" \n\r\t\f\v") + 1);
			Node* n = &dictionary[place].Head;
			if (n->Key == "")
			{
				n->Key = Word;
			}
			else
			{
				while (n->Next != nullptr)
				{
					n = n->Next;
				}
				Node* NewNode = new Node();
				n->Next = NewNode;
				NewNode->Key = Word;
			}
		}
		File.close();
	}
	catch(std::ifstream::failure e)
	{
		std::cout << "Exception thrown when opening and/or reading and/or closing file " << FileName << std::endl;
		return;
	}
}

bool Dictionary::SearchDictionary(std::string Word)
{
	int place = ((int)Word[0]) % 26;
	Node* n = &dictionary[place].Head;
	while (n != nullptr)
	{
		if (n->Key == Word)
		{
			std::cout << "True" << std::endl;
			return true;
		}
		n = n->Next;
	}
	std::cout << "False" << std::endl;
	return false;
}

void Dictionary::PrintDictionary()
{
	Node* n;
	for (int i = 0; i < 26; ++i)
	{
		n = &(dictionary[i].Head);
		while (n != nullptr)
		{
			std::cout << n->Key << std::endl;
			n = n->Next;
		}
	}
}

void Dictionary::PrintAllSimilarWords(std::string Word)
{
	if (Word.size() == 1)
	{
		std::cout << "No similar words." << std::endl;
		return;
	}
	std::cout << "Similar words to " << Word << ":" << std::endl;
	int place = ((int)Word[0]) % 26;
	Node* n = &dictionary[place].Head;
	while (n != nullptr)
	{
		if (n->Key != Word && n->Key[1] == Word[1])
		{
			std::cout<< n->Key << std::endl;
		}
		n = n->Next;
	}
}

std::string Dictionary::FindPossibleMatch(std::string Word)
{
	double Score = 0.0;
	double TestScore;
	double LengthRatio;
	double LRRecipricol;
	int MatchingCharacters;
	int MatchingPosition;
	int PMMatches = 0;
	std::string PossibleMatch;
	int place = ((int)Word[0]) % 26;
	Node* n = &dictionary[place].Head;
	std::string temp;
	while (n != nullptr)
	{
		TestScore = 0.0;
		LengthRatio = 0.0;
		MatchingCharacters = 0;
		MatchingPosition = 0;
		LRRecipricol = 0.0;
		temp = n->Key;
		LengthRatio = (double)(temp.size())/(double)Word.size();
		LRRecipricol = 1.00/LengthRatio;
		LengthRatio = std::min(LRRecipricol, LengthRatio);
		for (int i = 0; i < Word.size(); ++i)
		{
			for (int j = 0; j < temp.size(); ++j)
			{
				if (Word[i] == temp[j])
				{
					if (i == j)
					{
						++MatchingPosition;
					}
					RemoveCharFromWord(temp, j);
					++MatchingCharacters;
					break;
				}
			}
		}
		TestScore = MatchingCharacters + LengthRatio + MatchingPosition;
		if (TestScore > Score)
		{
			PossibleMatch = n->Key;
			Score = TestScore;
			PMMatches = MatchingCharacters;
		}
		n = n->Next;
	}
	int MaxScore = 1 + (PossibleMatch.size() << 1);
	//0.6 is arbitrary, I just decided 60% accuracy is enough to decide a similar word or not
	if (Score <= 0.6 * MaxScore)
	{
		PossibleMatch = "";
	}
	return PossibleMatch;
}

std::string Dictionary::RemoveCharFromWord(std::string Word, int i)
{
	for (int j = i; j < Word.size() - 1; ++j)
	{
		Word[j] = Word[j+1];
	}
	return Word;
}