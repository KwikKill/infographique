#include <Viewer.hpp>
#include <ShaderProgram.hpp>
#include <CylinderMeshRenderable.hpp>
#include <MeshRenderable.hpp>
#include <FrameRenderable.hpp>
#include <HierarchicalRenderable.hpp>
#include <Io.hpp>
#include <lighting/LightedMeshRenderable.hpp>
#include <lighting/Light.hpp>

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

    /*const std::string tuture_path = "../../good/carcasse.obj";
    MeshRenderablePtr tuture = std::make_shared<MeshRenderable>(flatShader, tuture_path);

    const std::string roues_avant_path = "../../good/roues.obj";
    MeshRenderablePtr roues_avant = std::make_shared<MeshRenderable>(flatShader, roues_avant_path);

    const std::string roues_arriere_path = "../../good/roues.obj";
    MeshRenderablePtr roues_arriere = std::make_shared<MeshRenderable>(flatShader, roues_arriere_path);

    // Move the roues to the right place
    roues_avant->setGlobalTransform(getTranslationMatrix(1.2, 0.3, 0));
    roues_arriere->setGlobalTransform(getTranslationMatrix(-1.7, 0.3, 0));


    // set the hierarchie
    MeshRenderable::addChild(tuture, roues_avant);
	MeshRenderable::addChild(tuture, roues_arriere);

    // make the roues rotate
    roues_avant->addLocalTransformKeyframe(getRotationMatrix(0.0, glm::vec3(0, 0, 2)), 0.0);
    roues_avant->addLocalTransformKeyframe(getRotationMatrix(3.14, glm::vec3(0, 0, 2)), 1.0);
    roues_avant->addLocalTransformKeyframe(getRotationMatrix(3.14*2, glm::vec3(0, 0, 2)), 2.0);

    roues_arriere->addLocalTransformKeyframe(getRotationMatrix(0.0, glm::vec3(0, 0, 2)), 0.0);
    roues_arriere->addLocalTransformKeyframe(getRotationMatrix(3.14, glm::vec3(0, 0, 2)), 1.0);
    roues_arriere->addLocalTransformKeyframe(getRotationMatrix(3.14*2, glm::vec3(0, 0, 2)), 2.0);

    viewer.startAnimation();

    //traing->setModelMatrix(getTranslationMatrix(0,0,0));
    // Reduce scale (/10)
    //traing->setModelMatrix(glm::scale(traing->getModelMatrix(), glm::vec3(0.1,0.1,0.1)));
    // Add traing to the viewer
    viewer.addRenderable(tuture);*/


    /*const std::string traing_path = "../../good/ossature_train.obj";
    MeshRenderablePtr traing = std::make_shared<MeshRenderable>(flatShader, traing_path);

    const std::string roue1_path = "../../good/roues_avant_train.obj";
    MeshRenderablePtr roue1 = std::make_shared<MeshRenderable>(flatShader, roue1_path);
    MeshRenderablePtr roue2 = std::make_shared<MeshRenderable>(flatShader, roue1_path);

    const std::string roue3_path = "../../good/roues_arriere_train.obj";
    MeshRenderablePtr roue3 = std::make_shared<MeshRenderable>(flatShader, roue3_path);

    // Move the roues to the right place
    roue1->setGlobalTransform(getTranslationMatrix(0.0, 2.5, 1.2));
    roue2->setGlobalTransform(getTranslationMatrix(0.0, 2.5, 5.5));

    roue3->setGlobalTransform(getTranslationMatrix(0.0, 3.6, -2.2));

    // set the hierarchie
    HierarchicalRenderable::addChild(traing, roue1);
    HierarchicalRenderable::addChild(traing, roue2);
    HierarchicalRenderable::addChild(traing, roue3);

    // make the roues rotate
    roue1->addLocalTransformKeyframe(getRotationMatrix(0.0, glm::vec3(2, 0, 0)), 0.0);
    roue1->addLocalTransformKeyframe(getRotationMatrix(3.14, glm::vec3(2, 0, 0)), 1.0);
    roue1->addLocalTransformKeyframe(getRotationMatrix(3.14*2, glm::vec3(2, 0, 0)), 2.0);

    roue2->addLocalTransformKeyframe(getRotationMatrix(0.0, glm::vec3(2, 0, 0)), 0.0);
    roue2->addLocalTransformKeyframe(getRotationMatrix(3.14, glm::vec3(2, 0, 0)), 1.0);
    roue2->addLocalTransformKeyframe(getRotationMatrix(3.14*2, glm::vec3(2, 0, 0)), 2.0);

    roue3->addLocalTransformKeyframe(getRotationMatrix(0.0, glm::vec3(2, 0, 0)), 0.0);
    roue3->addLocalTransformKeyframe(getRotationMatrix(3.14, glm::vec3(2, 0, 0)), 1.0);
    roue3->addLocalTransformKeyframe(getRotationMatrix(3.14*2, glm::vec3(2, 0, 0)), 2.0);

    viewer.startAnimation();

    viewer.addRenderable(traing);*/

    const std::string voiture_path = "../../good/obj/car.obj";
    const std::string voiture_texture_path = "../../good/mtl/";
    std::vector<std::vector<glm::vec3>> all_positions;
    std::vector<std::vector<glm::vec3>> all_normals;
    std::vector<std::vector<glm::vec2>> all_texcoords;
    std::vector<MaterialPtr> materials;

    read_obj_with_materials(voiture_path, voiture_texture_path, all_positions, all_normals, all_texcoords, materials);

    //const std::string pingu_path = "../../good/pingu.obj";
    //MeshRenderablePtr pingu = std::make_shared<MeshRenderable>(flatShader, pingu_path);

    //const std::string pinguv2_path = "../../good/pingu2v1.obj";
    //MeshRenderablePtr pinguv2 = std::make_shared<MeshRenderable>(flatShader, pinguv2_path);

    // Move the object to the right place
    //voiture->setGlobalTransform(getTranslationMatrix(0, 0, 0));
    //pingu->setGlobalTransform(getTranslationMatrix(0, 0, -6));
    //pinguv2->setGlobalTransform(getTranslationMatrix(0, 0, 6));

    // Add the object to the viewer
    //viewer.addRenderable(voiture);
    //viewer.addRenderable(pingu);
    //viewer.addRenderable(pinguv2);


    //const std::string test_path = "../../good/v0join.obj";
    //MeshRenderablePtr test = std::make_shared<MeshRenderable>(flatShader, test_path);

    // Move the roues to the right place
    //test->setGlobalTransform(getTranslationMatrix(1.2, 0.3, 0));

    //viewer.addRenderable(test);
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