#pragma once

#ifndef UNICODE
#define UNICODE
#endif

#include <Windows.h>
#include <assert.h>
#include <memory>

class Window
{
protected:
	friend LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	virtual LRESULT handleProc(const UINT& uMsg, const WPARAM& wParam, const LPARAM& lParam) = 0;
	void registerAndCreateWindow(HINSTANCE hInstance);
	void resizeToFitDesiredClientDimensions();

	void startup();

protected:
	HINSTANCE m_hInstance;
	HWND m_hwnd;
	UINT m_clientWidth, m_clientHeight;
	DWORD m_style, m_exStyle;
	const wchar_t* m_windowName;
	bool m_isClosed;

public:
	Window(HINSTANCE hInstance, 
			const wchar_t* name = L"Default Window", 
			UINT clientWidth = 1280,
			UINT clientHeight = 720
	);

	~Window();
	Window(const Window& rhs) = delete;

public:
	bool isClosed();
	HWND& getHWND();

	float getAspectRatio();
	UINT getClientWidth();
	UINT getClientHeight();

};

