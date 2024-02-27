#ifndef PROCEDURALGEN_CLASS_H
#define PROCEDURALGEN_CLASS_H
#include <cmath>
#include <algorithm>
#include <ctime>
#include <string>
#include <fstream>
#include <iostream>
#include<vector>

class ProceduralGen {
public:
    ProceduralGen();

    double noise(double x, double y, double z);
    void load_proceduralmap();


private:
    int p[512];
    std::vector<int> map_height;
    double fade(double t);
    double lerp(double t, double a, double b);
    double grad(int hash, double x, double y, double z);
    void gen_map_height();

};
#endif