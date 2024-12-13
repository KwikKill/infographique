#include <Viewer.hpp>
#include <ShaderProgram.hpp>
#include <CylinderMeshRenderable.hpp>
#include <MeshRenderable.hpp>
#include <FrameRenderable.hpp>

void initialize_scene( Viewer& viewer )
{
    // Create a shader program
	ShaderProgramPtr flatShader = std::make_shared<ShaderProgram>(
        "../../sfmlGraphicsPipeline/shaders/debugVertex.glsl",
        "../../sfmlGraphicsPipeline/shaders/debugFragment.glsl"
    );

    // Add the shader program to the viewer
    viewer.addShaderProgram( flatShader );

    FrameRenderablePtr frame = std::make_shared<FrameRenderable>(flatShader);
	//viewer.addRenderable(frame);

	// Create a cylinder
    bool indexed = false; // indexed version already implemented
    unsigned int slices = 20u; // number of slices
    bool vertex_normals = true; // use vertex normals ? else triangle normals
    // See CylinderMeshRenderable.cpp 
    CylinderMeshRenderablePtr cylinder = std::make_shared<CylinderMeshRenderable>(flatShader, indexed, slices, vertex_normals);

    // Add the cylinder to the viewer
    viewer.addRenderable(cylinder);
    
    // Create suzanne
    const std::string suzanne_path = "../../sfmlGraphicsPipeline/meshes/suzanne.obj";
    MeshRenderablePtr suzanne = std::make_shared<MeshRenderable>(flatShader, suzanne_path);
    suzanne->setModelMatrix(getTranslationMatrix(0,5,0));
    // Add suzanne to the viewer
    viewer.addRenderable(suzanne);

    // Create cat
    const std::string cat_path = "../../sfmlGraphicsPipeline/meshes/cat.obj";
    MeshRenderablePtr cat = std::make_shared<MeshRenderable>(flatShader, cat_path);
    cat->setModelMatrix(getTranslationMatrix(9,3.2,0));
    // Add cat to the viewer
    viewer.addRenderable(cat);
    
    // Create pillar
    const std::string pillar_path = "../../sfmlGraphicsPipeline/meshes/pillar.obj";
    MeshRenderablePtr pillar = std::make_shared<MeshRenderable>(flatShader, pillar_path);
    pillar->setModelMatrix(getTranslationMatrix(9,0,0));
    // rotate the pillar to make it vertical (90° = pi/2)
    pillar->setModelMatrix(glm::rotate(pillar->getModelMatrix(), 1.5708f, glm::vec3(0,0,1)));
    // Add pillar to the viewer
    viewer.addRenderable(pillar);

    const std::string traing_path = "../../good/goodgood3.obj";
    MeshRenderablePtr traing = std::make_shared<MeshRenderable>(flatShader, traing_path);
    traing->setModelMatrix(getTranslationMatrix(5,0,0));
    // Reduce scale (/10)
    traing->setModelMatrix(glm::scale(traing->getModelMatrix(), glm::vec3(0.1,0.1,0.1)));
    // Add traing to the viewer
    viewer.addRenderable(traing);
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