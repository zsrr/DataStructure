//
// Created by 张师睿 on 2016/10/26.
// 加权有向图，邻接矩阵实现

#ifndef DATASTRUCTURES_ADJACENCYWDIGRAPH_HPP
#define DATASTRUCTURES_ADJACENCYWDIGRAPH_HPP

#include "AbsGraph.hpp"
#include "../MyOwnException.h"
#include "../utils.hpp"
#include "../Queue/ArrayQueue.hpp"

template<class T>
class AdjacencyWDiGraph : public AbsGraph<T> {
public:

    AdjacencyWDiGraph(int n, T noEdge) {
        if (n < 0)
            throw IllegalParameterValue();
        this->n = n;
        this->noEdge = noEdge;
        e = 0;
        util::make2dArray(a, n + 1, n + 1);
        fill2dArray();
    }

    ~AdjacencyWDiGraph() {
        util::dispose2dArray(a, n + 1);
    }

    virtual int numberOfVertexes() const override {
        return n;
    }

    virtual int numberOfEdges() const override {
        return e;
    }

    virtual bool existsEdge(int i, int j) const override {
        return !(i < 1 || j < 1 || i > n || j > n || a[i][j] == noEdge);
    }

    virtual bool existsEdge(const Edge<T> &edge) const override {
        return existsEdge(edge.vertex1, edge.vertex2) &&
                a[edge.vertex1][edge.vertex2] == edge.weight;
    }

    virtual void insertEdge(const Edge<T> &edge) override {
        int i = edge.vertex1;
        int j = edge.vertex2;

        if (i < 1 || j < 1 || i > n || j > n)
            throw IllegalParameterValue();

        if (a[i][j] == noEdge)
            e++;
        a[i][j] = edge.weight;
    }

    virtual void eraseEdge(int i, int j) override {
        if (!existsEdge(i, j))
            return;
        a[i][j] = noEdge;
        e--;
    }

    virtual void eraseEdge(const Edge<T> &edge) override {
        if (!existsEdge(edge))
            return;
        a[edge.vertex1][edge.vertex2] = noEdge;
        e--;
    }

    virtual int degree(int vertex) const override {
        throw UnsupportedOperation();
    }

    virtual int inDegree(int vertex) const override {
        checkVertex(vertex);
        int sum = 0;
        for (int i = 1; i <= n; i++)
            if (a[i][vertex] != noEdge)
                sum++;
        return sum;
    }

    virtual int outDegree(int vertex) const override {
        checkVertex(vertex);
        int sum = 0;
        for (int i = 1; i <= n; i++)
            if (a[vertex][i] != noEdge)
                sum++;
        return sum;
    }

    virtual bool isDirected() const override {
        return true;
    }

    virtual bool isWeighted() const override {
        return true;
    }

    virtual VertexIterator<T> *getIterator(int vertex) const override {
        checkVertex(vertex);
        return new AdjacencyWDiGraphIterator<T>(a[vertex], n, noEdge);
    }

    virtual void bfs(int vertex, int *reach,
                     int label, void (*visit)(const int &)) const override {
        ArrayQueue<int> aq;
        reach[vertex] = label;
        aq.push(vertex);

        while (!aq.empty()) {
            int w = aq.front();
            visit(w);
            aq.pop();

            VertexIterator<T> *vi = getIterator(w);

            while ((w = vi->next()) != -1) {
                if (reach[w] != label) {
                    aq.push(w);
                    reach[w] = label;
                }
            }

            delete(vi);
        }
    }

    virtual void dfs(int vertex, int reach[], int label,
                     void (*visit)(const int &)) const override {
        rDfs(vertex, reach, label, visit);
    }

protected:
    int n;
    int e;
    T **a;
    //这个需要自己定义，这个泛型一般来说是数字类型
    T noEdge;

    void fill2dArray() {
        for (int i = 0; i < n + 1; i++)
            for (int j = 0; j < n + 1; j++)
                a[i][j] = noEdge;
    }

    void checkVertex(int vertex) const {
        if (vertex < 1 || vertex > n)
            throw IllegalParameterValue();
    }

    virtual void rDfs(int vertex, int reach[], int label, void (*visit)(const int &)) const override {
        reach[vertex] = label;
        visit(vertex);

        VertexIterator<T> *vi = getIterator(vertex);
        int u;
        while ((u = vi->next()) != -1)
            if (reach[u] != label)
                rDfs(u, reach, label, visit);
        delete(vi);
    }

    template <class E>
    class AdjacencyWDiGraphIterator : public VertexIterator<E> {
    public:
        AdjacencyWDiGraphIterator(E *a, int n, E noEdge): a(a), n(n), noEdge(noEdge), currentVertex(1) {}

        virtual int next() override {
            for (int i = currentVertex; i <= n; i++)
                if (a[i] != noEdge) {
                    currentVertex = i + 1;
                    return i;
                }
            currentVertex = n + 1;
            return -1;
        }

        virtual int next(E &t) override {
            for (int i = currentVertex; i <= n; i++)
                if (a[i] != noEdge) {
                    currentVertex = i + 1;
                    t = a[i];
                    return i;
                }
            currentVertex = n + 1;
            return -1;
        }

    private:
        E *a;
        int n;
        int currentVertex;
        E noEdge;
    };
};

#endif //DATASTRUCTURES_ADJACENCYWDIGRAPH_HPP
