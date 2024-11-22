#include <iostream>
#include <vector>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max(); // Определяем бесконечность

void floydWarshall(vector<vector<int>>& dist) {
    int n = dist.size();

    // Основной цикл алгоритма
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dist[i][k] != INF && dist[k][j] != INF) { // Проверяем на наличие пути
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
}

void printMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (const auto& val : row) {
            if (val == INF) {
                cout << "INF ";
            }
            else {
                cout << val << " ";
            }
        }
        cout << endl;
    }
}

int main() {
    setlocale(LC_ALL, "RU");
    // Пример матрицы смежности
    int n; // Количество городов
    cout << "Введите количество городов: ";
    cin >> n;

    vector<vector<int>> dist(n, vector<int>(n, INF));

    cout << "Введите матрицу смежности (введите " << INF << " для отсутствующих путей):" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> dist[i][j];
            if (i == j) {
                dist[i][j] = 0; // Расстояние до самого себя
            }
        }
    }

    floydWarshall(dist);

    cout << "Матрица кратчайших путей:" << endl;
    printMatrix(dist);

    return 0;
}