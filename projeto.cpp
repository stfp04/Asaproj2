#include <iostream>
#include <vector>
#include <stack>
using namespace std;

struct dfs_node {
    int color;
    int d;
    int low;
};

void le_input(vector<vector<int>>& grafo, vector<vector<int>>& grafoT){
    int n, m;
    if(!scanf("%d %d", &n, &m))
        exit(EXIT_FAILURE);

    grafo = vector<vector<int>>(n, vector<int>());
    grafoT = vector<vector<int>>(n, vector<int>());

    for(int i = 0; i < m; i++){
        int x, y;
        if(!scanf("%d %d", &x, &y)) 
            exit(EXIT_FAILURE);

        grafo[x - 1].push_back(y - 1);
        grafoT[y - 1].push_back(x - 1);
    }
}

int dfs(vector<vector<int>> &grafo, vector<dfs_node> &nodes, int v) {
    stack<int> stackSCC;
    stack<int> stackDFS;
    vector<bool> onStack(grafo.size(), false);

    stackDFS.push(v);
    stackSCC.push(v);    
    int id = 0;
    while (!stackDFS.empty()) { 
        int ve = stackDFS.top();
        stackDFS.pop();

        nodes[ve].color++;
        nodes[ve].d = id++;
        nodes[ve].low = id;
        for (unsigned int i = 0; i < grafo[ve].size(); i++) {
            int vertice = grafo[ve][i];
            if (nodes[vertice].color == 0) {
                stackDFS.push(vertice);
                stackSCC.push(vertice);
                onStack[vertice] = true;
            }
            else if(onStack[vertice])
                nodes[ve].low = min(nodes[vertice].low, nodes[ve].low);
        }
    }

    while (!stackSCC.empty()) { 
        int ve = stackSCC.top();
        stackSCC.pop();

        onStack[ve] = true;
        for (unsigned int i = 0; i < grafo[ve].size(); i++) {
            int vertice = grafo[ve][i];
            if (nodes[vertice].color == 0) {
                onStack[vertice] = true;
            }
            else if(onStack[vertice])
                nodes[ve].low = min(nodes[vertice].low, nodes[ve].low);
        }
    }
    

    return 0;
}

int maxValue(vector<vector<int>> &grafo) {
    vector<dfs_node> nodes = vector<dfs_node>(grafo.size(), {0, 0, 0});
    int maximo = 0;

    for(unsigned int i = 1; i < grafo.size(); i++) {
        if(nodes[i].color == 0)
            maximo = max(maximo, dfs(grafo, nodes, i + 1));
    }
    return maximo;
}

int main() {
    vector<vector<int>> grafo;
    vector<vector<int>> grafoT;
    le_input(grafo);
    printf("%d\n", maxValue(grafo));
}