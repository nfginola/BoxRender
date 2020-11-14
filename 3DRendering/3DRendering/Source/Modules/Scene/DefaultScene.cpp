#include "DefaultScene.h"

using namespace DirectX::SimpleMath;

DefaultScene::DefaultScene(std::shared_ptr<Player> player, std::shared_ptr<Input::InputEngine> inputEngine) :
	Scene::Scene(inputEngine),
	m_player(player)
{
	m_cameras.push_back(m_player->getCamera());

	// Init scene
	m_models.push_back(Scene::createModel("Models\\nanosuit\\nanosuit.obj", "testModel"));
	m_models[0]->setPosition(Vector3(0.f, 0.f, 0.f));
	m_models[0]->setScale(0.7f);

	m_models.push_back(Scene::createModel("Models\\Sponza\\Sponza.fbx", "sponza"));
	m_models[1]->setScale(0.03f);

}

DefaultScene::~DefaultScene()
{

}

void DefaultScene::update(float dt)
{
	Scene::baseUpdate(dt);

	m_player->update(dt);
	for (const auto& model : m_models)
	{
		model->update(dt);
	}

}
