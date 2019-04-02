//
//  main.cpp
//  Homework7
//
//  Created by Ben Schulz on 2/26/18.
//  Copyright © 2018 Ben Schulz. All rights reserved.
//

#include "surfaceExtraction.hpp"

int main(int argc, const char * argv[]) {

	std::cout << "\n\n\n";
	std::cout << "VoxelShape W/ Threads (WriteSTL uses threaded function): \n";
	VoxelShape v1(16, 31, 21);
	
	v1.fillShape();
	v1.clearShape();
	
	v1.addSphere(8, 15, 10, 16);
	
	v1.clearSphere(8, 15, 20, 7);
	v1.toggleSphere(8, 15, 20, 13);
	
	v1.clearSphere(8, 15, 0, 7);
	v1.toggleSphere(8, 15, 0, 13);
//	v1.toggleSphere(8, 15, 0, 13);
	
	v1.clearSphere(8, 30, 10, 7);
	
	std::cout << "Voxel at (0, 0, 0): " << v1.getVoxel(0, 0, 0) << "\n";
	std::cout << "Voxel at (8, 15, 10): " << v1.getVoxel(8, 15, 10) << "\n";
	std::cout << "Voxel at (15, 30, 20): " << v1.getVoxel(15, 30, 20) << "\n";
	
	v1.setVoxel(29, 29, 0);
	
//	v1.clearShape();
	
	writeSTL(v1, "output.stl");
	
	
	std::cout << std::endl;
    return 0;
}
