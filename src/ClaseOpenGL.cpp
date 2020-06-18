
#include "ClaseOpenGL.h"
///Copyright (C) <2017>  <Eliseo Rivera> curso.tareas@gmail.com


///***********************************************Cinética y cinemática********************************************///
 void ClaseOpenGL::InicializarRungeKutta()
{
 g=9.81; l=2;
 n=1;  //Grados de libertad
y.zero(2*n,1);
f1.zero(2*n,1);
f2.zero(2*n,1);
f3.zero(2*n,1);
f4.zero(2*n,1);


k=20;
m=0.3;
dt=0.0166666667; //definir tamaño de paso
t=0;  //inicializar el tiempo
///Definir condiciones iniciales para la posición y para la velocidad
x0=1;
y.entry(0,0)=x0+0.5;
y.entry(1,0)=0;

}
 void ClaseOpenGL::IntegrarRungeKutta(){
            f1=dt*F(y,t);
            f2=dt*F(y+0.5*f1,t+0.5*dt);
            f3=dt*F(y+0.5*f2,t+0.5*dt);
            f4=dt*F(y+f3,t+dt);

            y=y+(1/6.0)*(f1+2*f2+2*f3+f4);//RK
            cout<<"t = "<<t<<" , Theta ="<<y.entry(0,0)*180/PI<<endl;

}
 Matrix ClaseOpenGL::F(const Matrix &y_,float t){
 Matrix yv(2*n,1);

    yv.entry(0,0)=y_.entry(1,0);
    yv.entry(1,0)=-(k/m)*(y_.entry(0,0)-x0);
    return yv;

}
void ClaseOpenGL::preparar(){
IntegrarRungeKutta();
//cambiar configuracion
//cuerpo->O.x=l*cos(y.entry(0,0));
//cuerpo->O.y=l*sin(y.entry(0,0));
//aumentar tiempo
t=t+dt;
}
///************************************************Renderizado********************************************///

void ClaseOpenGL::DibujarEscena(float t){
     DibujarEjes();
     //cuerpo->dibujar();
     float x=y.entry(0,0);
     Drawcube3D({x+x0,0,0});
     draw_Xspring({0,0,0}, {x+x0,0,0});

}



void ClaseOpenGL::inicializar(){


CargarEscena();

InicializarRungeKutta();

}

void ClaseOpenGL::renderizar(){

        // calculate the camera's position
    cameraX=Rcamera*(fabs(cos(phiCamera)))*cos(thetaCamera);
    cameraY=Rcamera*(fabs(cos(phiCamera)))*sin(thetaCamera);
    cameraZ=Rcamera*(sin(phiCamera));
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT );
    glLoadIdentity();
    gluLookAt(cameraX,cameraY  ,cameraZ, 0,2,0, 0,0,1);
DibujarEscena();
/// ////////////////////////////
}
void ClaseOpenGL::CargarEscena(){
cuerpo=new modelo3D();
cuerpo->leer("esfera.stl");
}

void ClaseOpenGL::DibujarEjes(){

    Drawarrow3D({0,0,0},{100,0,0},rojo,0.03);
     Drawarrow3D({0,0,0},{0,100,0},verde,0.03);
     Drawarrow3D({0,0,0},{0,0,100},azul,0.01);
}

