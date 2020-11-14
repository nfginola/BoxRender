#pragma once

#include <vector>
#include <string>
#include <DirectXTK/SimpleMath.h>


namespace ModelLoader
{
	class IModelLoader
	{
	public:

		// Make sure to fit this with the format of a Vertex in the Engine!
		struct Position { float x, y, z; };
		struct Normal { float x, y, z; };
		struct TexCoord { float u, v; };

		struct Vertex
		{
			Position m_position;
			Normal m_normal;
			TexCoord m_texCoord;
		};


		/*
		Example of expected data:

		Vertices:
		{
			V0, V1, V2,
			V3, V4, V5.
			V6, V7, V8
		}

		Indices:
		{
			0, 1, 2,
			0, 1, 2,
			0, 1, 2
		}

		Subsets: 3

		subset1 vstart = 0, vcount = 3
		subset2 vstart = 3, vcount = 3
		subset3 vstart = 6, vcount = 3

		subset1 istart = 0, icount = 3
		subset2 istart = 3, icount = 3
		subset3 istart = 6, icount = 3

		*/


		// To-add: Material
		struct EngineMeshSubset
		{
			unsigned int m_vertexCount;
			unsigned int m_vertexStart;

			unsigned int m_indexStart;
			unsigned int m_indexCount;

			std::string m_diffuseFilePath;
			std::string m_specularFilePath;
			std::string m_normalFilePath;
		};

		struct EngineMeshData
		{
			std::vector<Vertex> m_vertices;
			std::vector<unsigned int> m_indices;			// 32 bit!
			std::vector<EngineMeshSubset> m_subsetsInfo;
		};


	public:
		IModelLoader() { };
		virtual ~IModelLoader() { };

		virtual EngineMeshData loadStaticModel(std::string filePath) = 0;
	};


}
