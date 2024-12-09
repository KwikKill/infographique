#include <Viewer.hpp>
#include <ShaderProgram.hpp>
#include <FrameRenderable.hpp>
#include <Io.hpp>
#include <lighting/LightedMeshRenderable.hpp>
#include <lighting/Light.hpp>

#include <QuadMeshRenderable.hpp>

#include <dynamics/DynamicSystemRenderable.hpp>
#include <dynamics/DampingForceField.hpp>
#include <dynamics/ConstantForceField.hpp>
#include <dynamics/SpringForceField.hpp>
#include <dynamics/EulerExplicitSolver.hpp>

#include <dynamics/ParticleRenderable.hpp>
#include <dynamics/ParticleListRenderable.hpp>
#include <dynamics/ConstantForceFieldRenderable.hpp>
#include <dynamics/SpringForceFieldRenderable.hpp>
#include <dynamics/SpringListRenderable.hpp>
#include <dynamics/ControlledForceFieldRenderable.hpp>

#include <texturing/TexturedPlaneRenderable.hpp>
#include <texturing/TexturedCubeRenderable.hpp>
#include <texturing/TexturedMeshRenderable.hpp>
#include <texturing/MultiTexturedCubeRenderable.hpp>
#include <texturing/MipMapCubeRenderable.hpp>
#include <texturing/BillBoardPlaneRenderable.hpp>
#include <lighting/DirectionalLightRenderable.hpp>
#include <texturing/TexturedTriangleRenderable.hpp>
#include <texturing/CubeMapRenderable.hpp>
#include <FrameRenderable.hpp>

const std::string texture_path = "../../good/mtl/";

LightedMeshRenderablePtr init_wall ( ShaderProgramPtr phong_shader) {
    // Add the wall
    const std::string wall_obj_path = "../../good/obj/wall_final.obj";
    std::vector<std::vector<glm::vec3>> wall_positions;
    std::vector<std::vector<glm::vec3>> wall_normals;
    std::vector<std::vector<glm::vec2>> wall_texcoords;
    std::vector<std::vector<unsigned int>> wall_indices;
    std::vector<MaterialPtr> wall_materials;
    
    read_obj_with_materials(wall_obj_path, texture_path, wall_positions, wall_normals, wall_texcoords, wall_materials);
    int wall_n_object = wall_materials.size();
    std::vector<glm::vec4> wall_colors;
    
    LightedMeshRenderablePtr wall_root;

    wall_root = std::make_shared<LightedMeshRenderable>(
        phong_shader, wall_positions[0], wall_normals[0], wall_colors, wall_materials[0]);
    for (int i = 1 ; i < wall_n_object ; ++i){
        LightedMeshRenderablePtr part = std::make_shared<LightedMeshRenderable>(
        phong_shader, wall_positions[i], wall_normals[i], wall_colors, wall_materials[i]);
        HierarchicalRenderable::addChild(wall_root, part);
    }

    return wall_root;
}

LightedMeshRenderablePtr init_caddy ( ShaderProgramPtr phong_shader) {
    // Add the caddy
    const std::string caddy_path = "../../good/obj/chariot.obj";
    std::vector<std::vector<glm::vec3>> all_positions_caddy;
    std::vector<std::vector<glm::vec3>> all_normals_caddy;
    std::vector<std::vector<glm::vec2>> all_texcoords_caddy;
    std::vector<std::vector<unsigned int>> all_indices_caddy;
    std::vector<MaterialPtr> materials_caddy;

    read_obj_with_materials(caddy_path, texture_path, all_positions_caddy, all_normals_caddy, all_texcoords_caddy, materials_caddy);

    int n_object_caddy = materials_caddy.size();
    std::vector<glm::vec4> colors_caddy;

    LightedMeshRenderablePtr root_caddy;

    root_caddy = std::make_shared<LightedMeshRenderable>(
        phong_shader, all_positions_caddy[0], all_normals_caddy[0], colors_caddy, materials_caddy[0]);
    for (int i = 1 ; i < n_object_caddy ; ++i){
        LightedMeshRenderablePtr part = std::make_shared<LightedMeshRenderable>(
        phong_shader, all_positions_caddy[i], all_normals_caddy[i], colors_caddy, materials_caddy[i]);
        HierarchicalRenderable::addChild(root_caddy, part);
    }

    return root_caddy;

}

