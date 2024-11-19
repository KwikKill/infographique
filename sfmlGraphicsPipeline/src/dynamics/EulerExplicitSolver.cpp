#include "./../../include/dynamics/EulerExplicitSolver.hpp"

EulerExplicitSolver::EulerExplicitSolver()
{

}

EulerExplicitSolver::~EulerExplicitSolver()
{

}

void EulerExplicitSolver::do_solve(const float& dt, std::vector<ParticlePtr>& particles)
{
    for(ParticlePtr p : particles)
    {
        if(!p->isFixed())
        {
            // Get current position, velocity, and force
            glm::vec3 position = p->getPosition();
            glm::vec3 velocity = p->getVelocity();
            glm::vec3 force = p->getForce();
            float mass = p->getMass();

            // Compute acceleration
            glm::vec3 acceleration = force / mass;

            // Update position and velocity using explicit Euler method
            position += dt * velocity;
            velocity += dt * acceleration;

            // Set updated position and velocity
            p->setPosition(position);
            p->setVelocity(velocity);
        }
    }
}
