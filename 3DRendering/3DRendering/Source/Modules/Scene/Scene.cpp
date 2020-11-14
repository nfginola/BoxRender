#include "Scene.h"

std::shared_ptr<Model> Scene::createModel(const std::string& fileName, const std::string& meshID)
{
	std::shared_ptr<Mesh> mesh = ModelLoader::loadMesh(fileName, meshID);
	m_meshes.push_back(mesh);
	return std::make_shared<Model>(mesh);
}

void Scene::baseUpdate(float dt)
{
	const std::shared_ptr<Input::IKeyboardInput>& kb = m_input->getKeyboard();
	const std::shared_ptr<Input::IMouseInput>& mouse = m_input->getMouse();

	if (kb->isKeyPressed("O"))
	{
		mouse->hideMouse();
	}
	else if (kb->isKeyPressed("P"))
	{
		mouse->showMouse();
	}

}

Scene::Scene(std::shared_ptr<Input::InputEngine> inputEngine) :
	m_input(inputEngine)
{
}

Scene::~Scene()
{
}

void Scene::update(float dt)
{
}

// [0] always player camera
const std::vector<std::shared_ptr<Camera>>& Scene::getCameras()
{
	return m_cameras;
}

const std::vector<std::shared_ptr<Mesh>>& Scene::getMeshes()
{
	return m_meshes;
}
