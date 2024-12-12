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
#include <texturing/TexturedLightedMeshRenderable.hpp>
#include <FrameRenderable.hpp>

const std::string texture_path = "../../good/mtl/";



LightedMeshRenderablePtr init_pinguin_glasses(ShaderProgramPtr phong_shader) {
    // Add the pinguin glasses
    const std::string pinguin_glasses_path = "../../good/obj/lunettes_eclair.obj";
    std::vector<std::vector<glm::vec3>> all_positions_pinguin_glasses;
    std::vector<std::vector<glm::vec3>> all_normals_pinguin_glasses;
    std::vector<std::vector<glm::vec2>> all_texcoords_pinguin_glasses;
    std::vector<std::vector<unsigned int>> all_indices_pinguin_glasses;
    std::vector<MaterialPtr> materials_pinguin_glasses;

    read_obj_with_materials(pinguin_glasses_path, texture_path, all_positions_pinguin_glasses, all_normals_pinguin_glasses, all_texcoords_pinguin_glasses, materials_pinguin_glasses);

    int n_object_pinguin_glasses = materials_pinguin_glasses.size();
    std::vector<glm::vec4> colors_pinguin_glasses;

    LightedMeshRenderablePtr root_pinguin_glasses;

    root_pinguin_glasses = std::make_shared<LightedMeshRenderable>(
        phong_shader, all_positions_pinguin_glasses[0], all_normals_pinguin_glasses[0], colors_pinguin_glasses, materials_pinguin_glasses[0]);
    for (int i = 1 ; i < n_object_pinguin_glasses ; ++i){
        LightedMeshRenderablePtr part = std::make_shared<LightedMeshRenderable>(
        phong_shader, all_positions_pinguin_glasses[i], all_normals_pinguin_glasses[i], colors_pinguin_glasses, materials_pinguin_glasses[i]);
        HierarchicalRenderable::addChild(root_pinguin_glasses, part);
    }

    return root_pinguin_glasses;
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

    root_roues_avant->setGlobalTransform(getTranslationMatrix(0, 0.2, 0.9));

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

    root_roues_arriere->setGlobalTransform(getTranslationMatrix(0, 0.2, -0.7));

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
    pinguin->setGlobalTransform(getTranslationMatrix(0, 0.4, 0.1));
    pinguin->setLocalTransform(getScaleMatrix(4, 4, 4));
    HierarchicalRenderable::addChild(root, pinguin);

    return root;
}

LightedMeshRenderablePtr init_wand(ShaderProgramPtr phong_shader, std::string path) {
    // Add the wand1
    const std::string wand1_path = path;
    std::vector<std::vector<glm::vec3>> all_positions_wand1;
    std::vector<std::vector<glm::vec3>> all_normals_wand1;
    std::vector<std::vector<glm::vec2>> all_texcoords_wand1;
    std::vector<std::vector<unsigned int>> all_indices_wand1;
    std::vector<MaterialPtr> materials_wand1;

    read_obj_with_materials(wand1_path, texture_path, all_positions_wand1, all_normals_wand1, all_texcoords_wand1, materials_wand1);

    int n_object_wand1 = materials_wand1.size();
    std::vector<glm::vec4> colors_wand1;

    LightedMeshRenderablePtr root_wand1;

    root_wand1 = std::make_shared<LightedMeshRenderable>(
        phong_shader, all_positions_wand1[0], all_normals_wand1[0], colors_wand1, materials_wand1[0]);
    for (int i = 1; i < n_object_wand1; ++i) {
        LightedMeshRenderablePtr part = std::make_shared<LightedMeshRenderable>(
            phong_shader, all_positions_wand1[i], all_normals_wand1[i], colors_wand1, materials_wand1[i]);
        HierarchicalRenderable::addChild(root_wand1, part);
    }

    return root_wand1;
}

TexturedLightedMeshRenderablePtr init_wand2(ShaderProgramPtr texShader) {
    // Add the wand2
    const std::string wand2_path = "../../good/obj/wand4withpng.obj";
    const std::string image_path = "../../good/texture/wand.jpeg";

    TexturedLightedMeshRenderablePtr root_wand2 = std::make_shared<TexturedLightedMeshRenderable>(
        texShader, wand2_path, Material::Bronze(), image_path
    );

    return root_wand2;
}

