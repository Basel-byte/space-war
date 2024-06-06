SRC_DIR := src
INCLUDE_DIR := include

ALL_SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)

OBJECTS := $(SOURCES:.cpp=.o)
CXX := g++
CXXFLAGS := -fdiagnostics-color=always -g -I $(INCLUDE_DIR)
LDFLAGS := -lsoil -lopengl32 -lfreeglut -lglew32 -lglu32 -lstdc++

all: src/game.exe

src/game.exe: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) src/game.exe
