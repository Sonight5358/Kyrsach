#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#include <httplib.h>

std::vector<std::vector<int>> WgFish(const std::string& word1, const std::string& word2)
{	
	size_t w1l, w2l;
	w1l = word1.size();
	w2l = word2.size();

	std::vector<std::vector<int>> mx(w1l + 1, std::vector<int>(w2l + 1));
	for (size_t i = 0; i <= w1l; ++i)
	{
		mx[i][0] = static_cast<int>(i);
	}
	for (size_t j = 0; j <= w2l; ++j)
	{
		mx[0][j] = static_cast<int>(j);
	}

	for (size_t i = 1; i <= w1l; ++i)
	{
		for (size_t j = 1; j <= w2l; ++j)
		{
			int cost = 0;

			if (word1[i - 1] != word2[j - 1])
			{
				cost = 1;
			}
			else
			{
				cost = 0;
			}

			mx[i][j] = std::min({ mx[i - 1][j] + 1, mx[i][j - 1] + 1, mx[i - 1][j - 1] + cost });
		}
	}

	return mx;
}

int main()
{	
	std::string word1, word2;
	std::getline(std::cin, word1);
	std::getline(std::cin, word2);

	std::vector<std::vector<int>> result = WgFish(word1, word2);

	if (!result.empty() && !result[0].empty())
	{
		std::cout << "Distance:" << result.back().back();
	}

	return 0;
}