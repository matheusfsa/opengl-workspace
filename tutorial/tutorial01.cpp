
#include <GL/freeglut.h>
#include <stdlib.h>
void RenderSceneCB(void){
    /*
    The only thing we do in our render function is to clear the 
    framebuffer (using the color specified above - try changing it). The second call tells GLUT to swap the roles of the backbuffer and the frontbuffer. In the next round through the render callback we will render into the current frames front buffer and the current backbuffer will be displayed
    */
    glClear(GL_COLOR_BUFFER_BIT); 
    glutSwapBuffers();
    
}
int main(int argc, char **argv)
{
    /** GLUT = OpenGL Utility Library
        Provides a simplified API for window management 
        as well as event handling, IO control and a few 
        other services. In addition, GLUT is cross platform 
        which makes portability easier.
    */
    // This call initializes GLUT
    glutInit(&argc, argv);
    
    // Configure some GLUT options.
    /* 
    GLUT_DOUBLE: enables double buffering (drawing to a background 
    buffer while another buffer is displayed) 
    GLUT_RGBA: color buffer where most rendering ends up (i.e. the screen).
    */
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
   

    // specify the window parameter and create it.
    glutInitWindowSize(1024, 768); 
    glutInitWindowPosition(100, 100); 
    glutCreateWindow("Tutorial 01");

    // specify the "main" callback function that  is continuously called by GLUT internal loop
    glutDisplayFunc(RenderSceneCB);

    /*
    he call above sets the color that will be used when clearing 
    the framebuffer (described later). The color has four channels (
    RGBA) and it is specified as a normalized value between 0.0 and 1.0.
    */
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    /*
    This call passes control to GLUT which now begins its own internal
    loop. In this loop it listens to events from the windowing system
    and passes them via the callbacks that we configured. In our 
    case GLUT will only call the function we registered as a display
    callback (RenderSceneCB) to give us a chace to render the frame.
    */
    glutMainLoop();
}
