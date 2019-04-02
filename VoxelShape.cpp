//
//  VoxelShape.cpp
//  Homework6
//
//  Created by Ben Schulz on 2/26/18.
//  Copyright © 2018 Ben Schulz. All rights reserved.
//

#include "VoxelShape.hpp"

VoxelShape::VoxelShape(uint32_t x, uint32_t y, uint32_t z) {
	xDim = x;
	yDim = y;
	zDim = z;
	
	bits = new BitVector(xDim, yDim, zDim);
}

VoxelShape::~VoxelShape() {
	delete bits;
	
	bits = nullptr;
	xDim = 0;
	yDim = 0;
	zDim = 0;
}

//void VoxelShape::resize(uint32_t x, uint32_t y, uint32_t z) {
//	xDim = x;
//	yDim = y;
//	zDim = z;
//	
//	uint32_t newSize = ceil((xDim*yDim*zDim)/8.0);
////	uint32_t minSize = std::min(bits->size(), newSize*8);
//	
//	BitVector newVector(xDim, yDim, zDim);
//	
//	uint32_t xMaxI =std::min(xDim, bits->getXDim());
//	uint32_t yMaxI =std::min(yDim, bits->getYDim());
//	uint32_t zMaxI =std::min(zDim, bits->getZDim());
//	
//	
//	for (int xi = 0; xi < xMaxI; ++xi) {
//		for (int yi = 0; yi < yMaxI; ++yi) {
//			for (int zi = 0; zi < zMaxI; ++zi) {
//				newVector.setBit(getIndex(xi, yi, zi), bits->getBit(getIndex(xi, yi, zi, bits->getXDim(), bits->getYDim(), bits->getZDim())));
//				
//			}
//		}
//	}
//	
//	bits->resize(&newVector, newSize);
//	
////	delete newVector;
//
//}

void VoxelShape::fillShape() {
	bits->fillVector();
}

void VoxelShape::clearShape() {
	bits->clearVector();
}

uint32_t VoxelShape::getXDim() {
	return xDim;
}

uint32_t VoxelShape::getYDim() {
	return yDim;
}

uint32_t VoxelShape::getZDim() {
	return zDim;
}

uint32_t VoxelShape::getIndex(uint32_t x, uint32_t y, uint32_t z) {
	return (x*yDim*zDim) + (y*zDim) + z;
}

uint32_t VoxelShape::getIndex(uint32_t x, uint32_t y, uint32_t z, uint32_t xDimI, uint32_t yDimI, uint32_t zDimI) {
	return (x*yDimI*zDimI) + (y*zDimI) + z;
}

void VoxelShape::getXYZ(uint32_t index, uint32_t& x, uint32_t& y, uint32_t& z) {
	x = index/(yDim*zDim);
	y = (index/(zDim))%yDim;
	z = index%zDim;
}

bool VoxelShape::getVoxel(uint32_t x, uint32_t y, uint32_t z) {
	if ((int32_t)x < 0 || x > xDim-1|| (int32_t)y < 0 || y > yDim-1|| (int32_t)z < 0 || z > zDim-1) {
		return false;
	}
	
	return bits->getBit(getIndex(x, y, z));
}

void VoxelShape::setVoxel(uint32_t x, uint32_t y, uint32_t z) {
	if ((int32_t)x < 0 || x > xDim-1|| (int32_t)y < 0 || y > yDim-1|| (int32_t)z < 0 || z > zDim-1) {
		std::cout << "Voxel at: (" << x << ", " << y << ", " << z << ") Out of Bounds\n";
		return;
	}
	
	bits->setBit(getIndex(x, y, z), true);
}

void VoxelShape::clearVoxel(uint32_t x, uint32_t y, uint32_t z) {
	if ((int32_t)x < 0 || x > xDim-1|| (int32_t)y < 0 || y > yDim-1|| (int32_t)z < 0 || z > zDim-1) {
		std::cout << "Voxel at: (" << x << ", " << y << ", " << z << ") Out of Bounds";
		return;
	}
	
	bits->setBit(getIndex(x, y, z), false);
}

void VoxelShape::toggleVoxel(uint32_t x, uint32_t y, uint32_t z) {
	if ((int32_t)x < 0 || x > xDim-1|| (int32_t)y < 0 || y > yDim-1|| (int32_t)z < 0 || z > zDim-1) {
		std::cout << "Voxel at: (" << x << ", " << y << ", " << z << ") Out of Bounds";
		return;
	}
	
	bits->setBit(getIndex(x, y, z), !bits->getBit(getIndex(x, y, z)));
}

bool VoxelShape::insideSphere(uint32_t x, uint32_t y, uint32_t z, uint32_t cx, uint32_t cy, uint32_t cz, uint32_t rad) {
	return (((x - cx)*(x - cx)) + ((y - cy)*(y - cy)) + ((z - cz)*(z - cz))) < (rad*rad);
}

void VoxelShape::addSphere(uint32_t cx, uint32_t cy, uint32_t cz, uint32_t rad) {
	for (uint32_t i = 0; i < (bits->size()); ++i) {
		uint32_t x = 0;
		uint32_t y = 0;
		uint32_t z = 0;
		
		getXYZ(i, x, y, z);
		
		if (insideSphere(x, y, z, cx, cy, cz, rad)) {
			setVoxel(x, y, z);
		}
	}
}

void VoxelShape::clearSphere(uint32_t cx, uint32_t cy, uint32_t cz, uint32_t rad) {
	for (uint32_t i = 0; i < (bits->size()); ++i) {
		uint32_t x = 0;
		uint32_t y = 0;
		uint32_t z = 0;
		
		getXYZ(i, x, y, z);
		
		if (insideSphere(x, y, z, cx, cy, cz, rad)) {
			clearVoxel(x, y, z);
		}
	}
}

void VoxelShape::toggleSphere(uint32_t cx, uint32_t cy, uint32_t cz, uint32_t rad) {
	for (uint32_t i = 0; i < (bits->size()); ++i) {
		uint32_t x = 0;
		uint32_t y = 0;
		uint32_t z = 0;
		
		getXYZ(i, x, y, z);
		
		if (insideSphere(x, y, z, cx, cy, cz, rad)) {
			toggleVoxel(x, y, z);
		}
	}
}


