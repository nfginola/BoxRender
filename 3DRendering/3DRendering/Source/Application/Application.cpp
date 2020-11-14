#include "Application.h"


using namespace Graphics;
using namespace Input;

Application::Application(HINSTANCE hInstance)
{
	// input and window are closely tied
	m_appWindow = std::make_unique<ApplicationWindow>(hInstance, L"Nad's Window", 1280, 720);
	m_input = std::make_unique<InputEngine>(m_appWindow->getHWND());
	m_appWindow->hookInput(m_input);
	
	m_graphics = std::make_unique<GraphicsEngine>(m_appWindow->getHWND(), m_appWindow->getClientWidth(), m_appWindow->getClientHeight());

	// Create a scene with player
	std::shared_ptr<Camera> playerCamera = std::make_shared<Camera>(80.f, m_appWindow->getAspectRatio(), 0.1f, 150.f);
	std::shared_ptr<Player> player = std::make_shared<Player>(playerCamera, nullptr, m_input);
	m_defaultScene = std::make_shared<DefaultScene>(player, m_input);
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
		m_input->update(0.f);

		// Update objects
		m_defaultScene->update(0.0005f);
		
		// Update graphics
		m_graphics->setScene(m_defaultScene);
		m_graphics->render(0.0005f);

	}


}
