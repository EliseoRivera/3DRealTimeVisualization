#ifndef CLASEOPENGL_H
#define CLASEOPENGL_H
#include <gl/gl.h>
#include<GL/GLU.h>
#include<vector3d.h>
#include<modelo3D.h>

///Copyright (C) <2017>  <Eliseo Rivera> curso.tareas@gmail.com

#define PI 3.14159265
class ClaseOpenGL
{
    public:

        ///cinética y cinemática
        float t,dt;
       unsigned int n;

        void InicializarRungeKutta();
        float x0,y0,z0;
        void IntegrarRungeKutta();
        void preparar();
         float g, l,k,m;
        Matrix y, f1,f2,f3,f4;
         Matrix F(const Matrix &y_,float t);
        ///////////////////parte visual
          ClaseOpenGL();
        virtual ~ClaseOpenGL();
        void inicializar();
        void DibujarEscena(float t=0);
        void CargarEscena();
        void renderizar();
        void DibujarEjes();
        void Resize(int width, int height);
        void  Drawarrow3D( vector3d A,  vector3d B, vector3d color, double R=0.01);
        void draw_Zspring();
        void draw_Yspring();
        void draw_Xspring(vector3d A,  vector3d B);
        void Drawcube3D(vector3d Position={0,0,0},float lado=1);
        	void Drawplane1( vector3d Position,  vector3d Udir, vector3d Vdir, float lado,vector3d color={0,0.6,1});
        float  cameraX,  cameraZ, cameraY ,   mouseX,mouseY, camerafactor,angle;
        float Rcamera, phiCamera, thetaCamera;
        float radians;
        void Drawcontinuostube( vector3d DELTA,const vector3d punto1,const vector3d n2);
        void Drawcontinuostube_init1(const vector3d A,  vector3d np,vector3d n);
       double intersectplane(vector3d l,vector3d d, vector3d p, vector3d n);
        vector3d vertexinicio[11],vertexfin[11];
        vector3d rojo={1,0.0,0.0};
        vector3d verde={0.0,1,0.0};
        vector3d azul={0.0,0.0,1};
        float Radiotube;
        modelo3D* cuerpo;

};

#endif // CLASEOPENGL_H
