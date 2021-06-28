#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <deque>
#include <unordered_set>


class Problem
{
public:

	void ReadGraph(const std::string& fileName)
	{
		std::fstream file(fileName, std::ios::in);

		std::string buf;
		for (int i = 1; std::getline(file, buf); ++i)
		{
			std::stringstream ss(buf);

			int val;
			for (int j = 1; ss >> val; ++j)
			{
				if (val == 0) continue;

				int from = j;
				int to = i;

				if (graph.size() <= std::max(from, to) + 1)
					graph.resize(std::max(from, to) + 1);

				graph[from].push_back(to);
			}
		}

		file.close();
	}

	std::deque<int> FindMinCycle()
	{
		for (int i = 1; i < graph.size(); ++i)
		{
			std::deque<int> dq;
			std::unordered_set<int> us;

			FindMinCycleHelp(dq, us, i, i);
		}

		return path;
	}

private:

	bool FindMinCycleHelp(std::deque<int>& currentPath, std::unordered_set<int>& visited, int startVertex, int currentVertex)
	{
		if (!currentPath.empty()
			&& currentVertex == startVertex)
		{
			if (currentPath.size() < path.size() || path.empty())
				path = currentPath;

			return false;
		}

		if (visited.count(currentVertex))
			return false;

		currentPath.push_back(currentVertex);
		visited.insert(currentVertex);

		for (int i = 0; i < graph[currentVertex].size(); ++i)
		{
			int nextVertex = graph[currentVertex][i];

			bool result = FindMinCycleHelp(currentPath, visited, startVertex, nextVertex);

			if (result)
			{
				currentPath.pop_back();
				visited.erase(nextVertex);
			}
		}

		return true;
	}

	std::vector<std::vector<int>> graph;
	std::deque<int> path;

};

int main()
{
	setlocale(LC_ALL, "");

	for (int i = 1; i <= 5; ++i)
	{
		Problem problem;

		std::string fileName = "graph" + std::to_string(i) + ".txt";
		problem.ReadGraph(fileName);

		std::deque<int> cycle = problem.FindMinCycle();

		std::cout << "Для графа " << fileName << " обхват: ";

		if (!cycle.empty())
		{
			std::cout << cycle.size() << std::endl;

			int startVertex = cycle.front();

			std::cout << "Один из наименьших циклов: ";
			while (!cycle.empty())
			{
				int front = cycle.front();
				cycle.pop_front();

				std::cout << front << "->";
			}

			std::cout << startVertex << std::endl;
		}
		else
		{
			std::cout << "infinity" << std::endl;
		}

		std::cout << std::endl;
	}

	return 0;
}
