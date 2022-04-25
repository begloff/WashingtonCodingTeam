//final_proj.cpp
//WashingtonCodingTeam

#include "../include/roadtrip.h"

int main(){

    //Goal 1 work on reading in cities and making them vertices
    Graph< STRING > graph;
    STACK < unsigned int > finalPath;

    STRING cities_filepath = "include/distance/ap.txt"; //Filepath that corresponds to each city and attraction points
    STRING edges_filepath = "include/distance/input.txt"; //Filepath that contains all distances between cities

    UNOR_MAP < STRING , int > city_order; //Stores City --> Number
    UNOR_MAP < int, STRING > city_number; //Stores Number --> City

    STRING origin_city, destin_city;

    //Reads in origin and destin from the user
    COUT << "Please enter an origin city: ";
    GETLINE(CIN,origin_city);
    COUT << "Please enter a destination city: ";
    GETLINE(CIN,destin_city);

    //Reads in the nodes and populates both maps
    read_in_cities(graph,cities_filepath,city_order,city_number);

    //Reads in edges and connects nodes
    connect_cities(graph,edges_filepath,city_order);

    auto origin_number = city_order.find(origin_city);
    auto destin_number = city_order.find(destin_city);

    finalPath = graph.Dijkstra(origin_number->second,destin_number->second);

    graph.print_graph();

    print_order(finalPath,city_number,origin_city,destin_city);

    return 0;
}