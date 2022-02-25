#pragma once
#include "Vertex.h"
#include "Matrix.h"
class Camera
{
public:
	Camera();
	Camera(float xRotation, float yRotation, float zRotation, const Vertex& position);
	void SetXRotation(float x);
	void SetYRotation(float y);
	void SetZRotation(float z);
	float GetXRotation();
	float GetYRotation();
	float GetZRotation();
	void SetPosition(Vertex position);
	Vertex GetPosition();
	void RotateCamera();
	Matrix GetCameraMatrix();
	Matrix GetRotatedCamera();
private:
	float _x;
	float _y;
	float _z;
	Vertex _position;
	Matrix _cameraMatrix;
	Matrix _xRot;
	Matrix _yRot;
	Matrix _zRot;
	Matrix _transformedCamera;
};

