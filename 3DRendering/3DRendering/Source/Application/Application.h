#pragma once

// Include modules
#include "../Modules/Window/ApplicationWindow.h"
#include "../Modules/Graphics/Engine/GraphicsEngine.h"
#include "../Modules/Input/InputEngine.h"
#include "../Modules/Scene/DefaultScene.h"

class Application
{
private:
	std::unique_ptr<ApplicationWindow> m_appWindow;
	std::unique_ptr<Graphics::GraphicsEngine> m_graphics;
	std::shared_ptr<Input::InputEngine> m_input;

	std::shared_ptr<Scene> m_defaultScene;

public:
	Application(HINSTANCE hInstance);
	~Application();

	void run();

};

