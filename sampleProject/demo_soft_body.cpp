#include <ShaderProgram.hpp>
#include <Viewer.hpp>

#include <ShaderProgram.hpp>

#include <QuadMeshRenderable.hpp>
#include <FrameRenderable.hpp>

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
#include <chrono>
#include <list>

void soft_body(Viewer& viewer, DynamicSystemPtr& system, DynamicSystemRenderablePtr &systemRenderable);

void initialize_scene( Viewer& viewer )
{
    //Set up a shader and add a 3D frame.
    ShaderProgramPtr flatShader = std::make_shared<ShaderProgram>(  "../../sfmlGraphicsPipeline/shaders/flatVertex.glsl", 
                                                                    "../../sfmlGraphicsPipeline/shaders/flatFragment.glsl");
    viewer.addShaderProgram( flatShader );
    FrameRenderablePtr frame = std::make_shared<FrameRenderable>(flatShader);
    viewer.addRenderable(frame);

    //Initialize a dynamic system (Solver, Time step, Restitution coefficient)
    DynamicSystemPtr system = std::make_shared<DynamicSystem>();
    EulerExplicitSolverPtr solver = std::make_shared<EulerExplicitSolver>();
    system->setSolver(solver);
    system->setDt(0.01);

    //Create a renderable associated to the dynamic system
    //This renderable is responsible for calling DynamicSystem::computeSimulationStep() in the animate() function
    //It is also responsible for some of the key/mouse events
    DynamicSystemRenderablePtr systemRenderable = std::make_shared<DynamicSystemRenderable>(system);
    viewer.addRenderable(systemRenderable);

    soft_body(viewer, system, systemRenderable);

    //Finally activate animation
    viewer.startAnimation();
    // Set up a shader and add a 3D frame.
    viewer.getCamera().setViewMatrix(lookAtUp(glm::vec3(3.5,3.5,-3.5), glm::vec3(0)));
}



int main() 
{
    glm::vec4 background_color(0.7,0.7,0.7,1);
	Viewer viewer(1280,720,background_color);
	initialize_scene(viewer);

    float last_time = 0;
    float new_time;
    float total_time = 0;
    int frame_count = 0;

	while( viewer.isRunning() )
	{
		viewer.handleEvent();
		viewer.animate();
		viewer.draw();
		viewer.display();
        new_time = viewer.getTime();
        //std::cout<<new_time -last_time <<std::endl;
        total_time += new_time-last_time;
        last_time = new_time;
        
        if (total_time > 1){
            total_time -= 1;
            std::cout<<frame_count<<"   ("<<5e-4 * frame_count<<" s)"<<std::endl;
            frame_count = 0;
        }
        frame_count ++;
        
	}	

	return EXIT_SUCCESS;
}


