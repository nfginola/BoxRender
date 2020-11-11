#include "Application.h"

using namespace Graphics;

Application::Application(HINSTANCE hInstance)
{
	m_appWindow = std::make_unique<ApplicationWindow>(hInstance, L"Nad's Window", 1024, 576);
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

		// Update input
		// Update objects
		// Update graphics
		// ..
		m_graphics->render(0.f);

	}


}
