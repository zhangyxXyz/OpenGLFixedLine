#pragma once
#include "Vector3f.h"

class Camera
{
public:
	Camera();
	~Camera();
public:
	Vector3f m_Pos;
	Vector3f m_ViewCenter;
	Vector3f m_Up;
	int m_ViewPortWidth;
	int m_VIewPortHeight;
	union
	{
		struct  
		{
			bool m_MoveLeft;
			bool m_MoveRight;
			bool m_MoveForward;
			bool m_MoveBackward;
		};
	};
	void Update(float deltaTime);
	void Pitch(float angle);
	void Yaw(float angle);
	void SwitchTo3D();
	void SwitchTo2D();

protected:
	void RotateView(float angle, float x, float y, float z);
};

