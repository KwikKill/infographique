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

const std::string texture_path = "../../good/mtl/";

void init_explosion(Viewer& viewer, ShaderProgramPtr phong_shader) {
    // Particules
    DynamicSystemPtr system = std::make_shared<DynamicSystem>();
    EulerExplicitSolverPtr solver = std::make_shared<EulerExplicitSolver>();
    system->setSolver(solver);
    system->setDt(0.01);

    //Create a renderable associated to the dynamic system
    //This renderable is responsible for calling DynamicSystem::computeSimulationStep() in the animate() function
    //It is also responsible for some of the key/mouse events
    DynamicSystemRenderablePtr systemRenderable = std::make_shared<DynamicSystemRenderable>(system);
    viewer.addRenderable(systemRenderable);

    //Populate the dynamic system with particles, forcefields and create renderables associated to them for visualization.
    ShaderProgramPtr instancedShader = std::make_shared<ShaderProgram>(
        "../../sfmlGraphicsPipeline/shaders/instancedVertex.glsl",
        "../../sfmlGraphicsPipeline/shaders/instancedFragment.glsl"
    );
    viewer.addShaderProgram( instancedShader );

    //Initialize particle attributes (radius, mass,position , velocity)
    float pr = 0.07, pm = 100.0;
    glm::vec3 px(20,5.0,-5.0), pv; 
    float particleSpeed = 8.0f;
    std::vector<ParticlePtr> particles(250);
    for (int i=0; i< particles.size(); ++i){
        float theta = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(2.0f*M_PI)));
        float phi = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(M_PI)));

        float x = sin(phi) * cos(theta);
        float y = sin(phi) * sin(theta);
        float z = cos(phi);

        // Get a random velocity
        pv = particleSpeed * glm::vec3(x, y, z);
        particles[i] = std::make_shared<Particle>( px, pv, pm, pr );
        system->addParticle(particles[i]);
    }

    //Initialize a force field that apply to all the particles of the system to simulate gravity
    //Add it to the system as a force field
    ConstantForceFieldPtr gravityForceField = std::make_shared<ConstantForceField>(system->getParticles(), DynamicSystem::gravity  );
    system->addForceField( gravityForceField );

    //Initialize a force field that apply to all the particles of the system to simulate vicosity (air friction)
    float dampingCoefficient = 7.0;
    DampingForceFieldPtr dampingForceField = std::make_shared<DampingForceField>(system->getParticles(), dampingCoefficient);
    system->addForceField(dampingForceField);

    //Create a particleListRenderable to efficiently visualize the particles of the system
    ParticleListRenderablePtr particleListRenderable = std::make_shared<ParticleListRenderable>( instancedShader, particles);
    particleListRenderable->setColor(glm::vec4(1,0,0,1));
    HierarchicalRenderable::addChild(systemRenderable, particleListRenderable);

    // Add an explosion object
    const std::string explosion_path = "../../good/obj/explosion.obj";
    std::vector<std::vector<glm::vec3>> all_positions_explosion;
    std::vector<std::vector<glm::vec3>> all_normals_explosion;
    std::vector<std::vector<glm::vec2>> all_texcoords_explosion;
    std::vector<std::vector<unsigned int>> all_indices_explosion;
    std::vector<MaterialPtr> materials_explosion;

    read_obj_with_materials(explosion_path, texture_path, all_positions_explosion, all_normals_explosion, all_texcoords_explosion, materials_explosion);

    int n_object_explosion = materials_explosion.size();
    std::vector<glm::vec4> colors_explosion;

    LightedMeshRenderablePtr root_explosion;

    root_explosion = std::make_shared<LightedMeshRenderable>(
        phong_shader, all_positions_explosion[0], all_normals_explosion[0], colors_explosion, materials_explosion[0]);
    for (int i = 1; i < n_object_explosion; ++i) {
        LightedMeshRenderablePtr part = std::make_shared<LightedMeshRenderable>(
            phong_shader, all_positions_explosion[i], all_normals_explosion[i], colors_explosion, materials_explosion[i]);
        HierarchicalRenderable::addChild(root_explosion, part);
    }
    root_explosion->addGlobalTransformKeyframe(
        getTranslationMatrix(30, 5.0, -5.0)
        *getScaleMatrix(0.1, 0.1, 0.1),
        0
    );
    root_explosion->addGlobalTransformKeyframe(
        getTranslationMatrix(20, 5.0, -5.0)
        *getScaleMatrix(1,1,1),
        1.7
    );
    root_explosion->addGlobalTransformKeyframe(
        getTranslationMatrix(20, 5.0, -5.0)
        *getScaleMatrix(0.01,0.01,0.01),
        2
    );
    root_explosion->addGlobalTransformKeyframe(
        getTranslationMatrix(20, 5.0, -5.0)
        *getScaleMatrix(0.01,0.01,0.01),
        5
    );

    viewer.addRenderable(root_explosion);
}

