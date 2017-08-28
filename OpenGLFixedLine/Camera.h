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
	void RotateView(float angle, float x, float y, float z);
	void Update(float deltaTime);
	void Pitch(float angle);
	void Yaw(float angle);
};

