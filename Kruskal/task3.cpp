#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Структура для представления ребра графа
struct Edge {
    int u, v; // вершины ребра
    int weight; // вес ребра (стоимость соединения)
};

// Функция для сравнения ребер по весу
bool compareEdges(const Edge& a, const Edge& b) {
    return a.weight < b.weight;
}

// Функция для поиска компоненты связности вершины
int find(int v, vector<int>& parent) {
    if (parent[v] == v) return v;
    return parent[v] = find(parent[v], parent);
}

// Функция для объединения компонент связности
void unionSets(int u, int v, vector<int>& parent) {
    u = find(u, parent);
    v = find(v, parent);
    parent[u] = v;
}

// Алгоритм Крускала
vector<Edge> kruskal(vector<Edge>& edges, int n) {
    vector<Edge> result;
    vector<int> parent(n);
    for (int i = 0; i < n; i++) parent[i] = i;

    sort(edges.begin(), edges.end(), compareEdges);

    for (const Edge& e : edges) {
        int u = find(e.u, parent);
        int v = find(e.v, parent);
        if (u != v) {
            result.push_back(e);
            unionSets(u, v, parent);
        }
    }

    return result;
}

int main() {
    setlocale(LC_ALL, "RU");
    int n, m; // количество вершин и ребер
    cin >> n >> m;

    vector<Edge> edges(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].weight;
    }

    vector<Edge> result = kruskal(edges, n);

    cout << "Минимальное дерево:" << endl;
    for (const Edge& e : result) {
        cout << e.u << " -- " << e.v << " : " << e.weight << endl;
    }

    return 0;
}