TexturedMeshRenderablePtr init_pinguin(ShaderProgramPtr texShader, std::string image_path) {
    // Add the pinguin
    const std::string pinguin_path = "../../good/obj/pinguin.obj";

    TexturedMeshRenderablePtr root_pinguin = std::make_shared<TexturedMeshRenderable>(
        texShader, pinguin_path, image_path
    );

    return root_pinguin;
}

LightedMeshRenderablePtr init_car ( ShaderProgramPtr phong_shader, ShaderProgramPtr texShader, bool rotation) {
    // Add the car
    const std::string obj_path = "../../good/obj/ossature.obj";
    std::vector<std::vector<glm::vec3>> all_positions;
    std::vector<std::vector<glm::vec3>> all_normals;
    std::vector<std::vector<glm::vec2>> all_texcoords;
    std::vector<std::vector<unsigned int>> all_indices;
    std::vector<MaterialPtr> materials;
    
    read_obj_with_materials(obj_path, texture_path, all_positions, all_normals, all_texcoords, materials);
    int n_object = materials.size();
    std::vector<glm::vec4> colors;
    
    LightedMeshRenderablePtr root;

    root = std::make_shared<LightedMeshRenderable>(
        phong_shader, all_positions[0], all_normals[0], colors, materials[0]);
    for (int i = 1 ; i < n_object ; ++i){
        LightedMeshRenderablePtr part = std::make_shared<LightedMeshRenderable>(
        phong_shader, all_positions[i], all_normals[i], colors, materials[i]);
        HierarchicalRenderable::addChild(root, part);
    }
    
    // Add car roues avant
    const std::string roues_path = "../../good/obj/roues_voiture.obj";
    std::vector<std::vector<glm::vec3>> all_positions_roues_avant;
    std::vector<std::vector<glm::vec3>> all_normals_roues_avant;
    std::vector<std::vector<glm::vec2>> all_texcoords_roues_avant;
    std::vector<std::vector<unsigned int>> all_indices_roues;
    std::vector<MaterialPtr> materials_roues;

    read_obj_with_materials(roues_path, texture_path, all_positions_roues_avant, all_normals_roues_avant, all_texcoords_roues_avant, materials_roues);

    int n_object_roues = materials_roues.size();
    std::vector<glm::vec4> colors_roues;

    LightedMeshRenderablePtr root_roues_avant;

    root_roues_avant = std::make_shared<LightedMeshRenderable>(
        phong_shader, all_positions_roues_avant[0], all_normals_roues_avant[0], colors_roues, materials_roues[0]);
    for (int i = 1 ; i < n_object_roues ; ++i){
        LightedMeshRenderablePtr part = std::make_shared<LightedMeshRenderable>(
        phong_shader, all_positions_roues_avant[i], all_normals_roues_avant[i], colors_roues, materials_roues[i]);
        HierarchicalRenderable::addChild(root_roues_avant, part);
    }

    // set the hierarchie
    HierarchicalRenderable::addChild(root, root_roues_avant);

    root_roues_avant->setGlobalTransform(getTranslationMatrix(3, 1, 0));

    // get the roues children
    std::vector<HierarchicalRenderablePtr> hierarchicalChildren = root_roues_avant->getChildren();
    std::vector<LightedMeshRenderablePtr> children;
    for (auto& child : hierarchicalChildren) {
        children.push_back(std::dynamic_pointer_cast<LightedMeshRenderable>(child));
    }
    for (int i = 0; i < children.size(); i++) {
        
        std::dynamic_pointer_cast<LightedMeshRenderable>(children[i])->addLocalTransformKeyframe(getRotationMatrix(0.0, glm::vec3(0, 0, 2)), 0.0);
        std::dynamic_pointer_cast<LightedMeshRenderable>(children[i])->addLocalTransformKeyframe(getRotationMatrix(3.14, glm::vec3(0, 0, 2)), 1.0);
        std::dynamic_pointer_cast<LightedMeshRenderable>(children[i])->addLocalTransformKeyframe(getRotationMatrix(3.14*2, glm::vec3(0, 0, 2)), 2.0);
    }

    // make the roues rotate
    if (rotation) {
        root_roues_avant->addLocalTransformKeyframe(getRotationMatrix(0.0, glm::vec3(0, 0, 2)), 0.0);
        root_roues_avant->addLocalTransformKeyframe(getRotationMatrix(3.14, glm::vec3(0, 0, 2)), 1.0);
        root_roues_avant->addLocalTransformKeyframe(getRotationMatrix(3.14*2, glm::vec3(0, 0, 2)), 2.0);
    }

    // Add car roues arriere
    LightedMeshRenderablePtr root_roues_arriere;

    root_roues_arriere = std::make_shared<LightedMeshRenderable>(
        phong_shader, all_positions_roues_avant[0], all_normals_roues_avant[0], colors_roues, materials_roues[0]);
    for (int i = 1 ; i < n_object_roues ; ++i){
        LightedMeshRenderablePtr part = std::make_shared<LightedMeshRenderable>(
        phong_shader, all_positions_roues_avant[i], all_normals_roues_avant[i], colors_roues, materials_roues[i]);
        HierarchicalRenderable::addChild(root_roues_arriere, part);
    }

    // set the hierarchie
    HierarchicalRenderable::addChild(root, root_roues_arriere);

    root_roues_arriere->setGlobalTransform(getTranslationMatrix(-3.8, 1, 0));

    // get the roues children
    std::vector<HierarchicalRenderablePtr> hierarchicalChildren2 = root_roues_arriere->getChildren();
    std::vector<LightedMeshRenderablePtr> children2;
    for (auto& child : hierarchicalChildren2) {
        children2.push_back(std::dynamic_pointer_cast<LightedMeshRenderable>(child));
    }
    for (int i = 0; i < children2.size(); i++) {
        
        std::dynamic_pointer_cast<LightedMeshRenderable>(children2[i])->addLocalTransformKeyframe(getRotationMatrix(0.0, glm::vec3(0, 0, 2)), 0.0);
        std::dynamic_pointer_cast<LightedMeshRenderable>(children2[i])->addLocalTransformKeyframe(getRotationMatrix(3.14, glm::vec3(0, 0, 2)), 1.0);
        std::dynamic_pointer_cast<LightedMeshRenderable>(children2[i])->addLocalTransformKeyframe(getRotationMatrix(3.14*2, glm::vec3(0, 0, 2)), 2.0);
    }

    // make the roues rotate
    if (rotation) {
        root_roues_arriere->addLocalTransformKeyframe(getRotationMatrix(0.0, glm::vec3(0, 0, 2)), 0.0);
        root_roues_arriere->addLocalTransformKeyframe(getRotationMatrix(3.14, glm::vec3(0, 0, 2)), 1.0);
        root_roues_arriere->addLocalTransformKeyframe(getRotationMatrix(3.14*2, glm::vec3(0, 0, 2)), 2.0);
    }

    // Add a pinguin in the car
    TexturedMeshRenderablePtr pinguin = init_pinguin(texShader, "../../good/texture/pinguin_1.png");
    pinguin->addGlobalTransformKeyframe(getTranslationMatrix(0, 2, 0.1), 0);
    pinguin->addGlobalTransformKeyframe(getTranslationMatrix(0, 1, 2), 1.7);
    pinguin->addGlobalTransformKeyframe(getTranslationMatrix(0, 1, 2), 5);

    pinguin->setLocalTransform(getScaleMatrix(4, 4, 4));
    HierarchicalRenderable::addChild(root, pinguin);

    return root;
}

