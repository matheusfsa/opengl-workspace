
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#define WINDOW_TITLE_PREFIX "Chapter 2"

int
  CurrentWidth = 800,
  CurrentHeight = 600,
  WindowHandle = 0;

GLuint
  VertexShaderId,
  FragmentShaderId,
  ProgramId,
  VaoId,
  VboId,
  ColorBufferId;

unsigned FrameCount = 0;
/*
 Um shader é um programa que roda na GPU, o OpenGl expressa um shader como
 um programa escrito em uma liguagem baseada em C, chamada de OpenGL Shading
 Language, or GLSL. 
*/
// O shadder abaixo  processa vertice por vertice.
const GLchar* VertexShader =
{
  /* a variável in_position contém a posição do vértice armazenada
   em um vetor de 4 dimensões, é usado o prefixo "in" pois deve ser fornecida 
   pelo programa OpenGL  
     a variável in_color é a msm coisa da outra só que pra cor
     ex_Color contem a cor final do vértice que vai ser copiada para
     o  próximo shader
     No main:
      A primeira linha de nossa função principal copia o valor que 
      passamos em in_Position para gl_Position, a posição final do 
      vértice passada para os estágios subseqüentes do shader.
      Qualquer transformação que vc aplica em gl_position vai refletir no
      render final.

  */

  "#version 400\n" 
  "layout(location=0) in vec4 in_Position;\n"\ 
  "layout(location=1) in vec4 in_Color;\n"\
  "out vec4 ex_Color;\n"\

  "void main(void)\n"\
  "{\n"\
  "  gl_Position = in_Position;\n"\
  "  ex_Color = in_Color;\n"\
  "}\n"
};

const GLchar* FragmentShader =
{

  "#version 400\n"\

  "in vec4 ex_Color;\n"\
  "out vec4 out_Color;\n"\

  "void main(void)\n"\
  "{\n"\
  "  out_Color = ex_Color;\n"\
  "}\n"
};
void Initialize(int, char*[]);
void InitWindow(int, char*[]);
void ResizeFunction(int, int);
void RenderFunction(void);
void TimerFunction(int);
void IdleFunction(void);
void Cleanup(void);
void CreateVBO(void);
void DestroyVBO(void);
void CreateShaders(void);
void DestroyShaders(void);


int main(int argc, char* argv[])
{
  Initialize(argc, argv);

  glutMainLoop();
  
  exit(EXIT_SUCCESS);
}

void Initialize(int argc, char* argv[])
{
  GLenum GlewInitResult;
  InitWindow(argc, argv);
  GlewInitResult = glewInit();

  if (GLEW_OK != GlewInitResult) {
    fprintf(
      stderr,
      "ERROR: %s\n",
      glewGetErrorString(GlewInitResult)
    );
    exit(EXIT_FAILURE);
  }
  fprintf(
    stdout,
    "INFO: OpenGL Version: %s\n",
    glGetString(GL_VERSION)
  );

  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  CreateShaders();
  CreateVBO();
}

void InitWindow(int argc, char* argv[])
{
  glutInit(&argc, argv);
  
  glutInitContextVersion(4, 0);
  glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
  glutInitContextProfile(GLUT_CORE_PROFILE);

  glutSetOption(
    GLUT_ACTION_ON_WINDOW_CLOSE,
    GLUT_ACTION_GLUTMAINLOOP_RETURNS
  );
  
  glutInitWindowSize(CurrentWidth, CurrentHeight);

  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

  WindowHandle = glutCreateWindow(WINDOW_TITLE_PREFIX);

  if(WindowHandle < 1) {
    fprintf(
      stderr,
      "ERROR: Could not create a new rendering window.\n"
    );
    exit(EXIT_FAILURE);
  }

  glutReshapeFunc(ResizeFunction);
  glutDisplayFunc(RenderFunction);
  glutIdleFunc(IdleFunction);
  glutTimerFunc(0, TimerFunction, 0);
  glutCloseFunc(Cleanup);
}


void ResizeFunction(int Width, int Height)
{
  CurrentWidth = Width;
  CurrentHeight = Height;
  //A viewport defines the area drawn to by OpenGL
  glViewport(0, 0, CurrentWidth, CurrentHeight);
}

void RenderFunction(void)
{

  ++FrameCount;  
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  // Desenhar os conteudos do VBO na taela
  glDrawArrays(GL_TRIANGLES, 0, 6);
  glutSwapBuffers();
  glutPostRedisplay();
}
void IdleFunction(void)
{
  glutPostRedisplay();
}

void TimerFunction(int Value)
{
  if (0 != Value) {
    char* TempString = (char*)
      malloc(512 + strlen(WINDOW_TITLE_PREFIX));

    sprintf(
      TempString,
      "%s: %d Frames Per Second @ %d x %d",
      WINDOW_TITLE_PREFIX,
      FrameCount * 4,
      CurrentWidth,
      CurrentHeight
    );

    glutSetWindowTitle(TempString);
    free(TempString);
  }
  
  FrameCount = 0;
  glutTimerFunc(250, TimerFunction, 1);
}

