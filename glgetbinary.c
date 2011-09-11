// glgetbinary - Lorenzo Mancini <lmancini80@gmail.com>

#include <stdio.h>
#include <stdint.h>

#include <GL/glew.h>
#include <GL/gl.h>

#include "pez.h"

void init()
{
  static const GLchar *vertexShader=\
      "void main()"
      "{"
          "gl_Position = gl_Vertex;"
      "}";

  static const GLchar *fragmentShader=\
      "void main()"
      "{"
          "gl_FragColor=vec4(1.0, 1.0, 1.0, 1.0);"
      "}";

  GLuint p = glCreateProgram();

  GLuint v = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(v, 1, &vertexShader, 0);
  glCompileShader(v);
  glAttachShader(p, v);

  GLuint f = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(f, 1, &fragmentShader, 0);
  glCompileShader(f);
  glAttachShader(p, f);

  glProgramParameteri(p, GL_PROGRAM_BINARY_RETRIEVABLE_HINT, GL_TRUE);
  glLinkProgram(p);
  glUseProgram(p);

  GLint formats = 0;
  glGetIntegerv(GL_NUM_PROGRAM_BINARY_FORMATS, &formats);
  printf("%d formats supported\n", formats);
  if (formats > 0)
  {
    int f;

    GLint *binary_formats = new GLint[formats];
    glGetIntegerv(GL_PROGRAM_BINARY_FORMATS, binary_formats);

    for (f = 0; f < formats; ++f)
      printf("%d\n", binary_formats[f]);
  }

  GLint len = 0;
  glGetProgramiv(p, GL_PROGRAM_BINARY_LENGTH, &len);

  uint8_t* binary = new uint8_t[len];
  GLsizei bin_len;
  GLenum format;
  glGetProgramBinary(p, len, &bin_len, &format, binary);
  glUseProgram(0);

  printf("Used format 0x%X, wrote %d bytes\n", format, bin_len);

  FILE* fp = fopen("shader.bin", "wb");
  fwrite(binary, len, 1, fp);
  fclose(fp);

  delete [] binary;
}

const char* PezInitialize(int width, int height)
{
  init();
  return "glgetbinary";
}

void PezResize(int width, int height)
{
}

void PezRender()
{
}

void PezUpdate(unsigned int milliseconds)
{
}

void PezHandleMouse(int x, int y, int action)
{
}

void PezHandleKeyPress(char key)
{
}

void PezHandleKeyRelease(char key)
{
}
