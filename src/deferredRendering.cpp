#include "../headers/globals.h"

unsigned int quadVAO = 0;
unsigned int quadVBO;

void initGBuffer() {
    glGenFramebuffers(1, &gBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);

    // - position color buffer
    glGenTextures(1, &gPosition);
    glBindTexture(GL_TEXTURE_2D, gPosition);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, gWidth, gHeight, 0, GL_RGBA, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gPosition, 0);

    // - normal color buffer
    glGenTextures(1, &gNormal);
    glBindTexture(GL_TEXTURE_2D, gNormal);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, gWidth, gHeight, 0, GL_RGBA, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, gNormal, 0);

    // - tell OpenGL which color attachments we'll use (of this framebuffer) for rendering
    unsigned int attachments[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
    glDrawBuffers(2, attachments);

    // then also add render buffer object as depth buffer and check for completeness.
    glGenRenderbuffers(1, &gDepth);
    glBindRenderbuffer(GL_RENDERBUFFER, gDepth);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, gWidth, gHeight);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, gDepth);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cerr << "GBuffer Framebuffer not complete!" << std::endl;
}

void initQuad() {
    float quadVertices[] = {
        // positions        // texCoords
        -1.0f,  1.0f, 0.0f,  0.0f, 1.0f,
        -1.0f, -1.0f, 0.0f,  0.0f, 0.0f,
         1.0f, -1.0f, 0.0f,  1.0f, 0.0f,

        -1.0f,  1.0f, 0.0f,  0.0f, 1.0f,
         1.0f, -1.0f, 0.0f,  1.0f, 0.0f,
         1.0f,  1.0f, 0.0f,  1.0f, 1.0f
    };

    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(quadVAO);

    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

    // Position attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);

    // Texture coordinate attribute
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
}

void makeGeometryPass()
{
    glEnable(GL_DEPTH_TEST);
    glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(geometryPassProgram);


    // Set uniforms for transformations
    glUniformMatrix4fv(glGetUniformLocation(geometryPassProgram, "modelingMatrix"), 1, GL_FALSE, glm::value_ptr(modelingMatrix));
    glUniformMatrix4fv(glGetUniformLocation(geometryPassProgram, "viewingMatrix"), 1, GL_FALSE, glm::value_ptr(viewingMatrix));
    glUniformMatrix4fv(glGetUniformLocation(geometryPassProgram, "projectionMatrix"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    // Pass armadillo from geometry pass
    glBindVertexArray(vao[0]);
    glDrawElements(GL_TRIANGLES, gFaces[0].size() * 3, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void renderGeometry() {
    glUseProgram(geometryVisualizeProgram);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gPosition);
    glUniform1i(glGetUniformLocation(geometryVisualizeProgram, "gPosition"), 0);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, gNormal);
    glUniform1i(glGetUniformLocation(geometryVisualizeProgram, "gNormal"), 1);

    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}