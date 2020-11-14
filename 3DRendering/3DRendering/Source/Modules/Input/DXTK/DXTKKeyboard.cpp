#include "DXTKKeyboard.h"

using namespace DirectX;
using namespace Input;

Keyboard::Keys MapStringToKey(const std::string& key)
{
	if (key == "Q") return Keyboard::Keys::Q;
	else if (key == "W") return Keyboard::Keys::W;
	else if (key == "E") return Keyboard::Keys::E;
	else if (key == "R") return Keyboard::Keys::R;
	else if (key == "T") return Keyboard::Keys::T;
	else if (key == "Y") return Keyboard::Keys::Y;
	else if (key == "U") return Keyboard::Keys::U;
	else if (key == "I") return Keyboard::Keys::I;
	else if (key == "O") return Keyboard::Keys::O;
	else if (key == "P") return Keyboard::Keys::P;

	else if (key == "A") return Keyboard::Keys::A;
	else if (key == "S") return Keyboard::Keys::S;
	else if (key == "D") return Keyboard::Keys::D;
	else if (key == "F") return Keyboard::Keys::F;
	else if (key == "G") return Keyboard::Keys::G;
	else if (key == "H") return Keyboard::Keys::H;
	else if (key == "J") return Keyboard::Keys::J;
	else if (key == "K") return Keyboard::Keys::K;
	else if (key == "L") return Keyboard::Keys::L;

	else if (key == "Z") return Keyboard::Keys::Z;
	else if (key == "X") return Keyboard::Keys::X;
	else if (key == "C") return Keyboard::Keys::C;
	else if (key == "V") return Keyboard::Keys::V;
	else if (key == "B") return Keyboard::Keys::B;
	else if (key == "N") return Keyboard::Keys::N;
	else if (key == "M") return Keyboard::Keys::M;

	else if (key == "TAB") return Keyboard::Keys::Tab;

	else if (key == "1") return Keyboard::Keys::D1;
	else if (key == "2") return Keyboard::Keys::D2;
	else if (key == "3") return Keyboard::Keys::D3;
	else if (key == "4") return Keyboard::Keys::D4;
	else if (key == "5") return Keyboard::Keys::D5;
	else if (key == "6") return Keyboard::Keys::D6;
	else if (key == "7") return Keyboard::Keys::D7;
	else if (key == "8") return Keyboard::Keys::D8;
	else if (key == "9") return Keyboard::Keys::D9;

	else if (key == "SPACE") return Keyboard::Keys::Space;

	else return Keyboard::Keys::None;
}

DXTKKeyboard::DXTKKeyboard()
{
	m_keyboard = std::make_unique<Keyboard>();
}

DXTKKeyboard::~DXTKKeyboard()
{
}

bool DXTKKeyboard::isKeyPressed(const std::string& key)
{
	return m_kbStateTracker.IsKeyPressed(MapStringToKey(key));
}

bool DXTKKeyboard::isKeyDown(const std::string& key)
{
	return m_kbState.IsKeyDown(MapStringToKey(key));
}

void DXTKKeyboard::windowProcedureHook(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	DirectX::Keyboard::ProcessMessage(uMsg, wParam, lParam);
}

void DXTKKeyboard::update()
{
	updateState();
}

void DXTKKeyboard::updateState()
{
	m_kbState = m_keyboard->GetState();
	m_kbStateTracker.Update(m_kbState);
}
