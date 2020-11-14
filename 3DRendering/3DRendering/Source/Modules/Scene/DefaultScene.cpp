#include "DefaultScene.h"

using namespace DirectX::SimpleMath;

DefaultScene::DefaultScene(std::shared_ptr<Player> player, std::shared_ptr<Input::InputEngine> inputEngine) :
	Scene::Scene(inputEngine),
	m_player(player)
{
	m_cameras.push_back(m_player->getCamera());

	// Init scene
	std::shared_ptr<Model> nanosuit = Scene::createModel("Models\\nanosuit\\nanosuit.obj", "testModel");
	std::shared_ptr<Model> nanosuit2 = Scene::createModel("Models\\nanosuit\\nanosuit.obj", "testModel");
	std::shared_ptr<Model> sponza = Scene::createModel("Models\\Sponza\\Sponza.fbx", "sponza");

	nanosuit->setPosition(Vector3(5.f, 0.f, 0.f));
	//nanosuit->setRotation(Vector3(0.f, M_PI / 2.f, 0.f));

	nanosuit2->setScale(0.3f);

	nanosuit->setScale(0.3f);

	sponza->setScale(0.03f);

}

DefaultScene::~DefaultScene()
{

}

void DefaultScene::update(float dt)
{
	Scene::baseUpdate(dt);

	if (m_input->getKeyboard()->isKeyPressed("H"))
	{
		m_models[0]->getMesh()->setRenderMode(false);
	}
	else if (m_input->getKeyboard()->isKeyPressed("G"))
	{
		m_models[0]->getMesh()->setRenderMode(true);

	}

	if (m_input->getKeyboard()->isKeyPressed("X"))
	{
		m_models[1]->setPosition(m_models[1]->getPosition() + Vector3(0.5f, 0.f, 0.f));
	}

	std::wstring x = std::to_wstring(m_models[1]->getAABB().Center.x + m_models[1]->getAABB().Extents.x);
	std::wstring y = std::to_wstring(m_models[1]->getAABB().Center.y + m_models[1]->getAABB().Extents.y);
	std::wstring z = std::to_wstring(m_models[1]->getAABB().Center.z + m_models[1]->getAABB().Extents.z);
	std::wstring info = L"x: " + x + L" | y: " + y + L" | z: " + z + L"\n";
	OutputDebugStringW(info.c_str());

	if (m_models[0]->getAABB().Intersects(m_models[1]->getAABB()))
	{
		m_models[0]->getMesh()->setRenderMode(false);
		OutputDebugStringW(L"Collided!\n");
	}

	m_player->update(dt);
	for (const auto& model : m_models)
	{
		model->update(dt);
	}

}
