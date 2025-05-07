#include "assets_handler.h"

static std::vector<Texture> _Textures;
static std::vector<Shader> _Shaders;
static std::vector<Model> _Models;

void ah_load_assets()
{
    load_textures();
    load_shaders();
    load_models();
}

void load_textures()
{
    _Textures.resize((int)TextureName::COUNT);
    for (int i = 0; i < (int)TextureName::COUNT; i++)
    {
        load_texture(&_Textures[i], _TextureAssets[i]);
    }
}

void load_texture(Texture* rp_texture, Asset& r_texture)
{
    create_texture(rp_texture, r_texture.Path);
}

TextureHandle ah_get_texture_handle(TextureName r_textureName)
{
    return TextureHandle{ (unsigned int)r_textureName };
}

Texture* ah_get_texture(TextureHandle r_textureHandle)
{
    assert(r_textureHandle.Id < _Textures.size());
    return &_Textures[r_textureHandle.Id];
}


void load_models()
{
    _Models.resize((int)ModelName::COUNT);
    for (int i = 0; i < (int)ModelName::COUNT; i++)
    {
        load_model(&_Models[i], _ModelAssets[i]);
    }
}

void load_model(Model* rp_model, Asset& r_model)
{
    // TODO: implement
}
ModelHandle ah_get_model_handle(ModelName r_modelName)
{
    return ModelHandle{ (unsigned int)r_modelName };
}

Model* ah_get_model(ModelHandle r_modelHandle)
{
    assert(r_modelHandle.Id < _Models.size());
    return &_Models[r_modelHandle.Id];
}


void load_shaders()
{
    _Shaders.resize((int)ShaderName::COUNT);
    for (int i = 0; i < (int)ShaderName::COUNT; i++)
    {
        load_shader(&_Shaders[i], _ShaderAssets[i]);
    }
}

void load_shader(Shader* rp_shader, ShaderAsset& r_shader)
{
    create_shader(rp_shader, r_shader.Vertex.Path, r_shader.Fragment.Path);
    use_shader(rp_shader);
}

ShaderHandle ah_get_shader_handle(ShaderName r_shaderName)
{
    return ShaderHandle{ (unsigned int)r_shaderName };
}

Shader* ah_get_shader(ShaderHandle r_shaderHandle)
{
    if (r_shaderHandle.Id >= _Shaders.size())
    {
        ;
    }
    return &_Shaders[r_shaderHandle.Id];
}