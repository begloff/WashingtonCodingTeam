/**********************************
 * Group: Washington Coding Team
 * Members: Benjamin Egloff, Will Truluck, Alex Potts, Steve Zhao
 * Email: begloff@nd.edu
 * File Name: roadtrip.h
 * Date Created: 4/27/2022
 * File Contents: This file contains the function declarations and macros for CSE 20312 Final Project
 **********************************/


#ifndef ROADTRIP_H
#define ROADTRIP_H

#include <cstdlib>
#include <string>
#include <fstream>
#include <cstring>
#include <iostream>
#include <cstdio>
#include <stack>
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

#include "Edge.h"
#include "Vertex.h"
#include "Graph.h"

#define VECTOR std::vector
#define STACK std::stack
#define QUEUE std::queue
#define PRIORITY_QUEUE std::priority_queue
#define UNOR_MAP std::unordered_map
#define STRING std::string
#define IFSTREAM std::ifstream
#define OFSTREAM std::ofstream
#define NUM_NODES 50

#define CIN std::cin
#define GETLINE std::getline
#define STOF std::stof

void read_in_cities( Graph < STRING >& graph, STRING& cities_filepath, UNOR_MAP < STRING , int >& city_order, UNOR_MAP < int , STRING >& city_number);
void connect_cities( Graph < STRING >& graph, STRING& edges_filepath, UNOR_MAP < STRING , int >& city_order );
void print_order( VECTOR < unsigned int > finalPath, Graph < STRING >& graph, UNOR_MAP < int, STRING > city_number, STRING origin_city, STRING destin_city);
void print_stats( VECTOR< unsigned int > finalPath, Graph < STRING >& graph, STRING origin_city, STRING destin_city );
void visit_cities( VECTOR< unsigned int > finalPath, Graph < STRING >& graph );
void get_file_input( char *file_name, STRING& origin_city, STRING& destin_city);
void print_order_outfile( OFSTREAM& output_file, VECTOR< unsigned int > finalPath, Graph < STRING >& graph, UNOR_MAP < int, STRING > city_number, STRING origin_city, STRING destin_city );
void print_stats_outfile( OFSTREAM& output_file, VECTOR< unsigned int > finalPath, Graph < STRING >& graph, STRING origin_city, STRING destin_city );


#endif