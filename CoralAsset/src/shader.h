#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

struct ShaderProgram {
    std::string Name;
    std::string VertexPath;
    std::string FragmentPath;
};


std::vector<std::string> _Shaders;
std::vector<ShaderProgram> _ShaderPrograms;

void process_shader(std::string r_path)
{
    // Read all .shad files and get its vertex and fragment paths
    std::ifstream file(r_path);
    if (!file.is_open()) return;

    std::string frag_path, vert_path;
    std::getline(file, frag_path);
    std::getline(file, vert_path);

    ShaderProgram shader;
    shader.Name = get_asset_name(r_path);
    shader.FragmentPath = frag_path;
    shader.VertexPath = vert_path;

    _ShaderPrograms.push_back(shader);
}

void process_shaders()
{
    for (size_t i = 0; i < _Shaders.size(); i++)
    {
        process_shader(_Shaders[i]);
    }
}

void write_shaders(std::ofstream& r_outputFile)
{
    r_outputFile << "\n// ------------------------------------\n";
    r_outputFile << "// Shaders \n";
    r_outputFile << "// ------------------------------------\n";

    // Enum
    r_outputFile << "enum class ShaderName\n";
    r_outputFile << "{\n";
    for (size_t i = 0; i < _ShaderPrograms.size(); i++)
    {
        r_outputFile << "\t" << _ShaderPrograms[i].Name;
        r_outputFile << ",\n";
    }
    r_outputFile << "\tCOUNT\n";
    r_outputFile << "};\n";

    // Paths
    r_outputFile << "static ShaderAsset _ShaderAssets[] =\n";
    r_outputFile << "{\n";

    for (size_t i = 0; i < _ShaderPrograms.size(); i++)
    {
        r_outputFile << "\t{ Asset{ \"" << _ShaderPrograms[i].FragmentPath << "\"}"
            << ", Asset{ \"" << _ShaderPrograms[i].VertexPath << "\"} }";
        if (i < _ShaderPrograms.size() - 1)
        {
            r_outputFile << ",";
        }
        r_outputFile << "\n";
    }
    r_outputFile << "}; \n";
}

#endif // !SHADER_H

