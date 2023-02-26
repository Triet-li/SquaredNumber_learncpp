#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <math.h>


namespace Random // capital R to avoid conflicts with functions named random()
{
	std::mt19937 mt{ std::random_device{}() };

	int get(int min, int max)
	{
		std::uniform_int_distribution range{ min, max }; // we can create a distribution in any function that needs it
		return range(mt); // and then generate a random number from our global generator
	}
}


void getUserInput(int& start, int& num)
{
	std::cout << "Start where: ";
	std::cin >> start;
	std::cout << "How many: ";
	std::cin >> num;
}

void generateSquaredNum(std::vector<int>& squaredNum, int start)
{
	int count = 0;
	for (int i = start; (i-start) != squaredNum.size(); i++)
	{
		squaredNum[count] = i * i;
		++count;
	}
}

void createRandomNum(std::vector<int>& list, int random)
{
	for (auto& i : list)
	{
		i = i * random;
	}
}

void play(std::vector<int>& list, int random)
{
	int userGuess{};
	int count = list.size();
	std::cout << "I generated " << count << " random numbers. Do you know " <<
		"what each number is after multiplying it by " << random << "? \n";

	while (true)
	{
		std::cout << "> ";
		std::cin >> userGuess;
		auto found{ std::find(list.begin(), list.end(), userGuess) };

		if (found == list.end())
		{
			int min = std::abs(userGuess - list[0]);
			int nearestElement = list[0];
			for (auto i : list)
			{
				if (std::abs(i - userGuess) < min)
				{
					min = std::abs(i - userGuess);
					nearestElement = i;
				}
			}
			if (min > 4)
			{
				std::cout << userGuess << " is wrong!\n";
				break;
			}
			else
			{
				std::cout << userGuess << " is wrong! Try " << nearestElement << " next time.\n";
				break;
			}
		}
		else
		{
			--count;
			if (count == 0)
			{
				std::cout << "Nice! You found all numbers, good job!\n";
				break;
			}
			else
			{
				std::cout << "Nice! " << count << " number(s) left.\n";
				list.erase(found);
			}
		}
		


	}
}

int main()
{
	int start, num;
	getUserInput(start, num);
	int random = Random::get(2, 4);
	std::vector<int> squaredNum(num);
	generateSquaredNum(squaredNum, start);
	createRandomNum(squaredNum, random);

	play(squaredNum, random);



	return 0;
}