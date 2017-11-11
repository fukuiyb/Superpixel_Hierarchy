/*$Id: ppm.cpp,v 1.23 2007/04/04 02:15:14 liiton Exp $*/
#include "basic.h"
#include "ppm.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "stdafx.h"

#define LEN_MAX	256
float* get_binary(FILE* file_in,int h,int w,int channel)
{
	float *image=NULL;
	image=(float*)malloc(sizeof(float)*w*h*channel); 
	memset(image,0,sizeof(float)*w*h*channel);
	fread(image,sizeof(float),w*h*channel,file_in);
	return image;
}
void qx_saveimage(char* filename,float *image,int h,int w,int channel)
{	
	FILE* file_out; int i; float maxx;
	//file_out=fopen(filename,"wb");
	fopen_s(&file_out,filename,"wb");
	maxx=image[0];
	for(i=0;i<h*w*channel;i++) maxx=max(maxx,image[i]);
	if(channel==1) fprintf(file_out,"P7\n%d %d\n%f\n",w,h,maxx);
	else if(channel==3) fprintf(file_out,"P8\n%d %d\n%f\n",w,h,maxx);
	else fprintf(file_out,"P9\n%d %d\n%d\n%f\n",w,h,channel,maxx);
	fwrite(image,sizeof(float),w*h*channel,file_out);
	fclose(file_out);
}
void qx_saveimage(char*filename,short*image,int h,int w,int channel)
{	
	FILE* file_out; int i; float maxx;
	//file_out=fopen(filename,"wb");
	fopen_s(&file_out,filename,"wb");
	maxx=image[0];
	for(i=0;i<h*w*channel;i++) maxx=max(maxx,image[i]);
	if(channel==1) fprintf(file_out,"P7\n%d %d\n%f\n",w,h,maxx);
	else if(channel==3) fprintf(file_out,"P8\n%d %d\n%f\n",w,h,maxx);
	else fprintf(file_out,"P9\n%d %d\n%d\n%f\n",w,h,channel,maxx);
	fwrite(image,sizeof(short),w*h*channel,file_out);
	fclose(file_out);
}
void qx_saveimage(char* filename,double *image,int h,int w,int channel)
{	
	FILE* file_out; int i; float maxx;
	float *image_f=new float [h*w*channel];
	for(i=0;i<h*w*channel;i++) image_f[i]=(float)image[i];
	//file_out=fopen(filename,"wb");
	fopen_s(&file_out,filename,"wb");
	maxx=image_f[0];
	for(i=0;i<h*w*channel;i++) maxx=max(maxx,image_f[i]);
	if(channel==1) fprintf(file_out,"P7\n%d %d\n%f\n",w,h,maxx);
	else if(channel==3) fprintf(file_out,"P8\n%d %d\n%f\n",w,h,maxx);
	else fprintf(file_out,"P9\n%d %d\n%d\n%f\n",w,h,channel,maxx);
	fwrite(image_f,sizeof(float),w*h*channel,file_out);
	fclose(file_out);
	delete [] image_f; image_f=NULL;
}
/*P2(PGM ASCII format), P3(is_ppm ASCII format), P5 (PGM Binary format), P6 (is_ppm Binary format), P7 (pgm Binary format)*/
float*qx_loadimage_f(char* filename,int &h,int &w)
{
	int nrc=qx_image_size(filename,h,w);
	float *image=new float [h*w*nrc];
	qx_loadimage(filename,image,h,w);
	return(image);
}
float**qx_loadimage_f2(char* filename,int &h,int &w)
{
	int nrc=qx_image_size(filename,h,w); float **image=NULL;
	if(nrc==1)
	{	
		image=qx_allocf(h,w);
		qx_loadimage(filename,image[0],h,w);
	}
	else
	{
		printf("Can not open image [%s]!!\n",filename); getchar(); exit(-1);
	}
	return(image);
}
float***qx_loadimage_f3(char* filename,int &h,int &w)
{
	int nrc=qx_image_size(filename,h,w); float ***image=NULL;
	if(nrc>1)
	{	
		image=qx_allocf_3(h,w,nrc);
		qx_loadimage(filename,image[0][0],h,w);
	}
	else
	{
		printf("Can not open image [%s]!!\n",filename); getchar(); exit(-1);
	}
	return(image);
}
unsigned char*qx_loadimage_u(char* filename,int &h,int &w)
{
	int nrc=qx_image_size(filename,h,w);
	unsigned char *image=new unsigned char [h*w*nrc];
	qx_loadimage(filename,image,h,w);
	return(image);
}
unsigned char**qx_loadimage_u2(char* filename,int &h,int &w)
{
	int nrc=qx_image_size(filename,h,w); unsigned char **image=NULL;
	if(nrc==1)
	{	
		image=qx_allocu(h,w);
		qx_loadimage(filename,image[0],h,w);
	}
	else
	{
		printf("Can not open image [%s]!!\n",filename); getchar(); exit(-1);
	}
	return(image);
}
unsigned char***qx_loadimage_u3(char* filename,int &h,int &w)
{
	int nrc=qx_image_size(filename,h,w); unsigned char ***image=NULL;
	if(nrc>1)
	{	
		image=qx_allocu_3(h,w,nrc);
		qx_loadimage(filename,image[0][0],h,w);
	}
	else
	{
		printf("Can not open image [%s]!!\n",filename); getchar(); exit(-1);
	}
	return(image);
}
void qx_saveimage(char* filename,unsigned char *image,int h,int w,int channel)
{	
	FILE* file_out; unsigned char maxx=255;
	fopen_s(&file_out,filename,"wb");
	if(channel==1) fprintf(file_out,"P5\n%d %d\n%d\n",w,h,maxx);
	//else if(channel==3) fprintf(file_out,"P6\n%d %d\n%d\n",w,h,maxx);
	else if(channel==3) fprintf(file_out,"P6\n%d %d\n%d\n",w,h,maxx);
	else fprintf(file_out,"P9\n%d %d\n%d\n%d\n",w,h,channel,maxx);
	fwrite(image,sizeof(unsigned char),h*w*channel,file_out);

	fclose(file_out);
}
void qx_saveimage(char*filename,char*image,int h,int w,int channel)
{	
	FILE* file_out; char maxx=255;
	fopen_s(&file_out,filename,"wb");
	if(channel==1) fprintf(file_out,"P5\n%d %d\n%d\n",w,h,maxx);
	//else if(channel==3) fprintf(file_out,"P6\n%d %d\n%d\n",w,h,maxx);
	else if(channel==3) fprintf(file_out,"P6\n%d %d\n%d\n",w,h,maxx);
	else fprintf(file_out,"P9\n%d %d\n%d\n%d\n",w,h,channel,maxx);
	fwrite(image,sizeof(char),h*w*channel,file_out);
	fclose(file_out);
}
int qx_loadimage(char* filename,unsigned char *image,int h,int w,int *nr_channel)
{
	FILE * file_in; int nrc;
	char line[LEN_MAX];
	int	i; int imax,hc,wc;	
	unsigned char *image_=image;
	fopen_s(&file_in,filename,"rb");
	if(!file_in)
	{
		printf("Please check input filename: %s\n",filename);
		exit(0);
	}
	if(fgetc(file_in)=='P') 
		fscanf_s(file_in,"%d\n",&i);
	else
	{
		printf("Bad	header in ppm file.\n");
		exit(1);
	}
	while(fgets(line,LEN_MAX,file_in)!=NULL)
	{
		if(line[0]=='#') continue;
		else
		{	
			sscanf_s(line, "%d %d\n",&wc,&hc);
			break;
		}
	}
	char str_tmp[100];
	switch (i)
	{
		case 5:
			fgets(str_tmp,100,file_in);
			imax=atoi(str_tmp);
			if(nr_channel!=NULL) (*nr_channel)=1;
			memset(image,0,sizeof(unsigned char)*h*w);
			fread(image,sizeof(unsigned char),h*w,file_in);
			break;
		case 6:
			fgets(str_tmp,100,file_in);
			imax=atoi(str_tmp);
			if(nr_channel!=NULL) (*nr_channel)=3;
			memset(image,0,sizeof(unsigned char)*h*w*3);
			fread(image,sizeof(unsigned char),h*w*3,file_in);
			break;
		case 2:
			fgets(str_tmp,100,file_in);
			imax=atoi(str_tmp);
			for(int y=0;y<h;y++) for(int x=0;x<w;x++)
			{
				//if(fscanf_s(file_in,"%d",&imax)!=1){printf("error in reading file.\n");getchar();exit(0);}
				fscanf_s(file_in,"%d",&imax);
				*image_++=imax;
			}
			break;
		case 3:
			fgets(str_tmp,100,file_in);
			imax=atoi(str_tmp);
			int cr,cg,cb;
			for(int y=0;y<h;y++) for(int x=0;x<w;x++)
			{
				//if(fscanf_s(file_in,"%d%d%d",&cr,&cg,&cb)!=3){printf("error in reading file.\n");getchar();exit(0);}
				fscanf_s(file_in,"%d%d%d",&cr,&cg,&cb);
				*image_++=cr; *image_++=cg; *image_++=cb; 
			}
			break;
		case 9:
			fgets(str_tmp,100,file_in);
			nrc=atoi(str_tmp);
			fscanf_s(file_in,"%d\n",&nrc);
			if(nr_channel!=NULL) (*nr_channel)=nrc;
			fgets(str_tmp,100,file_in);
			imax=atoi(str_tmp);
			fread(image,sizeof(unsigned char),h*w*nrc,file_in);
			break;
		default:
			printf("Can not open image [%s]!!\n",filename);
			break;					
	}
	fclose(file_in);
	return (0);
}
int qx_loadimage(char* filename,char *image,int h,int w,int *nr_channel)
{
	FILE * file_in; int nrc;
	char line[LEN_MAX];
	int	i; int imax,hc,wc;	
	char *image_=image;
	fopen_s(&file_in,filename,"rb");
	if(!file_in)
	{
		printf("Please check input filename: %s\n",filename);
		exit(0);
	}
	if(fgetc(file_in)=='P') 
		fscanf_s(file_in,"%d\n",&i);
	else
	{
		printf("Bad	header in ppm file.\n");
		exit(1);
	}
	while(fgets(line,LEN_MAX,file_in)!=NULL)
	{
		if(line[0]=='#') continue;
		else
		{	
			sscanf_s(line, "%d %d\n",&wc,&hc);
			break;
		}
	}
	char str_tmp[100];
	switch (i)
	{
		case 5:
			fgets(str_tmp,100,file_in);
			imax=atoi(str_tmp);
			if(nr_channel!=NULL) (*nr_channel)=1;
			memset(image,0,sizeof(char)*h*w);
			fread(image,sizeof(char),h*w,file_in);
			break;
		case 6:
			fgets(str_tmp,100,file_in);
			imax=atoi(str_tmp);
			if(nr_channel!=NULL) (*nr_channel)=3;
			memset(image,0,sizeof(char)*h*w*3);
			fread(image,sizeof(char),h*w*3,file_in);
			break;
		case 2:
			fgets(str_tmp,100,file_in);
			imax=atoi(str_tmp);
			for(int y=0;y<h;y++) for(int x=0;x<w;x++)
			{
				//if(fscanf_s(file_in,"%d",&imax)!=1){printf("error in reading file.\n");getchar();exit(0);}
				fscanf_s(file_in,"%d",&imax);
				*image_++=imax;
			}
			break;
		case 3:
			fgets(str_tmp,100,file_in);
			imax=atoi(str_tmp);
			int cr,cg,cb;
			for(int y=0;y<h;y++) for(int x=0;x<w;x++)
			{
				//if(fscanf_s(file_in,"%d%d%d",&cr,&cg,&cb)!=3){printf("error in reading file.\n");getchar();exit(0);}
				fscanf_s(file_in,"%d%d%d",&cr,&cg,&cb);
				*image_++=cr; *image_++=cg; *image_++=cb; 
			}
			break;
		case 9:
			fgets(str_tmp,100,file_in);
			nrc=atoi(str_tmp);
			fscanf_s(file_in,"%d\n",&nrc);
			if(nr_channel!=NULL) (*nr_channel)=nrc;
			fgets(str_tmp,100,file_in);
			imax=atoi(str_tmp);
			fread(image,sizeof(char),h*w*nrc,file_in);
			break;
		default:
			printf("Can not open image [%s]!!\n",filename);
			break;					
	}
	fclose(file_in);
	return (0);
}
int qx_loadimage(char* filename,float*image,int h,int w,int *nr_channel)
{
	FILE * file_in; int is_ppm; int nrc;
	char line[LEN_MAX];
	int	i; float imax; int hi,wi;	
	is_ppm=QX_DEF_IS_PGM;
	fopen_s(&file_in,filename,"rb");
	if(!file_in)
	{
		printf("Please check input filename: %s\n",filename);
		exit(0);
	}
	if(fgetc(file_in)=='P') 
		fscanf_s(file_in,"%d\n",&i);
	else
	{
		printf("Bad	header in ppm file.\n");
		exit(1);
	}
	while(fgets(line,LEN_MAX,file_in)!=NULL)
	{
		if(line[0]=='#') continue;
		else
		{	
			sscanf_s(line, "%d %d\n",&wi,&hi);
			break;
		}
	}
	char str_tmp[100];
	switch (i)
	{
		case 7:
			fgets(str_tmp,100,file_in);
			imax=atoi(str_tmp);
			if(nr_channel!=NULL) (*nr_channel)=1;
			memset(image,0,sizeof(float)*h*w);
			fread(image,sizeof(float),h*w,file_in);
			is_ppm=QX_DEF_IS_PGM;
			break;
		case 8:
			fgets(str_tmp,100,file_in);
			imax=atoi(str_tmp);
			if(nr_channel!=NULL) (*nr_channel)=3;
			memset(image,0,sizeof(float)*h*w*3);
			fread(image,sizeof(float),h*w*3,file_in);
			is_ppm=QX_DEF_IS_PPM;
			break;
		case 9:
			fgets(str_tmp,100,file_in);
			nrc=atoi(str_tmp);
			if(nr_channel!=NULL) (*nr_channel)=nrc;
			fgets(str_tmp,100,file_in);
			imax=atoi(str_tmp);
			fread(image,sizeof(float),h*w*nrc,file_in);
			is_ppm=QX_DEF_IS_PPM;
			break;
		default:
			break;					
	}
	fclose(file_in);
	return (is_ppm);
}
int qx_loadimage(char* filename,short*image,int h,int w,int *nr_channel)
{
	FILE * file_in; int is_ppm; int nrc;
	char line[LEN_MAX];
	int	i; float imax; int hi,wi;	
	is_ppm=QX_DEF_IS_PGM;
	fopen_s(&file_in,filename,"rb");
	if(!file_in)
	{
		printf("Please check input filename: %s\n",filename);
		exit(0);
	}
	if(fgetc(file_in)=='P') 
		fscanf_s(file_in,"%d\n",&i);
	else
	{
		printf("Bad	header in ppm file.\n");
		exit(1);
	}
	while(fgets(line,LEN_MAX,file_in)!=NULL)
	{
		if(line[0]=='#') continue;
		else
		{	
			sscanf_s(line, "%d %d\n",&wi,&hi);
			break;
		}
	}
	char str_tmp[100];
	switch (i)
	{
		case 7:
			fgets(str_tmp,100,file_in);
			imax=atoi(str_tmp);
			if(nr_channel!=NULL) (*nr_channel)=1;
			memset(image,0,sizeof(short)*h*w);
			fread(image,sizeof(short),h*w,file_in);
			is_ppm=QX_DEF_IS_PGM;
			break;
		case 8:
			fgets(str_tmp,100,file_in);
			imax=atoi(str_tmp);
			if(nr_channel!=NULL) (*nr_channel)=3;
			memset(image,0,sizeof(short)*h*w*3);
			fread(image,sizeof(short),h*w*3,file_in);
			is_ppm=QX_DEF_IS_PPM;
			break;
		case 9:
			fgets(str_tmp,100,file_in);
			nrc=atoi(str_tmp);
			if(nr_channel!=NULL) (*nr_channel)=nrc;
			fgets(str_tmp,100,file_in);
			imax=atoi(str_tmp);
			fread(image,sizeof(short),h*w*nrc,file_in);
			is_ppm=QX_DEF_IS_PPM;
			break;
		default:
			break;					
	}
	fclose(file_in);
	return (is_ppm);
}
/*P2(PGM ASCII format), P3(is_ppm ASCII format), P5 (PGM Binary format), P6 (is_ppm Binary format)*/
unsigned char* loadimage(char* filename, int &h, int &w, bool &is_ppm)
{
	FILE * file_in;
	char line[LEN_MAX];
	int	i,imax;	
	unsigned char *image=NULL;
	//file_in=fopen(filename,"rb");
	fopen_s(&file_in,filename,"rb");
	if(!file_in)
	{
		printf("Please check input filename: %s\n",filename);
		getchar();
		exit(0);
	}
	if(fgetc(file_in)=='P') 
		//fscanf(file_in,"%d\n",&i);
		fscanf_s(file_in,"%d\n",&i);
	else
	{ 
		printf("Bad	header in ppm file.\n");
		getchar();
		exit(1);
	}
	while(fgets(line,LEN_MAX,file_in)!=NULL)
	{
		if(line[0]=='#') continue;
		else
		{	
			//sscanf(line, "%d %d\n",	&w,	&h);
			sscanf_s(line, "%d %d\n",	&w,	&h);
			break;
		}
	}
	//fscanf(file_in, "%d\n", &imax);
	fscanf_s(file_in, "%d\n", &imax);
	switch (i)
	{
		case 2:
			image=get_ascii_pgm(file_in,w,h);
			is_ppm= QX_DEF_IS_PGM;
			break;
		case 3:
			image=get_ascii_ppm(file_in,w,h);
			is_ppm= QX_DEF_IS_PPM;
			break;
		case 5:
			image=get_binary_pgm(file_in,w,h);
			is_ppm= QX_DEF_IS_PGM;
			break;
		case 6:
			image=get_binary_ppm(file_in,w,h);
			is_ppm= QX_DEF_IS_PPM;
			break;
		default:
			break;					
	}
	fclose(file_in);
	return image;
}
int loadimage(unsigned char* out,char* filename, int h_in, int w_in)
{	
	FILE * file_in;
	char line[LEN_MAX];
	int	i,imax,h,w;
	//file_in=fopen(filename,"rb");
	fopen_s(&file_in,filename,"rb");
	if(!file_in)
	{
		printf("Please check input filename: %s\n",filename);
		getchar();
		return(-1);
	}
	if(fgetc(file_in)=='P') 
		//fscanf(file_in,"%d\n",&i);
		fscanf_s(file_in,"%d\n",&i);
	else
	{ 
		printf("Bad	header in ppm file.\n");
		getchar();
		return(-1);
	}
	while(fgets(line,LEN_MAX,file_in)!=NULL)
	{
		if(line[0]=='#') continue;
		else
		{	
			//sscanf(line, "%d %d\n",	&w,	&h);
			sscanf_s(line, "%d %d\n",	&w,	&h);
			break;
		}
	}
	if(h!=h_in||w!=w_in)
	{
		printf("The allocated memory for the image is not correct!! It should be [%dx%d].\n",h,w);
		getchar();
		return(-1);
	}
	//fscanf(file_in, "%d\n", &imax);
	fscanf_s(file_in, "%d\n", &imax);
	switch (i)
	{
		case 2:
			get_ascii_pgm(out,file_in,w,h);
			break;
		case 3:
			get_ascii_ppm(out,file_in,w,h);
			break;
		case 5:
			fread(out,sizeof(unsigned char),w*h,file_in);
			break;
		case 6:
			fread(out,sizeof(unsigned char),h*w*3,file_in);
			break;
		default:
			break;					
	}
	fclose(file_in);
	return(0);
}
int loadimage(float* out,unsigned char *out_u,char* filename, int h_in, int w_in)
{	
	FILE * file_in;
	char line[LEN_MAX];
	int	i,imax,h,w;
	//file_in=fopen(filename,"rb");
	fopen_s(&file_in,filename,"rb");
	if(!file_in)
	{
		printf("Please check input filename: %s\n",filename);
		getchar();
		return(-1);
	}
	if(fgetc(file_in)=='P') 
		//fscanf(file_in,"%d\n",&i);
		fscanf_s(file_in,"%d\n",&i);
	else
	{ 
		printf("Bad	header in ppm file.\n");
		getchar();
		return(-1);
	}
	while(fgets(line,LEN_MAX,file_in)!=NULL)
	{
		if(line[0]=='#') continue;
		else
		{	
			//sscanf(line, "%d %d\n",	&w,	&h);
			sscanf_s(line, "%d %d\n",	&w,	&h);
			break;
		}
	}
	if(h!=h_in||w!=w_in)
	{
		printf("The allocated memory for the image is not correct!! It should be [%dx%d].\n",h,w);
		getchar();
		return(-1);
	}
	//fscanf(file_in, "%d\n", &imax);
	fscanf_s(file_in, "%d\n", &imax);
	switch (i)
	{
		case 2:
			get_ascii_pgm(out_u,file_in,w,h);
			for(i=0;i<h_in*w_in;i++) out[i]=(float)out_u[i];
			break;
		case 3:
			get_ascii_ppm(out_u,file_in,w,h);
			for(i=0;i<h_in*w_in*3;i++) out[i]=(float)out_u[i];
			break;
		case 5:
			fread(out_u,sizeof(unsigned char),w*h,file_in);
			for(i=0;i<h_in*w_in;i++) out[i]=(float)out_u[i];
			break;
		case 6:
			fread(out_u,sizeof(unsigned char),h*w*3,file_in);
			for(i=0;i<h_in*w_in*3;i++) 
				out[i]=(float)out_u[i];
			break;
		default:
			break;
	}	
	fclose(file_in);
	return(0);
}
unsigned char* get_binary_ppm(FILE* in,int h,int w)
{	
	unsigned char *out=	NULL;
	out=(unsigned char*)malloc(h*w*3);	
	fread(out,sizeof(unsigned char),h*w*3,in);
	return out;
}
unsigned char* get_binary_pgm(FILE* file_in,int h,int w)
{
	unsigned char *image=NULL;
	image=(unsigned char*)malloc(w*h); 
	fread(image,sizeof(unsigned char),w*h,file_in);
	return image;
}
unsigned char* get_ascii_ppm(FILE* file_in,int h,int w)
{
	unsigned char *image=NULL; int	y,x; int	color_r,color_g,color_b;
	image=(unsigned char*)malloc(w*h*3);
	unsigned char *imagep=image;
	for	(y=0;y<h;y++) for	(x=0;x<w;x++)
	{
		//if(fscanf(file_in,"%d%d%d",&color_r,&color_g,&color_b)!=3)
		if(fscanf_s(file_in,"%d%d%d",&color_r,&color_g,&color_b)!=3)
		{
			printf("error in reading file.\n");
		getchar();
			exit(0);
		}
		//image[(y*w+x)*3]=(unsigned char)color_r;
		//image[(y*w+x)*3+1]=(unsigned char)color_g;
		//image[(y*w+x)*3+2]=(unsigned char)color_b;
		*imagep++=(unsigned char)color_r;
		*imagep++=(unsigned char)color_g;
		*imagep++=(unsigned char)color_b;
	}
	return image;
}
unsigned char* get_ascii_pgm(FILE* file_in,int h,int w)
{
	unsigned char *image=NULL;
	int	y,x,lum;
	image=(unsigned char*)malloc(w*h); 
	for	(y=0;y<h;y++) for(x=0;x<w;x++)
	{
		//if(fscanf(file_in,"%d",&lum)!=1)
		if(fscanf_s(file_in,"%d",&lum)!=1)
		{
			printf("error in reading file.\n");
		getchar();
			exit(0);
		}
		image[y*w+x]=(unsigned char)lum;
	}
	return image;
}
void get_ascii_ppm(unsigned char *image,FILE* file_in,int h,int w)
{
	int	y,x; int color_r,color_g,color_b;
	for	(y=0;y<h;y++) for (x=0;x<w;x++)
	{
		//if(fscanf(file_in,"%d%d%d",&color_r,&color_g,&color_b)!=3)
		//if(fscanf_s(file_in,"%d%d%d",&color_r,&color_g,&color_b)!=3)
		//{
		//	printf("error in reading file.\n");
		//	getchar();
		//	exit(0);
		//}
		//image[(y*w+x)*3]=(unsigned char)color_r;
		//image[(y*w+x)*3+1]=(unsigned char)color_g;
		//image[(y*w+x)*3+2]=(unsigned char)color_b;
		fscanf_s(file_in,"%d%d%d",&color_r,&color_g,&color_b);
		*image++=(unsigned char)color_r;
		*image++=(unsigned char)color_g;
		*image++=(unsigned char)color_b;
	}
}
void get_ascii_pgm(unsigned char *image,FILE* file_in,int h,int w)
{
	int	y,x,lum;
	for	(y=0;y<h;y++) for(x=0;x<w;x++)
	{
		//if(fscanf(file_in,"%d",&lum)!=1)
		if(fscanf_s(file_in,"%d",&lum)!=1)
		{
			printf("error in reading file.\n");
			getchar();
			exit(0);
		}
		image[y*w+x]=(unsigned char)lum;
	}
}
//void saveimage_ppm(char *filename,unsigned char *image,int h,int w,bool is_binary)
//{
//	if(is_binary==true) write_ascii_ppm(filename,image,h,w);
//	else write_ascii_ppm(filename,image,h,w);
//}
//void saveimage_pgm(char *filename,unsigned char *image,int h,int w,bool is_binary)
//{
//	if(is_binary==true) write_binary_pgm(filename,image,h,w);
//	else write_ascii_pgm(filename,image,h,w);
//}
void write_binary_ppm(char* filename,unsigned char *in,int h,int w)
{	
	FILE * file_out;
	//file_out=fopen(filename,"wb");
	fopen_s(&file_out,filename,"wb");
	fprintf(file_out,"P6\n%d %d\n%d\n",w,h,255);
	fwrite(in,sizeof(unsigned char),h*w*3,file_out);
	fclose(file_out);
}
void write_binary_pgm(char* filename,unsigned char *image,int h,int w)
{	
	FILE* file_out;
	//file_out=fopen(filename,"wb");
	fopen_s(&file_out,filename,"wb");
	if(file_out==NULL)
	{
		printf("Can't open the file %s, exit!\n",filename);
		getchar();
		exit(0);
	}
	fprintf(file_out,"P5\n%d %d\n%d\n",w,h,255);
	fwrite(image,sizeof(unsigned char),w*h,file_out);
	fclose(file_out);
}
void write_ascii_ppm(char* filename,unsigned char *image,int h,int w)
{	
	FILE* file_out; int y,x;
	//file_out=fopen(filename,"w");
	fopen_s(&file_out,filename,"w");
	fprintf(file_out,"P3\n%d %d\n%d\n",w,h,255);
	for (y=0;y<h;y++)
	{	
		for(x=0;x<w;x++)
		{
			fprintf(file_out, "%d", image[(y*w+x)*3+0]);
			fprintf(file_out, "%c",' ');
			fprintf(file_out, "%d", image[(y*w+x)*3+1]);
			fprintf(file_out, "%c",' ');
			fprintf(file_out, "%d", image[(y*w+x)*3+2]);
			fprintf(file_out, "%c",' ');
		}
	}
	fclose(file_out);
}
void write_ascii_pgm(char* filename,unsigned char *image,int h,int w)
{	
	FILE* file_out; int y,x;
	//file_out=fopen(filename,"w");
	fopen_s(&file_out,filename,"w");
	fprintf(file_out,"P2\n%d %d\n%d\n",w,h,255);
	for (y=0;y<h;y++)
	{	
		for(x=0;x<w;x++)
		{
			fprintf(file_out, "%d", image[y*w+x]);	
			fprintf(file_out, "%c",' ');
		}
	}
	fclose(file_out);
}
/*extended function*/
int qx_image_size(char* filename, int &h, int &w)
{
	FILE * file_in; int nr_channel;
	char line[LEN_MAX];
	int	p_idx;	
	unsigned char *image=NULL;
	//file_in=fopen(filename,"rb");
	fopen_s(&file_in,filename,"rb");
	if(!file_in)
	{
		printf("Please check input filename: %s\n",filename);
		getchar();
		exit(0);
	}
	if(fgetc(file_in)=='P') 
		//fscanf(file_in,"%d\n",&p_idx);
		fscanf_s(file_in,"%d\n",&p_idx);
	else
	{ 
		printf("Bad	header in ppm file.\n");
		getchar();
		exit(1);
	}
	while(fgets(line,LEN_MAX,file_in)!=NULL)
	{
		if(line[0]=='#') continue;
		else
		{
			sscanf_s(line, "%d %d\n",	&w,	&h);
			if(p_idx==9) 
			{
				fscanf_s(file_in,"%d\n",&nr_channel);
			}
			else if(p_idx==5||p_idx==2||p_idx==7) nr_channel=1;
			else if(p_idx==6||p_idx==3||p_idx==8) nr_channel=3;
			break;
		}
	}
	fclose(file_in);
	return(nr_channel);
}
float qx_image_max_value(char* filename)
{
	FILE * file_in; int h,w; 
	char line[LEN_MAX];
	int	p_idx;	
	unsigned char *image=NULL;
	//file_in=fopen(filename,"rb");
	fopen_s(&file_in,filename,"rb");
	if(!file_in)
	{
		printf("Please check input filename: %s\n",filename);
		getchar();
		exit(0);
	}
	if(fgetc(file_in)=='P') 
		//fscanf(file_in,"%d\n",&p_idx);
		fscanf_s(file_in,"%d\n",&p_idx);
	else
	{ 
		printf("Bad	header in ppm file.\n");
		getchar();
		exit(1);
	}
	char str_tmp[100];
	while(fgets(line,LEN_MAX,file_in)!=NULL)
	{
		if(line[0]=='#') continue;
		else
		{
			sscanf_s(line, "%d %d\n",	&w,	&h);
			fgets(str_tmp,100,file_in);
			if(p_idx==9) 
			{
				fgets(str_tmp,100,file_in);
			}
			break;
		}
	}
	fclose(file_in);
	return(atof(str_tmp));
}
unsigned char* verticalflip(int	width,int imageHeight,unsigned char* pixel)
{
	unsigned char *textureFlip=	NULL;
	int	y,x;
	textureFlip=(unsigned char*)malloc(width*imageHeight *	3);	
	for	(y=0;y<imageHeight;y++)
		for(x=0;x<width;x++)
		{
			textureFlip[(y*width+x)*3]	 =pixel[((imageHeight-y-1)*width+x)*3];
			textureFlip[(y*width+x)*3+1]=pixel[((imageHeight-y-1)*width+x)*3+1];
			textureFlip[(y*width+x)*3+2]=pixel[((imageHeight-y-1)*width+x)*3+2];
		}
	free(pixel);
	return textureFlip;
}
float ** loadimage_pgm(char *filename,int &h,int &w)
{
	float ** image_2d; unsigned char* image; bool is_ppm; int y,x,counter; 
	is_ppm=QX_DEF_IS_PPM; counter=0;
	image=loadimage(filename,h,w,is_ppm);
	image_2d=qx_allocf(h,w);
	if (is_ppm==QX_DEF_IS_PPM)
	{
		for (y=0;y<h;y++) for (x=0;x<w;x++)
		{
			image_2d[y][x]=(0.299F)*float(int(image[counter]))+(0.587F)*float(int(image[counter+1]))+(0.114F)*float(int(image[counter+2]));
			counter=counter+3;
		}
	}
	else
	{
		for(y=0;y<h;y++) for(x=0;x<w;x++)
			image_2d[y][x]=float(int(image[counter++]));
	}
	free(image);
	return image_2d;
}
float *** loadimage_ppm(char *filename,int &h,int &w)
{
	float *** image_3d; unsigned char* image; bool is_ppm; int y,x,k,counter;
	is_ppm=QX_DEF_IS_PPM; counter=0;
	image=loadimage(filename,h,w,is_ppm);
	image_3d=qx_allocf_3(h,w,3);
	for (y=0;y<h;y++) for(x=0;x<w;x++)
		for (k=0;k<3;k++) image_3d[y][x][k]=float(int(image[counter++]));
	free(image);
	return image_3d;
}
unsigned char *** loadimage_ppm_u(char *filename, int &h, int &w)
{
	unsigned char *** image_3d; unsigned char* image; bool is_ppm; int y,x,k,counter;
	is_ppm=QX_DEF_IS_PPM; counter=0;
	image=loadimage(filename,h,w,is_ppm);
	image_3d=qx_allocu_3(h,w,3);
	for (y=0;y<h;y++) for (x=0;x<w;x++) for(k=0;k<3;k++)
		image_3d[y][x][k]=image[counter++];
	free(image);
	return image_3d;
}
unsigned char **loadimage_pgm_u(char *filename, int &h, int &w)
{
	unsigned char ** image_2d; unsigned char* image; bool is_ppm; int y,x,counter; double lum;
	is_ppm=QX_DEF_IS_PPM; counter=0;
	image=loadimage(filename,h,w,is_ppm);
	image_2d=qx_allocu(h,w);
	if (is_ppm==QX_DEF_IS_PPM)
	{
		for(y=0;y<h;y++) for(x=0;x<w;x++)
		{
			lum=0.299*double(image[counter])+0.587*double(image[counter+1])+0.114*double(image[counter+2]);
			image_2d[y][x]= unsigned char(lum+0.5);
			counter= counter+3;
		}
	}
	else
	{
		for(y=0;y<h;y++) for(x=0;x<w;x++)
			image_2d[y][x]=image[counter++];
	}
	free(image);
	return image_2d;
}

