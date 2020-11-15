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
	std::shared_ptr<Model> stall = Scene::createModel("Models\\Stall\\stall.obj", "stall");
	//std::shared_ptr<Model> sponza = Scene::createModel("Models\\Sponza\\Sponza.fbx", "sponza");

	for (int i = 0; i < 10; ++i)
	{
		std::shared_ptr<Model> nano = Scene::createModel("Models\\nanosuit\\nanosuit.obj", "testModel");
		nano->setPosition(Vector3(i * 5.f, 0.f, 10.f));
		nano->setScale(0.3f);
		nano->setBoundingBoxOffsets(Vector3(0.f, 2.3f, 0.f));
	}

	// Offset the bounding box if needed
	nanosuit->setBoundingBoxOffsets(Vector3(0.f, 2.3f, 0.f));
	nanosuit2->setBoundingBoxOffsets(Vector3(0.f, 2.3f, 0.f));
	stall->setBoundingBoxOffsets(Vector3(0.f, 2.55f, 1.22f));

	stall->setPosition(Vector3(0.f, 0.f, 30.f));
	stall->setRotation(Vector3(0.f, M_PI, 0.f));

	nanosuit->setPosition(Vector3(5.f, 0.f, -0.1f));
	nanosuit->setRotation(Vector3(0.f, M_PI / 4.f, 0.f));
	nanosuit2->setPosition(Vector3(1.f, 0.f, 0.f));

	nanosuit2->setScale(0.3f);

	nanosuit->setScale(0.3f);

	//sponza->setScale(0.03f);

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
		m_models[1]->setPosition(m_models[1]->getPosition() + Vector3(0.1f, 0.f, 0.f));
	}

	std::wstring x = std::to_wstring(m_models[1]->getBoundingBox()->Center.x + m_models[1]->getBoundingBox()->Extents.x);
	std::wstring y = std::to_wstring(m_models[1]->getBoundingBox()->Center.y + m_models[1]->getBoundingBox()->Extents.y);
	std::wstring z = std::to_wstring(m_models[1]->getBoundingBox()->Center.z + m_models[1]->getBoundingBox()->Extents.z);
	std::wstring info = L"x: " + x + L" | y: " + y + L" | z: " + z + L"\n";
	OutputDebugStringW(info.c_str());

	if (m_models[0]->getBoundingBox()->Intersects(*m_models[1]->getBoundingBox().get()))
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
