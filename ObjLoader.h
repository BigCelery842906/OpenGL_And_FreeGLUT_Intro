#pragma once
#include "Structures.h"
#include <fstream>
#include <iostream>


namespace OBJ_Loader
{
    Mesh* Load(char* path);

    void LoadVertex(std::string& line, Mesh& objMesh);
    void LoadVertexTexture(std::string& line, Mesh& objMesh);
    void LoadVertexNormal(std::string& line, Mesh& objMesh);
    void LoadFaceOrder(std::string& line, Mesh& objMesh);
};