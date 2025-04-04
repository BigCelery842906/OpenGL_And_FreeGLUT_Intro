#include "Texture2D.h"
#include <Windows.h>
#include <fstream>
#include <iostream>
#include "Structures.h"

Texture2D::Texture2D()
{
    
}

Texture2D::~Texture2D()
{
    glDeleteTextures(1, &_ID);
}

bool Texture2D::Load(const char* path, int width, int height)
{
    char* tempTextureData;
    int fileSize;
    std::ifstream inFile;
    _width = width; _height = height;

    inFile.open(path, std::ios::binary);

    if (!inFile.good())
    {
        std::cerr << "Error opening file: " << path << std::endl;
        return false;
    }

    inFile.seekg(0, std::ios::end); //Seek to end of file
    fileSize = (int)inFile.tellg(); //Get current position (End) to get file size
    tempTextureData = new char [fileSize]; //Create new array
    inFile.seekg (0, std::ios::beg); //Go to beginning of file
    inFile.read(tempTextureData, fileSize); //Read all data
    inFile.close();
    std::cout << "Loading texture: " << path << std::endl;

    glGenTextures(1, &_ID);
    glBindTexture(GL_TEXTURE_2D, _ID);
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3,width,height,GL_RGB,GL_UNSIGNED_BYTE,tempTextureData);

    delete[] tempTextureData;
    return true;
}