TexturedLightedMeshRenderablePtr init_traing_interior(ShaderProgramPtr texShader, ShaderProgramPtr phong_shader, ShaderProgramPtr flat_shader) {
    // Add the traing interior Interior_baseColor
    const std::string traing_interior_path = "../../good/obj/interieur_wagon.obj";
    const std::string image_path = "../../good/texture/Interior_baseColor.png";

    TexturedLightedMeshRenderablePtr root_traing_interior = std::make_shared<TexturedLightedMeshRenderable>(
        texShader, traing_interior_path, Material::Bronze(), image_path
    );

    // Add the glass (LightedMeshRenderable)
    /*const std::string glass_path = "../../good/obj/vitres_wagon.obj";
    std::vector<std::vector<glm::vec3>> all_positions_glass;
    std::vector<std::vector<glm::vec3>> all_normals_glass;
    std::vector<std::vector<glm::vec2>> all_texcoords_glass;
    std::vector<std::vector<unsigned int>> all_indices_glass;
    std::vector<MaterialPtr> materials_glass;

    read_obj_with_materials(glass_path, texture_path, all_positions_glass, all_normals_glass, all_texcoords_glass, materials_glass);

    int n_object_glass = materials_glass.size();
    std::vector<glm::vec4> colors_glass;

    LightedMeshRenderablePtr root_glass;
    
    root_glass = std::make_shared<LightedMeshRenderable>(
        phong_shader, all_positions_glass[0], all_normals_glass[0], colors_glass, Material::Glass());
    for (int i = 1; i < n_object_glass; ++i) {
        LightedMeshRenderablePtr part = std::make_shared<LightedMeshRenderable>(
            phong_shader, all_positions_glass[i], all_normals_glass[i], colors_glass, Material::Glass());
        HierarchicalRenderable::addChild(root_glass, part);
    }

    HierarchicalRenderable::addChild(root_traing_interior, root_glass);*/

    // Add a plan as door 
    glm::vec3 p1(1.0, 3.0, -9.3), p2(1.0, 1.0, -9.3), p3(-1.0, 1.0, -9.3), p4(-1.0, 3.0, -9.3);
    QuadMeshRenderablePtr planeRenderable = std::make_shared<QuadMeshRenderable>(flat_shader, p1, p2, p3, p4, glm::vec4(0.0, 0.0, 0.0, 1.0));
    HierarchicalRenderable::addChild( root_traing_interior, planeRenderable );

    // Add penguins as characters
    std::vector<glm::vec3> penguin_positions = {
        glm::vec3(0.8, 1.8, -6.3),
        glm::vec3(-0.8, 1.8, -6.3),
        glm::vec3(0.8, 1.8, -4.3),
        glm::vec3(-0.8, 1.8, -4.3)
    };

    int i = 0;

    for (const auto& pos : penguin_positions) {
        TexturedMeshRenderablePtr penguin = init_pinguin(texShader, "../../good/texture/pinguin_" + std::to_string(i+1) + ".png");
        glm::mat4 translation = getTranslationMatrix(pos.x, pos.y, pos.z);
        HierarchicalRenderable::addChild(root_traing_interior, penguin);

        // Add a wand to the penguin
        if (i == 0) {
            LightedMeshRenderablePtr wand1 = init_wand(phong_shader, "../../good/obj/wand3.obj");
            wand1->addGlobalTransformKeyframe(translation * getRotationMatrix(3.14 / 24, glm::vec3(0, 0, 1)), 0);
            wand1->addGlobalTransformKeyframe(translation * getRotationMatrix(-3.14 / 24, glm::vec3(0, 0, 1)), 1);
            wand1->addGlobalTransformKeyframe(translation * getRotationMatrix(3.14 / 24, glm::vec3(0, 0, 1)), 2);
            HierarchicalRenderable::addChild(penguin, wand1);
        } else if (i == 1) {
            TexturedLightedMeshRenderablePtr wand2 = init_wand2(texShader);
            wand2->addGlobalTransformKeyframe(translation * getRotationMatrix(3.14 / 24, glm::vec3(0, 0, 1)), 0);
            wand2->addGlobalTransformKeyframe(translation * getRotationMatrix(-3.14 / 24, glm::vec3(0, 0, 1)), 1);
            wand2->addGlobalTransformKeyframe(translation * getRotationMatrix(3.14 / 24, glm::vec3(0, 0, 1)), 2);
            HierarchicalRenderable::addChild(penguin, wand2);
        } else if (i == 2) {
            LightedMeshRenderablePtr wand3 = init_wand(phong_shader, "../../good/obj/wand2.obj");
            wand3->addGlobalTransformKeyframe(translation * getRotationMatrix(3.14 / 24, glm::vec3(0, 0, 1)), 0);
            wand3->addGlobalTransformKeyframe(translation * getRotationMatrix(-3.14 / 24, glm::vec3(0, 0, 1)), 1);
            wand3->addGlobalTransformKeyframe(translation * getRotationMatrix(3.14 / 24, glm::vec3(0, 0, 1)), 2);
            HierarchicalRenderable::addChild(penguin, wand3);
        }else if (i == 3) {
            LightedMeshRenderablePtr wand4 = init_wand(phong_shader, "../../good/obj/wand1.obj");
            wand4->addGlobalTransformKeyframe(translation * getRotationMatrix(3.14 / 24, glm::vec3(0, 0, 1)), 0);
            wand4->addGlobalTransformKeyframe(translation * getRotationMatrix(-3.14 / 24, glm::vec3(0, 0, 1)), 1);
            wand4->addGlobalTransformKeyframe(translation * getRotationMatrix(3.14 / 24, glm::vec3(0, 0, 1)), 2);
            HierarchicalRenderable::addChild(penguin, wand4);
            // Add the glasses
            LightedMeshRenderablePtr pinguin_glasses = init_pinguin_glasses(phong_shader);
            pinguin_glasses->addGlobalTransformKeyframe(translation * getRotationMatrix(3.14 / 24, glm::vec3(0, 0, 1))*getScaleMatrix(0.8, 0.8, 0.8), 0);
            pinguin_glasses->addGlobalTransformKeyframe(translation * getRotationMatrix(-3.14 / 24, glm::vec3(0, 0, 1))*getScaleMatrix(0.8, 0.8, 0.8), 1);
            pinguin_glasses->addGlobalTransformKeyframe(translation * getRotationMatrix(3.14 / 24, glm::vec3(0, 0, 1))*getScaleMatrix(0.8, 0.8, 0.8), 2);
            HierarchicalRenderable::addChild(penguin, pinguin_glasses);
        } 

        penguin->addLocalTransformKeyframe(translation * getRotationMatrix(3.14 / 24, glm::vec3(0, 0, 1))*getScaleMatrix(0.8, 0.8, 0.8), 0);
        penguin->addLocalTransformKeyframe(translation * getRotationMatrix(-3.14 / 24, glm::vec3(0, 0, 1))*getScaleMatrix(0.8, 0.8, 0.8), 1);
        penguin->addLocalTransformKeyframe(translation * getRotationMatrix(3.14 / 24, glm::vec3(0, 0, 1))*getScaleMatrix(0.8, 0.8, 0.8), 2);
        i ++;
    }
    
    return root_traing_interior;
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
    ShaderProgramPtr texShader = std::make_shared<ShaderProgram>(
        "../../sfmlGraphicsPipeline/shaders/textureVertex.glsl",
        "../../sfmlGraphicsPipeline/shaders/textureFragment.glsl");

    // Add the shader program to the viewer
    viewer.addShaderProgram( texShader );
    viewer.addShaderProgram( phong_shader );

    viewer.getCamera().setViewMatrix( glm::lookAt( glm::vec3(1, 1, 1 ), glm::vec3(0, 0, 0), glm::vec3( 0, 1, 0 ) ) );
    ShaderProgramPtr cubeMapShader = std::make_shared<ShaderProgram>(  "../../sfmlGraphicsPipeline/shaders/cubeMapVertex.glsl",
                                                                "../../sfmlGraphicsPipeline/shaders/cubeMapFragment.glsl");
    viewer.addShaderProgram(cubeMapShader);
    
    std::string cubemap_dir = "../../sfmlGraphicsPipeline/textures/skybox";
    auto cubemap = std::make_shared<CubeMapRenderable>(cubeMapShader, cubemap_dir);

    viewer.addRenderable(cubemap);
        

    // Add the traing interior
    TexturedLightedMeshRenderablePtr traing = init_traing_interior(texShader, phong_shader, flat_shader);
    viewer.addRenderable(traing);

    // Add the car
    LightedMeshRenderablePtr car = init_car(phong_shader, texShader, true);
    car->addGlobalTransformKeyframe(getTranslationMatrix(-5, 2, -12)*getScaleMatrix(0.1, 0.1, 0.1)*getRotationMatrix(3.14/2, glm::vec3(0, 1, 0)), 0);
    car->addGlobalTransformKeyframe(getTranslationMatrix(-5, 2, 1)*getScaleMatrix(0.1, 0.1, 0.1)*getRotationMatrix(3.14/2, glm::vec3(0, 1, 0)), 10);
    viewer.addRenderable(car);

    // Move the camera
    Camera& camera = viewer.getCamera();

    camera.addGlobalTransformKeyframe(getTranslationMatrix(0.2, 2.6, -2.7)*getRotationMatrix(3.14/16, glm::vec3(0, 1, 0)),0);
    camera.addGlobalTransformKeyframe(getTranslationMatrix(0.2, 2.6, -2.7)*getRotationMatrix(3.14/2, glm::vec3(0, 1, 0)),10);


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