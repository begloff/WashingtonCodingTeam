/**********************************
 * Group: Washington Coding Team
 * Members: Benjamin Egloff, Will Truluck, Alex Potts, Steve Zhao
 * Email: begloff@nd.edu
 * File Name: final_proj.cpp
 * Date Created: 4/27/2022
 * File Contents: This file contains the Edge class for CSE 20312 Final Project
 **********************************/

 /* Class based on Dr. Matthew Morrison's Edge class found at: https://github.com/mmorri22/sp22-cse-20312/blob/main/Lec19_InClass/include/Edge.h */

#ifndef EDGE_H
#define EDGE_H


struct Edge{
	
	unsigned int destin;
	float weight;
	float dist;			

	// Default Constructor
	Edge() : destin(), weight(), dist() {}

	// Overloaded Constructor
	Edge( unsigned int dest, float weightIn, float distIn) : destin(dest), weight(weightIn), dist(distIn){}
	
	// Overloaded == operator
	bool operator==( const Edge& rhs ) const{
		
		return destin == rhs.destin && weight == rhs.weight;
		
	}
};

#endif
