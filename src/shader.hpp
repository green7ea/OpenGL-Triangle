#ifndef SHADER_H
#define SHADER_H

#include "fragment.hpp"
#include "vertex.hpp"

#include "globj.hpp"

using Program = GLobj<glDeleteProgram>;
using Shader = GLobj<glDeleteShader>;

// Creates a shader object of the specified type using the specified text
static Shader make_shader(GLenum type, const char *text)
{
  Shader shader;
  GLint shader_ok;

  shader.gl_obj = glCreateShader(type);
  if (shader.gl_obj != 0)
  {
    glShaderSource(shader.gl_obj, 1, (const GLchar **)&text, NULL);
    glCompileShader(shader.gl_obj);
    glGetShaderiv(shader.gl_obj, GL_COMPILE_STATUS, &shader_ok);
    if (shader_ok != GL_TRUE)
    {
      fprintf(stderr, "ERROR: Failed to compile %s shader\n",
              (type == GL_FRAGMENT_SHADER) ? "fragment" : "vertex");
      char info_log[8192];
      GLsizei log_length;
      glGetShaderInfoLog(shader.gl_obj, 8192, &log_length, info_log);
      fprintf(stderr, "ERROR: \n%s\n\n", info_log);

      return Shader();
    }
  }

  return shader;
}

static Program make_program(const char *vs_text, const char *fs_text)
{
  Shader vertex_shader = make_shader(GL_VERTEX_SHADER, vs_text);
  Shader fragment_shader = make_shader(GL_FRAGMENT_SHADER, fs_text);

  if (vertex_shader.gl_obj < 0 || fragment_shader.gl_obj < 0)
  {
    fprintf(stderr, "Couldn't create shader\n");
    return Program();
  }

  Program program;
  program.gl_obj = glCreateProgram();
  if (program.gl_obj > 0)
  {
    glAttachShader(program.gl_obj, vertex_shader.gl_obj);
    glAttachShader(program.gl_obj, fragment_shader.gl_obj);
    glLinkProgram(program.gl_obj);
    int program_ok;
    glGetProgramiv(program.gl_obj, GL_LINK_STATUS, &program_ok);

    if (program_ok != GL_TRUE)
    {
      fprintf(stderr, "ERROR, failed to link shader program\n");
      GLsizei log_length;
      char info_log[8192];
      glGetProgramInfoLog(program.gl_obj, 8192, &log_length, info_log);
      fprintf(stderr, "ERROR: \n%s\n\n", info_log);

      return Program();
    }
  }

  return program;
}

#endif // SHADER_H
