#include "ObjLoader.h"

#include <string>

//#include "MeshLoader.h"


namespace OBJ_Loader
{

    Mesh* Load(char* path)
    {
        Mesh* objMesh = new Mesh();
        std::ifstream objInFile;

        std::string objInTemp;
        std::string lineType;

        objInFile.open(path);

        if (!objInFile.good())
        {
            std::cerr << "Error opening OBJ file: " << path << std::endl;
            return nullptr;
        }

        //LOAD THINGS
        while (objInFile >> objInTemp)
        {
            lineType = objInTemp;
            std::getline(objInFile, objInTemp);
            //lineType = objInTemp.substr(0, 2);

            if (lineType == "v")
            {
                //LOAD VERTEX
                LoadVertex(objInTemp, *objMesh);
            }
            else if (lineType == "vt")
            {
                //LOAD VERTEX 
                LoadVertexTexture(objInTemp, *objMesh);
            }
            else if (lineType == "vn")
            {
                //LOAD VERTEX NORMAL
                LoadVertexNormal(objInTemp, *objMesh);
            }
            else if (lineType == "f")
            {
                //LOAD FACE
                LoadFaceOrder(objInTemp, *objMesh);
            }
            else
            {
                std::cout << "Nothing Useful on Line" << std::endl;
            }
        }

        std::cout << "End of File" << std::endl;


        objInFile.close();
        return objMesh;
    }

    void LoadVertex(std::string& line, Mesh& objMesh)
    {
        std::cout << "Loading Vertex" << std::endl;
        scanf_s(line.c_str(), "%f %f %f", objMesh.Vertices[objMesh.vertexCount].x, objMesh.Vertices[objMesh.vertexCount].y, objMesh.Vertices[objMesh.vertexCount].z);
        objMesh.vertexCount++;
        std::cout << "Loaded Vertex" << std::endl;
    }

    void LoadVertexTexture(std::string& line, Mesh& objMesh)
    {
        std::cout << "Loading Vertex Texture" << std::endl;
        scanf_s(line.c_str(), "%f %f", objMesh.TexCoords[objMesh.TexCoordCount].u, objMesh.TexCoords[objMesh.TexCoordCount].v);
        objMesh.TexCoordCount++;
        std::cout << "Loaded Vertex Texture" << std::endl;
    }

    void LoadVertexNormal(std::string& line, Mesh& objMesh)
    {
        std::cout << "Loading Vertex Normal" << std::endl;
        scanf_s(line.c_str(), "%f %f %f", objMesh.Normals[objMesh.normalCount].x, objMesh.Normals[objMesh.normalCount].y, objMesh.Normals[objMesh.normalCount].z);
        objMesh.normalCount++;
        std::cout << "Loaded Vertex Normal" << std::endl;
    }

    void LoadFaceOrder(std::string& line, Mesh& objMesh)
    {
        std::cout << "Loading Face" << std::endl;
        sscanf_s(line.c_str(), "%d/%d/%d %d/%d/%d %d/%d/%d", objMesh.Indices[objMesh.indexCount], objMesh.Indices[objMesh.indexCount+1], objMesh.Indices[objMesh.indexCount+2], objMesh.Indices[objMesh.indexCount+3], objMesh.Indices[objMesh.indexCount+4], objMesh.Indices[objMesh.indexCount+5], objMesh.Indices[objMesh.indexCount+6], objMesh.Indices[objMesh.indexCount+7], objMesh.Indices[objMesh.indexCount+8] );
        objMesh.indexCount += 9;
        std::cout << "Loaded Face" << std::endl;
    }
};
