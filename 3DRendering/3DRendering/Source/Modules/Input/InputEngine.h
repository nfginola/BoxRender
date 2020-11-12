#pragma once
#include <memory>
#include "DXTK/DXTKKeyboard.h"
#include "DXTK/DXTKMouse.h"

namespace Input
{
	class InputEngine
	{
	private:
		std::shared_ptr<IMouseInput> m_mouseInput;
		std::shared_ptr<IKeyboardInput> m_kbInput;

	public:
		InputEngine(HWND& hwnd);
		~InputEngine();

		void update(float dt);
		std::shared_ptr<IMouseInput> getMouse();
		std::shared_ptr<IKeyboardInput> getKeyboard();

	};
}


