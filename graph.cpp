#include "graph.h"

const Vertex Graph::InvalidVertex = "_CS225INVALIDVERTEX";
const int Graph::InvalidWeight = INT_MIN;
const string Graph:: InvalidLabel = "_CS225INVALIDLABEL";
const Edge Graph::InvalidEdge = Edge(Graph::InvalidVertex, Graph::InvalidVertex, Graph::InvalidWeight, Graph::InvalidLabel);

Graph::Graph(bool weighted) : weighted(weighted),directed(false)
{
}

Graph::Graph(bool weighted, bool directed) : weighted(weighted),directed(directed)
{
}

void Graph::loadData(string fileName) {
    Vertex start = "";
    std::ifstream infile(fileName);
    std::string line;
    std::getline(infile, line); // Get rid of first line
    while (std::getline(infile, line)) {
        std::istringstream buffer(line);
        std::vector<std::string> results((std::istream_iterator<std::string>(buffer)), // Parse string into vector separated by spaces
                                 std::istream_iterator<std::string>());
        if (start == "") {
            start = results[0];
        }
        if (!vertexExists(results[0])) {
            insertVertex(results[0]); // Insert source vertex if it doesn't exist
        }
        if (!vertexExists(results[1])) {
            insertVertex(results[1]); // Insert destination vertex if it doesn't exists
        }
        if (!edgeExists(results[0], results[1])) {
            insertEdge(results[0], results[1]); // Insert edge from that line
            setEdgeWeight(results[0], results[1], 1);
        } else {
            // Each link increases edge weight by one
            setEdgeWeight(results[0], results[1], getEdgeWeight(results[0], results[1]) + 1); 
        }
    }
    for (Edge e : getEdges()) {
        /**
         * Edges are reassessed so that each weight is a positive integer such that the cost
         * of an edge with n occurences is roughly 1/n the cost of an edge with 1 occurence
         */
        setEdgeWeight(e.source, e.dest, 10000 / getEdgeWeight(e.source, e.dest));
    }
}

void Graph::BFS() {
    std::unordered_set<std::string> traversed;
    std::queue<std::string> queue;
    srand(time(NULL)); // Set seed to be current time
    Vertex random = getVertices()[rand() % getVertices().size()];
    queue.push(random);
    while (!queue.empty()) {
        std::string current = queue.front();
        std::cout << current << std::endl;
        traversed.insert(current);
        queue.pop();

        for (Vertex neighbor : getAdjacent(current)) {
            if (edgeExists(current, neighbor) && traversed.find(neighbor) == traversed.end()) {
                queue.push(neighbor);
                traversed.insert(neighbor);
            }
        }
    }
}

void Graph::Djikstra(Vertex start, Vertex end) {
    list<Vertex> path = DjikstraPath(start, end);
    if (path.size() == 0) {
        cout << "No path between " << start << " and " << end << endl;
    } else {
        for (Vertex v : path) {
            cout << v << endl;
        }
    }
}

list<Vertex> Graph::DjikstraPath(Vertex start, Vertex end) {
    unordered_map<Vertex, int> dist;
    unordered_map<Vertex, Vertex> prev;

    dist[start] = 0;

    std::priority_queue<Node, vector<Node>, std::greater<Node>> myHeap;
    // Initialize the heap 
    for (Vertex v : getVertices()) {
        if (v != start) {
            dist[v] = INT_MAX;
            prev[v] = "";
        }
        myHeap.push(Node(v, dist[v]));
    }

    /*while (!myHeap.empty()) {
        cout << myHeap.top().v << " " << myHeap.top().d << endl;
        myHeap.pop();
    }
    return list<Vertex>();*/

    while (!myHeap.empty()) {
        Node current = myHeap.top();
        myHeap.pop();
        //cout << "Popped " << current.v << " with cost " << current.d << endl;

        if (current.d > dist[current.v]) {
            //cout << "Ignoring " << current.v << endl;
            continue;
        }

        // There is no path to the vertex so we break out of the loop
        if (current.v == end) {
            break;
        }

        for (Vertex neighbor: getAdjacent(current.v)) {
            if (edgeExists(current.v, neighbor)) {
                int weight = dist[current.v] + getEdgeWeight(current.v, neighbor);
                if (weight < dist[neighbor]) {
                    dist[neighbor] = weight;
                    prev[neighbor] = current.v;
                    myHeap.push(Node(neighbor, weight));
                }
            }
        }
    }

    list<Vertex> path;
    Vertex current = end;
    while (prev[current] != "" || current == start) {
        path.push_front(current);
        if (current != start) {
            current = prev[current];
        } else {
            break;
        }
    }

    return path;
}

