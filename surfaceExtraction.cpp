//
//  surfaceExtraction.cpp
//  Homework7
//
//  Created by Ben Jones on 2/6/17.
//  Copyright © 2017 Ben Jones. All rights reserved.
//
//	Edited by Ben Schulz
//

#include "surfaceExtraction.hpp"
#include "SharedQueue.h"
#include "Timer.h"
#include <thread>


enum FaceType {
	NX,
	NY,
	NZ,
	PX,
	PY,
	PZ
};

struct Triangle{
	float normal[3];
	float v1[3];
	float v2[3];
	float v3[3];
};

// 2.Create a data structure to use for distributing work to the thread.  This should be similar to the Range struct from the lab, and contain enough information to describe a "chunk of work."  For this application, it should contain the  x and y coordinates of a column of voxels you want to analyze.
struct workCol {
	uint32_t x, y;
};

inline void fillPlane(int a1, int a2, int b1, int b2, int c, int cInd, Triangle& t1, Triangle& t2){
    t1.v1[cInd] = c;
    t2.v1[cInd] = c;
    t1.v2[cInd] = c;
    t2.v2[cInd] = c;
    t1.v3[cInd] = c;
    t2.v3[cInd] = c;
    int aInd = (cInd +1) % 3;
    int bInd = (cInd +2) % 3;
    
    t1.v1[aInd] = a1;
    t1.v2[aInd] = a2;
    t1.v3[aInd] = a2;
    
    t2.v1[aInd] = a1;
    t2.v2[aInd] = a2;
    t2.v3[aInd] = a1;
    
    t1.v1[bInd] = b1;
    t1.v2[bInd] = b1;
    t1.v3[bInd] = b2;
    
    t2.v1[bInd] = b1;
    t2.v2[bInd] = b2;
    t2.v3[bInd] = b2;
    
}

void extractFace(int x, int y, int z, FaceType face, Triangle& t1, Triangle& t2){
    for(int i= 0; i < 3; i++){
        t1.normal[i] = 0;
        t2.normal[i] = 0;
    }
    switch(face){
        case NX:
            t1.normal[0] = -1;
            t2.normal[0] = -1;
            fillPlane(y + 1, y, z, z+1, x, 0, t1, t2);
            break;
        case NY:
            t1.normal[1] = -1;
            t2.normal[1] = -1;
            fillPlane(z + 1, z, x, x+1, y, 1, t1, t2);
            break;
        case NZ:
            t1.normal[2] = -1;
            t2.normal[2] = -1;
            fillPlane(x + 1, x, y, y + 1, z, 2, t1, t2);
            break;
        case PX:
            t1.normal[0] = 1;
            t2.normal[0] = 1;
            fillPlane(y, y + 1, z, z +1, x + 1, 0, t1, t2);
            break;
        case PY:
            t1.normal[1] = 1;
            t2.normal[1] = 1;
            fillPlane(z, z + 1, x, x + 1, y + 1, 1, t1, t2);
            break;
        case PZ:
            t1.normal[2] = 1;
            t2.normal[2] = 1;
            fillPlane(x, x +1, y, y + 1, z + 1, 2, t1, t2);
            break;
    }
}

//1. Inside the WriteSTL there is a set of for loops inside which the main extraction of triangles is performed. Start by replacing the inner for loop (over z) with a function that takes an x and y value and performs the extraction loop over the z value inside the function. You will also pass the Array for storing the results. (Test and make sure your code works with this function.)
void createAndExtract(VoxelShape& model, uint32_t x, uint32_t y, MyArray<Triangle>& storage, uint32_t& numTriangles, std::mutex& lock) {
	MyArray<Triangle> tempArr;
	uint32_t tempNum = 0;
//	std::cout << "In createAndExtract\n";
	for (uint32_t z = 0; z < model.getZDim(); ++z) {
		if (model.getVoxel(x, y, z)) {
			if (!model.getVoxel(x-1, y, z)) {
				FaceType face1 = NX;
				Triangle t1{};
				Triangle t2{};
				
				extractFace(x, y, z, face1, t1, t2);
				
				tempArr.pushBack(t1);
				tempArr.pushBack(t2);

				tempNum+=2;
			}
			
			if (!model.getVoxel(x+1, y, z)) {
				FaceType face2 = PX;
				Triangle t1{};
				Triangle t2{};
				
				extractFace(x, y, z, face2, t1, t2);
				
				tempArr.pushBack(t1);
				tempArr.pushBack(t2);
				tempNum+=2;
			}
			
			if (!model.getVoxel(x, y-1, z)) {
				FaceType face3 = NY;
				Triangle t1{};
				Triangle t2{};
				
				extractFace(x, y, z, face3, t1, t2);
				
				tempArr.pushBack(t1);
				tempArr.pushBack(t2);
				tempNum+=2;
			}
			
			if (!model.getVoxel(x, y+1, z)) {
				FaceType face4 = PY;
				Triangle t1{};
				Triangle t2{};
				
				extractFace(x, y, z, face4, t1, t2);
				
				tempArr.pushBack(t1);
				tempArr.pushBack(t2);
				tempNum+=2;
			}
			
			if (!model.getVoxel(x, y, z-1)) {
				FaceType face5 = NZ;
				Triangle t1{};
				Triangle t2{};
				
				extractFace(x, y, z, face5, t1, t2);
				
				tempArr.pushBack(t1);
				tempArr.pushBack(t2);
				tempNum+=2;
			}
			
			if (!model.getVoxel(x, y, z+1)) {
				FaceType face6 = PZ;
				Triangle t1{};
				Triangle t2{};
				
				extractFace(x, y, z, face6, t1, t2);
				
				tempArr.pushBack(t1);
				tempArr.pushBack(t2);
				tempNum+=2;
			}
		}
	}
	
//	7. Each of the threads will compute a subset of the output triangles and put them into the Array. This process needs to be locked. So, for efficiency purposes, you should create an array inside each thread that saves the triangles for that thread, and once the work is complete, the lock can be acquired and all the data can be copied into the Array used for storing results.
	lock.lock();
	for (int i = 0; i < tempArr.size(); ++i) {
		storage.pushBack(tempArr.get(i));
	}
	numTriangles+=tempNum;
	lock.unlock();
}

