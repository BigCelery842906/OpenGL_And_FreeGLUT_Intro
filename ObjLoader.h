#pragma once
#include "Structures.h"
#include <fstream>
#include <iostream>


namespace OBJ_Loader
{
    OBJMesh* Load(char* path);
    void LoadVertices(std::ifstream& objInFile, OBJMesh& objMesh);
    void LoadVertexNormals(std::ifstream& objInFile, OBJMesh& objMesh);
    void LoadVertexTextures(std::ifstream& objInFile, OBJMesh& objMesh);
    void LoadFaceOrder(std::ifstream& objInFile, OBJMesh& objMesh);
};