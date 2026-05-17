#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#include "httplib.h"

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
	httplib::Server svr;

	svr.Get("/solve", [](const httplib::Request& req, httplib::Response& res)
		{
			if (req.has_param("word1") && req.has_param("word2"))
			{
				std::string w1 = req.get_param_value("word1");
				std::string w2 = req.get_param_value("word2");

				std::vector<std::vector<int>> matrix = WgFish(w1, w2);

				std::string response_body = "";
				for (size_t i = 0; i < matrix.size(); ++i)
				{
					for (size_t j = 0; j < matrix[i].size(); ++j)
					{
						response_body += std::to_string(matrix[i][j]) + " ";
					}
					response_body += "\n";
				}

				res.set_header("Access-Control-Allow-Origin", "*");
				res.set_content(response_body, "text/plain");
			}
			else
			{
				res.status = 400;
				res.set_content("Error: Please provide word1 and word2 parameters", "text/plain");
			}
		});

	std::cout << "Server successfully started at http://localhost:8080";
	svr.listen("127.0.0.1", 8080);

	return 0;
}