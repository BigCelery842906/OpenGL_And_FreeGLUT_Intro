#include "MeshLoader.h"

#include <iostream>
#include <fstream>
#include <gl/GL.h>
using namespace std;

namespace MeshLoader
{	
	void LoadVertices(ifstream& inFile, Mesh& mesh)
	{
		inFile >> mesh.vertexCount;
		std::cout << "Number of Vertices: " << mesh.vertexCount << std::endl;
		if (mesh.vertexCount > 0)
		{
			Vertex tempVertex;
			for (int i = 0; i < mesh.vertexCount; i++)
			{
				
				inFile >> tempVertex.x;
				inFile >> tempVertex.y;
				inFile >> tempVertex.z;
				mesh.Vertices.push_back(tempVertex);
				std::cout << mesh.Vertices[i].x << " " << mesh.Vertices[i].y << " " << mesh.Vertices[i].z << std::endl;
				
			}
		}
	}

	void LoadNormals(ifstream& inFile, Mesh& mesh)
	{
		inFile >> mesh.normalCount;
		std::cout << "Number of Normals: " << mesh.normalCount << std::endl;
		if (mesh.normalCount > 0)
		{
			Vector3 tempNormal;
			for (int i = 0; i < mesh.normalCount; i++)
			{
				inFile >> tempNormal.x;
				inFile >> tempNormal.y;
				inFile >> tempNormal.z;
				mesh.Normals.push_back(tempNormal);
				std::cout << mesh.Normals[i].x << " " << mesh.Normals[i].y << " " << mesh.Normals[i].z << std::endl;
			}
		}
	}

	void LoadTexCoords(ifstream& inFile, Mesh& mesh)
	{
		inFile >> mesh.TexCoordCount;
		std::cout << "Number of Texture Coords: " << mesh.TexCoordCount << std::endl;
		if (mesh.TexCoordCount > 0)
		{
			TexCoord tempTexcoord;
			for (int i = 0; i < mesh.TexCoordCount; i++)
			{
				inFile >> tempTexcoord.u;
				inFile >> tempTexcoord.v;
				mesh.TexCoords.push_back(tempTexcoord);
				std::cout << mesh.TexCoords[i].u << " " << mesh.TexCoords[i].v << std::endl;
			}
		}
	}

	void LoadIndices(ifstream& inFile, Mesh& mesh)
	{
		inFile >> mesh.indexCount;
		std::cout << "Number of Indices: " << mesh.indexCount << std::endl;
		if (mesh.indexCount > 0)
		{
			GLushort tempIndex;
			for (int i = 0; i < mesh.indexCount; i++)
			{
				inFile >> tempIndex;
				mesh.Indices.push_back(tempIndex);
				std::cout << mesh.Indices[i] << std::endl;
			}
		}
	}

	Mesh* Load(char* path, bool isPyramid)
	{
		Mesh* mesh = new Mesh();

		ifstream inFile;

		inFile.open(path);

		if (!inFile.good())
		{
			cerr << "Can't open texture file " << path << endl;
			return nullptr;
		}

		LoadVertices(inFile, *mesh);
		if (!isPyramid)
		{
			LoadTexCoords(inFile, *mesh);
		}
		LoadNormals(inFile, *mesh);
		LoadIndices(inFile, *mesh);

		inFile.close();
		return mesh;
	}
}