LightedMeshRenderablePtr init_suitcase( ShaderProgramPtr phong_shader) {
    // Add the suitcase
    const std::string suitcase_path = "../../good/obj/suitcase_final.obj";
    std::vector<std::vector<glm::vec3>> all_positions_suitcase;
    std::vector<std::vector<glm::vec3>> all_normals_suitcase;
    std::vector<std::vector<glm::vec2>> all_texcoords_suitcase;
    std::vector<std::vector<unsigned int>> all_indices_suitcase;
    std::vector<MaterialPtr> materials_suitcase;

    read_obj_with_materials(suitcase_path, texture_path, all_positions_suitcase, all_normals_suitcase, all_texcoords_suitcase, materials_suitcase);

    int n_object_suitcase = materials_suitcase.size();
    std::vector<glm::vec4> colors_suitcase;

    LightedMeshRenderablePtr root_suitcase;

    root_suitcase = std::make_shared<LightedMeshRenderable>(
        phong_shader, all_positions_suitcase[0], all_normals_suitcase[0], colors_suitcase, materials_suitcase[0]);
    for (int i = 1 ; i < n_object_suitcase ; ++i){
        LightedMeshRenderablePtr part = std::make_shared<LightedMeshRenderable>(
        phong_shader, all_positions_suitcase[i], all_normals_suitcase[i], colors_suitcase, materials_suitcase[i]);
        HierarchicalRenderable::addChild(root_suitcase, part);
    }

    return root_suitcase;
}

LightedMeshRenderablePtr init_gare( ShaderProgramPtr phong_shader) {
    // Add the suitcase
    const std::string suitcase_path = "../../good/obj/gare.obj";
    std::vector<std::vector<glm::vec3>> all_positions_suitcase;
    std::vector<std::vector<glm::vec3>> all_normals_suitcase;
    std::vector<std::vector<glm::vec2>> all_texcoords_suitcase;
    std::vector<std::vector<unsigned int>> all_indices_suitcase;
    std::vector<MaterialPtr> materials_suitcase;

    read_obj_with_materials(suitcase_path, texture_path, all_positions_suitcase, all_normals_suitcase, all_texcoords_suitcase, materials_suitcase);

    int n_object_suitcase = materials_suitcase.size();
    std::vector<glm::vec4> colors_suitcase;

    LightedMeshRenderablePtr root_suitcase;

    root_suitcase = std::make_shared<LightedMeshRenderable>(
        phong_shader, all_positions_suitcase[0], all_normals_suitcase[0], colors_suitcase, materials_suitcase[0]);
    for (int i = 1 ; i < n_object_suitcase ; ++i){
        LightedMeshRenderablePtr part = std::make_shared<LightedMeshRenderable>(
        phong_shader, all_positions_suitcase[i], all_normals_suitcase[i], colors_suitcase, materials_suitcase[i]);
        HierarchicalRenderable::addChild(root_suitcase, part);
    }

    return root_suitcase;
}

