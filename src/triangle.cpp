#define GLFW_INCLUDE_NONE
#define GL_GLEXT_PROTOTYPES

#include <unistd.h>
#include <vector>
#include <tuple>

#include <cmath>

#include <GL/gl.h>
#include <GL/glext.h>
#include <GLFW/glfw3.h>

#include "vbo.hpp"
#include "vao.hpp"
#include "shader.hpp"

using Vec3 = std::array<float, 3>;

static void error_callback(int, const char *description)
{
  fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(
  GLFWwindow *window, int key, int, int, int)
{
  switch (key)
  {
  case GLFW_KEY_ESCAPE:
    glfwSetWindowShouldClose(window, GLFW_TRUE);
    break;
  }
}

static void init(GLFWwindow *window)
{
  glfwMakeContextCurrent(window);
  glfwSetErrorCallback(error_callback);

  int width = 0;
  int height = 0;
  glfwGetFramebufferSize(window, &width, &height);
  glViewport(0, 0, width, height);

  glClearColor(0.f, 0.f, 0.f, 1.f);
  glDisable(GL_SCISSOR_TEST);
  glEnable(GL_DEPTH_TEST);
  glDepthMask(GL_TRUE);
  glDepthFunc(GL_LESS);
  glDisable(GL_BLEND);
  glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

  glfwSetKeyCallback(window, key_callback);
  glfwSetFramebufferSizeCallback(window,
                                 [](GLFWwindow *, int width, int height)
                                 {
                                   glViewport(0, 0, width, height);
                                 });
}

int main(int, char **)
{
  if (!glfwInit())
    return 1;
  glfwSetErrorCallback([](int error, const char *description)
                       {
                         fprintf(stderr, "GLFW error #%i: %s\n", error, description);
                       });
  glfwDefaultWindowHints();
  auto *window = glfwCreateWindow(1024, 800, "OpenGL Triangle C++11", nullptr, nullptr);
  init(window);

  std::vector<std::tuple<Vec3, Vec3>> vertices =
    {
      std::make_tuple(Vec3{ {-0.5f, -0.5f, 0.f} },
                      Vec3{ {0.f, 0.f, 1.f} }),
      std::make_tuple(Vec3{ {0.5f, -0.5f, 0.f} },
                      Vec3{ {0.f, 1.f, 0.f} }),
      std::make_tuple(Vec3{ {-0.5f, 0.5f, 0.f} },
                      Vec3{ {1.f, 0.f, 0.f} }),
      std::make_tuple(Vec3{ {0.5f, 0.5f, 0.f} },
                      Vec3{ {0.f, 0.f, 1.f} } )
    };

  Program shader = make_program(vertex, fragment);
  glUseProgram(*shader);

  auto vbo = make_vbo(vertices);
  auto vao = make_vao(shader, vertices,
                      "position", GL_FLOAT, 3,
                      "color", GL_FLOAT, 3);
  const GLint mul = glGetUniformLocation(*shader, "mul");

  float time = 0.f;
  while (!glfwWindowShouldClose(window))
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(*shader);
    glUniform1f(mul, sin(time));
    time += 0.01f;
    glBindBuffer(GL_ARRAY_BUFFER, *vbo);
    glBindVertexArray(*vao);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, vertices.size());

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
