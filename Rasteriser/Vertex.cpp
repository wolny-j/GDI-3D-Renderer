#include "Vertex.h"

// Constructors

Vertex::Vertex(void)
{
	Init(0.0f, 0.0f, 0.0f, 0.0f);
}

Vertex::Vertex(float x, float y, float z, float w)
{
	Init(x, y, z, w);
}

Vertex::Vertex(const Vertex& v)
{
	Copy(v);
}

Vertex::Vertex(Vertex&& v)
{
	Copy(v);
}

Vertex::~Vertex(void)
{
}

// Accessors and mutators

float Vertex::GetX(void) const
{
	return _x;
}

void Vertex::SetX(float x)
{
	_x = x;
}

float Vertex::GetY(void) const
{
	return _y;
}

void Vertex::SetY(float y)
{
	_y = y;
}

float Vertex::GetW(void) const
{
	return _w;
}

void Vertex::SetW(float w)
{
	_w = w;
}

float Vertex::GetZ(void) const
{
	return _z;
}

void Vertex::SetZ(float z)
{
	_z = z;
}

void Vertex::Dehomogenize()
{
	this->SetX(GetX() / this->GetW());
	this->SetY(GetY() / this->GetW());
	this->SetZ(GetZ() / this->GetW());
	this->SetW(GetW() / this->GetW());
	
}

// Operator overloads

Vertex& Vertex::operator= (const Vertex& rhs)
{
	if (this != &rhs)
	{
		Copy(rhs);
	}
	return *this;
}

Vertex& Vertex::operator= (Vertex&& rhs)
{
	if (this != &rhs)
	{
		Copy(rhs);
	}
	return *this;
}


// Private methods

void Vertex::Init(float x, float y, float z, float w)
{
	_x = x;
	_y = y;
	_w = 1;
	_z = z;
}

void Vertex::Copy(const Vertex& v)
{
	_x = v.GetX();
	_y = v.GetY();
	_w = v.GetW();
	_z = v.GetZ();
}


