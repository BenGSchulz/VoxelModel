//
//  BitVector.hpp
//  Homework6
//
//  Created by Ben Schulz on 2/26/18.
//  Copyright © 2018 Ben Schulz. All rights reserved.
//

#ifndef BitVector_hpp
#define BitVector_hpp

#include "MyArray.hpp"

class BitVector {
public:
	BitVector(uint32_t x, uint32_t y, uint32_t z);
	~BitVector();
	void fillVector();
	void clearVector();
	bool getBit(uint32_t bit);
	void setBit(uint32_t bit, bool val);
	uint32_t getXDim();
	uint32_t getYDim();
	uint32_t getZDim();
	uint32_t size();
//	void resize(BitVector* newVector, uint32_t newSize);
//	uint8_t* getArray();
	
private:
//	uint8_t* bitVector;
	MyArray<uint8_t>* bitVector;
	uint32_t tSize;
	uint32_t xDim;
	uint32_t yDim;
	uint32_t zDim;
	
};

#endif /* BitVector_hpp */
