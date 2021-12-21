#include <iostream>
#include <algorithm>
#include "printHelpers.h"
#include "helperFunctions.h"
#include "labEndpoints.h"

constexpr auto MATRIX_SIZE = 10;

constexpr auto RESIZE = "resize";
constexpr auto ADD = "+";
constexpr auto SUBTRACT = "-";
constexpr auto DIVIDE = "/";
constexpr auto MULTIPLY = "*";
constexpr auto SPIRAL = "fill_spiral";
constexpr auto SNAKE = "fill_snake";
constexpr auto VERTICAL = "transform_vertical";
constexpr auto HORIZONTAL = "transform_horizontal";
constexpr auto ROTATE = "transform_rotate";
constexpr auto DIAGONAL = "transform_diagonal";
constexpr auto INDIVIDUAL = "individual";
constexpr auto SORT = "sort";
constexpr auto HELP = "help";

int arrSize;
int matrix[MATRIX_SIZE][MATRIX_SIZE];

void printLab3Help()
{
	std::cout << "\nall commands:";

	printHelpSection("setup");
	printHelpCommand(RESIZE, "changes size of the matrix and sets it's values to 0");
	printHelpCommand(SPIRAL, "fills array using the spiral pattern");
	printHelpCommand(SNAKE, "fills array using the snake pattern");

	printHelpSection("element manipulation");
	printHelpCommand(ADD, "add constant value to each element of the matrix");
	printHelpCommand(SUBTRACT, "subtract constant value to each element of the matrix");
	printHelpCommand(DIVIDE, "divide each element of matrix to the constant value");
	printHelpCommand(MULTIPLY, "multiply each element of matrix to the constant value");

	printHelpSection("array manipulation");
	printHelpCommand(VERTICAL, "swaps blocks of the array vertically");
	printHelpCommand(HORIZONTAL, "swaps blocks of the array horizontally");
	printHelpCommand(DIAGONAL, "swaps blocks of the array diagonally");
	printHelpCommand(ROTATE, "rotates the array blocks clockwise");
	printHelpCommand(SORT, "sorts rows of array");

	std::cout << "\n";
}

void printIntArrResult(const int(*arr)[10], int size)
{
	std::cout << "resulting array: \n";

	for (int i = 0; i < size; ++i)
	{
		std::cout << '\n';
		for (int j = 0; j < size; ++j)
			printf("%3d", arr[i][j]);
	}

	std::cout << "\n\n";
}

bool lab3Endpoints(const std::string& command)
{
	if (command == RESIZE)
	{
		int size;
		std::cin >> size;

		arrSize = size;

		for (int i = 0; i < arrSize; ++i)
			for (int j = 0; j < arrSize; ++j)
				matrix[i][j] = 0;

		printIntArrResult(matrix, arrSize);
	}
	else if (command == ADD)
	{
		int num;
		std::cin >> num;

		for (int i = 0; i < arrSize; ++i)
			for (int j = 0; j < arrSize; ++j)
				matrix[i][j] += num;

		printIntArrResult(matrix, arrSize);
	}
	else if (command == SUBTRACT)
	{
		int num;
		std::cin >> num;

		for (int i = 0; i < arrSize; ++i)
			for (int j = 0; j < arrSize; ++j)
				matrix[i][j] -= num;

		printIntArrResult(matrix, arrSize);
	}
	else if (command == MULTIPLY)
	{
		int num;
		std::cin >> num;

		for (int i = 0; i < arrSize; ++i)
			for (int j = 0; j < arrSize; ++j)
				matrix[i][j] *= num;

		printIntArrResult(matrix, arrSize);
	}
	else if (command == DIVIDE)
	{
		int num;
		std::cin >> num;

		for (int i = 0; i < arrSize; ++i)
			for (int j = 0; j < arrSize; ++j)
				matrix[i][j] /= num;

		printIntArrResult(matrix, arrSize);
	}
	else if (command == SNAKE)
	{
		int current = 1;
		for (int i = 0; i < arrSize; i += 2)
		{
			for (int column = 0; column < arrSize; ++column, ++current)
				matrix[column][i] = current;

			for (int column = arrSize - 1; column >= 0; --column, ++current)
				matrix[column][i + 1] = current;
		}

		printIntArrResult(matrix, arrSize);
	}
	else if (command == SPIRAL)
	{
		int current = 1;

		for (int i = 0; i < arrSize / 2; ++i)
		{
			for (int j = i; j < arrSize - 1 - i; ++j, ++current)
				matrix[i][j] = current;

			for (int j = i; j < arrSize - 1 - i; ++j, ++current)
				matrix[j][arrSize - i - 1] = current;

			for (int j = i; j < arrSize - 1 - i; ++j, ++current)
				matrix[arrSize - i - 1][arrSize - j - 1] = current;

			for (int j = i; j < arrSize - 1 - i; ++j, ++current)
				matrix[arrSize - j - 1][i] = current;
		}

		if (arrSize % 2 == 1) matrix[arrSize / 2][arrSize / 2] = current;

		printIntArrResult(matrix, arrSize);
	}
	else if (command == VERTICAL)
	{
		const int halfArraySize = arrSize / 2;

		for (int i = 0; i < halfArraySize; ++i)
			for (int j = 0; j < arrSize; ++j)
				std::swap(matrix[i][j], matrix[i + halfArraySize][j]);

		printIntArrResult(matrix, arrSize);
	}
	else if (command == DIAGONAL)
	{
		const int halfArraySize = arrSize / 2;

		for (int i = 0; i < halfArraySize; ++i)
			for (int j = 0; j < halfArraySize; ++j)
				std::swap(matrix[i][j], matrix[i + halfArraySize][j + halfArraySize]);

		for (int i = arrSize / 2; i < arrSize; ++i)
			for (int j = 0; j < halfArraySize; ++j)
				std::swap(matrix[i][j], matrix[i - halfArraySize][j + halfArraySize]);

		printIntArrResult(matrix, arrSize);
	}
	else if (command == HORIZONTAL)
	{
		const int halfArraySize = arrSize / 2;

		for (int i = 0; i < arrSize; ++i)
			for (int j = 0; j < halfArraySize; ++j)
				std::swap(matrix[i][j], matrix[i][j + halfArraySize]);

		printIntArrResult(matrix, arrSize);
	}
	else if (command == ROTATE)
	{
		const int halfArraySize = arrSize / 2;

		for (int i = 0; i < halfArraySize; ++i)
		{
			for (int j = 0; j < halfArraySize; ++j)
			{
				const int saved = matrix[i][j];
				matrix[i][j] = matrix[i + halfArraySize][j];
				matrix[i + halfArraySize][j] = matrix[i + halfArraySize][j + halfArraySize];
				matrix[i + halfArraySize][j + halfArraySize] = matrix[i][j + halfArraySize];
				matrix[i][j + halfArraySize] = saved;
			}
		}

		printIntArrResult(matrix, arrSize);
	}
	else if (command == SORT)
	{
		const int halfArraySize = arrSize / 2;

		for (int i = 0; i < halfArraySize; ++i)
			combSort(matrix[i], matrix[i] + arrSize);

		printIntArrResult(matrix, arrSize);
	}
	else if (command == HELP)
	{
		printLab3Help();
	}
	else
	{
		return false;
	}

	return true;
}
