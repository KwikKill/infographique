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
#include <lighting/SpotLightRenderable.hpp>
#include <lighting/PointLightRenderable.hpp>

const std::string texture_path = "../../assets/mtl/";

LightedMeshRenderablePtr init_traing_wheels(const std::string &path, const std::string &texture_path, ShaderProgramPtr shader, glm::vec3 translation, const std::vector<std::pair<glm::mat4, float>> &transformations)
{
    std::vector<std::vector<glm::vec3>> all_positions;
    std::vector<std::vector<glm::vec3>> all_normals;
    std::vector<std::vector<glm::vec2>> all_texcoords;
    std::vector<std::vector<unsigned int>> all_indices;
    std::vector<MaterialPtr> materials;

    read_obj_with_materials(path, texture_path, all_positions, all_normals, all_texcoords, materials);

    int n_objects = materials.size();
    std::vector<glm::vec4> colors;

    LightedMeshRenderablePtr root = std::make_shared<LightedMeshRenderable>(
        shader, all_positions[0], all_normals[0], colors, materials[0]);
    for (int i = 1; i < n_objects; ++i)
    {
        LightedMeshRenderablePtr part = std::make_shared<LightedMeshRenderable>(
            shader, all_positions[i], all_normals[i], colors, materials[i]);
        HierarchicalRenderable::addChild(root, part);
    }

    root->setGlobalTransform(getTranslationMatrix(translation.x, translation.y, translation.z));

    for (const auto &transform : transformations)
    {
        root->addLocalTransformKeyframe(transform.first, transform.second);
    }

    return root;
}

LightedMeshRenderablePtr init_wagon(ShaderProgramPtr phong_shader)
{
    // Add the car
    const std::string wagon_path = "../../assets/obj/wagon.obj";
    std::vector<std::vector<glm::vec3>> all_positions_wagon;
    std::vector<std::vector<glm::vec3>> all_normals_wagon;
    std::vector<std::vector<glm::vec2>> all_texcoords_wagon;
    std::vector<std::vector<unsigned int>> all_indices_wagon;
    std::vector<MaterialPtr> materials_wagon;

    read_obj_with_materials(wagon_path, texture_path, all_positions_wagon, all_normals_wagon, all_texcoords_wagon, materials_wagon);

    int n_object_wagon = materials_wagon.size();
    std::vector<glm::vec4> colors_wagon;

    LightedMeshRenderablePtr root_wagon;

    root_wagon = std::make_shared<LightedMeshRenderable>(
        phong_shader, all_positions_wagon[0], all_normals_wagon[0], colors_wagon, materials_wagon[0]);
    for (int i = 1; i < n_object_wagon; ++i)
    {
        LightedMeshRenderablePtr part = std::make_shared<LightedMeshRenderable>(
            phong_shader, all_positions_wagon[i], all_normals_wagon[i], colors_wagon, materials_wagon[i]);
        HierarchicalRenderable::addChild(root_wagon, part);
    }

    return root_wagon;
}

LightedMeshRenderablePtr init_traing(ShaderProgramPtr phong_shader, int nb_wagon, const std::vector<std::pair<glm::mat4, float>> &transformations)
{
    // Add the traing
    const std::string traing_path = "../../assets/obj/ossature_train_finale.obj";
    std::vector<std::vector<glm::vec3>> all_positions_traing;
    std::vector<std::vector<glm::vec3>> all_normals_traing;
    std::vector<std::vector<glm::vec2>> all_texcoords_traing;
    std::vector<std::vector<unsigned int>> all_indices_traing;
    std::vector<MaterialPtr> materials_traing;

    read_obj_with_materials(traing_path, texture_path, all_positions_traing, all_normals_traing, all_texcoords_traing, materials_traing);

    int n_object_traing = materials_traing.size();
    std::vector<glm::vec4> colors_traing;

    LightedMeshRenderablePtr root_traing;

    root_traing = std::make_shared<LightedMeshRenderable>(
        phong_shader, all_positions_traing[0], all_normals_traing[0], colors_traing, materials_traing[0]);
    for (int i = 1; i < n_object_traing; ++i)
    {
        LightedMeshRenderablePtr part = std::make_shared<LightedMeshRenderable>(
            phong_shader, all_positions_traing[i], all_normals_traing[i], colors_traing, materials_traing[i]);
        HierarchicalRenderable::addChild(root_traing, part);
    }

    const std::string roues_traing_path = "../../assets/obj/petites_roues_train.obj";
    const std::string roues_arriere_traing_path = "../../assets/obj/grandes_roues_train.obj";
    std::vector<glm::vec3> translations = {
        glm::vec3(-5.3, 2, -0.1),
        glm::vec3(-1, 2, -0.1),
        glm::vec3(2.2, 3, -0.1),
        glm::vec3(6.4, 3, -0.1),
        glm::vec3(11, 3, -0.1)};

    for (int i = 0; i < translations.size(); ++i)
    {
        std::string path = (i < 2) ? roues_traing_path : roues_arriere_traing_path;
        LightedMeshRenderablePtr wheels = init_traing_wheels(path, texture_path, phong_shader, translations[i], transformations);
        HierarchicalRenderable::addChild(root_traing, wheels);
    }

    // Add wagons behind the train
    LightedMeshRenderablePtr previous_wagon = root_traing;
    for (int i = 0; i < nb_wagon; ++i)
    {
        LightedMeshRenderablePtr wagon = init_wagon(phong_shader);
        glm::mat4 translation = (i == 0) ? getTranslationMatrix(25, 2, 0) : getTranslationMatrix(33, 0, 0);
        wagon->setGlobalTransform(translation);
        HierarchicalRenderable::addChild(previous_wagon, wagon);
        previous_wagon = wagon;
    }

    return root_traing;
}

