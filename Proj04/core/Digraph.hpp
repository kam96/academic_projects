// Digraph.hpp
//
// ICS 46 Spring 2017
// Project #4: Rock and Roll Stops the Traffic
//
// This header file declares a class template called Digraph, which is
// intended to implement a generic directed graph.  The implementation
// uses the adjacency lists technique, so each vertex stores a linked
// list of its outgoing edges.
//
// Along with the Digraph class template is a class DigraphException
// and a couple of utility structs that aren't generally useful outside
// of this header file.
//
// In general, directed graphs are all the same, except in the sense
// that they store different kinds of information about each vertex and
// about each edge; these two types are the type parameters to the
// Digraph class template.

#ifndef DIGRAPH_HPP
#define DIGRAPH_HPP

#include <functional>
#include <list>
#include <map>
#include <utility>
#include <vector>
#include <queue>
#include <algorithm> //added
#include <iterator> //added
#include <limits> //added

// DigraphExceptions are thrown from some of the member functions in the
// Digraph class template, so that exception is declared here, so it
// will be available to any code that includes this header file.

class DigraphException
{
public:
    DigraphException(const std::string& reason): reason_{reason} { }

    std::string reason() const { return reason_; }

private:
    std::string reason_;
};



// A DigraphEdge lists a "from vertex" (the number of the vertex from which
// the edge points), a "to vertex" (the number of the vertex to which the
// edge points), and an EdgeInfo object.  Because different kinds of Digraphs
// store different kinds of edge information, DigraphEdge is a template
// struct.

template <typename EdgeInfo>
struct DigraphEdge
{
    int fromVertex;
    int toVertex;
    EdgeInfo einfo;
};



// A DigraphVertex includes two things: a VertexInfo object and a list of
// its outgoing edges.  Because different kinds of Digraphs store different
// kinds of vertex and edge information, DigraphVertex is a template struct.

template <typename VertexInfo, typename EdgeInfo>
struct DigraphVertex
{
    VertexInfo vinfo;
    std::list<DigraphEdge<EdgeInfo>> edges;
};



// Digraph is a class template that represents a directed graph implemented
// using adjacency lists.  It takes two type parameters:
//
// * VertexInfo, which specifies the kind of object stored for each vertex
// * EdgeInfo, which specifies the kind of object stored for each edge
//
// You'll need to implement the member functions declared here; each has a
// comment detailing how it is intended to work.
//
// Each vertex in a Digraph is identified uniquely by a "vertex number".
// Vertex numbers are not necessarily sequential and they are not necessarily
// zero- or one-based.

template <typename VertexInfo, typename EdgeInfo>
class Digraph
{
public:
    // The default constructor initializes a new, empty Digraph so that
    // contains no vertices and no edges.
    Digraph();

    // The copy constructor initializes a new Digraph to be a deep copy
    // of another one (i.e., any change to the copy will not affect the
    // original).
    Digraph(const Digraph& d);

    // The move constructor initializes a new Digraph from an expiring one.
    Digraph(Digraph&& d);

    // The destructor deallocates any memory associated with the Digraph.
    ~Digraph();

    // The assignment operator assigns the contents of the given Digraph
    // into "this" Digraph, with "this" Digraph becoming a separate, deep
    // copy of the contents of the given one (i.e., any change made to
    // "this" Digraph afterward will not affect the other).
    Digraph& operator=(const Digraph& d);

    // The move assignment operator assigns the contents of an expiring
    // Digraph into "this" Digraph.
    Digraph& operator=(Digraph&& d);

    // vertices() returns a std::vector containing the vertex numbers of
    // every vertex in this Digraph.
    std::vector<int> vertices() const;

    // edges() returns a std::vector of std::pairs, in which each pair
    // contains the "from" and "to" vertex numbers of an edge in this
    // Digraph.  All edges are included in the std::vector.
    std::vector<std::pair<int, int>> edges() const;

    // This overload of edges() returns a std::vector of std::pairs, in
    // which each pair contains the "from" and "to" vertex numbers of an
    // edge in this Digraph.  Only edges outgoing from the given vertex
    // number are included in the std::vector.  If the given vertex does
    // not exist, a DigraphException is thrown instead.
    std::vector<std::pair<int, int>> edges(int vertex) const;

