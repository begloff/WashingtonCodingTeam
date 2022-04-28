/**********************************
 * Group: Washington Coding Team
 * Members: Benjamin Egloff, Will Truluck, Alex Potts, Steve Zhao
 * Email: begloff@nd.edu
 * File Name: final_proj.cpp
 * Date Created: 4/27/2022
 * File Contents: This file contains the main function for CSE 20312 Final Project
 **********************************/


#include "../include/roadtrip.h"

int main( int argc, char *argv[]){

    Graph< STRING > graph; //Makes graph obj
    VECTOR < unsigned int > finalPath; //Vector that stores the final road trip route

    STRING cities_filepath = "include/distance/ap.txt"; //Filepath that corresponds to each city and attraction points
    STRING edges_filepath = "include/distance/input.txt"; //Filepath that contains all distances between cities

    UNOR_MAP < STRING , int > city_order; //Stores City --> Number
    UNOR_MAP < int, STRING > city_number; //Stores Number --> City

    STRING origin_city, destin_city;

    //Take command line args as input and output files: 1 --> input 2 --> output
    if(argc > 1){

        get_file_input(argv[1],origin_city,destin_city); //If there is an input file, read the cities from there

    } else {

        //Reads in origin and destin from the user
        COUT << "Please enter an origin city: ";
        GETLINE(CIN,origin_city);
        COUT << "Please enter a destination city: ";
        GETLINE(CIN,destin_city);

    }

    //Reads in the nodes and populates both maps
    read_in_cities(graph,cities_filepath,city_order,city_number);

    //Reads in edges and connects nodes
    connect_cities(graph,edges_filepath,city_order);

    //Creates auto object --> finds origin and destin in unordered map
    auto origin_number = city_order.find(origin_city);
    auto destin_number = city_order.find(destin_city);

    //Outgoing trip
    finalPath = graph.Dijkstra(origin_number->second,destin_number->second);

    if(argc < 3){//no output file

        //String formatting
        COUT << ENDL;
        COUT << STRING(150,'=') << ENDL << ENDL;
        COUT << STRING(150,'-') << ENDL;
        COUT << STRING(67,' ') << "Outgoing Roadtrip" << STRING(68,' ') << ENDL;
        COUT << STRING(150,'-') << ENDL;
        COUT << ENDL;

    
        //Prints the order of the cities to terminal
        print_order(finalPath,graph,city_number,origin_city,destin_city);

        //Prints the total distance traveled
        print_stats(finalPath,graph,origin_city,destin_city);

    } else { //Output file

        //Opens OFSTREAM
        OFSTREAM output_file;
        output_file.open(argv[2]);

        //String formatting
        output_file << ENDL;
        output_file << STRING(150,'=') << ENDL << ENDL;
        output_file << STRING(150,'-') << ENDL;
        output_file << STRING(67,' ') << "Outgoing Roadtrip" << STRING(68,' ') << ENDL;
        output_file << STRING(150,'-') << ENDL;
        output_file << ENDL;

        print_order_outfile(output_file,finalPath,graph,city_number,origin_city,destin_city); //Prints the order of cities to OFSTREAM

        print_stats_outfile(output_file,finalPath,graph,origin_city,destin_city); //Prints the distance stats to OFSTREAM

    }

    //Check off the cities that are "visited" for the return trip
    visit_cities(finalPath, graph);

    //Returning trip
    finalPath = graph.Dijkstra(destin_number->second,origin_number->second);


    if (argc < 3){

        //More output formatting
        COUT << ENDL;
        COUT << STRING(150,'-') << ENDL;
        COUT << STRING(67,' ') << "Return Roadtrip" << STRING(68,' ') << ENDL;
        COUT << STRING(150,'-') << ENDL;
        COUT << ENDL;

        print_order(finalPath,graph,city_number,destin_city,origin_city); //Prints city order to COUT

        print_stats(finalPath,graph,destin_city,origin_city); //Prints distance stats to COUT

    } else {

        OFSTREAM output_file;
        output_file.open(argv[2], OFSTREAM::app ); //Appends to file opened earlier

        //Output formatting
        output_file << ENDL;
        output_file << STRING(150,'-') << ENDL;
        output_file << STRING(67,' ') << "Return Roadtrip" << STRING(68,' ') << ENDL;
        output_file << STRING(150,'-') << ENDL;
        output_file << ENDL;

        print_order_outfile(output_file,finalPath,graph,city_number,destin_city,origin_city); //Prints the order of cities to OFSTREAM

        print_stats_outfile(output_file,finalPath,graph,destin_city,origin_city); //Prints the distance stats to OFSTREAM
    }


    return 0;
}