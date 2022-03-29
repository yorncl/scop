#include "Mat4.hpp"
#include <string.h>

Mat4::Mat4()
{
	memset(_data, 0, sizeof(float) * 16);
}

Mat4::Mat4(float value)
{
	for (int i = 0; i < 16; i++)
		_data[i] = value;
}


Mat4::Mat4(const Mat4& m)
{
	for (int i = 0; i < 16; i++)
		_data[i] = m._data[i];
}

Mat4::~Mat4()
{
}

float* Mat4::data()
{
	return _data;
}

Mat4 Mat4::new_identity()
{
	Mat4 m;
	for (int i = 0; i < 4; i++)
		m[i][i] = 1.0f;
	return m;
}

Mat4 Mat4::new_scale(float x, float y, float z)
{
	Mat4 m;
	m[0][0] = x; 
	m[1][1] = y; 
	m[2][2] = z; 
	m[3][3] = 1.0f; 
	return m;
}

Mat4 Mat4::new_translate(float x, float y, float z)
{
	Mat4 m = new_identity();
	m[3][0] = x; 
	m[3][1] = y; 
	m[3][2] = z; 
	return m;
}

Mat4 Mat4::new_rotation()
{
	// TODO
	return new_identity();
}

Mat4 Mat4::new_projection()
{
	//TODO
	return new_identity();
}

Mat4& Mat4::operator=(const Mat4& m)
{
	for (int i = 0; i < 16; i++)
		_data[i] = m._data[i];
	return *this;
}

float* Mat4::operator[](size_t i)
{
	return &_data[i * 4];
}

const float* Mat4::operator[](size_t i) const
{
	return &_data[i * 4];
}

Mat4 operator*(const Mat4& m, float f)
{
	Mat4 r;
	for (int i = 0; i < 16; i++)
		r._data[i] = m._data[i] * f;
	return r;
}

Mat4 operator*(float f, const Mat4& m)
{
	return m * f;
}

Mat4 operator*(const Mat4& m1, const Mat4& m2)
{
	Mat4 r;
	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
			r[j][i] = m1[0][i] * m2[j][0] + m1[1][i] * m2[j][1] + m1[2][i] * m2[j][2] + m1[3][i] * m2[j][3];
	}
	return r;
}

std::ostream& operator<<(std::ostream &os, const Mat4& m)
{
	os << "Mat4 :" << std::endl;
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
			os << m[j][i] << ' ';
		os << std::endl;
	}
	os << "Raw Mat4: " << std::endl;
	for (int i = 0; i < 16; i++)
		std::cout << m._data[i];
	os << std::endl;
	return os;
}
