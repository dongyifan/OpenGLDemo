//
//  mesh.h
//  TinyOpenGL
//
//  Created by DongYifan on 2019/9/9.
//  Copyright © 2019 vanille. All rights reserved.
//

#ifndef mesh_h
#define mesh_h

#include <GL/glew.h> // holds all OpenGL type declarations

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

struct Texture {
    unsigned int id;
    std::string type;
};


#endif /* mesh_h */
