#include <Viewer.hpp>
#include <ShaderProgram.hpp>
#include <FrameRenderable.hpp>
#include <HierarchicalRenderable.hpp>
#include <CylinderMeshRenderable.hpp>
#include <MeshRenderable.hpp>
#include <SphereMeshRenderable.hpp>

void initialize_scene( Viewer& viewer )
{
	ShaderProgramPtr flatShader = std::make_shared<ShaderProgram>(
			"../../sfmlGraphicsPipeline/shaders/flatVertex.glsl",
			"../../sfmlGraphicsPipeline/shaders/flatFragment.glsl");

	viewer.addShaderProgram(flatShader);

	//Frame
	FrameRenderablePtr frame = std::make_shared<FrameRenderable>(flatShader);
	viewer.addRenderable(frame);

	// Create a cylinder
	bool indexed = false; // indexed version already implemented
	unsigned int slices = 50u; // number of slices
	bool vertex_normals = true; // use vertex normals ? else triangle normals
	// See CylinderMeshRenderable.cpp 
	//CylinderMeshRenderablePtr cylinder = std::make_shared<CylinderMeshRenderable>(flatShader, indexed, slices, vertex_normals);

	// Add the cylinder to the viewer
	//viewer.addRenderable(cylinder);

	// Create renderables
	CylinderMeshRenderablePtr root = std::make_shared<CylinderMeshRenderable>(flatShader, indexed, slices, vertex_normals);
	CylinderMeshRenderablePtr childR = std::make_shared<CylinderMeshRenderable>(flatShader, indexed, slices, vertex_normals);
	CylinderMeshRenderablePtr childL = std::make_shared<CylinderMeshRenderable>(flatShader, indexed, slices, vertex_normals);
	CylinderMeshRenderablePtr childRR = std::make_shared<CylinderMeshRenderable>(flatShader, indexed, slices, vertex_normals);
	CylinderMeshRenderablePtr childRL = std::make_shared<CylinderMeshRenderable>(flatShader, indexed, slices, vertex_normals);
	CylinderMeshRenderablePtr childLR = std::make_shared<CylinderMeshRenderable>(flatShader, indexed, slices, vertex_normals);
	CylinderMeshRenderablePtr childLL = std::make_shared<CylinderMeshRenderable>(flatShader, indexed, slices, vertex_normals);

	// Set local transform and global transform
	root->setGlobalTransform(getTranslationMatrix(0, 4, 0) * getRotationMatrix(3.14f / 2, glm::vec3(1, 0, 0)) * getScaleMatrix(0.4, 0.4, 4));

	glm::mat4 globalR = getTranslationMatrix(0, 4.3, 0.1) * getRotationMatrix(3.14f / 4, glm::vec3(1, 0, 0));
	glm::mat4 globalL = getTranslationMatrix(0, 4.3, -0.1) * getRotationMatrix(-3.14f / 4, glm::vec3(1, 0, 0));

	childR->setGlobalTransform(globalR);
	childL->setGlobalTransform(globalL);
	childRR->setGlobalTransform(globalR);
	childRL->setGlobalTransform(globalL);
	childLR->setGlobalTransform(globalR);
	childLL->setGlobalTransform(globalL);

	// Define parent/children relationships
	HierarchicalRenderable::addChild(root, childR);
	HierarchicalRenderable::addChild(root, childL);
	HierarchicalRenderable::addChild(childR, childRR);
	HierarchicalRenderable::addChild(childR, childRL);
	HierarchicalRenderable::addChild(childL, childLR);
	HierarchicalRenderable::addChild(childL, childLL);

	// Add the root of the hierarchy to the viewer
	viewer.addRenderable(root);
	// ...

}

int main()
{
	Viewer viewer(1280, 720);
	initialize_scene(viewer);

	while (viewer.isRunning())
	{
		viewer.handleEvent();
		viewer.animate();
		viewer.draw();
		viewer.display();
	}

	return EXIT_SUCCESS;
}