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
		for (int x = 0; x < 4; ++x)
		{
			std::shared_ptr<Model> nano = Scene::createModel("Models\\nanosuit\\nanosuit.obj", "testModel");
			nano->setPosition(Vector3(i * 5.f - 20.f, 0.f, 10 + x * 10.f));
			nano->setScale(0.3f);
			nano->setBoundingBoxOffsets(Vector3(0.f, 2.3f, 0.f));

			if (x == 0)
			{
				nano->setRotation(Vector3((float)i / 4.f, 0.f, 0.f));

			}
			else if (x == 1)
			{
				nano->setRotation(Vector3(0.f, (float)i / 4.f, 0.f));
			}
			else if (x == 2)
			{
				nano->setRotation(Vector3(0.f, 0.f, (float)i / 4.f));

			}
			else
			{
				nano->setRotation(Vector3((float)i / 4.f, (float)i / 4.f, (float)i / 4.f));

			}

		}
	}


	// Offset the bounding box if needed
	nanosuit->setBoundingBoxOffsets(Vector3(0.f, 2.3f, 0.f));
	nanosuit2->setBoundingBoxOffsets(Vector3(0.f, 2.3f, 0.f));
	stall->setBoundingBoxOffsets(Vector3(0.f, 2.55f, 0.f));

	stall->setPosition(Vector3(0.f, 0.f, -10.f));

	nanosuit->setPosition(Vector3(5.f, 3.f, -0.1f));
	nanosuit->setRotation(Vector3(M_PI / 4.f, M_PI / 4.f, M_PI / 4.f));
	nanosuit2->setPosition(Vector3(1.f, 0.f, 0.f));

	nanosuit2->setScale(0.3f);

	nanosuit->setScale(0.3f);

	//sponza->setScale(0.03f);
	//sponza->setPosition(Vector3(0.f, 0.f, 4.f));

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

	if (m_models[0]->getBoundingBox()->Intersects(*m_models[1]->getBoundingBox().get()))
	{
		m_models[0]->getMesh()->setRenderMode(false);
		OutputDebugStringW(L"Collided!\n");
	}

	m_player->update(0.0015);
	for (const auto& model : m_models)
	{
		model->update(dt);
	}

}
