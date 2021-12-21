#include <algorithm>
#include <iostream>
#include "printHelpers.h"

void printHelpCommand(const char * commandName, const char * helpString)
{
	std::cout << '\n' << commandName << ": " << helpString;
}

void printHelpSection(std::string sectionName)
{
	std::transform(sectionName.begin(), sectionName.end(), sectionName.begin(), ::toupper);
	std::cout << "\n\n" << sectionName;
}

void printAsk(const char * fieldName)
{
	std::cout << "\n" << fieldName << ": ";
}

void printAnswer(const char * fieldName, const char * result)
{
	std::cout << "\n" << fieldName << ": " << result;
}
