#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "math_3d.h"

/*

Este é o nosso primeiro encontro com o GLEW, a OpenGL Extension Wrangler 
Library. O GLEW ajuda você a lidar com a dor de cabeça que pode acompanhar 
o gerenciamento de extensões no OpenGL. Uma vez inicializado, ele consulta 
todas as extensões disponíveis na sua plataforma, carrega-as dinamicamente e 
fornece acesso fácil por meio de um único arquivo de cabeçalho.


Neste tutorial veremos o uso de objetos de buffer de vértices (VBOs) pela 
primeira vez. Como o nome indica, eles são usados para armazenar vértices. 
Os objetos que existem no mundo 3D que você está tentando visualizar, sejam 
monstros, castelos ou um simples cubo giratório, são sempre construídos conectando
um grupo de vértices. VBOs são a maneira mais eficiente de carregar vértices 
na GPU. Eles são buffers que podem ser armazenados na memória de vídeo e 
fornecem o menor tempo de acesso à GPU, portanto, eles são definitivamente 
recomendados.
*/

/*
Alocamos um GLuint na parte global do programa para armazenar o identificador
do VBO. Você verá mais tarde que a maioria (se não todos) objetos OpenGL são
acessados através de uma variável do tipo GLuint.
*/
GLuint VBO;
static void RenderSceneCB()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glDrawArrays(GL_POINTS, 0, 1);

    glDisableVertexAttribArray(0);

    glutSwapBuffers();
}
static void CreateVertexBuffer()
{   /*
    Criamos uma array de structs Vector3f (esse tipo é definido em math_3d.h)
    e inicializamos XYZ como zero. Isso fará com que o ponto apareça no meio da
    tela.
    */
    Vector3f Vertices[2];
    Vertices[0] = Vector3f(0.0f, 0.0f, 0.0f);
    /*
    O OpenGL define várias funções glGen * para gerar objetos de vários tipos. 
    Eles geralmente aceitam dois parâmetros - o primeiro especifica o número de
    objetos que você deseja criar e o segundo é o endereço de um array de GLuints
    para armazenar as alças que o driver aloca para você (certifique-se de que o array 
    seja grande o suficiente para lidar com rqequisiçao!). Chamadas futuras para 
    esta função não gerarão as mesmas object handles, a menos que você as exclua 
    primeiro com glDeleteBuffers. Note que neste momento você não especifica o que 
    você pretende fazer com os buffers para que eles possam ser considerados como 
    "genéricos". Este é o trabalho da próxima função.
    */
 	glGenBuffers(0, &VBO);
    /*
    O OpenGL tem uma maneira única de usar handles. Em muitas APIs, o handles é simplesmente
    passado para qualquer função relevante e a ação é executada nesse handle. No OpenGL, 
    ligamos o handle a um nome de destino e, em seguida, executamos comandos nesse destino.
    Esses comandos afetam o handle limitado até que outro esteja vinculado em seu lugar ou a
    chamada acima tome zero como o identificador. O alvo GL_ARRAY_BUFFER significa que o buffer 
    conterá uma matriz de vértices. Outro destino útil é GL_ELEMENT_ARRAY_BUFFER, o que significa
    que o buffer contém os índices dos vértices em outro buffer. Outros alvos também estão disponíveis
    e os veremos em futuros tutoriais.
    */
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
    /*
    Depois da  um bind no nosso objeto, nós o preenchemos com dados.
    */
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
    glDrawArrays(GL_POINTS, 0, 2);
}

static void InitializeGlutCallbacks()
{
    glutDisplayFunc(RenderSceneCB);
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowSize(1024, 768);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Tutorial 02");

    InitializeGlutCallbacks();

    // Must be done after glut is initialized!
    GLenum res = glewInit();
    if (res != GLEW_OK) {
      fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
      return 1;
    }

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    CreateVertexBuffer();

    glutMainLoop();

    return 0;
}

