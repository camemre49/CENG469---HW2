#include "../headers/globals.h"

// =============================================
// Global OpenGL Identifiers
// =============================================
GLuint vao[3];
GLuint gProgram[3];
GLuint geometryPassProgram;
int gWidth = 640, gHeight = 480;

// =============================================
// Transformation Matrices
// =============================================
GLint modelingMatrixLoc[2];
GLint viewingMatrixLoc[2];
GLint projectionMatrixLoc[2];
GLint eyePosLoc[2];

// =============================================
// Camera Setup
// =============================================
float fovyRad = (float)(90.0f / 180.0) * M_PI;
glm::mat4 projectionMatrix = glm::perspective(fovyRad, 1.0f, 1.0f, 100.0f);
glm::mat4 modelingMatrix;
// Camera is at (0, 0, 0)
glm::vec3 eyePos(0, 0, 0);
// Looking at -z direction
glm::vec3 eyeGaze(0, 0, -1);
// up vector pointing at +y direction
glm::vec3 eyeUp(0, 1, 0);
glm::mat4 viewingMatrix = glm::lookAt(eyePos, eyePos + eyeGaze, eyeUp);

// =============================================
// Font Rendering (e.g., for displaying text with FreeType)
// =============================================
std::map<GLchar, Character> Characters;
std::string lastPressedKey;
uint keyPressShowingFrameCount = 30;
bool shouldMove = true;
RenderMode currentRenderMode = TONEMAPPED;

// =============================================
// Mesh Data for Two Models
// =============================================
std::vector<Vertex> gVertices[2];
std::vector<Texture> gTextures[2];
std::vector<Normal> gNormals[2];
std::vector<Face> gFaces[2];

// =============================================
// OpenGL Buffer Objects
// =============================================
GLuint gVertexAttribBuffer[2];
GLuint gIndexBuffer[2];
GLuint gTextVBO;
GLint gInVertexLoc[2];
GLint gInNormalLoc[2];
int gVertexDataSizeInBytes[2], gNormalDataSizeInBytes[2], gTextureDataSizeInBytes[2];

// =============================================
// Window Related Variables
// =============================================
GLFWwindow* window;
GLuint fps;
bool vsync = true;

// =============================================
// Cubemap Initialization and Control
// =============================================
GLuint cubemapTexture;
GLint exposure = 1;
GLfloat key = 0.18;
GLfloat gammaValue = 2.2;
GLfloat logAverageLuminance = 0;

// =============================================
// Cubemap Initialization and Control
// =============================================
GLuint gBuffer;
GLuint gPosition, gNormal, gAlbedoSpec;