void add_soft_body(DynamicSystemPtr& system, DynamicSystemRenderablePtr &systemRenderable,
    float height, float width, float depth,
    float radius, float mass, float stiffness, float spring_damping,
    float scale, glm::vec3 position, float angle, glm::vec3 axis,
    ShaderProgramPtr spring_shader, ShaderProgramPtr particle_shader
    )
{
    glm::mat4 transform = getTranslationMatrix(position) * getScaleMatrix(scale) * getRotationMatrix(angle, axis);

    std::vector<std::vector<std::vector<ParticlePtr>>> particles;
    particles.resize(height);
    for (size_t i = 0; i < height ; ++i){
        particles[i].resize(width);
        for (size_t j = 0; j < width ; ++j){
            particles[i][j].resize(depth);
        }
    }

    std::vector<ParticlePtr> particle_list;

    for (size_t i = 0; i < height ; ++i){
        for (size_t j = 0; j < width ; ++j){
            for (size_t k = 0; k < depth ; ++k){
                glm::vec3 pos = glm::vec3(transform * glm::vec4(i,j,k,1));
                ParticlePtr particle = std::make_shared<Particle>(pos, glm::vec3(0), mass, scale * radius);
                particles[i][j][k] = particle;
                particle_list.push_back(particle);
                system->addParticle(particle);
            }
        }  
    }

    float l0 = scale;
    float l0_square_diag = std::sqrt(2) * scale;
    float l0_cube_diag = std::sqrt(3) * scale;

    std::list<SpringForceFieldPtr> spring_list;

    // Fully connected voxels
    for (size_t i = 0; i < height ; ++i){
        for (size_t j = 0; j < width; ++j){
            for (size_t k = 0; k < depth; ++k){
                if (i < height - 1){
                    SpringForceFieldPtr width_spring = std::make_shared<SpringForceField>(particles[i][j][k], particles[i+1][j][k], stiffness, l0, spring_damping);
                    spring_list.push_back(width_spring);
                    system->addForceField(width_spring);
                }
                if (j < width - 1){
                    SpringForceFieldPtr height_spring = std::make_shared<SpringForceField>(particles[i][j][k], particles[i][j+1][k], stiffness, l0, spring_damping);
                    spring_list.push_back(height_spring);
                    system->addForceField(height_spring);
                }
                if (k < depth - 1){
                    SpringForceFieldPtr depth_spring = std::make_shared<SpringForceField>(particles[i][j][k], particles[i][j][k+1], stiffness, l0, spring_damping);
                    spring_list.push_back(depth_spring);
                    system->addForceField(depth_spring);
                }
                if (i < height - 1 && j < width - 1){
                    SpringForceFieldPtr height_width_spring1 = std::make_shared<SpringForceField>(particles[i][j][k], particles[i+1][j+1][k], stiffness * 0.5, l0_square_diag, spring_damping);
                    spring_list.push_back(height_width_spring1);
                    system->addForceField(height_width_spring1);
                    SpringForceFieldPtr height_width_spring2 = std::make_shared<SpringForceField>(particles[i+1][j][k], particles[i][j+1][k], stiffness * 0.5, l0_square_diag, spring_damping);
                    spring_list.push_back(height_width_spring2);
                    system->addForceField(height_width_spring2);
                }
                if (k < depth - 1 && j < width - 1){
                    SpringForceFieldPtr depth_width_spring1 = std::make_shared<SpringForceField>(particles[i][j][k], particles[i][j+1][k+1], stiffness * 0.5, l0_square_diag, spring_damping);
                    spring_list.push_back(depth_width_spring1);
                    system->addForceField(depth_width_spring1);
                    SpringForceFieldPtr depth_width_spring2 = std::make_shared<SpringForceField>(particles[i][j+1][k], particles[i][j][k+1], stiffness * 0.5, l0_square_diag, spring_damping);
                    spring_list.push_back(depth_width_spring2);
                    system->addForceField(depth_width_spring2);
                }
                if (k < depth - 1 && i < height - 1){
                    SpringForceFieldPtr depth_height_spring1 = std::make_shared<SpringForceField>(particles[i][j][k], particles[i+1][j][k+1], stiffness * 0.5, l0_square_diag, spring_damping);
                    spring_list.push_back(depth_height_spring1);
                    system->addForceField(depth_height_spring1);
                    SpringForceFieldPtr depth_height_spring2 = std::make_shared<SpringForceField>(particles[i+1][j][k], particles[i][j][k+1], stiffness * 0.5, l0_square_diag, spring_damping);
                    spring_list.push_back(depth_height_spring2);
                    system->addForceField(depth_height_spring2);
                }
                if (i < height - 1 && j < width - 1 && k < depth - 1){
                    SpringForceFieldPtr diagonal_spring1 = std::make_shared<SpringForceField>(particles[i][j][k], particles[i+1][j+1][k+1], stiffness*0.25, l0_cube_diag, spring_damping);
                    spring_list.push_back(diagonal_spring1);
                    system->addForceField(diagonal_spring1);
                    SpringForceFieldPtr diagonal_spring2 = std::make_shared<SpringForceField>(particles[i][j+1][k], particles[i+1][j][k+1], stiffness*0.25, l0_cube_diag, spring_damping);
                    spring_list.push_back(diagonal_spring2);
                    system->addForceField(diagonal_spring2);
                    SpringForceFieldPtr diagonal_spring3 = std::make_shared<SpringForceField>(particles[i][j][k+1], particles[i+1][j+1][k], stiffness*0.25, l0_cube_diag, spring_damping);
                    spring_list.push_back(diagonal_spring3);
                    system->addForceField(diagonal_spring3);
                    SpringForceFieldPtr diagonal_spring4 = std::make_shared<SpringForceField>(particles[i+1][j][k], particles[i][j+1][k+1], stiffness*0.25, l0_cube_diag, spring_damping);
                    spring_list.push_back(diagonal_spring4);
                    system->addForceField(diagonal_spring4);
                }
            }
        }  
    }

    //Create a particleListRenderable to efficiently visualize the particles of the system
    ParticleListRenderablePtr particleListRenderable = std::make_shared<ParticleListRenderable>( particle_shader, particle_list);
    HierarchicalRenderable::addChild(systemRenderable, particleListRenderable);

    //Create a springListRenderable to efficiently visualize the springs of the system
    SpringListRenderablePtr springsRenderable = std::make_shared<SpringListRenderable>(spring_shader, spring_list);
    HierarchicalRenderable::addChild( systemRenderable, springsRenderable );
}

