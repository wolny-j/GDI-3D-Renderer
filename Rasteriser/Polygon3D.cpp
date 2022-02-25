#include "Polygon3D.h"

Polygon3D::Polygon3D()
{
	_indices[0] = 0;
	_indices[1] = 0;
	_indices[2] = 0;
};

Polygon3D::Polygon3D(int index0, int index1, int index2)
{
	_indices[0] = { index0 };
	_indices[1] = { index1 };
	_indices[2] = { index2 };

}

Polygon3D::~Polygon3D()
{}

Polygon3D::Polygon3D(const Polygon3D& p)
{
	Copy(p);
}

int Polygon3D::GetIndex(int index) const
{
	return _indices[index];
}

Polygon3D& Polygon3D::operator= (const Polygon3D& rhs)
{
	if (this != &rhs)
	{
		Copy(rhs);
	}
	return *this;
}
void Polygon3D::Copy(const Polygon3D& v)
{
	_indices[0] = v.GetIndex(0);
	_indices[1] = v.GetIndex(1);
	_indices[2] = v.GetIndex(2);
}