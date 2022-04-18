#ifndef EDGE_H
#define EDGE_H

struct Edge{
	
	unsigned int destin;
	unsigned int weight;
    unsigned int attraction_points;				

	// Default Constructor
	Edge() : destin(), weight(), attraction_points() {}

	// Overloaded Constructor
	Edge( unsigned int dest, unsigned int weightIn, unsigned int ap ) : destin(dest), weight(weightIn), attraction_points(ap) {}
	
	// Overloaded == operator
	bool operator==( const Edge& rhs ) const{
		
		return destin == rhs.destin && weight == rhs.weight;
		
	}
};

#endif
