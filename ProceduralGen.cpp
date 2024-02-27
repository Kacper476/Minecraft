#include "ProceduralGen.h"
#include <fstream>

ProceduralGen::ProceduralGen() {
    // Inicjalizacja permutacji
    for (int i = 0; i < 256; ++i) {
        p[i] = i;
    }

    // Mieszanie permutacji
    for (int i = 0; i < 256; ++i) {
        int j = i + rand() % (256 - i);
        std::swap(p[i], p[j]);
        p[i + 256] = p[i];
    }
 
}

double ProceduralGen::noise(double x, double y, double z) {
    // Zamiana wspó³rzêdnych na liczby ca³kowite
    int X = static_cast<int>(std::floor(x)) & 255;
    int Y = static_cast<int>(std::floor(y)) & 255;
    int Z = static_cast<int>(std::floor(z)) & 255;

    // Pobranie czêœci u³amkowej wspó³rzêdnych
    x -= std::floor(x);
    y -= std::floor(y);
    z -= std::floor(z);

    // Obliczenie sk³adowych gradientu
    double u = fade(x);
    double v = fade(y);
    double w = fade(z);

    // Wygenerowanie haszowania
    int A = p[X] + Y;
    int AA = p[A] + Z;
    int AB = p[A + 1] + Z;
    int B = p[X + 1] + Y;
    int BA = p[B] + Z;
    int BB = p[B + 1] + Z;

    // Interpolacja gradientów
    double result = lerp(w, lerp(v, lerp(u, grad(p[AA], x, y, z),
        grad(p[BA], x - 1, y, z)),
        lerp(u, grad(p[AB], x, y - 1, z),
            grad(p[BB], x - 1, y - 1, z))),
        lerp(v, lerp(u, grad(p[AA + 1], x, y, z - 1),
            grad(p[BA + 1], x - 1, y, z - 1)),
            lerp(u, grad(p[AB + 1], x, y - 1, z - 1),
                grad(p[BB + 1], x - 1, y - 1, z - 1))));

    // Ograniczenie zakresu do 0-10
    return (result + 1.0) * 5.0;
}

double ProceduralGen::fade(double t) {
    return t * t * t * (t * (t * 6 - 15) + 10);
}

double ProceduralGen::lerp(double t, double a, double b) {
    return a + t * (b - a);
}

double ProceduralGen::grad(int hash, double x, double y, double z) {
    int h = hash & 15;
    double grad = 1 + (h & 7); // Gradient value 1-8
    if (h & 8) grad = -grad;   // Randomly invert half of them
    return (h & 1 ? x : -x) + (h & 2 ? y : -y) + (h & 4 ? z : -z);
}

void ProceduralGen::load_proceduralmap()
{
    gen_map_height();

    std::ifstream file("world/world.txt");



    std::string begin_chunk = "Chunk0";

    std::string end_chunk = "Chunk1";

    bool inDesiredRange = false;



    if (file.is_open()) {
        
        std::string line;
        std::string temp_x;
        std::string temp_z;
        std::ofstream output_file("world/world_modified.txt");

        int number_pos = 0;

        while (std::getline(file, line)) {
          

               
                   
            if (line[0] != 'C') {
                line.pop_back();
                line.back() = '0';
            }

            for (int i=0; i != line.size(); i++)
            {
                if (line[i] == ' ')break;
                temp_x.push_back(line[i]);
                number_pos = i ;
            }

            for (number_pos; number_pos != line.size(); number_pos)
            {
                if (line[number_pos] == ' ')break;
                temp_z.push_back(line[number_pos]);
            }





            std::cout  << " " << temp_z << std::endl;




                    output_file << line << std::endl;
                
               
          



                    temp_x.clear();
                    temp_z.clear();
        }
    }
}

void ProceduralGen::gen_map_height()
{

    for (int j = 0; j < 16; ++j) {
        int value = noise(0 * 0.1, j * 0.1, 0.0);
        map_height.push_back(value);
        
    }


}

