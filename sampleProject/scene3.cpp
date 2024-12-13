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
#include <texturing/TexturedLightedMeshRenderable.hpp>
#include <random>

const std::string texture_path = "../../assets/mtl/";

LightedMeshRenderablePtr init_tree1(ShaderProgramPtr phong_shader)
{
    // Add the tree
    const std::string tree_path = "../../assets/obj/tree.obj";
    std::vector<std::vector<glm::vec3>> all_positions_tree;
    std::vector<std::vector<glm::vec3>> all_normals_tree;
    std::vector<std::vector<glm::vec2>> all_texcoords_tree;
    std::vector<std::vector<unsigned int>> all_indices_tree;
    std::vector<MaterialPtr> materials_tree;

    read_obj_with_materials(tree_path, texture_path, all_positions_tree, all_normals_tree, all_texcoords_tree, materials_tree);

    int n_object_tree = materials_tree.size();
    std::vector<glm::vec4> colors_tree;

    LightedMeshRenderablePtr root_tree;

    root_tree = std::make_shared<LightedMeshRenderable>(
        phong_shader, all_positions_tree[0], all_normals_tree[0], colors_tree, materials_tree[0]);
    root_tree->setLocalTransform(
        getScaleMatrix(0.1, 0.1, 0.1));
    for (int i = 1; i < n_object_tree; ++i)
    {
        LightedMeshRenderablePtr part = std::make_shared<LightedMeshRenderable>(
            phong_shader, all_positions_tree[i], all_normals_tree[i], colors_tree, materials_tree[i]);
        HierarchicalRenderable::addChild(root_tree, part);
        part->setLocalTransform(
            getScaleMatrix(0.1, 0.1, 0.1));
    }

    return root_tree;
}

LightedMeshRenderablePtr init_tree2(ShaderProgramPtr phong_shader)
{
    // Add the tree
    const std::string tree_path = "../../assets/obj/tree2.obj";
    std::vector<std::vector<glm::vec3>> all_positions_tree;
    std::vector<std::vector<glm::vec3>> all_normals_tree;
    std::vector<std::vector<glm::vec2>> all_texcoords_tree;
    std::vector<std::vector<unsigned int>> all_indices_tree;
    std::vector<MaterialPtr> materials_tree;

    read_obj_with_materials(tree_path, texture_path, all_positions_tree, all_normals_tree, all_texcoords_tree, materials_tree);

    int n_object_tree = materials_tree.size();
    std::vector<glm::vec4> colors_tree;

    LightedMeshRenderablePtr root_tree;

    root_tree = std::make_shared<LightedMeshRenderable>(
        phong_shader, all_positions_tree[0], all_normals_tree[0], colors_tree, materials_tree[0]);
    root_tree->setLocalTransform(
        getScaleMatrix(0.2, 0.2, 0.2));
    for (int i = 1; i < n_object_tree; ++i)
    {
        LightedMeshRenderablePtr part = std::make_shared<LightedMeshRenderable>(
            phong_shader, all_positions_tree[i], all_normals_tree[i], colors_tree, materials_tree[i]);
        HierarchicalRenderable::addChild(root_tree, part);
        part->setLocalTransform(
            getScaleMatrix(0.2, 0.2, 0.2));
    }

    return root_tree;
}

TexturedMeshRenderablePtr init_pinguin(ShaderProgramPtr texShader, std::string image_path)
{
    // Add the pinguin
    const std::string pinguin_path = "../../assets/obj/pinguin.obj";

    TexturedMeshRenderablePtr root_pinguin = std::make_shared<TexturedMeshRenderable>(
        texShader, pinguin_path, image_path);

    return root_pinguin;
}

