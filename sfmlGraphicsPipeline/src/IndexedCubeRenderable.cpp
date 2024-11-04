#include "./../include/IndexedCubeRenderable.hpp"
#include "./../include/gl_helper.hpp"
#include "./../include/log.hpp"
#include "./../include/Utils.hpp"

#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>

IndexedCubeRenderable::IndexedCubeRenderable(ShaderProgramPtr shaderProgram)
	: Renderable(shaderProgram), m_vBuffer(0), m_cBuffer(0), m_iBuffer(0)
{
	// Define the unique vertices of the cube
	m_positions = {
		// Front face
		glm::vec3(-1, -1,  1), glm::vec3( 1, -1,  1), glm::vec3( 1,  1,  1), glm::vec3(-1,  1,  1),
		// Back face
		glm::vec3(-1, -1, -1), glm::vec3( 1, -1, -1), glm::vec3( 1,  1, -1), glm::vec3(-1,  1, -1)
	};

	// Define the indices for the cube
	m_indices = {
		// Front face
		0, 1, 2, 0, 2, 3,
		// Back face
		4, 5, 6, 4, 6, 7,
		// Left face
		4, 0, 3, 4, 3, 7,
		// Right face
		1, 5, 6, 1, 6, 2,
		// Top face
		3, 2, 6, 3, 6, 7,
		// Bottom face
		4, 5, 1, 4, 1, 0
	};

	// Set the color of the vertices (one color per vertex)
	m_colors = {
		glm::vec3(1, 0, 0), glm::vec3(0, 1, 0), glm::vec3(0, 0, 1), glm::vec3(1, 1, 0),
		glm::vec3(1, 0, 1), glm::vec3(0, 1, 1), glm::vec3(0.5, 0.5, 0.5), glm::vec3(1, 1, 1)
	};

	// 4. How many triangles do you need? How many vertices?
	// 12 triangles, 8 vertices

	// Set the model matrix to identity
	m_model = glm::mat4(1.0);

	// Create buffers
	glGenBuffers(1, &m_vBuffer); // vertices
	glGenBuffers(1, &m_cBuffer); // colors
	glGenBuffers(1, &m_iBuffer); // indices

	// Activate buffer and send data to the graphics card
	glBindBuffer(GL_ARRAY_BUFFER, m_vBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_positions.size() * sizeof(glm::vec3), m_positions.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, m_cBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_colors.size() * sizeof(glm::vec3), m_colors.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), m_indices.data(), GL_STATIC_DRAW);
}

void IndexedCubeRenderable::do_draw()
{
	// Get the identifier (location) of the uniform modelMat in the shader program
	int modelLocation = m_shaderProgram->getUniformLocation("modelMat");
	// Send the data corresponding to this identifier on the GPU
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(m_model));

	// Get the identifier of the attribute vPosition in the shader program
	int positionLocation = m_shaderProgram->getAttributeLocation("vPosition");
	// Activate the attribute array at this location
	glEnableVertexAttribArray(positionLocation);
	// Bind the position buffer on the GL_ARRAY_BUFFER target
	glBindBuffer(GL_ARRAY_BUFFER, m_vBuffer);
	// Specify the location and the format of the vertex position attribute
	glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	// Get the identifier of the attribute vColor in the shader program
	int colorLocation = m_shaderProgram->getAttributeLocation("vColor");
	// Activate the attribute array at this location
	glEnableVertexAttribArray(colorLocation);
	// Bind the color buffer on the GL_ARRAY_BUFFER target
	glBindBuffer(GL_ARRAY_BUFFER, m_cBuffer);
	// Specify the location and the format of the vertex color attribute
	glVertexAttribPointer(colorLocation, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	// Bind the index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iBuffer);
	// Draw the triangles using indices
	glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, (void*)0);

	// Release the vertex attribute arrays
	glDisableVertexAttribArray(positionLocation);
	glDisableVertexAttribArray(colorLocation);
}


IndexedCubeRenderable::~IndexedCubeRenderable()
{
	glcheck(glDeleteBuffers(1, &m_vBuffer));
	glcheck(glDeleteBuffers(1, &m_cBuffer));
	glcheck(glDeleteBuffers(1, &m_iBuffer));
}
