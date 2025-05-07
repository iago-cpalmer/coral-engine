#ifndef ASSETS_HANDLER_H
#define ASSETS_HANDLER_H

#include "asset_list.h"
#include <vector>
#include "../renderer/data/texture.h"
#include "../renderer/data/shader.h"
#include "../renderer/data/model.h"

void ah_load_assets();

// ------------------------------------
// Textures
// ------------------------------------

void load_textures();
void load_texture(Texture* rp_texture, Asset& r_texture);

TextureHandle ah_get_texture_handle(TextureName r_textureName);
Texture* ah_get_texture(TextureHandle r_textureHandle);

// ------------------------------------
// Shaders
// ------------------------------------

void load_shaders();
void load_shader(Shader* rp_shader, ShaderAsset& r_shader);

ShaderHandle ah_get_shader_handle(ShaderName r_shaderName);

Shader* ah_get_shader(ShaderHandle r_shaderHandle);

// ------------------------------------
// Models
// ------------------------------------

void load_models();
void load_model(Model* rp_model, Asset& r_model);

ModelHandle ah_get_model_handle(ModelName r_modelName);
Model* ah_get_model(ModelHandle r_modelHandle);

#endif // ! ASSETS_HANDLER_H


