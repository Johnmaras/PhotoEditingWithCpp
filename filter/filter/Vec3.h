//------------------------------------------------------------
//
// C++ course assignment code 
//
// G. Papaioannou, 2015
//
//

#ifndef _Vec3_
#define _Vec3_

namespace math

{

	template <typename S>
	class Vec3
	{
	public:
		// members
		union { S x, r; };
		union { S y, g; };
		union { S z, b; };

		// member functions
		S & operator [] (size_t index)
		{
			return *(reinterpret_cast<S*>(this) + index);
		}

		Vec3<S> operator + (const Vec3<S> & right)
		{
			Vec3<S> left;
			left.x = x + right.x;
			left.y = y + right.y;
			left.z = z + right.z;
			return left;
		}

		Vec3<S> operator - (const Vec3<S> & right)
		{
			Vec3<S> left;
			left.x = x - right.x;
			left.y = y - right.y;
			left.z = z - right.z;
			return left;
		}

		Vec3<S> operator * (const Vec3<S> & right)
		{
			Vec3<S> left;
			left.x = x * right.x;
			left.y = y * right.y;
			left.z = z * right.z;
			return left;
		}

		Vec3<S> operator * (S right)
		{
			Vec3<S> left;
			left.x = x * right;
			left.y = y * right;
			left.z = z * right;
			return left;
		}

		Vec3<S> operator / (S right)
		{
			Vec3<S> left;
			left.x = x / right;
			left.y = y / right;
			left.z = z / right;
			return left;
		}

		Vec3<S> operator / (const Vec3<S> & right)
		{
			Vec3<S> left;
			left.x = x / right.x;
			left.y = y / right.y;
			left.z = z / right.z;
			return left;
		}

		Vec3<S> & operator += (const Vec3<S> & right)
		{
			x += right.x;
			y += right.y;
			z += right.z;
			return *this;
		}

		Vec3<S> & operator -= (const Vec3<S> & right)
		{
			x -= right.x;
			y -= right.y;
			z -= right.z;
			return *this;
		}

		Vec3<S> & operator /= (const Vec3<S> & right)
		{
			x /= right.x;
			y /= right.y;
			z /= right.z;
			return *this;
		}

		Vec3<S> & operator *= (const Vec3<S> & right)
		{
			x *= right.x;
			y *= right.y;
			z *= right.z;
			return *this;
		}

		Vec3<S> & operator *= (S right)
		{
			x *= right;
			y *= right;
			z *= right;
			return *this;
		}

		Vec3<S> & operator /= (S right)
		{
			x /= right;
			y /= right;
			z /= right;
			return *this;
		}

		// constructors
		Vec3<S>(S x, S y, S z): x(x), y(y), z(z) {}

		Vec3<S>(S val): x(val), y(val), z(val) {}

		Vec3<S>(): x(0), y(0), z(0) {}

		Vec3<S>(const Vec3<S> & right): x(right.x), y(right.y), z(right.z) {}

		// asignment and equality
		Vec3<S> & operator = (const Vec3<S> & right)
		{
			x = right.x;
			y = right.y;
			z = right.z;
			return *this;
		}

		bool operator == (const Vec3<S> & right) const
		{
			return x == right.x && y == right.y && z == right.z;
		}

		bool operator != (const Vec3<S> & right) const
		{
			return x != right.x || y != right.y || z != right.z;
		}
	};

	template<typename S>
	Vec3<S> operator * (S a, Vec3<S> v)
	{
		return v*a;
	}

	template<typename S>
	Vec3<S> operator * (int a, Vec3<S> v){
		return v*S(a);
	}

	template<typename S>
	Vec3<S> operator * (Vec3<S> v, int a){
		return v*S(a);
	}

	template<typename S>
	Vec3<S> operator / (Vec3<S> v, int a){
		return v/S(a);
	}
} // namespace math

#endif