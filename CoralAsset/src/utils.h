#ifndef UTILS_H
#define UTILS_H


constexpr int TEXTURE_COUNT = 14;
const char* texture_extensions[TEXTURE_COUNT] = {
    ".png",
    ".jpg",
    ".jpeg",
    ".tga",
    ".bmp",
    ".psd",
    ".gif",
    ".hdr",
    ".dds",
    ".ktx",
    ".ktx2",
    ".exr",
    ".tiff",
    ".webp"
};

constexpr int MODEL_COUNT = 13;
const char* model_extensions[MODEL_COUNT] = {
    ".obj",
    ".fbx",
    ".dae",   // COLLADA
    ".3ds",
    ".blend", // Blender source
    ".gltf",
    ".glb",   // Binary GLTF
    ".ply",
    ".stl",
    ".x",     // DirectX
    ".ms3d",  // Milkshape 3D
    ".cob",   // TrueSpace
    ".x3d"
};

constexpr int SHADER_COUNT = 1;
const char* shader_extensions[SHADER_COUNT] =
{
    ".shad"
};

enum class AssetType
{
    NONE,
    TEXTURE,
    MODEL,
    SHADER
};

AssetType get_asset_type(std::string extension)
{
    // Normalize the extension to lowercase
    std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);

    for (size_t i = 0; i < TEXTURE_COUNT; ++i) {
        if (extension == texture_extensions[i]) {
            return AssetType::TEXTURE;
        }
    }

    for (size_t i = 0; i < MODEL_COUNT; ++i) {
        if (extension == model_extensions[i]) {
            return AssetType::MODEL;
        }
    }

    for (size_t i = 0; i < SHADER_COUNT; ++i) {
        if (extension == shader_extensions[i]) {
            return AssetType::SHADER;
        }
    }

    return AssetType::NONE;
}


std::string get_asset_name(const std::string& filepath) {
    std::filesystem::path path(filepath);
    return path.stem().string(); // stem() gives filename without extension
}

#endif // !UTILS_H