void ClaseOpenGL::draw_Zspring()
{

    float tx,ty,tz;
	tx=0;
	ty=0;
	tz=0;
	Radiotube=0.03f;
	float rs=0.3;
    int k1=10*(2*PI); //ciclos del resorte
    float c1=0.5*(sin(t)+5); //longitud del resorte



float tt=0;
vector3d punto0(rs*cos(k1*tt)+tx,rs*sin(k1*tt)+ty,c1*tt+tz);

	vector3d n2;
	vector3d  punto2;
	float d=0.01;
	vector3d punto1(rs*cos(k1*(tt+d))+tx,rs*sin(k1*(tt+d))+ty,c1*(tt+d)+tz);
		vector3d n(punto1-punto0);
		vector3d np(-rs*k1*k1*cos(k1*tt),-rs*k1*k1*sin(k1*tt),0); //normal
	Drawcontinuostube_init1(punto0, np,n);

//	Drawcontinuostube_init(punto0, n);
	vector3d DELTA(punto1-punto0);

vector3d DELTA1;

float dtt=d;
//crea resorte
float lenght=1;

while (tt<lenght){
punto2={rs*cos(k1*(tt+2*d))+tx,rs*sin(k1*(tt+2*d))+ty,c1*(tt+2*d)+tz};

n2={-rs*k1*sin(k1*(tt+d)),rs*k1*cos(k1*(tt+d)),c1}; //tau
n2.normalize();
    Drawcontinuostube(DELTA,punto1,n2);

DELTA1= punto2-punto1;
punto1={rs*cos(k1*(tt+d))+tx,rs*sin(k1*(tt+d))+ty,c1*(tt+d)+tz};
    punto0=punto1;
    punto1=punto2;
    tt=tt+dtt;
    DELTA=DELTA1;
}

};
void ClaseOpenGL::draw_Yspring()
{

    float tx,ty,tz;
	tx=0;
	ty=0;
	tz=0;
	Radiotube=0.03f;
	float rs=0.3;
    int k1=10*(2*PI); //ciclos del resorte
    float c1=0.5*(sin(t)+5); //longitud del resorte



float tt=0;
vector3d punto0(rs*sin(k1*tt)+ty,c1*tt+tz,rs*cos(k1*tt)+tx);

	vector3d n2;
	vector3d  punto2;
	float d=0.01;
	vector3d punto1(rs*sin(k1*(tt+d))+ty,c1*(tt+d)+tz,rs*cos(k1*(tt+d))+tx);
		vector3d n(punto1-punto0);
		vector3d np(-rs*k1*k1*sin(k1*tt),0,-rs*k1*k1*cos(k1*tt)); //normal
	Drawcontinuostube_init1(punto0, np,n);

//	Drawcontinuostube_init(punto0, n);
	vector3d DELTA(punto1-punto0);

vector3d DELTA1;

float dtt=d;
//crea resorte
float lenght=1;

while (tt<lenght){
punto2={rs*sin(k1*(tt+2*d))+ty,c1*(tt+2*d)+tz,rs*cos(k1*(tt+2*d))+tx};

n2={rs*k1*cos(k1*(tt+d)),c1,-rs*k1*sin(k1*(tt+d))}; //tau
n2.normalize();
    Drawcontinuostube(DELTA,punto1,n2);

DELTA1= punto2-punto1;
punto1={rs*sin(k1*(tt+d))+ty,c1*(tt+d)+tz,rs*cos(k1*(tt+d))+tx};
    punto0=punto1;
    punto1=punto2;
    tt=tt+dtt;
    DELTA=DELTA1;
}

};
void ClaseOpenGL::draw_Xspring(vector3d A,  vector3d B)
{

    float tx,ty,tz;
	tx=A.x;
	ty=A.y;
	tz=A.z;
	Radiotube=0.03f;
	float rs=0.3;
    int k1=10*(2*PI); //ciclos del resorte
    float c1=(B-A).x; //longitud del resorte



float tt=0;
vector3d punto0(c1*tt+tz,rs*cos(k1*tt)+tx,rs*sin(k1*tt)+ty);

	vector3d n2;
	vector3d  punto2;
	float d=0.01;
	vector3d punto1(c1*(tt+d)+tz,rs*cos(k1*(tt+d))+tx,rs*sin(k1*(tt+d))+ty);
		vector3d n(punto1-punto0);
		vector3d np(0,-rs*k1*k1*cos(k1*tt),-rs*k1*k1*sin(k1*tt)); //normal
	Drawcontinuostube_init1(punto0, np,n);

//	Drawcontinuostube_init(punto0, n);
	vector3d DELTA(punto1-punto0);

vector3d DELTA1;

float dtt=d;
//crea resorte
float lenghtparam=1;

while (tt<lenghtparam){
punto2={c1*(tt+2*d)+tz,rs*cos(k1*(tt+2*d))+tx,rs*sin(k1*(tt+2*d))+ty};

n2={c1,-rs*k1*sin(k1*(tt+d)),rs*k1*cos(k1*(tt+d))}; //tau
n2.normalize();
    Drawcontinuostube(DELTA,punto1,n2);

DELTA1= punto2-punto1;
punto1={c1*(tt+d)+tz,rs*cos(k1*(tt+d))+tx,rs*sin(k1*(tt+d))+ty};
    punto0=punto1;
    punto1=punto2;
    tt=tt+dtt;
    DELTA=DELTA1;
}

};
void ClaseOpenGL::Drawcontinuostube_init1(const vector3d A,  vector3d np,vector3d n){
vector3d inicio,vertex[10];
/*n.normalize();
if(n.z!=0)np={1,1,(-1/n.z)*(n.x+n.y)};
else if(n.y!=0)np={1,(-1/n.y)*(n.x+n.z),1};
else np={(-1/n.x)*(n.y+n.z),1,1};

*/

float R;
R=Radiotube;
np.normalize();
vertex[0]=R*np;
vertex[2]=R*(n*np).normalize();
vertex[1]=R*((0.5)*(vertex[2]-vertex[0])+vertex[0]).normalize();
vertex[4]=R*(n*vertex[2]).normalize();
vertex[3]=R*((0.5)*(vertex[4]-vertex[2])+vertex[2]).normalize();
vertex[6]=R*(n*vertex[4]).normalize();
vertex[5]=R*((0.5)*(vertex[6]-vertex[4])+vertex[4]).normalize();
vertex[7]=R*((0.5)*(vertex[0]-vertex[6])+vertex[6]).normalize();
vertex[8]=vertex[0];

vertexinicio[0]=vertex[0]+A;
vertexinicio[1]=vertex[1]+A;
vertexinicio[2]=vertex[2]+A;
vertexinicio[3]=vertex[3]+A;
vertexinicio[4]=vertex[4]+A;
vertexinicio[5]=vertex[5]+A;
vertexinicio[6]=vertex[6]+A;
vertexinicio[7]=vertex[7]+A;
vertexinicio[8]=vertex[8]+A;
}

