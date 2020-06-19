#include <windows.h>
#include <gl/gl.h>
#include <ClaseOpenGL.h>
#include <ClaseOpenGLGraficador.h>
#include <iostream>
using namespace std;
#define PI 3.1415926535897932384626433832795
///Copyright (C) <2017>  <Eliseo Rivera> curso.tareas@gmail.com
LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WindowProc2(HWND, UINT, WPARAM, LPARAM);
void EnableOpenGL(HWND hwnd, HDC*, HGLRC*);
void DisableOpenGL(HWND, HDC, HGLRC);

 ClaseOpenGL* Miclase=NULL;
 ClaseOpenGL2D* Miclase2=NULL;


    WNDCLASSEX wcex;
    HWND hwnd;
    HDC hDC;
    HGLRC hRC;
    MSG msg;

    WNDCLASSEX wcex2;
    HWND hwnd2;
    HDC hDC2;
    HGLRC hRC2;
    MSG msg2;


int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{



    BOOL bQuit = FALSE;


    /* register window class */
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_OWNDC;
    wcex.lpfnWndProc = WindowProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = "opengl3D";
    wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);;

      /* register window class */
    wcex2.cbSize = sizeof(WNDCLASSEX);
    wcex2.style = CS_OWNDC;
    wcex2.lpfnWndProc = WindowProc2;
    wcex2.cbClsExtra = 0;
    wcex2.cbWndExtra = 0;
    wcex2.hInstance = hInstance;
    wcex2.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcex2.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex2.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wcex2.lpszMenuName = NULL;
    wcex2.lpszClassName = "opengl3D2";
    wcex2.hIconSm = LoadIcon(NULL, IDI_APPLICATION);;




    if (!RegisterClassEx(&wcex))
        return 0;
  if (!RegisterClassEx(&wcex2))
        return 0;

    /* create main window */
    hwnd = CreateWindowEx(0,
                          "opengl3D",
                          "Visualizador 3D por Físico Eliseo Rivera",
                          WS_OVERLAPPEDWINDOW,
                          CW_USEDEFAULT,
                          CW_USEDEFAULT,
                          800,
                          600,
                          NULL,
                          NULL,
                          hInstance,
                          NULL);

    hwnd2 = CreateWindowEx(0,
                          "opengl3D2",
                          "Graficador 2D por Físico Eliseo Rivera",
                          WS_OVERLAPPEDWINDOW,
                          CW_USEDEFAULT,
                          CW_USEDEFAULT,
                          800,
                          600,
                          NULL,
                          NULL,
                          hInstance,
                          NULL);



EnableOpenGL(hwnd, &hDC, &hRC); //va primero esto
ShowWindow(hwnd, nCmdShow); // y despues mostrar ventana
UpdateWindow(hwnd);					// update the window

EnableOpenGL(hwnd2, &hDC2, &hRC2); //va primero esto
ShowWindow(hwnd2, nCmdShow); // y despues mostrar ventana
UpdateWindow(hwnd2);


    /* enable OpenGL for the window */
wglMakeCurrent( hDC, hRC );

Miclase = new ClaseOpenGL;  //agregar código opengl
Miclase->inicializar();
SwapBuffers(hDC);





wglMakeCurrent( hDC2, hRC2 );
Miclase2 = new ClaseOpenGL2D;
Miclase2->inicializar();
SwapBuffers(hDC2);
    /* program main loop */
    while (!bQuit)
    {
        /* check for messages */
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            /* handle or dispatch messages */
            if (msg.message == WM_QUIT)
            {
                bQuit = TRUE;
            }
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {


            wglMakeCurrent( hDC2, hRC2 );
            Miclase2->preparar(Miclase->t,Miclase->y);
            Miclase2->renderizar();
            SwapBuffers(hDC2);

               wglMakeCurrent( hDC, hRC );
             Miclase->preparar();
             Miclase->renderizar();
             SwapBuffers(hDC);
         //   Sleep (1);
        }
    }
delete Miclase;
delete Miclase2;
Miclase=NULL;Miclase2=NULL;
    /* shutdown OpenGL */
    DisableOpenGL(hwnd, hDC, hRC);
    DisableOpenGL(hwnd2, hDC2, hRC2);
    /* destroy the window explicitly */
   DestroyWindow(hwnd);
   DestroyWindow(hwnd2);

    return msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{int height, width;
    switch (uMsg)
    {
    case WM_CREATE:


    break;
        case WM_CLOSE:
            PostQuitMessage(0);
        break;
    case WM_SIZE:
         wglMakeCurrent( hDC, hRC );
		height = HIWORD(lParam);		// retrieve width and height
		width = LOWORD(lParam);
        Miclase->Resize(width, height);

    break;

        case WM_DESTROY:
            return 0;

        case WM_KEYDOWN:
        {


            switch (wParam)
            {


                case 'A':
                Miclase->thetaCamera=Miclase->thetaCamera+0.05;

                break;
                  case 'D':
                Miclase->thetaCamera=Miclase->thetaCamera-0.05;

                break;

                case 'W':
                Miclase->phiCamera=Miclase->phiCamera+0.05;

                cout<< Miclase->phiCamera*180/PI<<endl;;
                break;
                  case 'S':
                Miclase->phiCamera=Miclase->phiCamera-0.05;

                break;
                case VK_ESCAPE:
                    PostQuitMessage(0);
                break;
            }
        }
        break;

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}
LRESULT CALLBACK WindowProc2(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{int height, width;
    switch (uMsg)
    {
    case WM_CREATE:


    break;
        case WM_CLOSE:
            PostQuitMessage(0);
        break;
    case WM_SIZE:
		height = HIWORD(lParam);		// retrieve width and height
		width = LOWORD(lParam);
		 wglMakeCurrent( hDC2, hRC2 );
        Miclase2->Resize(width, height);

    break;

        case WM_DESTROY:
            return 0;

        case WM_KEYDOWN:
        {


            switch (wParam)
            {


                case 'A':
                Miclase2->thetaCamera=Miclase2->thetaCamera+0.05;

                break;
                  case 'D':
                Miclase2->thetaCamera=Miclase2->thetaCamera-0.05;

                break;

                case 'W':
                Miclase2->phiCamera=Miclase2->phiCamera+0.05;

                cout<< Miclase->phiCamera*180/PI<<endl;;
                break;
                  case 'S':
                Miclase2->phiCamera=Miclase2->phiCamera-0.05;

                break;
                case VK_ESCAPE:
                    PostQuitMessage(0);
                break;
            }
        }
        break;

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}
void EnableOpenGL(HWND hwnd, HDC* hDC, HGLRC* hRC)
{
    PIXELFORMATDESCRIPTOR pfd;

    int iFormat;

    /* get the device context (DC) */
    *hDC = GetDC(hwnd);

    /* set the pixel format for the DC */
    ZeroMemory(&pfd, sizeof(pfd));

    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 3;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW |
                  PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;
    pfd.cDepthBits = 32;
    pfd.iLayerType = PFD_MAIN_PLANE;

    iFormat = ChoosePixelFormat(*hDC, &pfd);

    SetPixelFormat(*hDC, iFormat, &pfd);

    /* create and enable the render context (RC) */
    *hRC = wglCreateContext(*hDC);

    wglMakeCurrent(*hDC, *hRC);
}

void DisableOpenGL (HWND hwnd, HDC hDC, HGLRC hRC)
{
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hRC);
    ReleaseDC(hwnd, hDC);
}

