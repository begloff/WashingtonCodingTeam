//The include file for Final Project:
//Lists all function declarations and Macros

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
#define NUM_NODES 50

#define CIN std::cin
#define GETLINE std::getline
#define STOF std::stof

void read_in_cities( Graph < STRING >& graph, STRING& cities_filepath, UNOR_MAP < STRING , int >& city_order, UNOR_MAP < int , STRING >& city_number);
void connect_cities( Graph < STRING >& graph, STRING& edges_filepath, UNOR_MAP < STRING , int >& city_order );
void print_order( STACK < unsigned int > finalPath, UNOR_MAP < int, STRING > city_number, STRING origin_city, STRING destin_city);


#endif