LightedMeshRenderablePtr init_rails(ShaderProgramPtr phong_shader)
{
    // Add the rails
    const std::string rails_path = "../../assets/obj/rails.obj";
    std::vector<std::vector<glm::vec3>> all_positions_rails;
    std::vector<std::vector<glm::vec3>> all_normals_rails;
    std::vector<std::vector<glm::vec2>> all_texcoords_rails;
    std::vector<std::vector<unsigned int>> all_indices_rails;
    std::vector<MaterialPtr> materials_rails;

    read_obj_with_materials(rails_path, texture_path, all_positions_rails, all_normals_rails, all_texcoords_rails, materials_rails);

    int n_object_rails = materials_rails.size();
    std::vector<glm::vec4> colors_rails;

    LightedMeshRenderablePtr root_rails;

    root_rails = std::make_shared<LightedMeshRenderable>(
        phong_shader, all_positions_rails[0], all_normals_rails[0], colors_rails, materials_rails[0]);
    for (int i = 1; i < n_object_rails; ++i)
    {
        LightedMeshRenderablePtr part = std::make_shared<LightedMeshRenderable>(
            phong_shader, all_positions_rails[i], all_normals_rails[i], colors_rails, materials_rails[i]);
        HierarchicalRenderable::addChild(root_rails, part);
    }

    return root_rails;
}

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

TexturedLightedMeshRenderablePtr init_ground(ShaderProgramPtr texShader, MaterialPtr material)
{
    // Add the ground
    const std::string ground_path = "../../assets/obj/ground2.obj";
    const std::string image_path = "./../../sfmlGraphicsPipeline/textures/grass_texture.png";

    TexturedLightedMeshRenderablePtr root_ground = std::make_shared<TexturedLightedMeshRenderable>(
        texShader, ground_path, material, image_path);

    return root_ground;
}

