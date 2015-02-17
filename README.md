OpenGL Triangle
===============

A simple triangle in OpenGL using C++11. The shows a minimalistic
render pipeline that ironically renders a square to the screen. It
tries to have easy to use binding for managing the lifetime of the
OpenGL handles and for the creation of Vertex Array Objects and Vertex
Buffer Objects.

Requiremenots
------------

- glfw3 (http://www.glfw.org)
- glew (https://github.com/nigels-com/glew)
- GNU Make


VBO and VAO Creation
--------------------

Thanks to C++11, creating a VAO and VBO is as simple as:

```
auto vbo = make_vbo(vertices);
auto vao = make_vao(shader, vertices,
                    "position", GL_FLOAT, 3,
                    "color", GL_FLOAT, 3);
```
