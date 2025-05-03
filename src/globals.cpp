#include "../headers/globals.h"

// ---------- Global OpenGL Identifiers ----------

// Vertex Array Objects for storing vertex attribute configurations (e.g., for 2 meshes + text)
GLuint vao[3];

// Shader program identifiers (e.g., separate programs for object rendering and text rendering)
GLuint gProgram[3];

// Texture ID used for text rendering or object texturing
GLuint texture;

// Window dimensions
int gWidth = 640, gHeight = 480;

// ---------- Uniform Locations (for sending matrices and eye position to shaders) ----------

// Locations of the modeling matrix uniforms in the shader programs (per object type)
GLint modelingMatrixLoc[2];

// Locations of the viewing matrix uniforms in the shader programs
GLint viewingMatrixLoc[2];

// Locations of the projection matrix uniforms in the shader programs
GLint projectionMatrixLoc[2];

// Locations of the eye (camera) position uniform in the shader programs
GLint eyePosLoc[2];

// ---------- Transformation Matrices ----------

// Projection matrix for converting 3D coordinates to 2D screen coordinates
glm::mat4 projectionMatrix;

// Viewing matrix representing the camera's position and orientation in the scene
glm::mat4 viewingMatrix;

// Modeling matrix for positioning, rotating, and scaling individual objects
glm::mat4 modelingMatrix;

// ---------- Camera Setup ----------

// Eye (camera) position in world space
glm::vec3 eyePos(0, 0, 0);

// The direction the camera is looking toward
glm::vec3 eyeGaze(0, 0, -1);

// The up direction relative to the camera (defines camera's roll)
glm::vec3 eyeUp(0, 1, 0);

// ---------- Font Rendering (e.g., for displaying text with FreeType) ----------

// Map of characters to their associated texture and size metrics
std::map<GLchar, Character> Characters;

// ---------- Mesh Data for Two Models ----------

// Vertex positions for two different objects (indexed by 0 and 1)
std::vector<Vertex> gVertices[2];

// Texture coordinates for the two objects
std::vector<Texture> gTextures[2];

// Normals for lighting calculations for each object
std::vector<Normal> gNormals[2];

// Face indices (e.g., triangles made of vertices, used for drawing objects)
std::vector<Face> gFaces[2];

// ---------- OpenGL Buffer Objects ----------

// Vertex attribute buffers (used to store vertices, normals, textures on GPU)
GLuint gVertexAttribBuffer[2];

// Index buffers (used for drawing vertices via element arrays)
GLuint gIndexBuffer[2];

// Vertex buffer object for rendering text (usually separate from mesh data)
GLuint gTextVBO;

// Locations of the input vertex attribute in the shaders
GLint gInVertexLoc[2];

// Locations of the input normal attribute in the shaders
GLint gInNormalLoc[2];

// Sizes of vertex data buffers (in bytes) for each object
int gVertexDataSizeInBytes[2], gNormalDataSizeInBytes[2], gTextureDataSizeInBytes[2];

// ---------- GLFW Window Pointer ----------

// Pointer to the GLFW window object
GLFWwindow* window;
