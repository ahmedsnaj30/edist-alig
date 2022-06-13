// Copyright 2022 Ahmed Shaheen
#include "Matrix.h"
#include "EDistance.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>


int main(int argc, char *argv[]) {
    sf::Clock clock;
    sf::Time t;

    // std::string h = "AACAGTTACC";
    // std::string w = "TAAGGTCA";
    std::string h;
    std::string w;
    std::cin >> h;
    std::cin >> w;
    EDistance dist(h, w);
    std::cout << "Edit Distance = " << dist.optDistance() << std::endl;
    dist.printMatrix();

    std::cout << dist.alignment();

    t = clock.getElapsedTime();
    std::cout << "Execution time is " << t.asSeconds() << " seconds \n";

    return 0;
}
