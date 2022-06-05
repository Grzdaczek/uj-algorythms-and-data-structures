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

	// graph->AddEdge(3,9);
	g.new_edge(3, 9);

	// graph->AddEdge(5,7);
	g.new_edge(5, 7);

	// graph->AddEdge(9,8);
	g.new_edge(9, 8);

}

void test_spanning_tree(Graph& g, int v) {
	if (g.is_connected_from(v)) {
		std::cout << "  wierzchołki, drzewo rozpinające: " << v << std::endl;
		auto iter = g.dfs_vertices_iter(v);
		while (!iter.done()) {
			auto el = *iter;
			std::cout
				<< "    id: " << el.id()
				<< "\twaga: " << el.weight
				<< "\t\trodzic: " << (iter.parent() ? std::to_string(iter.parent()->id()) : "None")
				<< std::endl;
			iter.next();
		}
	}
	else {
		std::cout << "  graf nie jest spójny" << std::endl;
	}
}

int main() {
	// Utwórz graf nieskierowany złożony z 10 wierzchołków
	std::cout << "graf nieskierowany o rozmiarze 10" << std::endl;
	Graph g(false, 10);
	fill_graph(g);
	test_spanning_tree(g, 0);
}
