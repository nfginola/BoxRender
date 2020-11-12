#include "InputEngine.h"

using namespace Input;

Input::InputEngine::InputEngine(HWND& hwnd)
{
	// DXTK Input
	m_kbInput = std::make_shared<DXTKKeyboard>();
	m_mouseInput = std::make_shared<DXTKMouse>(hwnd);
}

Input::InputEngine::~InputEngine()
{
}

void Input::InputEngine::update(float dt)
{
	m_mouseInput->Update();
	m_kbInput->Update();
}

std::shared_ptr<IMouseInput> Input::InputEngine::getMouse()
{
	return m_mouseInput;
}

std::shared_ptr<IKeyboardInput> Input::InputEngine::getKeyboard()
{
	return m_kbInput;
}
