#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

std::vector<std::string> _Textures;


void write_textures(std::ofstream& r_outputFile)
{
    r_outputFile << "\n// ------------------------------------\n";
    r_outputFile << "// Textures \n";
    r_outputFile << "// ------------------------------------\n";

    // Enum
    r_outputFile << "enum class TextureName\n";
    r_outputFile << "{\n";
    for (size_t i = 0; i < _Textures.size(); i++)
    {
        r_outputFile << "\t" << get_asset_name(_Textures[i]);
        r_outputFile << ",\n";
    }
    r_outputFile << "\tCOUNT\n";
    r_outputFile << "};\n";

    // Paths
    r_outputFile << "static Asset _TextureAssets[] =\n";
    r_outputFile << "{\n";

    for (size_t i = 0; i < _Textures.size(); i++)
    {
        r_outputFile << "\tAsset{ \"" << _Textures[i] << "\"}";
        if (i < _Textures.size() - 1)
        {
            r_outputFile << ",";
        }
        r_outputFile << "\n";
    }
    r_outputFile << "}; \n";
}

#endif // !TEXTURE_H
