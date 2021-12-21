#pragma once
#include <map>
#include <string>
#include <iostream>
#include <functional>

class LabLoop
{
private:
	std::string state;

	std::map<std::string, std::function<bool(std::string)>> labs;

	void processLabSelection();

	void processLab(const std::string& labName, const std::function<bool(std::string)>& labEndpoints);

public:
	void registerLab(const std::string& labName, const std::function<bool(std::string)>& labEndpoints);

	void start();
};
