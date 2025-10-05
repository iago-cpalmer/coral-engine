#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>

#include "utils.h"
#include "shader.h"
#include "texture.h"
#include "model.h"

namespace fs = std::filesystem;

void collect_assets(const fs::path& dir) {
    // Iterate through all files and directories within the given directory
    for (const auto& entry : fs::recursive_directory_iterator(dir)) {
        if (fs::is_regular_file(entry)) {
            // Get the file path relative to the 'res' directory
            std::string relative_path = entry.path().string();

            std::string full_path = relative_path;
            size_t pos = relative_path.find("res\\");
            if (pos != std::string::npos) {
                relative_path = relative_path.substr(pos);
            }
            
            // Get extension
            AssetType asset_type = AssetType::NONE;
            size_t pos_ext = relative_path.find(".");
            if (pos_ext != std::string::npos)
            {
                asset_type = get_asset_type(relative_path.substr(pos_ext));
            }

            std::replace(relative_path.begin(), relative_path.end(), '\\', '/');

            switch (asset_type)
            {
                case AssetType::NONE:
                {
                    // do nothing
                } break;
                case AssetType::TEXTURE:
                {
                    _Textures.push_back(relative_path);
                } break;
                case AssetType::MODEL:
                {
                    _Models.push_back(relative_path);
                } break;
                case AssetType::SHADER:
                {
                    _Shaders.push_back(full_path);
                } break;
            }
        }
    }
}

int main() {
    std::string res_path = "../CoralEngine/res";
    //std::string out_path = "../../CoralEngine/src/assets/asset_list.h";
    std::string out_path = "output.h";

    // Open output file for writing the asset list
    std::ofstream out_file(out_path);
    if (!out_file.is_open()) {
        std::cerr << "Error opening output file for writing: " << out_path << std::endl;
        return 1;
    }

    // Collect asset files from the 'res' directory and write them to the output file
    collect_assets(res_path);

    // Process models
    //process_models();

    // Process shaders
    process_shaders();

    // Write the header and the start of the asset list
    out_file << "#ifndef ASSET_LIST_H\n";
    out_file << "#define ASSET_LIST_H\n\n";

    out_file << "typedef struct\n";
    out_file << "{\n";
    out_file << " \tconst char* Path;\n";
    out_file << "} Asset;\n";
    
    out_file << "typedef struct\n";
    out_file << "{\n";
    out_file << " \tAsset Fragment;\n";
    out_file << " \tAsset Vertex;\n";
    out_file << "} ShaderAsset;\n";

    // write assets
    write_textures(out_file);
    write_shaders(out_file);
    write_models(out_file);

    // End the asset list and close the header file
    out_file << "#endif // ASSET_LIST_H\n";

    out_file.close();

    std::cout << "Asset list has been written to: " << out_path << std::endl;

    return 0;
}
