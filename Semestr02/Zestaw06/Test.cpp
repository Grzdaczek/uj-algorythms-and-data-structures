#include "Graph.hpp"

void fill_graph(Graph& g) {

	// graph->AddEdge(0,1);
	g.new_edge(0, 1);

	// graph->AddEdge(1,2);
	g.new_edge(1, 2);

	// graph->AddEdge(2,3);
	g.new_edge(2, 3);

	// graph->AddEdge(3,4);
	g.new_edge(3, 4);

	// graph->AddEdge(3,7);
	g.new_edge(3, 7);

	// graph->AddEdge(4,5);
	g.new_edge(4, 5);

	// graph->AddEdge(5,9);
	g.new_edge(5, 9);

	// graph->AddEdge(9,9);
	g.new_edge(9, 9);

	// graph->AddEdge(6,8);
	g.new_edge(6, 8);

	// graph->AddEdge(8,6);
	g.new_edge(8, 6);

	// graph->AddEdge(0,8);
	g.new_edge(0, 8);
}

void test_dfs(Graph& g, int v) {
	auto iter = g.dfs_vertices_iter(v);
	std::cout << "  wierzchołki, dfs: " << v << std::endl;
	while (!iter->done()) {
		auto el = **iter;
		std::cout << "    id: " << el.id() << "\twaga: " << el.weight << std::endl;
		iter->next();
	}
}

void test_connected(Graph& g) {
	std::cout << "  graf jest spójny: " << (g.is_connected() ? "true" : "false") << std::endl;
}

int main() {
	{
		// Utwórz graf skierowany złożony z 10 wierzchołków
		std::cout << "graf skierowany o rozmiarze 10" << std::endl;
		Graph g(true, 10);
		fill_graph(g);
		test_dfs(g, 0);
		test_connected(g);

		g.new_edge(0, 8); std::cout << "  // AddEdge(0, 8);" << std::endl;
		g.new_edge(6, 0); std::cout << "  // AddEdge(6, 0);" << std::endl;
		g.new_edge(9, 0); std::cout << "  // AddEdge(9, 0);" << std::endl;

		test_connected(g);

		g.new_edge(7, 0); std::cout << "  // AddEdge(7, 0);" << std::endl;
		test_connected(g);
	}

	std::cout << std::endl;

	{
		// Testy proszę powtórzyć tworząc graf nieskierowany
		std::cout << "graf nieskierowany o rozmiarze 10" << std::endl;
		Graph g(false, 10);
		fill_graph(g);
		test_dfs(g, 0);
		test_connected(g);
	}
}
