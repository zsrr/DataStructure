//
// Created by 张师睿 on 2016/10/26.
//

#ifndef DATASTRUCTURES_ABSGRAPHICS_HPP
#define DATASTRUCTURES_ABSGRAPHICS_HPP

template<class T>
struct Edge {
    int vertex1;
    int vertex2;
    T weight;
};

template<class T>
class VertexIterator {
public:
    virtual int next() = 0;

    virtual int next(T &) = 0;
};

template<class T>
class AbsGraph {
public:

    virtual ~AbsGraph() {}

    virtual int numberOfVertexes() const = 0;

    virtual int numberOfEdges() const = 0;

    virtual bool existsEdge(int i, int j) const = 0;

    virtual bool existsEdge(const Edge<T> &edge) const = 0;

    virtual void insertEdge(const Edge<T> &edge) = 0;

    virtual void eraseEdge(int i, int j) = 0;

    virtual void eraseEdge(const Edge<T> &edge) = 0;

    virtual int degree(int vertex) const = 0;

    virtual int inDegree(int vertex) const = 0;

    virtual int outDegree(int vertex) const = 0;

    virtual bool isDirected() const = 0;

    virtual bool isWeighted() const = 0;

    virtual VertexIterator<T> * getIterator(int vertex) const = 0;

    virtual void bfs(int vertex, int reach[],
                     int label, void (*visit)(const int&)) const = 0;

    virtual void dfs(int vertex, int reach[],
                     int label, void (*visit)(const int&)) const = 0;

protected:
    static int *reach;
    static int label;

    virtual void rDfs(int vertex, void (*visit)(const int &)) const = 0;
};

#endif //DATASTRUCTURES_ABSGRAPHICS_HPP
