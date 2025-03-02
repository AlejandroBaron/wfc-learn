# include <random>

float noise(){
    std::random_device rd;
    std::mt19937 gen(rd());  // Mersenne Twister RNG
    std::uniform_real_distribution<> dis(0.0, 1.0);  // uniform dist
    return dis(gen);
}