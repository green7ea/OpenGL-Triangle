CXXFLAGS += -MD -pipe -Wall -Wextra -march=native -std=c++11 `pkg-config --cflags glfw3 glew`
LDFLAGS = `pkg-config --libs glfw3 glew`
SHADERS = fragment.glsl vertex.glsl
SHADER_HEADERS = $(SHADERS:.glsl=.hpp)
SRCS = triangle.cpp
OBJS = $(SRCS:.cpp=.o)
DEPS = $(SRCS:.cpp=.d)
PROG = triangle

.PHONY: all clean

all: $(SHADER_HEADERS) $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(PROG) $(OBJS) $(LDFLAGS)

clean:
	rm -f $(OBJS) $(DEPS) $(PROG)

%.hpp: %.glsl
	@echo "Building $<"
	@echo "#ifndef $*_HPP" > $@
	@echo "#define $*_HPP" >> $@
	@echo "static const char *$* = " >> $@
	@sed 's/^\(.*\)$$/"\1\\n"/g' $< >> $@
	@echo ";" >> $@
	@echo "#endif // $*_HPP" >> $@

-include $(DEPS)
