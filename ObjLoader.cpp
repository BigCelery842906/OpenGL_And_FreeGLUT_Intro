#include "ObjLoader.h"

//#include "MeshLoader.h"


namespace OBJ_Loader
{

    OBJMesh* Load(char* path)
    {
        OBJMesh* objMesh = new OBJMesh();
        std::ifstream objInFile;

        std::string objInTemp;

        objInFile.open(path);

        if (!objInFile.good())
        {
            std::cerr << "Error opening OBJ file: " << path << std::endl;
            return nullptr;
        }

        //LOAD THINGS
        while (objInFile >> objInTemp)
        {
            objInTemp = "";
            objInFile >> objInTemp;
            // std::cout << objInTemp << std::endl;
            
            if (objInTemp == "v")
            {
                //LoadVertices
                std::cout << "Reading as V" << std::endl;
                LoadVertices(objInFile, *objMesh);
                //Pull in 3 inFile
            }
            else if (objInTemp == "vn")
            {
                //Load Vertex Normals
                LoadVertexNormals(objInFile, *objMesh);
                //Pull in 3 inFile
            }
            else if (objInTemp == "vt")
            {
                //Load Vertex Textures(?) (I think thats what that is)
                LoadVertexTextures(objInFile, *objMesh);
                //Pull in 3 inFile
            }
            else if (objInTemp == "f")
            {
                //Load Face Vertex Order
                LoadFaceOrder(objInFile, *objMesh);
            }
            else
            {
                //This will have anything else like any 's' or # or just random text, basically anything this isn't designed to hanlde
                std::cout << "No useful found, moving to next." << std::endl;
            }
            
            
        }

        std::cout << "End of File" << std::endl;


        objInFile.close();
        return objMesh;        
    }

    void LoadVertices(std::ifstream& objInFile, OBJMesh& objMesh)
    {
        
        objMesh.vertexCount++;
        //SOMETHING WRONG HERE
        //objInFile >> objMesh.Vertices[objMesh.vertexCount-1].x;
        //objInFile >> objMesh.Vertices[objMesh.vertexCount-1].y;
        //objInFile >> objMesh.Vertices[objMesh.vertexCount-1].z;

        Vertex tempVertex;
		objInFile >> tempVertex.x >> tempVertex.y >> tempVertex.z;
		objMesh.Vertices.push_back(tempVertex);
    }

    void LoadVertexNormals(std::ifstream& objInFile, OBJMesh& objMesh)
    {
        objMesh.normalCount++;
       /* objInFile >> objMesh.Normals[objMesh.normalCount-1].x;
        objInFile >> objMesh.Normals[objMesh.normalCount-1].y;
        objInFile >> objMesh.Normals[objMesh.normalCount-1].z;*/

		Vector3 tempNormal;
		objInFile >> tempNormal.x >> tempNormal.y >> tempNormal.z;
		objMesh.Normals.push_back(tempNormal);
    }

    void LoadVertexTextures(std::ifstream& objInFile, OBJMesh& objMesh)
    {
        objMesh.TexCoordCount++;
        //objInFile >> objMesh.TexCoords[objMesh.TexCoordCount-1].u;
        //objInFile >> objMesh.TexCoords[objMesh.TexCoordCount-1].v;

		TexCoord tempTexCoord;
		objInFile >> tempTexCoord.u >> tempTexCoord.v;
		objMesh.TexCoords.push_back(tempTexCoord);
    }

    void LoadFaceOrder(std::ifstream& objInFile, OBJMesh& objMesh)
    {
        std::string tempLine;
        tempLine = objInFile.get();


        //Might need to & in front of the objMesh thing
        sscanf_s(tempLine.c_str(), "f %f/%f/%f %f/%f/%f %f/%f/%f", objMesh.Indices[objMesh.indexCount], objMesh.Indices[objMesh.indexCount+1], objMesh.Indices[objMesh.indexCount+2], objMesh.Indices[objMesh.indexCount+3], objMesh.Indices[objMesh.indexCount+4], objMesh.Indices[objMesh.indexCount+5], objMesh.Indices[objMesh.indexCount+6], objMesh.Indices[objMesh.indexCount+7], objMesh.Indices[objMesh.indexCount+8] );
        objMesh.indexCount += 9;
        
        
        //objInFile >> objMesh.Indices[objMesh.indexCount-1];
    }

    
};
