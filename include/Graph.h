#ifndef GRAPH_H
#define GRAPH_H

#include "Vertex.h"
#include <stack>
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

#define VECTOR std::vector
#define STACK std::stack
#define QUEUE std::queue
#define PRIORITY_QUEUE std::priority_queue
#define UNOR_MAP std::unordered_map

template< typename T >
struct Graph{
	
	private:
	
		VECTOR< Vertex< T > > vertices;	// Adjacency List

    public:
		// Constructor
		Graph( ) : vertices() {}
		
		// Destructor
		~Graph( ) { }
		
		// Add a vertex prior to any edges
		void add_vertex( const T& vertexData, unsigned int ap){
			
			Vertex<T> theVertex( vertexData, ap );
			vertices.push_back( theVertex );
		}


        // Overloaded Operator
		void print_graph(){
			
			for( unsigned int iter = 0; iter < this->vertices.size(); iter++ ){
				
				COUT << iter << ": "; 
				this->vertices[ iter ].print_vertex();
				COUT << ENDL;
				
			}
			
		}

};

#endif