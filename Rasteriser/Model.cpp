#include "Model.h"

Model::Model()
{}

Model::~Model()
{}

const vector<Polygon3D>& Model::GetPolygons()
{
	return _polygons;
}

const vector<Vertex>& Model::GetVertices()
{
	return _vertices;
}
const vector<Vertex>& Model::GetTransformedVertices()
{
	return _transformedVertices;
}

size_t Model::GetPolygonCount()const
{
	return _polygons.size();
}

size_t Model::GetVertexCount()const
{
	return _vertices.size();
}
void Model::AddVertex(float x, float y, float z)
{	
		_vertices.push_back(Vertex::Vertex(x, y, z, 1));
}

void Model::AddPolygon(int i0, int i1, int i2)
{
	_polygons.insert(_polygons.begin() + _polygons.size(), Polygon3D::Polygon3D(i0, i1, i2));
	//_polygons.push_back(Polygon3D::Polygon3D(i0, i1, i2));
}
void Model::ApplyTransformToLocalVertices(const Matrix& transform)
{
	if (_transformedVertices.size() > 0)
	{
		_transformedVertices.clear();
	}
	for (int x = 0; x < _vertices.size(); x++)
	{
		_transformedVertices.push_back(Vertex::Vertex((transform * _vertices[x])));
	}
}
void Model::ApplyTransformToTransformedVertices(const Matrix& transform)
{
	for (int x = 0; x < int(_transformedVertices.size()); x++)
	{
		_transformedVertices[x] = Vertex::Vertex((transform * _transformedVertices[x]));
	}
}
void Model::Dehomogenize()
{
	for (int x = 0; x < _transformedVertices.size(); x++)
	{
		_transformedVertices[x].Dehomogenize();
	}
}

