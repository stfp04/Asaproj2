#include <iostream>
#include <vector>
#include <stack>

using namespace std;


void le_input(vector<vector<int>>& grafo, vector<vector<int>>& grafoT, int& vertices, int& m);

void dfs(vector<vector<int>>& adj, int v, vector<bool>& visited, stack<int>& s);

void kosaraju(vector<vector<int>>& grafo, vector<vector<int>>& grafoT, vector<bool>& visited, int& vertices);

int maxValue(vector<vector<int>> &grafo, vector<int>& tabelaAux, int& vertices);


int main() {
    int vertices, m, res = 0;
    vector<vector<int>> grafo;
    vector<vector<int>> grafoT;
    le_input(grafo, grafoT, vertices, m);
    vector<bool> visited(vertices, false);
    vector<int> tabelaAux(vertices, 0);

    kosaraju(grafo, grafoT, visited, vertices);

    for(int i = 0; i < vertices; i++){
        if(tabelaAux[i] == 0){
            maxValue(grafo, tabelaAux, i);
        }
        res = max(tabelaAux[i], res);
    }

    printf("%d\n", res);

    return 0;
}


void le_input(vector<vector<int>>& grafo, vector<vector<int>>& grafoT, int& vertices, int& m){
    if(!scanf("%d %d", &vertices, &m))
        exit(EXIT_FAILURE);

    grafo = vector<vector<int>>(vertices, vector<int>());
    grafoT = vector<vector<int>>(vertices, vector<int>());

    for(int i = 0; i < m; i++){
        int x, y;
        if(!scanf("%d %d", &x, &y)) 
            exit(EXIT_FAILURE);

        grafo[x - 1].push_back(y - 1);
        grafoT[y - 1].push_back(x - 1);
    }
}


void dfs(vector<vector<int>>& adj, int v, vector<bool>& visited, stack<int>& s) {
    visited[v] = true;
    for (int u : adj[v]) {
        if (!visited[u]) {
            dfs(adj, u, visited, s);
        }
    }
    s.push(v);
}


void kosaraju(vector<vector<int>>& grafo, vector<vector<int>>& grafoT, vector<bool>& visited, int& vertices) {
    stack<int> s;

    for (int i = 0; i < vertices; i++) {
        if (!visited[i]) {
            dfs(grafo, i, visited, s);
        }
    }

    fill(visited.begin(), visited.end(), false);
    
    while (!s.empty()) {
        int v = s.top();
        s.pop();

        if (!visited[v]) {
            stack<int> component;
            dfs(grafoT, v, visited, component);

            while (!component.empty()) {
                component.pop();
            }
        }
    }
}


int maxValue(vector<vector<int>> &grafo, vector<int>& tabelaAux, int& vertices) {
    if(tabelaAux[vertices] != 0)
        return tabelaAux[vertices];
    if(grafo[vertices].size() == 0)
        return 0;

    int res = 1;

    for(int i : grafo[vertices]){
            tabelaAux[vertices] = max(tabelaAux[vertices], maxValue(grafo, tabelaAux, i) + 1);
            res = max(res, tabelaAux[vertices]);
    }

    return res;
}






