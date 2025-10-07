#include "scene.h"
#include "../renderer/scene_renderer.h"
#include "../assets/public/assets_handler.h"
//#include "../../assets/assets_handler.h"

void init_scene(Scene* rpScene)
{
	for (int i = 0; i < MAX_ENTITIES; i++)
	{
		rpScene->Entities[i] = NULL;
	}
}

void scene_set_camera(Scene* rpScene, CameraInfo* rpCamera)
{
	rpScene->p_Camera = rpCamera;
}

void scene_update(Scene* rpScene)
{
	// Update camera

	// Update entities
}

void scene_render(Scene* rpScene)
{
	begin_render(rpScene, rpScene->p_Camera);

	for (int i = 0; i < MAX_ENTITIES; i++)
	{
		Entity* entity = rpScene->Entities[i];
		if (entity != NULL)
		{
			glm::mat4 transform = glm::mat4(1.0f);
			transform = glm::scale(transform, entity->Scale);
			transform = glm::rotate(transform, entity->Rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
			transform = glm::rotate(transform, entity->Rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
			transform = glm::rotate(transform, entity->Rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
			transform = glm::translate(transform, entity->Position);
			
			Model* model = ah_get_model(entity->meshRendererData.ModelHandle);
			draw_mesh(model->p_Mesh, transform, model->p_MaterialHandles, model->MaterialCount);
		}
	}
}

void instantiate_entity(Scene* rp_scene, Entity* entity)
{
	// add entity to list of entities
	for (int i = 0; i < MAX_ENTITIES; i++)
	{
		if (rp_scene->Entities[i] == NULL)
		{
			rp_scene->Entities[i] = entity;
			break;
		}
	}
}


void add_directional_light(Scene* rp_scene, DirectionalLight* rp_light)
{
	rp_scene->SceneRenderData.LightEnv.p_DirectionalLight = rp_light;
}
void add_point_light(Scene* rp_scene, PointLight* rp_light)
{
	rp_scene->SceneRenderData.LightEnv.p_PointLight = rp_light;
}