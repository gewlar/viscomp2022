#ifndef __Quaternion_h__
#define __Quaternion_h__

#include "Vector.h"


class Quaternion {
private:
	Vector m_data;		// (v, w) =>  v=(x,y,z) ... imags ,  w ... reals

public:
	inline Quaternion ()
	:
		m_data(0.f,0.f,0.f,0.f)
	{

	}

	inline Quaternion (Vector q)
	{
		m_data = q;
	}

	inline Quaternion (Vector v, float w)
	{
		m_data = v;
		m_data[3] = w;
	}

	inline Quaternion (const Quaternion &other)
	{
		m_data = other.m_data;
	}

	inline float& operator[] (int element)
	{
		assert(element >= 0 && element <= 3);
		return m_data[element];
	}

	inline const float& operator[] (int element) const
	{
		assert(element >= 0 && element <= 3);
		return m_data[element];
	}

	static float myCopysign(float x, float y)
	{
		if(x*y >= 0)
			return x;
		else
			return -x;
	}

	static float myMax(float x, float y)
	{
		if(x > y)
			return x;
		else
			return y;
	}

	//////////////////////////////////////////////////////////////////////////
	// constructs a quaternion from a orthonormal rotations matrix.
	// only upper left 3x3 sub matrix is used
	//////////////////////////////////////////////////////////////////////////
	inline Quaternion (const Matrix &M)
	{
		Vector &q = m_data;

		q[3] = sqrt( myMax( 0, 1 + M[0][0] + M[1][1] + M[2][2] ) ) / 2;
		q[0] = sqrt( myMax( 0, 1 + M[0][0] - M[1][1] - M[2][2] ) ) / 2;
		q[1] = sqrt( myMax( 0, 1 - M[0][0] + M[1][1] - M[2][2] ) ) / 2;
		q[2] = sqrt( myMax( 0, 1 - M[0][0] - M[1][1] + M[2][2] ) ) / 2;
		q[0] = (float)myCopysign( q[0], M[2][1] - M[1][2] );
		q[1] = (float)myCopysign( q[1], M[0][2] - M[2][0] );
		q[2] = (float)myCopysign( q[2], M[1][0] - M[0][1] );
	}

	//////////////////////////////////////////////////////////////////////////
	// returns a orthonormal rotations matrix constructed from this quaternion.
	//////////////////////////////////////////////////////////////////////////
	inline Matrix getRotMatrix() const
	{
#if STEP >= 4
		// STEP 4
#else
		TODO(4);
		return Matrix::createIdentityMatrix();
#endif

	}

	//////////////////////////////////////////////////////////////////////////
	//common/simple mathematical functions
	//////////////////////////////////////////////////////////////////////////
	inline const Quaternion operator+(const Quaternion &other) const { return Quaternion( m_data.add4(other.m_data) );		};
	inline const Quaternion operator-(const Quaternion &other) const { return Quaternion( m_data.sub4(other.m_data) );		};
	inline const Quaternion operator*(const float other ) const {	   return Quaternion( m_data.multScalar4(other) );		};
	inline const Quaternion operator-() const { return Quaternion( m_data.minus4() );	 };

	inline float sqrdNorm() const {
		return m_data.sqrdLength4();
	}

	inline float norm() const
	{
		return sqrt(sqrdNorm());
	}

	inline float dot(const Quaternion &other) const
	{
		return m_data.dot4(other.m_data);
	}

	//////////////////////////////////////////////////////////////////////////
	// Quaternion mutiply
	//////////////////////////////////////////////////////////////////////////
	inline const Quaternion operator*(const Quaternion &other) const
	{
#if STEP >= 4
		// STEP 4
#else
		TODO(4);
		return Quaternion();
#endif
	}

	//////////////////////////////////////////////////////////////////////////
	// conjugate
	//////////////////////////////////////////////////////////////////////////
	inline const Quaternion unit() const
	{
		return *this * (1.0f / this->norm());
	}

	//////////////////////////////////////////////////////////////////////////
	// conjugate
	//////////////////////////////////////////////////////////////////////////
	inline const Quaternion conj() const
	{
		return Quaternion(m_data.minus3());
	}

	//////////////////////////////////////////////////////////////////////////
	// inverse
	//////////////////////////////////////////////////////////////////////////
	inline const Quaternion inversed() const
	{
		return this->conj() * this->sqrdNorm();
	}

	//////////////////////////////////////////////////////////////////////////
	// exponential
	//////////////////////////////////////////////////////////////////////////
	static const Quaternion qexp(const Quaternion & q)
	{
		Vector v = q.m_data;
		v[3] = 1;			//make it a normal vector (im. part)
		Vector res;

		res = v.normalized3().multScalar3(sin(v.length3()));
		res[3] = cos(v.length3());

		return Quaternion(res.multScalar4(exp(q.m_data[3])));

	}

	//////////////////////////////////////////////////////////////////////////
	// logarithm
	//////////////////////////////////////////////////////////////////////////
	static const Quaternion qlog(const Quaternion & q)
	{
		Vector v = q.m_data;
		v[3] = 1;			//make it a normal vector (im. part)

		v = v.normalized3() * acos(q[3] / q.norm() );
		v[3] = log(q.norm());

		return Quaternion(v);
	}

	//////////////////////////////////////////////////////////////////////////
	// slerp
	//////////////////////////////////////////////////////////////////////////
	static const Quaternion slerp(Quaternion q, Quaternion p, float t)
	{
		float cosphi = q.m_data.dot4(p.m_data);

		if(cosphi < 0.0f)
		{
			cosphi *= -1.0f;
			q = -q;
		}

		const float DOT_THRESHOLD = 0.9995f;
		if (cosphi > DOT_THRESHOLD) {
			// interpolate linearly
			return (q + (p - q) * t).unit();
		}

		float sinphi = sqrt(1 - cosphi * cosphi);
		float phi = acos(cosphi);

		Quaternion res = q * (sin( phi * (1-t) ) / sinphi) + p * (sin( phi * t) / sinphi);

		return res;

	}

};

#endif // __Quaternion_h__


