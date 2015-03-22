#include "GameModels.h"
#include "VertexFormat.h"

using namespace Models;
using namespace std;

GameModels::GameModels(){  }
GameModels::~GameModels()
{
    map<string, Model>::iterator it;
    for (it = gameModelList.begin(); it != gameModelList.end(); ++it)
    {
        // Delete VAO and VBOs related to every models
        unsigned int* p = &it->second.vao;
        glDeleteVertexArrays(1, p);
        glDeleteBuffers(it->second.vbos.size(), &it->second.vbos[0]);
        it->second.vbos.clear();
    }
    
    gameModelList.clear();
}
void GameModels::createTriangleModel(const std::string &gameModelName)
{
    unsigned int vao;
    unsigned int vbo;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    vector<VertexFormat> vertices; // Vertices position on the stack
    vertices.push_back(VertexFormat(glm::vec3( 0.25, -0.25, 0.0)));
    vertices.push_back(VertexFormat(glm::vec3(-0.25, -0.25, 0.0)));
    vertices.push_back(VertexFormat(glm::vec3( 0.25,  0.25, 0.0)));

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, vertices.size(), GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)0);

    Model myModel;
    myModel.vao = vao;
    myModel.vbos.push_back(vbo);
    gameModelList[gameModelName] = myModel; // Store model info in map
}
void GameModels::deleteModel(const std::string &gameModelName)
{
    Model model = gameModelList[gameModelName];
    unsigned int p = model.vao;
    glDeleteVertexArrays(1, &p);
    glDeleteBuffers(model.vbos.size(), &model.vbos[0]);
    model.vbos.clear();
    gameModelList.erase(gameModelName);
}

unsigned int GameModels::getModel(const std::string &gameModelName){
    return gameModelList[gameModelName].vao;
}