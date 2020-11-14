#pragma once
#include "../IMouseInput.h"
#include <memory>

#include <DirectXTK/Mouse.h>

namespace Input
{
	class DXTKMouse : public IMouseInput
	{
	public:
		DXTKMouse(HWND& hwnd);		// Important reference: hwnd doesn't exist yet until the first WindowProcedureHook call
		~DXTKMouse();

		int getDeltaX() override;
		int getDeltaY() override;

		int getScreenCoordX() override;
		int getScreenCoordY() override;

		void hideMouse() override;
		void showMouse() override;

		bool LMBDown() override;
		bool RMBDown() override;
		bool MMBDown() override;

		int getScrollWheelValue() override;

		void update() override;

	private:
		void windowProcedureHook(UINT message, WPARAM wParam, LPARAM lParam) override;
		void centerMousePosition();
		POINT getCursorPoint();

	private:
		HWND& m_hwnd;
		std::unique_ptr<DirectX::Mouse> m_mouse;
		DirectX::Mouse::State m_mouseState;
		DirectX::Mouse::ButtonStateTracker m_mouseTracker;

		bool m_initialized;

	};
}


