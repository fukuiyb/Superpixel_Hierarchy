/*$Id: basic.h,v 1.46 2007/04/04 02:15:14 liiton Exp $*/
/*******************************************************
\Author:	Qingxiong Yang (liiton)
\Function:	Basic functions.
********************************************************/
#ifndef BASIC_H
#define BASIC_H
//#include "qx_alloc.h"
//#include <afxdlgs.h>
#include <stdio.h>
#include <math.h>
#include <numeric>
#include <vector>
#include <time.h>
#include <string>
#include <algorithm>
#include <functional>      // For greater<int>()
#include <iostream>
#include <io.h>
#include <direct.h>
#include <process.h>
#include <memory.h>
#include "omp.h"
#include "qx_image_display.h"
#include "qx_constants.h"
#include "qx_basic_file.h"
#include "qx_alloc.h"
#if _MSC_VER > 1020   // if VC++ version is > 4.2
   using namespace std;  // std c++ libs implemented in std
#endif
#define qx_max(a,b)						(((a) > (b)) ? (a) : (b))
#define qx_min(a,b)						(((a) < (b)) ? (a) : (b))
#define QX_DEF_PI_DOUBLE				3.14159265359
#define QX_DEF_FLOAT_MAX				1.175494351e+38F
#define QX_DEF_DOUBLE_MAX				1.7E+308
#define QX_DEF_FLOAT_RELATIVE_ACCURACY	2.2204e-016
#define QX_DEF_INI_MAX					2147483647
#define QX_DEF_SHORT_MAX				65535
#define QX_DEF_CHAR_MAX					255
#define	QX_DEF_SEED						42
#define QX_DEF_THRESHOLD_ZERO			1e-6
#define QX_DEF_THRESHOLD_ZERO_DOUBLE	1e-16
#define QX_DEF_ENTER					10
#define QX_DEF_BLANK					32
#define QX_DEF_STRING_LENGTH			300

inline double qx_log_10(double x){double inv_log_base=1.0/log(10.0);return(x>QX_DEF_THRESHOLD_ZERO_DOUBLE?log(x)*inv_log_base:0);}
inline double qx_exp_10(double x){return(pow(10.0,x));}
inline double qx_sqrt(double x){return((x>=0)?sqrt(x):0);}
//inline double qx_log_10(double x){return(log(x));}
//inline double qx_exp_10(double x){return(exp(x));}
inline int qx_round(double in_x) { if(in_x<0) return (int)(in_x-0.5); else return (int)(in_x+0.5); }
double qx_rand(int &s);
double qx_rand(int &s,double dmin,double dmax);
double qx_randc(int &s);
void qx_rand_reorder(int*index,int len_out,int len_in,int &seed);
void qx_rand_reorder(int*index,int len_out,int len_in);
inline void qx_compute_random_color(unsigned char color[3],int &seed){*color++=unsigned char(qx_rand(seed)*255);*color++=unsigned char(qx_rand(seed)*255);*color++=unsigned char(qx_rand(seed)*255);}
void qx_compute_random_color(unsigned char**color,int nr_feature,int &seed);
//inline void qx_compute_linear_color(unsigned char color[3],int v,int vmin,int vmax){int id=int(((1<<24)-1)*double(v-vmin)/(vmax-vmin)+0.5); int r=(id>>16); int g=(id>>8)-r*(1<<8); int b=id-r*(1<<16)-g*(1<<8); color[0]=(unsigned char)r; color[1]=(unsigned char)g; color[2]=(unsigned char)b;}
//inline void qx_compute_linear_color(unsigned char color[3],int v,int vmin,int vmax)
//{
//	int id=int(((1<<24)-1)*double(v-vmin)/(vmax-vmin)+0.5); 
//	int r=(id>>16); 
//	int g=(id>>8)-r*(1<<8); 
//	int b=id-r*(1<<16)-g*(1<<8); 
//	color[0]=(unsigned char)r; color[1]=(unsigned char)g; color[2]=(unsigned char)b;
//}
void qx_rand8_init(unsigned char *in);
void qx_gaussian_2d(double **gaussian,int h,int w,int &s);
void qx_gaussian_2d(float **gaussian,int h,int w,int &s);
void qx_gaussian_2d(float **gaussian,int h,int w,int &s,float scale);
inline void qx_sleep(unsigned int mseconds){clock_t goal = mseconds + clock();while (goal > clock());};
inline void qx_get_date_and_time(char str[300]){time_t t=time(0);struct tm*now=localtime(&t);sprintf_s(str,300,"%d-%d-%d-%d-%d-%d",now->tm_year + 1900,now->tm_mon + 1,now->tm_mday,now->tm_hour,now->tm_min,now->tm_sec);}
void Normalize(double * Vec, int Len, double Sum);
void Normalize(float * Vec, int Len, float Sum);
/*statistics*/
double inline __declspec (naked) __fastcall qx_sqrt14(double n)
{
	_asm fld qword ptr [esp+4]
	_asm fsqrt
	_asm ret 8
}
inline double qx_div(float x,float y){return(x/(y+QX_DEF_FLOAT_RELATIVE_ACCURACY));}
inline double qx_div(double x,double y){return(x/(y+QX_DEF_FLOAT_RELATIVE_ACCURACY));}
inline double qx_div(int x,int y){return((double)x/((double)y+QX_DEF_FLOAT_RELATIVE_ACCURACY));}
inline int qx_sign(double x){return((x>=0)?1:(-1));};
inline int qx_sign(int x){return((x>=0)?1:(-1));};
inline void qx_memset_u3(unsigned char a[3],unsigned char zero=0){*a++=zero; *a++=zero; *a++=zero;}
inline void qx_memset_f3(float a[3],float zero=0.f){*a++=zero; *a++=zero; *a++=zero;}
inline void qx_memset_d3(double a[3],double zero=0.0){*a++=zero; *a++=zero; *a++=zero;}
inline void qx_memset_d9(double a[9],double zero=0.0){memset(a,zero,sizeof(double)*9);}
inline void qx_memset_d12(double a[12],double zero=0.0){memset(a,zero,sizeof(double)*12);}
inline void qx_memset_d16(double a[16],double zero=0.0){memset(a,zero,sizeof(double)*16);}
template<typename T>inline void qx_memset_3(T a[3],T zero){memset(a,zero,sizeof(T)*3);}
template<typename T>inline void qx_memset_12(T a[12],T zero){memset(a,zero,sizeof(T)*12);}
template<typename T>inline void qx_memset_16(T a[16],T zero){memset(a,zero,sizeof(T)*16);}
inline void qx_memcpy_u3(unsigned char a[3],unsigned char b[3]){*a++=*b++; *a++=*b++; *a++=*b++;}
inline void qx_memcpy_i3(int a[3],int b[3]){*a++=*b++; *a++=*b++; *a++=*b++;}
inline void qx_memcpy_f3(float a[3],float b[3]){*a++=*b++; *a++=*b++; *a++=*b++;}
inline void qx_memcpy_d3(double a[3],double b[3]){*a++=*b++; *a++=*b++; *a++=*b++;}
inline void qx_memcpy_d4(double a[4],double b[4]){*a++=*b++; *a++=*b++; *a++=*b++; *a++=*b++;}
inline void qx_memcpy_d9(double a[9],double b[9]){memcpy(a,b,sizeof(double)*9);}
inline void qx_memcpy_d12(double a[12],double b[12]){memcpy(a,b,sizeof(double)*12);}
template<typename T>inline void qx_memcpy_3(T a[3],T b[3]){memcpy(a,b,sizeof(T)*3);}
template<typename T>inline void qx_memcpy_12(T a[12],T b[12]){memcpy(a,b,sizeof(T)*12);}
template<typename T>inline void qx_memcpy_16(T a[16],T b[16]){memcpy(a,b,sizeof(T)*16);}

