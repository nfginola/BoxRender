#pragma once
#include "../IKeyboardInput.h"

#include <memory>
#include <string>

#include <DirectXTK/Keyboard.h>

namespace Input
{
	class DXTKKeyboard : public IKeyboardInput
	{
	public:
		DXTKKeyboard();
		~DXTKKeyboard();

		bool IsKeyPressed(const std::string& key) override;
		bool IsKeyDown(const std::string& key) override;
		void Update() override;

	private:
		void WindowProcedureHook(UINT uMsg, WPARAM wParam, LPARAM lParam) override;

		std::shared_ptr<DirectX::Keyboard> m_keyboard;
		DirectX::Keyboard::State m_kbState;
		DirectX::Keyboard::KeyboardStateTracker m_kbStateTracker;

		void UpdateState();


	};
}


