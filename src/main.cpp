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
#include <cstdio>

int main(){


    //Goal 1 work on reading in cities and making them vertices
    Graph< STRING > graph;

    STRING cities_filepath = "../distance/origin.txt";
    STRING edges_filepath = "../distance/input.txt";
    IFSTREAM read_cities, read_edges;
    read_cities.open(cities_filepath);
    read_edges.open(edges_filepath);

    char buffer[BUFSIZ];
    char *city_name;
    UNOR_MAP < STRING , int > city_order;
    int i = 0;

// Reads in from file, adding each city name (string until ",") to the graph as a vertex/node. Also creates an ordered map with each city name and corresponding number
    while (read_cities.getline(buffer, BUFSIZ)) {
        city_name = strtok(buffer, ",");
        graph.add_vertex(city_name, 5);
        city_order.insert({ city_name , i});
        i++;
    }

    // Code for utilizing map to find number corresponding to each city
    //auto orig = city_order.find("San Francisco");
    //COUT << orig->second << ENDL;
    read_cities.close();
    //graph.print_graph();
    char *first_city;
    char *second_city;
    char *distance_string;
    int distance;

    while (read_edges.getline(buffer, BUFSIZ)) {
        first_city = strtok(buffer, ",");
        second_city = strtok(NULL, ",");
        distance_string = strtok(NULL, ",");
        distance = atoi(distance_string);
        
        //auto orig = city_order.find(first_city);
        //COUT << first_city << ENDL;
    }

    return 0;
}