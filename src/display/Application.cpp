//
// Created by Dillon Yao on 4/26/17.
//

#include "Application.h"
#include <glm/gtc/type_ptr.hpp>

Application::Application() : camera(glm::vec3(0.0f, 0.0f, 3.0f)) {}

Application::~Application() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Application::init() {
    glEnable(GL_DEPTH_TEST);

    GLfloat vertices[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f,  0.5f, 0.0f
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    shader.load("src/shaders/fpscam.vert", "src/shaders/solid_cam.frag");
    solid_shader.load("src/shaders/basic.vert", "src/shaders/basic.frag");
    mode = MODE_EDIT;
}

void Application::render() {
    shader.use();
    glm::mat4 projection = glm::perspective(camera.zoom, (float) screen_w / (float) screen_h, camera.n_clip, camera.f_clip);
    glm::mat4 view = camera.get_view_matrix();
    glm::mat4 model;

    // Get their uniform location
    glUniformMatrix4fv(glGetUniformLocation(shader.program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(glGetUniformLocation(shader.program, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shader.program, "model"), 1, GL_FALSE, glm::value_ptr(model));

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}

void Application::update() {

}

void Application::resize(int width, int height) {

}

void Application::keyboard_event(int key, int action, int mods) {
    switch(key) {
        case GLFW_KEY_E: {
            if (mode == MODE_EDIT) {
                mode = MODE_VIEW;
            } else {
                mode = MODE_EDIT;
            }
        }
        case GLFW_KEY_W:
            camera.keyboard_event(FORWARD, 0.01);
            break;
        case GLFW_KEY_A:
            camera.keyboard_event(LEFT, 0.01);
            break;
        case GLFW_KEY_D:
            camera.keyboard_event(RIGHT, 0.01);
            break;
        case GLFW_KEY_S:
            camera.keyboard_event(BACKWARD, 0.01);
            break;
        default:
            break;
    }
}

void Application::cursor_event(double cursor_x, double cursor_y) {
//    camera.cursor_event(cursor_x - screen_w / 2, cursor_y - screen_h / 2);
}

void Application::scroll_event(double offset_x, double offset_y) {
    camera.scroll_event(offset_y);
}

void Application::mouse_event(int button, int action, int mods) {

}