void Graph::Landmark(Vertex start, Vertex landmark, Vertex end) {
    for (Vertex v : DjikstraPath(start, landmark)) {
        cout << v << endl;
    }
    list<Vertex> toEnd = DjikstraPath(landmark, end);
    for (Vertex v : toEnd) {
        if (v == toEnd.front()) {
            continue;
        }
        cout << v << endl;
    }
}


vector<Vertex> Graph::getAdjacent(Vertex source) const 
{
    auto lookup = adjacency_list.find(source);

    if(lookup == adjacency_list.end())
        return vector<Vertex>();

    else
    {
        vector<Vertex> vertex_list;
        unordered_map <Vertex, Edge> & map = adjacency_list[source];
        for (auto it = map.begin(); it != map.end(); it++)
        {
            vertex_list.push_back(it->first);
        }
        return vertex_list;
    }
}


Vertex Graph::getStartingVertex() const
{
    return adjacency_list.begin()->first;
}

vector<Vertex> Graph::getVertices() const
{
    vector<Vertex> ret;

    for(auto it = adjacency_list.begin(); it != adjacency_list.end(); it++)
    {
        ret.push_back(it->first);
    }

    return ret;
}

Edge Graph::getEdge(Vertex source , Vertex destination) const
{
    if(assertEdgeExists(source, destination, __func__) == false)
        return Edge();
    Edge ret = adjacency_list[source][destination];
    return ret;
}

vector<Edge> Graph::getEdges() const
{
    if (adjacency_list.empty())
        return vector<Edge>();

    vector<Edge> ret;
    set<pair<Vertex, Vertex> > seen;

    for (auto it = adjacency_list.begin(); it != adjacency_list.end(); it++)
    {
        Vertex source = it->first;
        for (auto its = adjacency_list[source].begin(); its != adjacency_list[source].end(); its++)
        {
            Vertex destination = its->first;
            if(seen.find(make_pair(source, destination)) == seen.end())
            {
                //this pair is never added to seen
                ret.push_back(its->second);
                seen.insert(make_pair(source,destination));
                if(!directed)
                {
                    seen.insert(make_pair(destination, source));
                }
            }
        }
    }

    return ret;
}

bool Graph::vertexExists(Vertex v) const
{
    return assertVertexExists(v, "");
}

bool Graph::edgeExists(Vertex source, Vertex destination) const
{
    return assertEdgeExists(source, destination, "");
}

Edge Graph::setEdgeLabel(Vertex source, Vertex destination, string label)
{
    if (assertEdgeExists(source, destination, __func__) == false)
        return InvalidEdge;
    Edge e = adjacency_list[source][destination];
    Edge new_edge(source, destination, e.getWeight(), label);
    adjacency_list[source][destination] = new_edge;

    if(!directed)
    {
        Edge new_edge_reverse(destination,source, e.getWeight(), label);
        adjacency_list[destination][source] = new_edge_reverse;
    }
    return new_edge;
}


string Graph::getEdgeLabel(Vertex source, Vertex destination) const
{
    if(assertEdgeExists(source, destination, __func__) == false)
        return InvalidLabel;
    return adjacency_list[source][destination].getLabel();
}

int Graph::getEdgeWeight(Vertex source, Vertex destination) const
{
    if (!weighted)
        error("can't get edge weights on non-weighted graphs!");

    if(assertEdgeExists(source, destination, __func__) == false)
        return InvalidWeight;
    return adjacency_list[source][destination].getWeight();
}

void Graph::insertVertex(Vertex v)
{
    // will overwrite if old stuff was there
    removeVertex(v);
    // make it empty again
    adjacency_list[v] = unordered_map<Vertex, Edge>();
}