int **loadimage_pgm_i(char *filename,int &h,int &w)
{
	int **image; unsigned char **image_2d; int y,x;
	image_2d=loadimage_pgm_u(filename,h,w);
	image=qx_alloci(h,w);
	for(y=0;y<h;y++) for(x=0;x<w;x++) 
		image[y][x]=(int)image_2d[y][x];
    qx_freeu(image_2d);
	return image;
}
void saveimage_pgm(char *filename,float **image,int h,int w,int scale)
{
	unsigned char *image_u; int counter,y,x;
	counter=0;
	image_u= new unsigned char [h*w];
	for(y=0;y<h;y++) for(x=0;x<w;x++) 
		image_u[counter++]=unsigned char(image[y][x]*scale+0.5f);
	write_binary_pgm(filename,image_u,h,w);
	delete image_u;
}
void saveimage_pgm_ascii(char *filename,float **image,int h,int w,int scale)
{
	unsigned char *image_u; int counter,y,x;
	counter=0;
	image_u= new unsigned char [h*w];
	for(y=0;y<h;y++) for(x=0;x<w;x++) 
		image_u[counter++]=unsigned char(image[y][x]*scale+0.5f);
	write_ascii_pgm(filename,image_u,h,w);
	delete image_u;
}
void saveimage_pgm_ascii(char *filename,int **image,int h,int w,int scale)
{
	unsigned char *image_u; int counter,y,x;
	counter=0;
	image_u= new unsigned char [h*w];
	for (y=0;y<h;y++) for(x=0;x<w;x++)
		image_u[counter++]= unsigned char(image[y][x]*scale);
	write_ascii_pgm(filename,image_u,h,w);
	delete image_u;
}
void saveimage_pgm(char *filename,unsigned char **image,int h,int w,int scale)
{
	unsigned char *image_u; int counter,y,x;
	counter=0;
	image_u=new unsigned char [h*w];
	for (y=0;y<h;y++) for(x=0;x<w;x++)
		image_u[counter++]=image[y][x]*scale;
	write_binary_pgm(filename,image_u,h,w);
	delete image_u;
}
void saveimage_pgm(char *filename,int **image,int h,int w,int scale)
{
	unsigned char *image_u; int counter,y,x;
	counter=0;
	image_u= new unsigned char [h*w];
	for (y=0;y<h;y++) for(x=0;x<w;x++)
		image_u[counter++]= unsigned char(image[y][x]*scale+0.5f);
	write_binary_pgm(filename,image_u,h,w);
	delete image_u;
}
void saveimage_pgm(char *filename,short**image,int h,int w,int scale)
{
	unsigned char *image_u; int counter,y,x;
	counter=0;
	image_u= new unsigned char [h*w];
	for (y=0;y<h;y++) for(x=0;x<w;x++)
		image_u[counter++]= unsigned char(image[y][x]*scale+0.5f);
	write_binary_pgm(filename,image_u,h,w);
	delete image_u;
}
void saveimage_pgm(char *filename,short*image,int h,int w,int scale)
{
	unsigned char *image_u; int counter,y,x;
	counter=0;
	image_u= new unsigned char [h*w];
	for (y=0;y<h;y++) for(x=0;x<w;x++)
		image_u[counter++]= unsigned char(image[y*w+x]*scale+0.5f);
	write_binary_pgm(filename,image_u,h,w);
	delete image_u;
}
void saveimage_ppm(char *filename,float ***image,int h,int w,int scale)
{
	int len=h*w*3; float *image_=image[0][0];
	unsigned char *in=new unsigned char[len];
	for(int i=0;i<len;i++)
		in[i]=(unsigned char)(image_[i]*scale);
	write_ascii_ppm(filename,in,h,w);
	delete [] in;
}
void saveimage_ppm(char *filename,double ***image,int h,int w,int scale)
{
	int len=h*w*3; double *image_=image[0][0];
	unsigned char *in=new unsigned char[len];
	for(int i=0;i<len;i++)
		in[i]=(unsigned char)(image_[i]*scale);
	write_ascii_ppm(filename,in,h,w);
	delete [] in;
}
void saveimage_ppm(char *filename,unsigned char ***image,int h,int w,int scale)
{
	write_ascii_ppm(filename,image[0][0],h,w);
}
float ***loadimage_ftif(char *filename,int &h,int &w,int &nr_channel)
{
	FILE* file_in;
	if(fopen_s(&file_in,filename,"r")!=0)
	{
		printf("Please check input filename: %s\n",filename);
		exit(0);
	}
	float ***image=NULL; int y,x,c; float color;
	if(fscanf_s(file_in,"%d%d%d",&h,&w,&nr_channel)!=3)
	{
		printf("error in reading file.\n");
		getchar();
		exit(0);
	}
	image=qx_allocf_3(h,w,nr_channel);
	for(y=0;y<h;y++) for(x=0;x<w;x++) for(c=0;c<nr_channel;c++)
	{
		fscanf_s(file_in,"%f",&color);
		image[0][0][(y*w+x)*nr_channel+c]=color;
	}
	fclose(file_in);
	return(image);
}
