#include "./../../include/dynamics/SpringForceField.hpp"

SpringForceField::SpringForceField(const ParticlePtr p1, const ParticlePtr p2, float stiffness, float equilibriumLength, float damping) :
    m_p1(p1),
    m_p2(p2),
    m_stiffness(stiffness),
    m_equilibriumLength(equilibriumLength),
    m_damping(damping)
{}

void SpringForceField::do_addForce()
{
    // Compute displacement vector
    glm::vec3 displacement = m_p1->getPosition() - m_p2->getPosition();

    // Compute displacement length
    float displacementLength = glm::length(displacement);

    // Check if the displacement length is above the threshold
    if (displacementLength > std::numeric_limits<float>::epsilon())
    {
        // Normalize the displacement vector
        glm::vec3 displacementDir = glm::normalize(displacement);

        // Compute spring force corresponding to the displacement
        glm::vec3 springForce = -m_stiffness * (displacementLength - m_equilibriumLength) * displacementDir;

        // Compute relative velocity
        glm::vec3 relativeVelocity = m_p2->getVelocity() - m_p1->getVelocity();

        // Compute damping force
        glm::vec3 dampingForce = -m_damping * glm::dot(relativeVelocity, displacementDir) * displacementDir;

        // Total force
        glm::vec3 totalForce = springForce + dampingForce;

        // Apply forces to the particles
        m_p1->setForce(m_p1->getForce() + totalForce);
        m_p2->setForce(m_p2->getForce() - totalForce);
    }
}

ParticlePtr SpringForceField::getParticle1() const
{
    return m_p1;
}

ParticlePtr SpringForceField::getParticle2() const
{
    return m_p2;
}