inline int qx_sum_u3(unsigned char *a) {return(a[0]+a[1]+a[2]);}
inline int qx_sum_i3(int*a) {return(a[0]+a[1]+a[2]);}
inline float qx_sum_f3(float *a){return(a[0]+a[1]+a[2]);}
inline double qx_sum_fn(float *a,int len){double b=0; for(int i=0;i<len;i++) b+=(double)(*a++); return(b);}
inline double qx_sum_d3(double*a){return(a[0]+a[1]+a[2]);}
inline void qx_sub_u3(unsigned char*out,unsigned char*a,unsigned char*b){out[0]=abs(a[0]-b[0]); out[1]=abs(a[1]-b[1]); out[2]=abs(a[2]-b[2]);}
inline void qx_sub_f3(float *out,float *a,float *b){out[0]=a[0]-b[0]; out[1]=a[1]-b[1]; out[2]=a[2]-b[2];}
inline void qx_sub_d3(double *out,double *a,double *b){out[0]=a[0]-b[0]; out[1]=a[1]-b[1]; out[2]=a[2]-b[2];}
inline void qx_sub_d2(double out[2],double a[2],double b[2]){out[0]=a[0]-b[0]; out[1]=a[1]-b[1];}
inline void qx_sub_i2(int out[2],int a[2],int b[2]){out[0]=a[0]-b[0]; out[1]=a[1]-b[1];}
inline unsigned char qx_min_u3(unsigned char *a){return(min(min(a[0],a[1]),a[2]));}
inline unsigned char qx_min_u3(unsigned char r,unsigned char g,unsigned char b){return(min(min(r,g),b));}
inline float qx_min_f3(float*a){return(min(min(a[0],a[1]),a[2]));}
inline float qx_min_f4(float*a){return(min(min(a[0],a[1]),min(a[2],a[3])));}
inline double qx_min_d3(double*a){return(min(min(a[0],a[1]),a[2]));}
inline double qx_min_d3(double a,double b,double c){return(min(min(a,b),c));}
inline double qx_min_d5(double a[5]){return(qx_min_d3(min(a[0],a[1]),min(a[2],a[3]),a[4]));}
inline unsigned char qx_max_u3(unsigned char *a){return(max(max(a[0],a[1]),a[2]));}
inline unsigned char qx_max_u3(const unsigned char r,const unsigned char g,const unsigned char b){int ret = r; if(ret<b) ret = b; if(ret<g) ret = g; return ret;}
inline float qx_max_f3(float*a){return(max(max(a[0],a[1]),a[2]));}
inline float qx_max_f4(float*a){return(max(max(a[0],a[1]),max(a[2],a[3])));}
inline double qx_max_d3(double a,double b,double c){return(max(max(a,b),c));}
inline double qx_max_d3(double*a){return(max(max(a[0],a[1]),a[2]));}
inline double qx_max_d4(double*a){return(max(max(a[0],a[1]),max(a[2],a[3])));}
inline float qx_median_f3(float a,float b,float c){if(a<=b){if(c>a){if(c<=b) return(c);return(b);}return(a);}if(c>b){if(c<=a) return(c);return(a);}return(b);}
inline float qx_median_f3(float v[3]){return(qx_median_f3(v[0],v[1],v[2]));}
inline unsigned char qx_compute_RGB_distance_max(const unsigned char*image,const unsigned int idt,const unsigned int id)
{
	unsigned int id3=id*3;
	unsigned int idt3=idt*3;
	unsigned char r=abs((int)image[idt3++]-(int)image[id3++]); 
	unsigned char g=abs((int)image[idt3++]-(int)image[id3++]);
	unsigned char b=abs((int)image[idt3++]-(int)image[id3++]);
	return qx_max_u3(r,g,b);
}
inline unsigned char qx_compute_RGB_distance_max(const unsigned char*raw1,const unsigned char*raw2)
{
	unsigned char r=abs((int)raw1[0]-(int)raw2[0]); 
	unsigned char g=abs((int)raw1[1]-(int)raw2[1]); 
	unsigned char b=abs((int)raw1[2]-(int)raw2[2]);   
	return qx_max_u3(r,g,b);
}
inline unsigned char qx_compute_RGB_distance_fast(const unsigned char*image,const unsigned int idt,const unsigned int id)
{
	unsigned int id3=id*3;
	unsigned int idt3=idt*3;
	unsigned char r=abs((int)image[idt3++]-(int)image[id3++]); 
	unsigned char g=abs((int)image[idt3++]-(int)image[id3++]);
	unsigned char b=abs((int)image[idt3++]-(int)image[id3++]);
	return (((r<<1)+g+b)>>2);
}
inline double qx_dot_i2(int a[2],int b[2]) {return(a[0]*b[0]+a[1]*b[1]);}
inline double qx_dot_d2(double a[2],double b[2]) {return(a[0]*b[0]+a[1]*b[1]);}
inline double qx_dot_d3(double a[3],double b[3]) {return(a[0]*b[0]+a[1]*b[1]+a[2]*b[2]);}
inline int qx_dot_i3(int a[3],int b[3]) {return(a[0]*b[0]+a[1]*b[1]+a[2]*b[2]);}
inline double qx_dot_d9(double a[9],double b[9]) {return(a[0]*b[0]+a[1]*b[1]+a[2]*b[2]+a[3]*b[3]+a[4]*b[4]+a[5]*b[5]+a[6]*b[6]+a[7]*b[7]+a[8]*b[8]);}
inline float qx_dot_f3(float a[3],float b[3]) {return(a[0]*b[0]+a[1]*b[1]+a[2]*b[2]);}
inline float qx_dot_f4(float *a,float *b){return(a[0]*b[0]+a[1]*b[1]+a[2]*b[2]+a[3]*b[3]);}
inline double qx_dot_d4(double *a,double *b){return(a[0]*b[0]+a[1]*b[1]+a[2]*b[2]+a[3]*b[3]);}
inline void qx_cross_product_f3(float out[3],float a[3],float b[3]){out[0]=-a[2]*b[1]+a[1]*b[2];out[1]=a[2]*b[0]-a[0]*b[2];out[2]=-a[1]*b[0]+a[0]*b[1];}
inline void qx_cross_product_d3(double out[3],double a[3],double b[3]){out[0]=-a[2]*b[1]+a[1]*b[2];out[1]=a[2]*b[0]-a[0]*b[2];out[2]=-a[1]*b[0]+a[0]*b[1];}
inline void qx_cross_product_d3xd9(double out[9],double a[3],double b[9])
{
	out[0]=-a[2]*b[1]+a[1]*b[2];out[1]=a[2]*b[0]-a[0]*b[2];out[2]=-a[1]*b[0]+a[0]*b[1];
	out[3]=-a[2]*b[4]+a[1]*b[5];out[4]=a[2]*b[3]-a[0]*b[5];out[5]=-a[1]*b[3]+a[0]*b[4];
	out[6]=-a[2]*b[7]+a[1]*b[8];out[7]=a[2]*b[6]-a[0]*b[8];out[8]=-a[1]*b[6]+a[0]*b[7];
}
inline void qx_kinv_cross_product_d3(double out[3],double a[3],double b[3],double kinv[9]){double ab[3]; qx_cross_product_d3(ab,a,b); out[0]=kinv[4]*ab[0]; out[1]=kinv[0]*ab[1]-kinv[1]*ab[0]; out[2]=(kinv[1]*kinv[5]-kinv[2]*kinv[4])*ab[0]-kinv[0]*kinv[5]*ab[1]+kinv[0]*kinv[4]*ab[2];}//Ka x Kb=det(K)K^{-T}(axb)
inline void qx_vec_normalization_d2(double a[2]){double ss=qx_dot_d2(a,a); if(ss>QX_DEF_THRESHOLD_ZERO_DOUBLE){ss=sqrt(ss); a[0]/=ss; a[1]/=ss;}else{a[0]=a[1]=1.0/2;}}
inline void qx_vec_normalization_d3(double a[3]){double ss=qx_dot_d3(a,a); if(ss>QX_DEF_THRESHOLD_ZERO_DOUBLE){ss=sqrt(ss); a[0]/=ss; a[1]/=ss; a[2]/=ss;}else{a[0]=a[1]=a[2]=1.0/3;}}
inline void qx_vec_normalization_f3(float a[3]){double ss=qx_dot_f3(a,a); if(ss>QX_DEF_THRESHOLD_ZERO_DOUBLE){ss=sqrt(ss); a[0]=float(double(a[0])/ss); a[1]=float(double(a[1])/ss); a[2]=float(double(a[2])/ss);}else{a[0]=a[1]=a[2]=1.f/3;}}
inline double qx_vec_distance_d2(double a[2],double b[2]){double dx=a[0]-b[0]; double dy=a[1]-b[1]; return(sqrt(dx*dx+dy*dy));}
inline double qx_vec_distance_f3(float a[3],float b[3]){double dx=double(a[0]-b[0]); double dy=double(a[1]-b[1]); double dz=double(a[2]-b[2]); return(sqrt(dx*dx+dy*dy+dz*dz));}
inline double qx_vec_distance_d3(double a[3],double b[3]){double dx=a[0]-b[0]; double dy=a[1]-b[1]; double dz=a[2]-b[2]; return(sqrt(dx*dx+dy*dy+dz*dz));}
inline float qx_norm_f3(float a[3]){return(sqrt(qx_dot_f3(a,a)));}
inline double qx_norm_d3(double a[3]){return(sqrt(qx_dot_d3(a,a)));}
inline double qx_norm_d4(double a[4]){return(sqrt(qx_dot_d4(a,a)));}
inline void qx_norm_d3_z(double norm[3]){if(abs(norm[2])>1.0e-6){norm[0]/=norm[2]; norm[1]/=norm[2]; norm[2]=1;}else {norm[0]=norm[1]=0; norm[2]=1;}}
inline void qx_norm_f3_z(float norm[3]){if(abs(norm[2])>1.0e-6f){norm[0]/=norm[2]; norm[1]/=norm[2]; norm[2]=1.f;}else {norm[0]=norm[1]=0.f; norm[2]=1.f;}}

