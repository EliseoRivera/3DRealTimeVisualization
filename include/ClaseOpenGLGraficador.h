#ifndef CLASEOPENGL2D_H
#define CLASEOPENGL2D_H
#include <gl/gl.h>
#include<GL/GLU.h>
#include<vector3d.h>
#include<modelo3D.h>
#include<vector>
///Copyright (C) <2017>  <Eliseo Rivera> curso.tareas@gmail.com

#define PI 3.14159265
class ClaseOpenGL2D
{
    public:

        ///cinética y cinemática
        float t,dt;
       std::vector< float> data;
         std::vector< float> tiempo;
        void preparar(const float &t_,const Matrix &y);
         float g, l;
        Matrix y, f1,f2,f3,f4;
         Matrix F(const Matrix &y_,float t);
        ///////////////////parte visual
          ClaseOpenGL2D();
        virtual ~ClaseOpenGL2D();
        void inicializar();
        void DibujarEscena(float t_=0);
        void CargarEscena();
        void renderizar();
        void DibujarEjes();
        void Resize(int width, int height);
       void drawdatos(float t_,float rojo=0.5, float verde=0.5, float azul=1);
      void dibujarlinea(float X1, float Y1, float X2, float Y2,float rojo=1, float verde=0, float azul=0);
        float  cameraX,  cameraZ, cameraY ,   mouseX,mouseY, camerafactor,angle;
        float Rcamera, phiCamera, thetaCamera,controlCameraX;
        float radians;


        vector3d rojo={1,0.0,0.0};
        vector3d verde={0.0,1,0.0};
        vector3d azul={0.0,0.0,1};



};

#endif // CLASEOPENGL2D_H
