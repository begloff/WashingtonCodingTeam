#ifndef GRAPH_H
#define GRAPH_H

#include "Vertex.h"
#include "roadtrip.h"
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
#define STRING std::string
#define IFSTREAM std::ifstream
#define NUM_NODES 50

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
		void add_vertex( const T& cityData, const T& stateData, float ap){
			
			Vertex<T> theVertex( cityData, stateData, ap );
			vertices.push_back( theVertex );
		}

		void add_edge( unsigned int origin, unsigned int destin, float weight, float distance) {

			if (origin < vertices.size() && destin < vertices.size() ) {
				vertices[origin].add_edge(destin, weight, distance);
			}
		}

		float get_ap_of_vertex(unsigned int index){

			return this->vertices[index].get_ap_value();

		}

		float return_dist_edge( unsigned int origin, unsigned int destin ){

			return this->vertices[origin].get_edge(destin).dist;
		}


        // Overloaded Operator
		void print_graph(){

			//COUT << this->vertices.size() << ENDL;
			
			for( unsigned int iter = 0; iter < this->vertices.size(); iter++ ){
				
				COUT << iter << ": "; 
				this->vertices[ iter ].print_vertex();
				COUT << ENDL;
				
			}
			
		}

		// Dijkstra's Algorithm
		VECTOR < unsigned int > Dijkstra( unsigned int origin, unsigned int destin ){
			
			
			/* Initialize the Elements */
			PRIORITY_QUEUE< unsigned int > the_PQ;
			VECTOR< int > parents( vertices.size(), 0 );
			VECTOR< float > distance( vertices.size(), 100000.0);
			VECTOR< unsigned int > finalPath;

			if( origin >= vertices.size() || destin >= vertices.size() || vertices.size() == 0 ){
				
				std::cout << "Invalid Inputs" << std::endl;
				return finalPath;
				
			}
			
			bool found = false;
			
			/* Initialize the origin */
			the_PQ.push( origin );
			distance[origin] = 0;
			parents[origin] = -1;
			
			if( destin == origin ){	
				found = true;
			}
			
			if( !found ){
				
				/* Run the shortest path algorithm */
				while( !the_PQ.empty() ){
					
					// Get the top element of the stack and pop
					unsigned int index = the_PQ.top();
					the_PQ.pop();
					
					// Evaluate the edges from the vertex 
					for(unsigned int iter = 0; iter < vertices[ index ].num_edges(); iter++ ){
						
						// Obtain the edge
						Edge tempEdge = vertices[ index ].get_edge( iter );
						
						// If the weight of the edge plus distance of the  distance is less than the destin weight
						if( distance[ index ] + tempEdge.weight < distance[ tempEdge.destin ] ) {
							
							// Update the distance
							distance[ tempEdge.destin ] = distance[ index ] + tempEdge.weight;
							
							// Update the parent of the destin 
							parents[ tempEdge.destin ] = index;
							
							// Check if destin is the result;
							if( tempEdge.destin == destin && !found ){
								
								found = true;
							}
							
							the_PQ.push( tempEdge.destin );
						}
					}
				}
			}
			
			// Otherwise, go through the parents until we find the origin
			if( found ){
				
				unsigned int sentinel = destin;	
				finalPath.push_back( sentinel );		// Push the desination onto the stack
				
				while( parents[sentinel] != -1 ){
					
					finalPath.push_back( parents[sentinel] );	// Push the parent onto the stack
					sentinel = parents[sentinel];			// Update the sentinel
					
				}
				
				// Stack contains the correct order 
				return finalPath;
			}

			return finalPath;
			
		}

};

#endif