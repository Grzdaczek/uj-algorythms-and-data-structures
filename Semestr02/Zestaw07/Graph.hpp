#include <string>
#include <vector>
#include <stack>
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
	class AllVerticesIter;
	class AllEdgesIter;
	class EmanEdgesIter;
	class InciEdgesIter;
	class DfsVertexIter;

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
		friend DfsVertexIter;

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

	class DfsVertexIter : public Iterator<Vertex> {
	private:
		Graph* m_target;
		std::vector<bool> m_visited;
		std::vector<int> m_parents;
		std::stack<int> m_stack;
	public:
		DfsVertexIter(Graph* target, int start_vertex) : m_target(target) {
			m_stack.push(start_vertex);

			int num = m_target->vertices_num();
			for (int i = 0; i < num; ++i)
				m_visited.push_back(false);

			for (int i = 0; i < num; ++i)
				m_parents.push_back(-1);

			m_visited[0] = true;
		}

		void next() {
			if (!m_stack.empty()) {
				int v = m_stack.top();
				m_stack.pop();
				auto iter = EmanEdgesIter(m_target, v);

				while (!iter.done()) {
					auto n = iter.m_b;

					if (!m_visited.at(n)) {
						m_visited.at(n) = true;
						m_stack.push(n);
						m_parents.at(n) = v;
					}

					iter.next();
				}
			}
		}

		Vertex* parent() {
			auto parent = m_parents.at(m_stack.top());

			if (parent == -1) {
				return nullptr;
			}
			else {
				return m_target->get_vertex(parent);
			}
		}

		bool done() { return m_stack.empty(); }

		Vertex& operator*() {
			return *m_target->get_vertex(m_stack.top());
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
		, m_edges(std::vector<std::vector<Edge*>>(n, (std::vector<Edge*>(n, nullptr)))) {
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

	bool is_connected_from(int v) {
		auto iter = dfs_vertices_iter(v);
		int j = 0;

		while (!iter.done()) {
			j += 1;
			iter.next();
		}

		return j == m_vertices_num;
	}

	bool is_connected() {
		if (m_directed) {
			for (int i = 0; i < m_vertices_num; ++i) {
				if (!is_connected_from(i)) return false;
			}

			return true;
		}
		else {
			return is_connected_from(0);
		}
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

	AllVerticesIter vertices_iter() {
		return AllVerticesIter(this);
	}

	AllEdgesIter edges_iter() {
		return AllEdgesIter(this);
	}

	EmanEdgesIter emanating_edges_iter(int v) {
		return EmanEdgesIter(this, v);
	}

	InciEdgesIter incident_edges_iter(int v) {
		return InciEdgesIter(this, v);
	}

	DfsVertexIter dfs_vertices_iter(int v) {
		return DfsVertexIter(this, v);
	}
};