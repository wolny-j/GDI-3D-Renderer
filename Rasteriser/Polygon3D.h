#pragma once
class Polygon3D
{
public:
	Polygon3D();
	Polygon3D(int index0, int index1, int index2);
	~Polygon3D();
	Polygon3D(const Polygon3D& p);
	// Accessor to return index of specified vertex
	int GetIndex(int) const;
	Polygon3D& operator= (const Polygon3D& rhs);
private:
	int _indices[3];
	void Copy(const Polygon3D& v);
};
