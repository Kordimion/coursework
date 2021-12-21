#include "labEndpoints.h"
#include "printHelpers.h"

#include <iostream>
#include <algorithm>
#include <chrono>
#include "helperFunctions.h"
#include <functional>

#define ARR_LENGTH 100

int arr[ARR_LENGTH];
int sortedArr[ARR_LENGTH];

constexpr auto REFILL = "refill";
constexpr auto SWAP = "swap";
constexpr auto COMPARE_SORTS = "sort_array";
constexpr auto MIN_MAX = "minmax";
constexpr auto MEDIAN = "median";
constexpr auto COMPARE_ARRAY_SEARCH = "array_search";
constexpr auto MORE_THAN = "more";
constexpr auto LESS_THAN = "less";
constexpr auto HELP = "help";

void refill()
{
	fillWithRandomIntegers(arr, arr + ARR_LENGTH);
	std::copy_n(arr, ARR_LENGTH, sortedArr);
	std::sort(sortedArr, sortedArr + ARR_LENGTH);
}

void printLab2Help()
{
	std::cout << "\nall commands:";

	printHelpSection("setup");
	printHelpCommand(REFILL, "refill array with random integers");

	printHelpSection("value manipulation");
	printHelpCommand(SWAP, "swap items in array in 2 given positions");

	printHelpSection("sorting");
	printHelpCommand(COMPARE_SORTS, "compare sort algorithms");

	printHelpSection("searching");
	printHelpCommand(MEDIAN, "find positions of numbers");
	printHelpCommand(COMPARE_ARRAY_SEARCH, "compare ways of searching value in sorted array");
	printHelpCommand(MORE_THAN, "find amount of values more than given in sorted array");
	printHelpCommand(LESS_THAN, "find amount of values less than given in sorted array");
	printHelpCommand(MIN_MAX, "compare speed of searching min and max element in sorted and unsorted arrays");
	std::cout << "\n";
}

