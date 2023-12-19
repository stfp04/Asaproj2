#include <iostream>
#include <vector>
#include <stack>
using namespace std;

struct dfs_node {
    int color;
    int pi;
    int d;
    int df;
};

void le_input(vector<vector<int>>& grafo){
    int n, m;
    if(!scanf("%d %d", &n, &m))
        exit(EXIT_FAILURE);

    grafo = vector<vector<int>>(n, vector<int>());

    for(int i = 0; i < m; i++){
        int x, y;
        if(!scanf("%d %d", &x, &y)) 
            exit(EXIT_FAILURE);

        grafo[x - 1].push_back(y - 1);
    }
}

int dfs_aux(vector<vector<int>> &grafo, vector<dfs_node> &nodes, int v) {
    stack<int> stack;
    stack.push(v);
    
    int time = 0, maximo = 0;
    while (!stack.empty()) { 
        int v = stack.top();
        stack.pop();
        bool end = true;
        nodes[v - 1].color = 1;
        nodes[v - 1].d = time;
        time += 1;
        for (unsigned int i = 0; i < grafo[v - 1].size(); i++) {
            int vertice = grafo[v - 1][i];
            if (nodes[vertice - 1].color == 0) {
                end = false;
                stack.push(vertice);
            }
            else if(nodes[v - 1].d > nodes[vertice - 1].d) {
                end = false;
                stack.push(vertice);
            }
        }
        if(end == true) {
            nodes[v - 1].df = time;
            if(maximo < nodes[v - 1].df)
                maximo = nodes[v - 1].df;
        }
    }
    return maximo;
}

int maxValue(vector<vector<int>> &grafo) {
    vector<dfs_node> nodes = vector<dfs_node>(grafo.size(), {0, 0, 0, 0});
    int maximo = 0;

    for(unsigned int i = 0; i < grafo.size(); i++) {
        if(nodes[i].color == 0)
            maximo = max(maximo, dfs_aux(grafo, nodes, i + 1));
    }

    return maximo;
}

int main() {
    vector<vector<int>> grafo;
    le_input(grafo);
    printf("%d\n", maxValue(grafo));
}