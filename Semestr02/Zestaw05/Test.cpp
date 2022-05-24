#include "Graph.hpp"

void test_edge(Edge* e) {
	// Wypisz V0 dla e
	std::cout << "    V0 dla e: " << e->a()->id() << std::endl;

	// Wypisz V1 dla e
	std::cout << "    V1 dla e: " << e->b()->id() << std::endl;

	// Wypisz sąsiada (V0) dla e //test metody Mate
	std::cout << "    sąsiad (V0) dla e: " << e->other(e->a())->id() << std::endl;

	// Wypisz sąsiada (V1) dla e //test metody Mate
	std::cout << "    sąsiad (V1) dla e: " << e->other(e->b())->id() << std::endl;

	// Nadaj krawędzi e wagę V0+V1
	e->weight = e->a()->id() + e->b()->id();

	// Wypisz wagę krawędzi e
	std::cout << "    waga krawędzi e: " << e->weight << std::endl;
}

void test_graph(Graph& g) {
	// Wypisz, ile jest wierzchołków
	std::cout << "  ilość wierzchołków: " << g.vertices_num() << std::endl;

	// Wypisz, ile jest krawędzi
	std::cout << "  ilość krawędzi: " << g.edges_num() << std::endl;

	// v= SelectVertex(2);
	auto v = g.get_vertex(2);

	// Wypisz unikalny Numer v
	std::cout << "  id wierzchołka 2: " << v->id() << std::endl;

	// Nadaj v wagę unikalnyNumer*UniklanyNumer;
	v->weight = v->id() * v->id();

	// Wypisz wagę v
	std::cout << "  waga wierzchołka 2: " << v->weight << std::endl;

	// AddEdge(1,2);
	g.new_edge(1, 2);

	// AddEdge(1,2);
	g.new_edge(1, 2);

	// AddEdge(2,3);
	g.new_edge(2, 3);

	// AddEdge(3,4);
	g.new_edge(3, 4);

	// AddEdge(9,9);
	g.new_edge(9, 9);

	// Wypisz, ile jest wierzchołków
	std::cout << "  ilość wierzchołków: " << g.vertices_num() << std::endl;

	// Wypisz, ile jest krawędzi
	std::cout << "  ilość krawędzi: " << g.edges_num() << std::endl;

	// Wypisz, czy istnieje krawędź (1,1)
	std::cout << "  istnieje krawędź (1, 1): " << g.exists_edge(1, 1) << std::endl;

	// Wypisz, czy istnieje krawędź (1,2)
	std::cout << "  istnieje krawędź (1, 2): " << g.exists_edge(1, 2) << std::endl;

	// Wypisz, czy istnieje krawędź (2,1)
	std::cout << "  istnieje krawędź (2, 1): " << g.exists_edge(2, 1) << std::endl;

	// e=SelectEdge(1,2)
	std::cout << "  e=SelectEdge(1, 2)" << std::endl;
	test_edge(g.get_edge(1, 2));

	// e=SelectEdge(2,3)
	std::cout << "  e=SelectEdge(2, 3)" << std::endl;
	test_edge(g.get_edge(2, 3));

	// e=SelectEdge(3,4)
	std::cout << "  e=SelectEdge(3, 4)" << std::endl;
	test_edge(g.get_edge(3, 4));

	// e=SelectEdge(9,9)
	std::cout << "  e=SelectEdge(9, 9)" << std::endl;
	test_edge(g.get_edge(9, 9));

	{
		// Wypisz wszystkie wierzchołki korzystając z iteratora po wierzchołkach 
		// (ich unikalny numer i wagę)
		std::cout << "  wierzchołki:" << std::endl;
		auto iter = g.vertices_iter();
		while (!iter->done()) {
			auto el = **iter;
			std::cout << "    id: " << el.id() << "\twaga: " << el.weight << std::endl;
			iter->next();
		}
	}

	// Dodaj krawędzie:
	// AddEdge(3, 5);
	g.new_edge(3, 5);

	// AddEdge(8, 3);
	g.new_edge(8, 3);

	// AddEdge(5, 2);
	g.new_edge(5, 2);

	{
		// Wypisz wszystkie krawędzie korzystając z odpowiedniego iteratoa( to
		// znaczy, wypisz pierwszy i drugi wierzchołek krawędzi – v0 i v1)
		std::cout << "  krawędzie:" << std::endl;
		auto iter = g.edges_iter();
		while (!iter->done()) {
			auto el = **iter;
			std::cout << "    V0: " << el.a()->id() << "\tV1: " << el.b()->id() << std::endl;
			iter->next();
		}
	}

	{
		// Wypisz wszystkie krawędzie wychodzące z wierzchołka o numerze 3,
		// korzystając z odpowiedniego iterator (to znaczy, wypisz pierwszy i
		// drugi wierzchołek krawędzi – v0 i v1)
		std::cout << "  krawędzie wychodzące z wierzchołka o numerze 3:" << std::endl;
		auto iter = g.emanating_edges_iter(3);
		while (!iter->done()) {
			auto el = **iter;
			std::cout << "    V0: " << el.a()->id() << "\tV1: " << el.b()->id() << std::endl;
			iter->next();
		}
	}

	{
		// Wypisz wszystkie krawędzie dochodzące do wierzchołka o numerze 2,
		// korzystając z odpowiedniego iterator  to znaczy, wypisz pierwszy i
		// drugi wierzchołek krawędzi – v0 i v1)
		std::cout << "  krawędzie dochodzące do wierzchołka o numerze 2:" << std::endl;
		auto iter = g.incident_edges_iter(2);
		while (!iter->done()) {
			auto el = **iter;
			std::cout << "    V0: " << el.a()->id() << "\tV1: " << el.b()->id() << std::endl;
			iter->next();
		}
	}
}

int main() {
	{
		// Utwórz graf skierowany złożony z 10 wierzchołków
		std::cout << "graf skierowany o rozmiarze 10" << std::endl;
		Graph g(true, 10);
		test_graph(g);
	}

	std::cout << std::endl;

	{
		// Testy proszę powtórzyć tworząc graf nieskierowany
		std::cout << "graf nieskierowany o rozmiarze 10" << std::endl;
		Graph g(false, 10);
		test_graph(g);
	}
}
