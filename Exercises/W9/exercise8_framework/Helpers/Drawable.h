#ifndef __Drawable_h__
#define __Drawable_h__

#include "Matrix.h"
#include "Vector.h"

class World;

enum DrawPass {
	DRAWPASS_FINAL			= 0x01,
	DRAWPASS_DEPTHONLY		= 0x02,
	DRAWPASS_SHADOWMAP		= 0x04,
	DRAWPASS_PREDRAW		= 0x08,
	DRAWPASS_POSTDRAW       = 0x10
};

// Base class for things that can be drawn
class Drawable
{
public:
	Drawable() {
		m_modelMatrix = Matrix::createIdentityMatrix();
	}

	virtual ~Drawable() {}

	// Returns the matrix transforming points from model coordinates to world coordinates
	const Matrix &getModelMatrix() const { return m_modelMatrix; }

	// Defines how points in model coordinates are transformed to world coordinates
	void setModelMatrix(const Matrix &val) { m_modelMatrix = val; }

	// Draws the object to the given world
	virtual void draw(World & World, DrawPass pass) = 0;

protected:
	// Matrix transforming points from model coordinates to world coordinates
	Matrix m_modelMatrix;

private:
};

enum BuiltInDrawables 
{
	DRAWABLE_RECTANGLE	= 0x01,
	DRAWABLE_CUBE		= 0x02,

	DRAWABLE_USERDEFINED = 0xFFFFFFFF
};
                    
struct SimpleDrawableVertex 
{
	Vector	position;
	Vector  normal;
	Vector  tex_coord;
};

class SimpleDrawable: public Drawable 
{
public:
//	SimpleDrawable(PrimitivesTypes type);


};


#endif // __Drawable_h__
