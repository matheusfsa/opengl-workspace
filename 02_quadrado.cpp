// Baseado nos exemplos de http://www.glprogramming.com/red/chapter01.html
// Beatriz T. Andrade

#include <GL/freeglut.h>
void display(void)
{
	
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //glTranslatef(-0.1f, -0.1f, 0.0f);  
    //glRotatef(20, 0.0f, 0.0f, 1.0f); 
    //glScalef(1.2f, 0.5f, 1.0f);
    
    
/*  clear all pixels  */
    glClear (GL_COLOR_BUFFER_BIT);

/*  draw polygon (rectangle) with corners at
 *  (0.25, 0.25, 0.0) and (0.75, 0.75, 0.0)  
 */
    glBegin(GL_QUADS);
        // cores mapeadas para 0 e 1 a partir do intervalo 
        // de valores de cada tipo (ub = unsigned byte)
        glColor3ub (255, 255, 255);
        glVertex3f (0.25, 0.25, 0.0);
        
        glColor3ub (255, 0, 0);
        glVertex3f (0.75, 0.25, 0.0);
        
        glColor3f (0.0, 1.0, 0.0);
        glVertex3f (0.75, 0.75, 0.0);
        
        glColor3f (0.0, 0.0, 1.0);
        glVertex3f (0.25, 0.75, 0.0);
        
    glEnd();

    glFlush ();
}

void init (void) 
{
/*  select clearing (background) color       */
    glClearColor (0.0, 0.0, 0.0, 0.0);

/*  initialize viewing values  */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (250, 250); 
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Quadrado");
    init ();
    glutDisplayFunc(display); 
    glutMainLoop();
    return 0;  
}