inline void cu_texture_size(int&nr_h,int&nr_w,int nr_image)
{
	nr_h=(int)sqrt(nr_image+0.0001);
	nr_w=nr_image/nr_h; 
	while(nr_h*nr_w!=nr_image&&nr_h>0) 
	{
		nr_w=nr_image/(--nr_h);
	}
}

bool larger(float a,float b);
bool smaller(float a,float b);
void qx_sort_increase_using_histogram(int*id,unsigned char*image,int len);
void qx_vec_sort_decrease_f3(float a[3],int b[3]);
void vec_sort_increase(float *in,int len);
void vec_sort_decrease(float *in,int len);
void vec_sort_decrease(double *in,int len);
void vec_sort_decrease_with_id(double*confidence,int*id,int len,int nr_selected);
void vec_sort_decrease_bf_2d(float *confidence,char **filename,int len,int nr_selected=0);
void vec_sort_decrease_bf_2d(int *confidence,char **filename,int len);
void vec_sort_decrease_bf_2d(int*confidence,int*index,int len,int nr_selected);
void vec_normalized(double *in,int len);
bool smaller_u(unsigned char a,unsigned char b);
void vec_sort_increase_u(unsigned char *in,int len);
bool smaller_i(int a,int b);
void vec_sort_increase_i(int *in,int len);
bool larger_i(int a,int b);
void vec_sort_decrease_i(int *in,int len);
double  VecSort			(double * InVec, int N);
double  VecSort			(float * InVec, int N);
void vec_exchange(int *vec,int i,int j);

template<typename T>inline double qx_vec_mean(T*in,int len)
{
	double mean=0;
	for(int i=0;i<len;i++)
	{
		mean+=double(in[i]);
	}
	mean/=len;
	return(mean);
}
template<typename T>inline double qx_vec_std(T*in,int len)
{
	double mean=qx_vec_mean(in,len);
	double std=0;
	for(int i=0;i<len;i++)
	{
		std+=double(in[i])*double(in[i]);
	}
	std/=len;
	std=sqrt(abs(std-mean*mean));
	return(std);
}
template<typename T>inline void qx_vec_min(T&min_val,int&min_pos,T*in,int len)
{
	T min_val_=in[0];
	int min_pos_=0;
	if(min_pos!=NULL)
	{
		for (int i=1;i<len;i++) if(in[i]<min_val_)
		{
			min_val_=in[i];
			min_pos_=i;
		}
		min_val=min_val_;
		min_pos=min_pos_;
	}
	else
	{
		for(int i=1;i<len;i++) if(in[i]<min_val_) min_val_=in[i];	
		min_val=min_val_;
	}
}
template<typename T>inline void qx_vec_max(T&max_val,int&max_pos,T*in,int len)
{
	T max_val_=in[0];
	int max_pos_=0;
	if(max_pos!=NULL)
	{
		for (int i=1;i<len;i++) if(in[i]>max_val_)
		{
			max_val_=in[i];
			max_pos_=i;
		}
		max_val=max_val_;
		max_pos=max_pos_;
	}
	else
	{
		for(int i=1;i<len;i++) if(in[i]>max_val_) max_val_=in[i];	
		max_val=max_val_;
	}
}
inline int qx_vec_max_pos_d3(double in[3]){int max_pos=0; double max_in=in[0]; if(in[1]>max_in){max_in=in[1]; max_pos=1;} if(in[2]>max_in){max_in=in[2]; max_pos=2;} return(max_pos);}