void Cleanup(void)
{
  DestroyShaders();
  DestroyVBO();
}

void CreateVBO(void)
{
  GLfloat Vertices[] = {
  -0.8f,  0.8f, 0.0f, 1.0f,
   0.8f,  0.8f, 0.0f, 1.0f,
  -0.8f, -0.8f, 0.0f, 1.0f,

  -0.8f, -0.8f, 0.0f, 1.0f,
   0.8f,  0.8f, 0.0f, 1.0f,
   0.8f, -0.8f, 0.0f, 1.0f
  };

  GLfloat Colors[] = {
    1.0f, 0.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 1.0f,

    0.0f, 0.0f, 1.0f, 1.0f,
    0.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f
  };

  GLenum ErrorCheckValue = glGetError();
  /*
    Um VAO é um objeto que descreve como os atributos de vértices são armazenados 
    em um VBO.
  */
  // gerar os VAOs na memória da GPU e passar o seus identificadores 
  // o primeiro parâmetro é o número array de vértices o segundo é o identificador 
  glGenVertexArrays(1, &VaoId);
  glBindVertexArray(VaoId);
  //Gerar os buffer na memória e associar a um identificador
  glGenBuffers(1, &VboId);
  // ligar o buffer a um target, que  definirá o tipo do buffer
  glBindBuffer(GL_ARRAY_BUFFER, VboId);
  // Copiar os dados do vértices para o buffer
  // Parâmetros: target, tamanho, dados, uso. GL_STATIC_DRAW siginifica que  os dados na memória não podem ser modificados e serão usados para geração de imagens(draw).
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
  //setar os atributos dos vertices
  // parâmetros: indice(usado no vertexshader, o location=index), tamanho de cada vertice,  tipo,  se é pra ser normalizado(caso não esteja entre [0, 1] ou [-1,1]), quantidade de bytes entre o bloco de dados
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
  // Ativar o atributo de vertices
  glEnableVertexAttribArray(0);
  // Os dados das cores são setados da mesma maneira
  glGenBuffers(1, &ColorBufferId);
  glBindBuffer(GL_ARRAY_BUFFER, ColorBufferId);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Colors), Colors, GL_STATIC_DRAW);
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
  
  glEnableVertexAttribArray(1);

  ErrorCheckValue = glGetError();
  if (ErrorCheckValue != GL_NO_ERROR)
  {
    fprintf(
      stderr,
      "ERROR: Could not create a VBO: %s \n",
      gluErrorString(ErrorCheckValue)
    );

    exit(-1);
  }
 }
 void DestroyVBO(void)
{
  GLenum ErrorCheckValue = glGetError();

  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glDeleteBuffers(1, &ColorBufferId);
  glDeleteBuffers(1, &VboId);

  glBindVertexArray(0);
  glDeleteVertexArrays(1, &VaoId);

  ErrorCheckValue = glGetError();
  if (ErrorCheckValue != GL_NO_ERROR)
  {
    fprintf(
      stderr,
      "ERROR: Could not destroy the VBO: %s \n",
      gluErrorString(ErrorCheckValue)
    );

    exit(-1);
  }
}
void CreateShaders(void)
{
  // Compilação e associação a um identificador do programas GLSL


  GLenum ErrorCheckValue = glGetError();

  VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
  // associação do codigo ao identificador
  glShaderSource(VertexShaderId, 1, &VertexShader, NULL);
  // compilação
  glCompileShader(VertexShaderId);

  FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(FragmentShaderId, 1, &FragmentShader, NULL);
  glCompileShader(FragmentShaderId);

  // Combinação dos shader em um programa
  ProgramId = glCreateProgram();
    glAttachShader(ProgramId, VertexShaderId);
    glAttachShader(ProgramId, FragmentShaderId);
  glLinkProgram(ProgramId);
  glUseProgram(ProgramId);

  ErrorCheckValue = glGetError();
  if (ErrorCheckValue != GL_NO_ERROR)
  {
    fprintf(
      stderr,
      "ERROR: Could not create the shaders: %s \n",
      gluErrorString(ErrorCheckValue)
    );

    exit(-1);
  }
}
void DestroyShaders(void)
{
  GLenum ErrorCheckValue = glGetError();

  glUseProgram(0);

  glDetachShader(ProgramId, VertexShaderId);
  glDetachShader(ProgramId, FragmentShaderId);

  glDeleteShader(FragmentShaderId);
  glDeleteShader(VertexShaderId);

  glDeleteProgram(ProgramId);

  ErrorCheckValue = glGetError();
  if (ErrorCheckValue != GL_NO_ERROR)
  {
    fprintf(
      stderr,
      "ERROR: Could not destroy the shaders: %s \n",
      gluErrorString(ErrorCheckValue)
    );

    exit(-1);
  }
}