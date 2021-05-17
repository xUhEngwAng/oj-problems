#include <cstdio>
#include <vector>
#define MOD (10007)

std::vector<std::vector<std::pair<int, int>>> graph;
std::vector<std::pair<int, int>> zebra_num;

std::pair<int, int> get_zebra_num(int v){
    if(zebra_num[v].first == -1){
        zebra_num[v] = {0, 0};
        std::pair<int, int> prev_zebra_num;

        for(auto& node: graph[v]){
            prev_zebra_num = get_zebra_num(node.first);
            if(node.second == 0)
                zebra_num[v].first += prev_zebra_num.second;
            else
                zebra_num[v].second += prev_zebra_num.first;
        }
    }
    zebra_num[v].first = zebra_num[v].first % MOD;
    zebra_num[v].second = zebra_num[v].second % MOD;
    return zebra_num[v];
}

int main(){
    int V, E, S, T;
    int A, B, C;
    scanf("%d %d %d %d", &V, &E, &S, &T);
    graph.resize(V);
    for(int ix = 0; ix != E; ++ix){
        scanf("%d %d %d", &A, &B, &C);
        graph[B].push_back({A, C});
    }
    zebra_num.resize(V, {-1, -1});
    zebra_num[S] = {1, 1};
    std::pair<int, int> result = get_zebra_num(T);
    printf("%d\n", (result.first + result.second) % MOD);
    return 0;
}
