#include "World_render.h"
#include "string"
World_render::World_render() {


	map_load(0);
	map_load(2);

	map_load(6);

	map_load(11);
	map_load(16);

	map_transform();


	shaderProgram = std::make_unique<Shader>("default.vert", "default.frag");
	uniID = glGetUniformLocation(shaderProgram->ID, "scale");
	dirt_side = std::make_unique<Texture>("textures/grass_block_side.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	dirt_side->texUnit(*shaderProgram, "tex0", 0);

	
	grass= std::make_unique<Texture>("textures/grass_block_top.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	grass->texUnit(*shaderProgram, "tex1", 1);

	dirt = std::make_unique<Texture>("textures/dirt.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	dirt->texUnit(*shaderProgram, "tex2", 2);

	VAO1.Bind();

	// links Vertex Buffer Object to vertices
	VBO1.link(Za_warudo[0], sizeof(Za_warudo[0]));

	// links Element Buffer Object to indices
	EBO1.Link(indices, sizeof(indices));

	// Links VBO attributes such as coordinates and colors to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));




	VAO2.Bind();
	VBO2.link(Za_warudo[1], sizeof(Za_warudo[1]));
	EBO2.Link(indices, sizeof(indices));
	VAO2.LinkAttrib(VBO2, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO2.LinkAttrib(VBO2, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO2.LinkAttrib(VBO2, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	VAO3.Bind();
	VBO3.link(Za_warudo[2], sizeof(Za_warudo[2]));
	EBO3.Link(indices, sizeof(indices));
	VAO3.LinkAttrib(VBO3, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO3.LinkAttrib(VBO3, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO3.LinkAttrib(VBO3, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	VAO4.Bind();
	VBO4.link(Za_warudo[3], sizeof(Za_warudo[3]));
	EBO4.Link(indices, sizeof(indices));
	VAO4.LinkAttrib(VBO4, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO4.LinkAttrib(VBO4, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO4.LinkAttrib(VBO4, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	VAO5.Bind();
	VBO5.link(Za_warudo[4], sizeof(Za_warudo[4]));
	EBO5.Link(indices, sizeof(indices));
	VAO5.LinkAttrib(VBO5, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO5.LinkAttrib(VBO5, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO5.LinkAttrib(VBO5, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	VAO6.Bind();
	VBO6.link(Za_warudo[5], sizeof(Za_warudo[5]));
	EBO6.Link(indices, sizeof(indices));
	VAO6.LinkAttrib(VBO6, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO6.LinkAttrib(VBO6, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO6.LinkAttrib(VBO6, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));


	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	VAO2.Unbind();
	VBO2.Unbind();
	EBO2.Unbind();

	VAO3.Unbind();
	VBO3.Unbind();
	EBO3.Unbind();

	VAO4.Unbind();
	VBO4.Unbind();
	EBO4.Unbind();

	VAO5.Unbind();
	VBO5.Unbind();
	EBO5.Unbind();

	VAO6.Unbind();
	VBO6.Unbind();
	EBO6.Unbind();

};

World_render::~World_render()
{
	// Delete all the objects we've created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	
	VAO2.Delete();
	VBO2.Delete();
	EBO2.Delete();

	VAO3.Delete();
	VBO3.Delete();
	EBO3.Delete();

	VAO4.Delete();
	VBO4.Delete();
	EBO4.Delete();

	VAO5.Delete();
	VBO5.Delete();
	EBO5.Delete();
	
	VAO6.Delete();
	VBO6.Delete();
	EBO6.Delete();
	
	
	dirt_side->Delete();
	grass->Delete();
	shaderProgram->Delete();
}




GLuint World_render::get_shaderid()
{
   return shaderProgram->ID;
}



void World_render::indices_add(GLfloat check_if_render) {
	//add indices of next cube
    if(check_if_render == 1.0f) indices.insert(indices.end(), start_indices.begin(), start_indices.end());
	else {

		indices.push_back(0);
		indices.push_back(0);
		indices.push_back(0);
		indices.push_back(0);
		indices.push_back(0);
		indices.push_back(0);


	}
	start_indices[0] += 4;
	start_indices[1] += 4;
	start_indices[2] += 4;
	start_indices[3] += 4;
	start_indices[4] += 4;
	start_indices[5] += 4;

}

void World_render::render()
{
	// Binds texture so that is appears in rendering
	dirt_side->Bind();

	// Bind the VAO so OpenGL knows to use it
	VAO1.Bind();
	glDrawElements(GL_TRIANGLES, sizeof(GLfloat) * Za_warudo[0].size(), GL_UNSIGNED_INT, 0);

	VAO2.Bind();
	glDrawElements(GL_TRIANGLES, sizeof(GLfloat) * Za_warudo[1].size(), GL_UNSIGNED_INT, 0);

	VAO3.Bind();
	glDrawElements(GL_TRIANGLES, sizeof(GLfloat) * Za_warudo[2].size(), GL_UNSIGNED_INT, 0);

	VAO4.Bind();
	glDrawElements(GL_TRIANGLES, sizeof(GLfloat) * Za_warudo[3].size(), GL_UNSIGNED_INT, 0);
	dirt_side->Unbind();


	dirt->Bind();
	VAO6.Bind();
	glDrawElements(GL_TRIANGLES, sizeof(GLfloat) * Za_warudo[4].size(), GL_UNSIGNED_INT, 0);
	dirt->Unbind();


	grass->Bind();
	VAO5.Bind();
	glDrawElements(GL_TRIANGLES, sizeof(GLfloat) * Za_warudo[5].size(), GL_UNSIGNED_INT, 0);
	grass->Unbind();

}

void World_render::shader_activate()
{

	shaderProgram->Activate();

}

void World_render::cube_remove(const glm::vec3& position, const glm::vec3& cameraDirection)
{
	/*
   //cordinates of the cube
	int x0, x1, y0, y1, z0, z1;
	for (int i = 0; i != map.size(); i++) {
		
		x0 = map[i][0];
		x1 = map[i][0] + 1.0f;

		y0 = map[i][1];
		y1 = map[i][1] + 1.0f;

		z0 = map[i][2];
		z1 = map[i][2] + 1.0f;
		// Points ahead of camera 
		glm::vec3 ThreeBlocksAheadPosition = position + (3.0f * cameraDirection);
		glm::vec3 TwoBlocksAheadPosition = position + (2.0f * cameraDirection);
		glm::vec3 OneBlocksAheadPosition = position + (1.0f * cameraDirection);
		
		if ((OneBlocksAheadPosition.x >= x0 && OneBlocksAheadPosition.x <= x1) && (OneBlocksAheadPosition.y >= y0 && OneBlocksAheadPosition.y <= y1) && (OneBlocksAheadPosition.z >= z0 && OneBlocksAheadPosition.z <= z1))
		{
			if (map[i][3] == 1) {
				int j = i * 6;
				// changing all indices of cube to 0 to stop render 
				indices[0 + j] = 0;
				indices[1 + j] = 0;
				indices[2 + j] = 0;
				indices[3 + j] = 0;
				indices[4 + j] = 0;
				indices[5 + j] = 0;

				map[i][3] = 0;

				map_update();
			}

		}
		else if ((TwoBlocksAheadPosition.x >= x0 && TwoBlocksAheadPosition.x <= x1) && (TwoBlocksAheadPosition.y >= y0 && TwoBlocksAheadPosition.y <= y1) && (TwoBlocksAheadPosition.z >= z0 && TwoBlocksAheadPosition.z <= z1))
		{
			if (map[i][3] == 1) {
				int j = i * 6;
				indices[0 + j] = 0;
				indices[1 + j] = 0;
				indices[2 + j] = 0;
				indices[3 + j] = 0;
				indices[4 + j] = 0;
				indices[5 + j] = 0;
				
				map[i][3] = 0;
				map_update();
			}
		}

		else if ((ThreeBlocksAheadPosition.x >= x0 && ThreeBlocksAheadPosition.x <= x1) && (ThreeBlocksAheadPosition.y >= y0 && ThreeBlocksAheadPosition.y <= y1) && (ThreeBlocksAheadPosition.z >= z0 && ThreeBlocksAheadPosition.z <= z1))
		{
			if (map[i][3] == 1) {
				int j = i * 6;
    			indices[0 + j] = 0;
				indices[1 + j] = 0;
				indices[2 + j] = 0;
				indices[3 + j] = 0;
				indices[4 + j] = 0;
				indices[5 + j] = 0;
				map[i][3] = 0;
				map_update();
			}
		}


	}
	*/
}


void World_render::cube_add(const glm::vec3& position, const glm::vec3& cameraDirection)
{
	/*
	//cube area
	GLfloat x0, x1, y0, y1, z0, z1;
	for (int i = 0; i != map.size(); i++) {
		x0 = map[i][0];
		x1 = map[i][0] + 1.0f;

		y0 = map[i][1];
		y1 = map[i][1] + 1.0f;

		z0 = map[i][2];
		z1 = map[i][2] + 1.0f;




		// Point ahead of camera 
		glm::vec3 ThreeBlocksAheadPosition = position + (3.0f * cameraDirection);
		glm::vec3 TwoBlocksAheadPosition = position + (2.0f * cameraDirection);
		glm::vec3 OneBlocksAheadPosition = position + (1.0f * cameraDirection);

		if ((OneBlocksAheadPosition.x >= x0 && OneBlocksAheadPosition.x <= x1) && (OneBlocksAheadPosition.y >= y0 && OneBlocksAheadPosition.y <= y1) && (OneBlocksAheadPosition.z >= z0 && OneBlocksAheadPosition.z <= z1))
		{
			if (map[i][3] == 0) {
				GLuint j = i * 6;
			
				GLuint x = i * 4;
				
				
				
				indices[0 + j] = x;
				indices[1 + j] = x+1;
				indices[2 + j] = x+2;
				indices[3 + j] = x;
				indices[4 + j] = x+3;
				indices[5 + j] = x+2;
				

				std::cout << indices[0 + j] << std::endl;
				std::cout << indices[1 + j] << std::endl;
				std::cout << indices[2 + j] << std::endl;
				std::cout << indices[3 + j] << std::endl;
				std::cout << indices[4 + j] << std::endl;
				std::cout << indices[5 + j] << std::endl;
				std::cout << std::endl;

				map[i][3] = 1;
				map_update();
			}
			
		}
	}
	*/
}



void World_render::map_update()
{
	
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();

	VAO2.Delete();
	VBO2.Delete();
	EBO2.Delete();

	VAO3.Delete();
	VBO3.Delete();
	EBO3.Delete();

	VAO4.Delete();
	VBO4.Delete();
	EBO4.Delete();

	VAO5.Delete();
	VBO5.Delete();
	EBO5.Delete();

	VAO6.Delete();
	VBO6.Delete();
	EBO6.Delete();
	
	// Generates Vertex Array Object and binds it
	VAO VAO1, VAO2, VAO3, VAO4, VAO5, VAO6;

	// Generates Vertex Buffer Object
	VBO VBO1, VBO2, VBO3, VBO4, VBO5, VBO6;
	// Generates Element Buffer Object
	EBO EBO1, EBO2, EBO3, EBO4, EBO5, EBO6;
	
	VAO1.Bind();

	// links Vertex Buffer Object to vertices
	VBO1.link(Za_warudo[0], sizeof(Za_warudo[0]));

	// links Element Buffer Object to indices
	EBO1.Link(indices, sizeof(indices));

	// Links VBO attributes such as coordinates and colors to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));




	VAO2.Bind();
	VBO2.link(Za_warudo[1], sizeof(Za_warudo[1]));
	EBO2.Link(indices, sizeof(indices));
	VAO2.LinkAttrib(VBO2, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO2.LinkAttrib(VBO2, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO2.LinkAttrib(VBO2, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	VAO3.Bind();
	VBO3.link(Za_warudo[2], sizeof(Za_warudo[2]));
	EBO3.Link(indices, sizeof(indices));
	VAO3.LinkAttrib(VBO3, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO3.LinkAttrib(VBO3, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO3.LinkAttrib(VBO3, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	VAO4.Bind();
	VBO4.link(Za_warudo[3], sizeof(Za_warudo[3]));
	EBO4.Link(indices, sizeof(indices));
	VAO4.LinkAttrib(VBO4, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO4.LinkAttrib(VBO4, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO4.LinkAttrib(VBO4, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	VAO5.Bind();
	VBO5.link(Za_warudo[4], sizeof(Za_warudo[4]));
	EBO5.Link(indices, sizeof(indices));
	VAO5.LinkAttrib(VBO5, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO5.LinkAttrib(VBO5, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO5.LinkAttrib(VBO5, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	VAO6.Bind();
	VBO6.link(Za_warudo[5], sizeof(Za_warudo[5]));
	EBO6.Link(indices, sizeof(indices));
	VAO6.LinkAttrib(VBO6, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO6.LinkAttrib(VBO6, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO6.LinkAttrib(VBO6, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));


	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	VAO2.Unbind();
	VBO2.Unbind();
	EBO2.Unbind();

	VAO3.Unbind();
	VBO3.Unbind();
	EBO3.Unbind();

	VAO4.Unbind();
	VBO4.Unbind();
	EBO4.Unbind();

	VAO5.Unbind();
	VBO5.Unbind();
	EBO5.Unbind();

	VAO6.Unbind();
	VBO6.Unbind();
	EBO6.Unbind();



}

void World_render::map_load(int chunk) {
	
	
		std::vector<std::vector<GLfloat>> temp_map;
		std::ifstream file("world/world.txt");



		std::string begin_chunk = "Chunk";
		begin_chunk += std::to_string(chunk);
		chunk++;
		std::string end_chunk = "Chunk";
		end_chunk += std::to_string(chunk);

		bool inDesiredRange = false;

		if (file.is_open()) {
			std::string line;

			while (std::getline(file, line)) {
				if (line.find(begin_chunk) != std::string::npos) {
					inDesiredRange = true;
					continue;
				}
				else if (line.find(end_chunk) != std::string::npos) {
					inDesiredRange = false;
					break;
				}

				if (inDesiredRange) {
					std::vector<GLfloat> row;
					std::istringstream iss(line);
					GLfloat value;

					while (iss >> value) {
						row.push_back(value);
					}

					temp_map.push_back(row);
				}
			}



			if (!temp_map.empty()) {
				map3d.push_back(temp_map);
			}

			file.close();
		}
		else {
			std::cerr << "Cannot open saved world" << std::endl;
		}
	}


void World_render::map_transform() {
	
	int map_size = map3d.size();
	for (int i = 0; i != map_size; i++) {
	
	int wall_number = 0;
	int cube_number = 0;


	
		while (cube_number != map3d[i].size()) {
			while (wall_number != 6) {
				std::vector<GLfloat > temp_wall = start_cube[wall_number];

				temp_wall[0] += map3d[i][cube_number][0];
				temp_wall[1] += map3d[i][cube_number][1];
				temp_wall[2] += map3d[i][cube_number][2];


				temp_wall[8] += map3d[i][cube_number][0];
				temp_wall[9] += map3d[i][cube_number][1];
				temp_wall[10] += map3d[i][cube_number][2];

				temp_wall[16] += map3d[i][cube_number][0];
				temp_wall[17] += map3d[i][cube_number][1];
				temp_wall[18] += map3d[i][cube_number][2];

				temp_wall[24] += map3d[i][cube_number][0];
				temp_wall[25] += map3d[i][cube_number][1];
				temp_wall[26] += map3d[i][cube_number][2];




				Za_warudo[wall_number].insert(Za_warudo[wall_number].end(), temp_wall.begin(), temp_wall.end());
				wall_number++;
			}
			indices_add(map3d[i][cube_number][3]);
			wall_number = 0;
			cube_number++;
		}
	}
}
