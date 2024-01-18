#ifndef World_create_CLASS_H
#define World_create_CLASS_H

#include<vector>
#include<glad/glad.h>
#include <fstream>
#include <string>
#include <iostream>


class World_create
{

public:
	World_create();
protected:

	void world_generate();
	void chunk_generate(std::vector<GLfloat> temp);
	void save_to_file();
	std::vector<std::vector<GLfloat>> generated_world
	{
	
	};

private:
	GLfloat x = 0.0f;
	GLfloat y = 0.0f;
	GLfloat z = 0.0f;
	GLfloat render = 0.0f;
	int chunk_number = 0;

	

	//  x     y     z    render
	//{ 0.0f, 0.0f, 0.0f, 1.0f},


};
#endif