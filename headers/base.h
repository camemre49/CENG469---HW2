#ifndef BASE_H
#define BASE_H
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <cassert>
#include <cmath>

// OpenGL libraries
#define _USE_MATH_DEFINES
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include <map>
#include <ft2build.h>
#include FT_FREETYPE_H


// Gets the index and convert it into a pointer offset
#define CONVERT_TO_BUFFER_OFFSET(i) ((char*)NULL + (i))

#define IS_CUBEMAP_PROGRAM(i) (i == 1)

// Struct definitions
struct Vertex {
    Vertex(GLfloat inX, GLfloat inY, GLfloat inZ) : x(inX), y(inY), z(inZ) {}
    GLfloat x, y, z;
};

struct Texture {
    Texture(GLfloat inU, GLfloat inV) : u(inU), v(inV) {}
    GLfloat u, v;
};

struct Normal {
    Normal(GLfloat inX, GLfloat inY, GLfloat inZ) : x(inX), y(inY), z(inZ) {}
    GLfloat x, y, z;
};

struct Face {
    Face(int v[], int t[], int n[]) {
        vIndex[0] = v[0];
        vIndex[1] = v[1];
        vIndex[2] = v[2];
        tIndex[0] = t[0];
        tIndex[1] = t[1];
        tIndex[2] = t[2];
        nIndex[0] = n[0];
        nIndex[1] = n[1];
        nIndex[2] = n[2];
    }
    GLuint vIndex[3], tIndex[3], nIndex[3];
};

/// Holds all state information relevant to a character as loaded using FreeType
struct Character {
    GLuint TextureID;   // ID handle of the glyph texture
    glm::ivec2 Size;    // Size of glyph
    glm::ivec2 Bearing; // Offset from baseline to left/top of glyph
    GLuint Advance;     // Horizontal offset to advance to next glyph
};

enum RenderMode {
    TONEMAPPED, // = 0
    CUBE_ONLY, // = 1
    MODELS_WORLD_POS, // = 2
    MODELS_WORLD_NOR, // = 3
    DEFERRED_RENDERING, // = 4
    COMPOSITE, // = 5
};
inline std::string toString(RenderMode mode) {
    switch (mode) {
        case TONEMAPPED: return "TONEMAPPED";
        case CUBE_ONLY: return "CUBE_ONLY";
        case MODELS_WORLD_POS: return "MODELS_WORLD_POS";
        case MODELS_WORLD_NOR: return "MODELS_WORLD_NOR";
        case DEFERRED_RENDERING: return "DEFERRED_RENDERING";
        case COMPOSITE: return "COMPOSITE";
        default: return "UNKNOWN";
    }
}

// =============================================
// File & Resource Loading Utilities
// =============================================
bool ReadDataFromFile(const std::string& fileName, std::string& data);
bool ParseObj(const std::string& fileName, int objId);

// =============================================
// Shader Management
// =============================================
GLuint createVS(const char* shaderName);
GLuint createFS(const char* shaderName);
void initShaders();

// =============================================
// Rendering & Graphics Initialization
// =============================================
void initVBO();
GLFWwindow*  initWindow();
void setCallbacks();
void calculateCurrentFps();

// =============================================
// Text Initialization & Rendering
// =============================================
void initFonts(int windowWidth, int windowHeight);
void renderText(const std::string& text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
void displayTexts();
void savePressedKey(int key, int scancode);

// =============================================
// Cubemap Texture Initialization & Control
// =============================================
void initCubemap();

// =============================================
// Deferred Rendering
// =============================================
void initGBuffer();
void initQuad();
void makeGeometryPass();
void renderGeometry();

#endif //BASE_H
