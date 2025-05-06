#include "../headers/globals.h"
using namespace std;

GLuint createVS(const char* shaderName)
{
	const string vsFolderName = "vs";
    string shaderSource;

    string filename(vsFolderName + "/" +shaderName);
    if (!ReadDataFromFile(filename, shaderSource))
    {
        cout << "Cannot find file name: " + filename << endl;
        exit(-1);
    }

    GLint length = shaderSource.length();
    const GLchar* shader = (const GLchar*)shaderSource.c_str();

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &shader, &length);
    glCompileShader(vs);

    char output[1024] = { 0 };
    glGetShaderInfoLog(vs, 1024, &length, output);
    printf("VS compile log: %s\n", output);

    return vs;
}

GLuint createFS(const char* shaderName)
{
	const string vsFolderName = "fs";
	string shaderSource;

	string filename(vsFolderName + "/" +shaderName);
    if (!ReadDataFromFile(filename, shaderSource))
    {
        cout << "Cannot find file name: " + filename << endl;
        exit(-1);
    }

    GLint length = shaderSource.length();
    const GLchar* shader = (const GLchar*)shaderSource.c_str();

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &shader, &length);
    glCompileShader(fs);

    char output[1024] = { 0 };
    glGetShaderInfoLog(fs, 1024, &length, output);
    printf("FS compile log: %s\n", output);

    return fs;
}

void initShaders()
{
	// Create the programs

	gProgram[0] = glCreateProgram(); //for armadillo
	gProgram[1] = glCreateProgram(); //for background quad
	gProgram[2] = glCreateProgram(); //for text rendering
	geometryPassProgram = glCreateProgram(); // for geometry pass
	geometryVisualizeProgram = glCreateProgram(); // for geometry rendering
	motionBlurProgram = glCreateProgram(); // for motion blur

	// Create the shaders for both programs

	//for armadillo
	GLuint vs1 = createVS("vert.glsl");
	GLuint fs1 = createFS("frag.glsl");

	//for background quad
	GLuint vs2 = createVS("vert_cubemap.glsl");
	GLuint fs2 = createFS("frag_cubemap.glsl");

	//for texts
	GLuint vs3 = createVS("vert_text.glsl");
	GLuint fs3 = createFS("frag_text.glsl");

	// for geometry pass
	GLuint shaderVs = createVS("vert_geometry.glsl");
	GLuint shaderFs = createFS("frag_geometry.glsl");

	GLuint visualizeVS = createVS("vert_geometry_visualization.glsl");
	GLuint visualizeFS = createFS("frag_geometry_visualization.glsl");

	GLuint motionBlurVS = createVS("vert_motion_blur.glsl");
	GLuint motionBlurFS = createFS("frag_motion_blur.glsl");

	// Attach the shaders to the programs

	glAttachShader(gProgram[0], vs1);
	glAttachShader(gProgram[0], fs1);

	glAttachShader(gProgram[1], vs2);
	glAttachShader(gProgram[1], fs2);

	glAttachShader(gProgram[2], vs3);
	glAttachShader(gProgram[2], fs3);

	glAttachShader(geometryPassProgram, shaderVs);
	glAttachShader(geometryPassProgram, shaderFs);

	glAttachShader(geometryVisualizeProgram, visualizeVS);
	glAttachShader(geometryVisualizeProgram, visualizeFS);

	glAttachShader(motionBlurProgram, motionBlurVS);
	glAttachShader(motionBlurProgram, motionBlurFS);

	// Link the programs

	glLinkProgram(gProgram[0]);
	GLint status;
	glGetProgramiv(gProgram[0], GL_LINK_STATUS, &status);

	if (status != GL_TRUE)
	{
		cout << "Program link failed" << endl;
		exit(-1);
	}

	glLinkProgram(gProgram[1]);
	glGetProgramiv(gProgram[1], GL_LINK_STATUS, &status);

	if (status != GL_TRUE)
	{
		cout << "Program link failed" << endl;
		exit(-1);
	}

	glLinkProgram(gProgram[2]);
	glGetProgramiv(gProgram[2], GL_LINK_STATUS, &status);

	if (status != GL_TRUE)
	{
		cout << "Program link failed" << endl;
		exit(-1);
	}

	glLinkProgram(geometryPassProgram);
	glGetProgramiv(geometryPassProgram, GL_LINK_STATUS, &status);

	if (status != GL_TRUE)
	{
		cout << "Program link failed" << endl;
		exit(-1);
	}

	glLinkProgram(geometryVisualizeProgram);
	glGetProgramiv(geometryVisualizeProgram, GL_LINK_STATUS, &status);

	if (status != GL_TRUE)
	{
		cout << "Program link failed" << endl;
		exit(-1);
	}

	glLinkProgram(motionBlurProgram);
	glGetProgramiv(motionBlurProgram, GL_LINK_STATUS, &status);

	if (status != GL_TRUE)
	{
		cout << "Program link failed" << endl;
		exit(-1);
	}

	// Get the locations of the uniform variables from both programs

	for (int i = 0; i < 2; ++i)
	{
		glUseProgram(gProgram[i]);

		modelingMatrixLoc[i] = glGetUniformLocation(gProgram[i], "modelingMatrix");
		viewingMatrixLoc[i] = glGetUniformLocation(gProgram[i], "viewingMatrix");
		projectionMatrixLoc[i] = glGetUniformLocation(gProgram[i], "projectionMatrix");
		eyePosLoc[i] = glGetUniformLocation(gProgram[i], "eyePos");
	}
}