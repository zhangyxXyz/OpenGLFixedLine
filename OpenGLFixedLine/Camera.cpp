#include "Camera.h"
#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>


Camera::Camera() :m_Pos(0.0f, 0.0f, 0.0f), m_ViewCenter(0.0f, 0.0f, -1.0f),
m_Up(0.0f, 1.0f, 0.0f), m_MoveLeft(false), m_MoveRight(false), m_MoveForward(false), m_MoveBackward(false)
{
}


Camera::~Camera()
{
}

void Camera::RotateView(float angle, float x, float y, float z)
{
	Vector3f viewDirection = m_ViewCenter - m_Pos;
	Vector3f newDirection;
	float C = cosf(angle);
	float S = sinf(angle);

	// rotate matrix
	Vector3f tmpX(C + x*x*(1 - C), x*y*(1 - C) - z*S, x*z*(1 - C) + y*S);
	newDirection.x = tmpX*viewDirection;

	Vector3f tmpY(x*y*(1 - C) + z*S, C + y*y*(1 - C), y*z*(1 - C) - x*S);
	newDirection.y = tmpY*viewDirection;

	Vector3f tmpZ(x*z*(1 - C) - y*S, y*z*(1 - C) + x*S, C + z*z*(1 - C));
	newDirection.z = tmpZ*viewDirection;

	m_ViewCenter = m_Pos + newDirection;

}

void Camera::Update(float deltaTime)
{
	// update everything
	float moveSpeed = 10.0f;
	float rotateSpeed = 1.0f;
	if (m_MoveLeft)
	{
		// left direction vector
		Vector3f leftDirection = m_ViewCenter - m_Pos;;
		leftDirection.Normalize();
		Vector3f rightDirection = leftDirection^m_Up;
		rightDirection.Normalize();
		m_Pos = m_Pos + rightDirection*moveSpeed*deltaTime*-1.0f;
		m_ViewCenter = m_ViewCenter + rightDirection*moveSpeed*deltaTime*-1.0f;
	}
	if (m_MoveRight)
	{
		//right direction vector
		Vector3f leftDirection = m_ViewCenter - m_Pos;;
		leftDirection.Normalize();
		Vector3f rightDirection = leftDirection^m_Up;
		rightDirection.Normalize();
		m_Pos = m_Pos + rightDirection*moveSpeed*deltaTime;
		m_ViewCenter = m_ViewCenter + rightDirection*moveSpeed*deltaTime;
	}
	if (m_MoveForward)
	{
		//forword direction vector
		Vector3f forwardDirection = m_ViewCenter - m_Pos;
		forwardDirection.Normalize();
		m_Pos = m_Pos + forwardDirection*moveSpeed*deltaTime;
		m_ViewCenter = m_ViewCenter + forwardDirection*moveSpeed*deltaTime;
	}
	if (m_MoveBackward)
	{
		//background direction vector
		Vector3f backwardDirection = m_Pos - m_ViewCenter;
		backwardDirection.Normalize();
		m_Pos = m_Pos + backwardDirection*moveSpeed*deltaTime;
		m_ViewCenter = m_ViewCenter + backwardDirection*moveSpeed*deltaTime;
	}

	// set model view matrix
	gluLookAt(m_Pos.x, m_Pos.y, m_Pos.z,
		m_ViewCenter.x, m_ViewCenter.y, m_ViewCenter.z,
		m_Up.x, m_Up.y, m_Up.z);
}

void Camera::Pitch(float angle)
{
	// right direction vector(up and down)
	Vector3f viewDirection = m_ViewCenter - m_Pos;
	viewDirection.Normalize();
	Vector3f rightDirection = viewDirection^m_Up;
	rightDirection.Normalize();
	RotateView(angle, rightDirection.x, rightDirection.y, rightDirection.z);
}

void Camera::Yaw(float angle)
{
	// up direction vector(left and right)
	RotateView(angle, m_Up.x, m_Up.y, m_Up.z);
}

void Camera::SwitchTo3D()
{
	glMatrixMode(GL_PROJECTION);// tell the GPU processer that i would select the project Matrix
	glLoadIdentity();
	gluPerspective(50.0f, (float)m_ViewPortWidth / (float)m_VIewPortHeight, 0.1f, 1000.0f); // set some value to project matrix
	glMatrixMode(GL_MODELVIEW);// tel .. modle view matrix
}

void Camera::SwitchTo2D()
{
	glMatrixMode(GL_PROJECTION);//tell the gpu processer that i would select the projection matrix
	glLoadIdentity();
	gluOrtho2D(-m_ViewPortWidth / 2, m_ViewPortWidth / 2, -m_VIewPortHeight / 2, m_VIewPortHeight / 2);
	glMatrixMode(GL_MODELVIEW);//tell .... model view matrix
}
