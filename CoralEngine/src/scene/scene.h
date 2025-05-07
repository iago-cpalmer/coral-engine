#ifndef SCENE_H
#define SCENE_H

#include <string>
#include "../renderer/camera.h"
#include "entity.h"
#include "../renderer/material_table.h"
#include "../renderer/light/directional_light.h"
#include "../renderer/light/point_light.h"

#define MAX_ENTITIES 10

typedef struct
{
	DirectionalLight* p_DirectionalLight;
	PointLight* p_PointLight;
} LightEnvironment;

typedef struct
{
	// Light environment
	LightEnvironment LightEnv;

	MaterialTable MaterialTable;	// Material table is used to avoid setting uniforms multiple time
									// to the same material, for each entity that shares the material.
									// TODO: implement uniform buffers to avoid this
									
} SceneRenderingData;

typedef struct {
	std::string SceneName;
	
	CameraInfo* p_Camera;

	// TODO: change way to store entities
	Entity* Entities[MAX_ENTITIES];
	int NumberOfEntities;
	// ^^^

	SceneRenderingData SceneRenderData;
} Scene;

void init_scene(Scene* rpScene);

void scene_set_camera(Scene* rpScene, CameraInfo* rpCamera);

void scene_update(Scene* rpScene);

void scene_render(Scene* rpScene);

void instantiate_entity(Scene* rp_scene, Entity* entity);

void add_directional_light(Scene* rp_scene, DirectionalLight* rp_light);
void add_point_light(Scene* rp_scene, PointLight* rp_light);

#endif // !SCENE_H


