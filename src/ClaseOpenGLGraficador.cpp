
#include "ClaseOpenGLGraficador.h"
///Copyright (C) <2017>  <Eliseo Rivera> curso.tareas@gmail.com



void ClaseOpenGL2D::preparar(const float &t_,const Matrix &y){

t=t_;
tiempo.push_back(t_);
data.push_back(y.entry(0,0));


}
///************************************************Renderizado********************************************///





void ClaseOpenGL2D::inicializar(){

Rcamera=10;
phiCamera=PI/2.0;
thetaCamera=-PI/2;
camerafactor=0.005;
controlCameraX=5;
////

    glClearColor(0,0,0,1);
    glEnable( GL_LINE_SMOOTH );
    glHint( GL_LINE_SMOOTH_HINT, GL_NICEST );
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);					// hidden surface removal
    glShadeModel(GL_SMOOTH);					// use smooth shading
    glEnable(GL_LIGHTING);
	glEnable(GL_LINE_SMOOTH);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
    glEnable(GL_COLOR_MATERIAL );

    CargarEscena();



}

void ClaseOpenGL2D::CargarEscena(){
cameraX=0;
}


void ClaseOpenGL2D::DibujarEscena(float t_){
DibujarEjes();
drawdatos(t_);

}
void ClaseOpenGL2D::DibujarEjes(){
dibujarlinea(-100+cameraX,0,100+cameraX,0);
dibujarlinea(0,100,0,-100,0,1);
}
void ClaseOpenGL2D::drawdatos(float t,float rojo, float verde, float azul){
 glPointSize(3);
 glColor3f(rojo,verde,azul);
    glBegin(GL_POINTS);

 for (int i=0;i<data.size();i++){
    glVertex3f(tiempo[i],data[i],0);

}
  glEnd();
}

void ClaseOpenGL2D::dibujarlinea(float X1, float Y1, float X2, float Y2,float rojo, float verde, float azul)
{
    glBegin(GL_LINES);
    glColor3f(rojo,verde, azul); glVertex3f(X1,Y1,0);
    glColor3f(rojo,verde,azul); glVertex3f(X2,Y2,0);
    glEnd();
}


void ClaseOpenGL2D::renderizar(){

       glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT );
       glLoadIdentity();
       cameraX=13;
       float q=t/cameraX;
	   gluLookAt(controlCameraX+cameraX*int(q), 0.0, 10, controlCameraX+cameraX*int(q), 0.0, 0.0, 0.0, 1.0, 0.0);
       DibujarEscena(t);

}
void ClaseOpenGL2D::Resize(int width, int height){

        glViewport(0, 0, width, height);		// reset the viewport to new dimensions
        glMatrixMode(GL_PROJECTION);			// set projection matrix current matrix
        glLoadIdentity();						// reset projection matrix
        // calculate aspect ratio of window
        gluPerspective(52.0f,(GLdouble)width/(GLdouble)height,1.0f,1000.0f);
        glMatrixMode(GL_MODELVIEW);				// set modelview matrix
        glLoadIdentity();



     				// reset modelview matrix


}


ClaseOpenGL2D::ClaseOpenGL2D(){

};

ClaseOpenGL2D::~ClaseOpenGL2D()
{

}

