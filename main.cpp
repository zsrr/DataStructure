
#include <iostream>
#include "Graphics/AdjacencyWDiGraph.hpp"

#define NO_EDGE -100000

using std::cout;
using std::cin;
using std::endl;
using std::string;

void visit(const int& n) {
    cout << n << " ";
}

int main() {
    AdjacencyWDiGraph<int> *awdg = new AdjacencyWDiGraph<int>(10, NO_EDGE);
    awdg->insertEdge({1, 2, 10});
    awdg->insertEdge({2, 3, 40});
    awdg->insertEdge({4, 5, 50});
    int *reach = new int[awdg->numberOfVertexes()];
    awdg->bfs(1, reach, 10, visit);
    cout << endl;
    awdg->dfs(1, reach, 11, visit);
    delete(awdg);
    return 0;
}