Vertex Graph::removeVertex(Vertex v)
{

    if (adjacency_list.find(v) != adjacency_list.end())
    {
        if(!directed){
            for (auto it = adjacency_list[v].begin(); it != adjacency_list[v].end(); it++)
            {
                Vertex u = it->first;
                adjacency_list[u].erase(v); 
            }
            adjacency_list.erase(v);
            return v;
        }
        
        adjacency_list.erase(v);
        for(auto it2 = adjacency_list.begin(); it2 != adjacency_list.end(); it2++)
        {
            Vertex u = it2->first;
            if (it2->second.find(v)!=it2->second.end())
            {
                it2->second.erase(v);
            }
        }
        return v;
    }

    return InvalidVertex;
}

bool Graph::insertEdge(Vertex source, Vertex destination)
{
    if(adjacency_list.find(source)!= adjacency_list.end() 
    && adjacency_list[source].find(destination)!= adjacency_list[source].end())
    {
        //edge already exit
        return false;
    }

    if(adjacency_list.find(source)==adjacency_list.end())
    {
        adjacency_list[source] = unordered_map<Vertex, Edge>();
    }
        //source vertex exists
    adjacency_list[source][destination] = Edge(source, destination);
    if(!directed)
    {
        if(adjacency_list.find(destination)== adjacency_list.end())
        {
            adjacency_list[destination] = unordered_map<Vertex, Edge>();
        }
        adjacency_list[destination][source] = Edge(source, destination);
    }
    
    return true;
}

Edge Graph::removeEdge(Vertex source, Vertex destination)
{
    if(assertEdgeExists(source, destination, __func__) == false)
        return InvalidEdge;
    Edge e = adjacency_list[source][destination];
    adjacency_list[source].erase(destination);
    // if undirected, remove the corresponding edge
    if(!directed)
    {
        adjacency_list[destination].erase(source);
    }
    return e;
}


Edge Graph::setEdgeWeight(Vertex source, Vertex destination, int weight)
{
    if (assertEdgeExists(source, destination, __func__) == false)
        return InvalidEdge;
    Edge e = adjacency_list[source][destination];
    //std::cout << "setting weight: " << weight << std::endl;
    Edge new_edge(source, destination, weight, e.getLabel());
    adjacency_list[source][destination] = new_edge;

    if(!directed)
        {
            Edge new_edge_reverse(destination,source, weight, e.getLabel());
            adjacency_list[destination][source] = new_edge_reverse;
        }

    return new_edge;
}

bool Graph::assertVertexExists(Vertex v, string functionName) const
{
    if (adjacency_list.find(v) == adjacency_list.end())
    {
        if (functionName != "")
            error(functionName + " called on nonexistent vertices");
        return false;
    }
    return true;
}

bool Graph::assertEdgeExists(Vertex source, Vertex destination, string functionName) const
{
    if(assertVertexExists(source,functionName) == false)
        return false;
    if(adjacency_list[source].find(destination)== adjacency_list[source].end())
    {
        if (functionName != "")
            error(functionName + " called on nonexistent edge " + source + " -> " + destination);
        return false;
    }

    if(!directed)
    {
        if (assertVertexExists(destination,functionName) == false)
            return false;
        if(adjacency_list[destination].find(source)== adjacency_list[destination].end())
        {
            if (functionName != "")
                error(functionName + " called on nonexistent edge " + destination + " -> " + source);
            return false;
        }
    }
    return true;
}

bool Graph::isDirected() const
{
    return directed;
}

void Graph::clear()
{
    adjacency_list.clear();
}


/**
 * Prints a graph error and quits the program.
 * The program is exited with a segfault to provide a stack trace.
 * @param message - the error message that is printed
 */
void Graph::error(string message) const
{
    cerr << "\033[1;31m[Graph Error]\033[0m " + message << endl;
}



/**
 * Prints the graph to stdout.
 */
void Graph::print() const
{
    for (auto it = adjacency_list.begin(); it != adjacency_list.end(); ++it) 
    {
        cout << it->first << endl;
        for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) 
        {
            std::stringstream ss;
            ss << it2->first; 
            string vertexColumn = "    => " + ss.str();
            vertexColumn += " " ;
            cout << std::left << std::setw(26) << vertexColumn;
            string edgeColumn = "edge label = \"" + it2->second.getLabel()+ "\"";
            cout << std::left << std::setw(26) << edgeColumn;
            if (weighted)
                cout << "weight = " << it2->second.getWeight();
            cout << endl;
        }
        cout << endl;
    }
}