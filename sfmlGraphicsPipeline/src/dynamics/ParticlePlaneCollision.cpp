#include "./../../include/dynamics/ParticlePlaneCollision.hpp"

ParticlePlaneCollision::~ParticlePlaneCollision()
{}


ParticlePlaneCollision::ParticlePlaneCollision(ParticlePtr particle, PlanePtr plane, float restitution) :
    Collision(restitution)
{
    m_particle = particle;
    m_plane = plane;
}

void ParticlePlaneCollision::do_solveCollision()
{
    // Don't process fixed particles (Let's assume that the ground plane is fixed)
    if (m_particle->isFixed()) return;

    // Compute particle-plane distance
    float distance = glm::dot(m_plane->normal(), m_particle->getPosition()) - m_plane->distanceToOrigin();

    // Check if the particle is colliding with the plane
    if (distance < m_particle->getRadius())
    {
        // Project the particle on the plane
        glm::vec3 correction = (m_particle->getRadius() - distance) * m_plane->normal();
        glm::vec3 newPosition = m_particle->getPosition() + correction;
        m_particle->setPosition(newPosition);

        // Compute post-collision velocity
        glm::vec3 velocity = m_particle->getVelocity();
        glm::vec3 normal = m_plane->normal();
        glm::vec3 newVelocity = velocity - (1.0f + m_restitution) * glm::dot(velocity, normal) * normal;
        m_particle->setVelocity(newVelocity);
    }
}



bool testParticlePlane(const ParticlePtr &particle, const PlanePtr &plane)
{
    // Compute the distance from the particle to the plane
    float distance = glm::dot(plane->normal(), particle->getPosition()) - plane->distanceToOrigin();

    // Check if the absolute distance is less than or equal to the particle's radius
    return std::abs(distance) <= particle->getRadius();
}
