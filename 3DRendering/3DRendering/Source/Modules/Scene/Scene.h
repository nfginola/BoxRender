#pragma once
#include <vector>
#include <memory>

#include "../Graphics/Components/Camera.h"
#include "../Graphics/Engine/D3D11/Mesh/Mesh.h"
#include "../Graphics/Entities/Player.h"
#include "../Graphics/Entities/Model.h"
#include "../Input/InputEngine.h"


class Scene
{
protected:
	std::vector<std::shared_ptr<Model>> m_models;
	std::vector<std::shared_ptr<Camera>> m_cameras;
	std::vector<std::shared_ptr<Mesh>> m_meshes;
	std::vector<std::shared_ptr<DirectX::BoundingOrientedBox>> m_boundingBoxes;

	std::shared_ptr<Input::InputEngine> m_input;

	// Helper
	std::shared_ptr<Model> createModel(const std::string& fileName, const std::string& meshID);

	// every scene has to call this
	void baseUpdate(float dt);

public:
	Scene(std::shared_ptr<Input::InputEngine> inputEngine);
	virtual ~Scene();

	virtual void update(float dt) = 0;

	const std::vector<std::shared_ptr<Camera>>& getCameras();
	const std::vector<std::shared_ptr<Mesh>>& getMeshes();
	const std::vector<std::shared_ptr<DirectX::BoundingOrientedBox>> getBoundingBoxes();

};