    // vertexInfo() returns the VertexInfo object belonging to the vertex
    // with the given vertex number.  If that vertex does not exist, a
    // DigraphException is thrown instead.
    VertexInfo vertexInfo(int vertex) const;

    // edgeInfo() returns the EdgeInfo object belonging to the edge
    // with the given "from" and "to" vertex numbers.  If either of those
    // vertices does not exist *or* if the edge does not exist, a
    // DigraphException is thrown instead.
    EdgeInfo edgeInfo(int fromVertex, int toVertex) const;

    // addVertex() adds a vertex to the Digraph with the given vertex
    // number and VertexInfo object.  If there is already a vertex in
    // the graph with the given vertex number, a DigraphException is
    // thrown instead.
    void addVertex(int vertex, const VertexInfo& vinfo);

    // addEdge() adds an edge to the Digraph pointing from the given
    // "from" vertex number to the given "to" vertex number, and
    // associates with the given EdgeInfo object with it.  If one
    // of the vertices does not exist *or* if the same edge is already
    // present in the graph, a DigraphException is thrown instead.
    void addEdge(int fromVertex, int toVertex, const EdgeInfo& einfo);

    // removeVertex() removes the vertex (and all of its incoming
    // and outgoing edges) with the given vertex number from the
    // Digraph.  If the vertex does not exist already, a DigraphException
    // is thrown instead.
    void removeVertex(int vertex);

    // removeEdge() removes the edge pointing from the given "from"
    // vertex number to the given "to" vertex number from the Digraph.
    // If either of these vertices does not exist *or* if the edge
    // is not already present in the graph, a DigraphException is
    // thrown instead.
    void removeEdge(int fromVertex, int toVertex);

    // vertexCount() returns the number of vertices in the graph.
    int vertexCount() const;

    // edgeCount() returns the total number of edges in the graph,
    // counting edges outgoing from all vertices.
    int edgeCount() const;

    // This overload of edgeCount() returns the number of edges in
    // the graph that are outgoing from the given vertex number.
    // If the given vertex does not exist, a DigraphException is
    // thrown instead.
    int edgeCount(int vertex) const;

    // isStronglyConnected() returns true if the Digraph is strongly
    // connected (i.e., every vertex is reachable from every other),
    // false otherwise.
    bool isStronglyConnected() const;

    // findShortestPaths() takes a start vertex number and a function
    // that takes an EdgeInfo object and determines an edge weight.
    // It uses Dijkstra's Shortest Path Algorithm to determine the
    // shortest paths from the start vertex to every other vertex
    // in the graph.  The result is returned as a std::map<int, int>
    // where the keys are vertex numbers and the value associated
    // with each key k is the precedessor of that vertex chosen by
    // the algorithm.  For any vertex without a predecessor (e.g.,
    // a vertex that was never reached, or the start vertex itself),
    // the value is simply a copy of the key.
    std::map<int, int> findShortestPaths(
        int startVertex,
        std::function<double(const EdgeInfo&)> edgeWeightFunc) const;


private:
    // Add whatever member variables you think you need here.  One
    // possibility is a std::map where the keys are vertex numbers
    // and the values are DigraphVertex<VertexInfo, EdgeInfo> objects.

    std::map<int,DigraphVertex<VertexInfo,EdgeInfo>> graph;
    int eCount = 0;
    int vCount = 0;

    // You can also feel free to add any additional member functions
    // you'd like (public or private), so long as you don't remove or
    // change the signatures of the ones that already exist.

    void DFTr(int vertex, std::vector<bool> &visited) const;

    struct DijkstraNode
    {
        int vertex; //number of vertex
        bool flag;
        int predecessor;
        double distance;

        DijkstraNode(int v, bool f, int p, double d)
            :vertex(v),flag(f),predecessor(p),distance(d){}

        DijkstraNode(const DijkstraNode &node)
            :vertex(node.vertex),flag(node.flag),predecessor(node.predecessor),distance(node.distance) {}

        DijkstraNode()
            :vertex(0), flag(false), predecessor(0), distance(0.0) {}
    };

    struct Comparator
    {
        bool operator()(DijkstraNode const &a, DijkstraNode const &b)
        {
            return a.distance > b.distance;
        }
    };
};

// You'll need to define the member functions of your Digraph class
// template here.


template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo,EdgeInfo>::Digraph(){} //COMPLETE