LightedMeshRenderablePtr init_rails(ShaderProgramPtr phong_shader) {
    // Add the rails
    const std::string rails_path = "../../good/obj/rails.obj";
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
    for (int i = 1; i < n_object_rails; ++i) {
        LightedMeshRenderablePtr part = std::make_shared<LightedMeshRenderable>(
            phong_shader, all_positions_rails[i], all_normals_rails[i], colors_rails, materials_rails[i]);
        HierarchicalRenderable::addChild(root_rails, part);
    }

    return root_rails;
}

LightedMeshRenderablePtr init_traing_wheels(const std::string& path, const std::string& texture_path, ShaderProgramPtr shader, glm::vec3 translation, const std::vector<std::pair<glm::mat4, float>>& transformations) {
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
    for (int i = 1; i < n_objects; ++i) {
        LightedMeshRenderablePtr part = std::make_shared<LightedMeshRenderable>(
            shader, all_positions[i], all_normals[i], colors, materials[i]);
        HierarchicalRenderable::addChild(root, part);
    }

    root->setGlobalTransform(getTranslationMatrix(translation.x, translation.y, translation.z));

    for (const auto& transform : transformations) {
        root->addLocalTransformKeyframe(transform.first, transform.second);
    }

    return root;
}

LightedMeshRenderablePtr init_wagon( ShaderProgramPtr phong_shader) {
    // Add the car
    const std::string wagon_path = "../../good/obj/wagon.obj";
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
    for (int i = 1 ; i < n_object_wagon ; ++i){
        LightedMeshRenderablePtr part = std::make_shared<LightedMeshRenderable>(
        phong_shader, all_positions_wagon[i], all_normals_wagon[i], colors_wagon, materials_wagon[i]);
        HierarchicalRenderable::addChild(root_wagon, part);
    }

    return root_wagon;
}

