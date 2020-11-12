#include "Application.h"


using namespace Graphics;
using namespace Input;

Application::Application(HINSTANCE hInstance)
{
	// input and window closely tied
	m_appWindow = std::make_unique<ApplicationWindow>(hInstance, L"Nad's Window", 1024, 576);
	m_input = std::make_unique<InputEngine>(m_appWindow->getHWND());
	m_appWindow->hookInput(m_input);
	
	m_graphics = std::make_unique<GraphicsEngine>(m_appWindow->getHWND(), m_appWindow->getClientWidth(), m_appWindow->getClientHeight());

}

Application::~Application()
{
}

void Application::run()
{
	MSG msg = { };
	while (!m_appWindow->isClosed())
	{	
		while (PeekMessageW(&msg, m_appWindow->getHWND(), 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// test -- to do: Change naming convention for input
		if (m_input->getMouse()->LMBDown())
		{
			if (m_input->getKeyboard()->IsKeyPressed("W")) OutputDebugStringW(std::wstring(std::wstring(L"Absolute X: ") + std::to_wstring(m_input->getMouse()->GetScreenCoordX()).c_str() + std::wstring(L"\n")).c_str());
			if (m_input->getKeyboard()->IsKeyPressed("A")) OutputDebugStringW(std::wstring(std::wstring(L"Absolute Y: ") + std::to_wstring(m_input->getMouse()->GetScreenCoordY()).c_str() + std::wstring(L"\n")).c_str());
			if (m_input->getKeyboard()->IsKeyPressed("S")) OutputDebugStringW(std::wstring(std::wstring(L"Relative X: ") + std::to_wstring(m_input->getMouse()->GetDeltaX()).c_str() + std::wstring(L"\n")).c_str());
			if (m_input->getKeyboard()->IsKeyPressed("D")) OutputDebugStringW(std::wstring(std::wstring(L"Relative Y: ") + std::to_wstring(m_input->getMouse()->GetDeltaY()).c_str() + std::wstring(L"\n")).c_str());
		}

		// Update input
		m_input->update(0.f);

		// Update objects

		// Update graphics
		m_graphics->render(0.f);

	}


}
