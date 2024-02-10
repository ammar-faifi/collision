CC = clang
CFLAGS = -Wall -Wextra
FRAMEWORKS = -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL
RAYLIB_LIB = libraylib.a
SOURCE = my_app.c
OUTPUT = my_app

$(OUTPUT): $(SOURCE) $(RAYLIB_LIB)
	$(CC) $(CFLAGS) $(SOURCE) $(RAYLIB_LIB) $(FRAMEWORKS) -o $(OUTPUT)

.PHONY: clean
clean:
	rm -f $(OUTPUT)
