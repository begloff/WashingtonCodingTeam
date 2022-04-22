//final_proj.cpp
//WashingtonCodingTeam

#include "../include/roadtrip.h"

int main(){


    //Goal 1 work on reading in cities and making them vertices
    Graph< STRING > graph;

    STRING cities_filepath = "include/distance/ap.txt";
    STRING edges_filepath = "include/distance/input.txt";

    UNOR_MAP < STRING , int > city_order;
    /*IFSTREAM read_cities, read_edges;
    read_cities.open(cities_filepath);
    read_edges.open(edges_filepath);

    char buffer[BUFSIZ];
    char *city_name;
    char *city_state;
    char *attraction_points;
    UNOR_MAP < STRING , int > city_order;
    int i = 0;

// Reads in from file, adding each city name (string until ",") to the graph as a vertex/node. Also creates an ordered map with each city name and corresponding number
    while (read_cities.getline(buffer, BUFSIZ)) {

        city_name = strtok(buffer, ",");
        city_state = strtok(NULL,",");
        attraction_points = strtok(NULL,",");

        graph.add_vertex(city_name, city_state,atoi(attraction_points));
        city_order.insert({ city_name , i});
        i++;

    }

    // Code for utilizing map to find number corresponding to each city
    //auto orig = city_order.find("San Francisco");
    //COUT << orig->second << ENDL;
    read_cities.close();*/
    //graph.print_graph();
    /*char *first_city;
    char *second_city;
    char *distance_string;
    int distance;

    while (read_edges.getline(buffer, BUFSIZ)) {
        first_city = strtok(buffer, ",");
        second_city = strtok(NULL, ",");
        distance_string = strtok(NULL, ",");
        distance = atoi(distance_string);
        
        auto orig = city_order.find(first_city);
        auto destin = city_order.find(second_city);

        //gets the total number of attraction points between two nodes
        unsigned int total_ap = graph.get_ap_of_vertex(orig->second) + graph.get_ap_of_vertex(destin->second);
        unsigned int weight = (unsigned int) distance/total_ap;
        
        //adds edge between two cities with weight as distance/total_ap
        graph.add_edge(orig->second, destin->second, weight);
        //COUT << first_city << ENDL;
    }*/

    read_in_cities(graph,cities_filepath,city_order);
    connect_cities(graph,edges_filepath,city_order);

    graph.print_graph();

    return 0;
}