void ClaseOpenGL::Drawcontinuostube( vector3d DELTA,const vector3d punto1,const vector3d n2)
{

double cota,color1,color2,color3,a,b,c,d,e,t,t1,t2,t3,t4,t5,t6,t7,t8;
vector3d normallight,n;
n=DELTA.normalize();

color1=0.8,color2=0.8,color3=0.8;
glColor3f( color1,color2, color3);
t=intersectplane(vertexinicio[0],n, punto1,n2);


t1=intersectplane(vertexinicio[1],n, punto1,n2);
t2=intersectplane(vertexinicio[2],n, punto1,n2);
t3=intersectplane(vertexinicio[3],n, punto1,n2);
t4=intersectplane(vertexinicio[4],n, punto1,n2);
t5=intersectplane(vertexinicio[5],n, punto1,n2);
t6=intersectplane(vertexinicio[6],n, punto1,n2);
t7=intersectplane(vertexinicio[7],n, punto1,n2);
t8=intersectplane(vertexinicio[8],n, punto1,n2);
vertexinicio[9]=vertexinicio[1];
vertexinicio[10]=vertexinicio[2];
if(t>1||t1>1||t2>1||t3>1||t4>1||t5>1||t6>1||t7>1||t8>1)return ;

vertexfin[0]=vertexinicio[0]+t*n;
vertexfin[1]=vertexinicio[1]+t1*n;
vertexfin[2]=vertexinicio[2]+t2*n;
vertexfin[3]=vertexinicio[3]+t3*n;
vertexfin[4]=vertexinicio[4]+t4*n;
vertexfin[5]=vertexinicio[5]+t5*n;
vertexfin[6]=vertexinicio[6]+t6*n;
vertexfin[7]=vertexinicio[7]+t7*n;
vertexfin[8]=vertexinicio[8]+t8*n;
vertexfin[9]=vertexfin[1];
vertexfin[10]=vertexfin[2];
int nx=8;
double d_thetha;

d_thetha=2.0f*PI/nx;




 glBegin( GL_TRIANGLE_STRIP );

         for(int i=1;i<10;i++)
               {


normallight=(n)*(vertexinicio[i-1]-vertexinicio[i]);
normallight.normalize();
glNormal3f(normallight.x, normallight.y, normallight.z);
                 glVertex3f(vertexinicio[i].x,vertexinicio[i].y,vertexinicio[i].z);


normallight=(n)*(vertexfin[i-1]-vertexfin[i]);
normallight.normalize();
glNormal3f(normallight.x, normallight.y, normallight.z);
glVertex3f(vertexfin[i].x,vertexfin[i].y,vertexfin[i].z);

                }



glEnd();

vertexinicio[0]=vertexfin[0];
vertexinicio[1]=vertexfin[1];
vertexinicio[2]=vertexfin[2];
vertexinicio[3]=vertexfin[3];
vertexinicio[4]=vertexfin[4];
vertexinicio[5]=vertexfin[5];
vertexinicio[6]=vertexfin[6];
vertexinicio[7]=vertexfin[7];
vertexinicio[8]=vertexfin[8];



}
	double ClaseOpenGL::intersectplane(vector3d l,vector3d d, vector3d p, vector3d n){ // l point of line, d directon of line, p point of plane, n normal plane
	double t;
	t=-(l.x*n.x+l.y*n.y+l.z*n.z)+p.x*n.x+p.y*n.y+p.z*n.z;
	t=t/(d.x*n.x+d.y*n.y+d.z*n.z);

	return t;
		}

