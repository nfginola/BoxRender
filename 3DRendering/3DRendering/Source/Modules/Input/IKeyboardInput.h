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

		virtual bool IsKeyPressed(const std::string& key) = 0;
		virtual bool IsKeyDown(const std::string& key) = 0;
		virtual void Update() = 0;

	private:
		friend Window;
		friend ApplicationWindow;

		virtual void WindowProcedureHook(UINT message, WPARAM wParam, LPARAM lParam) = 0;





	};
}


