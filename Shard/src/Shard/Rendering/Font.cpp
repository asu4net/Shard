#include "shpch.h"
#include "Font.h"
#include "stb_truetype.h"

namespace Shard::Rendering
{
    Font::Font(const std::string& fileLocation)
    {
        std::ifstream fileStream(fileLocation, std::ifstream::binary);

        if (!fileStream) return;
        fileStream.seekg(0, fileStream.end);
        int length = fileStream.tellg();
        fileStream.seekg(0, fileStream.beg);
        char* buffer = new char[length];
        fileStream.read(buffer, length);
        delete[] buffer;
        
    }
}
