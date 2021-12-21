#include "labEndpoints.h"
#include "LabLoop.h"

int main()
{
	LabLoop loop;

	loop.registerLab("lab1", lab1Endpoints);
	loop.registerLab("lab2", lab2Endpoints);
	loop.registerLab("lab3", lab3Endpoints);
	loop.registerLab("lab4", lab4Endpoints);

	loop.start();
}


