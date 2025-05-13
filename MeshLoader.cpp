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
			mesh.Vertices = new Vertex[mesh.vertexCount];

			for (int i = 0; i < mesh.vertexCount; i++)
			{
				inFile >> mesh.Vertices[i].x;
				inFile >> mesh.Vertices[i].y;
				inFile >> mesh.Vertices[i].z;
				std::cout <<mesh.Vertices[i].x << " " << mesh.Vertices[i].y << " " << mesh.Vertices[i].z << std::endl;

			}
		}
	}

	/*void LoadColours(ifstream& inFile, Mesh& mesh)
	{
		inFile >> mesh.colorCount;
		std::cout << "Number of Colours: " << mesh.colorCount << std::endl;
		if (mesh.colorCount > 0)
		{
			mesh.Colors = new Color[mesh.colorCount];

			for (int i = 0; i < mesh.colorCount; i++)
			{
				inFile >> mesh.Colors[i].r;
				inFile >> mesh.Colors[i].g;
				inFile >> mesh.Colors[i].b;
				std::cout << mesh.Colors[i].r << " " << mesh.Colors[i].g << " " << mesh.Colors[i].b << std::endl;

			}
		}
	}*/

	void LoadNormals(ifstream& inFile, Mesh& mesh)
	{
		inFile >> mesh.normalCount;
		std::cout << "Number of Normals: " << mesh.normalCount << std::endl;
		if (mesh.normalCount > 0)
		{
			mesh.Normals = new Vector3[mesh.normalCount];
			for (int i = 0; i < mesh.normalCount; i++)
			{
				inFile >> mesh.Normals[i].x;
				inFile >> mesh.Normals[i].y;
				inFile >> mesh.Normals[i].z;
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
			mesh.TexCoords = new TexCoord[mesh.TexCoordCount];

			for (int i = 0; i < mesh.TexCoordCount; i++)
			{
				inFile >> mesh.TexCoords[i].u;
				inFile >> mesh.TexCoords[i].v;
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
			mesh.Indices = new GLushort[mesh.indexCount];

			for (int i = 0; i < mesh.indexCount; i++)
			{
				inFile >> mesh.Indices[i];
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