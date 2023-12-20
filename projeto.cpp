#include <iostream>
#include <vector>
#include <stack>
using namespace std;

struct dfs_node {
    int color;
    int d;
    int low;
};

stack<int> S;
int component[100];
vector < int > components[100];
int numComponents = 0;

void le_input(vector<vector<int>>& grafo, vector<vector<int>>& grafoT){
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

int Kosaraju(vector<vector<int>> &grafo, vector<vector<int>> &grafoT) {
    n = grafo.size();
    stack<int> S, LT;
    vector<int> gt = vector<vector<int>>(n, vector<int>());
    vector<bool> marked = vector<bool>(n, false);

    for (unsigned int i = 0; i < n; i++) {
        if (!marked[i]) {
            marked[i] = true;
            S.push(i);
            while(!S.empty()) {
                int v = S.top();
                d = true;
                for(unsigned int i = 0; i < grafo[v].size(); i++) {
                    gt[grafo[v][i]].push_back(v);
                    if(!marked[grafo[v][i]]) {
                        d = false;
                        marked[grafo[v][i]] = true;
                        S.push(grafo[v][i]);
                        break;
                    }
                }
                if(d) {
                    S.pop();
                    LT.push(v);
                }
            }
        }
    }
    /*
        
    # postorder DFS on T to pop root vertices from L and mark SCCs
    C = [None] * N
    while L:
        r = L.pop()
        S = [r]
        if U[r]:
            U[r], C[r] = False, r
        while S:
            u, done = S[-1], True
            for v in T[u]:
                if U[v]:
                    U[v] = done = False
                    S.append(v)
                    C[v] = r
                    break
            if done:
                S.pop()
    
    return C
    
    */
    vector<int> C = vector<int>(n, -1);
    while(!LT.empty()) {
        v = LT.pop();
        S.push(v);
        if(marked[v]) {
            marked[v] = false;
            C[v] = v;
        }

        while(!S.empty()) {
            int v = S.top();
            d = true;
            for(unsigned int i = 0; i < grafo[v].size(); i++) {
                if(marked[grafo[i]]) {
                    d = false;
                    marked[grafo[v][i]] = false;
                    S.push(grafo[v][i]);
                    C[grafo[v][i]] = v;
                    break;
                }
            }
            if(d):
                S.pop();
        }

    }
    return numComponents;
}

int main() {
    vector<vector<int>> grafo;
    vector<vector<int>> grafoT;
    le_input(grafo, grafoT);
    printf("%d\n", maxValue(grafo));
}

/*
def kosaraju(G):
    
    # postorder DFS on G to transpose the graph and push root vertices to L
    N = len(G)
    T, L, U = [[] for _ in range(N)], [], [False] * N
    for u in range(N):
        if not U[u]:
            U[u], S = True, [u]
            while S:
                u, done = S[-1], True
                for v in G[u]:
                    T[v].append(u)
                    if not U[v]:
                        U[v], done = True, False
                        S.append(v)
                        break
                if done:
                    S.pop()
                    L.append(u)
    
    # postorder DFS on T to pop root vertices from L and mark SCCs
    C = [None] * N
    while L:
        r = L.pop()
        S = [r]
        if U[r]:
            U[r], C[r] = False, r
        while S:
            u, done = S[-1], True
            for v in T[u]:
                if U[v]:
                    U[v] = done = False
                    S.append(v)
                    C[v] = r
                    break
            if done:
                S.pop()
    
    return C
*/