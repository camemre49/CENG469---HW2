#include "../headers/globals.h"
using namespace std;

#include "../headers/stb_image.h"
#define GET_CUBEMAP_PROGRAM(gProgramArray) gProgramArray[1];

const string cubemapFolderName = "cubemap";

std::vector<std::string> faces = {
    cubemapFolderName + "/px.hdr", // right
    cubemapFolderName + "/nx.hdr", // left
    cubemapFolderName + "/py.hdr", // top
    cubemapFolderName + "/ny.hdr", // bottom
    cubemapFolderName + "/pz.hdr", // front
    cubemapFolderName + "/nz.hdr"  // back
};

GLuint loadHDRCubemap(const std::vector<std::string>& faces) {

    glGenTextures(1, &cubemapTexture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrComponents;
    float logLumSum = 0.0f;
    int totalPixels = 0;
    const float delta = 1e-4f;

    for (unsigned int i = 0; i < faces.size(); i++) {
        float* data = stbi_loadf(faces[i].c_str(), &width, &height, &nrComponents, 0);
        if (data) {
            int pixelCount = width * height;
            totalPixels += pixelCount;

            for (int j = 0; j < pixelCount; ++j) {
                float r = data[j * nrComponents + 0];
                float g = data[j * nrComponents + 1];
                float b = data[j * nrComponents + 2];

                // Compute luminance using Rec. 709 coefficients
                float luminance = 0.2126f * r + 0.7152f * g + 0.0722f * b;
                logLumSum += std::log(delta + luminance);
            }

            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                         0, GL_RGB32F, width, height,
                         0, GL_RGB, GL_FLOAT, data);
            stbi_image_free(data);
        } else {
            std::cerr << "Failed to load HDR cubemap face: " << faces[i] << std::endl;
            return 0;
        }
    }

    logAverageLuminance = std::exp(logLumSum / totalPixels);

    // Generate mipmaps for pre-filter map
    glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

    return cubemapTexture;
}

void initCubemap() {
    loadHDRCubemap(faces);
    cout << "Texture Id: " << cubemapTexture << endl;
}

