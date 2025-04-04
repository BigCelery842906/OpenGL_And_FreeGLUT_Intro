#pragma once
#include <fstream>
#include <Windows.h>
#include "Structures.h"

namespace MeshLoader
{
	Mesh* Load(char* path);
	void LoadTexCoords(std::ifstream& inFile, Mesh& mesh);
	void LoadVertices(std::ifstream& inFile, Mesh& mesh);
	void LoadColours(std::ifstream& inFile, Mesh& mesh);
	void LoadIndices(std::ifstream& inFile, Mesh& mesh);
};

