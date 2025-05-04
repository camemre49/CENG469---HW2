#include <algorithm>
#include <iomanip>

#include "../headers/globals.h"

void renderText(const std::string& text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color)
{
    // Activate corresponding render state
    glUseProgram(gProgram[2]);
    glUniform3f(glGetUniformLocation(gProgram[2], "textColor"), color.x, color.y, color.z);
    glActiveTexture(GL_TEXTURE0);

    // Iterate through all characters
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
        Character ch = Characters[*c];

        GLfloat xpos = x + ch.Bearing.x * scale;
        GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

        GLfloat w = ch.Size.x * scale;
        GLfloat h = ch.Size.y * scale;

        // Update VBO for each character
        GLfloat vertices[6][4] = {
            { xpos,     ypos + h,   0.0, 0.0 },
            { xpos,     ypos,       0.0, 1.0 },
            { xpos + w, ypos,       1.0, 1.0 },

            { xpos,     ypos + h,   0.0, 0.0 },
            { xpos + w, ypos,       1.0, 1.0 },
            { xpos + w, ypos + h,   1.0, 0.0 }
        };

        // Render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);

        glBindVertexArray(vao[2]);
        // Update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, gTextVBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // Be sure to use glBufferSubData and not glBufferData

        //glBindBuffer(GL_ARRAY_BUFFER, 0);

        // Render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)

        x += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
    }

    glBindTexture(GL_TEXTURE_2D, 0);
}

void initFonts(int windowWidth, int windowHeight)
{
    // Set OpenGL options
    //glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    std::cout << "windowWidth = " << windowWidth << std::endl;
    std::cout << "windowHeight = " << windowHeight << std::endl;

    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(windowWidth), 0.0f, static_cast<GLfloat>(windowHeight));
    glUseProgram(gProgram[2]);
    glUniformMatrix4fv(glGetUniformLocation(gProgram[2], "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    // FreeType
    FT_Library ft;
    // All functions return a value different than 0 whenever an error occurred
    if (FT_Init_FreeType(&ft))
    {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
    }

    // Load font as face
    FT_Face face;
    if (FT_New_Face(ft, "/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf", 0, &face))
    //if (FT_New_Face(ft, "/usr/share/fonts/truetype/gentium-basic/GenBkBasR.ttf", 0, &face))
    {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
    }

    // Set size to load glyphs as
    FT_Set_Pixel_Sizes(face, 0, 48);

    // Disable byte-alignment restriction
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // Load first 128 characters of ASCII set
    for (GLubyte c = 0; c < 128; c++)
    {
        // Load character glyph
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }
        // Generate texture
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer
                );
        // Set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // Now store character for later use
        Character character = {
            texture,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            (GLuint) face->glyph->advance.x
        };
        Characters.insert(std::pair<GLchar, Character>(c, character));
    }

    glBindTexture(GL_TEXTURE_2D, 0);
    // Destroy FreeType once we're finished
    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    //
    // Configure VBO for texture quads
    //
    GLuint vaoLocal, vbo;
    glGenVertexArrays(1, &vaoLocal);
    assert(vaoLocal > 0);
    vao[2] = vaoLocal;
    glBindVertexArray(vaoLocal);

    glGenBuffers(1, &gTextVBO);
    glBindBuffer(GL_ARRAY_BUFFER, gTextVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

auto floatToString = [](float value, int precision = 2) {
    std::ostringstream out;
    out << std::fixed << std::setprecision(precision) << value;
    std::string str = out.str();
    // Trim trailing zeros and possibly the decimal point
    str.erase(str.find_last_not_of('0') + 1, std::string::npos);
    if (str.back() == '.') str.pop_back();
    return str;
};

std::string booleanToString(bool value) {
    return value ? "true" : "false";
}

void displayTexts() {
    static glm::vec3 yellow = glm::vec3(1.0f, 1.0f, 0);
    static glm::vec3 blue = glm::vec3(0.0f, 0.0f, 1.0f);
    static glm::vec3 green = glm::vec3(0.0f, 1.0f, 0.0f);
    static glm::vec3 red = glm::vec3(1.0f, 0.0f, 0.0f);

    static float bottomMargin = 5;
    static glm::vec2 rightBottom = glm::vec2(gWidth, bottomMargin);
    static glm::vec2 leftBottom = glm::vec2(0, 0);
    static glm::vec2 rightTop = glm::vec2(gWidth, gHeight);
    static glm::vec2 leftTop = glm::vec2(0, gHeight);

    // render shading related values and vsync from bottom to top
    float charHeight = 18;
    float charWidth = 9;
    float scale = 0.3;
    std::string str = std::string("gamma = " + floatToString(gammaValue));
    renderText(str, rightBottom.x - str.size() * charWidth, rightBottom.y, scale, yellow);
    str = std::string("key = " + floatToString(key));
    renderText(str, rightBottom.x - str.size() * charWidth, rightBottom.y + charHeight, scale, yellow);
    str = std::string("exposure = " + std::to_string(exposure));
    renderText(str, rightBottom.x - (str.size() - 1) * charWidth , rightBottom.y + charHeight * 2, scale, yellow);
    str = std::string("vsync = " + booleanToString(vsync));
    renderText(str, rightBottom.x - (str.size() - 1) * charWidth , rightBottom.y + charHeight * 3, scale, yellow);

    // Render fps
    if (fps > 0) {
        renderText("FPS: " + std::to_string(fps), leftTop.x + 15, leftTop.y - 25, 0.5f, green);
        keyPressShowingFrameCount = fps / 3;
    }

    // Render pressed key for a while
    static uint shownFrameCountOfKey = 0;
    if (!lastPressedKey.empty()) {
        renderText(lastPressedKey, leftBottom.x + 5, rightBottom.y + 5, 0.35, blue);
        if (shownFrameCountOfKey > keyPressShowingFrameCount) {
            shownFrameCountOfKey = 0;
            lastPressedKey = "";
        }
        shownFrameCountOfKey++;
    }

    // Render current render mode
    std::string mode = toString(currentRenderMode);
    renderText(toString(currentRenderMode), rightTop.x - mode.size()*18, rightTop.y - 25, 0.5f, red);
}

void savePressedKey(int key, int scancode) {
    const char* keyNameC = glfwGetKeyName(key, scancode);
    if (keyNameC) {
        lastPressedKey = keyNameC;
        std::transform(lastPressedKey.begin(), lastPressedKey.end(), lastPressedKey.begin(), ::toupper); // convert to uppercase
    } else {
        lastPressedKey = "";
    }
}