#include "Rasteriser.h"
#include <list> 
#include <initializer_list>
#include <string>
Rasteriser app;

Rasteriser::Rasteriser():Framework()
{
}

bool Rasteriser::Initialise()
{

	_camera = Camera::Camera(0, 0, 0, Vertex::Vertex(0, 0, -50, 1));
	
	if (!MD2Loader::LoadModel("cube.md2", _model, &Model::AddPolygon, &Model::AddVertex))
	{
		return false;
	}
	return true;

}

void Rasteriser::Update(Bitmap& bitmap)
{
	_yRotation = Matrix::Matrix(std::initializer_list<float>{float(cos(_rotation)), 0, float(sin(_rotation)), 0,
																0, float(1), 0, 0,
																float(-sin(_rotation)), 0, float(cos(_rotation)), 0,
																0, 0, 0, float(1)});
	_xRotation = Matrix::Matrix(std::initializer_list<float>{float(1), float(0), float(0), float(0),
															float(0), float(cos(_rotation)), float(sin(_rotation)), float(0),
															float(0), float(-sin(_rotation)), float(cos(_rotation)), -float(0),
															float(0), float(0), float(0), float(1)});

	_zRotation = Matrix::Matrix(std::initializer_list<float>{float(cos(_rotation)), float(sin(_rotation)), float(0), float(0),
													float(-sin(_rotation)), float(cos(_rotation)), float(0), float(0),
													float(0), float(0), float(1), -float(0),
													float(0), float(0), float(0), float(1)});

	_scaling = Matrix::Matrix(std::initializer_list<float>{float(_scale), 0, 0, 0,
															0, float(_scale), 0, 0,
															0, 0, float(_scale), 0,
															0, 0, 0, 1});

	_translation = Matrix::Matrix(std::initializer_list<float>{float(1), 0, 0, float(_transform),
																0, float(1), 0, 0,
																0, 0, float(1), 0,
																0, 0, 0, float(1)});
	GeneratePerspectiveMatrix(1, (float(bitmap.GetWidth())/float(bitmap.GetHeight())));
	GenerateViewMatrix(1, bitmap.GetWidth(), bitmap.GetHeight());

	//Presentation statements 
	if (_rotation < 2)
	{
		yRot = true;
	}
	else if (_rotation > 2 && _rotation < 5)
	{
		xRot = true;
		yRot = false;
	}
	else if (_rotation > 5 && _rotation < 7)
	{
		zRot = true;
		xRot = false;
	}
	else if (_rotation > 7 && _rotation < 8.5)
	{
		zRot = false;
		yRot = true;
		scaling = true;
	}
	else if (_rotation > 8.5 && _rotation < 12)
	{
		transformBool = true;
		scaling = false;
	}
	else if (_rotation > 12)
	{
		_rotation = 0;
		_scale = 0;
		_transform = 0;
		scaling = false;
		transformBool = false;
	}
	_rotation = _rotation + 0.01;

	if(_rotation > 7)
	{
		_scale = _scale + 0.01;
	}
	if (_rotation > 8.5 && _rotation < 10)
	{
		_transform = _transform + 0.5;		
	}
	else if (_rotation > 10)
	{
		_transform = _transform - 0.5;
	}
	
	
}

void Rasteriser::Render(Bitmap& bitmap)
{
	bitmap.Clear(RGB(0, 0, 0));
	if (yRot == true)
	{
		_model.ApplyTransformToLocalVertices(_yRotation);
	}
	else if (xRot == true)
	{
		_model.ApplyTransformToLocalVertices(_xRotation);
	}
	else if (zRot == true)
	{
		_model.ApplyTransformToLocalVertices(_zRotation);
	}

	if (scaling == true)
	{
		_model.ApplyTransformToTransformedVertices(_scaling);
	}

	if (transformBool == true)
	{
		_model.ApplyTransformToTransformedVertices(_translation);
	}
	_camera.RotateCamera();
	_model.ApplyTransformToTransformedVertices(_camera.GetRotatedCamera());
	_model.ApplyTransformToTransformedVertices(_perspectiveMatrix1);
	_model.Dehomogenize();
	_model.ApplyTransformToTransformedVertices(_viewMatrix);
	
	DrawWireFrame(bitmap);
	
}


void Rasteriser::DrawWireFrame(Bitmap& bitmap)
{
	HPEN hPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	
	HDC hdc = bitmap.GetDC();
	SelectObject(hdc, hPen);
	int i = 0;
	if (yRot == true && scaling == false && transformBool == false)
	{
	DrawString(bitmap, L"Y rotation");
	}
	else if (xRot == true)
	{
		DrawString(bitmap, L"X rotation");
	}
	else if (zRot == true)
	{
		DrawString(bitmap, L"Z rotation");
	}
	else if (scaling == true)
	{
		DrawString(bitmap, L"Scaling");
	}
	else if (transformBool == true)
	{
		DrawString(bitmap, L"Transform");
	}
	
	for (i; i < _model.GetPolygonCount(); i++)
	{
		int index1 = _model.GetPolygons()[i].GetIndex(0);
		int index2 = _model.GetPolygons()[i].GetIndex(1);
		int index3 = _model.GetPolygons()[i].GetIndex(2);
		
		MoveToEx(hdc, int(this->_model.GetTransformedVertices()[index1].GetX()), int(this->_model.GetTransformedVertices()[index1].GetY()), NULL);
		LineTo(hdc, int(this->_model.GetTransformedVertices()[index2].GetX()), int(this->_model.GetTransformedVertices()[index2].GetY()));
		LineTo(hdc, int(this->_model.GetTransformedVertices()[index3].GetX()), int(this->_model.GetTransformedVertices()[index3].GetY()));
		LineTo(hdc, int(this->_model.GetTransformedVertices()[index1].GetX()), int(this->_model.GetTransformedVertices()[index1].GetY()));

		
	}

	DeleteObject(hPen);

}


void Rasteriser::GeneratePerspectiveMatrix(float d, float aspectRatio)
{
	_perspectiveMatrix1 = Matrix::Matrix(std::initializer_list<float>{ (d / aspectRatio), float(0), float(0), float(0),
		float(0), d, float(0), float(0),
		float(0), float(0), d, float(0), 
		float(0), float(0), float(1), float(0) });
}

void Rasteriser::GenerateViewMatrix(float d, int width, int height)
{
	_viewMatrix = Matrix::Matrix(std::initializer_list<float>{ float(width / 2), float(0), float(0), float(width / 2),
		float(0), float(-height / 2), float(0), float(height / 2), 
		float(0), float(0), float(d / 2), float(d / 2), 
		float(0), float(0), float(0), float(1) });

}
void Rasteriser::DrawString(Bitmap& bitmap, LPCTSTR text)
{
	HDC hdc = bitmap.GetDC();
	HFONT hFont, hOldFont;

	// Retrieve a handle to the variable stock font.  
	hFont = hFont = CreateFont(48, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Myfont"));

	// Select the variable stock font into the specified device context. 
	if (hOldFont = (HFONT)SelectObject(hdc, hFont))
	{
		SetTextColor(hdc, RGB(255, 255, 255));
		SetBkColor(hdc, RGB(0, 0, 0));

		// Display the text string.  
		TextOut(hdc, 10, 10, text, lstrlen(text));

		// Restore the original font.        
		SelectObject(hdc, hOldFont);
	}
	DeleteObject(hFont);
}




