#pragma once
#include <string>
struct Node
{
	std::string Key = "";
	Node* Next = nullptr;
};

struct LinkedList
{
	Node Head = Node();
};

class Dictionary
{
private:
	LinkedList dictionary[26];
public:
	Dictionary();
	void BuildDictionary(std::string FileName);
	bool SearchDictionary(std::string Word);
	void PrintDictionary();
	void PrintAllSimilarWords(std::string Word);
	std::string FindPossibleMatch(std::string Word);
	std::string RemoveCharFromWord(std::string Word, int i);
};

