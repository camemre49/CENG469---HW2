#ifndef GLOBALS_H
#define GLOBALS_H
#include "base.h"

// Global variables declarations
extern GLuint vao[3];
extern GLuint gProgram[3];
extern GLuint texture;
extern int gWidth, gHeight;

extern GLint modelingMatrixLoc[2];
extern GLint viewingMatrixLoc[2];
extern GLint projectionMatrixLoc[2];
extern GLint eyePosLoc[2];

extern glm::mat4 projectionMatrix;
extern glm::mat4 viewingMatrix;
extern glm::mat4 modelingMatrix;
extern glm::vec3 eyePos;
extern glm::vec3 eyeGaze;
extern glm::vec3 eyeUp;

extern std::map<GLchar, Character> Characters;

extern std::vector<Vertex> gVertices[2];
extern std::vector<Texture> gTextures[2];
extern std::vector<Normal> gNormals[2];
extern std::vector<Face> gFaces[2];

extern GLuint gVertexAttribBuffer[2];
extern GLuint gIndexBuffer[2];
extern GLuint gTextVBO;
extern GLint gInVertexLoc[2];
extern GLint gInNormalLoc[2];
extern int gVertexDataSizeInBytes[2], gNormalDataSizeInBytes[2], gTextureDataSizeInBytes[2];

extern GLFWwindow* window;


#endif //GLOBALS_H
