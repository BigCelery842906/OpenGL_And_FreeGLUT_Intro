#include "ObjLoader.h"

#include <string>

//#include "MeshLoader.h"


namespace OBJ_Loader
{
    std::vector<Vertex> VerticesVector;
    std::vector<Vector3> NormalsVector;
    std::vector<TexCoord> TexCoordsVector;
    std::vector<GLushort> IndicesVector;
    int vertexCount, normalCount, TexCoordCount, indexCount;
    std::vector<int> normalIndicesVector, texCoordIndicesVector;


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
                LoadVertex(objInTemp);
            }
            else if (lineType == "vt")
            {
                //LOAD VERTEX TEXTURE
                LoadVertexTexture(objInTemp);
            }
            else if (lineType == "vn")
            {
                //LOAD VERTEX 
                LoadVertexNormal(objInTemp);
            }
            else if (lineType == "f")
            {
                //LOAD FACE
                LoadFaceOrder(objInTemp);
            }
            else
            {
                //std::cout << "Nothing Useful on Line" << std::endl;
            }
        }

        std::cout << "End of File" << std::endl;

        ApplyDataToMesh(*objMesh);

        std::cout << "Loaded " << objMesh->vertexCount << " vertices." << std::endl;
        std::cout << "Loaded " << objMesh->normalCount << " normals." << std::endl;
        std::cout << "Loaded " << objMesh->TexCoordCount << " TexCoords." << std::endl;
        std::cout << "Loaded " << objMesh->indexCount << " indices." << std::endl;


        objInFile.close();
        return objMesh;
    }

    void LoadVertex(std::string& line)
    {
        //std::cout << "Loading Vertex" << std::endl;
        Vertex tempVertex;
        sscanf_s(line.c_str(), "%f %f %f", &tempVertex.x, &tempVertex.y, &tempVertex.z);
        VerticesVector.push_back(tempVertex);
        vertexCount++;

        //std::cout << "Loaded Vertex" << std::endl;
    }

    void LoadVertexTexture(std::string& line)
    {
        //std::cout << "Loading Vertex Texture" << std::endl;
        TexCoord tempVertexTexture;
        sscanf_s(line.c_str(), "%f %f", &tempVertexTexture.u, &tempVertexTexture.v);
        TexCoordsVector.push_back(tempVertexTexture);
        TexCoordCount++;
        //std::cout << "Loaded Vertex Texture" << std::endl;
    }

    void LoadVertexNormal(std::string& line)
    {
        // std::cout << "Loading Vertex Normal" << std::endl;
        Vector3 tempVertexNormal;
        sscanf_s(line.c_str(), "%f %f %f", &tempVertexNormal.x, &tempVertexNormal.y, &tempVertexNormal.z);
        NormalsVector.push_back(tempVertexNormal);
        normalCount++;
        //std::cout << "Loaded Vertex Normal" << std::endl;
    }

    void LoadFaceOrder(std::string& line)
    {
        // std::cout << "Loading Face" << std::endl;
        unsigned int tempIndicesOrder[3];
        unsigned int tempTexCoordsOrder[3];
        unsigned int tempNormalOrder[3];
        sscanf_s(line.c_str(), "%d/%d/%d %d/%d/%d %d/%d/%d", &tempIndicesOrder[0], &tempTexCoordsOrder[0], &tempNormalOrder[0], &tempIndicesOrder[1], &tempTexCoordsOrder[1], &tempNormalOrder[1], &tempIndicesOrder[2], &tempTexCoordsOrder[2], &tempNormalOrder[2]);

        //Vertex, Texture, Normal
        for (int i = 0; i < 3; i++)
        {
            IndicesVector.push_back(tempIndicesOrder[i]);
            texCoordIndicesVector.push_back(tempTexCoordsOrder[i]);
            normalIndicesVector.push_back(tempNormalOrder[i]);
        }
        indexCount += 3;
        //std::cout << "Loaded Face" << std::endl;
    }
    
    void ApplyDataToMesh(Mesh& objMesh)
    {
        int numVertices = IndicesVector.size();
        objMesh.vertexCount = numVertices;
        objMesh.normalCount = numVertices;
        objMesh.TexCoordCount = numVertices;
        objMesh.indexCount = numVertices;

        objMesh.Vertices = new Vertex[numVertices];
        objMesh.Normals = new Vector3[numVertices];
        objMesh.TexCoords = new TexCoord[numVertices];
        objMesh.Indices = new GLushort[numVertices];

        for (int i = 0; i < numVertices; ++i)
        {
            // Vertex position
            int vIdx = IndicesVector[i] - 1;
            objMesh.Vertices[i] = VerticesVector[vIdx];

            // Texture coordinate
            int vtIdx = texCoordIndicesVector[i] - 1;
            objMesh.TexCoords[i] = TexCoordsVector[vtIdx];

            // Normal
            int vnIdx = normalIndicesVector[i] - 1;
            objMesh.Normals[i] = NormalsVector[vnIdx];
            
            objMesh.Indices[i] = i; //Set the index to be the current iteration, aka the first position is 0, 2nd is 1 etc etc.
        }
    }
}
