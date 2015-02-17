#ifndef VAO_HPP
#define VAO_HPP

#include <memory>
#include <vector>

#include "globj.hpp"
#include "shader.hpp"

typedef GLobjs<glDeleteVertexArrays> VertexArrayObject;

template <typename Vertex, int pos>
void attrib_pointers(const Program &)
{

}

template <typename Vertex, int pos, typename... Args>
void attrib_pointers(const Program &shader,
                     const char *attrib_name, GLenum type, GLint size,
                     Args... attribs)
{
  const GLint shader_pos = glGetAttribLocation(*shader, attrib_name);
  glEnableVertexAttribArray(shader_pos);
  glVertexAttribPointer(shader_pos, size, type, GL_FALSE,
                        sizeof(Vertex),
                        (void *)offset_of<pos, Vertex>());
  attrib_pointers<Vertex, pos + 1>(shader, attribs...);
}

template <typename Vertex, typename... Args>
VertexArrayObject make_vao(Program &shader,
                           const std::vector<Vertex> &,
                           Args... attribs)
{
  VertexArrayObject vao;
  glGenVertexArrays(1, &vao.gl_obj);
  glBindVertexArray(*vao);
  attrib_pointers<Vertex, 0>(shader, attribs...);
  return vao;
}

#endif // VAO_HPP