//3. Define a function that extracts work from the queue, and calls your function from part 1 with the appropriate arguments.  This function will need to take an array where you'll store the extracted triangles, the SharedQueue, and a lock (for the array).
void extractWork(SharedQueue<workCol>* workqueue, std::mutex& lock, VoxelShape& model, MyArray<Triangle>& storage, uint32_t& numTriangles) {
	
	workCol col;
	
	while (true) {

		while (workqueue->Remove(col) == false) {
			std::this_thread::yield();
		}
		
		if (col.x == (uint32_t)-1 && col.y == (uint32_t)-1) {
			break;
		}
		
		createAndExtract(model, col.x, col.y, storage, numTriangles, lock);
	}
}

void threadedExtract(FILE* myFile, VoxelShape& model, MyArray<Triangle>& storage, uint32_t& numTriangles, unsigned numThreads) {
//	2. Create a SharedQueue (use your code from the lab) that using this data structure as its template parameter. It will be used for passing work to the threads.
	SharedQueue<workCol> workQueue;
	std::mutex lock;
	
	Timer t;
	t.StartTimer();
	
//	4. Start up the appropriate number (Eventually, you'll want to use hardware_concurrency(), but test your code with a single thread first!) of threads for your machine before your for loops over x and y. These threads should be calling the function you wrote for part 3.
	std::thread **threads;
	threads = new std::thread*[numThreads];
	for (int x = 0; x < numThreads; x++)
	{
		threads[x] = new std::thread(extractWork, &workQueue, std::ref(lock), std::ref(model), std::ref(storage), std::ref(numTriangles));
	}
	
//	5. Inside the for loop, instead of making the function call from step 1, just add the x and y coordinates to the work queue.  The threads you created in part 4 will grab this work as it's created and start extracting triangles.
	for (uint32_t x = 0; x < model.getXDim(); ++x) {
		for (uint32_t y = 0; y < model.getYDim(); ++y) {
			workQueue.Add({x,y});
		}
	}
	
//	6. After all work has been added, add completion "work" (eg x=y=-1) to the work queue in a separate for loop.  Your thread functions should return when they pull this work off the queue.
	for (unsigned i = 0; i < numThreads; ++i) {
		workQueue.Add({(uint32_t)-1, (uint32_t)-1});
	}
	
//	8. Then join with all the threads and save the results to a file.
	for (int x = 0; x < numThreads; x++)
	{
		threads[x]->join();
		delete threads[x];
	}
	delete [] threads;
	
	std::cout << "\nNumber of Triangles: " << std::dec << numTriangles << "\n";
	std::cout << "Size of triangle vector: " << storage.size() << "\n";
	
	uint8_t header[80] = {0};
	uint16_t attribute = 0;
	
	fwrite(header, sizeof(uint8_t), 80, myFile);
	fseek(myFile, 80, SEEK_SET);
	fwrite(&numTriangles, sizeof(uint32_t), 1, myFile);
	fseek(myFile, 84, SEEK_SET);
	
	for (int i = 0; i < numTriangles; ++i) {
		fwrite(storage.back().normal, sizeof(float), 3, myFile);
		fwrite(storage.back().v1, sizeof(float), 3, myFile);
		fwrite(storage.back().v2, sizeof(float), 3, myFile);
		fwrite(storage.back().v3, sizeof(float), 3, myFile);
		fwrite(&attribute, sizeof(uint16_t), 1, myFile);
		storage.popBack();
	}
	
	std::cout << "Finished writing!\n";
	
	std::cout<<"Time to process " << numTriangles << " triangles with " << numThreads << " threads: " << t.EndTimer() << "s.\n";
	
	numTriangles = storage.size();
}

void writeSTL(VoxelShape& model, const char* filename) {
	FILE* myFile;
	myFile = fopen(filename, "wb+");
	
	if (myFile != NULL) {
		
		uint32_t numTriangles = 0;

		MyArray<Triangle> triangles(0);
		
		unsigned numThreads = std::thread::hardware_concurrency();
		
		threadedExtract(myFile, model, triangles, numTriangles, 1);
		threadedExtract(myFile, model, triangles, numTriangles, 2);
		threadedExtract(myFile, model, triangles, numTriangles, 3);
		threadedExtract(myFile, model, triangles, numTriangles, numThreads);
		
		fclose(myFile);

	} else {
		std::cout << "File " << filename << " does not exist! \nProgram stopped." << std::endl;
		
	}
}
