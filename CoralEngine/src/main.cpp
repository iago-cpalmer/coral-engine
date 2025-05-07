#include <iostream>

#include "core/window.h"

#include "renderer/data/shader.h"
#include "renderer/data/texture.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "renderer/data/mesh.h"

#include "core/input_handler.h"
#include "renderer/renderer.h"
#include "renderer/camera.h"
#include "core/time_manager.h"
#include "meshes.h"
#include "renderer/light/directional_light.h"
#include "renderer/light/point_light.h"
#include "core/utils.h"

#include "scene/entity.h"
#include "scene/scene.h"

#include "assets/assets_handler.h"

int main()
{
	if (create_window(800, 600, "Graphics Playground") == -1)
	{
		return -1;
	}
	renderer_init_opengl();
	renderer_set_clear_color(0, 181, 226);

	init_input();
	cursor_set_state(CursorLockType::CenterLock, false);
	
	CameraInfo camera{};
	camera.Projection = ProjectionType::Perspective;
	camera.Position = glm::vec3(0.0f, 0.0f, 6.0f);
	camera.Rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	camera.Fov = 45.0f;
	camera.SensitivityX = 1000.0f;
	camera.SensitivityY = 1500.0f;
	camera.MovementSpeed = 10.0f;
	camera.NearPlane = 0.1f;
	camera.FarPlane = 100.0f;

	bool locked = true;

	Scene scene;
	init_scene(&scene);
	scene_set_camera(&scene, &camera);

	ah_load_assets();

	// vvv Mesh creation --------------
	VertexAttribute vertexAttributes[] =
	{
		VertexAttribute{sizeof(float), 3, GL_FLOAT},	// Position
		VertexAttribute{sizeof(float), 3, GL_FLOAT},	// Normal
		VertexAttribute{sizeof(float), 2, GL_FLOAT}		// UV
	};
	Mesh mesh;
	create_mesh(&mesh, vertexAttributes, 3, VERTICES_CUBE, 24, INDICES_CUBE, 36, GL_STATIC_DRAW);

	Material defMat;
	defMat.Ambient = glm::vec3(1.0f, 1.0f, 1.0f);
	defMat.Diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
	defMat.Specular = glm::vec3(1.0f, 1.0f, 1.0f);
	defMat.Shininess = 32.0f;
	defMat.Shader = ah_get_shader_handle(ShaderName::BASIC_SHADER);
	defMat.AlbedoMap = ah_get_texture_handle(TextureName::CONTAINER);

	mesh.Material = &defMat;

	Entity cubeEntity;
	cubeEntity.p_Mesh = &mesh;
	cubeEntity.Position = glm::vec3(0);
	cubeEntity.Rotation = glm::vec3(0);
	cubeEntity.Scale = glm::vec3(1);

	instantiate_entity(&scene, &cubeEntity);

	// ^^^ ----------------------------

	// vvv Light plane ----------------
	
	VertexAttribute vertexAttributesLight[] =
	{
		VertexAttribute{sizeof(float), 3, GL_FLOAT},
		VertexAttribute{sizeof(float), 2, GL_FLOAT}
	};

	Mesh lightPlane;
	create_mesh(&lightPlane, vertexAttributesLight, 2, VERTICES_PLANE, 4, INDICES_PLANE, 6, GL_STATIC_DRAW);

	Material lightMat;
	lightMat.Ambient = glm::vec3(1.0f, 1.0f, 1.0f);
	lightMat.Diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
	lightMat.Specular = glm::vec3(1.0f, 1.0f, 1.0f);
	lightMat.Shininess = 32.0f;
	lightMat.Shader = ah_get_shader_handle(ShaderName::LIGHT_SHADER);
	lightMat.AlbedoMap = ah_get_texture_handle(TextureName::LIGHT_PLANE_TEXTURE);

	lightPlane.Material = &lightMat;

	Entity lightSourceEntity;
	lightSourceEntity.p_Mesh = &lightPlane;
	lightSourceEntity.Position = glm::vec3(0);
	lightSourceEntity.Rotation = glm::vec3(0);
	lightSourceEntity.Scale = glm::vec3(1);

	instantiate_entity(&scene, &lightSourceEntity);
	

	PointLight pointLight;
	pointLight.Position = glm::vec3(2.0f, 0.0f, 0.0f);
	pointLight.AmbientColor = glm::vec3(0.1f, 0.1f, 0.1f);
	pointLight.DiffuseColor = glm::vec3(0.5f, 0.5f, 0.5f);
	pointLight.SpecularColor = glm::vec3(0.75f, 0.75f, 0.75f);
	pointLight.Constant = 1.0f;
	pointLight.Linear = 0.09f;
	pointLight.Quadratic = 0.032f;


	DirectionalLight directionalLight;
	directionalLight.Direction = glm::vec3(-0.2f, -0.5f, -0.3f);
	directionalLight.AmbientColor = glm::vec3(0.1f, 0.1f, 0.1f);
	directionalLight.DiffuseColor = glm::vec3(0.75f, 0.75f, 0.75f);
	directionalLight.SpecularColor = glm::vec3(0.9f, 0.9f, 0.9f);

	add_directional_light(&scene, &directionalLight);
	add_point_light(&scene, &pointLight);

	// ^^^ ----------------------------

	while (!window_should_close())
	{
#pragma region region_time_and_input
		calculate_delta_time(window_get_time_since_start());
		update_input();
#pragma endregion

#pragma region region_update_state
		if (is_input_pressed(Input::Escape))
		{
			cursor_set_state(CursorLockType::Free, true);
			locked = false;
		}
		if (is_mouse_button_pressed(MouseButton::LeftClick))
		{
			cursor_set_state(CursorLockType::CenterLock, false);
			locked = true;
		}

		// vvv Camera stuff -----------
		if (locked)
		{
			camera_update(&camera);
		}
		// ^^^ ------------------------

		scene_update(&scene);

		// vvv Rotating Light 
		float lightX = 5.0f * sin(glfwGetTime());
		float lightY = 0.0f;
		float lightZ = 5.0f * cos(glfwGetTime());
		pointLight.Position = glm::vec3(lightX, lightY, lightZ);
		lightSourceEntity.Position = pointLight.Position;
		// ^^^ ------------------------

#pragma endregion

		renderer_prepare_frame();

		scene_render(&scene);

		renderer_finish_render();
	}

	window_terminate();
	return 0;
}


