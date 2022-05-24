#include <string>
#include <vector>
#include <iostream>
#include <cassert>

class Vertex {
private:
	static unsigned int s_last_id;
	unsigned int m_id;

public:
	std::string label;
	int weight;

	Vertex() : m_id(s_last_id++) {};
	Vertex(int id) : m_id(id) {};
	int id() const { return m_id; }
};

unsigned int Vertex::s_last_id = 0;

class Edge {
	Vertex* m_a;
	Vertex* m_b;

public:
	int weight;
	std::string label;

	Vertex* a() { return m_a; }
	Vertex* b() { return m_b; }
	Vertex* other(Vertex* v) { return v != m_a ? m_a : m_b; }
	Edge(Vertex* a, Vertex* b) : m_a(a), m_b(b) {};
};

class Graph {
private:
	bool m_directed;
	std::vector<Vertex> m_vertices;
	std::vector<std::vector<Edge*>> m_edges;

public:
	Graph(bool directed, int n)
		: m_directed(directed)
		, m_edges(std::vector(n, (std::vector<Edge*>(n, nullptr)))) {
		for (int i = 0; i < n; ++i) {
			m_vertices.push_back(Vertex());
		}
	}

	void clear() {
		for (auto& row : m_edges) {
			for (auto& cell : row) {
				delete cell;
				cell = nullptr;
			}
		}
	}

	int vertices_num() const {
		return m_vertices.size();
	}

	int edges_num() const {
		int num = 0;

		for (auto& row : m_edges) {
			for (auto& cell : row) {
				num++;
			}
		}

		return m_directed ? num : num / 2;
	}

	bool is_directed() const {
		return m_directed;
	}

	Edge* new_edge(int v_a, int v_b) {
		auto curent_edge = get_edge(v_a, v_b);

		if (curent_edge) {
			return curent_edge;
		}
		else {
			auto edge_ptr = new Edge(&m_vertices[v_a], &m_vertices[v_b]);

			m_edges[v_a][v_b] = edge_ptr;
			if (!is_directed()) m_edges[v_b][v_a] = edge_ptr;

			return edge_ptr;
		}
	}

	Edge* get_edge(int v_a, int v_b) {
		return m_edges[v_a][v_b];

	}

	bool exists_edge(int v_a, int v_b) {
		return get_edge(v_a, v_b) != nullptr;
	}

	Vertex* get_vertex(int v) {
		return &m_vertices[v];
	}
};