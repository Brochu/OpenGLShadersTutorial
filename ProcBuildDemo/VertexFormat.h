#ifndef VertexFormat_H_
#define VertexFormat_H_

#include "glm\glm.hpp"

struct VertexFormat {
    glm::vec3 position; // First vertex attribute

    VertexFormat(const glm::vec3 &pos){
        position = pos;
    }
};
#endif // !VertexFormat_H_