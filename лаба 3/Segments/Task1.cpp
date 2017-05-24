#include <time.h>
#include "vstub.h"
#include <conio.h>
#include <stdio.h>
namespace std{
static float wxr[11] = {50.0, 50.0, 175.0, 300.0, 300.0, 250.0, 250.0, 175.0, 100.0, 100.0 }; //X координаты окна
static float wyr[11] = {300.0, 50.0, 100.0, 50.0, 300.0, 300.0, 114.3, 150.0, 114.3, 300.0 };//Y координаты окна
static float wxnr[5] = {1.0, 0.0, -1.0, 0.0 }; //X координата начальных нормалей
static float wynr[5] = {0.0, -1.0, 0.0, 1.0 };// Y координата начальных нормалей
static int n = 11; //Количество вершин в окне
static float *wx = wxr, *wy = wyr;
static float *wnx = wxnr, *wny = wynr;

int normal(int kv, float *wx, float *wy, float *nx, float *ny)
{ 
 // kv - количество вершин в окне
 // wx - X-координаты вершин
 // wy - Y-координаты вершин
 // nx - X-координаты нормалей к ребрам
 // ny - Y-координаты нормалей к ребрам

	int i;
	float ox, oy;//Координаты (i-1) вершины
	float ix, iy;//Координаты i вершины	
	i = 0;
	kv--;

	
	ox = wx[0];//ox==50
	oy= wy[0];//oy==300
	

	do {
	if (++i > kv) i= 0;
	ix = wx[i];//Координата X следующей вершины (начинается с 1 включительно)
	iy = wy[i];//Координата Y следующей вершины (начинается с 1 включительно)
	*nx = iy-oy;
	*ny = ox-ix;

	*nx= -*nx;
	*ny = -*ny;
	*nx++ = *nx; 
	*ny++ = *ny;
	ox= ix;
	oy= iy;
	} while (i);
	
return (0);
} 

int skl (float *x0, float *y0, float *x1, float *y1)//(x0 и y0 координата точки на отрезке х1 и у1 координаты точки на отрезке)
{ 
int i, vb, kw;
float xn, yn, dx, dy, r, CB_t0, CB_t1, Qx, Qy, Nx, Ny, Pn, Qn;
kw= n - 1;
vb= 1;
CB_t0 = 0; //Параметры концов отрезка
CB_t1= 1;
dx= *x1 - (xn= *x0);//X координата входящей точки на отрезке
dy= *y1 - (yn= *y0);//Y координата входящей точки на отрезке 


for (i=0; i<=kw; ++i) 
{ 
	Qx = xn - wx[i];	//Положение  относительно ребра				
	Qy = yn - wy[i];
	Nx = wnx[i];		//Координата Х Нормали к ребру
	Ny = wny[i];		//Координата Y Нормали к ребру
	Pn = dx*Nx + dy*Ny; //Cкалярное произведение
	Qn = Qx*Nx + Qy*Ny;//Скалярное произведение определяющее положение точки отрезка(внутри/снаружи многоугольника)

if (Pn == 0)//Грань параллельна вектору
	{ 
		if (Qn < 0) //Точка снаружи
			{
				vb = 0; //Точка вне окна
				break; 
			}
	} else //Увеличить CB_t0 или уменьшить CB_t1?
			{
				r = -Qn/Pn;//Значение t на которое изменится значение CB_t0 или CB_t1(Получается в ходе решение уравнения в описании алгоритма)
					if (Pn < 0) 
						{ 
							if (r < CB_t0) 
								{
									vb = 0; //Точка вне окна
									break; 
								}
							if (r < CB_t1) CB_t1= r;//Уменьшить CB_t1 
						} else 
							{ 
								if (r > CB_t1) 
									{
										vb = 0; //Точка вне окна
										break; 
									}
								if (r > CB_t0) CB_t0 = r;//Увеличить CB_t0
							}
			}
}



return (vb);
} 
int main(void){
//time_t t=clock();
drawgrid();
setcolor(255,0,0);
int i;

for ( i = 1; i < 10; ++i)										//Рисование окна
putline((int)wxr[i-1], (int)wyr[i-1], (int)wxr[i], (int)wyr[i]);
putline((int)wxr[0], (int)wyr[0], (int)wxr[4], (int)wyr[4]);

int f = normal(n, wx, wy, wnx, wny);//Функция по нахождению нормали к каждой грани
float xn, yn, xk, yk;
xn = 0;
yn = 0;
xk = 0;
yk = 0;
for ( i = 0; i < 400; ++i) 
{
yn = (float)i;//Y координата нормали
yk = (float)i;
xn = (float)i;//X координата нормали
xk = (float)i;
int k = skl(&xn, &yn, &xk, &yk);//Функция вычисляющая принадлежит ли точка окну
//vc << "\nTime diff is : " << k;
if (k == 1)			//Если принадлежит то рисуется отрезок в 2 пипикселя
{ 
setcolor(0,255,255);
putline(i,i,i+1,i+1);
}else
{
setcolor(0,0,255);
putline(i,i,i+1,i+1);

}
}

for ( i = 400; i> 0; --i) 
{
yn = float(2*i+2);
yk = float(2*i+2);
xn = (float)i;
xk = (float)i;
int k = skl(&xn, &yn, &xk, &yk);//Функция вычисляющая принадлежит ли точка окну
vc << "\nTime diff is : " << k;
if (k == 1)			//Если принадлежит то рисуется отрезок в 2 пипикселя
{ 
setcolor(0,255,255);
putline(i,2*i+2,i+1,2*(i+1)+2);
}
else
{
setcolor(0,0,255);
putline(i,2*i+2,i+1,2*(i+1)+2);
}
}

for ( i = 0; i< 400; ++i) 
{
yn = (float)(0.5*i+2);
yk = (float)(0.5*i+2);
xn = (float)i;
xk = (float)i;
int k = skl(&xn, &yn, &xk, &yk);//Функция вычисляющая принадлежит ли точка окну
//vc << "\nTime diff is : " << k;
if (k == 1)			//Если принадлежит то рисуется отрезок в 2 пипикселя
{ 
setcolor(0,255,255);
putline(i,0.5*i+2,i+1,0.5*(i+1)+2);
}
else
{
setcolor(0,0,255);
putline(i,0.5*i+2,i+1,0.5*(i+1)+2);

}
}




//vc << "\nTime diff is : " << clock()-t;
TFlush();
GFlush();
vgetchar();
return 0;
}
}