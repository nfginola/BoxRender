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

		virtual int getDeltaX() = 0;
		virtual int getDeltaY() = 0;

		virtual int getScreenCoordX() = 0;
		virtual int getScreenCoordY() = 0;

		virtual void hideMouse() = 0;
		virtual void showMouse() = 0;

		virtual bool LMBDown() = 0;
		virtual bool RMBDown() = 0;
		virtual bool MMBDown() = 0;
		virtual int getScrollWheelValue() = 0;

		virtual void update() = 0;

	private:
		friend Window;
		friend ApplicationWindow;

		virtual void windowProcedureHook(UINT message, WPARAM wParam, LPARAM lParam) = 0;


	};
}
