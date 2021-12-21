#include <iostream>
#include <map>
#include <string>
#include <functional>

#include "printHelpers.h"
#include "LabLoop.h"

void LabLoop::processLabSelection()
{
	std::string lab;

	std::cout << "\nSelect Lab";
	std::cout << "\nAvailable labs: | ";
	for (auto& pair : labs)
		std::cout << pair.first << " | "; // print lab name (key)

	printAsk("lab");
	std::cin >> lab;

	if(state.empty())
	{
		
	}

	const auto foundEndpoints = labs.find(lab);

	if (foundEndpoints == labs.end())
	{
		std::cout << "\nInvalid input";
	}
	else {
		std::cout << "\nSelected " << lab;
		state = lab;
	}
}

void LabLoop::processLab(const std::string& labName, const std::function<bool(std::string)>& labEndpoints)
{
	std::string command;
	std::string askString = "command for " + labName;
	printAsk(askString.c_str());
	std::cin >> command;

	if(!labEndpoints(command))
	{
		constexpr auto exitLab = "exit";
		if(command == exitLab)
		{
			std::cout << "\nexited " << labName;
			state = "";
		}
		else
		{
			std::cout << "\nthere is no such command";
			std::cout << "\ntype help to view list of available commands of " << labName;
			std::cout << "\ntype " << exitLab << " to exit " << labName << "\n";
		}
	}
}

void LabLoop::registerLab(const std::string& labName, const std::function<bool(std::string)>& labEndpoints)
{
	labs[labName] = labEndpoints;
}

void LabLoop::start()
{
	std::cout << "Program started\n";

	while(true)
	{
		if(state.empty()) processLabSelection();
		else processLab(state, labs[state]);
	}
}