LightedMeshRenderablePtr init_wall(ShaderProgramPtr phong_shader)
{
    // Add the wall
    const std::string wall_obj_path = "../../assets/obj/wall_final.obj";
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
    for (int i = 1; i < wall_n_object; ++i)
    {
        LightedMeshRenderablePtr part = std::make_shared<LightedMeshRenderable>(
            phong_shader, wall_positions[i], wall_normals[i], wall_colors, wall_materials[i]);
        HierarchicalRenderable::addChild(wall_root, part);
    }

    return wall_root;
}

LightedMeshRenderablePtr init_caddy(ShaderProgramPtr phong_shader)
{
    // Add the caddy
    const std::string caddy_path = "../../assets/obj/chariot.obj";
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
    for (int i = 1; i < n_object_caddy; ++i)
    {
        LightedMeshRenderablePtr part = std::make_shared<LightedMeshRenderable>(
            phong_shader, all_positions_caddy[i], all_normals_caddy[i], colors_caddy, materials_caddy[i]);
        HierarchicalRenderable::addChild(root_caddy, part);
    }

    return root_caddy;
}

LightedMeshRenderablePtr init_gare(ShaderProgramPtr phong_shader)
{
    // Add the suitcase
    const std::string suitcase_path = "../../assets/obj/gare.obj";
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
    for (int i = 1; i < n_object_suitcase; ++i)
    {
        LightedMeshRenderablePtr part = std::make_shared<LightedMeshRenderable>(
            phong_shader, all_positions_suitcase[i], all_normals_suitcase[i], colors_suitcase, materials_suitcase[i]);
        HierarchicalRenderable::addChild(root_suitcase, part);
    }

    return root_suitcase;
}

