//main.cpp
//WashingtonCodingTeam

#include "../include/Edge.h"
#include "../include/Vertex.h"
#include "../include/Graph.h"

#include <cstdlib>
#include <string>
#include <fstream>
#include <cstring>
#include <iostream>

int main(){


    //Goal 1 work on reading in cities and making them vertices
    Graph< STRING > new_graph;
    // for( int i = 0; i < 5; i++){
    //     std::string origin;
    //     std::cout << "Please enter a city: ";
    //     std::cin >> origin;
    //     new_graph.add_vertex(origin,i);
    // }
    // new_graph.print_graph();

    STRING filepath = "../distance/origin.txt";

    IFSTREAM read_file;
    read_file.open(filepath);
    char full_city[256];
    char *city_name;


    while (read_file.getline(full_city, 256)) {
        city_name = strtok(full_city, ",");
        new_graph.add_vertex(city_name, 0);
    }

    read_file.close();
    new_graph.print_graph();

    return 0;
}