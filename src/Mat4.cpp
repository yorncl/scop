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

Mat4 Mat4::new_identity()
{
	Mat4 m;
	for (int i = 0; i < 4; i++)
		m[i][i] = 1.0f;
	return m;
}

Mat4 Mat4::new_scale(float x, float y, float z)
{
	Mat4 m = new_identity();
	m[0][0] = x; 
	m[1][1] = y; 
	m[2][2] = z; 
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

Mat4& Mat4::operator=(Mat4& m)
{
	for (int i = 0; i < 16; i++)
		_data[i] = m._data[i];
	return *this;
}

float* Mat4::operator[](size_t i)
{
	return &_data[i]; // probably not a best practice, because _data is private, but returning a pointer to it makes us able to modify the data elsewhere than in the class
	// but I don't care right now
}
