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
        float weight = distance / total_ap;

        //Penalize longer distances: 200 < 500 < 1000 < 1500 < 2000 < 2500

        if( distance < 200 ){ //Incentivize short distance travel to cities
            weight = weight/3;
        }

        if( distance > 200 && distance < 500 ){
            weight = weight/2;
        }

        if( distance > 500 && distance < 1000 ){
            weight = weight * (3/2) ;
        }

        if( distance > 1000 && distance < 1500 ){
            weight += 5;
        }

        if( distance > 1500 && distance < 2000 ){
            weight += 40;
        }

        if( distance > 2000 && distance < 2500 ){
            weight += 50;
        }

        if( distance > 2500 ){
            weight += 100;
        }        
        
        //adds edge between two cities with weight as distance/total_ap
        graph.add_edge(orig->second, destin->second, weight, distance);

    }

    return;
}

void print_order( VECTOR< unsigned int > finalPath, UNOR_MAP < int, STRING > city_number, STRING origin_city, STRING destin_city ){

    
    COUT << STRING(65,'=') << ENDL;
    COUT << "The optimal roadtrip from " << origin_city << " to " << destin_city << " is: " << ENDL;


    for( long unsigned int i = finalPath.size(); i > 0 ; i-- ){

        auto current_city = city_number.find( finalPath[i-1] );

        if( i != 1 ){
            COUT << current_city->second << " -> ";
        } else {
            COUT << current_city->second << ENDL;
        }
        
    }

}

void print_stats( VECTOR< unsigned int > finalPath, Graph < STRING >& graph, STRING origin_city, STRING destin_city ){

    COUT << STRING(65,'=') << ENDL;

    COUT << "Total number of cities visited: " << finalPath.size() << ENDL;

    COUT << STRING(65,'=') << ENDL;

    float short_line_distance = 0, traveled_distance = 0;
    unsigned int sz_of_path = (unsigned int) finalPath.size() - 1;

    unsigned int origin, destin;

    origin = finalPath[sz_of_path];
    if( finalPath[0] > origin ) destin = finalPath[0] - 1;
    else destin = finalPath[0];

    short_line_distance = graph.return_dist_edge( origin, destin );

    //Find the total number of miles traveled --> search edges for length between nodes
    for( unsigned int i = (unsigned int) finalPath.size() - 1; i > 0 ; i-- ){

        //Find the milage between each node: example, size 4: 3->2 2->1 1->0
        origin = finalPath[i];
        if( finalPath[i-1] > origin ) destin = finalPath[i-1] - 1;
        else destin = finalPath[i-1];

        //Takes the distance of said edge and adds to a running total
        traveled_distance += graph.return_dist_edge( origin, destin );

    }

    COUT << "The straight path from " << origin_city << " to " << destin_city << " is " << short_line_distance << " miles" << ENDL << ENDL;
    COUT << "The suggested roadtrip from " << origin_city << " to " << destin_city << " is " << traveled_distance << " miles" << ENDL << ENDL;

    COUT << "The suggested roadtrip visits " << finalPath.size() - 2 << " more cities, traveling " << traveled_distance - short_line_distance << " more miles" << ENDL; 

    COUT << STRING(65,'=') << ENDL;

}
