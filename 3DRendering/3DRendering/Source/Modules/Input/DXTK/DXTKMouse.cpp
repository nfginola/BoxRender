#include "DXTKMouse.h"

#include <string>

using namespace DirectX;
using namespace Input;

DXTKMouse::DXTKMouse(HWND& hwnd) :
	m_hwnd(hwnd),
	m_initialized(false)
{
	m_mouse = std::make_unique<Mouse>();

}


DXTKMouse::~DXTKMouse()
{
}

int DXTKMouse::GetDeltaX()
{
	if (m_mouseState.positionMode == Mouse::MODE_RELATIVE)
	{
		return m_mouseState.x;
	}
	else
	{
		return 0;
	}
}

int DXTKMouse::GetDeltaY()
{
	if (m_mouseState.positionMode == Mouse::MODE_RELATIVE)
	{
		return m_mouseState.y;
	}
	else
	{
		return 0;
	}
}

int DXTKMouse::GetScreenCoordX()
{
	int num = 0;
	if (m_mouseState.positionMode == Mouse::MODE_ABSOLUTE)
	{
		return m_mouseState.x;
	}
	else
	{
		return GetCursorPoint().x;
	}
}

int DXTKMouse::GetScreenCoordY()
{
	int num = 0;
	if (m_mouseState.positionMode == Mouse::MODE_ABSOLUTE)
	{
		return m_mouseState.y;
	}
	else
	{
		return GetCursorPoint().y;

	}
}

void DXTKMouse::HideMouse()
{
	m_mouse->SetMode(DirectX::Mouse::MODE_RELATIVE);

}

void DXTKMouse::ShowMouse()
{
	m_mouse->SetMode(DirectX::Mouse::MODE_ABSOLUTE);
}

bool DXTKMouse::LMBDown()
{
	return m_mouseState.leftButton;
}

bool DXTKMouse::RMBDown()
{
	return m_mouseState.rightButton;
}

bool DXTKMouse::MMBDown()
{
	return m_mouseState.middleButton;
}

int DXTKMouse::GetScrollWheelValue()
{
	return m_mouseState.scrollWheelValue;
}

void DXTKMouse::Update()
{
	m_mouseState = m_mouse->GetState();
	m_mouseTracker.Update(m_mouseState);

	if (m_mouseState.positionMode == Mouse::MODE_RELATIVE)
		CenterMousePosition();
}

void DXTKMouse::WindowProcedureHook(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (!m_initialized)
	{
		m_mouse->SetWindow(m_hwnd);
		m_initialized = true;
	}

	Mouse::ProcessMessage(message, wParam, lParam);
}

void DXTKMouse::CenterMousePosition()
{
	RECT r;
	GetClientRect(m_hwnd, &r);

	POINT p;
	p.x = r.right / 2;
	p.y = r.bottom / 2;

	ClientToScreen(m_hwnd, &p);
	SetCursorPos(p.x, p.y);

	//OutputDebugStringW(std::to_wstring(r.right).c_str());
	//OutputDebugStringW(L"\n");

}

POINT DXTKMouse::GetCursorPoint()
{
	POINT p;
	GetCursorPos(&p);
	ScreenToClient(m_hwnd, &p);
	return p;
}
