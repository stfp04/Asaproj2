#include <iostream>
#include <vector>
#include <stack>
using namespace std;

void le_input(vector<vector<int>>& grafo, vector<vector<int>> &gt){
    int n, m;
    if(!scanf("%d %d", &n, &m))
        exit(EXIT_FAILURE);
    grafo = vector<vector<int>>(n, vector<int>());
    gt = vector<vector<int>>(n, vector<int>());

    for(int i = 0; i < m; i++){
        int x, y;
        if(!scanf("%d %d", &x, &y)) 
            exit(EXIT_FAILURE);

        grafo[x - 1].push_back(y - 1);
        gt[y - 1].push_back(x - 1);
    }
}

int Kosaraju(vector<vector<int>> &grafo, vector<vector<int>> &gt) {
    int n = grafo.size();
    stack<int> S, LT;
    vector<bool> marked = vector<bool>(n, false);

    for (int i = 0; i < n; i++) {
        if(marked[i])
            continue;

        marked[i] = true;
        S.push(i);
        while(!S.empty()) {
            int v = S.top();
            bool d = true;
            for(unsigned int i = 0; i < grafo[v].size(); i++) {
                if(marked[grafo[v][i]])
                    continue;
                d = false;
                marked[grafo[v][i]] = true;
                S.push(grafo[v][i]);
                break;
            }
            if(d) {
                S.pop();
                LT.push(v);
            }
        }
    }

    vector<int> C = vector<int>(n, -1);

    int num_scc = 0, max_jumps = 0;
    vector<int> max_jumps_scc;
    while(!LT.empty()) {
        int v = LT.top();
        LT.pop();

        if(marked[v]) {
            marked[v] = false;
            C[v] = num_scc;
            S.push(v);
            max_jumps_scc.push_back(0);
        }

        while(!S.empty()) {
            int t = S.top();
            S.pop();
            marked[t] = false;
            for(unsigned int i = 0; i < gt[t].size(); i++) {
                if(marked[gt[t][i]]) {
                    S.push(gt[t][i]);
                    C[gt[t][i]] = v;
                }
                else if(C[gt[t][i]] != num_scc) {
                    max_jumps_scc[num_scc] = max(max_jumps_scc[num_scc], max_jumps_scc[C[gt[t][i]]] + 1);
                }
            }
        }
        if(max_jumps_scc[num_scc] > max_jumps) {
            max_jumps = max_jumps_scc[num_scc];
        }
        num_scc++;
    }

    return max_jumps;
}

int main() {
    vector<vector<int>> grafo, gt;
    le_input(grafo, gt);
    printf("%d\n", Kosaraju(grafo, gt));
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