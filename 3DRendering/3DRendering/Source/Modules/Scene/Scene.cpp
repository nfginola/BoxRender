#include "Scene.h"

std::shared_ptr<Model> Scene::createModel(const std::string& fileName, const std::string& meshID)
{

	DirectX::BoundingOrientedBox boundingBox;

	std::shared_ptr<Mesh> mesh = ModelLoader::loadMesh(fileName, meshID, boundingBox);
	m_meshes.push_back(mesh);

	std::shared_ptr<DirectX::BoundingOrientedBox> aabbToPush = std::make_shared<DirectX::BoundingOrientedBox>(boundingBox);
	m_boundingBoxes.push_back(aabbToPush);

	std::shared_ptr<Model> model = std::make_shared<Model>(mesh, aabbToPush);
	m_models.push_back(model);
	return model;
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

const std::vector<std::shared_ptr<DirectX::BoundingOrientedBox>> Scene::getBoundingBoxes()
{
	return m_boundingBoxes;
}
