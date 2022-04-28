/**********************************
 * Group: Washington Coding Team
 * Members: Benjamin Egloff, Will Truluck, Alex Potts, Steve Zhao
 * Email: begloff@nd.edu
 * File Name: final_proj.cpp
 * Date Created: 4/27/2022
 * File Contents: This file contains the Vertex class for CSE 20312 Final Project
 **********************************/

 /* Class based on Dr. Matthew Morrison's Vertex class found at: https://github.com/mmorri22/sp22-cse-20312/blob/main/Lec19_InClass/include/Vertex.h */


#ifndef VERTEX_H
#define VERTEX_H

#include "Edge.h"

#include <iostream>
#include <vector>

#define VECTOR std::vector
#define COUT std::cout
#define ENDL std::endl

template<class T>
class Vertex{

	private:
	
		VECTOR< Edge > edges; 
		T city; //Name of City
		T state; //State of City
        float attraction_points;
		bool valid;			// Valid Vertex
		bool visited;
		
	public:
	
		Vertex( ) : edges(), city( ), state (), attraction_points(),valid( true ), visited() {}
	
		Vertex( const T& cityIn, const T& stateIn, float ap, bool visit ) : edges(), city( cityIn ), state( stateIn ), attraction_points(ap), valid( true ), visited(visit) {}
		
		~Vertex(){ }
		
		//Gets the templated city name from vertex
		T get_city_value() const{
			
			return city;
		}

		//Gets the templated state name from vertex
		T get_state_value() const{

			return state;

		}

		//Returns the visit bool of a given vertex
		bool get_visit_status() const{

			return visited;

		}

		//Gets the ap value from a given vertex
        float get_ap_value() const{
            
            return attraction_points;
			
        }

		//Sets the city name of a vertex
		void set_vertex_value(const T& cityIn){
			
			city = cityIn;
		}

		//Sets the visit bool of a vertex
		void set_visit_value( const bool visit_status){

			visited = visit_status;

		}
		
		// Adding an Edge to a Vertex
		void add_edge( unsigned int destin, float weight, float distance ){
			
			// If not, put the edge on the back of the array
			edges.push_back( Edge(destin, weight, distance) );
			
		}
		
		// Pass the destination, return weight with call be reference, bool if found
		bool get_edge_value( unsigned int destin, int& weight ) const{
			
			bool edgeFound = false;
			
			for( unsigned int i = 0; i < edges.size(); i++){
				if( edges[i].destin == destin ){

					edgeFound = true;
					weight = edges[i].weight;
				}					
			}
			
			return edgeFound;
		}

		// Pass the destination and weight, bool if found		
		bool set_edge_value( unsigned int destin, int weight) {
			
			bool edgeFound = false;
			
			for( unsigned int i = 0; i < edges.size(); i++){
				if( edges[i].destin == destin ){

					edgeFound = true;
					edges[i].weight = weight;
				}
			}
			
			return edgeFound;
		}
		
		// Remove the edge to an input destination
		bool remove_edge( unsigned int edgeLoc ){
			
			bool deleted = false;
			
			for(unsigned int i = 0; i < edges.size(); i++){
				
				if( edges[i].destin == edgeLoc ){
					edges.erase( edges.begin() + i);
					deleted = true;
					break;
				}
			}
			
			return deleted;
		}
		
		// Return an edge
		Edge get_edge( unsigned int edgeOrder ) {
			
			return edges[ edgeOrder ];
		}
		
		// Return the number of edges
		unsigned int num_edges() const{
			
			return (unsigned int)edges.size();
		}
		
		// Clear the vertex 
		void lazy_delete(){
			
			valid = false;
			
			while( edges.size() > 0 ){
				
				// Remove the front edge
				edges.erase( edges.begin() );
			}
			
		}
		
		// Print to the Output
		void print_vertex(){

			// If the vertex is valid
			if( this->valid ){
			
				// Print the city element first
				COUT << "[" << this->city << ", " << this->state << ": " << this->attraction_points << ": ";
				
				// 
				for( long unsigned int iter = 0; iter < this->edges.size(); iter++ ){
					
					// Print the destination
					COUT << "{" << this->edges[iter].destin << ", ";
					
					// Print the weight
					COUT << this->edges[iter].weight << "} ";
					
				}
				COUT << "]" << ENDL;
			
			}
			// If the vertex is not valid, indicate Lazy Deletion
			else{
				COUT << "[DELETED]";
			}		
			
		}

		
};

#endif