//roadtrip.cpp

#include "../include/roadtrip.h"


void read_in_cities( Graph < STRING >& graph, STRING& cities_filepath, UNOR_MAP < STRING , int >& city_order, UNOR_MAP < int , STRING >& city_number){

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

        graph.add_vertex(city_name, city_state,STOF(attraction_points));
        city_order.insert({ city_name , i});
        city_number.insert({ i , city_name });
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
    float distance;

    char buffer[BUFSIZ];

    while (read_edges.getline(buffer, BUFSIZ)) {

        first_city = strtok(buffer, ",");
        second_city = strtok(NULL, ",");
        distance_string = strtok(NULL, ",");
        distance = STOF(distance_string);
        
        auto orig = city_order.find(first_city);
        auto destin = city_order.find(second_city);

        //gets the total number of attraction points between two nodes
        float total_ap = graph.get_ap_of_vertex(orig->second);
        float weight = distance + total_ap;

        //Penalize longer distances: 200 < 500 < 1000 < 1500 < 2000 < 2500

        if( distance > 200 && distance < 500 ){
            weight += 50;
        }

        if( distance > 500 && distance < 1000 ){
            weight += 100;
        }

        if( distance > 1000 && distance < 1500 ){
            weight += 500;
        }

        if( distance > 1500 && distance < 2000 ){
            weight += 700;
        }

        if( distance > 2000 && distance < 2500 ){
            weight += 900;
        }

        if( distance > 2500 ){
            weight += 1100;
        }        
        
        //adds edge between two cities with weight as distance/total_ap
        graph.add_edge(orig->second, destin->second, weight);

    }

    return;
}

void print_order( STACK < unsigned int > finalPath, UNOR_MAP < int, STRING > city_number, STRING origin_city, STRING destin_city ){

    COUT << "The optimal roadtrip from " << origin_city << " to " << destin_city << " is: " << ENDL;

    while( !finalPath.empty() ){

        auto current_city = city_number.find( finalPath.top() );

        if( finalPath.size() != 1 ){
            COUT << current_city->second << " -> ";
        } else {
            COUT << current_city->second << ENDL;
        }
        
        finalPath.pop();
    }

}
