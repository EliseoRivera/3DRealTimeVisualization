#ifndef MODELO3D_H
#define MODELO3D_H
#include"Triangle3D.h"
#include"Matrix.h"
#include<fstream>
#include <iostream>

#include <gl/gl.h>
#include<GL/GLU.h>
#define PI 3.14159265
#include <string>
///Copyright (C) <2017>  <Eliseo Rivera Silva> curso.tareas@gmail.com

using namespace std;
class modelo3D
{
    public:
modelo3D();
vector3d O;
Matrix R;
void dibujar();
//////////////////
int ntriangles;
Triangle3D* triangulos;
modelo3D(int ntriangulos);


void RotarZ(float theta);
ifstream archivo;
void leer(string nombre);
virtual ~modelo3D();
Matrix Rx,Ry,Rz;  //local
void Drawarrow3D( vector3d A,  vector3d B, vector3d color, double R);
};

#endif // MODELO3D_H
