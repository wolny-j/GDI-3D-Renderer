#pragma once
#include "Framework.h"
#include "Vertex.h"
#include "Matrix.h"
#include "Model.h"
#include "MD2Loader.h"
#include "Camera.h"

class Rasteriser : public Framework
{
public:
	Rasteriser();
	bool Initialise();
	void Update(Bitmap& bitmap);
	void Render(Bitmap& bitmap);
	void GeneratePerspectiveMatrix(float d, float aspectRatio);
	void GenerateViewMatrix(float d, int width, int height);
	void DrawWireFrame(Bitmap& bitmap);
	void DrawBox(HDC hdc, Vertex vertices[]);
	void DrawString(Bitmap& bitmap, LPCTSTR text);

private:
	

	Vertex vertices[4];
	Matrix transform;

	
	Model _model;
	Camera _camera;
	Matrix _perspectiveMatrix1;
	Matrix _perspectiveMatrix2;
	Matrix _viewMatrix;
	Matrix _yRotation;
	Matrix _xRotation;
	Matrix _zRotation;
	Matrix _scaling;
	Matrix _translation;
	double _rotation = 0;
	double _scale = 0;
	double _transform = 0;
	bool xRot = false;
	bool yRot = false;
	bool zRot = false;
	bool scaling = false;
	bool transformBool = false;
	

};


