#include <iostream>
#include <bits/stdc++.h>
#include <complex>

using namespace std;

class Point {
public:
    int index;

    Point(int x, int y, int index) {
        this->x = x;
        this->y = y;
        this->index = index;
    }

    int getEnergyToPoint(Point p) {
        auto boost = p.hasCoin ? -1 : 1;
        int distance = (int) (std::pow((p.x - this->x), 2) + pow((p.y - this->y), 2));
        return distance * boost;
    }


    int x;
    int y;
    bool hasCoin = false;
};



class Edge {
public:
    Point origem;
    Point destino;

    Edge(Point origem, Point destino) : origem(origem), destino(destino) {
        this->origem = origem;
        this->destino = destino;
    }
};

pair<int, vector<int>> bellmanFord(vector<vector<Edge>> graph, int start) {
    int graphSize = graph.size();
    auto distances = vector<vector<int>>(graphSize, vector<int>(graphSize, INT_MAX));
    auto percursores = vector<int>(graphSize, -1);
    distances[0][start] = 0;

    for (int k = 1; k < graphSize; k++) {
        for (int t = 0; t < graphSize; t++) {
            distances[k][t] = distances[k - 1][t];
        }

        for (int u = 0; u < graphSize; u++) {
            auto edges = graph[u];

            for (auto edge: edges) {
                int t = edge.destino.index;
                int weight = edge.origem.getEnergyToPoint(edge.destino);

                if (distances[k - 1][u] != INT_MAX && distances[k - 1][u] + weight < distances[k][t]) {
                    distances[k][t] = distances[k - 1][u] + weight;
                    percursores[t] = u;
                }
            }
        }
    }

    for (int u = 0; u < graphSize; u++) {
        auto edges = graph[u];
        for (auto edge: edges) {
            int t = edge.destino.index;
            int weight = edge.origem.getEnergyToPoint(edge.destino);
            if (distances[graphSize - 1][u] != INT_MAX &&
                distances[graphSize - 1][u] + weight < distances[graphSize - 1][t]) {
                return pair<int, vector<int>>(-1, vector<int>());
            }
        }
    }

    return pair<int, vector<int>>(distances[graphSize - 1][graphSize - 1], percursores);
}

vector<int> reconstructPath(vector<int> percursores) {
    vector<int> caminho = vector<int>();

    int indiceAtual = percursores[percursores.size() - 1];

    while (indiceAtual != -1) {
        caminho.emplace_back(indiceAtual);
        indiceAtual = percursores[indiceAtual];
    }

    reverse(caminho.begin(), caminho.end());
    return caminho;
}

int main() {


    int totalLevels;
    cin >> totalLevels;

    for (int i = 0; i < totalLevels; i++) {
        int totalPoints;
        cin >> totalPoints;

        auto points = vector<Point>();

        
        for (int j = 0; j < totalPoints; j++) {
            int x, y;
            cin >> x;
            cin >> y;
            points.emplace_back(Point(x, y, j));
        }

        
        int totalCoins;
        cin >> totalCoins;

        for (int k = 0; k < totalCoins; ++k) {
            int pointIndex;
            cin >> pointIndex;
            points[pointIndex].hasCoin = true;
        }

        
        auto graph = vector<vector<Edge>>();

        for (int k = 0; k < totalPoints; k++) {
            int totalAccessiblePoints;
            cin >> totalAccessiblePoints;

            auto list = vector<Edge>();

            for (int l = 0; l < totalAccessiblePoints; ++l) {
                int pointIndex;
                cin >> pointIndex;
                list.emplace_back(Edge(points[k], points[pointIndex]));
            }

            graph.emplace_back(list);
        }

        auto data = bellmanFord(graph, 0);

        if (data.first == -1) {
            cout << "LOOP" << endl;
        } else {
            cout << data.first << ' ';

            auto path = reconstructPath(data.second);
            for (auto point : path) {
                cout << point << ' ';
            }
            cout << data.second.size() - 1;
            cout << endl;
        }

    }

    return 0;
}
