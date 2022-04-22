//roadtrip.cpp

#include "../include/roadtrip.h"


void read_in_cities( Graph < STRING >& graph, STRING& cities_filepath, UNOR_MAP < STRING , int >& city_order ){

    IFSTREAM read_cities;
    read_cities.open(cities_filepath);

    char buffer[BUFSIZ];
    char *city_name;
    char *city_state;
    char *attraction_points;
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

    read_cities.close();

    return;

}

void connect_cities( Graph < STRING >& graph, STRING& edges_filepath, UNOR_MAP < STRING , int >& city_order ){

    IFSTREAM read_edges;
    read_edges.open(edges_filepath);

    char *first_city;
    char *second_city;
    char *distance_string;
    int distance;

    char buffer[BUFSIZ];

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

    }

    return;
}
