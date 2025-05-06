#ifndef GLOBALS_H
#define GLOBALS_H
#include "base.h"

// =============================================
// Global OpenGL Identifiers
// =============================================

// Vertex Array Objects for storing vertex attribute configurations (e.g., for 2 meshes + text)
extern GLuint vao[3];
// Shader program identifiers (e.g., separate programs for object rendering and text rendering)
extern GLuint gProgram[3];
// Geometry pass shader program
extern GLuint geometryPassProgram;
// Program to show geometry of objects
extern GLuint geometryVisualizeProgram;
// Program to apply motion blur
extern GLuint motionBlurProgram;
// Window dimensions
extern int gWidth, gHeight;


// =============================================
// Uniform Locations (for sending matrices and eye position to shaders)
// =============================================

// Locations of the modeling matrix uniforms in the shader programs (per object type)
extern GLint modelingMatrixLoc[2];
// Locations of the viewing matrix uniforms in the shader programs
extern GLint viewingMatrixLoc[2];
// Locations of the projection matrix uniforms in the shader programs
extern GLint projectionMatrixLoc[2];
// Locations of the eye (camera) position uniform in the shader programs
extern GLint eyePosLoc[2];


// =============================================
// Transformation Matrices
// =============================================

// Projection matrix for converting 3D coordinates to 2D screen coordinates
extern glm::mat4 projectionMatrix;
// Viewing matrix representing the camera's position and orientation in the scene
extern glm::mat4 viewingMatrix;
// Modeling matrix for positioning, rotating, and scaling individual objects
extern glm::mat4 modelingMatrix;


// =============================================
// Camera Setup
// =============================================

// Eye (camera) position in world space
extern glm::vec3 eyePos;
// The direction the camera is looking toward
extern glm::vec3 eyeGaze;
// The up direction relative to the camera (defines camera's roll)
extern glm::vec3 eyeUp;


// =============================================
// Font Rendering (e.g., for displaying text with FreeType)
// =============================================

// Map of characters to their associated texture and size metrics
extern std::map<GLchar, Character> Characters;
extern std::string lastPressedKey;
extern uint keyPressShowingFrameCount;
extern bool shouldMove;
extern RenderMode currentRenderMode;


// =============================================
// Mesh Data for Armadillo, Cubemap
// =============================================

// Vertex positions for two different objects (indexed by 0 and 1)
extern std::vector<Vertex> gVertices[2];
// Texture coordinates for the two objects
extern std::vector<Texture> gTextures[2];
// Normals for lighting calculations for each object
extern std::vector<Normal> gNormals[2];
// Face indices (e.g., triangles made of vertices, used for drawing objects)
extern std::vector<Face> gFaces[2];


// =============================================
// OpenGL Buffer Objects
// =============================================

// Vertex attribute buffers (used to store vertices, normals, textures on GPU)
extern GLuint gVertexAttribBuffer[2];
// Index buffers (used for drawing vertices via element arrays)
extern GLuint gIndexBuffer[2];
// Vertex buffer object for rendering text (usually separate from mesh data)
extern GLuint gTextVBO;
// Locations of the input vertex attribute in the shaders
extern GLint gInVertexLoc[2];
// Locations of the input normal attribute in the shaders
extern GLint gInNormalLoc[2];
// Sizes of vertex data buffers (in bytes) for each object
extern int gVertexDataSizeInBytes[2], gNormalDataSizeInBytes[2], gTextureDataSizeInBytes[2];


// =============================================
// Window Related Variables
// =============================================

// Pointer to the GLFW window object
extern GLFWwindow* window;
extern int windowedXPos, windowedYPos, windowedWidth, windowedHeight;
extern GLuint fps;
extern bool vsync;


// =============================================
// Cubemap Initialization and Control
// =============================================

// Texture ID used for cubemap rendering
extern GLuint cubemapTexture;
// Current exposure value of the cubemap fragment shader
extern GLfloat exposure;
// Key value of Reinhard Tonemapping
extern GLfloat keyValue;
// Gamma correction value
extern GLfloat gammaValue;
// Reingard tone mapping average luminance
extern GLfloat logAverageLuminance;

// =============================================
// Deferred Rendering Buffers
// =============================================
extern GLuint gBuffer;
extern GLuint gPosition, gNormal, gDepth;
extern unsigned int quadVAO;

// =============================================
// Mouse Control
// =============================================
extern float mouseSensitivity;
extern float yaw;
extern float pitch;

// =============================================
// Motion Blur
// =============================================
extern GLuint sceneFBO, sceneColorTex, sceneDepthRBO;
extern bool isBlurEnabled;
extern float blurAmount;
extern float blurScale;
extern float previousYaw;
extern float previousPitch;
extern double previousTime;

#endif // GLOBALS_H