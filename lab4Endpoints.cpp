#include <chrono>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

#include "printHelpers.h"
#include "labEndpoints.h"

constexpr auto SCAN_CONSOLE = "console";
constexpr auto SCAN_FILE = "file";
constexpr auto SPACES = "spaces";
constexpr auto PUNCTUATION = "punctuation";
constexpr auto CASING = "casing";
constexpr auto ALL_TRANSFORMATIONS = "transformations";
constexpr auto REPEATING_CHARS = "repeats";
constexpr auto REPLACE_NUMBERS = "replace_numbers";
constexpr auto SUBSTRING = "substr";
constexpr auto HELP = "help";

std::string inputStr;

std::string trim(const std::string& str)
{
	int start = 0;
	int end = str.length() - 1;
	while (str[start] == ' ') ++start;
	while (str[end] == ' ') --end;
	return str.substr(start, end - start + 1);
}

bool wordHasRepeatingChars(std::string word)
{
	for(int i = 0; i < word.length() - 1; ++i)
		for(int j = i + 1; j < word.length(); ++j)
			if (word[i] == word[j]) return true;

	return false;
}

void printWordsWithRepeatingChars(const std::string& str)
{

	bool foundWord = false;
	int begin = 0;
	for (int i = 0; i < str.length(); ++i)
	{
		if(isalpha(str[i]))
		{
			if(!foundWord) begin = i;
			foundWord = true;
		}
		else
		{
			if (foundWord) 
			{
				auto word = str.substr(begin, i - begin);
				if(wordHasRepeatingChars(word))std::cout << word << ' ';
			}
			foundWord = false;
		}
	}
}

void printSubstitutedNumbersWithCorrespondingChars(const std::string& str)
{
	for(const char& ch : str)
	{
		if (isdigit(ch)) std::cout << static_cast<char>(ch - '0' + 'A' - 1);
		else std::cout << ch;
	}
}

std::string leaveOnlyOneSpace(const std::string& str)
{
	std::string res;

	bool foundSpace = true;
	for (const char ch : str)
	{
		if(isspace(ch))
		{
			if (!foundSpace) res += ch;
			foundSpace = true;
		}
		else
		{
			foundSpace = false;
			res += ch;
		}
	}

	return res;
}

std::string removeExcessSpaces(const std::string& str)
{
	return leaveOnlyOneSpace(trim(str));
}

std::string removeExcessPunctuation(const std::string& str)
{
	std::string res;

	bool foundPunctuation = true;
	for (const char ch : str)
	{
		if(ispunct(ch))
		{
			if (!foundPunctuation) res += ch;
			foundPunctuation = true;
		}
		else
		{
			foundPunctuation = false;
			res += ch;
		}
	}

	return res;
}

void fixCasing(std::string& str)
{
	bool foundLetter = false;
	for(int i = 0; str[i]; ++i)
	{
		if (foundLetter && isupper(str[i])) str[i] = tolower(str[i]);
		foundLetter = isalpha(str[i]);
	}
}

std::vector<int> searchLinear(const::std::string& str, std::string substr)
{
	int iter = 0;
	std::vector<int> res;
	for(int i = 0; i < str.length(); ++i)
	{
		if(str[i] == substr[0])
		{
			int j = 0;
			while(j < substr.length() && str[i + j] == substr[j]) j++;
			if(j == substr.length()) res.push_back(i);
		}
	}
	
	return res;
}

std::vector<int> searchKmp(const std::string& str, const std::string& substr)
{
	const auto lps = new int[substr.length()]{};
	std::vector<int> res;
	lps[0] = 0;

	// ReSharper disable once CppTooWideScope
	int longestPrefixSuffix = 0, i = 1;
	while (i < substr.length())
	{
		if (substr[i] == substr[longestPrefixSuffix]) 
		{
			longestPrefixSuffix++;
			lps[i] = longestPrefixSuffix;
			i++;
		}
		else
		{
			if (longestPrefixSuffix == 0) 
			{
				lps[i] = 0;
				i++;
			}
			else 
			{
				longestPrefixSuffix = lps[longestPrefixSuffix - 1];
			}
		}

	}

	int strIter = 0, substrIter = 0;
	while (strIter < str.length()) 
	{
		if (substr[substrIter] == str[strIter]) 
		{
			substrIter++;
			strIter++;
		}

		if (substrIter == substr.length()) 
		{
			res.push_back(strIter - substrIter);
			substrIter = lps[substrIter - 1];
		}
		else if (strIter < str.length() && substr[substrIter] != str[strIter]) 
		{
			if (substrIter != 0)
				substrIter = lps[substrIter - 1];
			else
				strIter = strIter + 1;
		}
	}

	delete[] lps;

	return res;
}

