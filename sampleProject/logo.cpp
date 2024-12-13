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

const std::string texture_path = "../../assets/mtl/";

LightedMeshRenderablePtr init_logo(ShaderProgramPtr phong_shader) {
    // Add the logo
    const std::string logo_path = "../../assets/obj/logo.obj";
    std::vector<std::vector<glm::vec3>> all_positions_logo;
    std::vector<std::vector<glm::vec3>> all_normals_logo;
    std::vector<std::vector<glm::vec2>> all_texcoords_logo;
    std::vector<std::vector<unsigned int>> all_indices_logo;
    std::vector<MaterialPtr> materials_logo;

    read_obj_with_materials(logo_path, texture_path, all_positions_logo, all_normals_logo, all_texcoords_logo, materials_logo);

    int n_object_logo = materials_logo.size();
    std::vector<glm::vec4> colors_logo;

    LightedMeshRenderablePtr root_logo;

    root_logo = std::make_shared<LightedMeshRenderable>(
        phong_shader, all_positions_logo[0], all_normals_logo[0], colors_logo, Material::Gold());
    for (int i = 1; i < n_object_logo; ++i) {
        LightedMeshRenderablePtr part = std::make_shared<LightedMeshRenderable>(
            phong_shader, all_positions_logo[i], all_normals_logo[i], colors_logo, Material::Gold());
        HierarchicalRenderable::addChild(root_logo, part);
    }

    return root_logo;
}

void logo ( Viewer& viewer) {
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
    viewer.addShaderProgram( phong_shader );
    viewer.addShaderProgram( flat_shader );
    
    std::string cubemap_dir = "../../sfmlGraphicsPipeline/textures/skybox2";
    auto cubemap = std::make_shared<CubeMapRenderable>(cubeMapShader, cubemap_dir);
    viewer.addRenderable(cubemap);

    // Add the logo
    LightedMeshRenderablePtr logo = init_logo(phong_shader);
    logo->setGlobalTransform(getTranslationMatrix(0, 0, -80)*getScaleMatrix(100,100,100));
    viewer.addRenderable(logo);

    // Move the camera
    Camera& camera = viewer.getCamera();
    
    camera.addGlobalTransformKeyframe(getTranslationMatrix(0, 0, -40), 0);
    camera.addGlobalTransformKeyframe(getTranslationMatrix(0, 0, -20), 5);

    // Add a spotlight behind the camera
    glm::vec3 s_position(0.0,0.0,0.0);
    glm::vec3 s_spotDirection = glm::normalize(glm::vec3(0.0,0.0,-1.0));
    //glm::vec3 s_ambient(0.0,0.0,0.0), s_diffuse(0.0,0.0,0.0), s_specular(0.0,0.0,0.0);
    glm::vec3 s_ambient(0.0,0.0,0.0), s_diffuse(0.5,0.5,0.5), s_specular(0.5,0.5,0.5);
    float s_constant=1.0, s_linear=0.0, s_quadratic=0.0;
    float s_innerCutOff=std::cos(glm::radians(20.0f)), s_outerCutOff=std::cos(glm::radians(40.0f));
    SpotLightPtr spotLight = std::make_shared<SpotLight>(s_position, s_spotDirection,
                                                         s_ambient, s_diffuse, s_specular,
                                                         s_constant, s_linear, s_quadratic,
                                                         s_innerCutOff, s_outerCutOff);
    SpotLightRenderablePtr spotLightRenderable = std::make_shared<SpotLightRenderable>(flat_shader, spotLight);
    spotLightRenderable->setLocalTransform(glm::scale(glm::mat4(1.0), glm::vec3(0.5,0.5,0.5)));

    viewer.addSpotLight(spotLight);
    viewer.addRenderable(spotLightRenderable);

    FrameRenderablePtr frame = std::make_shared<FrameRenderable>(flat_shader);
    viewer.addRenderable(frame);

    viewer.startAnimation();
}


int main() 
{
    glm::vec4 background_color(0.8,0.8,0.8,1);
	Viewer viewer(1280,720, background_color);
	
    logo(viewer);

	while( viewer.isRunning() )
	{
		viewer.handleEvent();
		viewer.animate();
		viewer.draw();
		viewer.display();
	}	

	return EXIT_SUCCESS;
}