bool lab2Endpoints(const std::string& command)
{
	if (command == REFILL)
	{
		refill();
	}
	else if (command == SWAP)
	{
		int a, b;
		std::cin >> a >> b;

		const auto startTime = std::chrono::steady_clock::now();

		const int temp = arr[a];
		arr[a] = arr[b];
		arr[b] = temp;

		const auto endTime = std::chrono::steady_clock::now();

		const long long nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();

		std::cout << "swapping elements took " << nanoseconds << " nanoseconds\n";
	}
	else if (command == COMPARE_SORTS) 
	{
		std::cout << "select sorting algorithm:\n"
			<< "write one number\n"
			<< "1. bubble sort\n"
			<< "2. shaker sort\n"
			<< "3. insertion sort\n"
			<< "4. comb sort\n"
			<< "5. quick sort\n";

		int sortingAlgorithm;
		std::cin >> sortingAlgorithm;

		int copiedArray[ARR_LENGTH];
		std::copy_n(arr, ARR_LENGTH, copiedArray);

		std::function<void(int*, int*)> sortingFunction;
		const char* sortingName;

		switch (sortingAlgorithm)
		{
		case 1:
			sortingFunction = bubbleSort;
			sortingName = "bubble sort";
			break;
		case 2:
			sortingFunction = shakerSort;
			sortingName = "shaker sort";
			break;
		case 3:
			sortingFunction = insertSort;
			sortingName = "insert sort";
			break;
		case 4:
			sortingFunction = combSort;
			sortingName = "comb sort";
			break;
		case 5:
			sortingFunction = quickSort;
			sortingName = "quick sort";
			break;
		default:
			std::cout << "wrong input\n";
			return true;
		}

		std::cout << "\nUnsorted:\n";
		for (int a : copiedArray)
			std::cout << a << ' ';

		const auto startedTime = std::chrono::steady_clock::now();
		sortingFunction(copiedArray, copiedArray + ARR_LENGTH);
		const auto endedTime = std::chrono::steady_clock::now();

		std::cout << "\nSorted:\n";
		for (int a : copiedArray)
			std::cout << a << ' ';

		const auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(endedTime - startedTime).count();

		std::cout << '\n' << sortingName << " took " << microseconds << " microseconds\n";
	}
	else if (command == MIN_MAX)
	{
		{
			const auto startedTime = std::chrono::steady_clock::now();
			int minElem = INT32_MAX;
			int maxElem = INT32_MIN;
			for (int i = 0; i < ARR_LENGTH; ++i)
			{
				if (arr[i] > maxElem) maxElem = arr[i];
				if (arr[i] < minElem) minElem = arr[i];
			}
			const auto endedTime = std::chrono::steady_clock::now();

			const auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(endedTime - startedTime).count();
			std::cout << "unsorted minmax search took " << nanoseconds << " nanoseconds\n";
		}
		{
			const auto startedTime = std::chrono::steady_clock::now();
			int minElem = sortedArr[0];
			int maxElem = sortedArr[ARR_LENGTH - 1];
			const auto endedTime = std::chrono::steady_clock::now();

			const auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(endedTime - startedTime).count();
			std::cout << "sorted minmax search took " << nanoseconds << " nanoseconds\n";
		}
	}
	else if (command == COMPARE_ARRAY_SEARCH)
	{
		int a;
		std::cin >> a;
		{
			const auto startedTime = std::chrono::steady_clock::now();
			bool found = false;
			for (int* i = sortedArr; i - sortedArr < ARR_LENGTH; ++i)
				if (*i == a)
				{
					found = true;
					break;
				}
			const auto endedTime = std::chrono::steady_clock::now();
			const auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(endedTime - startedTime).count();

			std::cout << "item " << (found ? "" : "not ") << "found\n";
			std::cout << "linear search took " << nanoseconds << " nanoseconds\n";
		}
		{
			const auto startedTime = std::chrono::steady_clock::now();
			bool found = false;
			int l = 0;
			int r = ARR_LENGTH;
			while (l < r) {
				int mid = l + (r - l) / 2;
				if (a > sortedArr[mid]) {
					l = mid + 1;
				}
				else {
					r = mid;
				}
			}

			found = a == sortedArr[l];
			const auto endedTime = std::chrono::steady_clock::now();
			const auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(endedTime - startedTime).count();

			std::cout << "\nitem " << (found ? "" : "not ") << "found\n";
			std::cout << "binary search took " << nanoseconds << " nanoseconds\n";
		}
	}
	else if (command == MEDIAN)
	{
		int minElem = INT32_MAX;
		int maxElem = INT32_MIN;
		for (int i = 0; i < ARR_LENGTH; ++i)
		{
			if (arr[i] > maxElem) maxElem = arr[i];
			if (arr[i] < minElem) minElem = arr[i];
		}

		const int median = (maxElem + minElem) / 2;
		std::cout << "median: " << median << '\n';
		int count = 0;

		std::cout << "indexes: ";
		for (int i = 0; i < ARR_LENGTH; ++i)
			if (arr[i] == median)
			{
				++count;
				std::cout << i << ' ';
			}

		std::cout << "\ntotal elements: " << count << '\n';
	}
	else if (command == MORE_THAN)
	{
		int b;
		std::cin >> b;
		int* upperPos = binarySearchUpperBound(sortedArr, sortedArr + ARR_LENGTH, b);
		std::cout << "there are " << sortedArr + ARR_LENGTH - upperPos
			<< " items more than " << b << '\n';
	}
	else if (command == LESS_THAN)
	{
		int b;
		std::cin >> b;
		int* lowerPos = binarySearchLowerBound(sortedArr, sortedArr + ARR_LENGTH, b);
		std::cout << "there are " << lowerPos - sortedArr
			<< " items less than " << b << '\n';
	}
	else if(command == HELP)
	{
		printLab2Help();
	}
	else
	{
		return false;
	}

	return true;
}
