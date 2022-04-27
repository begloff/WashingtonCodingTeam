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
