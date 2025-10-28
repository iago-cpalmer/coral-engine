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

#include "assets/public/assets_handler.h"
#include "assets/asset_list.h"
#include "core/memory_utils.h"
#include "renderer/data/buffers/frame_buffer.h"

const float DESIRED_FPS = 120;

int main()
{
	if (create_window(800, 600, "Coral Engine") == -1)
	{
		return -1;
	}
	glfwSwapInterval(0);
	renderer_init_opengl();
	renderer_set_clear_color(0, 181, 226);

	init_input();
	cursor_set_state(CursorLockType::CenterLock, false);
	
	CameraInfo camera{};
	camera.RenderTarget = RenderTargetType::Screen;
	camera.Projection = ProjectionType::Perspective;
	camera.Position = glm::vec3(0.0f, 0.0f, 6.0f);
	camera.Rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	camera.Fov = 45.0f;
	camera.SensitivityX = 10.0f;
	camera.SensitivityY = 15.0f;
	camera.MovementSpeed = 10.0f;
	camera.NearPlane = 0.1f;
	camera.FarPlane = 100.0f;

	bool locked = true;

	Scene scene;
	init_scene(&scene);
	scene_add_camera(&scene, &camera);

	al_load_all_assets();

	// vvv Mesh creation --------------
#pragma region BACKPACK_DEFINITION
	// Backpack
	Entity backpackEntity;
	backpackEntity.meshRendererData.ModelHandle = al_get_model_handle(ModelName::backpack);
	backpackEntity.Position = glm::vec3(10, 0, 0);
	backpackEntity.Rotation = glm::vec3(0, 0, 0);
	backpackEntity.Scale = glm::vec3(0.25f);
	//instantiate_entity(&scene, &backpackEntity);
#pragma endregion	

#pragma region CUBE_DEFINITION
	// vvv ----------------------------
	// Cube
	Entity cubeEntity;
	cubeEntity.meshRendererData.ModelHandle = al_get_model_handle(ModelName::backpack);
	cubeEntity.Position = glm::vec3(0);
	cubeEntity.Rotation = glm::vec3(0, 0, 0);
	cubeEntity.Scale = glm::vec3(1.0f);

	Entity cube2Entity;
	cube2Entity.meshRendererData.ModelHandle = al_get_model_handle(ModelName::backpack);
	cube2Entity.Position = glm::vec3(1, 0, 0);
	cube2Entity.Rotation = glm::vec3(0, 0, 0);
	cube2Entity.Scale = glm::vec3(1.0f);

	// --- Definition of material --------
	Material cubeMat;
	cubeMat.Ambient = glm::vec3(1.0f, 1.0f, 1.0f);
	cubeMat.Diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
	cubeMat.Specular = glm::vec3(1.0f, 1.0f, 1.0f);
	cubeMat.Shininess = 32.0f;
	cubeMat.Shader = al_get_shader_handle(ShaderName::basic_shader);
	cubeMat.AlbedoMap = al_get_texture_handle(TextureName::container);
	// -----------------------------------
	

	// --- Definition of mesh ------------
	VertexAttribute vertexAttributes[] =
	{
		VertexAttribute{VertexAttributeType::FLOAT, 3},	// Position
		VertexAttribute{VertexAttributeType::FLOAT, 3},	// Normal
		VertexAttribute{VertexAttributeType::FLOAT, 2}		// UV
	};
	Mesh cubeMesh;
	create_mesh(&cubeMesh, vertexAttributes, 3, VERTICES_CUBE, 24, INDICES_CUBE, 36, 1, GL_STATIC_DRAW);
	cubeMesh.Submeshes[0] = { 0, 36 };
	// -----------------------------------

	Model cubeModel;
	cubeModel.p_Mesh = &cubeMesh;
	cubeModel.MaterialCount = 1;
	cubeModel.p_MaterialHandles = (MaterialHandle*)CE_MALLOC(sizeof(MaterialHandle) * cubeModel.MaterialCount);
	cubeModel.p_MaterialHandles[0] = ah_register_material(&cubeMat);

	ModelHandle cubeModelHandle = ah_register_model(&cubeModel);
	cubeEntity.meshRendererData.ModelHandle = cubeModelHandle;

	cube2Entity.meshRendererData.ModelHandle = cubeModelHandle;

	instantiate_entity(&scene, &cubeEntity);
	instantiate_entity(&scene, &cube2Entity);
	// ^^^ ----------------------------
#pragma endregion

	// vvv ----------------------------
	// Light plane
	VertexAttribute vertexAttributesLight[] =
	{
		VertexAttribute{VertexAttributeType::FLOAT, 3},	// Position
		VertexAttribute{VertexAttributeType::FLOAT, 2}		// UV
	};

	Mesh lightPlane;
	create_mesh(&lightPlane, vertexAttributesLight, 2, VERTICES_PLANE, 4, INDICES_PLANE, 12, 1, GL_STATIC_DRAW);
	lightPlane.Submeshes[0] = { 0, 12 };
	
	Material lightMat;
	lightMat.Ambient = glm::vec3(1.0f, 1.0f, 1.0f);
	lightMat.Diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
	lightMat.Specular = glm::vec3(1.0f, 1.0f, 1.0f);
	lightMat.Shininess = 32.0f;
	lightMat.Shader = al_get_shader_handle(ShaderName::light_shader);
	lightMat.AlbedoMap = al_get_texture_handle(TextureName::point_light);
	MaterialHandle matLightHandle = ah_register_material(&lightMat);

	Entity lightSourceEntity;
	lightSourceEntity.Position = glm::vec3(0);
	lightSourceEntity.Rotation = glm::vec3(0);
	lightSourceEntity.Scale = glm::vec3(1);

	Model lightSourceModel;
	lightSourceModel.p_Mesh = &lightPlane;
	lightSourceModel.MaterialCount = 1;
	lightSourceModel.p_MaterialHandles = (MaterialHandle*)CE_MALLOC(sizeof(MaterialHandle));
	lightSourceModel.p_MaterialHandles[0] = matLightHandle;

	ModelHandle lightModelHandle = ah_register_model(&lightSourceModel);
	lightSourceEntity.meshRendererData.ModelHandle = lightModelHandle;

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

	// ----- Mirror
	// TODO: Attach frame buffers to cameras as render targets
	//RenderBuffer rb = create_rb(GL_DEPTH24_STENCIL8, 800, 600);
	FrameBuffer testFb = create_fb(FbRenderTargetType::Texture, 800, 600, 3);
	fb_create_rb_for_depth(&testFb, GL_DEPTH24_STENCIL8, 800, 600);

	CameraInfo cameraMirror{};
	camera_add_render_target(&cameraMirror, testFb);
	cameraMirror.Projection = ProjectionType::Perspective;
	cameraMirror.Position = glm::vec3(0.0f, 0.0f, 8.0f);
	cameraMirror.Rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	cameraMirror.Fov = 45.0f;
	cameraMirror.SensitivityX = 10.0f;
	cameraMirror.SensitivityY = 15.0f;
	cameraMirror.MovementSpeed = 10.0f;
	cameraMirror.NearPlane = 0.1f;
	cameraMirror.FarPlane = 100.0f;

	scene_add_camera(&scene, &cameraMirror);

	// --- Definition of mesh ------------
	VertexAttribute vertexAttributesMirror[] =
	{
		VertexAttribute{VertexAttributeType::FLOAT, 3},	// Position
		VertexAttribute{VertexAttributeType::FLOAT, 3},	// Texture
		VertexAttribute{VertexAttributeType::FLOAT, 2}		// UV
	};
	Mesh mirrorMesh;
	create_mesh(&mirrorMesh, vertexAttributesMirror, 3, VERTICES_CUBE, 24, INDICES_CUBE, 36, 1, GL_STATIC_DRAW);
	mirrorMesh.Submeshes[0] = { 0, 36 };

	Material mirrorMat;
	mirrorMat.Ambient = glm::vec3(1.0f, 1.0f, 1.0f);
	mirrorMat.Diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
	mirrorMat.Specular = glm::vec3(1.0f, 1.0f, 1.0f);
	mirrorMat.Shininess = 32.0f;
	mirrorMat.Shader = al_get_shader_handle(ShaderName::basic_shader);
	mirrorMat.AlbedoMap = testFb.ColorTarget.Texture;
	//mirrorMat.AlbedoMap = al_get_texture_handle(TextureName::container);

	Model mirrorModel;
	mirrorModel.p_Mesh = &mirrorMesh;
	mirrorModel.MaterialCount = 1;
	mirrorModel.p_MaterialHandles = (MaterialHandle*)CE_MALLOC(sizeof(MaterialHandle) * mirrorModel.MaterialCount);
	mirrorModel.p_MaterialHandles[0] = ah_register_material(&mirrorMat);

	ModelHandle mirrorModelHandle = ah_register_model(&mirrorModel);

	Entity mirrorEntity;
	mirrorEntity.meshRendererData.ModelHandle = mirrorModelHandle;
	mirrorEntity.Position = glm::vec3(0, 0, 3);
	mirrorEntity.Rotation = glm::vec3(0, 0, 0);
	mirrorEntity.Scale = glm::vec3(1.0f);
	
	mirrorEntity.meshRendererData.ModelHandle = mirrorModelHandle;

	instantiate_entity(&scene, &mirrorEntity);

	// ^^^ ----------------------------
	while (!window_should_close())
	{
#pragma region region_time_and_input
		if(!calculate_delta_time(window_get_time_since_start(), DESIRED_FPS)) continue;
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


