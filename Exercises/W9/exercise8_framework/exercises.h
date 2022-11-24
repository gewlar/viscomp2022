#ifndef __STEPs_h__
#define __STEPs_h__

#include <iostream>

// Empty Skeleton
#define STEP 0

// STEP 1:  Matrix
// finish Matrix Class, fill in empty functions
// #define STEP  1

// STEP 2:  Camera
// Use lookAtMatrix to implement Simple camera movements/
// #define STEP  2

// STEP 3:  Helicopter
// Use Matrices to rotate and position rotors. scale helicopter 
// place helicopter to roof 
// #define STEP  3

// STEP 4:  Quaternion
//Finish quaternion class, fill in empty functions
// #define STEP  4

// STEP 5:  Camera Path
// Use built in cameraviews matrices to reconstruct camera path key points
// (position and rotation quaternions), use given spline functions to interpolate 
// between key frames(position and quaternions)
// #define STEP  5



#define TODO(A)					\
	if((A) <= STEP)			\
		std::cout << "You have to fill in Code at" << __FILE__ << ":" << __LINE__ << " for Ex.:" << #A << std::endl

#endif // __STEPs_h__
