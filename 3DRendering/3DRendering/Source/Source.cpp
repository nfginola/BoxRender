#include <memory>
#include "Modules/Window/Window.h"
#include "Application/Application.h"

// http://manual.gromacs.org/documentation/5.1-current/dev-manual/naming.html

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	std::unique_ptr<Application> gameApp = std::make_unique<Application>(hInstance);

	gameApp->run();

	return 0;
}