void scene2(Viewer &viewer)
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

    viewer.addShaderProgram(texShader);
    viewer.addShaderProgram(cubeMapShader);
    viewer.addShaderProgram(flat_shader);
    viewer.addShaderProgram(phong_shader);

    // Add the gare
    LightedMeshRenderablePtr gare_root = init_gare(phong_shader);
    gare_root->setGlobalTransform(getTranslationMatrix(4, 3, 25) * getScaleMatrix(2, 2, 2) * getRotationMatrix(3.14, glm::vec3(0, 1, 0)));
    viewer.addRenderable(gare_root);

    // Add a wall at the animation starting point
    LightedMeshRenderablePtr wall_root = init_wall(phong_shader);
    wall_root->setGlobalTransform(getTranslationMatrix(-26.5, 0, 42));
    viewer.addRenderable(wall_root);

    // Add the chariot
    LightedMeshRenderablePtr root_caddy = init_caddy(phong_shader);

    root_caddy->addGlobalTransformKeyframe(getTranslationMatrix(-24, 4, 36) * getScaleMatrix(1.6, 1.6, 1.6), 0);
    root_caddy->addGlobalTransformKeyframe(getTranslationMatrix(-24, 4, 28) * getScaleMatrix(1.6, 1.6, 1.6), 5);
    root_caddy->addGlobalTransformKeyframe(getTranslationMatrix(-24, 4, 28) * getScaleMatrix(1.6, 1.6, 1.6), 14);

    viewer.addRenderable(root_caddy);

    // Add the train with a wheel animation
    std::vector<std::pair<glm::mat4, float>> transformations = {
        {getRotationMatrix(0.0, glm::vec3(2, 0, 0)), 0.0},
        {getRotationMatrix(3.14, glm::vec3(2, 0, 0)), 1.0},
        {getRotationMatrix(3.14 * 2, glm::vec3(2, 0, 0)), 2.0},
        {getRotationMatrix(3.14 * 3, glm::vec3(2, 0, 0)), 3.0},
        {getRotationMatrix(3.14 * 4, glm::vec3(2, 0, 0)), 4.0},
        {getRotationMatrix(3.14 * 5, glm::vec3(2, 0, 0)), 5.0},
        {getRotationMatrix(3.14 * 6, glm::vec3(2, 0, 0)), 6.0},
        {getRotationMatrix(3.14 * 7, glm::vec3(2, 0, 0)), 7.0},
        {getRotationMatrix(3.14 * 7.5, glm::vec3(2, 0, 0)), 8.0},
        {getRotationMatrix(3.14 * 7.5, glm::vec3(2, 0, 0)), 14},
    };

    LightedMeshRenderablePtr traing = init_traing(phong_shader, 3, transformations);
    traing->addGlobalTransformKeyframe(getTranslationMatrix(30, 2, 25) * getScaleMatrix(1, 1, 1) * getRotationMatrix(3.14 / 2, glm::vec3(0, -1, 0)), 5);
    traing->addGlobalTransformKeyframe(getTranslationMatrix(-10, 2, 25) * getScaleMatrix(1, 1, 1) * getRotationMatrix(3.14 / 2, glm::vec3(0, -1, 0)), 7);
    traing->addGlobalTransformKeyframe(getTranslationMatrix(-20, 2, 25) * getScaleMatrix(1, 1, 1) * getRotationMatrix(3.14 / 2, glm::vec3(0, -1, 0)), 8);
    traing->addGlobalTransformKeyframe(getTranslationMatrix(-20, 2, 25) * getScaleMatrix(1, 1, 1) * getRotationMatrix(3.14 / 2, glm::vec3(0, -1, 0)), 14);

    viewer.addRenderable(traing);

    // Animate the camera
    Camera &camera = viewer.getCamera();
    camera.addGlobalTransformKeyframe(getTranslationMatrix(-26.5, 7, 43), 0);
    camera.addGlobalTransformKeyframe(getTranslationMatrix(-26.5, 7, 35), 5);
    camera.addGlobalTransformKeyframe(getTranslationMatrix(-26.5, 7, 35) * getRotationMatrix(3.14 / 8, glm::vec3(0, -1, 0)), 7);
    camera.addGlobalTransformKeyframe(getTranslationMatrix(-26.5, 7, 35) * getRotationMatrix(3.14 / 8, glm::vec3(0, -1, 0)), 14);

    // Lightning
    glm::vec3 dir = glm::normalize(glm::vec3(-1, -1, -1));
    glm::vec3 ambient = glm::vec3(0, 0, 0);
    glm::vec3 diffuse = glm::vec3(1, 1, 1);
    glm::vec3 specular = glm::vec3(1, 1, 1);
    DirectionalLightPtr light1 = std::make_shared<DirectionalLight>(dir, ambient, diffuse, specular);
    dir = glm::normalize(glm::vec3(1, -1, 1));
    ambient = glm::vec3(0, 0, 0);
    diffuse = glm::vec3(1, 1, 1);
    specular = glm::vec3(1, 1, 1);
    DirectionalLightPtr light2 = std::make_shared<DirectionalLight>(dir, ambient, diffuse, specular);
    dir = glm::normalize(glm::vec3(0, 1, 0));
    ambient = glm::vec3(0, 0, 0);
    diffuse = glm::vec3(1, 1, 1);
    specular = glm::vec3(1, 1, 1);
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
    glm::vec4 background_color(0.8, 0.8, 0.8, 1);
    Viewer viewer(1280, 720, background_color);

    scene2(viewer);

    while (viewer.isRunning())
    {
        viewer.handleEvent();
        viewer.animate();
        viewer.draw();
        viewer.display();
    }

    return EXIT_SUCCESS;
}