#pragma once
#include "Window.h"

// Specific for this application (e.g custom GUI, resize, etc.)
class ApplicationWindow : public Window
{
private:

public:
	ApplicationWindow(HINSTANCE hInstance,
		const wchar_t* name = L"Default Window",
		UINT clientWidth = 1280,
		UINT clientHeight = 720
	);

	~ApplicationWindow();

	virtual LRESULT handleProc(const UINT& uMsg, const WPARAM& wParam, const LPARAM& lParam) override;


	

};

