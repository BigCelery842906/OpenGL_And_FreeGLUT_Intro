#pragma once
#include "Structures.h"
#include <fstream>
#include <iostream>


namespace OBJ_Loader
{
    OBJMesh* Load(char* path);

    void LoadVertex(std::string& line, OBJMesh& objMesh);
    void LoadVertexTexture(std::string& line, OBJMesh& objMesh);
    void LoadVertexNormal(std::string& line, OBJMesh& objMesh);
    void LoadFaceOrder(std::string& line, OBJMesh& objMesh);
};