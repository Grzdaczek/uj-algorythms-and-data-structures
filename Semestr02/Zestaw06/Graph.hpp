#include <string>
#include <vector>
#include <iostream>
#include <cassert>
#include <memory>

template<typename T>
class Iterator {
public:
	virtual void next() = 0;
	virtual bool done() = 0;
	virtual T& operator*() = 0;
	void operator++() { next(); }
};

class Vertex {
private:
	static unsigned int s_last_id;
	unsigned int m_id;

public:
	std::string label;
	int weight;

	Vertex() : m_id(s_last_id++), weight(0) {};
	Vertex(int id) : m_id(id), weight(0) {};
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
	Edge(Vertex* a, Vertex* b) : m_a(a), m_b(b), weight(0) {};
};

class Graph {
	class AllVerticesIter : public Iterator<Vertex> {
	private:
		Graph* m_target;
		int m_index;
	public:
		AllVerticesIter(Graph* target) : m_target(target), m_index(0) {}
		void next() { if (!done()) m_index++; }
		bool done() { return m_target->vertices_num() <= m_index; }
		Vertex& operator*() { return *m_target->get_vertex(m_index); }
	};

	class AllEdgesIter : public Iterator<Edge> {
	private:
		Graph* m_target;
		int m_a;
		int m_b;

	public:
		AllEdgesIter(Graph* target) : m_target(target), m_a(0), m_b(0) {
			if (!m_target->get_edge(m_a, m_b)) next();
		}

		void next() {
			if (done()) return;

			m_a += 1;
			if (m_a >= m_target->vertices_num()) {
				m_a = 0;
				m_b += 1;
			}

			auto edge = m_target->get_edge(m_a, m_b);

			if (!edge) next();
		}

		bool done() {
			int ver = m_target->vertices_num();
			return m_b >= ver || m_a >= ver;
		}

		Edge& operator*() { return *m_target->get_edge(m_a, m_b); }
	};

	class EmanEdgesIter : public Iterator<Edge> {
	private:
		Graph* m_target;
		const int m_a;
		int m_b;

	public:
		EmanEdgesIter(Graph* target, int v) : m_target(target), m_a(v), m_b(0) {
			if (!m_target->get_edge(m_a, m_b)) next();
		}

		void next() {
			if (done()) return;

			m_b += 1;
			auto edge = m_target->get_edge(m_a, m_b);

			if (!edge) next();
		}

		bool done() { return m_b >= m_target->vertices_num(); }

		Edge& operator*() { return *m_target->get_edge(m_a, m_b); }
	};

	class InciEdgesIter : public Iterator<Edge> {
	private:
		Graph* m_target;
		int m_a;
		const int m_b;

	public:
		InciEdgesIter(Graph* target, int v) : m_target(target), m_a(0), m_b(v) {
			if (!m_target->get_edge(m_a, m_b)) next();
		}

		void next() {
			if (done()) return;

			m_a += 1;
			auto edge = m_target->get_edge(m_a, m_b);

			if (!edge) next();
		}

		bool done() { return m_a >= m_target->vertices_num(); }

		Edge& operator*() { return *m_target->get_edge(m_a, m_b); }
	};

	class DfsIterator : public Iterator<Vertex> {
	private:
		Graph* m_target;
		std::vector<bool> m_visited;
		std::stack<InciEdgesIter> m_stack;
	public:
		DfsIterator(Graph* target, Node* start) : m_target(target), m_start(start) {
			int num = target.vertices_num();

			for (int i = 0; i < num; ++i) {
				m_visited.push_back(false)
			}
		}
	};

private:
	bool m_directed;
	int m_edges_num;
	int m_vertices_num;
	std::vector<Vertex> m_vertices;
	std::vector<std::vector<Edge*>> m_edges;

public:
	Graph(bool directed, int n)
		: m_directed(directed)
		, m_edges_num(0)
		, m_vertices_num(n)
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
		return m_vertices_num;
	}

	int edges_num() const {
		return m_edges_num;
	}

	bool is_directed() const {
		return m_directed;
	}

	void new_edge(int v_a, int v_b) {
		auto curent_edge = get_edge(v_a, v_b);

		if (curent_edge) {
			return;
		}
		else {
			m_edges[v_a][v_b] = new Edge(&m_vertices[v_a], &m_vertices[v_b]);

			if (!is_directed()) {
				m_edges[v_b][v_a] = new Edge(&m_vertices[v_b], &m_vertices[v_a]);
			}

			m_edges_num += 1;

			return;
		}
	}

	Edge* get_edge(int v_a, int v_b) {
		if (m_vertices_num > v_a && m_vertices_num > v_b) {
			return m_edges[v_a][v_b];
		}
		else {
			return nullptr;
		}

	}

	bool exists_edge(int v_a, int v_b) {
		return get_edge(v_a, v_b) != nullptr;
	}

	Vertex* get_vertex(int v) {
		return &m_vertices[v];
	}

	std::unique_ptr<Iterator<Vertex>> vertices_iter() {
		return std::make_unique<AllVerticesIter>(AllVerticesIter(this));
	}

	std::unique_ptr<Iterator<Edge>> edges_iter() {
		return std::make_unique<AllEdgesIter>(AllEdgesIter(this));
	}

	std::unique_ptr<Iterator<Edge>> emanating_edges_iter(int v) {
		return std::make_unique<EmanEdgesIter>(EmanEdgesIter(this, v));
	}

	std::unique_ptr<Iterator<Edge>> incident_edges_iter(int v) {
		return std::make_unique<InciEdgesIter>(InciEdgesIter(this, v));
	}
};