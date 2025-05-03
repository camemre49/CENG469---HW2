#include "../headers/globals.h"
using namespace std;

#include "../headers/stb_image.h"

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

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrComponents;
    for (unsigned int i = 0; i < faces.size(); i++) {
        float* data = stbi_loadf(faces[i].c_str(), &width, &height, &nrComponents, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                        0, GL_RGB16F, width, height,
                        0, GL_RGB, GL_FLOAT, data);
            stbi_image_free(data);
        } else {
            std::cerr << "Failed to load HDR cubemap face: " << faces[i] << std::endl;
            stbi_image_free(data);
            return 0;
        }
    }

    // Generate mipmaps for pre-filter map
    glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

    return texture;
}

void initTexture()
{
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // load the texture
    int width, height, nrChannels;
    unsigned char* data = stbi_load("haunted_library.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}

void initCubemap() {
    loadHDRCubemap(faces);
    cout << "Texture Id: " << texture << endl;
}

