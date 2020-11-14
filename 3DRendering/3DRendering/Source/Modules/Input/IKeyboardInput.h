#pragma once
#include <Windows.h>

#include <string>

class Window;
class ApplicationWindow;

namespace Input
{
	class IKeyboardInput
	{
	public:
		IKeyboardInput() { };
		virtual ~IKeyboardInput() { };

		IKeyboardInput(const IKeyboardInput& rhs) = delete;

		virtual bool isKeyPressed(const std::string& key) = 0;
		virtual bool isKeyDown(const std::string& key) = 0;
		virtual void update() = 0;

	private:
		friend Window;
		friend ApplicationWindow;

		virtual void windowProcedureHook(UINT message, WPARAM wParam, LPARAM lParam) = 0;





	};
}


