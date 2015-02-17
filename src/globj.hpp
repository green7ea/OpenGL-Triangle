#ifndef GLOBJ_H
#define GLOBJ_H

template <void (*dealloc_func)(GLuint)>
struct GLobj
{
  GLuint gl_obj = -1;

  GLobj() = default;
  GLobj(const GLobj &) = delete;
  GLobj(GLobj &&other)
    : gl_obj(other.gl_obj)
  {
    other.gl_obj = -1;
  }
  ~GLobj()
  {
    if (gl_obj > 0)
    {
      dealloc_func(gl_obj);
    }
  }
  GLobj & operator=(const GLobj &) = delete;
  GLobj & operator=(GLobj &&other)
  {
    std::swap(gl_obj, other.gl_obj);
    return *this;
  }
  GLuint operator*() const {
    return gl_obj;
  }
};

template <void (*dealloc_func)(int, const GLuint *)>
struct GLobjs
{
  GLuint gl_obj = 0;

  GLobjs() = default;
  GLobjs(const GLobjs &) = delete;
  GLobjs(GLobjs &&other)
    : gl_obj(other.gl_obj)
  {
    other.gl_obj = 0;
  }
  ~GLobjs()
  {
    if (gl_obj > 0)
    {
      dealloc_func(1, &gl_obj);
    }
  }
  GLobjs & operator=(const GLobjs &) = delete;
  GLobjs & operator=(GLobjs &&other)
  {
    std::swap(gl_obj, other.gl_obj);
    return *this;
  }
  GLuint operator*() const {
    return gl_obj;
  }
};

#endif // GLOBJ_H
