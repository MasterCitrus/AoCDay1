#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

std::vector<std::string> Split(std::string string, std::string delim);
int DistBtwn(int a, int b);

int main()
{
	//Input parsing
	std::ifstream io;
	io.open("input.txt");
	std::vector<std::string> input;
	std::vector<int> leftList;
	std::vector<int> rightList;

	for (std::string line; std::getline(io, line);)
	{
		std::vector<std::string> temp = Split(line, "   ");
		leftList.push_back(std::stoi(temp[0]));
		rightList.push_back(std::stoi(temp[1]));
	}

	std::sort(leftList.begin(), leftList.end(), [](int a, int b) { return a < b; });
	std::sort(rightList.begin(), rightList.end(), [](int a, int b) { return a < b; });


	//Getting distance betwen each list element
	std::vector<int> distances;
	int distance = 0;

	for (std::size_t i = 0; i < rightList.size(); i++)
	{
		distance = DistBtwn(leftList[i], rightList[i]);
		distances.push_back(distance);
	}

	int totalDistance = 0;

	for (auto n : distances) totalDistance += n;

	std::cout << "Total distance: " << totalDistance << std::endl;

	//Parsing for similarity
	int similarityScore = 0;
	std::pair<int, int> countRef = {0,0};
	for (std::size_t i = 0; i < leftList.size(); i++)
	{
		countRef.first = leftList[i];
		countRef.second = 0;
		for (std::size_t j = 0; j < rightList.size(); j++)
		{
			if (rightList[j] == leftList[i]) countRef.second++;
		}
		similarityScore += countRef.first * countRef.second;
	}

	std::cout << "Similarity score: " << similarityScore << std::endl;
}

std::vector<std::string> Split(std::string string, std::string delim)
{
	std::vector<std::string> substrings;
	std::string token;
	while (true)
	{
		std::size_t findFirst = string.find(delim);
		if (findFirst == std::string::npos)
		{
			substrings.push_back(string);
			return substrings;
		}

		token = string.substr(0, string.find(delim));
		string = string.substr(string.find(delim) + delim.size());
		substrings.push_back(token);
	}
	return substrings;
}

int DistBtwn(int a, int b)
{
	if (a < b)
	{
		return b - a;
	}
	else if (b < a)
	{
		return a - b;
	}
	else return 0;
}