void ClaseOpenGL::Drawcube3D(vector3d Position,float lado){
vector3d P[6];

P[0]={lado/2,0,0};
P[0]=P[0]+Position;
P[1]={-lado/2,0,0};
P[1]=P[1]+Position;
P[2]={0,lado/2,0};
P[2]=P[2]+Position;
P[3]={0,-lado/2,0};
P[3]=P[3]+Position;
P[4]={0,0,lado/2};
P[4]=P[4]+Position;
P[5]={0,0,-lado/2};
P[5]=P[5]+Position;



Drawplane1(P[0],{0,1,0},{0,0,1},lado);
Drawplane1(P[1],{0,-1,0},{0,0,1},lado);
Drawplane1(P[2],{1,0,0},{0,0,1},lado);
Drawplane1(P[3],{1,0,0},{0,0,-1},lado);
Drawplane1(P[4],{1,0,0},{0,1,0},lado);
Drawplane1(P[5],{1,0,0},{0,-1,0},lado);

	}
	void ClaseOpenGL::Drawplane1( vector3d Position,  vector3d Udir, vector3d Vdir, float lado,vector3d color){


Udir.normalize();
Vdir=Vdir-(Vdir.dotProduct(Udir)*Udir);
Vdir.normalize();

vector3d normal((Udir*Vdir));
normal.normalize();
vector3d A,B,C,D;
float alpha=1;
glColor4f( color.x,color.y, color.z,alpha);
float t=lado/2.0f;

A=Position+t*Udir-t*Vdir;
B=Position+t*Udir+t*Vdir;
C=Position-t*Udir-t*Vdir;
D=Position-t*Udir+t*Vdir;
glNormal3f(normal.x, normal.y, normal.z);
    glBegin( GL_TRIANGLES);
    glVertex4f(A.x,A.y,A.z,alpha);
    glVertex4f(B.x,B.y,B.z,alpha);
    glVertex4f(C.x,C.y,C.z,alpha);

     glVertex4f(C.x,C.y,C.z,alpha);
    glVertex4f(B.x,B.y,B.z,alpha);
    glVertex4f(D.x,D.y,D.z,alpha);
    glEnd();

	};
