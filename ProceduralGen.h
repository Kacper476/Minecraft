#ifndef PROCEDURAL_GEN_H
#define PROCEDURAL_GEN_H

#include <vector>
constexpr int ChunkSize = 16;

class ProceduralGen {
public:
    ProceduralGen();
    int noise(double x, double y, double z);

private:
    
    
    std::vector<int> p;
    std::vector<int> gen_map;
    std::vector<std::vector<int> > cord_3d;


    double fade(double t);
    double lerp(double t, double a, double b);
    double grad(int hash, double x, double y, double z);
    void convert_to_cord3d();
    void saveToFile();
};

#endif // PROCEDURAL_GEN_H
