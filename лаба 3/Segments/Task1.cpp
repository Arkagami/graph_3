#include <time.h>
#include "vstub.h"
#include <conio.h>
#include <stdio.h>
namespace std{
static float wxr[11] = {50.0, 50.0, 175.0, 300.0, 300.0, 250.0, 250.0, 175.0, 100.0, 100.0 }; //X ���������� ����
static float wyr[11] = {300.0, 50.0, 100.0, 50.0, 300.0, 300.0, 114.3, 150.0, 114.3, 300.0 };//Y ���������� ����
static float wxnr[5] = {1.0, 0.0, -1.0, 0.0 }; //X ���������� ��������� ��������
static float wynr[5] = {0.0, -1.0, 0.0, 1.0 };// Y ���������� ��������� ��������
static int n = 11; //���������� ������ � ����
static float *wx = wxr, *wy = wyr;
static float *wnx = wxnr, *wny = wynr;

int normal(int kv, float *wx, float *wy, float *nx, float *ny)
{ 
 // kv - ���������� ������ � ����
 // wx - X-���������� ������
 // wy - Y-���������� ������
 // nx - X-���������� �������� � ������
 // ny - Y-���������� �������� � ������

	int i;
	float ox, oy;//���������� (i-1) �������
	float ix, iy;//���������� i �������	
	i = 0;
	kv--;

	
	ox = wx[0];//ox==50
	oy= wy[0];//oy==300
	

	do {
	if (++i > kv) i= 0;
	ix = wx[i];//���������� X ��������� ������� (���������� � 1 ������������)
	iy = wy[i];//���������� Y ��������� ������� (���������� � 1 ������������)
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

int skl (float *x0, float *y0, float *x1, float *y1)//(x0 � y0 ���������� ����� �� ������� �1 � �1 ���������� ����� �� �������)
{ 
int i, vb, kw;
float xn, yn, dx, dy, r, CB_t0, CB_t1, Qx, Qy, Nx, Ny, Pn, Qn;
kw= n - 1;
vb= 1;
CB_t0 = 0; //��������� ������ �������
CB_t1= 1;
dx= *x1 - (xn= *x0);//X ���������� �������� ����� �� �������
dy= *y1 - (yn= *y0);//Y ���������� �������� ����� �� ������� 


for (i=0; i<=kw; ++i) 
{ 
	Qx = xn - wx[i];	//���������  ������������ �����				
	Qy = yn - wy[i];
	Nx = wnx[i];		//���������� � ������� � �����
	Ny = wny[i];		//���������� Y ������� � �����
	Pn = dx*Nx + dy*Ny; //C�������� ������������
	Qn = Qx*Nx + Qy*Ny;//��������� ������������ ������������ ��������� ����� �������(������/������� ��������������)

if (Pn == 0)//����� ����������� �������
	{ 
		if (Qn < 0) //����� �������
			{
				vb = 0; //����� ��� ����
				break; 
			}
	} else //��������� CB_t0 ��� ��������� CB_t1?
			{
				r = -Qn/Pn;//�������� t �� ������� ��������� �������� CB_t0 ��� CB_t1(���������� � ���� ������� ��������� � �������� ���������)
					if (Pn < 0) 
						{ 
							if (r < CB_t0) 
								{
									vb = 0; //����� ��� ����
									break; 
								}
							if (r < CB_t1) CB_t1= r;//��������� CB_t1 
						} else 
							{ 
								if (r > CB_t1) 
									{
										vb = 0; //����� ��� ����
										break; 
									}
								if (r > CB_t0) CB_t0 = r;//��������� CB_t0
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

for ( i = 1; i < 10; ++i)										//��������� ����
putline((int)wxr[i-1], (int)wyr[i-1], (int)wxr[i], (int)wyr[i]);
putline((int)wxr[0], (int)wyr[0], (int)wxr[4], (int)wyr[4]);

int f = normal(n, wx, wy, wnx, wny);//������� �� ���������� ������� � ������ �����
float xn, yn, xk, yk;
xn = 0;
yn = 0;
xk = 0;
yk = 0;
for ( i = 0; i < 400; ++i) 
{
yn = (float)i;//Y ���������� �������
yk = (float)i;
xn = (float)i;//X ���������� �������
xk = (float)i;
int k = skl(&xn, &yn, &xk, &yk);//������� ����������� ����������� �� ����� ����
//vc << "\nTime diff is : " << k;
if (k == 1)			//���� ����������� �� �������� ������� � 2 ���������
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
int k = skl(&xn, &yn, &xk, &yk);//������� ����������� ����������� �� ����� ����
vc << "\nTime diff is : " << k;
if (k == 1)			//���� ����������� �� �������� ������� � 2 ���������
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
int k = skl(&xn, &yn, &xk, &yk);//������� ����������� ����������� �� ����� ����
//vc << "\nTime diff is : " << k;
if (k == 1)			//���� ����������� �� �������� ������� � 2 ���������
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