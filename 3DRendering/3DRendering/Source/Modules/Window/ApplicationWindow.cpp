#include "ApplicationWindow.h"

ApplicationWindow::ApplicationWindow(HINSTANCE hInstance, const wchar_t* name, UINT clientWidth, UINT clientHeight) :
	Window::Window(hInstance, name, clientWidth, clientHeight)
{
	startup();
}

ApplicationWindow::~ApplicationWindow()
{

}

LRESULT ApplicationWindow::handleProc(const UINT& uMsg, const WPARAM& wParam, const LPARAM& lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		m_isClosed = true;
		return 0;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(m_hwnd, &ps);

		FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

		EndPaint(m_hwnd, &ps);
		break;
	}

	case WM_ACTIVATEAPP:
		//m_kbInput->WindowProcedureHook(uMsg, wParam, lParam);
		//m_mouseInput->WindowProcedureHook(uMsg, wParam, lParam);
		break;

	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
	case WM_KEYUP:
	case WM_SYSKEYUP:
		//m_kbInput->WindowProcedureHook(uMsg, wParam, lParam);
		break;

	case WM_INPUT:
	case WM_MOUSEMOVE:
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
	case WM_MOUSEWHEEL:
	case WM_XBUTTONDOWN:
	case WM_XBUTTONUP:
	case WM_MOUSEHOVER:
		//m_mouseInput->WindowProcedureHook(uMsg, wParam, lParam);
		break;
	
	}
	return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
}
