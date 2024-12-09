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

LightedMeshRenderablePtr init_car ( ShaderProgramPtr phong_shader, bool rotation) {
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

    root_roues_avant->setGlobalTransform(getTranslationMatrix(6.8, 2, 0));

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

    root_roues_arriere->setGlobalTransform(getTranslationMatrix(-9.3, 2, 0));

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

    return root;
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

void scene3( Viewer& viewer )
{
    // Create a shader program
	ShaderProgramPtr phong_shader = std::make_shared<ShaderProgram>(
        "../../sfmlGraphicsPipeline/shaders/phongVertex.glsl",
        "../../sfmlGraphicsPipeline/shaders/phongFragment.glsl");
	ShaderProgramPtr flat_shader = std::make_shared<ShaderProgram>(
        "../../sfmlGraphicsPipeline/shaders/flatVertex.glsl",
        "../../sfmlGraphicsPipeline/shaders/flatFragment.glsl");

    // Add the shader program to the viewer
    viewer.addShaderProgram( phong_shader );

    // Add the car
    LightedMeshRenderablePtr car = init_car(phong_shader, true);
    // animate the car
    car->addGlobalTransformKeyframe(getTranslationMatrix(0, 0, 0), 0);
    car->addGlobalTransformKeyframe(getTranslationMatrix(-5, 0, 0), 2);
    car->addGlobalTransformKeyframe(getTranslationMatrix(-10, 0, 0), 4);
    car->addGlobalTransformKeyframe(getTranslationMatrix(-15, 0, 0), 6);
    car->addGlobalTransformKeyframe(getTranslationMatrix(-20, 0, 0), 8);
    viewer.addRenderable(car);

    // Add the traing
    std::vector<std::pair<glm::mat4, float>> transformations = {
        {getRotationMatrix(0.0, glm::vec3(2, 0, 0)), 0.0},
        {getRotationMatrix(3.14, glm::vec3(2, 0, 0)), 1.0},
        {getRotationMatrix(3.14 * 2, glm::vec3(2, 0, 0)), 2.0}
    };

    LightedMeshRenderablePtr traing = init_traing(phong_shader, 3, transformations);
    viewer.addRenderable(traing);

    // Lightning
    glm::vec3 dir = glm::normalize(glm::vec3(-1,-1,-1));
    glm::vec3 ambient = glm::vec3(0,0,0);
    glm::vec3 diffuse = glm::vec3(1,1,1);
    glm::vec3 specular = glm::vec3(1,1,1);
    DirectionalLightPtr light1 = std::make_shared<DirectionalLight>(dir, ambient, diffuse, specular);
    dir = glm::normalize(glm::vec3(1,-1,1));
    ambient = glm::vec3(0,0,0);
    diffuse = glm::vec3(1,0.9,0.9);
    specular = glm::vec3(1,0.9,0.9);
    DirectionalLightPtr light2 = std::make_shared<DirectionalLight>(dir, ambient, diffuse, specular);
    dir = glm::normalize(glm::vec3(0,1,0));
    ambient = glm::vec3(0,0,0);
    diffuse = glm::vec3(0.5,0.3,0.3);
    specular = glm::vec3(0.5,0.3,0.3);
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
	
    scene3(viewer);

	while( viewer.isRunning() )
	{
		viewer.handleEvent();
		viewer.animate();
		viewer.draw();
		viewer.display();
	}	

	return EXIT_SUCCESS;
}