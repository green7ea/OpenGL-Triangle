#ifndef VBO_HPP
#define VBO_HPP

#include <vector>

#include "globj.hpp"

using VertexBufferObject = GLobjs<glDeleteBuffers>;

template <typename T>
VertexBufferObject make_vbo(const std::vector<T> &data)
{
  VertexBufferObject vbo;
  glGenBuffers(1, &vbo.gl_obj);
  glBindBuffer(GL_ARRAY_BUFFER, *vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(T) * data.size(),
               data.data(), GL_STATIC_DRAW);

  return vbo;
}

template <int POS, typename TYPE>
constexpr void * offset_of()
{
  return (void *)(&(std::get<POS>(*(TYPE *)nullptr)));
}

#endif // VBO_HPP
