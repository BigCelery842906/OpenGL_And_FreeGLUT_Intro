#pragma once
#include "Structures.h"
#include <fstream>
#include <iostream>


namespace OBJ_Loader
{

    Mesh* Load(char* path);

    void LoadVertex(std::string& line);
    void LoadVertexTexture(std::string& line);
    void LoadVertexNormal(std::string& line);
    void LoadFaceOrder(std::string& line);
	void ApplyDataToMesh(Mesh& objMesh);
};