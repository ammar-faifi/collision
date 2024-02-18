CC = clang
CFLAGS = -Wall -Wextra
FRAMEWORKS = -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL
RAYLIB_LIB = libraylib.a
SOURCE = app.c
OUTPUT = app

$(OUTPUT): $(SOURCE) $(RAYLIB_LIB)
	$(CC) $(CFLAGS) $(SOURCE) $(RAYLIB_LIB) $(FRAMEWORKS) -o $(OUTPUT)

.PHONY: clean
clean:
	rm -f $(OUTPUT)
