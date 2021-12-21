#include <iostream>

#include "printHelpers.h"
#include "labEndpoints.h"

#include <iomanip>
#include <iostream>

constexpr auto MEMORY_CONSUMPTION = "memory";
constexpr auto BINARY_FLOAT = "float";
constexpr auto BINARY_INT = "int";
constexpr auto BINARY_DOUBLE = "double";
constexpr auto HELP = "help";

void printTypesMemoryConsumption(std::ostream& out)
{
	out << "Types memory consumption (in bytes)\n";
	out << "int:           " << sizeof(int) << "\n";
	out << "short int:     " << sizeof(short int) << "\n";
	out << "long int:      " << sizeof(long int) << "\n";
	out << "long long int: " << sizeof(long long int) << "\n";
	out << "float:         " << sizeof(float) << "\n";
	out << "double:        " << sizeof(double) << "\n";
	out << "long double:   " << sizeof(long double) << "\n";
	out << "char:          " << sizeof(char) << "\n";
	out << "bool:          " << sizeof(bool) << "\n";
}

constexpr char ORDER_BREAK = '_';

std::string binaryStringView(int value)
{
	std::string res;
	constexpr unsigned int orders = sizeof(value) * 8;
	unsigned int mask = 1U << (orders - 1);
	for (int i = 0; i < orders; ++i)
	{
		if (i != 0 && i % 8 == 0) res += ORDER_BREAK;
		if (i == 1) res += ORDER_BREAK;

		res += (value & mask ? '1' : '0');
		mask >>= 1;
	}
	return res;
}

std::string binaryStringView(float _value)
{
	union {
		int value;
		float num_f;
	};
	num_f = _value;

	constexpr unsigned int orders = sizeof(_value) * 8;
	unsigned int mask = 1U << (orders - 1);
	std::string res;
	for (int i = 0; i < orders; ++i)
	{
		if (i == 1 || i == 9) res += ORDER_BREAK;

		res += (value & mask ? '1' : '0');
		mask >>= 1;
	}
	return res;
}

std::string binaryStringView(double _value)
{
	union {
		long long int value;
		double num_f;
	};
	num_f = _value;

	constexpr unsigned int orders = sizeof(_value) * 8;
	unsigned long long int mask = 1ULL << (orders - 1);
	std::string res;
	for (int i = 0; i < orders; ++i)
	{
		if (i == 1 || i == 12) res += ORDER_BREAK;

		res += (value & mask ? '1' : '0');
		mask >>= 1;
	}
	return res;
}

void printLab1Help()
{
	std::cout << "\nall commands:";

	printHelpSection("memory consumption");
	printHelpCommand(MEMORY_CONSUMPTION, "print memory consumption of common variable types");

	printHelpSection("binary representation");
	printHelpCommand(BINARY_INT, "print int binary representation");
	printHelpCommand(BINARY_FLOAT, "print float binary representation");
	printHelpCommand(BINARY_DOUBLE, "print double binary representation");
	std::cout << "\n";
}

bool lab1Endpoints(const std::string& command)
{
	if (command == MEMORY_CONSUMPTION)
	{
		printTypesMemoryConsumption(std::cout);
	}
	else if (command == BINARY_INT)
	{
		int num;
		printAsk("integer");
		std::cin >> num;
		printAnswer("binary representation", binaryStringView(num).c_str());
	}
	else if (command == BINARY_FLOAT) 
	{
		float num;
		printAsk("float");
		std::cin >> num;
		printAnswer("binary representation", binaryStringView(num).c_str());
	}
	else if (command == BINARY_DOUBLE)
	{
		double num;
		printAsk("double");
		std::cin >> num;
		printAnswer("binary representation", binaryStringView(num).c_str());
	}
	else if(command == HELP)
	{
		printLab1Help();
	}
	else
	{
		return false;
	}

	return true;
}
