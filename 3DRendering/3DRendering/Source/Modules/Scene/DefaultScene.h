#pragma once
#include "Scene.h"


class DefaultScene : public Scene
{
private:
	std::shared_ptr<Player> m_player;

public:
	DefaultScene(std::shared_ptr<Player> player, std::shared_ptr<Input::InputEngine> inputEngine);
	~DefaultScene();

	void update(float dt) override;
};