inline int qx_vec_min_pos_d3(double in[3]){int min_pos=0; double min_in=in[0]; if(in[1]<min_in){min_in=in[1]; min_pos=1;} if(in[2]<min_in){min_in=in[2]; min_pos=2;} return(min_pos);}
void vec_min_val(int &min_val,int *in,int len);
void vec_min_pos(int &min_pos,int *in,int len);
void vec_max_val(int &max_val,int *in,int len);
void vec_max_pos(int &max_pos,int *in,int len);
void vec_max_pos(unsigned int &max_pos,unsigned int *in,unsigned int len);
void vec_min_val(float &min_val,float *in,int len);
void vec_min_pos(int &min_pos,float *in,int len);
void vec_max_val(float &max_val,float *in,int len);
void vec_max_pos(int &max_pos,float *in,int len);

void vec_min_pos(int &min_pos,short *in,int len);

void vec_min_val(double &min_val,double *in,int len);
void vec_min_pos(int &min_pos,double *in,int len);
void vec_max_val(double &max_val,double *in,int len);
void vec_max_pos(int &max_pos,double *in,int len);
void vec_min_val(unsigned char &min_val,unsigned char *in,int len);
void vec_min_pos(int &min_pos,unsigned char *in,int len);
void vec_max_val(unsigned char &max_val,unsigned char *in,int len);
void vec_max_pos(int &max_pos,unsigned char *in,int len);

void vec_max_val(unsigned char &max_val,unsigned char *in,int len);
void vec_min_val(unsigned char &min_val,unsigned char *in,int len);
double vec_max(int &max_pos,double *in,int len);
double vec_min(int &min_pos,double *in,int len);
double vec_min_2nd(int &min_pos,double *in,double in_min,int len);
inline int qx_vec_find(unsigned char*in,unsigned char x,int len){for(int i=0;i<len;i++){if((*in++)==x) return(i);}return(-1);};
///*matrix operation*/
inline void qx_cross_matrix(double*out,double*in){out[0]=0; out[1]=-in[2]; out [2]=in[1]; out[3]=in[2]; out[4]=0; out [5]=-in[0]; out[6]=-in[1]; out[7]=in[0]; out [8]=0;};
double qx_determinant(double**InMat,int N);
float qx_determinant(float**InMat,int N);
bool qx_inv_2x2(double out[4],double in[4]);
inline double qx_det_3x3(double a[9]){return(a[0]*(a[4]*a[8]-a[5]*a[7])-a[1]*(a[3]*a[8]-a[5]*a[6])+a[2]*(a[3]*a[7]-a[4]*a[6]));}
double qx_inv_3x3(double out[9],double in[9],double threshold);
//void inv_3x3(double h_inv[9],double h_in[9]);
void inv_3x3(float h_inv[9],float h_in[9]);
void inv_3x3(double h_inv[9],float h_in[9]);
void inv_3x3(float h_inv[9],float &det,float h_in[9]);
void qx_inv_3x3(double h_inv[9],double &det,double h_in[9]);
//int qx_inv_4x4(double out[16],double in[16]);//+qx_inv_nxn: see qx_basic_geometric.h

inline void qx_eye_33(double a[9]){memset(a,0,sizeof(double)*9); a[0]=a[4]=a[8]=1;}
inline void qx_eye_3x3(double*out){memset(out,0,sizeof(double)*9); out[0]=out[4]=out[8]=1;}
inline void qx_eye_3x3(double**out){memset(out[0],0,sizeof(double)*9); out[0][0]=out[1][1]=out[2][2]=1;}
inline void qx_eye(double**out,int len){memset(out[0],0,sizeof(double)*len*len); for(int i=0;i<len;i++) out[i][i]=1;}
inline void qx_eye(int**out,int len){memset(out[0],0,sizeof(int)*len*len); for(int i=0;i<len;i++) out[i][i]=1;}
inline void qx_eye(float**out,int len){memset(out[0],0,sizeof(float)*len*len); for(int i=0;i<len;i++) out[i][i]=1;}
void qx_matrix_product_ata_3x3_a(float out[9],float at[9]);
void qx_matrix_product_ata_3x3_at(float out[9],float at[9]);
void inline qx_transpose_3x3(float at[9],float a[9]){at[0]=a[0]; at[1]=a[3]; at[2]=a[6]; at[3]=a[1]; at[4]=a[4]; at[5]=a[7]; at[6]=a[2]; at[7]=a[5]; at[8]=a[8];}
void inline qx_transpose_3x3(double at[9],double a[9]){at[0]=a[0]; at[1]=a[3]; at[2]=a[6]; at[3]=a[1]; at[4]=a[4]; at[5]=a[7]; at[6]=a[2]; at[7]=a[5]; at[8]=a[8];}
inline void qx_matrix_product_3x1(double out[3],double a[9],double b[3]){out[0]=a[0]*b[0]+a[1]*b[1]+a[2]*b[2];out[1]=a[3]*b[0]+a[4]*b[1]+a[5]*b[2];out[2]=a[6]*b[0]+a[7]*b[1]+a[8]*b[2];}
void qx_matrix_product_3x3(float out[9],float a[9],float b[9]);
void qx_matrix_product_ata_3x3_a(double out[9],double a[9]);
void qx_matrix_product_ata_3x3_at(double out[9],double at[9]);
void qx_matrix_product_3x3(double out[9],double a[9],double b[9]);
void qx_matrix_product(double**out,double**a,double**b,int N,int M,int L);//a[N,M]xb[M,L]=out[N,L]
void qx_matrix_product(float**out,float**a,float**b,int N,int M,int L);//a[N,M]xb[M,L]
void qx_matrix_product_axbt(double**out,double**a,double**b,int N,int M,int L);//a[N,M]xb[L,M](b'[M,L])=out[N,L]
void qx_matrix_product_axbt(float**out,float**a,float**b,int N,int M,int L);//a[N,M]xb[L,M](b'[M,L])=out[N,L]
void qx_matrix_product(double*out,double**a,double*b,int N,int M);//a[N,M]xb[M,1]=out[N,1]
void LX_Y (double **L, double *Y, int N, double *X);
void UX_Y (double **U, double *Y, int N, double *X);
void LU_33 (double **A, double **L, double **U);
void LU_Inverse (double **A, double **B);
void Transpose (double ** K, int N, int M, double ** K_Inv);

