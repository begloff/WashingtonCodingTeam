//main.cpp
//WashingtonCodingTeam

#include "../include/Edge.h"
#include "../include/Vertex.h"
#include "../include/Graph.h"

#include <cstdlib>
#include <string>

int main(){


    //Goal 1 work on reading in cities and making them vertices

    Graph< std::string > new_graph;

    for( int i = 0; i < 5; i++){
        std::string origin;
        std::cout << "Please enter a city: ";
        std::cin >> origin;

        new_graph.add_vertex(origin,i);
    }

    new_graph.print_graph();

    return 0;
}