#ifndef GAME_MODELS_H_
#define GAME_MODELS_H_

#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <vector>
#include <map>

namespace Models
{
    // Structure explained in part 3 ... we'll see
    struct Model{
        unsigned int vao;
        std::vector<unsigned int> vbos;

        Model(){}
    };

    class GameModels
    {
    public:
        GameModels();
        ~GameModels();

        void createTriangleModel(const std::string &gameModelName);
        void deleteModel(const std::string &gameModelName);
        unsigned int getModel(const std::string &gameModelName);

    private:
        std::map<std::string, Model> gameModelList; // keep models in a map
    };
}
#endif