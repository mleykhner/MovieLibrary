#include "SFML/Graphics.hpp"
#include "DataArrays.h"

sf::Texture createBackgroundTexture(int windowWidth, int windowHeight, sf::Color color){
    //Создаем текстуру фона
    sf::Texture backgroundTexture;
    backgroundTexture.create(windowWidth, windowHeight);
    //Массив пикселей
    sf::Uint8 * backgroundPixels = new sf::Uint8 [windowHeight * windowWidth * 4];
    //Раскладываем цвет на составляющие
    sf::Uint8 myColor[4] = {color.r, color.g, color.b, color.a};
    //Записываем цвет в каждый пиксель
    for(int pixel = 0; pixel < windowWidth * windowHeight * 4; pixel++){
        backgroundPixels[pixel] = myColor[pixel % 4];
    }
    //Обновляем текстуру новыми пикселями
    backgroundTexture.update(backgroundPixels);
    //Возвращаем текстуру
    return backgroundTexture;
}
