#include <random>
class Random {
    static std::mt19937 random;

public:
    static int Int(int min, int max){std::uniform_int_distribution<int> dist(min, max);
        return dist(random);};
    static float Float(float min, float max){std::uniform_real_distribution<float> dist(min, max);
        return dist(random);};
};