LightedMeshRenderablePtr init_traing(ShaderProgramPtr phong_shader, int nb_wagon, const std::vector<std::pair<glm::mat4, float>>& transformations) {
    // Add the traing
    const std::string traing_path = "../../good/obj/ossature_train_finale.obj";
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
    for (int i = 1; i < n_object_traing; ++i) {
        LightedMeshRenderablePtr part = std::make_shared<LightedMeshRenderable>(
            phong_shader, all_positions_traing[i], all_normals_traing[i], colors_traing, materials_traing[i]);
        HierarchicalRenderable::addChild(root_traing, part);
    }

    const std::string roues_traing_path = "../../good/obj/petites_roues_train.obj";
    const std::string roues_arriere_traing_path = "../../good/obj/grandes_roues_train.obj";
    std::vector<glm::vec3> translations = {
        glm::vec3(-5.3, 2, -0.1),
        glm::vec3(-1, 2, -0.1),
        glm::vec3(2.2, 3, -0.1),
        glm::vec3(6.4, 3, -0.1),
        glm::vec3(11, 3, -0.1)
    };

    for (int i = 0; i < translations.size(); ++i) {
        std::string path = (i < 2) ? roues_traing_path : roues_arriere_traing_path;
        LightedMeshRenderablePtr wheels = init_traing_wheels(path, texture_path, phong_shader, translations[i], transformations);
        HierarchicalRenderable::addChild(root_traing, wheels);
    }

    // Add wagons behind the train
    LightedMeshRenderablePtr previous_wagon = root_traing;
    if (nb_wagon >= 1) {
        LightedMeshRenderablePtr wagon = init_wagon(phong_shader);
        glm::mat4 translation = getTranslationMatrix(25, 2, 0);
        wagon->setGlobalTransform(translation);
        HierarchicalRenderable::addChild(previous_wagon, wagon);
        previous_wagon = wagon;
    }

    for (int i = 1; i < nb_wagon; ++i) {
        LightedMeshRenderablePtr wagon = init_wagon(phong_shader);
        glm::mat4 translation = getTranslationMatrix(33, 0, 0);
        wagon->setGlobalTransform(translation);
        HierarchicalRenderable::addChild(previous_wagon, wagon);
        previous_wagon = wagon;
    }

    return root_traing;
}