void LX_Y			(float **L, float *Y, int N, float *X);
void UX_Y			(float **U, float *Y, int N, float *X);
void LU_33			(float **A, float **L, float **U);
void LU_Inverse		(float **A, float **B);
void LUX_Y(double **L,double **U,double *UX,double *X,int N,double *Y);
void lu(int *exchange,double **l,double **u,double **in,double *tmp_array,int size);
void lu(int *exchange,float **l,float **u,float **in,float *tmp_array,int size);
void lux_y(float *x,float *y,float **l,float **u,float **in,int size);
void lux_y(double *x,double *y,double **l,double **u,double **in,int size);
void Transpose(float ** K, int N, int M, float ** K_Inv);

void Accumulate(double **InMat, int H, int W, double**OutMat);
void Accumulate(float **InMat, int H, int W, float**OutMat);

bool elem_not_in_array(int elem,int *array,int len);
int index_elem_in_array(int elem,int *array,int len);
void seek_8_neighbors(int neighbor_8[8],int &neighbor_8_nr,int p,int h,int w);

int pyramic_accumulate_2x2_sub(int in);
void pyramic_accumulate_2x2(float *p,int h,int w,int d,int scales);
void pyramic_alloc_2x2(float **p,int h,int w,int d,int scales);
void pyramic_locate_2x2(float ***qqq,float **qq,float *p,int h,int w,int d,int scales_idx);


//image processing
int get_binomial_elem(int n,int m);
void get_binomial_array(int *bin, int len);
void get_binomial_matrix(int **out, int len);
void get_binomial_matrix_coef(float **out,int **t_out,int len);
void img_smooth_3x3(float **img_in, int h, int w);
void img_smooth_3x3_shift(unsigned char **image,int h,int w);
void img_smooth_121(unsigned char **image,int h,int w);
void img_smooth_121(unsigned char ***image,int h,int w);

void img_smooth_14641_shift(unsigned char ***image,int h,int w);
void img_smooth_14641(unsigned char ***image,int h,int w);
void img_smooth_14641_shift(double***image,int h,int w);
void img_smooth_14641(double***image,int h,int w);

void img_smooth_14641_shift(unsigned char**image,int h,int w);
void img_smooth_14641(unsigned char**image,int h,int w);
void img_smooth_14641_shift(double**image,int h,int w);
void img_smooth_14641(double**imae,int h,int w);

void img_smooth_3x3_rgb(float ***img_in_rgb, int h, int w);
void img_smooth_nxn(float **img_in,int h,int w,int len);
void img_smooth_nxn(float ***img_in,int h,int w,int len);
void img_boxcar_odd(float **in,int h,int w,int win_size);
void img_boxcar_odd(double **in,int h,int w,int win_size);
void img_boxcar_odd(int **in,int h,int w,int win_size);
void img_boxcar_odd(unsigned char **in,double **box,int h,int w,int win_size);
void img_boxcar_odd(float **in,double **box,int **nr_valid,int h,int w,int win_size);
void img_boxcar_odd(float**in,double **box,int h,int w,int win_size);
void img_boxcar_odd(double **in,double **box,int h,int w,int win_size);
void qx_boxcar_filter(int **out,int **in,int **temp,int w,int h,int filter_w,int filter_h);
void img_grad(float **img_in, int h, int w);
void qx_image_gradient_xy(unsigned char***gradients,unsigned char***image,int h,int w);
void qx_image_gradient_xy(unsigned char***gradients,unsigned char**image,int h,int w);
void untexture_search(unsigned char**untexture,unsigned char***gradients,unsigned char ***image,unsigned char max_grad,int h,int w);
void qx_image_gradient_8_neighbor(unsigned char***gradients,unsigned char ***image,int h,int w);
void image_gradient_back(float ***gradient,unsigned char ***image,int h,int w);
void image_gradient_back(float ***gradient,float ***image,int h,int w);
void image_gradient_back(float ***gradient,float **image,int h,int w);
void image_gradient_back(float ***gradient,unsigned char **image,int h,int w);
void image_divergence_forward(float ***image,float ***gradient,int h,int w,bool is_calc_gradient=true);
void image_divergence_forward(float **image,float ***gradient,int h,int w,bool is_calc_gradient=true);
//void image_divergence_forward(unsigned char **image,float ***gradient,int h,int w,bool is_calc_gradient=true);
void image_divergence_forward(float ***div,float ***gradient,unsigned char ***image,int h,int w);
void image_divergence_forward_without_gradient(float **image,float ***gradient,int h,int w);
void get_edges(unsigned char **out,float **in,int radius,float larger_equal,int h,int w);
void get_edges(unsigned char **out,short**in,int radius,short larger_equal,int h,int w);
void get_edges(unsigned char **out,int **in,int radius,int larger_equal,int h,int w);
void get_edges(unsigned char **out,unsigned char **in,int radius,unsigned char larger_equal,int h,int w);
void get_edges(unsigned char **out,unsigned char **in,unsigned char larger_equal,int h,int w);
void get_edges_inside_mask(unsigned char **edge,unsigned char **mask,int h,int w);
void img_rgb_2_gray(float **out,float***in,int h,int w);
void down_sample_1(unsigned char ***out,unsigned char ***in,int h,int w,int downsample_rate,int id=0);
void down_sample_1(unsigned char **out,unsigned char **in,int h,int w,int downsample_rate);
void down_sample_1(float ***out,float ***in,int h,int w,int downsample_rate);
void down_sample_1(double***out,double***in,int h,int w,int downsample_rate);
void down_sample_1(float**out,float**in,int h,int w,int downsample_rate);/*h,w: input resolution*/
void down_sample_1(float*out,float*in,int h,int w,int downsample_rate);
void down_sample_1(double**out,double**in,int h,int w,int downsample_rate);
void segm_display(int **labels,int nr_labels,int h,int w);
void segm_display(unsigned char***labels_ppm,int **labels,int nr_labels,int h,int w);
void label_2_segm(unsigned char ***segm,int **labels,int nr_labels,int h,int w);
void down_sample_121(unsigned char ***out,unsigned char ***in,int h,int w,int downsample_rate);
void down_sample_121(unsigned char **out,unsigned char **in,int h,int w,int downsample_rate);
void down_sample_14641(unsigned char ***out,unsigned char ***in,int h,int w,int downsample_rate);
void down_sample_14641_rgb(unsigned char*out,unsigned char*in,int h,int w,int downsample_rate);
void down_sample_14641(unsigned char ***out,unsigned char ***in,int ho,int wo,int h,int w);
void up_sample(float **out,float **in,int h,int w,int upsample_rate);
void up_sample(int **out,int**in,int h,int w,int upsample_rate);
void up_sample(short**out,short**in,int h,int w,int upsample_rate);
void up_sample(unsigned char **out,unsigned char **in,int h,int w,int upsample_rate);
void up_sample(unsigned char***out,unsigned char***in,int h,int w,int nr_channel,int upsample_rate);
///*image debug*/
//void image_display(unsigned char *in,int h,int w);
//void image_display(float *in,int h,int w);
//void image_display(int *in,int h,int w);
//void image_display(unsigned char **in,int h,int w);
//void image_display(float **in,int h,int w);
//void image_display(int **in,int h,int w);
//void image_display(unsigned char ***in,int h,int w);
//void image_display(double **in,int h,int w);
/*camera parameter*/
inline void qx_2dline_from_2point(double &k,double &b,int x1,int y1,int x2,int y2){k=qx_div(y1-y2,x1-x2); b=qx_div(x1*y2-x2*y1,x1-x2);}
inline void qx_canonical_cam(double p[12]){memset(p,0,sizeof(double)*12); p[0]=p[5]=p[10]=1;}
inline void qx_kmat_scale(double kmat[9],double scalar){kmat[0]*=scalar; kmat[2]*=scalar; kmat[4]*=scalar; kmat[5]*=scalar;};
void get_kinv(float kinvmat[3][3],float kmat[3][3]);
void get_kinv(double kinv[9],double kmat[9]);
inline void kinv_xy_d(double point[3],double kinv[9],double x,double y){point[0]=kinv[0]*x+kinv[1]*y+kinv[2]; point[1]=kinv[4]*y+kinv[5]; point[2]=1;}
inline void kinv_xy(double point[3],double kinv[9],int x,int y){point[0]=kinv[0]*x+kinv[1]*y+kinv[2]; point[1]=kinv[4]*y+kinv[5]; point[2]=1;}
inline void kinv_xy(float point[3],double kinv[9],int x,int y){point[0]=float(kinv[0]*x+kinv[1]*y+kinv[2]); point[1]=float(kinv[4]*y+kinv[5]); point[2]=1.f;}
inline void kmat_xy(int &x,int &y,double kmat[9],double point[3]){x=int(kmat[0]*point[0]+kmat[1]*point[1]+kmat[2]+0.5); y=int(kmat[4]*point[1]+kmat[5]+0.5);}
void kinv_xy(float ***xy,double kinv[9],int h,int w);
void kinv_xy(float**xy,double kinv[9],int h,int w);
void kmat_xy(float ***xy,double kmat[9],int h,int w);
void get_rinv(float rinvmat[3][3],float viewmat[3][4]);
void get_cop(float cop[3],float viewmat[3][4],float rinvmat[3][3]);
void qx_depth_2_zvalue(float **depth,double *kinv,int h,int w);
void qx_depth_2_disp(float **depth,int h,int w,int nr_planes,float depth_min,float depth_max,double *kinv);
void qx_disp_2_depth(float **depth,int h,int w,int nr_planes,float depth_min,float depth_max,double *kinv,bool use_zdepth_value=false);
double qx_disp_2_depth(int disparity,int nr_plane,double zmin,double zmax,bool use_zdepth_value=true,double *kinv=NULL,int h=0,int w=0);
void qx_disp_2_zdepth(float **depth,float baseline,float focal_length,int h,int w);
void qx_zdepth_2_disp(float **depth,float baseline,float focal_length,int h,int w);
inline float qx_disp_2_zdepth(float disparity,double baseline,double focal_length){if(disparity>QX_DEF_THRESHOLD_ZERO) return(float(baseline*focal_length/disparity)); else return(-QX_DEF_THRESHOLD_ZERO);}
inline float qx_disp_2_zdepth(float disparity,double baseline_x_focal_length){if(disparity>QX_DEF_THRESHOLD_ZERO) return(float(baseline_x_focal_length/disparity)); else return(-QX_DEF_THRESHOLD_ZERO);}
inline float qx_zdepth_2_disp(float disparity,double baseline,double focal_length){if(disparity>QX_DEF_THRESHOLD_ZERO) return(float(baseline*focal_length/disparity)); else return(-QX_DEF_THRESHOLD_ZERO);}
inline float qx_zdepth_2_disp(float disparity,double baseline_x_focal_length){if(disparity>QX_DEF_THRESHOLD_ZERO) return(float(baseline_x_focal_length/disparity)); else return(-QX_DEF_THRESHOLD_ZERO);}
void qx_depth_2_disp(float **depth,float baseline,float focal_length,double *kinv,int h,int w);
void qx_disp_2_depth(float **depth,float baseline,float focal_length,double *kinv,int h,int w);
float qx_disp_2_depth(int disparity,double baseline_x_focal_length,double *kinv,int x,int y);
void qx_zvalue_2_depth(float **depth,double *kinv,int h,int w);
float qx_disp_2_zvalue(float depth,int nr_planes,float depth_min,float depth_max,double *kinv);
float qx_zvalue_2_depth(float depth,double *kinv,int y,int x);

