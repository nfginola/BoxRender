#include "Window.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	// WindowProc needs to be a static function for class initialization! (We pass function ptr)
	// But remember that we want our action handling to happen in functions of classes (non static members)

	// Since a window has a few bytes that we can use to store data in (LongPtr) then we can use this to
	// store the ptr to the active window object of ours on class creation! (non-static)
	Window* currWin;
	if (uMsg == WM_CREATE)
	{
		// Once window is created we make sure to store the active window class in the
		// window's user data storage!
		CREATESTRUCT* pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
		Window* currWin = reinterpret_cast<Window*>(pCreate->lpCreateParams);
		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)currWin);

		return currWin->handleProc(uMsg, wParam, lParam);		// Handle WM_CREATE in Application too!
	}
	else
	{
		currWin = reinterpret_cast<Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
	}

	if (currWin == nullptr)
	{
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}


	return currWin->handleProc(uMsg, wParam, lParam);


}

Window::Window(HINSTANCE hInstance, const wchar_t* name, UINT clientWidth, UINT clientHeight) :
	m_style(WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX),
	m_exStyle(0),
	m_hwnd(NULL),
	m_hInstance(hInstance),
	m_windowName(name),
	m_clientWidth(clientWidth),
	m_clientHeight(clientHeight),
	m_isClosed(false)
{
	// Input associated with window
	//m_kbInput = std::make_shared<DXTKKeyboard>();
	//m_mouseInput = std::make_shared<DXTKMouse>(m_hwnd);

}

Window::~Window()
{
}

bool Window::isClosed()
{
	return m_isClosed;
}

HWND Window::getHWND()
{
	return m_hwnd;
}

//std::shared_ptr<IKeyboardInput> Window::getKeyboard()
//{
//	return m_kbInput;
//}
//
//std::shared_ptr<IMouseInput> Window::getMouse()
//{
//	return m_mouseInput;
//}

float Window::getAspectRatio()
{
	return (float)(m_clientWidth) / (float)(m_clientHeight);
}

UINT Window::getClientWidth()
{
	return m_clientWidth;
}

UINT Window::getClientHeight()
{
	return m_clientHeight;
}

LRESULT Window::handleProc(const UINT& uMsg, const WPARAM& wParam, const LPARAM& lParam)
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

void Window::registerAndCreateWindow(HINSTANCE hInstance)
{
	WNDCLASS wc = { 0 };
	wc.lpfnWndProc = WindowProc;							// reference to the procedure to be called for this window
	wc.hInstance = hInstance;								// instance handle
	wc.lpszClassName = m_windowName;				// class name (identifier)

	RegisterClass(&wc);

	m_hwnd = CreateWindowEx(
		0,						// Default behaviour (optionals)
		m_windowName,	// Class name (identifier)
		m_windowName,	// Window title 
		m_style,				// Window style 
		CW_USEDEFAULT,			// Window x-pos
		CW_USEDEFAULT,			// Window y-pos 
		CW_USEDEFAULT,			// Default width
		CW_USEDEFAULT,			// Default height
		NULL,					// Parent window (we are top level window)
		NULL,					// Menu
		hInstance,
		(LPVOID)this			// Passing this pointer so that we can use member function procedure handling
	);


	if (m_hwnd == NULL)
	{
		assert(false);
	}
}

void Window::resizeToFitDesiredClientDimensions()
{
	RECT rect = { 0 };
	rect.right = m_clientWidth;
	rect.bottom = m_clientHeight;

	// We pass a rect that has our desired client area and receive corrected window rect
	if (!AdjustWindowRectEx(&rect, m_style, 0, m_exStyle)) assert(false);

	// cx, cy are width and height!
	if (!SetWindowPos(m_hwnd, HWND_TOP, 100, 100, rect.right - rect.left, rect.bottom - rect.top, SWP_NOREPOSITION)) assert(false);

}

void Window::startup()
{
	registerAndCreateWindow(m_hInstance);
	resizeToFitDesiredClientDimensions();
	ShowWindow(m_hwnd, SW_SHOWDEFAULT);
}
