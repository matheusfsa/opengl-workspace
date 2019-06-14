// Baseado em PrimeiroPrograma.c - Isabel H. Manssour
// Beatriz T. Andrade

//para compilar:
//g++ -o primeiro_programa primeiro_programa.cpp -lGL -lGLU -lglut
//para rodar:    ./primeiro_programa

#include <GL/freeglut.h>
#include <stdlib.h>


// Função callback chamada para fazer o desenho
void exibir(void)
{
	
	static float R =0, G=0, B=0;

	if (R>1) R=0;
	if (G>1) G=0;
	if (B>1) B=0;
	
	R+=0.1;
	G+=0.2;
	B+=0.3;
	
	//altera cor de fundo da janela de visualização
    glClearColor(R, G, B, 1);

	
	//Limpa a janela de visualização com a cor de fundo especificada 
	glClear(GL_COLOR_BUFFER_BIT);

	//Executa os comandos OpenGL 
	glFlush();
	
}
// Inicializa parâmetros de rendering
void iniciar (void)
{   
    // Define a cor de fundo da janela de visualização
    glClearColor(1.0, 0.0, 0.0, 1);
}
// Programa Principal 
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutCreateWindow("Primeiro Programa");
	glutDisplayFunc(exibir);
	iniciar();
	glutMainLoop();
}
