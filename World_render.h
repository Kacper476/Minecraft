#ifndef World_render_CLASS_H
#define World_render_CLASS_H

#include<glad/glad.h>

#include<vector>
#include<string>

#include <memory>

#include"Texture.h"
#include<stb/stb_image.h>

#include"shaderClass.h"

#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include "World_create.h"



#include<glm/glm.hpp>

class World_render 
{
public:
	World_render();
	~World_render();
	void render();
	void shader_activate();
	void cube_remove(const glm::vec3& position, const glm::vec3& cameraDirection);
	void cube_add(const glm::vec3& position, const glm::vec3& cameraDirection);
	GLuint get_shaderid();
	std::unique_ptr<Shader> shaderProgram = nullptr;
protected:
	//transform cube XYZ to full vector of coordinates  
	void map_transform();
	//add indices for next cube
	void indices_add(GLfloat check_if_render);
	//update maps after creating/removing cube
	void map_update();
	//load 
	void map_load(int chunk);
	
	// Generates Vertex Array Object and binds it
	VAO VAO1, VAO2, VAO3, VAO4, VAO5, VAO6;

	// Generates Vertex Buffer Object
	VBO VBO1, VBO2, VBO3, VBO4, VBO5, VBO6;
	// Generates Element Buffer Object
	EBO EBO1, EBO2, EBO3, EBO4, EBO5, EBO6;

	// Generates Shader object using shaders default.vert and default.frag

	// Gets ID of uniform called "scale"
	GLuint uniID;
	std::unique_ptr<Texture> dirt = nullptr;
	std::unique_ptr<Texture> dirt_side = nullptr;
	std::unique_ptr<Texture> grass = nullptr;


	//vector of all cubes
	std::vector<std::vector<GLfloat>> Za_warudo{ //is this jojo refference?



		//back of cube
		{
			//     COORDINATES     /        COLORS      /   TexCoord  //

			// 0.0f,  0.0f, 0.0f,     1.0f, 0.0f, 0.0f,	0.0f, 0.0f, // Lower left corner
			// 0.0f,  1.0f, 0.0f,     0.0f, 1.0f, 0.0f,	0.0f, 1.0f, // Upper left corner
			// 1.0f,  1.0f, 0.0f,     0.0f, 0.0f, 1.0f,	1.0f, 1.0f, // Upper right corner
			// 1.0f,  0.0f, 0.0f,     1.0f, 1.0f, 1.0f,	1.0f, 0.0f,  // Lower right corner
		},

		//front of cube 
		{
		},


		//left of cube
		{
		},

		//right of cube 
	   {
	   },

	   //top of cube 
	   {
	   },

	   //bot of cube 
	   {
	   }



	};

	//0x 0y 0z cube
	std::vector<std::vector<GLfloat>> start_cube{



		//back of cube
		{
			//     COORDINATES     /        COLORS      /   TexCoord  //

			 0.0f,  0.0f, 0.0f,     1.0f, 0.0f, 0.0f,	0.0f, 0.0f, // Lower left corner
			 0.0f,  1.0f, 0.0f,     0.0f, 1.0f, 0.0f,	0.0f, 1.0f, // Upper left corner
			 1.0f,  1.0f, 0.0f,     0.0f, 0.0f, 1.0f,	1.0f, 1.0f, // Upper right corner
			 1.0f,  0.0f, 0.0f,     1.0f, 1.0f, 1.0f,	1.0f, 0.0f,  // Lower right corner
		},

		//front of cube 
		{
		 0.0f,  0.0f, 1.0f,     1.0f, 0.0f, 0.0f,	0.0f, 0.0f,
		 0.0f,  1.0f, 1.0f,     0.0f, 1.0f, 0.0f,	0.0f, 1.0f,
		 1.0f,  1.0f, 1.0f,     0.0f, 0.0f, 1.0f,	1.0f, 1.0f,
		 1.0f,  0.0f, 1.0f,     1.0f, 1.0f, 1.0f,	1.0f, 0.0f,


		 },


		 //left of cube
		 {
		 0.0f,  0.0f, 0.0f,     1.0f, 0.0f, 0.0f,	0.0f, 0.0f,
		 0.0f,  1.0f, 0.0f,     0.0f, 1.0f, 0.0f,	0.0f, 1.0f,
		 0.0f,  1.0f, 1.0f,     0.0f, 0.0f, 1.0f,	1.0f, 1.0f,
		 0.0f,  0.0f, 1.0f,     1.0f, 1.0f, 1.0f,	1.0f, 0.0f,
		 },

		 //right of cube 
		{
		1.0f,  0.0f, 0.0f,     1.0f, 1.0f, 1.0f,	0.0f, 0.0f,
		1.0f,  1.0f, 0.0f,     0.0f, 0.0f, 1.0f,	0.0f, 1.0f,
		1.0f,  1.0f, 1.0f,     0.0f, 0.0f, 1.0f,	1.0f, 1.0f,
		1.0f,  0.0f, 1.0f,     1.0f, 1.0f, 1.0f,	1.0f, 0.0f,
		},

		//top of cube 
		{
		0.0f,  1.0f, 0.0f,     1.0f, 1.0f, 1.0f,	0.0f, 0.0f,
		0.0f,  1.0f, 1.0f,     0.0f, 1.0f, 0.0f,	0.0f, 1.0f,
		1.0f,  1.0f, 1.0f,     0.0f, 0.0f, 1.0f,	1.0f, 1.0f,
		1.0f,  1.0f, 0.0f,     0.0f, 0.0f, 1.0f,	1.0f, 0.0f
		},


		//bot of cube 
		{
		0.0f,   0.0f, 0.0f,     1.0f, 1.0f, 1.0f,	0.0f, 0.0f,
		0.0f,   0.0f, 1.0f,     0.0f, 1.0f, 0.0f,	0.0f, 1.0f,
		1.0f,   0.0f, 1.0f,     0.0f, 0.0f, 1.0f,	1.0f, 1.0f,
		1.0f,   0.0f, 0.0f,     0.0f, 0.0f, 1.0f,	1.0f, 0.0f
		}



	};

	//Indices of Cube wall
	std::vector<GLuint> indices{};
	//indices for 0x0y0zcube
	std::vector<GLuint> start_indices{
			0, 1, 2,
			0, 3, 2
	};

	//cordinate of every cube
	std::vector<std::vector<std::vector<GLfloat>>> map3d
	{
		
	};


	std::vector<std::vector<GLfloat>> map
	{
	
	};

	std::vector<int> Rendered_chunks
	{
	1,2,3,4
	};
};










#endif