/*sphere calibration*/
double get_sphere_mask_center_and_radius(double center_sphere[2],unsigned char **mask,int h,int w);
void get_highlight_center(double center_highlight[2],unsigned char **image,unsigned char **mask,int h,int w);
void normal_from_mirror_sphere(double normal[3],unsigned char **image,unsigned char **mask,int h,int w);
inline void qx_get_reflected_light(float rl[3],float l[3],float n[3])
{
	double ln2=2*qx_dot_f3(l,n); rl[0]=float(ln2*n[0]-l[0]); rl[1]=float(ln2*n[1]-l[1]); rl[2]=float(ln2*n[2]-l[2]);
}
/*two-view stereo*/
void qx_occlusion_from_disparity(unsigned char**occl,unsigned char**disp,int h,int w);
bool plane_fit_3p(float para[3],float p0[3],float p1[3],float p2[3]);
bool plane_fit_3p(double para[3],double p0[3],double p1[3],double p2[3]);
void depth_sub_pixel(float **depth_f,int **depth_i,float ***evidence,int h,int w,int nr_planes);
void depth_sub_pixel(float**depth_f,unsigned char**depth_i,double***evidence,int h,int w,int nr_planes);
void depth_sub_pixel(float **depth_f,float ***evidence,int h,int w,int nr_planes);
void depth_sub_pixel(float**depth_f,short***evidence,int h,int w,int nr_planes);
void depth_sub_pixel(float &depth_f,float *evidence,int nr_planes);
void depth_sub_pixel(float&depth_f,double*evidence,int nr_planes);
float depth_sub_pixel(float*evidence,int nr_planes);
double depth_sub_pixel(double*evidence,int nr_planes);
double depth_sub_pixel(double*evidence,int d,int nr_planes);
double depth_sub_pixel_linear(double*evidence,int nr_planes);
double depth_sub_pixel_max(double *evidence,int nr_planes);
float depth_sub_pixel_max(float *evidence,int nr_planes);
void depth_best_cost(unsigned char**depth,double***evidence,int h,int w,int nr_planes);
void depth_best_cost(int**depth,unsigned char***evidence,int h,int w,int nr_planes);
void depth_best_cost(unsigned char**depth,unsigned char***evidence,int h,int w,int nr_planes);
void depth_best_cost(unsigned char**depth,float ***evidence,int h,int w,int nr_planes);
void depth_best_cost(unsigned char**depth,short***evidence,int h,int w,int nr_planes);
void depth_best_cost(short**depth,short***evidence,int h,int w,int nr_planes);
void depth_best_cost(int **depth,float ***evidence,int h,int w,int nr_planes);
void depth_best_cost(float **depth,float ***evidence,int h,int w,int nr_planes);
void depth_kth_cost(int **depth,float ***evidence,int h,int w,int nr_planes);
void quantized_depth_2_sub_pixel(float **depth_f,int **depth,float ***evidence,int h,int w,int nr_planes);
void confidence_from_corr_vol(float **confidence,float ***cost,int **depth,int h,int w,int nr_planes);
void confidence_from_corr_vol(float **confidence,float ***cost,int **depth,int h,int w,int nr_planes,float sigma);
void confidence_from_corr_vol(float **confidence,float ***cost,float **depth,int h,int w,int nr_planes,float sigma);
void confidence_from_corr_vol(float **confidence,float ***cost,int **depth,int h,int w,int nr_planes,int win_size,float sigma);
float confidence_from_corr_vol(float *cost,int depth,int nr_planes,float sigma);
float confidence_from_corr_vol(int *cost,int depth,int nr_planes,float sigma);
void confidence_using_entropy(float **confidence,float ***cost,int h,int w,int nr_planes);
void qx_detect_occlusion_left_right(unsigned char**mask_left,unsigned char**depth_left,unsigned char**depth_right,int h,int w,int nr_plane);
void qx_detect_occlusion_left_right(unsigned char**mask_left,unsigned char**mask_right,unsigned char**depth_left,unsigned char**depth_right,int h,int w,int nr_plane);
void qx_occlusion_solver_left_right(short**depth_left,short**depth_right,int h,int w,int nr_plane,bool solve_both=false,int downsample_rate=0);
void qx_occlusion_solver_left_right(unsigned char**depth_left,unsigned char**depth_right,unsigned char**temp,int h,int w,int nr_plane);
void qx_occlusion_solver_left_right(unsigned char**depth_left,unsigned char**depth_right,int h,int w,int nr_plane,bool solve_both=false);
void qx_occlusion_solver_left_right(int**depth_left,int**depth_right,int h,int w,int nr_plane,bool solve_both=false);
void qx_occlusion_solver_left_right(float**depth_left,float**depth_right,int h,int w,int nr_plane,bool solve_both=false);
void qx_stereo_flip_corr_vol(short***corr_vol_right,short***corr_vol,int h,int w,int nr_plane);
void qx_stereo_flip_corr_vol(double***corr_vol_right,double***corr_vol,int h,int w,int nr_plane);
void qx_stereo_flip_corr_vol(float***corr_vol_right,float***corr_vol,int h,int w,int nr_plane);
void qx_stereo_evaluation_middlebury(float error[3],unsigned char**disparity,unsigned char**disparity_gt,unsigned char***mask,int h,int w,int scalar,float error_threshold=1.f);
double qx_stereo_evaluation_middlebury(unsigned char**disparity,unsigned char**disparity_gt,int h,int w,int scalar,float error_threshold);
double qx_stereo_evaluation_middlebury(unsigned char**disparity,unsigned char**disparity_gt,unsigned char**mask,int h,int w,int scalar,float error_threshold);
/*plot*/
void plot_2d(float *ys,float *xs,float ymin,float ymax,int h,float xmin,float xmax,int w);
void plot_2d(float *ys,float ymin,float ymax,int h,float xmin,float xmax,float xdelta,int w);
void plot_hist(int *hist,int h,int w);
void plot_hist(unsigned char **image,int *hist,int h,int w);
void plot_hist(double *hist,int h,int w);
void plot_hist(float *hist,int h,int w);
class qx_timer{public: void start(); double stop(); void time_display(char *disp="",int nr_frame=1); void fps_display(char *disp="",int nr_frame=1); private: double m_pc_frequency; __int64 m_counter_start;};//clock_t m_begin,m_end;};
inline unsigned char euro_dist_nonlocal_means(unsigned char*a,unsigned char*b,int nr_dimension) 
{
	double dist=0;
	for(int i=0;i<nr_dimension;i++) 
	{
		double dab=(*a++)-(*b++);
		dist+=dab*dab;
	}
	return(unsigned char(sqrt(dist/nr_dimension)+0.5));
}
inline unsigned char euro_dist_nonlocal_means(float*a,float*b,int nr_dimension) 
{
	double dist=0;
	for(int i=0;i<nr_dimension;i++) 
	{
		double dab=(*a++)-(*b++);
		dist+=dab*dab;
	}
	return(unsigned char(min(255,sqrt(dist/nr_dimension))+0.5));
}

