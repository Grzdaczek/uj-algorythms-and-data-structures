#include "Graph.hpp"

void fill_graph(Graph& g) {
	g.new_edge(0, 1);
	g.new_edge(1, 2);
	g.new_edge(2, 3);
	g.new_edge(3, 4);
	g.new_edge(3, 7);
	g.new_edge(4, 5);
	g.new_edge(5, 9);
	g.new_edge(9, 9);
	g.new_edge(6, 8);
	g.new_edge(8, 6);
	g.new_edge(0, 8);
}

void test_dfs(Graph& g) {

}

void test_connected(Graph& g) {
	
}

int main() {
	{
		// Utwórz graf skierowany złożony z 10 wierzchołków
		std::cout << "graf skierowany o rozmiarze 10" << std::endl;
		Graph g(true, 10);
		fill_graph(g);
		test_dfs(g);
		test_connected(g);
	}

	std::cout << std::endl;

	{
		// Testy proszę powtórzyć tworząc graf nieskierowany
		std::cout << "graf nieskierowany o rozmiarze 10" << std::endl;
		Graph g(false, 10);
	}
}