void ClaseOpenGL::Drawarrow3D( vector3d A,  vector3d B, vector3d color, double R)
{

double color1,color2,color3,a,b,c,d,e;

color1=color.x;//abs(color1/255);
color2=color.y;//abs(color2/255);
color3=color.z;//abs(color3/255);

glColor4f( color1,color2, color3,0.8);

vector3d n=B-A,np,vertex[10],normallight;
n.normalize();
if(n.z!=0)np={1,1,(-1/n.z)*(n.x+n.y)};
else if(n.y!=0)np={1,(-1/n.y)*(n.x+n.z),1};
else np={(-1/n.x)*(n.y+n.z),1,1};

np.normalize();
vertex[0]=R*np;
vertex[2]=R*(n*np).normalize();
vertex[1]=R*((0.5)*(vertex[2]-vertex[0])+vertex[0]).normalize();
vertex[4]=R*(n*vertex[2]).normalize();
vertex[3]=R*((0.5)*(vertex[4]-vertex[2])+vertex[2]).normalize();
vertex[6]=R*(n*vertex[4]).normalize();
vertex[5]=R*((0.5)*(vertex[6]-vertex[4])+vertex[4]).normalize();
vertex[7]=R*((0.5)*(vertex[0]-vertex[6])+vertex[6]).normalize();
vertex[8]=vertex[0];
vertex[9]=vertex[1];
int nx=8;
double d_thetha,fraccion=0.1,radioflecha=R+.7*R;
d_thetha=2.0f*PI/nx;


  ///tubos
 glBegin( GL_TRIANGLE_STRIP );

         for(int i=0;i<9;i++)
               {

normallight=n*(vertex[i-1]-vertex[i+1]);
normallight.normalize();
glNormal3f(normallight.x, normallight.y, normallight.z);
                 glVertex3f(vertex[i].x+A.x,vertex[i].y+A.y,vertex[i].z+A.z);

glVertex3f(vertex[i].x+B.x-fraccion*(B.x-A.x),vertex[i].y+B.y-fraccion*(B.y-A.y),vertex[i].z+B.z-fraccion*(B.z-A.z));

    // top face

                }

glEnd();



//flecha
vertex[0]=radioflecha*np;
vertex[2]=radioflecha*(n*np).normalize();
vertex[1]=radioflecha*((0.5)*(vertex[2]-vertex[0])+vertex[0]).normalize();
vertex[4]=radioflecha*(n*vertex[2]).normalize();
vertex[3]=radioflecha*((0.5)*(vertex[4]-vertex[2])+vertex[2]).normalize();
vertex[6]=radioflecha*(n*vertex[4]).normalize();
vertex[5]=radioflecha*((0.5)*(vertex[6]-vertex[4])+vertex[4]).normalize();
vertex[7]=radioflecha*((0.5)*(vertex[0]-vertex[6])+vertex[6]).normalize();
vertex[8]=vertex[0];
vertex[9]=vertex[1];
vector3d Ap(B-fraccion*(B-A));



 glBegin( GL_TRIANGLE_STRIP );  //flecha

         for(int i=0;i<9;i++)
               {

normallight=n*(vertex[i-1]-vertex[i+1]);
normallight.normalize();
glNormal3f(normallight.x, normallight.y, normallight.z);
                 glVertex3f(vertex[i].x+Ap.x,vertex[i].y+Ap.y,vertex[i].z+Ap.z);


glNormal3f(n.x, n.y, n.z);
glVertex3f(Ap.x+fraccion*(B-A).x,Ap.y+fraccion*(B-A).y,Ap.z+fraccion*(B-A).z);

    // top face

                }

glEnd();


}

ClaseOpenGL::ClaseOpenGL(){

    Rcamera=10;
phiCamera=PI/2.0;
thetaCamera=-PI/2;
camerafactor=0.005;
////

    glClearColor(1,1,1,1);
    glEnable( GL_LINE_SMOOTH );
    glHint( GL_LINE_SMOOTH_HINT, GL_NICEST );
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);					// hidden surface removal
    glShadeModel(GL_SMOOTH);					// use smooth shading
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
    glEnable(GL_COLOR_MATERIAL );


};
void ClaseOpenGL::Resize(int width, int height){

        glViewport(0, 0, width, height);		// reset the viewport to new dimensions
        glMatrixMode(GL_PROJECTION);			// set projection matrix current matrix
        glLoadIdentity();						// reset projection matrix
        // calculate aspect ratio of window
        gluPerspective(52.0f,(GLdouble)width/(GLdouble)height,1.0f,1000.0f);
        glMatrixMode(GL_MODELVIEW);				// set modelview matrix
        glLoadIdentity();						// reset modelview matrix
}
ClaseOpenGL::~ClaseOpenGL()
{
    delete cuerpo;
}

