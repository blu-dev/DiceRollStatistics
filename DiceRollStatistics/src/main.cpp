#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#define GET_TOTAL(x,y) (size_t)pow(x,y)

void fillCombinations(std::vector<std::vector<size_t>>& combinations, size_t callcount = 0);

std::vector<std::pair<size_t, size_t>> findDuplicates(std::vector<std::vector<std::size_t>>& combinations);

std::vector<std::pair<std::pair<size_t, size_t>, float>> makePercent(std::vector<std::pair<size_t, size_t>>& duplicates);

int main(void)
{
	size_t diceCount, maxValue;
	std::cout << "Enter the amount of dice:";
	std::cin >> diceCount;
	std::cout << "Enter the highest value on the dice:";
	std::cin >> maxValue;
	std::cin.get();
	if (GET_TOTAL(maxValue, diceCount) > 1000)
	{
		std::cout << "Warning! This **may** take up a decent chunk of memory. To continue, press any key." << std::endl;
		std::cin.get();
	}
	std::vector<std::vector<size_t>> combinations(GET_TOTAL(maxValue, diceCount));
	std::cout << combinations.max_size() << std::endl;
	for (size_t i = 0; i < combinations.size(); i++)
	{
		combinations[i] = std::vector<size_t>(diceCount);
	}
	fillCombinations(combinations);
	auto finished = findDuplicates(combinations);
	auto finished2 = makePercent(finished);
	std::cout << "Roll\tCount\tChance" << std::endl;
	for (size_t i = 0; i < finished.size(); i++)
	{
		std::cout << finished2[i].first.first << "\t" << finished2[i].first.second << "\t" << std::fixed << std::setprecision(2) << finished2[i].second * 100 << "%" << std::endl;
	}
	std::cout << "\nPress any key to exit..." << std::endl;
	std::cin.get();
}

void fillCombinations(std::vector<std::vector<size_t>>& combinations, size_t callcount)
{
	size_t total = combinations.size();
	size_t diceCount = combinations[0].size();
	size_t maxValue = GET_TOTAL(total, 1 / (float)diceCount);
	size_t a = 0;
	while (a < total)
	{
		for (size_t i = 1; i <= maxValue; i++)
		{
			for (size_t j = 0; j < GET_TOTAL(maxValue, diceCount - (callcount + 1)); j++)
				combinations[j + a][callcount] = i;
			a += GET_TOTAL(maxValue, diceCount - (callcount + 1));
		}
	}
	if ((int)diceCount - ((int)callcount + 2) > -1)
		fillCombinations(combinations, callcount + 1);
}

std::vector<std::pair<size_t, size_t>> findDuplicates(std::vector<std::vector<std::size_t>> & combinations)
{
	size_t total = combinations.size();
	size_t diceCount = combinations[0].size();
	std::vector<std::pair<size_t, size_t>> ret;
	for (size_t i = 0; i < total; i++)
	{
		size_t sum = 0;
		for (size_t j = 0; j < diceCount; j++)
			sum += combinations[i][j];
		size_t j;
		for (j = 0; j < ret.size(); j++)
		{
			if (ret[j].first == sum)
			{
				ret[j].second += 1;
				break;
			}
		}
		if (j == ret.size())
			ret.push_back(std::make_pair(sum, 1));
	}
	return ret;
}

std::vector<std::pair<std::pair<size_t, size_t>, float>> makePercent(std::vector<std::pair<size_t, size_t>> & duplicates)
{
	size_t sum = 0;
	std::vector<std::pair<std::pair<size_t, size_t>, float>> ret = std::vector<std::pair<std::pair<size_t, size_t>, float>>(duplicates.size());
	for (size_t i = 0; i < duplicates.size(); i++)
		sum += duplicates[i].second;
	for (size_t i = 0; i < duplicates.size(); i++)
		ret[i] = std::make_pair(duplicates[i], (float)duplicates[i].second / sum);
	return ret;
}