void scene3(Viewer &viewer)
{
    // Create a shader program
    ShaderProgramPtr phong_shader = std::make_shared<ShaderProgram>(
        "../../sfmlGraphicsPipeline/shaders/phongVertex.glsl",
        "../../sfmlGraphicsPipeline/shaders/phongFragment.glsl");
    ShaderProgramPtr flat_shader = std::make_shared<ShaderProgram>(
        "../../sfmlGraphicsPipeline/shaders/flatVertex.glsl",
        "../../sfmlGraphicsPipeline/shaders/flatFragment.glsl");
    ShaderProgramPtr texShader = std::make_shared<ShaderProgram>(
        "../../sfmlGraphicsPipeline/shaders/textureVertex.glsl",
        "../../sfmlGraphicsPipeline/shaders/textureFragment.glsl");
    ShaderProgramPtr cubeMapShader = std::make_shared<ShaderProgram>(
        "../../sfmlGraphicsPipeline/shaders/cubeMapVertex.glsl",
        "../../sfmlGraphicsPipeline/shaders/cubeMapFragment.glsl");

    // Add the shader program to the viewer
    viewer.addShaderProgram(phong_shader);
    viewer.addShaderProgram(flat_shader);
    viewer.addShaderProgram(texShader);
    viewer.addShaderProgram(cubeMapShader);

    std::string cubemap_dir = "../../sfmlGraphicsPipeline/textures/skybox";
    auto cubemap = std::make_shared<CubeMapRenderable>(cubeMapShader, cubemap_dir);
    viewer.addRenderable(cubemap);

    // Add the traing
    std::vector<std::pair<glm::mat4, float>> transformations = {
        {getRotationMatrix(0.0, glm::vec3(2, 0, 0)), 0.0},
        {getRotationMatrix(3.14, glm::vec3(2, 0, 0)), 1.0},
        {getRotationMatrix(3.14 * 2, glm::vec3(2, 0, 0)), 2.0}};

    LightedMeshRenderablePtr traing = init_traing(phong_shader, 3, transformations);
    traing->addGlobalTransformKeyframe(getTranslationMatrix(60, 0, -5) * getRotationMatrix(3.14 / 2, glm::vec3(0, -1, 0)), 0);
    traing->addGlobalTransformKeyframe(getTranslationMatrix(60, 0, -5) * getRotationMatrix(3.14 / 2, glm::vec3(0, -1, 0)), 3);
    traing->addGlobalTransformKeyframe(getTranslationMatrix(0, 0, -5) * getRotationMatrix(3.14 / 2, glm::vec3(0, -1, 0)), 6);
    traing->addGlobalTransformKeyframe(getTranslationMatrix(-60, 0, -5) * getRotationMatrix(3.14 / 2, glm::vec3(0, -1, 0)), 9);
    viewer.addRenderable(traing);

    // Add the ground
    int ground_pieces_x = 15;  // Number of ground pieces along the X-axis
    int ground_pieces_z = 10;  // Number of ground pieces along the Z-axis
    float ground_size = 10.0f; // Size of each ground piece

    // Random number generator for rotation angles and elevation variations
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 360.0);
    std::uniform_real_distribution<> dis_elevation(-1.0, 1.0); // Adjust the range for desired elevation variation
    std::uniform_real_distribution<> dis_tree(0.0, 1.0);       // Random distribution for tree spawning

    for (int i = 0; i < ground_pieces_x; ++i)
    {
        for (int j = 0; j < ground_pieces_z; ++j)
        {
            // for the 2 rows in the middle
            MaterialPtr material;
            float elevation = 0.0f;
            if (j < ground_pieces_z / 3)
            {
                elevation = (ground_pieces_z / 3 - j) * 2.0f;
                elevation += dis_elevation(gen);

                material = Material::Grass();
            }
            else if (j > 2 * ground_pieces_z / 3)
            {
                elevation = (j - 2 * ground_pieces_z / 3) * 2.0f;
                elevation += dis_elevation(gen);

                material = Material::Grass();
            }
            else
            {
                material = Material::Ground();
            }

            TexturedLightedMeshRenderablePtr ground = init_ground(texShader, material);
            glm::mat4 translation = getTranslationMatrix((i - ground_pieces_x / 2) * ground_size, elevation, (j - ground_pieces_z / 2) * ground_size);

            // Generate a random rotation angle
            float angle = dis(gen);
            glm::mat4 rotation = getRotationMatrix(glm::radians(angle), glm::vec3(0, 1, 0));

            // Apply translation and rotation
            ground->setLocalTransform(translation * rotation);
            viewer.addRenderable(ground);

            // 20% chance to spawn a tree in the outside areas
            if ((j <= ground_pieces_z / 3) && dis_tree(gen) < 0.3)
            {
                LightedMeshRenderablePtr tree;
                if (dis_tree(gen) < 0.5)
                {
                    tree = init_tree1(phong_shader);
                }
                else
                {
                    tree = init_tree2(phong_shader);
                }
                tree->setGlobalTransform(
                    getTranslationMatrix((i - ground_pieces_x / 2) * ground_size, elevation, (j - ground_pieces_z / 2) * ground_size));
                HierarchicalRenderable::addChild(ground, tree);
            }
        }
    }

    // Add the rails
    LightedMeshRenderablePtr rails = init_rails(phong_shader);
    rails->setGlobalTransform(getTranslationMatrix(0, 1.3, -5) * getScaleMatrix(4, 4, 4));
    viewer.addRenderable(rails);

    // Add a pinguin
    TexturedMeshRenderablePtr pinguin = init_pinguin(texShader, "../../assets/texture/pinguin_4.png");
    pinguin->addGlobalTransformKeyframe(getTranslationMatrix(5, 2.3, -5) * getRotationMatrix(3.14 / 4, glm::vec3(0, 1, 0)), 0);
    pinguin->addGlobalTransformKeyframe(getTranslationMatrix(5, 2.3, -5) * getRotationMatrix(3.14 / 4, glm::vec3(0, 1, 0)), 5.2);
    pinguin->addGlobalTransformKeyframe(getTranslationMatrix(5, 1.3, -5) * getRotationMatrix(3.14 / 2, glm::vec3(0, -0.5, 1)), 5.4);
    pinguin->addGlobalTransformKeyframe(getTranslationMatrix(5, 1.3, -5) * getRotationMatrix(3.14 / 2, glm::vec3(0, -0.5, 1)), 9);
    pinguin->setLocalTransform(getScaleMatrix(4, 4, 4));
    viewer.addRenderable(pinguin);

    // Move the camera
    Camera &camera = viewer.getCamera();
    camera.addGlobalTransformKeyframe(
        getTranslationMatrix(20, 9, 10) * getRotationMatrix(3.14 / 7, glm::vec3(-1, 0, 0)),
        0);
    camera.addGlobalTransformKeyframe(
        getTranslationMatrix(20, 9, 10) * getRotationMatrix(3.14 / 7, glm::vec3(-1, 0, 0)),
        6);
    camera.addGlobalTransformKeyframe(
        getTranslationMatrix(-40, 9, 10) * getRotationMatrix(3.14 / 7, glm::vec3(-1, 0, 0)),
        9);

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

    scene3(viewer);

    while (viewer.isRunning())
    {
        viewer.handleEvent();
        viewer.animate();
        viewer.draw();
        viewer.display();
    }

    return EXIT_SUCCESS;
}