template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo,EdgeInfo>::Digraph(const Digraph &d) //COMPLETE
{
    graph.clear();
    graph.insert(d.graph.begin(),d.graph.end());
}


template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo,EdgeInfo>::Digraph(Digraph &&d) //COMPLETE
{
    graph.clear();
    graph.insert(d.graph.begin(),d.graph.end());
    d.graph.clear();
}


template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo,EdgeInfo>::~Digraph(){} //COMPLETE


template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo,EdgeInfo> &Digraph<VertexInfo,EdgeInfo>::operator=(const Digraph &d) //COMPLETE
{
    graph.clear();
    graph.insert(d.graph.begin(),d.graph.end());
    return *this;
}


template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo,EdgeInfo> &Digraph<VertexInfo,EdgeInfo>::operator=(Digraph &&d) //COMPLETE
{
    graph.clear();
    graph.insert(d.graph.begin(),d.graph.end());
    d.graph.clear();
    return *this;
}


template <typename VertexInfo, typename EdgeInfo>
std::vector<int> Digraph<VertexInfo,EdgeInfo>::vertices() const //COMPLETE
{
    std::vector<int> vertexVect;
    for (auto pairs:graph)
        vertexVect.push_back(pairs.first);
    return vertexVect;
}


template <typename VertexInfo, typename EdgeInfo>
std::vector<std::pair<int,int>> Digraph<VertexInfo,EdgeInfo>::edges() const //COMPLETE
{
    std::vector<std::pair<int,int>> edgeVect;
    std::vector<int> vertVect = vertices();
    for (int i = 0; i < vertVect.size(); i++)
    {
        for (auto i:graph.find(vertVect[i])->second.edges)
            edgeVect.push_back(std::make_pair(i.fromVertex,i.toVertex));
    }

    return edgeVect;
}


template <typename VertexInfo, typename EdgeInfo>
std::vector<std::pair<int,int>> Digraph<VertexInfo,EdgeInfo>::edges(int vertex) const //COMPLETE 
{
    if (graph.find(vertex) == graph.end())
        throw DigraphException("Vertex does not exist");
    std::vector<std::pair<int,int>> edgeVect;
    for (auto i:graph.find(vertex)->second.edges)
        edgeVect.push_back(std::make_pair(i.fromVertex,i.toVertex));
    return edgeVect;
}


template <typename VertexInfo, typename EdgeInfo>
VertexInfo Digraph<VertexInfo,EdgeInfo>::vertexInfo(int vertex) const //COMPLETE
{
    if (graph.find(vertex) == graph.end())
        throw DigraphException("Vertex does not exist");
    return graph.find(vertex)->second.vinfo;
}


template <typename VertexInfo, typename EdgeInfo> //COMPLETE
EdgeInfo Digraph<VertexInfo,EdgeInfo>::edgeInfo(int fromVertex, int toVertex) const
{
    if (graph.find(fromVertex) == graph.end() || graph.find(toVertex) == graph.end()) 
        throw DigraphException("Outgoing vertex or incoming vertex does not exist");
    for (auto i:graph.find(fromVertex)->second.edges)
    {
        if (i.toVertex == toVertex)
            return i.einfo;
    }
    throw DigraphException("Edge not found");
}


template <typename VertexInfo, typename EdgeInfo>
void Digraph<VertexInfo,EdgeInfo>::addVertex(int vertex, const VertexInfo &vinfo) //COMPLETE
{
    if (graph.find(vertex) != graph.end())
        throw DigraphException("Vertex already exists");
    DigraphVertex<VertexInfo,EdgeInfo> newVert;
    newVert.vinfo = vinfo;
    graph.insert(std::make_pair(vertex,newVert));
    vCount++;
}


template <typename VertexInfo, typename EdgeInfo> //COMPLETE
void Digraph<VertexInfo,EdgeInfo>::addEdge(int fromVertex, int toVertex, const EdgeInfo &einfo)
{
    if (graph.find(fromVertex) == graph.end() || graph.find(toVertex) == graph.end())
        throw DigraphException("Outgoing or incoming vertex does not exist");
    DigraphEdge<EdgeInfo> newEdge;
    newEdge.fromVertex = fromVertex;
    newEdge.toVertex = toVertex;
    newEdge.einfo = einfo;
    graph.find(fromVertex)->second.edges.push_back(newEdge);
    eCount++;
}


