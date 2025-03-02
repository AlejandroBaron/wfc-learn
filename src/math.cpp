# include <random>

float noise(){
    std::random_device rd;
    std::mt19937 gen(rd());  // Mersenne Twister RNG
    std::normal_distribution<> dis(0.0, 1.0);  // Mean 0, Standard Deviation 1
    return dis(gen);
}