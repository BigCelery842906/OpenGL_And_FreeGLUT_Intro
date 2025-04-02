#pragma once
#include <fstream>

#include "Structures.h"

namespace MeshLoader
{
	Mesh* Load(char* path);
	void LoadVertices(std::ifstream& inFile, Mesh& mesh);
	void LoadColours(std::ifstream& inFile, Mesh& mesh);
	void LoadIndices(std::ifstream& inFile, Mesh& mesh);
};