std::vector<int> searchBoyerMoore(const std::string& str, const std::string& substr)
{
	std::vector<int> res;
	constexpr int charsTotal = 256;
	int badCharHeuristic[charsTotal];

	for (int& i : badCharHeuristic) i = -1;

	for (int i = 0; i < substr.length(); ++i)
		badCharHeuristic[substr[i]] = i;

	int shift = 0;
	while (shift <= (str.length() - substr.length()))
	{
		int substrIndex = substr.length() - 1;

		while (substrIndex >= 0 && substr[substrIndex] == str[shift + substrIndex])
			substrIndex--;

		if (substrIndex < 0)
		{
			res.push_back(shift);
			shift += (shift + substr.length() < str.length()) ? substr.length() - badCharHeuristic[shift + substr.length()] : 1;
		}

		else
		shift += std::max(1, substrIndex - badCharHeuristic[str[shift + substrIndex]]);
	}
	return res;
}

void substringSearchBenchmark(const std::string& str, const std::string& substr,
                              const std::function<std::vector<int>(std::string, std::string)> &f)
{
	std::cout << "\nsearching for the substring " << substr;
	std::cout << "\npositions: ";

	const auto startedTime = std::chrono::steady_clock::now();
	const auto positions = f(str, substr);
	const auto endedTime = std::chrono::steady_clock::now();
	const auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(endedTime - startedTime).count();

	for (const int& position : positions)
		std::cout << position << ' ';

	std::cout << "\nthis took: " << microseconds << " microseconds";
}

void printLab4Help()
{
	std::cout << "\nall commands: ";

	printHelpSection("input");
	printHelpCommand(SCAN_CONSOLE, "changes size of the matrix and sets it's values to 0");
	printHelpCommand(SCAN_FILE, "add constant value to each element of the matrix");

	printHelpSection("persistent string transformations");
	printHelpCommand(SPACES, "   remove excess    spaces   ");
	printHelpCommand(PUNCTUATION, "remove?. excess,.. punctuation!?? marks...");
	printHelpCommand(CASING, "rEMOvE wEiRd cASiNg");
	printHelpCommand(ALL_TRANSFORMATIONS, "apply all those transformations");

	printHelpSection("print only string transformations");
	printHelpCommand(REPEATING_CHARS, "shows only 'words' with repeating characters");
	printHelpCommand(REPLACE_NUMBERS, "replaces numbers with corresponding chars. 0 = A, 1 = B, 11 = BB e.t.c.");

	printHelpSection("substring search");
	printHelpCommand(SUBSTRING, "compares substring searching algorithms: naive(linear), KMP and Boyer-Moore");

	std::cout << "\n";
}

void printStringState(const std::string& state)
{
	printAnswer("String state", state.c_str());
}

bool lab4Endpoints(const std::string& command)
{
	if (command == SCAN_CONSOLE)
	{
		printAsk("string");
		std::getline(std::cin, inputStr);

		printStringState(inputStr);
	}
	else if (command == SCAN_FILE)
	{
		std::string fileName;
		printAsk("file name");
		std::cin >> fileName;

		std::ifstream input(fileName);
		std::getline(input, inputStr);

		printStringState(inputStr);
	}
	else if (command == SPACES) 
	{
		inputStr = removeExcessSpaces(inputStr);
		printStringState(inputStr);
	}
	else if (command == PUNCTUATION)
	{
		inputStr = removeExcessPunctuation(inputStr);
		printStringState(inputStr);
	}
	else if (command == CASING) 
	{
		fixCasing(inputStr);
		printStringState(inputStr);
	}
	else if (command == ALL_TRANSFORMATIONS)
	{
		inputStr = removeExcessSpaces(inputStr);
		inputStr = removeExcessPunctuation(inputStr);
		fixCasing(inputStr);
		printStringState(inputStr);
	}
	else if (command == REPEATING_CHARS)
	{
		printWordsWithRepeatingChars(inputStr);
	}
	else if (command == REPLACE_NUMBERS)
	{
		printSubstitutedNumbersWithCorrespondingChars(inputStr);
	}
	else if (command == SUBSTRING)
	{
		std::string substr;
		printAsk("Substring to search for: ");
		std::cin >> substr;

		std::cout << "\n\nNAIVE LINEAR SEARCH: ";
		substringSearchBenchmark(inputStr, substr, searchLinear);

		std::cout << "\n\nKMP SEARCH: ";
		substringSearchBenchmark(inputStr, substr, searchKmp);

		std::cout << "\n\nBOYER-MOORE SEARCH: ";
		substringSearchBenchmark(inputStr, substr, searchBoyerMoore);
	}
	else if(command == HELP)
	{
		printLab4Help();
	}
	else
	{
		return false;
	}


	return true;
}
