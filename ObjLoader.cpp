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
        TexCoordCount += 1;
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
        unsigned int tempFaces[9];
        sscanf_s(line.c_str(), "%d/%d/%d %d/%d/%d %d/%d/%d", &tempFaces[0], &tempFaces[1], &tempFaces[2], &tempFaces[3], &tempFaces[4], &tempFaces[5], &tempFaces[6], &tempFaces[7], &tempFaces[8]);

        //Vertex, Texture, Normal
        for (int i = 0; i < 3; i++)
        {
            IndicesVector.push_back(tempFaces[i * 3]);
            texCoordIndicesVector.push_back(tempFaces[(i * 3) + 1]);
            normalIndicesVector.push_back(tempFaces[(i * 3) + 2]);
        }
        indexCount += 3;
        //std::cout << "Loaded Face" << std::endl;
    }

    void ApplyDataToMesh(Mesh& objMesh)
    {
        objMesh.vertexCount = vertexCount;
        objMesh.normalCount = normalCount;
        objMesh.TexCoordCount = TexCoordCount;
        objMesh.indexCount = indexCount;
        
        objMesh.Vertices = new Vertex[objMesh.indexCount];
        objMesh.Normals = new Vector3[objMesh.indexCount];
        objMesh.TexCoords = new TexCoord[objMesh.indexCount];
        objMesh.Indices = new GLushort[objMesh.indexCount];
        
        if (vertexCount > 0)
        {
            for (int i = 0; i < objMesh.indexCount; i++)
            {
                int vIndex  = IndicesVector[i] - 1;
                int vtIndex = texCoordIndicesVector[i] - 1;
                int vnIndex = normalIndicesVector[i] - 1;

                objMesh.Vertices[i] = VerticesVector[vIndex];

                if (vtIndex >= 0 && vtIndex < TexCoordsVector.size())
                    objMesh.TexCoords[i] = TexCoordsVector[vtIndex];

                if (vnIndex >= 0 && vnIndex < NormalsVector.size())
                    objMesh.Normals[i] = NormalsVector[vnIndex];

                objMesh.Indices[i] = IndicesVector[i] - 1;

            }
            //     if (normalCount > 0)
            //     {
            //         objMesh.normalCount = normalCount;
            //         objMesh.Normals = new Vector3[normalCount];
            //         for (int i = 0; i < normalCount; i++)
            //         {
            //             objMesh.Normals[i].x = NormalsVector[normalIndicesVector[i]-1].x;
            //             objMesh.Normals[i].y = NormalsVector[normalIndicesVector[i]-1].y;
            //             objMesh.Normals[i].z = NormalsVector[normalIndicesVector[i]-1].z;
            // std::cout << "Normal: " << objMesh.Normals[i].x << ", " << objMesh.Normals[i].y << ", " << objMesh.Normals[i].z << std::endl;
            //         }
            //     }
            //     if (TexCoordCount > 0)
            //     {
            //         objMesh.TexCoordCount = texCoordIndicesVector.size();
            // objMesh.TexCoords = new TexCoord[objMesh.indexCount];
            //         for (int i = 0; i < objMesh.TexCoordCount; i++)
            //         {
            //             objMesh.TexCoords[i].u = TexCoordsVector[texCoordIndicesVector[i]-1].u;
            // objMesh.TexCoords[i].v = TexCoordsVector[texCoordIndicesVector[i]-1].v;
            // std::cout << "TexCoord: " << objMesh.TexCoords[i].u << ", " << objMesh.TexCoords[i].v << std::endl;
            //         }
            //     }
            //     if (indexCount > 0)
            //     {
            //         objMesh.indexCount = indexCount;
            //         objMesh.Indices = new GLushort[indexCount];
            //         for (int i = 0; i < indexCount; i++)
            //         {
            //             objMesh.Indices[i] = IndicesVector[i]-1;
            //         }
        }
    }

    void ApplyIndexing(Mesh& objMesh)
    {
        if (vertexCount > 0)
        {
            objMesh.vertexCount = vertexCount;
            objMesh.Vertices = new Vertex[vertexCount];
            
            for (int i = 0; i < IndicesVector.size(); i++)
            {
                //int vertexIndexX = VerticesVector[i];
                //objMesh.Vertices[i] = VerticesVector[vertexIndexX -1];
                //int vertexIndexY = VerticesVector[i].y;
            }
        }

        if (TexCoordCount > 0)
        {
            objMesh.TexCoordCount = TexCoordCount;
            objMesh.TexCoords = new TexCoord[TexCoordCount];
            for (int i = 0; i < TexCoordsVector.size(); i++)
            {
                int TexVertexIndexU = TexCoordsVector[i].u;
                objMesh.TexCoords[i].u = TexCoordsVector[TexVertexIndexU-1].u;

                int TexVertexIndexV = TexCoordsVector[i].v;
                objMesh.TexCoords[i].v = TexCoordsVector[TexVertexIndexV-1].v;
            
            }
        }
        if (normalCount > 0)
        {
            objMesh.normalCount = normalCount;
            objMesh.Normals = new Vector3[normalCount];
            for (int i = 0; i < NormalsVector.size(); i++)
            {
                int vertexIndexX = NormalsVector[i].x;
                objMesh.Normals[i].x = NormalsVector[vertexIndexX -1].x;
                int vertexIndexY = NormalsVector[i].y;
                objMesh.Normals[i].y = NormalsVector[vertexIndexY-1].y;
                int vertexIndexZ = NormalsVector[i].z;
                objMesh.Normals[i].z = NormalsVector[vertexIndexZ-1].z;
            }
        }

        if (indexCount > 0)
        {
            objMesh.indexCount = indexCount;
            objMesh.Indices = new GLushort[indexCount];
            for (int i = 0; i < indexCount; i++)
            {
                objMesh.Indices[i] = i;
            }
        }
    }
}