inline unsigned char euro_dist_rgb_max(unsigned char *a,unsigned char *b) {unsigned char x,y,z; x=abs(a[0]-b[0]); y=abs(a[1]-b[1]); z=abs(a[2]-b[2]); return(max(max(x,y),z));}
inline float euro_dist_rgb_max(float *a,float *b) {float x,y,z; x=abs(a[0]-b[0]); y=abs(a[1]-b[1]); z=abs(a[2]-b[2]); return(max(max(x,y),z));}
inline double euro_dist_rgb_max(double *a,double *b) {double x,y,z; x=abs(a[0]-b[0]); y=abs(a[1]-b[1]); z=abs(a[2]-b[2]); return(max(max(x,y),z));}
inline unsigned char euro_dist_rgb_mean(unsigned char*a,unsigned char*b) {unsigned char x,y,z; x=abs(a[0]-b[0]); y=abs(a[1]-b[1]); z=abs(a[2]-b[2]); return(unsigned char(0.229f*x+0.587f*y+0.114f*z+0.5));}
inline unsigned char euro_dist_rgb_mean(unsigned char*a,unsigned char*b,int len) {double diff,diff_sum=0; for(int i=0;i<len;i++){diff=a[i]-b[i]; diff_sum+=diff*diff;}; return(unsigned char(sqrt(diff_sum/len)+0.5));}
//inline unsigned char euro_dist_rgb_mean(unsigned char*a,unsigned char*b) {unsigned char x,y,z; x=abs(a[0]-b[0]); y=abs(a[1]-b[1]); z=abs(a[2]-b[2]); return(((x<<1)+y+z)>>2);}
inline float euro_dist_rgb_mean(float *a,float *b) {float x,y,z; x=abs(a[0]-b[0]); y=abs(a[1]-b[1]); z=abs(a[2]-b[2]); return(0.229f*x+0.587f*y+0.114f*z);}
inline double euro_dist_rgb_mean(double*a,double*b) {double x,y,z; x=abs(a[0]-b[0]); y=abs(a[1]-b[1]); z=abs(a[2]-b[2]); return(0.229*x+0.587*y+0.114*z);}

