#ifndef RANDOMIZERH
#define RANDOMIZERH

#include <random>


class Randomizer {
    private:
        static std::random_device rd;
        static std::mt19937 gen;
        static std::uniform_real_distribution<float> dis;

    public:
        static float get_random_number() {
            return dis(gen);
        };
};

std::random_device Randomizer::rd;
std::mt19937 Randomizer::gen = std::mt19937(rd());
std::uniform_real_distribution<float> Randomizer::dis = std::uniform_real_distribution((float) 0.0, (float) 0.99999);

#endif
