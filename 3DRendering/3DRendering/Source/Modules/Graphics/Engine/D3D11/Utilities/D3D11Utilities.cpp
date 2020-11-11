#include "D3D11Utilities.h"

#include <fstream>
#include <iostream>
#include <assert.h>
#include <windows.h>

namespace D3D11Utilities
{
	std::string D3D11Utilities::loadShader(ShaderType type, std::string fileName)
	{
		std::string data;
		std::ifstream fileStream;
		fileStream.open(fileName.c_str(), std::ios_base::binary);

		if (fileStream.fail())
		{
			OutputDebugStringW(L"Failed to read file or can't find file!");
			assert(false);
		}

		// reserve memory once
		fileStream.seekg(0, fileStream.end);
		int length = static_cast<int>(fileStream.tellg());
		data.reserve(length);

		fileStream.seekg(0, fileStream.beg);	// place back at beginning
		// copy binary data to string
		data.assign(std::istreambuf_iterator<char>(fileStream), std::istreambuf_iterator<char>());

		fileStream.close();

		return data;
	}
}