template <typename VertexInfo, typename EdgeInfo>
void Digraph<VertexInfo,EdgeInfo>::removeVertex(int vertex) //COMPLETE
{
    if (graph.find(vertex) == graph.end())
        throw DigraphException("Vertex does not exist");
    graph.erase(vertex);
    vCount--;
}


template <typename VertexInfo, typename EdgeInfo>
void Digraph<VertexInfo,EdgeInfo>::removeEdge(int fromVertex, int toVertex) //COMPLETE
{
    if (graph.find(fromVertex) == graph.end() || graph.find(toVertex) == graph.end())
       throw DigraphException("Outgoing or incoming vertex does not exist");

    typename std::list<DigraphEdge<EdgeInfo>>::iterator it;
    it = graph.find(fromVertex)->second.edges.begin();

    for (auto i:graph.find(fromVertex)->second.edges)
    {
        if (i.fromVertex == fromVertex && i.toVertex == toVertex)
        {
            it = graph.find(fromVertex)->second.edges.erase(it);
            return;
        }
        else
            ++it;
    }
    eCount--;
}


template <typename VertexInfo, typename EdgeInfo>
int Digraph<VertexInfo,EdgeInfo>::vertexCount() const //COMPLETE
{
    return vCount;
}


template <typename VertexInfo, typename EdgeInfo>
int Digraph<VertexInfo,EdgeInfo>::edgeCount() const //COMPLETE
{
    return eCount;
}


template <typename VertexInfo, typename EdgeInfo>
int Digraph<VertexInfo,EdgeInfo>::edgeCount(int vertex) const //COMPLETE
{
    std::vector<std::pair<int,int>> edgeCount = edges(vertex);
    return edgeCount.size();
}


template <typename VertexInfo, typename EdgeInfo>
bool Digraph<VertexInfo,EdgeInfo>::isStronglyConnected() const //COMPLETE
{
    for (int i = 0; i < vertices().size(); i++)
    {
        std::vector<bool> visited(vertices().size());
        DFTr(i, visited);
        if (find(visited.begin(), visited.end(), false) != visited.end())
            return false;
    }
    return true;
}


template <typename VertexInfo, typename EdgeInfo>
std::map<int,int> Digraph<VertexInfo,EdgeInfo>::findShortestPaths(
    int startVertex,
    std::function<double(const EdgeInfo&)> edgeWeightFunc) const
{
    std::map<int,int> shortestPaths;
    shortestPaths[startVertex] = startVertex;
    std::vector<int> v = vertices();
    std::map<int, DijkstraNode> DNodes;
    
    for (int i = 0; i < v.size(); ++i)
    {
        DNodes[v[i]] = DijkstraNode(v[i],false,0,std::numeric_limits<double>::max());
    }

        DNodes.at(startVertex).distance = 0;
        DNodes.at(startVertex).predecessor = startVertex;
        DNodes.at(startVertex).flag = true;

    std::priority_queue<int, std::vector<DijkstraNode>, Comparator> order;
    order.push(DNodes.at(startVertex));

    while(!order.empty())
    {
        if(!order.top().flag)
        {
            DijkstraNode v = DijkstraNode(std::move(order.top()));
            v.flag = true;
            order.pop();
            order.push(v);
        }

        std::vector<std::pair<int,int>> connections = edges(order.top().vertex);

        for (auto it = connections.begin(); it!= connections.end(); ++it)
        {
            int v0 = it->first;
            int v1 = it->second;
            double cost = DNodes.at(v0).distance + edgeWeightFunc(edgeInfo(v0,v1));

            if(DNodes.at(v1).distance > cost)
            {
                DNodes.at(v1).distance = cost;
                DNodes.at(v1).predecessor = v0;
                order.push(DNodes.at(v1));
                shortestPaths[v1] = v0;
            }
        }
        order.pop();
    }

    return shortestPaths;
}


//HELPER FUNCTIONS---------------------------------------------------


template <typename VertexInfo, typename EdgeInfo>
void Digraph<VertexInfo,EdgeInfo>::DFTr(int vertex, std::vector<bool> &visited) const //DONE
{
    visited[vertex] = true;

    for (auto i : graph.find(vertex)->second.edges)
    {
        if (!visited[i.toVertex])
            DFTr(i.toVertex, visited);
    }
}


#endif // DIGRAPH_HPP

