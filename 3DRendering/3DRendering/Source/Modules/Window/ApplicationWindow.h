#pragma once
#include "Window.h"
#include "../Input/InputEngine.h"

// Specific for this application (e.g custom GUI, resize, etc.)
class ApplicationWindow : public Window
{
private:
	std::shared_ptr<Input::InputEngine> m_inputEngine;

public:
	ApplicationWindow(HINSTANCE hInstance,
		const wchar_t* name = L"Default Window",
		UINT clientWidth = 1280,
		UINT clientHeight = 720
	);

	~ApplicationWindow();

	virtual LRESULT handleProc(const UINT& uMsg, const WPARAM& wParam, const LPARAM& lParam) override;
	void hookInput(std::shared_ptr<Input::InputEngine> inputEngine);


	

};

