#include "ProceduralGen.h"
#include <cmath>
#include <algorithm>
#include <iostream>
#include <random>
#include <fstream>

ProceduralGen::ProceduralGen() {
    // Inicjalizacja permutacji
    for (int i = 0; i < 256; ++i) {
        p.push_back(i);
    }

    // Mieszanie permutacji
    std::random_device rd;
    std::mt19937 gen(rd());
    for (int i = 0; i < 256; ++i) {
        int j = i + gen() % (256 - i);
        std::swap(p[i], p[j]);
        p.push_back(p[i]);
    }

    for (int i = 0; i < ChunkSize; ++i) {
        for (int j = 0; j < ChunkSize; ++j) {
            int value = noise(i * 0.05, j * 0.05, 0.0);
            gen_map.push_back(value);
        }
    }

    convert_to_cord3d();
    saveToFile();
}

int ProceduralGen::noise(double x, double y, double z) {
    int X = static_cast<int>(std::floor(x)) & 255;
    int Y = static_cast<int>(std::floor(y)) & 255;
    int Z = static_cast<int>(std::floor(z)) & 255;
    x -= std::floor(x);
    y -= std::floor(y);
    z -= std::floor(z);
    double u = fade(x);
    double v = fade(y);
    double w = fade(z);
    int A = p[X] + Y;
    int AA = p[A] + Z;
    int AB = p[A + 1] + Z;
    int B = p[X + 1] + Y;
    int BA = p[B] + Z;
    int BB = p[B + 1] + Z;
    double result = lerp(w, lerp(v, lerp(u, grad(p[AA], x, y, z), grad(p[BA], x - 1, y, z)),
        lerp(u, grad(p[AB], x, y - 1, z), grad(p[BB], x - 1, y - 1, z))),
        lerp(v, lerp(u, grad(p[AA + 1], x, y, z - 1), grad(p[BA + 1], x - 1, y, z - 1)),
            lerp(u, grad(p[AB + 1], x, y - 1, z - 1), grad(p[BB + 1], x - 1, y - 1, z - 1))));
    return static_cast<int>((result + 1.0) * 5.0);
}

double ProceduralGen::fade(double t) {
    return t * t * t * (t * (t * 6 - 15) + 10);
}

double ProceduralGen::lerp(double t, double a, double b) {
    return a + t * (b - a);
}

double ProceduralGen::grad(int hash, double x, double y, double z) {
    int h = hash & 15;
    double grad = 1 + (h & 7);
    if (h & 8) grad = -grad;
    return (h & 1 ? x : -x) + (h & 2 ? y : -y) + (h & 4 ? z : -z);
}

void ProceduralGen::convert_to_cord3d() {
    int temp_x = 0;
    int temp_y = 0;
    int temp_z = 0;

    for (int j = 0; j != gen_map.size(); j++) {
        int render = 1;

        if (temp_x == ChunkSize) {
            temp_x = 0;
            temp_y++;
        }

        for (int i = 0; i < ChunkSize; i++) {
            cord_3d.push_back({ temp_x, temp_z, temp_y, render });
            temp_z++;
            if (i > gen_map[j]) render = 0;
        }

        temp_x++;
        temp_z = 0;
    }
}

void ProceduralGen::saveToFile() {
    std::ofstream outputFile("world/world.txt");

    if (!outputFile.is_open()) {
        std::cerr << "Nie mo¿na otworzyæ pliku do zapisu." << std::endl;
        return;
    }

    outputFile << "Chunk0" << std::endl;

    for (const auto& row : cord_3d) {
        for (int value : row) {
            outputFile << value << ' ';
        }
        outputFile << std::endl;
    }

    outputFile << "Chunk1" << std::endl;
    outputFile.close();

    std::cout << "Zapisano do pliku world/world.txt" << std::endl;
}