LightedMeshRenderablePtr init_bridge(ShaderProgramPtr phong_shader) {
    // Add the bridge
    const std::string bridge_path = "../../good/obj/pont.obj";
    std::vector<std::vector<glm::vec3>> all_positions_bridge;
    std::vector<std::vector<glm::vec3>> all_normals_bridge;
    std::vector<std::vector<glm::vec2>> all_texcoords_bridge;
    std::vector<std::vector<unsigned int>> all_indices_bridge;
    std::vector<MaterialPtr> materials_bridge;

    read_obj_with_materials(bridge_path, texture_path, all_positions_bridge, all_normals_bridge, all_texcoords_bridge, materials_bridge);

    int n_object_bridge = materials_bridge.size();
    std::vector<glm::vec4> colors_bridge;

    LightedMeshRenderablePtr root_bridge;

    root_bridge = std::make_shared<LightedMeshRenderable>(
        phong_shader, all_positions_bridge[0], all_normals_bridge[0], colors_bridge, materials_bridge[0]);
    for (int i = 1; i < n_object_bridge; ++i) {
        LightedMeshRenderablePtr part = std::make_shared<LightedMeshRenderable>(
            phong_shader, all_positions_bridge[i], all_normals_bridge[i], colors_bridge, materials_bridge[i]);
        HierarchicalRenderable::addChild(root_bridge, part);
    }

    return root_bridge;
}

TexturedLightedMeshRenderablePtr init_ground(ShaderProgramPtr texShader, MaterialPtr material) {
    // Add the ground
    const std::string ground_path = "../../good/obj/ground2.obj";
    const std::string image_path = "./../../sfmlGraphicsPipeline/textures/grass_texture.png";

    TexturedLightedMeshRenderablePtr root_ground = std::make_shared<TexturedLightedMeshRenderable>(
        texShader, ground_path, material, image_path
    );

    return root_ground;
}

