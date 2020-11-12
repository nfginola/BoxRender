#pragma once
#include <Windows.h>

class Window;
class ApplicationWindow;

namespace Input
{
	class IMouseInput
	{
	public:
		IMouseInput() { };
		virtual ~IMouseInput() { };

		IMouseInput(const IMouseInput& rhs) = delete;

		virtual int GetDeltaX() = 0;
		virtual int GetDeltaY() = 0;

		virtual int GetScreenCoordX() = 0;
		virtual int GetScreenCoordY() = 0;

		virtual void HideMouse() = 0;
		virtual void ShowMouse() = 0;

		virtual bool LMBDown() = 0;
		virtual bool RMBDown() = 0;
		virtual bool MMBDown() = 0;
		virtual int GetScrollWheelValue() = 0;

		virtual void Update() = 0;

	private:
		friend Window;
		friend ApplicationWindow;

		virtual void WindowProcedureHook(UINT message, WPARAM wParam, LPARAM lParam) = 0;


	};
}
