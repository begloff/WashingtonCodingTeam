/**********************************
 * Group: Washington Coding Team
 * Members: Benjamin Egloff, Will Truluck, Alex Potts, Steve Zhao
 * Email: begloff@nd.edu
 * File Name: roadtrip.cpp
 * Date Created: 4/27/2022
 * File Contents: This file contains the function definitions for CSE 20312 Final Project
 **********************************/

#include "../include/roadtrip.h"


void read_in_cities( Graph < STRING >& graph, STRING& cities_filepath, UNOR_MAP < STRING , int >& city_order, UNOR_MAP < int , STRING >& city_number){

    //opens IFSTREAM to read from file with all cities
    IFSTREAM read_cities;
    read_cities.open(cities_filepath);

    char buffer[BUFSIZ];
    char *city_name;
    char *city_state;
    char *attraction_points;
    int i = 0;

    // Reads in from file, adding each city name (string until ",") to the graph as a vertex/node. Also creates an ordered map with each city name and corresponding number
    while (read_cities.getline(buffer, BUFSIZ)) {

        //String parsing
        city_name = strtok(buffer, ",");
        city_state = strtok(NULL,",");
        attraction_points = strtok(NULL,",");

        //Adds vertex with city_name, city_state, attraction points, and visited members 
        graph.add_vertex(city_name, city_state,STOF(attraction_points),false);

        //Inserts into map so City_name can reference its insertion number and vice versa
        city_order.insert({ city_name , i});
        city_number.insert({ i , city_name });
        i++; //Insertion number

    }

    read_cities.close(); //Closes IFSTREAM

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

        //String parsing
        first_city = strtok(buffer, ",");
        second_city = strtok(NULL, ",");
        distance_string = strtok(NULL, ",");
        distance = STOF(distance_string);
        
        //Auto objects that store the map object returned by the find method
        auto orig = city_order.find(first_city);
        auto destin = city_order.find(second_city);

        //gets the total number of attraction points between two nodes
        float total_ap = graph.get_ap_of_vertex(orig->second);
        float weight = distance / total_ap;

        //Penalize longer distances: 200 < 500 < 1000 < 1500 < 2000 < 2500

        /*WORKING PART OF PROJECT
        A perfect scale is impossible to establish, so one that rewards short distance travel
        and penalizes long distance travel was chosen*/

        if( distance < 200 ){ //Incentivize short distance travel to cities
            weight = weight/3;
        }

        if( distance > 200 && distance < 500 ){
            weight = weight/2;
        }

        if( distance > 500 && distance < 1000 ){
            weight = weight / (3/2) ;
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

    read_edges.close(); //Closes IFSTREAM

    return;
}

void print_order( VECTOR< unsigned int > finalPath, Graph < STRING >& graph, UNOR_MAP < int, STRING > city_number, STRING origin_city, STRING destin_city ){

    //Ouput formatting
    COUT << STRING(150,'=') << ENDL;
    COUT << "The optimal roadtrip from " << origin_city << " to " << destin_city << " is: " << ENDL;


    for( long unsigned int i = finalPath.size(); i > 0 ; i-- ){ //Loops through finalpath vector

        auto current_city = city_number.find( finalPath[i-1] ); //References insertion number to city name

        if( i != 1 ){
            COUT << current_city->second << ", " << graph.get_state(current_city->first) << " -> "; //Prints out Name and state
        } else {
            COUT << current_city->second <<  ", " << graph.get_state(current_city->first) << ENDL; //Same as above but with new line, as it is the last city
        }
        
    }

}

void print_stats( VECTOR< unsigned int > finalPath, Graph < STRING >& graph, STRING origin_city, STRING destin_city ){
    //Prints the distance statistics for the final roadtrip path

    //Output formatting
    COUT << STRING(150,'=') << ENDL;

    COUT << "Total number of cities visited: " << finalPath.size() << ENDL;

    COUT << STRING(150,'=') << ENDL;


    float short_line_distance = 0, traveled_distance = 0;
    unsigned int sz_of_path = (unsigned int) finalPath.size() - 1;

    unsigned int origin, destin;

    //Due to edge insertion, need to check if the city number is before or after the origin
    //If after, need to subtract 1, as the city is skipped
    origin = finalPath[sz_of_path];
    if( finalPath[0] > origin ) destin = finalPath[0] - 1;
    else destin = finalPath[0];

    //Finds the distance directly to the city
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

    //Output formatting --> need to include city state, using get_state method

    COUT << "The straight path from " << origin_city << ", " << graph.get_state( finalPath[(unsigned int) finalPath.size() - 1] ) << " to " 
    << destin_city << ", " << graph.get_state(finalPath[0] ) << " is " << short_line_distance << " miles" << ENDL << ENDL;

    COUT << "The suggested roadtrip from " << origin_city << ", " << graph.get_state( finalPath[(unsigned int) finalPath.size() - 1] ) << " to " 
    << destin_city << ", " << graph.get_state(finalPath[0] ) << " is " << traveled_distance << " miles" << ENDL << ENDL;

    COUT << "The suggested roadtrip visits " << finalPath.size() - 2 << " more cities, traveling " << traveled_distance - short_line_distance << " more miles" << ENDL; 

    COUT << STRING(150,'=') << ENDL;

}

void visit_cities( VECTOR< unsigned int > finalPath, Graph < STRING >& graph ){
    //Makes visited member of nodes true so visited cities will not be returned to on return trip

    for( int i = (int)finalPath.size() - 1; i >= 0 ; i-- ){ //loop through final path

        if( i != 0 && i != (int)finalPath.size() - 1){ //all cities but the origin and destination

            graph.visit_city( finalPath[i] );

        }

    } 

}

void get_file_input( char *file_name, STRING& origin_city, STRING& destin_city){

    //Gets two cities from an external file

    IFSTREAM input_file; //Open Ifstream

    input_file.open(file_name); //open file for reading

    char buffer[BUFSIZ];

    
    //Read next two lines to get the two cities
    input_file.getline(buffer,BUFSIZ);
    origin_city = buffer;

    input_file.getline(buffer,BUFSIZ);
    destin_city = buffer;

    return;
}

void print_order_outfile( OFSTREAM& output_file, VECTOR< unsigned int > finalPath, Graph < STRING >& graph, UNOR_MAP < int, STRING > city_number, STRING origin_city, STRING destin_city ){
    //Same as other print_order function, just printing to output_file rather than COUT
    
    output_file << STRING(150,'=') << ENDL;
    output_file << "The optimal roadtrip from " << origin_city << " to " << destin_city << " is: " << ENDL;


    for( long unsigned int i = finalPath.size(); i > 0 ; i-- ){

        auto current_city = city_number.find( finalPath[i-1] );

        if( i != 1 ){
            output_file << current_city->second << ", " << graph.get_state(current_city->first) << " -> ";
        } else {
            output_file <<  current_city->second <<  ", " << graph.get_state(current_city->first) << ENDL;
        }
        
    }

}

void print_stats_outfile( OFSTREAM& output_file, VECTOR< unsigned int > finalPath, Graph < STRING >& graph, STRING origin_city, STRING destin_city ){
    //Same as other print_stats function, just printing to output_file rather than COUT    

    output_file << STRING(150,'=') << ENDL;

    output_file << "Total number of cities visited: " << finalPath.size() << ENDL;

    output_file << STRING(150,'=') << ENDL;

    float short_line_distance = 0, traveled_distance = 0;
    unsigned int sz_of_path = (unsigned int) finalPath.size() - 1;

    unsigned int origin, destin, curr_city, next_city;

    origin = finalPath[sz_of_path];
    if( finalPath[0] > origin ) destin = finalPath[0] - 1;
    else destin = finalPath[0];

    short_line_distance = graph.return_dist_edge( origin, destin );

    //Find the total number of miles traveled --> search edges for length between nodes
    for( unsigned int i = (unsigned int) finalPath.size() - 1; i > 0 ; i-- ){

        //Find the milage between each node: example, size 4: 3->2 2->1 1->0
        curr_city = finalPath[i];
        if( finalPath[i-1] > curr_city ) next_city = finalPath[i-1] - 1;
        else next_city = finalPath[i-1];

        //Takes the distance of said edge and adds to a running total
        traveled_distance += graph.return_dist_edge( curr_city, next_city );

    }

    output_file << "The straight path from " << origin_city << ", " << graph.get_state( finalPath[(unsigned int) finalPath.size() - 1] ) << " to " 
    << destin_city << ", " << graph.get_state(finalPath[0] ) << " is " << short_line_distance << " miles" << ENDL << ENDL;

    output_file << "The suggested roadtrip from " << origin_city << ", " << graph.get_state( finalPath[(unsigned int) finalPath.size() - 1] ) << " to " 
    << destin_city << ", " << graph.get_state(finalPath[0] ) << " is " << traveled_distance << " miles" << ENDL << ENDL;

    output_file << "The suggested roadtrip visits " << finalPath.size() - 2 << " more cities, traveling " << traveled_distance - short_line_distance << " more miles" << ENDL; 

    output_file << STRING(150,'=') << ENDL;

}

