#include "Camera.h"
#include "Math.h"

Camera::Camera()
{
	_x = 0;
	_y = 0;
	_z = 0;
	_position = Vertex::Vertex();
	_cameraMatrix = Matrix::Matrix();
	_xRot = Matrix::Matrix();
	_yRot = Matrix::Matrix();
	_zRot = Matrix::Matrix();;
	_transformedCamera = Matrix::Matrix();;
}

Camera::Camera(float xRotation, float yRotation, float zRotation, const Vertex& position)
{
	_x = xRotation;
	_y = yRotation;
	_z = zRotation;
	_position = position;
	_cameraMatrix = Matrix::Matrix(std::initializer_list<float>{float(1), float(0), float(0), -float(_position.GetX()),
		float(0), float(1), float(0), -float(_position.GetY()),
		float(0), float(0), float(1), -float(_position.GetZ()),
		float(0), float(0), float(0), float(1)});
	RotateCamera();
}

void Camera::SetXRotation(float x)
{
	_x = x;
}

void Camera::SetYRotation(float y)
{
	_y = y;
}

void Camera::SetZRotation(float z)
{
	_z = z;
}

float Camera::GetXRotation()
{
	return _x;
}

float Camera::GetYRotation()
{
	return _y;
}

float Camera::GetZRotation()
{
	return _z;
}

void Camera::SetPosition(Vertex position)
{
	_position = position;
}

Vertex Camera::GetPosition()
{
	return _position;
}

Matrix Camera::GetCameraMatrix()
{
	return _cameraMatrix;
}

void Camera::RotateCamera()
{
	_xRot = Matrix::Matrix(std::initializer_list<float>{float(1), float(0), float(0), float(0),
		float(0), float(cos(_x)), float(sin(_x)), float(0),
		float(0), float(-sin(_x)), float(cos(_x)), -float(0),
		float(0), float(0), float(0), float(1)});

	_yRot = Matrix::Matrix(std::initializer_list<float>{float(cos(_y)), float(0), float(sin(_y)), float(0),
		float(0), float(1), float(0), float(0),
		float(-sin(_y)), float(-sin(_x)), float(cos(_y)), -float(0),
		float(0), float(0), float(0), float(1)});

	_zRot = Matrix::Matrix(std::initializer_list<float>{float(cos(_z)), float(sin(_z)), float(0), float(0),
		float(-sin(_z)), float(cos(_z)), float(0), float(0),
		float(0), float(0), float(1), -float(0),
		float(0), float(0), float(0), float(1)});

	_transformedCamera = _cameraMatrix * _zRot * _yRot * _xRot;
}

Matrix Camera::GetRotatedCamera()
{
	return _transformedCamera;
}