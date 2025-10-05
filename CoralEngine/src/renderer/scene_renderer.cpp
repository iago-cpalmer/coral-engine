#include "scene_renderer.h"
#include <glm/trigonometric.hpp>
#include <glm/ext/quaternion_transform.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

#include "light/point_light.h"
#include "light/directional_light.h"

#include "renderer.h"
#include "../assets/assets_handler.h"


static CameraInfo* sp_Camera;
static glm::mat4x4 s_ViewMatrix;
static glm::mat4x4 s_ProjectionMatrix;

static Scene* sp_CurrentScene;

void begin_render(Scene* rp_Scene, CameraInfo* rpCamera)
{
	sp_CurrentScene = rp_Scene;
	sp_Camera = rpCamera;
	
	_calculate_view_matrix();
	_calculate_projection_matrix();
	/*
	// write all uniforms to shaders
	LightEnvironment* pLights = &sp_CurrentScene->SceneRenderData.LightEnv;

	for (int i = 0; i < sp_CurrentScene->SceneRenderData.MaterialTable.Materials.size(); i++)
	{
		Material* pMaterial = sp_CurrentScene->SceneRenderData.MaterialTable.Materials.at(i);
		if (pMaterial != nullptr)
		{
			Shader* pShader = ah_get_shader(pMaterial->Shader);
			use_shader(pShader);
			write_directional_light_to_shader(pShader, pLights->p_DirectionalLight);
			write_point_light_to_shader(pShader, pLights->p_PointLight);

			write_material_to_shader(pMaterial);

			set_uniform_vec3(pShader, "uViewPosition", sp_Camera->Position);
			shader_set_view_matrix(pShader, s_ViewMatrix);
			shader_set_projection_matrix(pShader, s_ProjectionMatrix);
		}
	}*/
}

void draw_mesh(Mesh* rp_mesh, glm::mat4x4 r_transform, Material* r_materials, unsigned int r_matCount)
{
	LightEnvironment* pLights = &sp_CurrentScene->SceneRenderData.LightEnv;
	for (unsigned int i = 0; i < rp_mesh->SubmeshCount; i++)
	{
		// all rendering stuff

		// TODO: all this uniforms should become part of uniform buffers
		// to avoid writing same uniforms multiple times
		assert(r_matCount == 1 || r_matCount == rp_mesh->SubmeshCount, "ERROR::Draw_Mesh - No general material used, expected then same number of materials than submeshes\n");
		Material& mat = r_materials[r_matCount == 1 ? 0 : r_matCount];
		Shader* shader = ah_get_shader(mat.Shader);
		use_shader(shader);

		write_directional_light_to_shader(shader, pLights->p_DirectionalLight);
		write_point_light_to_shader(shader, pLights->p_PointLight);

		write_material_to_shader(&mat);

		set_uniform_vec3(shader, "uViewPosition", sp_Camera->Position);
		shader_set_view_matrix(shader, s_ViewMatrix);
		shader_set_projection_matrix(shader, s_ProjectionMatrix);

		glActiveTexture(GL_TEXTURE0);
		use_texture(ah_get_texture(mat.AlbedoMap));

		shader_set_model_matrix(shader, r_transform);

		draw_indexed(rp_mesh->Vao, rp_mesh->Ibo, rp_mesh->Submeshes[i].IndexCount, rp_mesh->Submeshes[i].StartIndex);
	}
	
}


static void _calculate_view_matrix()
{
	s_ViewMatrix = glm::mat4(1.0f);
	s_ViewMatrix = glm::rotate(s_ViewMatrix, glm::radians(sp_Camera->Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	s_ViewMatrix = glm::rotate(s_ViewMatrix, glm::radians(sp_Camera->Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	s_ViewMatrix = glm::rotate(s_ViewMatrix, glm::radians(sp_Camera->Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	s_ViewMatrix = glm::translate(s_ViewMatrix, -sp_Camera->Position);
}

static void _calculate_projection_matrix()
{
	if (sp_Camera != nullptr && RendererData.ViewportSizePx != glm::vec2(0, 0))
	{
		s_ProjectionMatrix = glm::perspective(glm::radians(sp_Camera->Fov),
			RendererData.ViewportSizePx.x / RendererData.ViewportSizePx.y,
			sp_Camera->NearPlane,
			sp_Camera->FarPlane);
	}
}

void write_point_light_to_shader(Shader* rpShader, PointLight* rp_Light)
{
	set_uniform_vec3(rpShader, "uPointLight.AmbientColor", rp_Light->AmbientColor);
	set_uniform_vec3(rpShader, "uPointLight.DiffuseColor", rp_Light->DiffuseColor);
	set_uniform_vec3(rpShader, "uPointLight.SpecularColor", rp_Light->SpecularColor);
	set_uniform_vec3(rpShader, "uPointLight.Position", rp_Light->Position);
	set_uniform_float(rpShader, "uPointLight.Constant", rp_Light->Constant);
	set_uniform_float(rpShader, "uPointLight.Linear", rp_Light->Linear);
	set_uniform_float(rpShader, "uPointLight.Quadratic", rp_Light->Quadratic);
}

void write_directional_light_to_shader(Shader* rpShader, DirectionalLight* rp_Light)
{
	set_uniform_vec3(rpShader, "uDirectionalLight.AmbientColor", rp_Light->AmbientColor);
	set_uniform_vec3(rpShader, "uDirectionalLight.DiffuseColor", rp_Light->DiffuseColor);
	set_uniform_vec3(rpShader, "uDirectionalLight.SpecularColor", rp_Light->SpecularColor);
	set_uniform_vec3(rpShader, "uDirectionalLight.Direction", rp_Light->Direction);
}

void write_material_to_shader(Material* rp_material)
{
	set_uniform_vec3(ah_get_shader(rp_material->Shader), "uMaterial.Ambient", rp_material->Ambient);
	set_uniform_vec3(ah_get_shader(rp_material->Shader), "uMaterial.Diffuse", rp_material->Diffuse);
	set_uniform_vec3(ah_get_shader(rp_material->Shader), "uMaterial.Specular", rp_material->Specular);
	set_uniform_float(ah_get_shader(rp_material->Shader), "uMaterial.Shininess", rp_material->Shininess);
	//set_uniform_1i(ah_get_shader(rp_material->Shader), "uMaterial.AlbedoMap", ah_get_texture(rp_material->AlbedoMap)->Texture);
}