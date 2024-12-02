#include <Viewer.hpp>
#include <ShaderProgram.hpp>
#include <FrameRenderable.hpp>
#include <Io.hpp>
#include <lighting/LightedMeshRenderable.hpp>
#include <lighting/Light.hpp>


void initialize_scene( Viewer& viewer )
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

    const std::string obj_path = "../../good/obj/ossature.obj";
    const std::string mtl_basepath = "../../good/mtl/";

    std::vector<std::vector<glm::vec3>> all_positions;
    std::vector<std::vector<glm::vec3>> all_normals;
    std::vector<std::vector<glm::vec2>> all_texcoords;
    std::vector<std::vector<unsigned int>> all_indices;
    std::vector<MaterialPtr> materials;
    
    read_obj_with_materials(obj_path, mtl_basepath, all_positions, all_normals, all_texcoords, materials);
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

    viewer.addRenderable(root);

    // animate the object
    root->addGlobalTransformKeyframe(getTranslationMatrix(0, 0, 0), 0);
    root->addGlobalTransformKeyframe(getTranslationMatrix(-5, 0, 0), 2);
    root->addGlobalTransformKeyframe(getTranslationMatrix(-10, 0, 0), 4);
    root->addGlobalTransformKeyframe(getTranslationMatrix(-15, 0, 0), 6);
    root->addGlobalTransformKeyframe(getTranslationMatrix(-20, 0, 0), 8);
    

    // Add car roues avant
    const std::string roues_path = "../../good/obj/roues_voiture.obj";
    const std::string roues_texture_path = "../../good/mtl/";
    std::vector<std::vector<glm::vec3>> all_positions_roues_avant;
    std::vector<std::vector<glm::vec3>> all_normals_roues_avant;
    std::vector<std::vector<glm::vec2>> all_texcoords_roues_avant;
    std::vector<std::vector<unsigned int>> all_indices_roues;
    std::vector<MaterialPtr> materials_roues;

    read_obj_with_materials(roues_path, roues_texture_path, all_positions_roues_avant, all_normals_roues_avant, all_texcoords_roues_avant, materials_roues);

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
    root_roues_avant->addLocalTransformKeyframe(getRotationMatrix(0.0, glm::vec3(0, 0, 2)), 0.0);
    root_roues_avant->addLocalTransformKeyframe(getRotationMatrix(3.14, glm::vec3(0, 0, 2)), 1.0);
    root_roues_avant->addLocalTransformKeyframe(getRotationMatrix(3.14*2, glm::vec3(0, 0, 2)), 2.0);

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
    root_roues_arriere->addLocalTransformKeyframe(getRotationMatrix(0.0, glm::vec3(0, 0, 2)), 0.0);
    root_roues_arriere->addLocalTransformKeyframe(getRotationMatrix(3.14, glm::vec3(0, 0, 2)), 1.0);
    root_roues_arriere->addLocalTransformKeyframe(getRotationMatrix(3.14*2, glm::vec3(0, 0, 2)), 2.0);

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
	initialize_scene(viewer);

	while( viewer.isRunning() )
	{
		viewer.handleEvent();
		viewer.animate();
		viewer.draw();
		viewer.display();
	}	

	return EXIT_SUCCESS;
}