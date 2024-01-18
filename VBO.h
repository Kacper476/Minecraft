#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include<glad/glad.h>
#include<vector>

class VBO
{
public:
	// Reference ID of the Vertex Buffer Object
	GLuint ID;

	//empty constructor 
	VBO();
	 
	// Links Vertex Buffer to vertices
     void link(std::vector<GLfloat> vertices, GLsizeiptr size);
	// Binds the VBO
	void Bind();
	// Unbinds the VBO
	void Unbind();
	// Deletes the VBO
	void Delete();

};

#endif