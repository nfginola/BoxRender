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

		int GetDeltaX() override;
		int GetDeltaY() override;

		int GetScreenCoordX() override;
		int GetScreenCoordY() override;

		void HideMouse() override;
		void ShowMouse() override;

		bool LMBDown() override;
		bool RMBDown() override;
		bool MMBDown() override;

		int GetScrollWheelValue() override;

		void Update() override;

	private:
		void WindowProcedureHook(UINT message, WPARAM wParam, LPARAM lParam) override;
		void CenterMousePosition();
		POINT GetCursorPoint();

	private:
		HWND& m_hwnd;
		std::unique_ptr<DirectX::Mouse> m_mouse;
		DirectX::Mouse::State m_mouseState;
		DirectX::Mouse::ButtonStateTracker m_mouseTracker;

		bool m_initialized;

	};
}


