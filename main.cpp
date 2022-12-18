#include "json.hpp"
#include "DataArrays.h"
#include "DataTypes.h"
#include "jsonHandler.h"

using json = nlohmann::json;

int main() {

    List<Human> * directors;
    directors = deserializeJSON(loadFromFile("/Users/mleykhner/Documents/Курсовая 3 сем/MovieLibrary/resources/input.json"));
    writeToFile("/Users/mleykhner/Documents/Курсовая 3 сем/MovieLibrary/resources/output.json", serializeJSON(directors).dump(4));
    return 0;
}