void scene6( Viewer& viewer )
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

    // Add the shader program to the viewer
    viewer.addShaderProgram( phong_shader );
    viewer.addShaderProgram( flat_shader );
    viewer.addShaderProgram( texShader );

    ShaderProgramPtr cubeMapShader = std::make_shared<ShaderProgram>(
        "../../sfmlGraphicsPipeline/shaders/cubeMapVertex.glsl",
        "../../sfmlGraphicsPipeline/shaders/cubeMapFragment.glsl"
    );
    viewer.addShaderProgram(cubeMapShader);
    
    std::string cubemap_dir = "../../sfmlGraphicsPipeline/textures/skybox";
    auto cubemap = std::make_shared<CubeMapRenderable>(cubeMapShader, cubemap_dir);
    viewer.addRenderable(cubemap);

    // Add the traing
    std::vector<std::pair<glm::mat4, float>> transformations = {
        {getRotationMatrix(0.0, glm::vec3(2, 0, 0)), 0.0},
        {getRotationMatrix(3.14, glm::vec3(2, 0, 0)), 1.0},
        {getRotationMatrix(3.14 * 2, glm::vec3(2, 0, 0)), 2.0}
    };

    LightedMeshRenderablePtr traing = init_traing(phong_shader, 3, transformations);
    traing->addGlobalTransformKeyframe(
        getTranslationMatrix(20, 0, -5)*getRotationMatrix(3.14/2, glm::vec3(0, -1, 0)),
        0
    );
    traing->addGlobalTransformKeyframe(
        getTranslationMatrix(15, 0, -5)*getRotationMatrix(3.14/2, glm::vec3(0, -1, 0)),
        0.5
    );
    traing->addGlobalTransformKeyframe(
        getTranslationMatrix(10, 1, 0)*getRotationMatrix(3.14/2, glm::vec3(0, -1, 0))*getRotationMatrix(3.14/3, glm::vec3(0, 0, -1)),
        1.5
    );
    traing->addGlobalTransformKeyframe(
        getTranslationMatrix(10, 1, 0)*getRotationMatrix(3.14/2, glm::vec3(0, -1, 0))*getRotationMatrix(3.14/3, glm::vec3(0, 0, -1)),
        5
    );
    viewer.addRenderable(traing);

    // Add the ground
    int ground_pieces_x = 15; // Number of ground pieces along the X-axis
    int ground_pieces_z = 10; // Number of ground pieces along the Z-axis
    float ground_size = 10.0f; // Size of each ground piece

    // Random number generator for rotation angles
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 360.0);
    std::uniform_real_distribution<> dis_elevation(-1.0, 1.0); // Adjust the range for desired elevation variation

    for (int i = 0; i < ground_pieces_x; ++i) {
        for (int j = 0; j < ground_pieces_z; ++j) {
            // for the 2 rows in the middle
            MaterialPtr material;
            float elevation = 0.0f;
            if (j < ground_pieces_z / 3) {
                elevation = (ground_pieces_z / 3 - j) * 2.0f;
                elevation += dis_elevation(gen);

                material = Material::Grass();
            } else if (j > 2 * ground_pieces_z / 3) {
                elevation = (j - 2 * ground_pieces_z / 3) * 2.0f;
                elevation += dis_elevation(gen);

                material = Material::Grass();
            } else {
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
        }
    }

    // Add the rails
    LightedMeshRenderablePtr rails = init_rails(phong_shader);
    rails->setGlobalTransform(getTranslationMatrix(0, 1.3, -5)*getScaleMatrix(4, 4, 4));
    viewer.addRenderable(rails);

    // Add the car
    LightedMeshRenderablePtr car = init_car(phong_shader, texShader, true);
    
    car->addGlobalTransformKeyframe(
        getTranslationMatrix(30, 2, -15)*getScaleMatrix(0.4, 0.4, 0.4),
        0
    );
    car->addGlobalTransformKeyframe(
        getTranslationMatrix(20, 2, -5)
        *getScaleMatrix(0.4, 0.4, 0.4)
        *getRotationMatrix(3.14/4, glm::vec3(1, 0, 0)),
        1.5
    );
    car->addGlobalTransformKeyframe(
        getTranslationMatrix(19, 2, -5)
        *getScaleMatrix(0.4, 0.4, 0.4)
        *getRotationMatrix(3.14/2, glm::vec3(1, 0, 0)),
        1.7
    );
    car->addGlobalTransformKeyframe(
        getTranslationMatrix(16, 2, -5)
        *getScaleMatrix(0.4, 0.4, 0.4)
        *getRotationMatrix(3.14/2, glm::vec3(1, 0, 0)),
        3
    );
    car->addGlobalTransformKeyframe(
        getTranslationMatrix(15, 2, -5)
        *getScaleMatrix(0.4, 0.4, 0.4)
        *getRotationMatrix(3.14/2, glm::vec3(1, 0, 0)),
        4
    );
    car->addGlobalTransformKeyframe(
        getTranslationMatrix(14.5, 2, -5)
        *getScaleMatrix(0.4, 0.4, 0.4)
        *getRotationMatrix(3.14/2, glm::vec3(1, 0, 0)),
        5
    );
    viewer.addRenderable(car);

    // Move the camera
    Camera& camera = viewer.getCamera();
    camera.addGlobalTransformKeyframe(
        getTranslationMatrix(37, 25, -10)
        *getRotationMatrix(3.14/2, glm::vec3(-1, 0, 0)),
        0
    );
    camera.addGlobalTransformKeyframe(
        getTranslationMatrix(27, 25, -10)
        *getRotationMatrix(3.14/2, glm::vec3(-1, 0, 0)),
        1.5
    );
    camera.addGlobalTransformKeyframe(
        getTranslationMatrix(27, 25, -10)
        *getRotationMatrix(3.14/2, glm::vec3(-1, 0, 0)),
        5
    );

    // create explosion
    init_explosion(viewer, phong_shader);

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
	
    scene6(viewer);

	while( viewer.isRunning() )
	{
		viewer.handleEvent();
		viewer.animate();
		viewer.draw();
		viewer.display();
	}	

	return EXIT_SUCCESS;
}