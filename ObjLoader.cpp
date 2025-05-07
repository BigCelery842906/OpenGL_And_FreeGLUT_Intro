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
        Vertex tempVertex;
        sscanf_s(line.c_str(), "%f %f %f", &tempVertex.x, &tempVertex.y, &tempVertex.z);
        objMesh.Vertices.push_back(tempVertex);
        objMesh.vertexCount++;
        
        std::cout << "Loaded Vertex" << std::endl;
    }

    void LoadVertexTexture(std::string& line, Mesh& objMesh)
    {
        std::cout << "Loading Vertex Texture" << std::endl;
        TexCoord tempVertexTexture;
        sscanf_s(line.c_str(), "%f %f", &tempVertexTexture.u, &tempVertexTexture.v);
        objMesh.TexCoords.push_back(tempVertexTexture);
        objMesh.TexCoordCount++;
        std::cout << "Loaded Vertex Texture" << std::endl;
    }

    void LoadVertexNormal(std::string& line, Mesh& objMesh)
    {
        std::cout << "Loading Vertex Normal" << std::endl;
        Vector3 tempVertexNormal;
        sscanf_s(line.c_str(), "%f %f %f", &tempVertexNormal.x, &tempVertexNormal.y, &tempVertexNormal.z);
        objMesh.Normals.push_back(tempVertexNormal);
        objMesh.normalCount++;
        std::cout << "Loaded Vertex Normal" << std::endl;
    }

    void LoadFaceOrder(std::string& line, Mesh& objMesh)
    {
        std::cout << "Loading Face" << std::endl;
        int tempFaces[9];
        sscanf_s(line.c_str(), "%d/%d/%d %d/%d/%d %d/%d/%d", &tempFaces[0], &tempFaces[1], &tempFaces[2], &tempFaces[3], &tempFaces[4], &tempFaces[5], &tempFaces[6], &tempFaces[7], &tempFaces[8]);
        for (int i = 0; i < 9; i++)
        {
            objMesh.Indices.push_back(tempFaces[i]);
        }
        objMesh.indexCount += 9;
        std::cout << "Loaded Face" << std::endl;
    }
};
