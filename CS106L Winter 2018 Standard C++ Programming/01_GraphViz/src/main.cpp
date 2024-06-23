#include <iostream>
#include "SimpleGraph.h"
#include<fstream>
#include<string>
#include <cstdlib>
#include <ctime> 

using std::cout;	using std::endl;

void Welcome();
std::vector<Node> InitalGraph(size_t n);
void read_file(SimpleGraph& graph, std::string& filename);
void force_directed_algorithum(SimpleGraph& graph);

const double krepel = 1e-3;
const double kattact = 1e-3;

// Main method
int main() {
    Welcome();

    while (true) {
		std::cout << "Please input the graph you want to visualize: " << endl;
        std::string graph_name = "";
        std::cin >> graph_name;

        std::string filename = "D:\\Major\\Course_Assignments\\CS106L Winter 2018 Standard C++ Programming\\01_GraphViz\\01_GraphViz\\res\\" + graph_name;
        SimpleGraph graph;

        read_file(graph, filename);

        InitGraphVisualizer(graph);
        DrawGraph(graph);

        double duration;
        cout << "Enter the elapsed time:";
        std::cin >> duration;

        time_t startTime = time(NULL);


        while (difftime(time(NULL), startTime) < duration) {
	        force_directed_algorithum(graph);
	        DrawGraph(graph);
        }
		std::string endOrNot, dummy;
        cout << "Press Y/y if you want to draw another graph: ";
        std::getline(std::cin, dummy);
        std::getline(std::cin, endOrNot);
        if (endOrNot != "Y" && endOrNot != "y")
            break;
    }

    return 0;
}

/* Prints a message to the console welcoming the user and
 * describing the program. */
void Welcome() {
    cout << "Welcome to CS106L GraphViz!" << endl;
    cout << "This program uses a force-directed graph layout algorithm" << endl;
    cout << "to render sleek, snazzy pictures of various graphs." << endl;
    cout << endl;
}


/*
* name: InitialGraph
* function: Initialize the coordinate of nodes
* parames:
    # size_t: n  The number of nodes
* return:
    # std::vector<Node>
*/
std::vector<Node> InitalGraph(size_t n) {

    std::vector<Node> nodes(n);

	double angle_increment = 2 * M_PI / n;

	double radius = 10.0; // 定义圆的半径

	for (int i = 0; i < n; ++i) {
        double angle = i * angle_increment;
        nodes[i] = {radius * cos(angle), radius * sin(angle)};
    }

    return nodes;
}

/*
* name: read_file 
* function: get the nodes infomation from file
* params: 
    # std::string filename: name of file
* return: 
    # Simplegraph 
*/
void read_file(SimpleGraph& graph , std::string& filename) {
    std::vector<Edge> edges;

    std::ifstream file(filename);

	if (!file) {
        std::cerr << "Unable to open file " << filename << std::endl;
        exit;
    }
	size_t node_count;
    file >> node_count;

    std::vector<Node> nodes = InitalGraph(node_count);

    int start = 0, end = 0;

    while (file >> start >> end) {
        Edge edge;
        edge.start = start;
        edge.end = end;

        edges.push_back(edge);
    }

    file.close();

    graph.nodes = nodes;
    graph.edges = edges;
}

/*
* name: force_directed_algorithum
* function: modifiy the coordinate of nodes by force-dircted algorithum
* params: 
    # SimpleGraph graph
    # double elapsedTime
* return:
*   # SimpleGraph graph
*/
void force_directed_algorithum(SimpleGraph& graph) {
    std::vector<Node> nodes = graph.nodes;
    std::vector<Edge> edges = graph.edges;

    size_t nodes_count = nodes.size();

    std::vector<std::pair<double, double>> delta(nodes_count);

    for (size_t i = 0; i < nodes_count; ++i) {
        for (size_t j = i + 1; j < nodes_count; ++j) {

			double dx = nodes[j].x - nodes[i].x;
            double dy = nodes[j].y - nodes[i].y;
            double dist2 = dx * dx + dy * dy; // (x1 - x0)^2 + (y1 - y0)^2
            
            if (dist2 == 0) continue; // Prevent division by zero
            
            double dist = std::sqrt(dist2);

			double Frepel = krepel / dist;

			double theta = std::atan2(dy, dx);

			double cosTheta = std::cos(theta);
            double sinTheta = std::sin(theta);

            delta[i].first -= Frepel * cosTheta;
            delta[i].second -= Frepel * sinTheta;
            delta[j].first += Frepel * cosTheta;
			delta[j].second += Frepel * sinTheta;
        }
    }

    size_t edges_count = edges.size();

    for (size_t i = 0; i < edges_count; ++i) {
        size_t point0 = edges[i].start;
        size_t point1 = edges[i].end;

        double x0 = nodes[point0].x;
        double y0 = nodes[point0].y;
        double x1 = nodes[point1].x;
        double y1 = nodes[point1].y;

        double dx = x1 - x0;
        double dy = y1 - y0;

		double dist2 = dx * dx + dy * dy;
		if (dist2 == 0) continue; // Prevent division by zero

        double Fattract = kattact * dist2;

		double theta = std::atan2(dy, dx);

		double cosTheta = std::cos(theta);
        double sinTheta = std::sin(theta);

        delta[point0].first += Fattract * cosTheta;
        delta[point0].second += Fattract * sinTheta;
        delta[point1].first -= Fattract * cosTheta;
        delta[point1].second -= Fattract * sinTheta;
    }

    for (size_t i = 0; i < nodes_count; ++i) {
        nodes[i].x += delta[i].first;
        nodes[i].y += delta[i].second;
    }

    graph.nodes = nodes;
    graph.edges = edges;

}