void soft_body(Viewer& viewer, DynamicSystemPtr& system, DynamicSystemRenderablePtr &systemRenderable)
{
    //Initialize a shader for the following renderables
    ShaderProgramPtr flatShader = std::make_shared<ShaderProgram>(  "../../sfmlGraphicsPipeline/shaders/flatVertex.glsl",
                                                                    "../../sfmlGraphicsPipeline/shaders/flatFragment.glsl");
    ShaderProgramPtr instancedShader = std::make_shared<ShaderProgram>(  "../../sfmlGraphicsPipeline/shaders/instancedVertex.glsl",
                                                                    "../../sfmlGraphicsPipeline/shaders/instancedFragment.glsl");
    viewer.addShaderProgram( flatShader );
    viewer.addShaderProgram( instancedShader );

    system->setCollisionsDetection(true);
    system->setRestitution(0.3f);

    glm::vec3 p1(6.0,0.0,6.0),p2(6.0,0.0,-6.0), p3(-6.0,0.0,-6.0), p4(-6.0,0.0,6.0);
    PlanePtr plane = std::make_shared<Plane>(glm::vec3(0,1,0), glm::vec3(0));
    system->addPlaneObstacle(plane);    
    QuadMeshRenderablePtr planeRenderable = std::make_shared<QuadMeshRenderable>(flatShader, p1, p2, p3, p4);
    HierarchicalRenderable::addChild( systemRenderable, planeRenderable );

    {
        int height = 3;
        int width = 3;
        int depth = 3;
        float scale = 0.5;
        float radius = 0.25;
        float mass = 1.0;
        float angle = M_PI * 0.25;
        glm::vec3 position = glm::vec3(0,5,0);
        glm::vec3 axis = glm::normalize(glm::vec3(1,1,1));
        float stiffness = 1e3;
        float spring_damping = 0.5;
        add_soft_body(system, systemRenderable, height, width, depth, radius, mass, stiffness, spring_damping, scale, position, angle, axis, flatShader, instancedShader);
    }
    {
        int height = 4;
        int width = 2;
        int depth = 5;
        float scale = 0.5;
        float radius = 0.25;
        float mass = 1.0;
        float angle = M_PI * 0.5;
        glm::vec3 position = glm::vec3(3,6,-2);
        glm::vec3 axis = glm::normalize(glm::vec3(1,-1,1));
        float stiffness = 2e3;
        float spring_damping = 0.5;
        add_soft_body(system, systemRenderable, height, width, depth, radius, mass, stiffness, spring_damping, scale, position, angle, axis, flatShader, instancedShader);
    }

    {
        int height = 2;
        int width = 2;
        int depth = 5;
        float scale = 0.5;
        float radius = 0.25;
        float mass = 1.0;
        float angle = M_PI * 0.5;
        glm::vec3 position = glm::vec3(-3,6,2);
        glm::vec3 axis = glm::normalize(glm::vec3(1,1,-1));
        float stiffness = 4e3;
        float spring_damping = 0.5;
        add_soft_body(system, systemRenderable, height, width, depth, radius, mass, stiffness, spring_damping, scale, position, angle, axis, flatShader, instancedShader);
    }
    {
        int height = 4;
        int width = 3;
        int depth = 4;
        float scale = 0.5;
        float radius = 0.25;
        float mass = 1.0;
        float angle = M_PI * 0.5;
        glm::vec3 position = glm::vec3(-2,3,-2);
        glm::vec3 axis = glm::normalize(glm::vec3(-1,1,-1));
        float stiffness = 4e2;
        float spring_damping = 0.5;
        add_soft_body(system, systemRenderable, height, width, depth, radius, mass, stiffness, spring_damping, scale, position, angle, axis, flatShader, instancedShader);
    }
   
    ConstantForceFieldPtr gravityForceField = std::make_shared<ConstantForceField>(system->getParticles(), DynamicSystem::gravity  );
    system->addForceField( gravityForceField );

    float dampingCoefficient = 1.0;
    DampingForceFieldPtr dampingForceField = std::make_shared<DampingForceField>(system->getParticles(), dampingCoefficient);
    system->addForceField(dampingForceField);

}