#pragma once

class Vertex
{
public:
	Vertex(void);
	Vertex(float x, float y, float z, float w);
	Vertex(const Vertex& v);
	Vertex(Vertex&& other);

	~Vertex(void);

	float GetX(void) const;
	void SetX(float x);
	float GetY(void) const;
	void SetY(float y);
	float GetW(void) const;
	void SetW(float w);
	float GetZ(void) const;
	void SetZ(float z);
	void Dehomogenize();

	Vertex& operator= (const Vertex& rhs);
	Vertex& operator= (Vertex&& rhs);

private:
	float _x;
	float _y;
	float _z;
	float _w;

	void Init(float x, float y, float z, float w);
	void Copy(const Vertex& v);
};