inline unsigned char qx_hamming_distance(unsigned char val){unsigned char dist=0; while(val){dist++; val&=val-1;} return dist;}
inline unsigned char qx_hamming_distance(unsigned char x, unsigned char y){unsigned char dist=0, val=x^y; while(val){dist++; val&=val-1;} return dist;}
inline unsigned qx_hamming_distance(unsigned x, unsigned y){unsigned dist=0, val=x^y; while(val){dist++; val&=val-1;} return dist;}
inline unsigned char qx_census_transform_3x3_sub(unsigned char*in,int w)
{
	unsigned char census=(*(in-w-1)>*in);
	census+=((*(in-w)>*in)<<1);
	census+=((*(in-w+1)>*in)<<2);
	census+=((*(in-1)>*in)<<3);
	census+=((*(in+1)>*in)<<4);
	census+=((*(in+w-1)>*in)<<5);
	census+=((*(in+w)>*in)<<6);
	census+=((*(in+w+1)>*in)<<7);
	return(census);
}
inline void qx_census_transform_3x3(unsigned char*out,unsigned char*in,int h,int w)
{
	memset(out,0,sizeof(char)*h*w);
	omp_set_num_threads(omp_get_max_threads());
	#pragma omp parallel for
	for(int y=1;y<h-1;y++) 
	{
		for(int x=1;x<w-1;x++)
		{
			int id=y*w+x;
			out[id]=qx_census_transform_3x3_sub(&(in[id]),w);
		}
	}
}
inline void qx_census_transform_3x3(unsigned char**out,unsigned char**in,int h,int w)
{
	qx_census_transform_3x3(out[0],in[0],h,w);
}
inline unsigned char qx_census_transform_3x3_sub(unsigned short*in,int w)
{
	unsigned char census=(*(in-w-1)>*in);
	census+=((*(in-w)>*in)<<1);
	census+=((*(in-w+1)>*in)<<2);
	census+=((*(in-1)>*in)<<3);
	census+=((*(in+1)>*in)<<4);
	census+=((*(in+w-1)>*in)<<5);
	census+=((*(in+w)>*in)<<6);
	census+=((*(in+w+1)>*in)<<7);
	return(census);
}
inline void qx_census_transform_3x3(unsigned char**out,unsigned short**in,int h,int w)
{
	for(int y=1;y<h-1;y++) for(int x=1;x<w-1;x++)
	{
		out[y][x]=qx_census_transform_3x3_sub(&(in[y][x]),w);
	}
	memset(out[0],0,sizeof(char)*w);
	memset(out[h-1],0,sizeof(char)*w);
	for(int y=1;y<h-1;y++) for(int x=0;x<w;x+=w-1) 
	{
		out[y][x]=0;
	}
}
void qx_split(int &h,int &w,int len);
inline unsigned char qx_vec_difference_min(unsigned char *a,unsigned char *b,int len){unsigned char diff,diff_min=255; for(int i=0;i<len;i++){diff=abs(a[i]-b[i]); if(diff<diff_min) diff_min=diff;} return(diff_min);}
inline unsigned char qx_vec_difference_max(unsigned char *a,unsigned char *b,int len){unsigned char diff,diff_max=0; for(int i=0;i<len;i++){diff=abs(a[i]-b[i]); if(diff>diff_max) diff_max=diff;} return(diff_max);}
inline unsigned char qx_vec_rms(unsigned char *a,unsigned char *b,int len){unsigned char diff,diff_max=0; for(int i=0;i<len;i++){diff=abs(a[i]-b[i]); if(diff>diff_max) diff_max=diff;} return(diff_max);}
void compute_hypothesis_array(float *hypo,float hmin,float hmax,int len);
inline double qx_radian_2_degree(double theta){return(theta*180.0/QX_DEF_PI_DOUBLE);}
inline float qx_radian_2_degree(float theta){return(float(theta*180/QX_DEF_PI_DOUBLE));}
inline double qx_degree_2_radian(double theta){return(theta*QX_DEF_PI_DOUBLE/180);}
inline float qx_degree_2_radian(float theta){return(float(theta*QX_DEF_PI_DOUBLE/180));}
inline double qx_radian_from_vector(double cos_theta,double sin_theta)
{
	double out;
	if(abs(cos_theta)<QX_DEF_THRESHOLD_ZERO&&abs(sin_theta)<QX_DEF_THRESHOLD_ZERO) return(0);
	if(abs(cos_theta)<QX_DEF_THRESHOLD_ZERO&&sin_theta>0) return(QX_DEF_PI_DOUBLE*0.5);
	else if(abs(cos_theta)<QX_DEF_THRESHOLD_ZERO&&sin_theta<0) return(QX_DEF_PI_DOUBLE*1.5);
	else if(abs(sin_theta)<QX_DEF_THRESHOLD_ZERO&&cos_theta>0) return(0);
	else if(abs(sin_theta)<QX_DEF_THRESHOLD_ZERO&&cos_theta<0) return(QX_DEF_PI_DOUBLE);
	else out=sin_theta/cos_theta;
	if(sin_theta>0&&cos_theta>0) return(atan(out)); /*1*/
	else if(sin_theta<0&&cos_theta>0) return(QX_DEF_PI_DOUBLE+QX_DEF_PI_DOUBLE+atan(out)); /*4*/
	else if(sin_theta<0&&cos_theta<0) return(QX_DEF_PI_DOUBLE+atan(out));/*3*/
	else return(QX_DEF_PI_DOUBLE+atan(out));/*2*/
}
inline double qx_degree_from_vector(double cos_theta,double sin_theta)
{
	return(qx_radian_2_degree(qx_radian_from_vector(cos_theta,sin_theta)));
}
void qx_bounding_box_from_mask(int &y0,int &x0,int &ho,int &wo,unsigned char**mask,int h,int w);
inline void qx_colormapped(unsigned char out[3],float d,float dmin,float dmax,float**colormap,int nr_color)
{
	int id=int((nr_color-1)*(d-dmin)/(dmax-dmin)+0.5);
	if(id>=0&&id<nr_color) for(int c=0;c<3;c++) out[c]=unsigned char(255*colormap[id][c]+0.5);
	else memset(out,0,sizeof(char)*3);
}
void qx_mmx_compute_max_abs_gradient(unsigned char*texture,unsigned char*gradient_x,unsigned char*gradient_y,int h,int w);
inline void qx_mmx_absolution_difference_8(unsigned char*c,unsigned char*a,unsigned char*b)
{
	_asm
	{
		mov eax,a
		mov ebx,b
		mov ecx,c
		movq mm0,[eax]
		movq mm1,[ebx]
		movq mm2,mm0
		psubusb mm0,mm1
		psubusb mm1,mm2
		por mm0,mm1

		movq [ecx],mm0
		//movd       b,mm0
		emms
	}
}
void qx_mmx_compute_abs_of_2_gray_image(unsigned char*out,unsigned char*Ia,unsigned char*Ib,int h,int w);
void qx_mmx_compute_abs_of_2_gray_image2(unsigned char*out,unsigned char*Ia,unsigned char*Ib,int h,int w);
void qx_mmx_compute_abs_of_2_gray_image3(unsigned char*out,unsigned char*Ia,unsigned char*Ib,int h,int w);
#endif