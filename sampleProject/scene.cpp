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

    const std::string traing_path = "../../good/goodgood3.obj";
    MeshRenderablePtr traing = std::make_shared<MeshRenderable>(flatShader, traing_path);
    traing->setModelMatrix(getTranslationMatrix(0,0,0));
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