void scene1( Viewer& viewer )
{
    // Create a shader program
	ShaderProgramPtr phong_shader = std::make_shared<ShaderProgram>(
        "../../sfmlGraphicsPipeline/shaders/phongVertex.glsl",
        "../../sfmlGraphicsPipeline/shaders/phongFragment.glsl");
	ShaderProgramPtr flat_shader = std::make_shared<ShaderProgram>(
        "../../sfmlGraphicsPipeline/shaders/flatVertex.glsl",
        "../../sfmlGraphicsPipeline/shaders/flatFragment.glsl");

    ShaderProgramPtr texShader = std::make_shared<ShaderProgram>(
        "../../sfmlGraphicsPipeline/shaders/simpleTextureVertex.glsl",
        "../../sfmlGraphicsPipeline/shaders/simpleTextureFragment.glsl");
    ShaderProgramPtr cubeMapShader = std::make_shared<ShaderProgram>(
        "../../sfmlGraphicsPipeline/shaders/cubeMapVertex.glsl",
        "../../sfmlGraphicsPipeline/shaders/cubeMapFragment.glsl");
    viewer.addShaderProgram( texShader );
    viewer.addShaderProgram( cubeMapShader );

    
    //std::string cubemap_dir = "../../sfmlGraphicsPipeline/textures/skybox";
    //auto cubemap = std::make_shared<CubeMapRenderable>(cubeMapShader, cubemap_dir);
    //viewer.addRenderable(cubemap);

    // Add the shader program to the viewer
    viewer.addShaderProgram( phong_shader );

    // Add the walls
    LightedMeshRenderablePtr wall_root = init_wall(phong_shader);
    wall_root->setGlobalTransform(getTranslationMatrix(+3, -2, -5.5)*getScaleMatrix(3, 3, 1));
    viewer.addRenderable(wall_root);

    LightedMeshRenderablePtr wall_root2 = init_wall(phong_shader);
    wall_root2->setGlobalTransform(getTranslationMatrix(+33, -2, -5.5)*getScaleMatrix(3, 3, 1));
    viewer.addRenderable(wall_root2);

    // Add the gare
    LightedMeshRenderablePtr gare_root = init_gare(phong_shader);
    gare_root->setGlobalTransform(getTranslationMatrix(4, 3, 25)*getScaleMatrix(2, 2, 2)*getRotationMatrix(3.14, glm::vec3(0, 1, 0)));
    viewer.addRenderable(gare_root);

    // Add the 9 3/4 sign
    const std::string sign_obj_path = "../../good/obj/pancarte9_3_4.obj";
    std::vector<std::vector<glm::vec3>> sign_positions;
    std::vector<std::vector<glm::vec3>> sign_normals;
    std::vector<std::vector<glm::vec2>> sign_texcoords;
    std::vector<std::vector<unsigned int>> sign_indices;
    std::vector<MaterialPtr> sign_materials;
    
    read_obj_with_materials(sign_obj_path, texture_path, sign_positions, sign_normals, sign_texcoords, sign_materials);
    int sign_n_object = sign_materials.size();
    std::vector<glm::vec4> sign_colors;
    
    LightedMeshRenderablePtr sign_root;

    sign_root = std::make_shared<LightedMeshRenderable>(
        phong_shader, sign_positions[0], sign_normals[0], sign_colors, sign_materials[0]);
    for (int i = 1 ; i < sign_n_object ; ++i){
        LightedMeshRenderablePtr part = std::make_shared<LightedMeshRenderable>(
        phong_shader, sign_positions[i], sign_normals[i], sign_colors, sign_materials[i]);
        HierarchicalRenderable::addChild(sign_root, part);
    }

    // resize and move the plateform
    sign_root->setGlobalTransform(
        getTranslationMatrix(6, 3, -8)
        *getScaleMatrix(1, 1, 1)
    );

    viewer.addRenderable(sign_root);

    // Add the caddie
    LightedMeshRenderablePtr root_caddie = init_caddy(phong_shader);
    //root_caddie->setGlobalTransform(getTranslationMatrix(2, 4.4, -2)*getScaleMatrix(1.4, 1.4, 1.4));

    // Animate the caddie
    root_caddie->addGlobalTransformKeyframe(getTranslationMatrix(3, 4.4, 0)*getScaleMatrix(1.6, 1.6, 1.6), 0);
    root_caddie->addGlobalTransformKeyframe(getTranslationMatrix(3, 4.4, -2)*getScaleMatrix(1.6, 1.6, 1.6), 3);
    root_caddie->addGlobalTransformKeyframe(getTranslationMatrix(3, 4.4, -13)*getScaleMatrix(1.6, 1.6, 1.6), 6);

    viewer.addRenderable(root_caddie);

    // Animate the camera as child of the caddie
    Camera& camera = viewer.getCamera();

    //camera.setGlobalTransform(getTranslationMatrix(0, 4.2, 5)*getRotationMatrix(3.14, glm::vec3(0, 1, 0)));
    
    camera.addGlobalTransformKeyframe(getTranslationMatrix(10, 12, 16)*getRotationMatrix(-3.14/12, glm::vec3(0, -1, 0)), 0);
    camera.addGlobalTransformKeyframe(getTranslationMatrix(0, 8, 5.5)*getRotationMatrix(-3.14/12, glm::vec3(1, 0, 0)), 3);
    camera.addGlobalTransformKeyframe(getTranslationMatrix(0, 8, -5)*getRotationMatrix(-3.14/12, glm::vec3(1, 0, 0)), 6);

    // Add the suitcase
    //LightedMeshRenderablePtr root_suitcase = init_suitcase(phong_shader);

    // set the suitcase as a child of the caddie
    //HierarchicalRenderable::addChild(root_caddie, root_suitcase);

    // Lightning
    glm::vec3 dir = glm::normalize(glm::vec3(-1,-1,-1));
    glm::vec3 ambient = glm::vec3(0,0,0);
    glm::vec3 diffuse = glm::vec3(1,1,1);
    glm::vec3 specular = glm::vec3(1,1,1);
    DirectionalLightPtr light1 = std::make_shared<DirectionalLight>(dir, ambient, diffuse, specular);
    dir = glm::normalize(glm::vec3(1,-1,1));
    ambient = glm::vec3(0,0,0);
    diffuse = glm::vec3(1,1,1);
    specular = glm::vec3(1,1,1);
    DirectionalLightPtr light2 = std::make_shared<DirectionalLight>(dir, ambient, diffuse, specular);
    dir = glm::normalize(glm::vec3(0,1,0));
    ambient = glm::vec3(0,0,0);
    diffuse = glm::vec3(1,1,1);
    specular = glm::vec3(1,1,1);
    DirectionalLightPtr light3 = std::make_shared<DirectionalLight>(dir, ambient, diffuse, specular);

    viewer.addDirectionalLight(light1);
    viewer.addDirectionalLight(light2);
    viewer.addDirectionalLight(light3);

    FrameRenderablePtr frame = std::make_shared<FrameRenderable>(flat_shader);
    viewer.addRenderable(frame);

    viewer.startAnimation();
}

int main() 
{
    glm::vec4 background_color(0.8,0.8,0.8,1);
	Viewer viewer(1280,720, background_color);
	
    scene1(viewer);

	while( viewer.isRunning() )
	{
		viewer.handleEvent();
		viewer.animate();
		viewer.draw();
		viewer.display();
	}	

	return EXIT_SUCCESS;
}