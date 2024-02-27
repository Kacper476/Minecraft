#include "World_create.h"



World_create::World_create()
{
    world_generate();
    save_to_file();
};

void World_create::world_generate() {

    std::vector<GLfloat> temp{ x, y, z, render };
   
    for (int i = 0; i != 1; i++) {
        for (int map_length = 0; map_length != 5; map_length++) {
            for (int map_width = 0; map_width != 5; map_width++) {
                chunk_generate(temp);
                x += 10;
            }
            x = 0;
            z += 10;
        }
    }

}

void World_create::chunk_generate(std::vector<GLfloat> temp)
{
    GLfloat local_x = x;
    GLfloat local_z=z;
    GLfloat local_y=y;
    GLfloat local_render=render;
   
    generated_world.push_back({ 2137 });// mark begin of the chunk
    for (int k = 0; k != 10; k++)
    {
        

        for (int j = 0; j != 16; j++) {
            for (int i = 0; i != 16; i++) {

                local_render = 1.0f;
                temp[0] = local_x;
                temp[1] = local_y;
                temp[2] = local_z;
                temp[3] = local_render;
                generated_world.push_back(temp);
                local_x++;
            }
            local_x = x;
            local_z++;
        }
        local_z = z;
        local_x = x;
        local_y--;

    }


    
    



}


void World_create::save_to_file() {
    std::string filePath = "world/world.txt"; // Pe³na œcie¿ka do pliku
    std::ofstream file(filePath);
    
    if (file.is_open()) {
        for (const std::vector<GLfloat>& row : generated_world) {
            for (GLfloat value : row) {
            
 
                if (value == 2137) {  
                    file << "Chunk" << chunk_number;
                    chunk_number++;
                
                
                }
                else {
                    
                
                    file << value << ' ';
                }
        
            }
           
            file << '\n'; // Nowy wiersz po ka¿dym rzêdzie
           
        }
        
        file << "Chunk" << chunk_number;
        file.close();
       
    }
    else {
        std::cerr << "Cannot open file to save." << std::endl;
    }
}
