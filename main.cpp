// Copyright 2024 Marquzes Ford Jr
#include "FibLFSR.hpp"
#include "PhotoMagic.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <input image> <output image> <LFSR seed>"
                  << std::endl;
        return -1;
    }

    std::string inputFile = argv[1];
    std::string outputFile = argv[2];
    std::string lfsrSeed = argv[3];

    sf::Image image, transformedImage;
    if (!image.loadFromFile(inputFile)) {
        std::cerr << "Error: Could not load image " << inputFile
                  << std::endl;
        return -1;
    }

    transformedImage = image;
    PhotoMagic::FibLFSR lfsr(lfsrSeed);
    PhotoMagic::transform(transformedImage, &lfsr);

    sf::Vector2u size = image.getSize();
    sf::RenderWindow originalWindow(sf::VideoMode(size.x, size.y), "Original Image");
    sf::RenderWindow transformedWindow(sf::VideoMode(size.x, size.y), "Transformed Image");

    sf::Texture originalTexture, transformedTexture;
    originalTexture.loadFromImage(image);
    transformedTexture.loadFromImage(transformedImage);

    sf::Sprite originalSprite, transformedSprite;
    originalSprite.setTexture(originalTexture);
    transformedSprite.setTexture(transformedTexture);

    while (originalWindow.isOpen() && transformedWindow.isOpen()) {
        sf::Event event;
        while (originalWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                originalWindow.close();
        }

        while (transformedWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                transformedWindow.close();
        }

        originalWindow.clear(sf::Color::White);
        originalWindow.draw(originalSprite);
        originalWindow.display();

        transformedWindow.clear(sf::Color::White);
        transformedWindow.draw(transformedSprite);
        transformedWindow.display();
    }

    if (!transformedImage.saveToFile(outputFile)) {
        std::cerr << "Error: Could not save transformed image to " << outputFile
                  << std::endl;
        return -1;
    }

    return 0;
}
