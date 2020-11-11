#pragma once

// Include modules
#include "../Modules/Window/ApplicationWindow.h"
#include "../Modules/Graphics/Engine/GraphicsEngine.h"

class Application
{
private:
	std::unique_ptr<ApplicationWindow> m_appWindow;
	std::unique_ptr<Graphics::GraphicsEngine> m_graphics;

public:
	Application(HINSTANCE hInstance);
	~Application();

	void run();

};

