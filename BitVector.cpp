//
//  BitVector.cpp
//  Homework6
//
//  Created by Ben Schulz on 2/26/18.
//  Copyright © 2018 Ben Schulz. All rights reserved.
//

#include "BitVector.hpp"

BitVector::BitVector(uint32_t x, uint32_t y, uint32_t z) {
	xDim = x;
	yDim = y;
	zDim = z;
	
	tSize = ceil((xDim*yDim*zDim)/8.0);
	bitVector = new MyArray<uint8_t>(tSize);
	
	for (uint32_t i = 0; i < tSize; ++i) {
		bitVector->pushBack(0);
	}
	
}

BitVector::BitVector::~BitVector() {
	delete bitVector;
}

void BitVector::fillVector() {
	for (uint32_t i = 0; i < size()/8; ++i) {
		//		bitVector[i] = 255;
		bitVector->set(i, 255);
	}
}

void BitVector::clearVector() {
	for (uint32_t i = 0; i < size()/8; ++i) {
//		bitVector[i] = 0;
		bitVector->set(i, 0);
	}
}

bool BitVector::getBit(uint32_t bit) {
	uint8_t mask = 1;
//	return ((bitVector[bit/8] >> (bit%8)) & mask);
	return ((bitVector->get(bit/8) >> (bit%8)) & mask);
}

void BitVector::setBit(uint32_t bit, bool val) {
	uint8_t mask = 1;
	
	if (getBit(bit) == val) {
		return;
	} else {
//		bitVector[(int)ceil(bit/8)] = bitVector[bit/8] ^ (mask << (bit%8));
		bitVector->set((int)ceil(bit/8), bitVector->get(bit/8) ^ (mask << (bit%8)));
	}
}

uint32_t BitVector::getXDim() {
	return xDim;
}

uint32_t BitVector::getYDim() {
	return yDim;
}

uint32_t BitVector::getZDim() {
	return zDim;
}

uint32_t BitVector::size() {
	return tSize*8;
}

//void BitVector::resize(BitVector* newVector, uint32_t newSize) {
//	
//	delete [] bitVector;
//	
//	bitVector->getPointer() newVector->getArray();
//	
//	tSize = newSize;
//	
//}

//uint8_t* BitVector::getArray() {
//	return bitVector;
//}