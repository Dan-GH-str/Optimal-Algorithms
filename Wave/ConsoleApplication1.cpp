#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// Структура для хранения координат клетки
struct Cell {
    int x, y;
};

// Направления движения (вверх, вниз, влево, вправо)
vector<Cell> directions = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

// Функция для проверки, является ли клетка проходимой
bool isValid(int x, int y, int rows, int cols, vector<vector<int>>& field) {
    return (x >= 0 && x < rows && y >= 0 && y < cols && field[x][y] != -1);
}

void print_field(vector<vector<int>>& field) {
    for (const auto& row : field) {
        for (int cell : row) {
            if (cell == -1)
                cout << "# ";
            else
                cout << cell << ' ';
        }
        cout << endl;
    }
}

void retrace_path(vector<vector<int>>& field, vector<vector<int>>& visited, Cell current, int steps) {
    int rows = field.size();
    int cols = field[0].size();

    queue<Cell> q;
    q.push(current);

    while (!q.empty() && steps != 0) {
        Cell current = q.front();
        q.pop();

        field[current.x][current.y] = steps;

        for (const auto& dir : directions) {
            int newX = current.x + dir.x;
            int newY = current.y + dir.y;

            if (isValid(newX, newY, rows, cols, field) && steps - visited[newX][newY] == 1) {
                field[newX][newY] = steps - 1;

                q.push({ newX, newY });

                steps--;
                break;
            }
        }
    }
}

// Функция для нахождения кратчайшего пути в лабиринте
int shortestPath(vector<vector<int>>& field, Cell start, Cell end) {
    int rows = field.size();
    int cols = field[0].size();

    // Очередь для BFS
    queue<Cell> q;
    q.push(start);

    // Массив для отслеживания посещенных клеток
    vector<vector<int>> visited(rows, vector<int>(cols, 0));
    visited[start.x][start.y] = -1;

    // Счетчик шагов
    int steps = 0;

    while (!q.empty()) {
        int size = q.size();
        for (int i = 0; i < size; ++i) {
            Cell current = q.front();
            q.pop();

            // Проверка, достигли ли мы конечной точки
            if (current.x == end.x && current.y == end.y) {
                retrace_path(field, visited, current, steps);

                print_field(field);

                while (!q.empty()) {
                    q.pop();
                }

                return steps;
            }

            // Проверяем все возможные направления
            for (const auto& dir : directions) {
                int newX = current.x + dir.x;
                int newY = current.y + dir.y;

                if (isValid(newX, newY, rows, cols, field) && !visited[newX][newY]) {
                    visited[newX][newY] = steps + 1;
                    q.push({ newX, newY });
                }
            }
        }
        // Увеличиваем счетчик шагов после обработки всех клеток на текущем уровне
        steps++;
    }

    return -1; // Если путь не найден
}

int main() {
    setlocale(LC_ALL, "RU");
    // Пример лабиринта
    vector<vector<int>> field = {
        {0, -1, 0, 0, 0},
        {0, -1, 0, -1, 0},
        {0, 0, 0, -1, 0},
        {-1, -1, 0, 0, 0},
        {0, 0, -1, -1, 0}
    };

    Cell start = { 0, 0 }; // Начальная точка
    Cell end = { 4, 4 };   // Конечная точка

    int result = shortestPath(field, start, end);

    if (result != -1) {
        cout << "Кратчайший путь найден, количество шагов: " << result << endl;
    }
    else {
        cout << "Путь не найден." << endl;
    }

    return 0;
}