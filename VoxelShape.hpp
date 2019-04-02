//
//  VoxelShape.hpp
//  Homework6
//
//  Created by Ben Schulz on 2/26/18.
//  Copyright © 2018 Ben Schulz. All rights reserved.
//

#ifndef VoxelShape_hpp
#define VoxelShape_hpp

#include "BitVector.hpp"

class VoxelShape {
public:
	VoxelShape(uint32_t xDim, uint32_t yDim, uint32_t zDim);
	~VoxelShape();
//	void resize(uint32_t x, uint32_t y, uint32_t z);
	void fillShape();
	void clearShape();
	uint32_t getXDim();
	uint32_t getYDim();
	uint32_t getZDim();
	bool getVoxel(uint32_t x, uint32_t y, uint32_t z);
	void setVoxel(uint32_t x, uint32_t y, uint32_t z);
	void clearVoxel(uint32_t x, uint32_t y, uint32_t z);
	void toggleVoxel(uint32_t x, uint32_t y, uint32_t z);
	void addSphere(uint32_t cx, uint32_t cy, uint32_t cz, uint32_t rad);
	void clearSphere(uint32_t cx, uint32_t cy, uint32_t cz, uint32_t rad);
	void toggleSphere(uint32_t cx, uint32_t cy, uint32_t cz, uint32_t rad);

private:
	BitVector* bits;
	uint32_t xDim;
	uint32_t yDim;
	uint32_t zDim;
	
	uint32_t getIndex(uint32_t x, uint32_t y, uint32_t z);
	uint32_t getIndex(uint32_t x, uint32_t y, uint32_t z, uint32_t xDimI, uint32_t yDimI, uint32_t zDimI);
	void getXYZ(uint32_t index, uint32_t& x, uint32_t& y, uint32_t& z);
	bool insideSphere(uint32_t x, uint32_t y, uint32_t z, uint32_t cx, uint32_t cy, uint32_t cz, uint32_t rad);
	
};

#endif /* VoxelShape_hpp */
