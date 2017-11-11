/*$Id: basic.cpp,v 1.43 2007/04/04 02:15:14 liiton Exp $*/
#include "basic.h"
#include <windows.h>//The win32 API library 
#include "stdafx.h"
//#include <imdebug.h>
double qx_rand(int &s)
{
	int a;
	a =     s/127773;
	s =     16807*(s-a*127773)-2836*a;
	if(s<0) { s+=2147483647; }
	return( (1.0/((double)2147483647))*s );
}
double qx_rand(int &s,double dmin,double dmax)
{
	return((dmax-dmin)*qx_rand(s)+dmin);
}
double qx_randc(int &s) { return(2*qx_rand(s)-1); }

void qx_rand_reorder(int*index,int len_out,int len_in,int &seed)
{
	for(int i=0;i<len_in;i++) index[i]=i;
	for(int i=0;i<len_out;i++)
	{
		int len_i=(len_in-1-i);
		int selected=int(qx_rand(seed)*len_i+0.5)+i;
		int index_i=index[i];
		index[i]=index[selected];
		index[selected]=index_i;
	}
}
void qx_rand_reorder(int*index,int len_out,int len_in)
{
	int seed=QX_DEF_SEED;
	qx_rand_reorder(index,len_out,len_in,seed);
}
void qx_compute_random_color(unsigned char**color,int nr_feature,int &seed)
{
	for(int i=0;i<nr_feature;i++) qx_compute_random_color(color[i],seed);
}
void qx_rand8_init(unsigned char *in)
{
    int s=QX_DEF_SEED; unsigned char pi,pj,tt;
    for(int i=0;i<256;i++) in[i]=i;
    for(int i=0;i<256;i++)
    {
        pi=unsigned char(qx_rand(s)*255+0.5);
        for(int j=0;j<256;j++)
        {
            pj=unsigned char(qx_rand(s)*255+0.5);
            tt=in[pi];
            in[pi]=in[pj];
            in[pj]=tt;
        }
    }
}
void qx_gaussian_2d(double **gaussian,int h,int w,int &s)
{
	int i, j;	
	double fac, rsq, v1, v2;
	for (i= 0; i< h; i++)
	{
		for (j=0; j< w; j++)
		{
			v1     = qx_randc(s);
			v2     = qx_randc(s);
			rsq    = v1*v1 + v2*v2;
			while ( (rsq >= 1.0) || (rsq ==0.0) )
			{
				v1 = qx_randc(s);
				v2 = qx_randc(s);
				rsq= v1*v1 + v2*v2;
			}
			fac    = sqrt(-2.0*log(rsq)/rsq);
			gaussian[i][j]= v1*fac;
		}
	}	
}
void qx_gaussian_2d(float **gaussian,int h,int w,int &s)
{
	int i, j;	
	float fac, rsq, v1, v2;
	for (i= 0; i< h; i++)
	{
		for (j=0; j< w; j++)
		{
			v1     = (float)qx_randc(s);
			v2     = (float)qx_randc(s);
			rsq    = v1*v1 + v2*v2;
			while ( (rsq >= 1.0) || (rsq ==0.0) )
			{
				v1 = (float)qx_randc(s);
				v2 = (float)qx_randc(s);
				rsq= v1*v1 + v2*v2;
			}
			fac    = sqrt(-2.0f*log(rsq)/rsq);
			gaussian[i][j]= v1*fac;
		}
	}	
} 
void qx_gaussian_2d(float **gaussian,int h,int w,int &s,float scale)
{
	int i, j;	
	float fac, rsq, v1, v2;
	for (i= 0; i< h; i++)
	{
		for (j=0; j< w; j++)
		{
			v1     = (float)qx_randc(s);
			v2     = (float)qx_randc(s);
			rsq    = v1*v1 + v2*v2;
			while ( (rsq >= 1.0) || (rsq ==0.0) )
			{
				v1 = (float)qx_randc(s);
				v2 = (float)qx_randc(s);
				rsq= v1*v1 + v2*v2;
			}
			fac    = sqrt(-2.0f*log(rsq)/rsq);
			if(qx_randc(s)>0) gaussian[i][j]=v1*fac*scale;
			else gaussian[i][j]=-v1*fac*scale;
		}
	}	
}
//int get_nr_file(char *file_folder,char *file_format,bool display_files)
//{	
//	int nr_file=0;
//	struct _finddata_t pgm_file;
//	intptr_t hFile;
//	_chdir(file_folder);
//	if((hFile=_findfirst(file_format,&pgm_file))!=-1)
//	{
//		if(display_files) printf("%s\n",pgm_file.name);
//		nr_file++;
//		while(_findnext(hFile,&pgm_file)==0)
//		{
//			if(display_files) printf("%s\n",pgm_file.name);
//			nr_file++;
//		}
//	}
//	_findclose(hFile);
//	return(nr_file);
//}
//int get_files(char **files,char *file_folder,char *file_format,int str_length)
//{	
//	int nr_file=0;
//	struct _finddata_t pgm_file;
//	//long hFile;
//	intptr_t hFile;
//	_chdir(file_folder);
//	if((hFile=_findfirst(file_format,&pgm_file))!=-1)
//	{
//		sprintf_s(files[nr_file++],str_length,"%s",pgm_file.name);
//		while(_findnext(hFile,&pgm_file)==0)
//		{
//			//printf("%s\n",pgm_file.name);
//			//nr_file++;
//			sprintf_s(files[nr_file++],str_length,"%s",pgm_file.name);
//		}
//	}
//	_findclose(hFile);
//	return(nr_file);
//}
//void file_create(char *file_path)
//{
//	FILE * file_in;
//	//file_in= fopen(file_path, "w+");
//	fopen_s(&file_in,file_path, "w+");
//	fclose(file_in);
//}
//int file_open(char *file_path,char *out,int len)
//{
//	FILE * file_in;
//	//file_in= fopen(file_path, "rb");
//	fopen_s(&file_in,file_path, "rb");
//	if(file_in==NULL)
//	{
//		printf("(file open)The file %s does NOT EXIST!!\n",file_path);
//		return(-1);
//	}
//	fread(out,sizeof(char),len,file_in);
//	fclose(file_in);
//	return(0);
//}
//void file_save(char *file_path,char *out,int len)
//{
//	FILE * file_out;
//	//file_out= fopen(file_path, "wb");
//	fopen_s(&file_out,file_path, "wb");
//	if(file_out==NULL)
//	{
//		printf("(file save)The file %s does NOT EXIST!!\n",file_path);;
//		exit(1);
//	}
//	fwrite(out,sizeof(char),len,file_out);
//	fclose(file_out);
//}
//int file_open(char *file_path,unsigned char *out,int len)
//{
//	FILE * file_in;
//	//file_in= fopen(file_path, "rb");
//	fopen_s(&file_in,file_path, "rb");
//	if(file_in!=NULL)
//	{
//		fread(out,sizeof(unsigned char),len,file_in);
//		fclose(file_in);
//	}
//	else
//	{
//		printf("Can not open file: %s\n",file_path);
//		getchar();
//		return(-1);
//	}
//	return(0);
//}
//void file_save(char *file_path,unsigned char *out,int len)
//{
//	FILE * file_out;
//	fopen_s(&file_out,file_path, "wb");
//	fwrite(out,sizeof(unsigned char),len,file_out);
//	fclose(file_out);
//}
//int file_open(char *file_path,int *out,int len)
//{
//	FILE * file_in;
//	//file_in= fopen(file_path, "rb");
//	fopen_s(&file_in,file_path, "rb");
//	if(file_in!=NULL)
//	{
//		fread(out,sizeof(int),len,file_in);
//		fclose(file_in);
//	}
//	else
//	{
//		printf("Can not open file: %s\n",file_path);
//		getchar();
//		return(-1);
//	}
//	return(0);
//}
//void file_save(char *file_path,int *out,int len)
//{
//	FILE * file_out;
//	//file_out= fopen(file_path, "wb");
//	fopen_s(&file_out,file_path, "wb");
//	//for (int i=0; i<len; i++)    
//	//	fprintf(StreamSave,FormatStr,out[i]);	
//	fwrite(out,sizeof(int),len,file_out);
//	fclose(file_out);
//}
//int file_open(char *file_path,float *out,int len)
//{
//	FILE * file_in;
//	//file_in= fopen(file_path, "rb");
//	fopen_s(&file_in,file_path, "rb");
//	if(file_in!=NULL)
//	{
//		fread(out,sizeof(float),len,file_in);
//		fclose(file_in);
//	}
//	else
//	{
//		printf("Can not open file: %s\n",file_path);
//		getchar();
//		return(-1);
//	}
//	return(0);
//}
//void file_save(char *file_path,float *out,int len)
//{
//	FILE * file_out;
//	//file_out= fopen(file_path, "wb");
//	fopen_s(&file_out,file_path, "wb");
//	//for (int i=0; i<len; i++)    
//	//	fprintf(StreamSave,FormatStr,out[i]);	
//	fwrite(out,sizeof(float),len,file_out);
//	fclose(file_out);
//}
//int file_open(char *file_path,double *out,int len)
//{
//	FILE * file_in;
//	//file_in= fopen(file_path, "rb");
//	fopen_s(&file_in,file_path, "rb");
//	if(file_in!=NULL)
//	{
//		fread(out,sizeof(double),len,file_in);
//		fclose(file_in);
//	}
//	else
//	{
//		printf("Can not open file: %s\n",file_path);
//		getchar();
//		return(-1);
//	}
//	return(0);
//}
//void file_save(char *file_path,double *out,int len)
//{
//	FILE * file_out;
//	//file_out= fopen(file_path, "wb");
//	fopen_s(&file_out,file_path, "wb");
//	fwrite(out,sizeof(double),len,file_out);
//	fclose(file_out);
//}
//int file_open_ascii(char *file_path,int *out,int len)
//{
//	FILE *file_in; char str[65]; int i;
//	//file_in=fopen(file_path,"r");
//	fopen_s(&file_in,file_path,"r");
//	if(file_in!=NULL)
//	{
//		fseek(file_in,0,SEEK_SET);	
//		for(i=0;i<len;i++ )
//		{ 
//			//fscanf(file_in,"%s",str); 
//			fscanf_s(file_in,"%s",str,65); 
//			out[i]=atoi(str);
//		}
//		fclose(file_in);
//	}
//	else
//	{
//		printf("Can not open file: %s\n",file_path);
//		getchar();
//		return(-1);
//	}
//	return(0);
//}
//int file_open_ascii(char *file_path,unsigned char *out,int len)
//{
//	FILE *file_in; char str[65]; int i;
//	//file_in=fopen(file_path,"r");
//	fopen_s(&file_in,file_path,"r");
//	if(file_in!=NULL)
//	{
//		fseek(file_in,0,SEEK_SET);	
//		for(i=0;i<len;i++ )
//		{ 
//			//fscanf(file_in,"%s",str); 
//			fscanf_s(file_in,"%s",str,65); 
//			out[i]=atoi(str);
//		}
//		fclose(file_in);
//	}
//	else
//	{
//		printf("Can not open file: %s\n",file_path);
//		getchar();
//		return(-1);
//	}
//	return(0);
//}
//int file_open_ascii(char *file_path,double *out,int len)
//{
//	FILE *file_in; char str[65]; int i;
//	//file_in=fopen(file_path, "r");
//	fopen_s(&file_in,file_path,"r");
//	if(file_in!=NULL)
//	{
//		fseek(file_in,0,SEEK_SET);	
//		for(i=0;i<len;i++ )
//		{ 
//			//fscanf(file_in,"%s",str); 
//			fscanf_s(file_in,"%s",str,65); 
//			out[i]=atof(str);
//		}
//		fclose(file_in);
//	}
//	else
//	{
//		printf("Can not open file: %s\n",file_path);
//		getchar();
//		return(-1);
//	}
//	return(0);
//}
//int file_open_ascii(char *file_path,float *out,int len,int nr_escape)
//{
//	FILE * file_in; char str[65]; int i;
//	//file_in= fopen(file_path, "r");
//	fopen_s(&file_in,file_path,"r");
//	if(file_in!=NULL)
//	{
//		fseek(file_in, 0, SEEK_SET);
//		for(i=0;i<nr_escape;i++) 
//			//fscanf(file_in,"%s",str);
//			fscanf_s(file_in,"%s",str,65);
//		for(i=0;i<len;i++)
//		{ 
//			//fscanf(file_in,"%s",str); 
//			fscanf_s(file_in,"%s",str,65); 
//			out[i]=(float)atof(str);
//		}
//		fclose(file_in);
//	}
//	else
//	{
//		printf("Can not open file: %s\n",file_path);
//		getchar();
//		return(-1);
//	}
//	return(0);
//}
//void file_save_ascii(char *file_path,double *out,int len,char *str)
//{
//	FILE * fileout; int i;
//	//fileout= fopen(file_path,"w");
//	fopen_s(&fileout,file_path,"w");
//	for(i=0;i<len;i++)    
//	{	
//		if(str==NULL) fprintf(fileout,"%e ",out[i]);	
//		else fprintf(fileout,str,out[i]);	
//	}
//	fclose(fileout);
//}
//void file_save_ascii(char *file_path,float *out,int len)
//{
//	FILE * fileout; int i;
//	//fileout= fopen(file_path,"w");
//	fopen_s(&fileout,file_path,"w");
//	for(i=0;i<len;i++)    
//	{	
//		fprintf(fileout,"%f ",out[i]);	
//	}
//	fclose(fileout);
//}
//void file_save_ascii_2d(char *file_path,float **out,int h,int w)
//{
//	FILE * fileout; int y,x;
//	//fileout= fopen(file_path,"w");
//	fopen_s(&fileout,file_path,"w");
//	for(y=0;y<h;y++)
//	{	
//		for(x=0;x<w;x++)
//		{
//			fprintf(fileout,"%f ",out[y][x]);	
//		}
//		fprintf(fileout,"\n ");	
//	}
//	fclose(fileout);
//}
//void file_save_ascii_2d(char *file_path,double **out,int h,int w)
//{
//	FILE * fileout; int y,x;
//	//fileout= fopen(file_path,"w");
//	fopen_s(&fileout,file_path,"w");
//	for(y=0;y<h;y++)
//	{	
//		for(x=0;x<w;x++)
//		{
//			fprintf(fileout,"%f ",out[y][x]);	
//		}
//		fprintf(fileout,"\n ");	
//	}
//	fclose(fileout);
//}
//void file_save_ascii_2d(char *file_path,unsigned char **out,int h,int w)
//{
//	FILE * fileout; int y,x;
//	//fileout= fopen(file_path,"w");
//	fopen_s(&fileout,file_path,"w");
//	for(y=0;y<h;y++)
//	{	
//		for(x=0;x<w;x++)
//		{
//			fprintf(fileout,"%i ",out[y][x]);	
//		}
//		fprintf(fileout,"\n ");	
//	}
//	fclose(fileout);
//}
//void file_save_ascii_2d(char *file_path,int **out,int h,int w)
//{
//	FILE * fileout; int y,x;
//	//fileout= fopen(file_path,"w");
//	fopen_s(&fileout,file_path,"w");
//	for(y=0;y<h;y++)
//	{	
//		for(x=0;x<w;x++)
//		{
//			fprintf(fileout,"%i ",out[y][x]);	
//		}
//		fprintf(fileout,"\n ");	
//	}
//	fclose(fileout);
//}
//void file_save_ascii_2d(char *file_path,char **out,int h,int w)
//{
//	FILE * fileout; int y,x;
//	//fileout= fopen(file_path,"w");
//	fopen_s(&fileout,file_path,"w");
//	for(y=0;y<h;y++)
//	{	
//		for(x=0;x<w;x++)
//		{
//			fprintf(fileout,"%c",out[y][x]);	
//		}
//			fprintf(fileout,"\n");	
//	}
//	fclose(fileout);
//}
//int file_open_ascii_2d(char *file_path,char **out,int h,int w)
//{
//	FILE * file_in; int i;
//	//file_in= fopen(file_path, "r");
//	fopen_s(&file_in,file_path,"r");
//	if(file_in!=NULL)
//	{
//		fseek(file_in,0,SEEK_SET);
//		for(i=0;i<h;i++)
//		{ 
//			fscanf_s(file_in,"%s",out[i],w+1); 
//		}
//		fclose(file_in);
//	}
//	else
//	{
//		printf("Can not open file: %s\n",file_path);
//		getchar();
//		return(-1);
//	}
//	return(0);
//}
//void file_save_ascii(char *file_path,unsigned char *out,int len)
//{
//	FILE * fileout; int i;
//	//fileout= fopen(file_path,"w");
//	fopen_s(&fileout,file_path,"w");
//	for(i=0;i<len;i++)    
//	{	
//		fprintf(fileout,"%d ",out[i]);	
//	}
//	fclose(fileout);
//}
//void file_save_ascii(char *file_path,int *out,int len)
//{
//	FILE * fileout; int i;
//	//fileout= fopen(file_path,"w");
//	fopen_s(&fileout,file_path,"w");
//	for(i=0;i<len;i++)    
//	{	
//		fprintf(fileout,"%d ",out[i]);	
//	}
//	fclose(fileout);
//}
//void file_save_ascii(char *file_path,char *out)
//{
//	FILE * fileout; int i; int len;
//	//fileout= fopen(file_path,"w");
//	fopen_s(&fileout,file_path,"w");
//	len=(int)strlen(out);
//	for(i=0;i<len;i++)    
//	{	
//		fprintf(fileout,"%c",out[i]);	
//	}
//	fclose(fileout);
//}
//void save_ply(char* file_name,float **depth,float ***normal,unsigned char ***image,unsigned char **mask,int **index,int h,int w,float sx,float sy,float sz,int y0,int x0)
//{
//	FILE * stream; int y,x,nr_points,nr_faces,counter; int h1,w1;
//	//nr_points=h*w;
//	nr_points=nr_faces=0;
//	h1=h-1; w1=w-1;
//	if(x0<0||x0>=w) x0=(w>>1);
//	if(y0<0||y0>=h) y0=(h>>1);
//	for(y=0;y<h;y++)
//	{
//		for(x=0;x<w;x++)
//		{
//			if(mask[y][x])
//			{
//				nr_points++;
//				if(y<h1&&x<w1&&y>0&&x>0)
//				{
//					if(mask[y-1][x]&&mask[y][x-1]) nr_faces++;
//					if(mask[y+1][x]&&mask[y][x+1]) nr_faces++;
//				}
//			}
//		}
//	}
//	fopen_s(&stream,file_name,"w");
//	//*write header*/
//	fprintf(stream,"ply\n format ascii 1.0\n");
//	fprintf(stream,"comment Author: Qingxiong Yang (liiton)\n");
//	fprintf(stream,"element vertex %d\n",nr_points);
//	fprintf(stream,"property float x\n");
//	fprintf(stream,"property float y\n");
//	fprintf(stream,"property float z\n");
//	if(normal!=NULL)
//	{
//		fprintf(stream,"property float nx\n");
//		fprintf(stream,"property float ny\n");
//		fprintf(stream,"property float nz\n");
//	}
//	if(image!=NULL)
//	{
//		fprintf(stream,"property uchar red\n");
//		fprintf(stream,"property uchar green\n");
//		fprintf(stream,"property uchar blue\n");
//	}
//	fprintf(stream,"element face %d\n",nr_faces);
//	fprintf(stream,"property list uchar int vertex_indices\n");
//	fprintf(stream,"end_header\n");
//	//*write vertices*/
//	for(counter=0,y=0;y<h;y++)
//	{
//		for(x=0;x<w;x++)
//		{
//			if(mask[y][x])
//			{
//				index[y][x]=counter++;
//				fprintf(stream,"%f %f %f ",(x-x0)*sx,(y-y0)*sy,depth[0][y*w+x]*sz);
//				if(normal!=NULL)
//				{
//					fprintf(stream,"%f %f %f ",normal[y][x][0],normal[y][x][1],normal[y][x][2]);
//				}
//				if(image!=NULL)
//				{
//					fprintf(stream,"%d %d %d",image[y][x][0],image[y][x][1],image[y][x][2]);
//				}
//				fprintf(stream,"\n");
//			}
//		}
//	}
//	//*write faces*/
//	for(y=0;y<h;y++)
//	{
//		for(x=0;x<w;x++)
//		{
//			if(mask[y][x])
//			{
//				if(y<h1&&x<w1&&y>0&&x>0)
//				{
//					if(mask[y-1][x]&&mask[y][x-1])
//					{
//						fprintf(stream,"3 %d %d %d\n",index[y][x],index[y-1][x],index[y][x-1]);
//					}
//					if(mask[y+1][x]&&mask[y][x+1])
//					{
//						fprintf(stream,"3 %d %d %d\n",index[y][x],index[y+1][x],index[y][x+1]);
//					}
//				}
//			}
//		}
//	}
//}
//void save_ply(char* file_name,float **depth,float ***normal,unsigned char ***image,int h,int w,float sx,float sy,float sz,int y0,int x0)
//{
//	FILE * stream; int y,x,nr_points,nr_faces,counter; int h1,w1;
//	nr_points=h*w;
//	h1=h-1; w1=w-1;
//	nr_faces=2*h1*w1;
//	if(x0<0||x0>=w) x0=(w>>1);
//	if(y0<0||y0>=h) y0=(h>>1);
//
//	fopen_s(&stream,file_name,"w");
//	//*write header*/
//	fprintf(stream,"ply\nformat ascii 1.0\n");
//	fprintf(stream,"comment Author: Qingxiong Yang (liiton)\n");
//	fprintf(stream,"element vertex %d\n",nr_points);
//	fprintf(stream,"property float x\n");
//	fprintf(stream,"property float y\n");
//	fprintf(stream,"property float z\n");
//	if(normal!=NULL)
//	{
//		fprintf(stream,"property float nx\n");
//		fprintf(stream,"property float ny\n");
//		fprintf(stream,"property float nz\n");
//	}
//	if(image!=NULL)
//	{
//		fprintf(stream,"property uchar red\n");
//		fprintf(stream,"property uchar green\n");
//		fprintf(stream,"property uchar blue\n");
//	}
//	fprintf(stream,"element face %d\n",nr_faces);
//	fprintf(stream,"property list uchar int vertex_indices\n");
//	fprintf(stream,"end_header\n");
//	//*write vertices*/
//	counter=0;
//	for(y=0;y<h;y++)
//	{
//		for(x=0;x<w;x++)
//		{
//			fprintf(stream,"%5.5f %5.5f %5.5f ",(x-x0)*sx,(y-y0)*sy,depth[0][y*w+x]*sz);
//			if(normal!=NULL)
//			{
//				fprintf(stream,"%f %f %f ",normal[y][x][0],normal[y][x][1],normal[y][x][2]);
//			}
//			if(image!=NULL)
//			{
//				fprintf(stream,"%d %d %d",image[y][x][0],image[y][x][1],image[y][x][2]);
//			}
//			fprintf(stream,"\n");
//			counter++;
//		}
//	}
//	printf("counter: %d\n",counter);
//	//*write faces*/
//	counter=0;
//	for(y=0;y<h1;y++)
//	{
//		for(x=0;x<w1;x++)
//		{
//			int id1=y*w+x;
//			int id2=(y+1)*w+x+1;
//			fprintf(stream,"3 %d %d %d\n",id1,id1+1,id2-1);
//			fprintf(stream,"3 %d %d %d\n",id2,id2-1,id1+1);
//			counter+=2;
//		}
//	}
//	printf("counter: %d\n",counter);	
//}
//
//int save_iv(char* file_name,float **depth,unsigned char ***image,int h,int w,int point_size,float depth_scale)
//{
//	FILE * stream_iv; int y,x,nr_points;
//	nr_points=h*w;
//	//stream_iv=fopen(file_name,"w");
//	fopen_s(&stream_iv,file_name,"w");
//	fprintf(stream_iv,"#Inventor V2.1 ascii\n");
//	fprintf(stream_iv,"Separator\n{\n");
//	fprintf(stream_iv,"  DrawStyle\n  {\n");
//	fprintf(stream_iv,"    pointSize %d\n  }\n",point_size);
//	fprintf(stream_iv,"  Material\n  {\n");
//	fprintf(stream_iv,"    diffuseColor\n    [\n");
//	/*file in the color*/
//	if(image==NULL)
//	{
//		for(y=0;y<h;y++) for(x=0;x<w;x++)
//		{
//			fprintf(stream_iv,"        %2.5f %2.5f %2.5f ,\n",1.0f,1.0f,1.0f);
//		}
//	}
//	else
//	{
//		for(y=0;y<h;y++) for(x=0;x<w;x++)
//		{
//			fprintf(stream_iv,"        %3.5f %3.5f %3.5f ,\n",float(image[y][x][0])/255,float(image[y][x][1])/255,float(image[y][x][2])/255);
//		}
//	}
//	fprintf(stream_iv,"\n    ]\n  }\n  Coordinate3\n  {\n    point\n    [\n");
//	/*file in the coordinates*/
//	for(y=0;y<h;y++) for(x=0;x<w;x++)
//	{
//		fprintf(stream_iv,"        %5.5f %5.5f %5.5f ,\n",-float(x),-float(y),-depth[y][x]*depth_scale);	
//	}
//	fprintf(stream_iv,"\n    ]\n  }\n  MaterialBinding\n  {\n    value PER_VERTEX\n  }\n  PointSet\n  {\n    numPoints %d\n  }\n}\n",nr_points);
//	fclose(stream_iv);
//	return(0);
//}
//int save_iv(char* file_name,float **depth,unsigned char ***image,unsigned char **mask,int h,int w,int point_size,float depth_scale)
//{
//	FILE * stream_iv; int y,x,nr_points;
//	nr_points=0;
//	//stream_iv=fopen(file_name,"w");
//	fopen_s(&stream_iv,file_name,"w");
//	fprintf(stream_iv,"#Inventor V2.1 ascii\n");
//	fprintf(stream_iv,"Separator\n{\n");
//	fprintf(stream_iv,"  DrawStyle\n  {\n");
//	fprintf(stream_iv,"    pointSize %d\n  }\n",point_size);
//	fprintf(stream_iv,"  Material\n  {\n");
//	fprintf(stream_iv,"    diffuseColor\n    [\n");
//	/*file in the color*/
//	if(image==NULL)
//	{
//		for(y=0;y<h;y++) for(x=0;x<w;x++)
//		{
//			if(mask[y][x])
//			{
//				fprintf(stream_iv,"        %2.5f %2.5f %2.5f ,\n",1.0f,1.0f,1.0f);
//				nr_points++;
//			}
//		}
//	}
//	else
//	{
//		for(y=0;y<h;y++) for(x=0;x<w;x++)
//		{
//			if(mask[y][x])
//			{
//				fprintf(stream_iv,"        %3.5f %3.5f %3.5f ,\n",float(image[y][x][0])/255,float(image[y][x][1])/255,float(image[y][x][2])/255);
//				nr_points++;
//			}
//		}
//	}
//	fprintf(stream_iv,"\n    ]\n  }\n  Coordinate3\n  {\n    point\n    [\n");
//	/*file in the coordinates*/
//	for(y=0;y<h;y++) for(x=0;x<w;x++)
//	{
//		if(mask[y][x])
//		{
//			fprintf(stream_iv,"        %5.5f %5.5f %5.5f ,\n",-float(x),-float(y),-depth[y][x]*depth_scale);	
//		}
//	}
//	fprintf(stream_iv,"\n    ]\n  }\n  MaterialBinding\n  {\n    value PER_VERTEX\n  }\n  PointSet\n  {\n    numPoints %d\n  }\n}\n",nr_points);
//	fclose(stream_iv);
//	return(0);
//}
//
//int save_iv_triangles(char* file_name,float **depth,unsigned char ***image,unsigned char **mask,int h,int w,int point_size,float depth_scale,float xy_scale)
//{
//	FILE * stream_iv; int y,x,nr_points;
//	nr_points=0;
//	//stream_iv=fopen(file_name,"w");
//	fopen_s(&stream_iv,file_name,"w");
//	fprintf(stream_iv,"#Inventor V2.1 ascii\n");
//	fprintf(stream_iv,"Separator\n{\n");
//	fprintf(stream_iv,"  DrawStyle\n  {\n");
//	fprintf(stream_iv,"    pointSize %d\n  }\n",point_size);
//	fprintf(stream_iv,"  Material\n  {\n");
//	/*file in the color*/
//	fprintf(stream_iv,"    diffuseColor\n    [\n");
//	if(image==NULL)
//	{
//		for(y=0;y<h;y++) for(x=0;x<w;x++)
//			if(mask[y][x])
//			{
//				fprintf(stream_iv,"        %2.5f %2.5f %2.5f ,\n",1.0f,1.0f,1.0f);
//				nr_points++;
//			}
//	}
//	else
//	{
//		for(y=0;y<h;y++) for(x=0;x<w;x++)
//		{
//			if(mask[y][x])
//			{
//				fprintf(stream_iv,"        %2.5f %2.5f %2.5f ,\n",float(image[y][x][0])/255,float(image[y][x][1])/255,float(image[y][x][2])/255);
//				nr_points++;
//			}
//		}
//	}
//	fprintf(stream_iv,"\n    ]\n  }\n");
//
//	/*TextureCoordinate Bind*/
//	fprintf(stream_iv,"  TextureCoordinateBinding\n  {\n    value PER_VERTEX_INDEXED\n  }\n");
//	/*material Bind*/
//	fprintf(stream_iv,"  MaterialBinding\n  {\n    value PER_VERTEX_INDEXED\n  }\n");
//	/*ShapeHints*/
//	fprintf(stream_iv,"ShapeHints\n  {\n");
//	fprintf(stream_iv,"    vertexOrdering COUNTERCLOCKWISE\n");
//	fprintf(stream_iv,"    shapeType UNKNOWN_SHAPE_TYPE\n");
//	fprintf(stream_iv,"    faceType CONVEX\n");
//	fprintf(stream_iv,"    creaseAngle 6.28319\n");
//	fprintf(stream_iv,"  }\n");
//
//	/*file in the coordinates*/
//	fprintf(stream_iv,"  Coordinate3\n  {\n    point\n    [\n");
//	for(y=0;y<h;y++) for(x=0;x<w;x++)
//	{
//		if(mask[y][x])
//		{
//			fprintf(stream_iv,"        %2.5f %2.5f %2.5f ,\n",float(x)*xy_scale,-float(y)*xy_scale,-depth[y][x]*depth_scale);	
//		}
//	}
//	fprintf(stream_iv,"\n    ]\n  }\n");
//	/*draw triangles*/
//	fprintf(stream_iv,"  IndexedFaceSet\n  {\n");
//	fprintf(stream_iv,"    coordIndex\n    [\n");
//	for(y=0;y<h-1;y++) for(x=0;x<w-1;x++)
//	{	
//		if(mask[y][x])
//		{
//			fprintf(stream_iv,"        %d,%d,%d,%d,\n",((y+1)*w+x),(y*w+x+1),(y*w+x),-1);
//			fprintf(stream_iv,"        %d,%d,%d,%d,\n",((y+1)*w+x),((y+1)*w+x+1),(y*w+x+1),-1);
//		}
//	}
//	fprintf(stream_iv,"\n    ]\n");
//	//fprintf(stream_iv,"    materialIndex \n    [\n");
//	//for(y=0;y<h-1;y++) for(x=0;x<w-1;x++)
//	//{	
//	//	//fprintf(stream_iv,"        %d,%d,%d,%d,\n",((y+1)*w+x),(y*w+x+1),(y*w+x),-1);
//	//	//fprintf(stream_iv,"        %d,%d,%d,%d,\n",((y+1)*w+x),((y+1)*w+x+1),(y*w+x+1),-1);
//	//	fprintf(stream_iv,"        %d,%d,%d,%d,\n",y,y,y,-1);
//	//	fprintf(stream_iv,"        %d,%d,%d,%d,\n",y,y,y,-1);
//	//}
//	//fprintf(stream_iv,"\n    ]\n");
//
//
//	fprintf(stream_iv,"  }\n");
//
//	fprintf(stream_iv,"  PointSet\n  {\n    numPoints %d\n  }\n}\n",nr_points);
//	fclose(stream_iv);
//	return(0);
//}
//
//int save_iv(char* file_name,float **depth,unsigned char ***image,int ymin,int ymax,int xmin,int xmax,int point_size,float depth_scale)
//{
//	FILE * stream_iv; int y,x,nr_points;
//	
//	nr_points=(ymax-ymin+1)*(xmax-xmin+1);
//	//stream_iv=fopen(file_name,"w");
//	fopen_s(&stream_iv,file_name,"w");
//	fprintf(stream_iv,"#Inventor V2.1 ascii\n");
//	fprintf(stream_iv,"Separator\n{\n");
//	fprintf(stream_iv,"  DrawStyle\n  {\n");
//	fprintf(stream_iv,"    pointSize %d\n  }\n",point_size);
//	fprintf(stream_iv,"  Material\n  {\n");
//	fprintf(stream_iv,"    diffuseColor\n    [\n");
//	/*file in the color*/
//	if(image==NULL)
//	{
//		for(y=ymin;y<=ymax;y++) for(x=xmin;x<=xmax;x++)
//			fprintf(stream_iv,"        %2.5f %2.5f %2.5f ,\n",1.0f,1.0f,1.0f);
//	}
//	else
//	{
//		for(y=ymin;y<=ymax;y++) for(x=xmin;x<=xmax;x++)
//			fprintf(stream_iv,"        %2.5f %2.5f %2.5f ,\n",float(image[y][x][0])/255,float(image[y][x][1])/255,float(image[y][x][2])/255);
//	}
//	fprintf(stream_iv,"\n    ]\n  }\n  Coordinate3\n  {\n    point\n    [\n");
//	/*file in the coordinates*/
//	for(y=ymin;y<=ymax;y++) for(x=xmin;x<=xmax;x++)
//	{
//		fprintf(stream_iv,"        %2.5f %2.5f %2.5f ,\n",-float(x),-float(y),-depth[y][x]*depth_scale);	
//	}
//	fprintf(stream_iv,"\n    ]\n  }\n  MaterialBinding\n  {\n    value PER_VERTEX\n  }\n  PointSet\n  {\n    numPoints %d\n  }\n}\n",nr_points);
//	fclose(stream_iv);
//	return(0);
//}
//
//int save_iv_triangles(char* file_name,float **depth,unsigned char ***image,int ymin,int ymax,int xmin,int xmax,int point_size,float depth_scale,float xy_scale)
//{
//	FILE * stream_iv; int y,x,nr_points,h,w;
//	
//	nr_points=(ymax-ymin+1)*(xmax-xmin+1);
//	//stream_iv=fopen(file_name,"w");
//	fopen_s(&stream_iv,file_name,"w");
//	fprintf(stream_iv,"#Inventor V2.1 ascii\n");
//	fprintf(stream_iv,"Separator\n{\n");
//	fprintf(stream_iv,"  DrawStyle\n  {\n");
//	fprintf(stream_iv,"    pointSize %d\n  }\n",point_size);
//	fprintf(stream_iv,"  Material\n  {\n");
//	/*file in the color*/
//	fprintf(stream_iv,"    diffuseColor\n    [\n");
//	if(image==NULL)
//	{
//		for(y=ymin;y<=ymax;y++) for(x=xmin;x<=xmax;x++)
//			fprintf(stream_iv,"        %2.5f %2.5f %2.5f ,\n",1.0f,1.0f,1.0f);
//	}
//	else
//	{
//		for(y=ymin;y<=ymax;y++) for(x=xmin;x<=xmax;x++)
//			fprintf(stream_iv,"        %2.5f %2.5f %2.5f ,\n",float(image[y][x][0])/255,float(image[y][x][1])/255,float(image[y][x][2])/255);
//	}
//	fprintf(stream_iv,"\n    ]\n  }\n");
//
//	/*TextureCoordinate Bind*/
//	fprintf(stream_iv,"  TextureCoordinateBinding\n  {\n    value PER_VERTEX_INDEXED\n  }\n");
//	/*material Bind*/
//	fprintf(stream_iv,"  MaterialBinding\n  {\n    value PER_VERTEX_INDEXED\n  }\n");
//	/*ShapeHints*/
//	fprintf(stream_iv,"ShapeHints\n  {\n");
//	fprintf(stream_iv,"    vertexOrdering COUNTERCLOCKWISE\n");
//	fprintf(stream_iv,"    shapeType UNKNOWN_SHAPE_TYPE\n");
//	fprintf(stream_iv,"    faceType CONVEX\n");
//	fprintf(stream_iv,"    creaseAngle 6.28319\n");
//	fprintf(stream_iv,"  }\n");
//
//	/*file in the coordinates*/
//	fprintf(stream_iv,"  Coordinate3\n  {\n    point\n    [\n");
//	for(y=ymin;y<=ymax;y++) for(x=xmin;x<=xmax;x++)
//	{
//		fprintf(stream_iv,"        %2.5f %2.5f %2.5f ,\n",float(x)*xy_scale,-float(y)*xy_scale,-depth[y][x]*depth_scale);	
//	}
//	fprintf(stream_iv,"\n    ]\n  }\n");
//	/*draw triangles*/
//	fprintf(stream_iv,"  IndexedFaceSet\n  {\n");
//	h=ymax-ymin+1; w=xmax-xmin+1;
//	fprintf(stream_iv,"    coordIndex\n    [\n");
//	for(y=0;y<h-1;y++) for(x=0;x<w-1;x++)
//	{	
//		fprintf(stream_iv,"        %d,%d,%d,%d,\n",((y+1)*w+x),(y*w+x+1),(y*w+x),-1);
//		fprintf(stream_iv,"        %d,%d,%d,%d,\n",((y+1)*w+x),((y+1)*w+x+1),(y*w+x+1),-1);
//	}
//	fprintf(stream_iv,"\n    ]\n");
//	//fprintf(stream_iv,"    materialIndex \n    [\n");
//	//for(y=0;y<h-1;y++) for(x=0;x<w-1;x++)
//	//{	
//	//	//fprintf(stream_iv,"        %d,%d,%d,%d,\n",((y+1)*w+x),(y*w+x+1),(y*w+x),-1);
//	//	//fprintf(stream_iv,"        %d,%d,%d,%d,\n",((y+1)*w+x),((y+1)*w+x+1),(y*w+x+1),-1);
//	//	fprintf(stream_iv,"        %d,%d,%d,%d,\n",y,y,y,-1);
//	//	fprintf(stream_iv,"        %d,%d,%d,%d,\n",y,y,y,-1);
//	//}
//	//fprintf(stream_iv,"\n    ]\n");
//
//
//	fprintf(stream_iv,"  }\n");
//
//	fprintf(stream_iv,"  PointSet\n  {\n    numPoints %d\n  }\n}\n",nr_points);
//	fclose(stream_iv);
//	return(0);
//}
//
//void matrix_save_ascii(char *file_path,double **in,int h,int w)
//{
//	FILE * file_in; int i,j;
//	//file_in= fopen(file_path, "w");
//	fopen_s(&file_in,file_path, "w");
//	for (i=0;i<h;i++)    
//	{	
//		for(j=0;j<w;j++)
//		{
//			fprintf(file_in, "%e", in[i][j]);	
//			fprintf(file_in, "%c",' ');
//		}
//		fprintf(file_in, "%c",'\n');
//	}
//	fclose(file_in);
//}

void Normalize(double * Vec, int Len, double Sum)
{
	int i;
	double SumVal= 0;
	for(i=0; i<Len; i++){ SumVal += Vec[i]; }
	SumVal+=-QX_DEF_DOUBLE_MAX;
	SumVal/=Sum;
	for (i=0; i<Len; i++){ Vec[i]/=SumVal; }
}
void Normalize(float * Vec, int Len, float Sum)
{
	int i;
	float SumVal= 0;
	for(i=0; i<Len; i++){ SumVal += Vec[i]; }
	SumVal+=-QX_DEF_FLOAT_MAX;
	SumVal/=Sum;
	for (i=0; i<Len; i++){ Vec[i]/=SumVal; }
}
bool larger(float a,float b)
{
   return a>b;
}
bool smaller(float a,float b)
{
   return a<b;
}
void vec_sort_increase(float *in,int len)
{
	sort(&in[0],&in[len],smaller);
}
void vec_sort_decrease(float *in,int len)
{
	sort(&in[0],&in[len],larger);
}
void vec_sort_decrease(double *in,int len)
{
	sort(&in[0],&in[len],larger);
}

void qx_sort_increase_using_histogram(int*id,unsigned char*image,int len)
{
	int histogram[QX_DEF_CHAR_MAX+1];
	int nr_bin=QX_DEF_CHAR_MAX+1;
	memset(histogram,0,sizeof(int)*nr_bin);
	for(int i=0;i<len;i++)
	{
		histogram[image[i]]++;
	}
	int nr_hitted_prev=histogram[0];
	histogram[0]=0;
	for(int k=1;k<nr_bin;k++)
	{
		int nr_hitted=histogram[k];
		histogram[k]=nr_hitted_prev+histogram[k-1];
		nr_hitted_prev=nr_hitted;
	}
	for(int i=0;i<len;i++)
	{
		unsigned char dist=image[i];
		int index=histogram[dist]++;
		id[index]=i;
	}
}

void qx_vec_sort_decrease_f3(float a[3],int b[3])
{
	float at; int bt;
	if(a[0]<a[1])
	{
		at=a[0]; a[0]=a[1]; a[1]=at;
		bt=b[0]; b[0]=b[1]; b[1]=bt;
	}
	if(a[0]<a[2])
	{
		at=a[0]; a[0]=a[2]; a[2]=at;
		bt=b[0]; b[0]=b[2]; b[2]=bt;
	}
	if(a[1]<a[2])
	{
		at=a[1]; a[1]=a[2]; a[2]=at;
		bt=b[1]; b[1]=b[2]; b[2]=bt;
	}
}
void vec_sort_decrease_with_id(double*confidence,int*id,int len,int nr_selected)
{
	double conf; int pos; double temp;
	if(nr_selected<=0) nr_selected=len;
	for(int i=0;i<nr_selected;i++)
	{
		vec_max_pos(pos,&confidence[i],len-i);
		pos+=i;
		/*exchange*/
		temp=id[i];
		conf=confidence[i];

		id[i]=id[pos];
		confidence[i]=confidence[pos];
		
		id[pos]=temp;
		confidence[pos]=conf;
	}
}
void vec_sort_decrease_bf_2d(float *confidence,char **filename,int len,int nr_selected)
{
	float conf; int pos; char str[QX_DEF_STRING_LENGTH]; int str_len=QX_DEF_STRING_LENGTH;
	if(nr_selected<=0) nr_selected=len;
	for(int i=0;i<nr_selected;i++)
	{
		vec_max_pos(pos,&confidence[i],len-i);
		pos+=i;
		/*exchange*/
		sprintf_s(str,str_len,"%s",filename[i]);
		conf=confidence[i];

		sprintf_s(filename[i],str_len,"%s",filename[pos]);
		confidence[i]=confidence[pos];
		
		sprintf_s(filename[pos],str_len,"%s",str);
		confidence[pos]=conf;
	}
}
void vec_sort_decrease_bf_2d(int *confidence,char **filename,int len)
{
	int conf; int pos; char str[QX_DEF_STRING_LENGTH]; int str_len=QX_DEF_STRING_LENGTH;
	for(int i=0;i<len;i++)
	{
		vec_max_pos(pos,&confidence[i],len-i);
		pos+=i;
		/*exchange*/
		sprintf_s(str,str_len,"%s",filename[i]);
		conf=confidence[i];

		sprintf_s(filename[i],str_len,"%s",filename[pos]);
		confidence[i]=confidence[pos];
		
		sprintf_s(filename[pos],str_len,"%s",str);
		confidence[pos]=conf;
	}
}
void vec_sort_decrease_bf_2d(int*confidence,int*index,int len,int nr_selected)
{
	int conf,id; int pos;
	for(int i=0;i<nr_selected;i++)
	{
		vec_max_pos(pos,&confidence[i],len-i);
		pos+=i;
		/*exchange*/
		conf=confidence[i];
		id=index[i];
		confidence[i]=confidence[pos];
		index[i]=index[pos];
		confidence[pos]=conf;
		index[pos]=id;
	}
}
bool smaller_u(unsigned char a,unsigned char b)
{
   return a<b;
}
void vec_sort_increase_u(unsigned char *in,int len)
{
	sort(&in[0],&in[len],smaller_u);
}
bool smaller_i(int a,int b)
{
   return a<b;
}
void vec_sort_increase_i(int *in,int len)
{
	sort(&in[0],&in[len],smaller_i);
}
bool larger_i(int a,int b)
{
   return a>b;
}
void vec_sort_decrease_i(int *in,int len)
{
	sort(&in[0],&in[len],larger_i);
}
void vec_normalized(double *in,int len)
{
	double sum=0; int i; double *curr;
	for(curr=in,i=0;i<len;i++) sum+=*(curr++);
	sum=1.0/sum;
	for(curr=in,i=0;i<len;i++) (*(curr++))*=sum;
}
double VecSort(double * InVec, int N)
{
	int i,j;
	double tmp;
	for (i=0; i<N; i++)
	{
		tmp= InVec[i];
		for (j=i+1; j<N; j++) 
		{
			if (InVec[j]>tmp)
			{
				InVec[i]= InVec[j];
				InVec[j]= tmp;
				tmp= InVec[i];
			}
		}
	}
	return InVec[N/2];
}
double VecSort(float * InVec, int N)
{
	int i,j;
	float tmp;
	for (i=0; i<N; i++)
	{
		tmp= InVec[i];
		for (j=i+1; j<N; j++) 
		{
			if (InVec[j]>tmp)
			{
				InVec[i]= InVec[j];
				InVec[j]= tmp;
				tmp= InVec[i];
			}
		}
	}
	return InVec[N/2];
}
void vec_exchange(int *vec,int i,int j)
{
	int t;
	t=vec[i];
	vec[i]=vec[j];
	vec[j]=t;
}
void vec_min_val(int &min_val,int *in,int len)
{
	min_val=in[0];
	for(int i=1;i<len;i++) if(in[i]<min_val) min_val=in[i];	
}
void vec_min_pos(int &min_pos,int *in,int len)
{
	int min_val=in[0];
	min_pos=0;
	for (int i=1;i<len;i++) if(in[i]<min_val)
	{
		min_val=in[i];	
		min_pos= i;
	}
}
void vec_min_pos(int &min_pos,short *in,int len)
{
	short min_val=in[0];
	min_pos=0;
	for (int i=1;i<len;i++) if(in[i]<min_val)
	{
		min_val=in[i];	
		min_pos= i;
	}
}
void vec_max_val(int &max_val,int *in,int len)
{
	max_val=in[0];
	for(int i=1;i<len;i++) if(in[i]>max_val) max_val=in[i];	
}
void vec_max_val(short&max_val,short*in,int len)
{
	max_val=in[0];
	for(int i=1;i<len;i++) if(in[i]>max_val) max_val=in[i];	
}

void vec_max_pos(unsigned int &max_pos,unsigned int *in,unsigned int len)
{
	unsigned int max_val=in[0];
	max_pos=0;
	for(unsigned int i=1;i<len;i++) if(in[i]>max_val)
	{
		max_val=in[i];	
		max_pos=i;
	}
}
void vec_max_pos(int &max_pos,int *in,int len)
{
	int max_val=in[0];
	max_pos=0;
	for (int i=1;i<len;i++) if(in[i]>max_val)
	{
		max_val=in[i];	
		max_pos= i;
	}
}
void vec_min_val(float &min_val,float *in,int len)
{
	min_val=in[0];
	for(int i=1;i<len;i++) if(in[i]<min_val) min_val=in[i];	
}
void vec_min_pos(int &min_pos,float *in,int len)
{
	float min_val=in[0];
	min_pos=0;
	for (int i=1;i<len;i++) if(in[i]<min_val)
	{
		min_val=in[i];	
		min_pos= i;
	}
}
void vec_max_val(float &max_val,float *in,int len)
{
	max_val=in[0];
	for(int i=1;i<len;i++) if(in[i]>max_val) max_val=in[i];	
}
void vec_max_pos(int &max_pos,float *in,int len)
{
	float max_val=in[0];
	max_pos=0;
	for (int i=1;i<len;i++) if(in[i]>max_val)
	{
		max_val=in[i];	
		max_pos= i;
	}
}

void vec_min_val(double &min_val,double *in,int len)
{
	min_val=in[0];
	for(int i=1;i<len;i++) if(in[i]<min_val) min_val=in[i];	
}
void vec_min_pos(int &min_pos,double *in,int len)
{
	double min_val=in[0];
	min_pos=0;
	for (int i=1;i<len;i++) if(in[i]<min_val)
	{
		min_val=in[i];	
		min_pos= i;
	}
}
void vec_max_val(double &max_val,double *in,int len)
{
	max_val=in[0];
	for(int i=1;i<len;i++) if(in[i]>max_val) max_val=in[i];	
}
void vec_max_pos(int &max_pos,double *in,int len)
{
	double max_val=in[0];
	max_pos=0;
	for (int i=1;i<len;i++) if(in[i]>max_val)
	{
		max_val=in[i];	
		max_pos= i;
	}
}
void vec_max_val(unsigned char &max_val,unsigned char *in,int len)
{
	max_val=in[0];
	for(int i=1;i<len;i++) if(in[i]>max_val) max_val=in[i];	
}
void vec_max_pos(int &max_pos,unsigned char *in,int len)
{
	unsigned char max_val=in[0];
	max_pos=0;
	for (int i=1;i<len;i++) if(in[i]>max_val)
	{
		max_val=in[i];	
		max_pos= i;
	}
}
double vec_max(int &max_pos,double *in,int len)
{
	double max_val=in[0];
	max_pos=0;
	for (int i=1;i<len;i++) if(in[i]>max_val)
	{
		max_val=in[i];	
		max_pos= i;
	}
	return(max_val);
}
double vec_min(int &min_pos,double *in,int len)
{
	double min_val=in[0];
	min_pos=0;
	for (int i=1;i<len;i++) if(in[i]<min_val)
	{
		min_val=in[i];	
		min_pos= i;
	}
	return(min_val);
}
double vec_min_2nd(int &min_pos,double *in,double in_min,int len)
{
	double min_val=in[0];
	min_pos=0;
	for (int i=1;i<len;i++) if(in[i]<min_val&&in[i]!=in_min)
	{
		min_val=in[i];	
		min_pos= i;
	}
	return(min_val);
}
void vec_min_val(unsigned char &min_val,unsigned char *in,int len)
{
	min_val=in[0];
	for(int i=1;i<len;i++) if(in[i]<min_val) min_val=in[i];	
}
void vec_min_pos(int &min_pos,unsigned char *in,int len)
{
	unsigned char min_val=in[0];
	min_pos=0;
	for (int i=1;i<len;i++) if(in[i]<min_val)
	{
		min_val=in[i];	
		min_pos= i;
	}
}
double qx_determinant(double**InMat,int N)
{
	int n, m, i, N_=N-1;
	double CoefMul, det=InMat[0][0];	
	for (n=0; n<N_; n++)
	{
		for (i=n+1; i<N; i++)
		{
			CoefMul= InMat[i][n]/InMat[n][n];
			for (m=n; m<N; m++)
				InMat[i][m]= InMat[i][m]- InMat[n][m]*CoefMul;
		}
	}
	for (n=1; n<N; n++) { det= det*InMat[n][n]; }
	return det; 
}
float qx_determinant(float**InMat,int N)
{
	int n, m, i, N_=N-1;
	float CoefMul, det=InMat[0][0];	
	for (n=0; n<N_; n++)
	{
		for (i=n+1; i<N; i++)
		{
			CoefMul= InMat[i][n]/InMat[n][n];
			for (m=n; m<N; m++)
				InMat[i][m]= InMat[i][m]- InMat[n][m]*CoefMul;
		}
	}
	for (n=1; n<N; n++) { det= det*InMat[n][n]; }
	return det; 
}
void qx_matrix_product(double**out,double**a,double**b,int N,int M,int L)//a[N,M]xb[M,L]
{
	int n,m,l;
	for(n=0;n<N;n++)
	{
		for(l=0;l<L;l++)
		{
			out[n][l]=0;
			for(m=0;m<M;m++) out[n][l]+=a[n][m]*b[m][l];
		}
	}
}
void qx_matrix_product_axbt(double**out,double**a,double**b,int N,int M,int L)//a[N,M]xb[L,M](b'[M,L])=out[N,L]
{
	int n,m,l;
	for(n=0;n<N;n++)
	{
		for(l=0;l<L;l++)
		{
			out[n][l]=0;
			for(m=0;m<M;m++) out[n][l]+=a[n][m]*b[l][m];
		}
	}
}
void qx_matrix_product(float**out,float**a,float**b,int N,int M,int L)//a[N,M]xb[M,L]
{
	int n,m,l;
	for(n=0;n<N;n++)
	{
		for(l=0;l<L;l++)
		{
			out[n][l]=0;
			for(m=0;m<M;m++) out[n][l]+=a[n][m]*b[m][l];
		}
	}
}
void qx_matrix_product_axbt(float**out,float**a,float**b,int N,int M,int L)//a[N,M]xb[L,M](b'[M,L])=out[N,L]
{
	int n,m,l;
	for(n=0;n<N;n++)
	{
		for(l=0;l<L;l++)
		{
			out[n][l]=0;
			for(m=0;m<M;m++) out[n][l]+=a[n][m]*b[l][m];
		}
	}
}
void qx_matrix_product(double*out,double**a,double*b,int N,int M)//axb
{
	int n,m;
	for(n=0;n<N;n++)
	{
		out[n]=0;
		for(m=0;m<M;m++) out[n]+=a[n][m]*b[m];
	}
}
void qx_matrix_product(float*out,float**a,float*b,int N,int M)//axb
{
	int n,m;
	for(n=0;n<N;n++)
	{
		out[n]=0;
		for(m=0;m<M;m++) out[n]+=a[n][m]*b[m];
	}
}
//Compute Matrix Y, such that L*Y=B
void LX_Y(double **L, double *Y, int N, double *X)
{
	double tmp; 
	int i,j;
	X[0]= Y[0]/L[0][0];
	for (i=1; i<N; i++)
	{
		tmp= 0;
		for (j=0; j<i; j++)
			tmp+= L[i][j]*X[j];
		X[i]= (Y[i]-tmp)/L[i][i];
	}
}
void LX_Y(float **L, float *Y, int N, float *X)
{
	float tmp; 
	int i,j;
	X[0]= Y[0]/L[0][0];
	for (i=1; i<N; i++)
	{
		tmp= 0;
		for (j=0; j<i; j++)
			tmp+= L[i][j]*X[j];
		X[i]= (Y[i]-tmp)/L[i][i];
	}
}
//Compute Matrix X, such that U*X=Y
void UX_Y(double **U, double *Y, int N, double *X)
{
	double tmp; 
	int i,j;
	X[N-1]= Y[N-1]/U[N-1][N-1];
	for (i=N-2; i>=0; i--)
	{
		tmp= 0;
		for (j=N-1; j>i; j--)
			tmp+= U[i][j]*X[j];
		X[i]= (Y[i]-tmp)/U[i][i];
	}
}
void UX_Y(float **U, float *Y, int N, float *X)
{
	float tmp; 
	int i,j;
	X[N-1]= Y[N-1]/U[N-1][N-1];
	for (i=N-2; i>=0; i--)
	{
		tmp= 0;
		for (j=N-1; j>i; j--)
			tmp+= U[i][j]*X[j];
		X[i]= (Y[i]-tmp)/U[i][i];
	}
}
void LUX_Y(double **L,double **U,double *UX,double *X,int N,double *Y)
{
	LX_Y(L,Y,N,UX);
	UX_Y(U,UX,N,X);
}
void LU_33(float **A, float **L, float **U)
{	
	U[0][0]= A[0][0]; U[0][1]= A[0][1]; U[0][2]= A[0][2]; 
	L[1][0]= A[1][0]/A[0][0];
	L[2][0]= A[2][0]/A[0][0];
	U[1][1]= A[1][1]- L[1][0]*A[0][1]; U[1][2]= A[1][2]- L[1][0]*A[0][2];
	U[2][1]= A[2][1]- L[2][0]*A[0][1]; U[2][2]= A[2][2]- L[2][0]*A[0][2];
	L[2][1]= U[2][1]/U[1][1]; 
	U[2][1]= U[2][1]- L[2][1]*U[1][1]; U[2][2]= U[2][2]- L[2][1]*U[1][2];	
}
void LU_Inverse(float **A, float **B)
{	
	float **L, **U,**U_Transpose,**L_Transpose, **Ones_33;
	L			= qx_allocf(3,3);
	U			= qx_allocf(3,3);
	U_Transpose = qx_allocf(3,3);
	L_Transpose = qx_allocf(3,3);
	Ones_33		= qx_allocf(3,3);
	qx_eye(Ones_33,3);	
	qx_eye(L,3);	
	qx_eye(U,3);	
	LU_33(A, L, U);
	UX_Y(U, Ones_33[0], 3, U_Transpose[0]);
	UX_Y(U, Ones_33[1], 3, U_Transpose[1]);
	UX_Y(U, Ones_33[2], 3, U_Transpose[2]);
	Transpose(U_Transpose, 3, 3, U);	
	LX_Y(L, Ones_33[0], 3, L_Transpose[0]);
	LX_Y(L, Ones_33[1], 3, L_Transpose[1]);
	LX_Y(L, Ones_33[2], 3, L_Transpose[2]);
	Transpose(L_Transpose, 3, 3, L);
	qx_matrix_product(B,U,L,3,3,3);
	qx_freef(L);
	qx_freef(U);
	qx_freef(U_Transpose);
	qx_freef(L_Transpose);
	qx_freef(Ones_33);
}
void LU_33(double **A, double **L, double **U)
{	
	U[0][0]= A[0][0]; U[0][1]= A[0][1]; U[0][2]= A[0][2]; 
	L[1][0]= A[1][0]/A[0][0];
	L[2][0]= A[2][0]/A[0][0];
	U[1][1]= A[1][1]- L[1][0]*A[0][1]; U[1][2]= A[1][2]- L[1][0]*A[0][2];
	U[2][1]= A[2][1]- L[2][0]*A[0][1]; U[2][2]= A[2][2]- L[2][0]*A[0][2];
	L[2][1]= U[2][1]/U[1][1]; 
	U[2][1]= U[2][1]- L[2][1]*U[1][1]; U[2][2]= U[2][2]- L[2][1]*U[1][2];	
}
void LU_Inverse(double **A, double **B)
{	
	double **L, **U,**U_Transpose,**L_Transpose, **Ones_33;
	L			= qx_allocd(3,3);
	U			= qx_allocd(3,3);
	U_Transpose = qx_allocd(3,3);
	L_Transpose = qx_allocd(3,3);
	Ones_33		= qx_allocd(3,3);
	qx_eye(Ones_33,3);	
	qx_eye(L,3);	
	qx_eye(U,3);	
	LU_33(A, L, U);
	UX_Y(U, Ones_33[0], 3, U_Transpose[0]);
	UX_Y(U, Ones_33[1], 3, U_Transpose[1]);
	UX_Y(U, Ones_33[2], 3, U_Transpose[2]);
	Transpose(U_Transpose, 3, 3, U);
	
	LX_Y(L, Ones_33[0], 3, L_Transpose[0]);
	LX_Y(L, Ones_33[1], 3, L_Transpose[1]);
	LX_Y(L, Ones_33[2], 3, L_Transpose[2]);
	Transpose(L_Transpose, 3, 3, L);
	qx_matrix_product(B,U,L,3,3,3);
	qx_freed(L);
	qx_freed(U);
	qx_freed(U_Transpose);
	qx_freed(L_Transpose);
	qx_freed(Ones_33);
}
void lu(int *exchange,float **l,float **u,float **in,float *tmp_array,int size)
{
	int d,y,x,max_pos;
	float max_val;
	memset(l[0],0,sizeof(float)*size*size);
	memset(u[0],0,sizeof(float)*size*size);
	for(d=0;d<size-1;d++)
	{
		max_val=0.0f;
		max_pos=d;
		for(y=d;y<size;y++)
			if( abs(in[y][d])>max_val )
			{
				max_val=abs(in[y][d]);
				max_pos=y;
			}
		y=exchange[d];
		exchange[d]=exchange[max_pos];
		exchange[max_pos]=y;
		memcpy(tmp_array,in[d],sizeof(float)*size);
		memcpy(in[d],in[max_pos],sizeof(float)*size);
		memcpy(in[max_pos],tmp_array,sizeof(float)*size);		
		memcpy(tmp_array,l[d],sizeof(float)*size);
		memcpy(l[d],l[max_pos],sizeof(float)*size);
		memcpy(l[max_pos],tmp_array,sizeof(float)*size);		
		memcpy(tmp_array,u[d],sizeof(float)*size);
		memcpy(u[d],u[max_pos],sizeof(float)*size);
		memcpy(u[max_pos],tmp_array,sizeof(float)*size);
	
		memcpy(&(u[d][d]),&(in[d][d]),sizeof(float)*(size-d));
		for(y=d;y<size;y++)
			l[y][d]=in[y][d]/in[d][d];
		for(y=d+1;y<size;y++)
			for(x=d+1;x<size;x++)
				in[y][x]-=l[y][d]*in[d][x];

	}
    l[size-1][size-1]=1.0f;
    u[size-1][size-1]=in[size-1][size-1];
}
void lu(int *exchange,double **l,double **u,double **in,double *tmp_array,int size)
{
	int d,y,x,max_pos;
	double max_val;
	memset(l[0],0,sizeof(double)*size*size);
	memset(u[0],0,sizeof(double)*size*size);
	for(d=0;d<size-1;d++)
	{
		max_val=0.0f;
		max_pos=d;
		for(y=d;y<size;y++)
			if( abs(in[y][d])>max_val )
			{
				max_val=abs(in[y][d]);
				max_pos=y;
			}
		y=exchange[d];
		exchange[d]=exchange[max_pos];
		exchange[max_pos]=y;
		memcpy(tmp_array,in[d],sizeof(double)*size);
		memcpy(in[d],in[max_pos],sizeof(double)*size);
		memcpy(in[max_pos],tmp_array,sizeof(double)*size);		
		memcpy(tmp_array,l[d],sizeof(double)*size);
		memcpy(l[d],l[max_pos],sizeof(double)*size);
		memcpy(l[max_pos],tmp_array,sizeof(double)*size);		
		memcpy(tmp_array,u[d],sizeof(double)*size);
		memcpy(u[d],u[max_pos],sizeof(double)*size);
		memcpy(u[max_pos],tmp_array,sizeof(double)*size);
	
		memcpy(&(u[d][d]),&(in[d][d]),sizeof(double)*(size-d));
		for(y=d;y<size;y++)
			l[y][d]=in[y][d]/in[d][d];
		for(y=d+1;y<size;y++)
			for(x=d+1;x<size;x++)
				in[y][x]-=l[y][d]*in[d][x];

	}
    l[size-1][size-1]=1.0;
    u[size-1][size-1]=in[size-1][size-1];
}
void lux_y(float *x,float *y,float **l,float **u,float **in,int size)
{
	int d;
	int *exchange=new int [size];
	float *y_cpy=new float [size],*x_cpy=new float [size];
	float *tmp_array=new float [size];
	for(d=0;d<size;d++)
		exchange[d]=d;
	lu(exchange,l,u,in,tmp_array,size);
	for(d=0;d<size;d++)
		y_cpy[d]=y[(exchange[d])];
	LX_Y(l,y_cpy,size,x_cpy);
	UX_Y(u,x_cpy,size,x);
	delete [] exchange;
	delete [] y_cpy;
	delete [] x_cpy;
	delete [] tmp_array;
}
void lux_y(double *x,double *y,double **l,double **u,double **in,int size)
{
	int d;
	int *exchange=new int [size];
	double *y_cpy=new double [size],*x_cpy=new double [size];
	double *tmp_array=new double [size];
	for(d=0;d<size;d++)
		exchange[d]=d;
	lu(exchange,l,u,in,tmp_array,size);
	for(d=0;d<size;d++)
		y_cpy[d]=y[(exchange[d])];
	LX_Y(l,y_cpy,size,x_cpy);
	UX_Y(u,x_cpy,size,x);
	delete [] exchange;
	delete [] y_cpy;
	delete [] x_cpy;
	delete [] tmp_array;
}

void Transpose(double ** K, int N, int M, double ** K_Inv)
{
	int i,j;
	for (i=0; i<M; i++)
		for (j=0; j<N; j++) { K_Inv[i][j]= K[j][i]; }
}
void Transpose(float ** K, int N, int M, float ** K_Inv)
{
	int i,j;
	for (i=0; i<M; i++)
		for (j=0; j<N; j++) { K_Inv[i][j]= K[j][i]; }
}
void Accumulate(double **InMat, int H, int W, double**OutMat)
{
	int i,j,i_1,j_1;

	for (i=0; i<H; i++)
		for (j=0; j<W; j++)
			OutMat[i][j]= 0;
	OutMat[0][0]= InMat[0][0];
	for (i=1; i<H; i++)
		OutMat[i][0]= OutMat[i-1][0]+InMat[i][0];	
	for (j=1; j<W; j++)
		OutMat[0][j]= OutMat[0][j-1]+InMat[0][j];
	for (i=1; i<H; i++)
		for (j=1; j<W; j++)
		{
			i_1= i-1; j_1= j-1;
			OutMat[i][j]= OutMat[i_1][j]+OutMat[i][j_1]-OutMat[i_1][j_1]+InMat[i][j];
		}
	//for (i=0; i<H; i++) { for (j=0; j<W; j++) {	cout<<OutMat[i][j]<<" "; } cout<<endl; }
}
bool qx_inv_2x2(double inv[4],double in[4])
{
	double det;
	det=in[0]*in[3]-in[1]*in[2];
	if (abs(det)<QX_DEF_THRESHOLD_ZERO_DOUBLE)
	{
		//printf("det==0!\n");
		//getchar();
		//exit(0);
		return(false);
	}
	det=1.0/det;
	inv[0]=in[3]*det;
	inv[1]=-in[1]*det;
	inv[2]=-in[2]*det;
	inv[3]=in[0]*det;
	return(true);
}
void inv_3x3(double h_inv[9],float h_in[9])
{
	double det, inv_det;
	double h5h7, h4h8, h3h8,h5h6,h4h6,h3h7;
	double h1h8, h2h7, h0h8, h2h6, h0h7, h1h6, h1h5, h2h4, h0h5, h2h3, h0h4, h1h3;
	h4h8= h_in[4]*h_in[8]; h5h7=h_in[5]*h_in[7]; h3h8= h_in[3]*h_in[8]; 
	h5h6= h_in[5]*h_in[6]; h3h7= h_in[3]*h_in[7]; h4h6= h_in[4]*h_in[6]; 
	det= h_in[0]*(h4h8-h5h7)-h_in[1]*(h3h8-h5h6)+h_in[2]*(h3h7-h4h6);
	if (abs(det)<1e-6)
	{
		//cout<<"det==0"<<endl;
		//exit(0);
	}
	else
	{
		h1h8= h_in[1]*h_in[8];
		h2h7= h_in[2]*h_in[7];
		h0h8= h_in[0]*h_in[8]; 
		h2h6= h_in[2]*h_in[6]; 
		h0h7= h_in[0]*h_in[7];
		h1h6= h_in[1]*h_in[6]; 
		h1h5= h_in[1]*h_in[5];
		h2h4= h_in[2]*h_in[4];
		h0h5= h_in[0]*h_in[5];
		h2h3= h_in[2]*h_in[3];
		h0h4= h_in[0]*h_in[4];
		h1h3= h_in[1]*h_in[3];
		inv_det= 1.0/det;
		h_inv[0]=  inv_det*(h4h8-h5h7);
		h_inv[3]= -inv_det*(h3h8-h5h6);
		h_inv[6]=  inv_det*(h3h7-h4h6);
		h_inv[1]= -inv_det*(h1h8-h2h7);
		h_inv[4]=  inv_det*(h0h8-h2h6);
		h_inv[7]= -inv_det*(h0h7-h1h6);
		h_inv[2]=  inv_det*(h1h5-h2h4);
		h_inv[5]= -inv_det*(h0h5-h2h3);
		h_inv[8]=  inv_det*(h0h4-h1h3);
	}
	//for (int i=0; i<9; i++) { cout<<h_inv[i]<<" "; } cout<<endl;
}
void inv_3x3(float h_inv[9],float h_in[9])
{
	float det, inv_det;
	float h5h7, h4h8, h3h8,h5h6,h4h6,h3h7;
	float h1h8, h2h7, h0h8, h2h6, h0h7, h1h6, h1h5, h2h4, h0h5, h2h3, h0h4, h1h3;
	h4h8= h_in[4]*h_in[8]; h5h7=h_in[5]*h_in[7]; h3h8= h_in[3]*h_in[8]; 
	h5h6= h_in[5]*h_in[6]; h3h7= h_in[3]*h_in[7]; h4h6= h_in[4]*h_in[6]; 
	det= h_in[0]*(h4h8-h5h7)-h_in[1]*(h3h8-h5h6)+h_in[2]*(h3h7-h4h6);
	if (abs(det)<1e-6)
	{
		//cout<<"det==0"<<endl;
		//exit(0);
	}
	else
	{
		h1h8= h_in[1]*h_in[8];
		h2h7= h_in[2]*h_in[7];
		h0h8= h_in[0]*h_in[8]; 
		h2h6= h_in[2]*h_in[6]; 
		h0h7= h_in[0]*h_in[7];
		h1h6= h_in[1]*h_in[6]; 
		h1h5= h_in[1]*h_in[5];
		h2h4= h_in[2]*h_in[4];
		h0h5= h_in[0]*h_in[5];
		h2h3= h_in[2]*h_in[3];
		h0h4= h_in[0]*h_in[4];
		h1h3= h_in[1]*h_in[3];
		inv_det= 1.0f/det;
		h_inv[0]=  inv_det*(h4h8-h5h7);
		h_inv[3]= -inv_det*(h3h8-h5h6);
		h_inv[6]=  inv_det*(h3h7-h4h6);
		h_inv[1]= -inv_det*(h1h8-h2h7);
		h_inv[4]=  inv_det*(h0h8-h2h6);
		h_inv[7]= -inv_det*(h0h7-h1h6);
		h_inv[2]=  inv_det*(h1h5-h2h4);
		h_inv[5]= -inv_det*(h0h5-h2h3);
		h_inv[8]=  inv_det*(h0h4-h1h3);
	}
	//for (int i=0; i<9; i++) { cout<<h_inv[i]<<" "; } cout<<endl;
}
double qx_inv_3x3(double h_inv[9],double h_in[9],double threshold)
{
	double det, inv_det;
	double h5h7, h4h8, h3h8,h5h6,h4h6,h3h7;
	double h1h8, h2h7, h0h8, h2h6, h0h7, h1h6, h1h5, h2h4, h0h5, h2h3, h0h4, h1h3;
	h4h8= h_in[4]*h_in[8]; h5h7=h_in[5]*h_in[7]; h3h8= h_in[3]*h_in[8]; 
	h5h6= h_in[5]*h_in[6]; h3h7= h_in[3]*h_in[7]; h4h6= h_in[4]*h_in[6]; 
	det= h_in[0]*(h4h8-h5h7)-h_in[1]*(h3h8-h5h6)+h_in[2]*(h3h7-h4h6);
	if (abs(det)<threshold) 
	{
		printf("[det<%e] ",threshold);
		memset(h_inv,0,sizeof(double)*9);
	}
	else
	{
		h1h8= h_in[1]*h_in[8];
		h2h7= h_in[2]*h_in[7];
		h0h8= h_in[0]*h_in[8]; 
		h2h6= h_in[2]*h_in[6]; 
		h0h7= h_in[0]*h_in[7];
		h1h6= h_in[1]*h_in[6]; 
		h1h5= h_in[1]*h_in[5];
		h2h4= h_in[2]*h_in[4];
		h0h5= h_in[0]*h_in[5];
		h2h3= h_in[2]*h_in[3];
		h0h4= h_in[0]*h_in[4];
		h1h3= h_in[1]*h_in[3];
		//inv_det= 1.0/det;
		//h_inv[0]=  inv_det*(h4h8-h5h7);
		//h_inv[3]= -inv_det*(h3h8-h5h6);
		//h_inv[6]=  inv_det*(h3h7-h4h6);
		//h_inv[1]= -inv_det*(h1h8-h2h7);
		//h_inv[4]=  inv_det*(h0h8-h2h6);
		//h_inv[7]= -inv_det*(h0h7-h1h6);
		//h_inv[2]=  inv_det*(h1h5-h2h4);
		//h_inv[5]= -inv_det*(h0h5-h2h3);
		//h_inv[8]=  inv_det*(h0h4-h1h3);
		h_inv[0]=  (h4h8-h5h7)/det;
		h_inv[3]= -(h3h8-h5h6)/det;
		h_inv[6]=  (h3h7-h4h6)/det;
		h_inv[1]= -(h1h8-h2h7)/det;
		h_inv[4]=  (h0h8-h2h6)/det;
		h_inv[7]= -(h0h7-h1h6)/det;
		h_inv[2]=  (h1h5-h2h4)/det;
		h_inv[5]= -(h0h5-h2h3)/det;
		h_inv[8]=  (h0h4-h1h3)/det;
	}
	return(det);
	//for (int i=0; i<9; i++) { cout<<h_inv[i]<<" "; } cout<<endl;
}
void inv_3x3(float h_inv[9],float &det,float h_in[9])
{
	float inv_det;
	float h5h7, h4h8, h3h8,h5h6,h4h6,h3h7;
	float h1h8, h2h7, h0h8, h2h6, h0h7, h1h6, h1h5, h2h4, h0h5, h2h3, h0h4, h1h3;
	h4h8= h_in[4]*h_in[8]; h5h7=h_in[5]*h_in[7]; h3h8= h_in[3]*h_in[8]; 
	h5h6= h_in[5]*h_in[6]; h3h7= h_in[3]*h_in[7]; h4h6= h_in[4]*h_in[6]; 
	det= h_in[0]*(h4h8-h5h7)-h_in[1]*(h3h8-h5h6)+h_in[2]*(h3h7-h4h6);
	if (abs(det)<1e-6)
	{
		//cout<<"det==0"<<endl;
		//exit(0);
	}
	else
	{
		h1h8= h_in[1]*h_in[8];
		h2h7= h_in[2]*h_in[7];
		h0h8= h_in[0]*h_in[8]; 
		h2h6= h_in[2]*h_in[6]; 
		h0h7= h_in[0]*h_in[7];
		h1h6= h_in[1]*h_in[6]; 
		h1h5= h_in[1]*h_in[5];
		h2h4= h_in[2]*h_in[4];
		h0h5= h_in[0]*h_in[5];
		h2h3= h_in[2]*h_in[3];
		h0h4= h_in[0]*h_in[4];
		h1h3= h_in[1]*h_in[3];
		inv_det= 1.0f/det;
		h_inv[0]=  inv_det*(h4h8-h5h7);
		h_inv[3]= -inv_det*(h3h8-h5h6);
		h_inv[6]=  inv_det*(h3h7-h4h6);
		h_inv[1]= -inv_det*(h1h8-h2h7);
		h_inv[4]=  inv_det*(h0h8-h2h6);
		h_inv[7]= -inv_det*(h0h7-h1h6);
		h_inv[2]=  inv_det*(h1h5-h2h4);
		h_inv[5]= -inv_det*(h0h5-h2h3);
		h_inv[8]=  inv_det*(h0h4-h1h3);
	}
	//for (int i=0; i<9; i++) { cout<<h_inv[i]<<" "; } cout<<endl;
}
void qx_inv_3x3(double h_inv[9],double &det,double h_in[9])
{
	double inv_det;
	double h5h7, h4h8, h3h8,h5h6,h4h6,h3h7;
	double h1h8, h2h7, h0h8, h2h6, h0h7, h1h6, h1h5, h2h4, h0h5, h2h3, h0h4, h1h3;
	h4h8= h_in[4]*h_in[8]; h5h7=h_in[5]*h_in[7]; h3h8= h_in[3]*h_in[8]; 
	h5h6= h_in[5]*h_in[6]; h3h7= h_in[3]*h_in[7]; h4h6= h_in[4]*h_in[6]; 
	det= h_in[0]*(h4h8-h5h7)-h_in[1]*(h3h8-h5h6)+h_in[2]*(h3h7-h4h6);
	if (abs(det)<1e-6)
	{
		//cout<<"det==0"<<endl;
		//exit(0);
	}
	else
	{
		h1h8= h_in[1]*h_in[8];
		h2h7= h_in[2]*h_in[7];
		h0h8= h_in[0]*h_in[8]; 
		h2h6= h_in[2]*h_in[6]; 
		h0h7= h_in[0]*h_in[7];
		h1h6= h_in[1]*h_in[6]; 
		h1h5= h_in[1]*h_in[5];
		h2h4= h_in[2]*h_in[4];
		h0h5= h_in[0]*h_in[5];
		h2h3= h_in[2]*h_in[3];
		h0h4= h_in[0]*h_in[4];
		h1h3= h_in[1]*h_in[3];
		inv_det= 1.0f/det;
		h_inv[0]=  inv_det*(h4h8-h5h7);
		h_inv[3]= -inv_det*(h3h8-h5h6);
		h_inv[6]=  inv_det*(h3h7-h4h6);
		h_inv[1]= -inv_det*(h1h8-h2h7);
		h_inv[4]=  inv_det*(h0h8-h2h6);
		h_inv[7]= -inv_det*(h0h7-h1h6);
		h_inv[2]=  inv_det*(h1h5-h2h4);
		h_inv[5]= -inv_det*(h0h5-h2h3);
		h_inv[8]=  inv_det*(h0h4-h1h3);
	}
	//for (int i=0; i<9; i++) { cout<<h_inv[i]<<" "; } cout<<endl;
}
void qx_matrix_product_ata_3x3(float out[9],float at[9])
{
	out[0]=at[0]*at[0]+at[1]*at[1]+at[2]*at[2];
	out[1]=at[0]*at[3]+at[1]*at[4]+at[2]*at[5];
	out[2]=at[0]*at[6]+at[1]*at[7]+at[2]*at[8];
	
	out[3]=at[3]*at[0]+at[4]*at[1]+at[5]*at[2];
	out[4]=at[3]*at[3]+at[4]*at[4]+at[5]*at[5];
	out[5]=at[3]*at[6]+at[4]*at[7]+at[5]*at[8];
	
	out[6]=at[6]*at[0]+at[7]*at[1]+at[8]*at[2];
	out[7]=at[6]*at[3]+at[7]*at[4]+at[8]*at[5];
	out[8]=at[6]*at[6]+at[7]*at[7]+at[8]*at[8];
}
void qx_matrix_product_3x3_a(float out[9],float a[9],float b[9])
{
	out[0]=a[0]*b[0]+a[1]*b[3]+a[2]*b[6];
	out[1]=a[0]*b[1]+a[1]*b[4]+a[2]*b[7];
	out[2]=a[0]*b[2]+a[1]*b[5]+a[2]*b[8];
	
	out[3]=a[3]*b[0]+a[4]*b[3]+a[5]*b[6];
	out[4]=a[3]*b[1]+a[4]*b[4]+a[5]*b[7];
	out[5]=a[3]*b[2]+a[4]*b[5]+a[5]*b[8];
	
	out[6]=a[6]*b[0]+a[7]*b[3]+a[8]*b[6];
	out[7]=a[6]*b[1]+a[7]*b[4]+a[8]*b[7];
	out[8]=a[6]*b[2]+a[7]*b[5]+a[8]*b[8];
}
void qx_matrix_product_ata_3x3_a(double out[9],double a[9])
{
	out[0]=a[0]*a[0]+a[3]*a[3]+a[6]*a[6];
	out[1]=a[0]*a[1]+a[3]*a[4]+a[6]*a[7];
	out[2]=a[0]*a[2]+a[3]*a[5]+a[6]*a[8];
	out[3]=a[1]*a[0]+a[4]*a[3]+a[7]*a[6];
	out[4]=a[1]*a[1]+a[4]*a[4]+a[7]*a[7];
	out[5]=a[1]*a[2]+a[4]*a[5]+a[7]*a[8];
	out[6]=a[2]*a[0]+a[5]*a[3]+a[8]*a[6];
	out[7]=a[2]*a[1]+a[5]*a[4]+a[8]*a[7];
	out[8]=a[2]*a[2]+a[5]*a[5]+a[8]*a[8];
}
void qx_matrix_product_ata_3x3_at(double out[9],double at[9])
{
	out[0]=at[0]*at[0]+at[1]*at[1]+at[2]*at[2];
	out[1]=at[0]*at[3]+at[1]*at[4]+at[2]*at[5];
	out[2]=at[0]*at[6]+at[1]*at[7]+at[2]*at[8];
	
	out[3]=at[3]*at[0]+at[4]*at[1]+at[5]*at[2];
	out[4]=at[3]*at[3]+at[4]*at[4]+at[5]*at[5];
	out[5]=at[3]*at[6]+at[4]*at[7]+at[5]*at[8];
	
	out[6]=at[6]*at[0]+at[7]*at[1]+at[8]*at[2];
	out[7]=at[6]*at[3]+at[7]*at[4]+at[8]*at[5];
	out[8]=at[6]*at[6]+at[7]*at[7]+at[8]*at[8];
}
void qx_matrix_product_ata_3x3_at(float out[9],float at[9])
{
	out[0]=at[0]*at[0]+at[1]*at[1]+at[2]*at[2];
	out[1]=at[0]*at[3]+at[1]*at[4]+at[2]*at[5];
	out[2]=at[0]*at[6]+at[1]*at[7]+at[2]*at[8];
	
	out[3]=at[3]*at[0]+at[4]*at[1]+at[5]*at[2];
	out[4]=at[3]*at[3]+at[4]*at[4]+at[5]*at[5];
	out[5]=at[3]*at[6]+at[4]*at[7]+at[5]*at[8];
	
	out[6]=at[6]*at[0]+at[7]*at[1]+at[8]*at[2];
	out[7]=at[6]*at[3]+at[7]*at[4]+at[8]*at[5];
	out[8]=at[6]*at[6]+at[7]*at[7]+at[8]*at[8];
}
void qx_matrix_product_3x3(double out[9],double a[9],double b[9])
{
	out[0]=a[0]*b[0]+a[1]*b[3]+a[2]*b[6];
	out[1]=a[0]*b[1]+a[1]*b[4]+a[2]*b[7];
	out[2]=a[0]*b[2]+a[1]*b[5]+a[2]*b[8];
	
	out[3]=a[3]*b[0]+a[4]*b[3]+a[5]*b[6];
	out[4]=a[3]*b[1]+a[4]*b[4]+a[5]*b[7];
	out[5]=a[3]*b[2]+a[4]*b[5]+a[5]*b[8];
	
	out[6]=a[6]*b[0]+a[7]*b[3]+a[8]*b[6];
	out[7]=a[6]*b[1]+a[7]*b[4]+a[8]*b[7];
	out[8]=a[6]*b[2]+a[7]*b[5]+a[8]*b[8];
}

	
void Accumulate(float **InMat, int H, int W, float**OutMat)
{
	int i,j,i_1,j_1;
	for (i=0; i<H; i++)
		for (j=0; j<W; j++)
			OutMat[i][j]= 0;
	OutMat[0][0]= InMat[0][0];
	for (i=1; i<H; i++)
		OutMat[i][0]= OutMat[i-1][0]+InMat[i][0];	
	for (j=1; j<W; j++)
		OutMat[0][j]= OutMat[0][j-1]+InMat[0][j];
	for (i=1; i<H; i++)
	{
		for (j=1; j<W; j++)
		{
			i_1= i-1; j_1= j-1;
			OutMat[i][j]= OutMat[i_1][j]+OutMat[i][j_1]-OutMat[i_1][j_1]+InMat[i][j];
		}
	}	
	//for (i=0; i<H; i++) { for (j=0; j<W; j++) {	cout<<OutMat[i][j]<<" "; } cout<<endl; }
}
//binomial
int get_binomial_elem(int n,int m)
{
	if (m==0||m==n)
		return 1;
	else 
		return get_binomial_elem(n-1,m-1)+get_binomial_elem(n-1,m);
}
void get_binomial_array(int *bin, int len)
{
	bin[0]= 1; 
	bin[len-1]= 1;
	int len2=len/2+1;
	for (int m=1; m<len2; m++)
	{
		bin[m]= get_binomial_elem(len-1, m);
		bin[len-1-m]= bin[m];
	}
}
void get_binomial_matrix(int **out, int len)
{
	int *bin,n,m,t,len2= len/2+1,inv_m,inv_n;
	bin = new int [len];
	get_binomial_array(bin, len);
	for (m=0; m<len; m++)
	{
		t= bin[m];
		out[0][m]= t;
		out[len-1][m]= t;
		out[m][0]= t;
		out[m][len-1]=t;
	}
	for (n=1; n<len2; n++)
	{
		for (m=n; m<len2; m++)
		{
			t= out[n][n-1]+out[n-1][m];
			inv_m= len-1-m;
			inv_n= len-1-n;
			out[n][m]= t;
			out[n][inv_m]= t;
			out[inv_n][m]= t;
			out[inv_n][inv_m]= t;			
			out[m][n]= t;
			out[inv_m][n]= t;
			out[m][inv_n]= t;
			out[inv_m][inv_n]= t;
		}
	}
}

void get_binomial_matrix_coef(float **out,int **t_out,int len)
{
	int y,x; float sum=0;
	get_binomial_matrix(t_out,len);
	for(y=0;y<len;y++)
		for(x=0;x<len;x++)
			sum+=t_out[y][x];
	for(y=0;y<len;y++)
		for(x=0;x<len;x++)
			out[y][x]=float(t_out[y][x])/sum;
}
//image smooth
void img_smooth_3x3(float **img_in, int h, int w)
{
	float **img_out=qx_allocf(h,w);
	float mask[9]={1,2,1,2,4,2,1,2,1};
	int i,j;
	for (i=1; i<h-1; i++)
	{
		for (j=1; j<w-1; j++)
		{
			img_out[i][j]= img_in[i-1][j-1]*mask[0]+img_in[i-1][j]*mask[1]+img_in[i-1][j+1]*mask[2]
			+img_in[i][j-1]*mask[3]+img_in[i][j]*mask[4]+img_in[i][j+1]*mask[5]
			+img_in[i+1][j-1]*mask[6]+img_in[i+1][j]*mask[7]+img_in[i+1][j+1]*mask[8];
			img_out[i][j]=(img_out[i][j]*0.0625f);
		}
	}	
	for (i=1; i<h-1; i++)
		for (j=1; j<w-1; j++)
			img_in[i][j]=img_out[i][j];
	qx_freef(img_out);
}
void img_smooth_3x3_shift(unsigned char **image,int h,int w)
{
	int y,x; unsigned char *image_y,*image_y2,*image_y1;
	for(y=0;y<h;y++)
	{
		image_y=image[y];
		for(x=0;x<w-2;x++)
		{
			*image_y=(((*image_y+*(image_y+1)+*(image_y+1)+*(image_y+2)))>>2);
			image_y++;
		}
	}
	for(y=0;y<h-2;y++)
	{
		image_y=image[y];
		image_y1=image[y+1];
		image_y2=image[y+2];
		for(x=0;x<w;x++)
		{
			*image_y=(((*image_y)+(*image_y1)+(*image_y1)+(*image_y2))>>2);
			image_y++; image_y1++; image_y2++;
		}
	}
}
void img_smooth_121(unsigned char **image,int h,int w)
{
	img_smooth_3x3_shift(image,h,w);
}
void img_smooth_121(unsigned char ***image,int h,int w)
{
	int y,x; unsigned char *image_y,*image_y2,*image_y1;
	for(y=0;y<h;y++)
	{
		image_y=image[y][0];
		for(x=0;x<w-2;x++)
		{
			*image_y=(((*image_y+*(image_y+3)+*(image_y+3)+*(image_y+6)))>>2); image_y++;
			*image_y=(((*image_y+*(image_y+3)+*(image_y+3)+*(image_y+6)))>>2); image_y++;
			*image_y=(((*image_y+*(image_y+3)+*(image_y+3)+*(image_y+6)))>>2); image_y++;
		}
	}
	for(y=0;y<h-2;y++)
	{
		image_y=image[y][0];
		image_y1=image[y+1][0];
		image_y2=image[y+2][0];
		for(x=0;x<w;x++)
		{
			*image_y=(((*image_y)+(*image_y1)+(*image_y1)+(*image_y2))>>2); image_y++; image_y1++; image_y2++;
			*image_y=(((*image_y)+(*image_y1)+(*image_y1)+(*image_y2))>>2); image_y++; image_y1++; image_y2++;
			*image_y=(((*image_y)+(*image_y1)+(*image_y1)+(*image_y2))>>2); image_y++; image_y1++; image_y2++;
		}
	}
}
void img_smooth_14641_shift(unsigned char***image,int h,int w)
{
	int y,x; unsigned char*image_y,*image_y1,*image_y2,*image_y3,*image_y4;
	for(y=0;y<h;y++)
	{
		image_y=image[y][0];
		for(x=0;x<w-4;x++)
		{
			*image_y=(((*image_y+(*(image_y+3)<<2)+(*(image_y+6)<<1)+(*(image_y+6)<<2)+(*(image_y+9)<<2)+*(image_y+12)))>>4); image_y++;
			*image_y=(((*image_y+(*(image_y+3)<<2)+(*(image_y+6)<<1)+(*(image_y+6)<<2)+(*(image_y+9)<<2)+*(image_y+12)))>>4); image_y++;
			*image_y=(((*image_y+(*(image_y+3)<<2)+(*(image_y+6)<<1)+(*(image_y+6)<<2)+(*(image_y+9)<<2)+*(image_y+12)))>>4); image_y++;
		}
	}
	for(y=0;y<h-4;y++)
	{
		image_y=image[y][0];
		image_y1=image[y+1][0];
		image_y2=image[y+2][0];
		image_y3=image[y+3][0];
		image_y4=image[y+4][0];
		for(x=0;x<w;x++)
		{
			*image_y=(((*image_y)+((*image_y1)<<2)+((*image_y2)<<1)+((*image_y2)<<2)+((*image_y3)<<2)+((*image_y4)))>>4); 
			image_y++; image_y1++; image_y2++; image_y3++; image_y4++;
			*image_y=(((*image_y)+((*image_y1)<<2)+((*image_y2)<<1)+((*image_y2)<<2)+((*image_y3)<<2)+((*image_y4)))>>4); 
			image_y++; image_y1++; image_y2++; image_y3++; image_y4++;
			*image_y=(((*image_y)+((*image_y1)<<2)+((*image_y2)<<1)+((*image_y2)<<2)+((*image_y3)<<2)+((*image_y4)))>>4); 
			image_y++; image_y1++; image_y2++; image_y3++; image_y4++;
		}
	}
}
void img_smooth_14641_shift_rgb(unsigned char*image,int h,int w)
{
	int y,x; unsigned char*image_y,*image_y1,*image_y2,*image_y3,*image_y4;
	for(y=0;y<h;y++)
	{
		image_y=&image[y*w*3];
		for(x=0;x<w-4;x++)
		{
			*image_y=(((*image_y+(*(image_y+3)<<2)+(*(image_y+6)<<1)+(*(image_y+6)<<2)+(*(image_y+9)<<2)+*(image_y+12)))>>4); image_y++;
			*image_y=(((*image_y+(*(image_y+3)<<2)+(*(image_y+6)<<1)+(*(image_y+6)<<2)+(*(image_y+9)<<2)+*(image_y+12)))>>4); image_y++;
			*image_y=(((*image_y+(*(image_y+3)<<2)+(*(image_y+6)<<1)+(*(image_y+6)<<2)+(*(image_y+9)<<2)+*(image_y+12)))>>4); image_y++;
		}
	}
	for(y=0;y<h-4;y++)
	{
		image_y=&image[y*w*3];
		image_y1=&image[(y+1)*w*3];
		image_y2=&image[(y+2)*w*3];
		image_y3=&image[(y+3)*w*3];
		image_y4=&image[(y+4)*w*3];
		for(x=0;x<w;x++)
		{
			*image_y=(((*image_y)+((*image_y1)<<2)+((*image_y2)<<1)+((*image_y2)<<2)+((*image_y3)<<2)+((*image_y4)))>>4); 
			image_y++; image_y1++; image_y2++; image_y3++; image_y4++;
			*image_y=(((*image_y)+((*image_y1)<<2)+((*image_y2)<<1)+((*image_y2)<<2)+((*image_y3)<<2)+((*image_y4)))>>4); 
			image_y++; image_y1++; image_y2++; image_y3++; image_y4++;
			*image_y=(((*image_y)+((*image_y1)<<2)+((*image_y2)<<1)+((*image_y2)<<2)+((*image_y3)<<2)+((*image_y4)))>>4); 
			image_y++; image_y1++; image_y2++; image_y3++; image_y4++;
		}
	}
}
void img_smooth_14641(unsigned char***in,int h,int w)
{
	int y,x; unsigned char*out_y,*in_y;
	img_smooth_14641_shift(in,h,w);
	for(y=h-1;y>=2;y--)
	{
		out_y=&in[y][w-1][2]; in_y=&in[(y-2)][w-3][2];
		for(x=2;x<w;x++)
		{
			*out_y--=*in_y--; *out_y--=*in_y--; *out_y--=*in_y--;
		}
	}
}
void img_smooth_14641_shift(unsigned char**image,int h,int w)
{
	int y,x; unsigned char*image_y,*image_y1,*image_y2,*image_y3,*image_y4;
	for(y=0;y<h;y++)
	{
		image_y=image[y];
		for(x=0;x<w-4;x++)
		{
			*image_y=(((*image_y+(*(image_y+1)<<2)+(*(image_y+2)<<1)+(*(image_y+3)<<2)+(*(image_y+4)<<2)+*(image_y+5)))>>4); image_y++;
		}
	}
	for(y=0;y<h-4;y++)
	{
		image_y=image[y];
		image_y1=image[y+1];
		image_y2=image[y+2];
		image_y3=image[y+3];
		image_y4=image[y+4];
		for(x=0;x<w;x++)
		{
			*image_y=(((*image_y)+((*image_y1)<<2)+((*image_y2)<<1)+((*image_y2)<<2)+((*image_y3)<<2)+((*image_y4)))>>4); 
			image_y++; image_y1++; image_y2++; image_y3++; image_y4++;
		}
	}
}
void img_smooth_14641(unsigned char**in,int h,int w)
{
	int y,x; unsigned char*out_y,*in_y;
	img_smooth_14641_shift(in,h,w);
	for(y=h-1;y>=2;y--)
	{
		out_y=&in[y][w-1]; in_y=&in[(y-2)][w-3];
		for(x=2;x<w;x++) *out_y--=*in_y--; 
	}
}



void img_smooth_14641_shift(double***image,int h,int w)
{
	int y,x; double*image_y,*image_y1,*image_y2,*image_y3,*image_y4;
	for(y=0;y<h;y++)
	{
		image_y=image[y][0];
		for(x=0;x<w-4;x++)
		{
			*image_y=(((*image_y+(*(image_y+3)*4)+(*(image_y+6)*2)+(*(image_y+6)*4)+(*(image_y+9)*4)+*(image_y+12)))*0.0625); image_y++;
			*image_y=(((*image_y+(*(image_y+3)*4)+(*(image_y+6)*2)+(*(image_y+6)*4)+(*(image_y+9)*4)+*(image_y+12)))*0.0625); image_y++;
			*image_y=(((*image_y+(*(image_y+3)*4)+(*(image_y+6)*2)+(*(image_y+6)*4)+(*(image_y+9)*4)+*(image_y+12)))*0.0625); image_y++;
		}
	}
	for(y=0;y<h-4;y++)
	{
		image_y=image[y][0];
		image_y1=image[y+1][0];
		image_y2=image[y+2][0];
		image_y3=image[y+3][0];
		image_y4=image[y+4][0];
		for(x=0;x<w;x++)
		{
			*image_y=(((*image_y)+((*image_y1)*4)+((*image_y2)*2)+((*image_y2)*4)+((*image_y3)*4)+((*image_y4)))*0.0625); 
			image_y++; image_y1++; image_y2++; image_y3++; image_y4++;
			*image_y=(((*image_y)+((*image_y1)*4)+((*image_y2)*2)+((*image_y2)*4)+((*image_y3)*4)+((*image_y4)))*0.0625); 
			image_y++; image_y1++; image_y2++; image_y3++; image_y4++;
			*image_y=(((*image_y)+((*image_y1)*4)+((*image_y2)*2)+((*image_y2)*4)+((*image_y3)*4)+((*image_y4)))*0.0625); 
			image_y++; image_y1++; image_y2++; image_y3++; image_y4++;
		}
	}
}
void img_smooth_14641(double***in,int h,int w)
{
	int y,x; double*out_y,*in_y;
	img_smooth_14641_shift(in,h,w);
	for(y=h-1;y>=2;y--)
	{
		out_y=&in[y][w-1][2]; in_y=&in[(y-2)][w-3][2];
		for(x=2;x<w;x++)
		{
			*out_y--=*in_y--; *out_y--=*in_y--; *out_y--=*in_y--;
		}
	}
}
void img_smooth_14641_shift(double**image,int h,int w)
{
	int y,x; double*image_y,*image_y1,*image_y2,*image_y3,*image_y4;
	for(y=0;y<h;y++)
	{
		image_y=image[y];
		for(x=0;x<w-4;x++)
		{
			*image_y=(((*image_y+(*(image_y+1)*4)+(*(image_y+2)*2)+(*(image_y+3)*4)+(*(image_y+4)*4)+*(image_y+5)))*0.0625); image_y++;
		}
	}
	for(y=0;y<h-4;y++)
	{
		image_y=image[y];
		image_y1=image[y+1];
		image_y2=image[y+2];
		image_y3=image[y+3];
		image_y4=image[y+4];
		for(x=0;x<w;x++)
		{
			*image_y=(((*image_y)+((*image_y1)*4)+((*image_y2)*2)+((*image_y2)*4)+((*image_y3)*4)+((*image_y4)))*0.0625); 
			image_y++; image_y1++; image_y2++; image_y3++; image_y4++;
		}
	}
}
void img_smooth_14641(double**in,int h,int w)
{
	int y,x; double*out_y,*in_y;
	img_smooth_14641_shift(in,h,w);
	for(y=h-1;y>=2;y--)
	{
		out_y=&in[y][w-1]; in_y=&in[(y-2)][w-3];
		for(x=2;x<w;x++) *out_y--=*in_y--; 
	}
}
void img_smooth_3x3_rgb(float ***img_in_rgb, int h, int w)
{
	float ***img_out=qx_allocf_3(h,w,3);
	float mask[9]={1,2,1,2,4,2,1,2,1};
	int i,j,k;
	for (i=1; i<h-1; i++)
		for (j=1; j<w-1; j++)
			for(k=0;k<3;k++)
			{
				img_out[i][j][k]=img_in_rgb[i-1][j-1][k]*mask[0]+img_in_rgb[i-1][j][k]*mask[1]+img_in_rgb[i-1][j+1][k]*mask[2]
				+img_in_rgb[i][j-1][k]*mask[3]+img_in_rgb[i][j][k]*mask[4]+img_in_rgb[i][j+1][k]*mask[5]
				+img_in_rgb[i+1][j-1][k]*mask[6]+img_in_rgb[i+1][j][k]*mask[7]+img_in_rgb[i+1][j+1][k]*mask[8];
				img_out[i][j][k]= float(int(img_out[i][j][k]*0.0625));
			}
	for (i=1; i<h-1; i++)
		for (j=1; j<w-1; j++)
			for(k=0;k<3;k++)
				img_in_rgb[i][j][k]=img_out[i][j][k];
	qx_freef_3(img_out);
}

void img_smooth_nxn(float **img_in,int h,int w,int len)
{
	//imdebug("lum *auto b=32f w=%d h=%d %p",w,h,&img_in[0][0]);
	float len_correct=float(len)/2-len/2;
	if(len_correct<0.1)
	{
		printf("The size of the smooth window should be n=2k+1!!\n");
		exit(0);
	}
	float **img_out=qx_allocf(h,w);
	int **mask= qx_alloci(len,len);
	get_binomial_matrix(mask,len);
	int i,j,n,m,h_first,h_last,w_first,w_last,len2= len/2;
	float multi_para= 0;
	for (i=0; i<len; i++)
		for (j=0; j<len; j++)
			multi_para+= mask[i][j];
	multi_para= (1.0f)/multi_para;
	h_first= len2;
	w_first= len2;
	h_last= h-len2;
	w_last= w-len2;
	float sumup;
	for (i=h_first; i<h_last; i++)
	{
		for (j=w_first; j<w_last; j++)
		{
			sumup= 0;
			for (n=-len2; n<=len2; n++)
			{
				for (m=-len2; m<=len2; m++)
				{
					sumup+=img_in[i+n][j+m]*mask[n+len2][m+len2];
				}
			}
			//img_out[i][j]= float(int(sumup*multi_para));
			img_out[i][j]=sumup*multi_para;
		}
	}
	for (i=h_first; i<h_last; i++)
		for (j=w_first; j<w_last; j++)
			img_in[i][j]=img_out[i][j];
	qx_freef(img_out);
}
void img_smooth_nxn(float ***img_in,int h,int w,int len)
{

	float len_correct,multi_para,sumup[3],***img_out;
	int **mask,i,j,d,n,m,h_first,h_last,w_first,w_last,len2= len/2;

	img_out=qx_allocf_3(h,w,3);
	mask= qx_alloci(len,len);
	len_correct=float(len)/2-len/2;
	len2=(len>>1); multi_para=0;
	if(len_correct<0.1)
	{
		printf("The size of the smooth window should be n=2k+1!!\n");
		exit(0);
	}
	get_binomial_matrix(mask,len);
	for (i=0; i<len; i++)
		for (j=0; j<len; j++)
			multi_para+= mask[i][j];
	multi_para=(1.0f)/multi_para;
	h_first= len2;
	w_first= len2;
	h_last= h-len2;
	w_last= w-len2;
	for (i=h_first; i<h_last; i++)
	{
		for (j=w_first; j<w_last; j++)
		{
			sumup[0]=sumup[1]=sumup[2]=0;
			for (n=-len2; n<=len2; n++)
			{
				for (m=-len2; m<=len2; m++)
				{
					for(d=0;d<3;d++) sumup[d]+=img_in[i+n][j+m][d]*mask[n+len2][m+len2];
				}
			}
			//img_out[i][j]= float(int(sumup*multi_para));
			for(d=0;d<3;d++) img_out[i][j][d]=sumup[d]*multi_para;
		}
	}
	for (i=h_first; i<h_last; i++)
		for (j=w_first; j<w_last; j++)
			for(d=0;d<3;d++) img_in[i][j][d]=img_out[i][j][d];
	qx_freef_3(img_out);
}
void img_boxcar_odd(float **in,int h,int w,int win_size)
{
	int half=win_size/2,half2=half*2,bh,bw,y,x; float box_size,box_size_inv,**box,*box1,*box2;
	bh=h+win_size; bw=w+win_size; box_size=(float)win_size*win_size; box_size_inv=1.0f/box_size;

	box=qx_allocf(bh,bw);
	memset(box[0],0,sizeof(float)*bh*bw);
	for(y=0;y<h;y++) memcpy(&box[y+half+1][half+1],in[y],sizeof(float)*w);
	
	//for(y=0;y<bh;y++)
	//{
	//	for(x=0;x<bw;x++)
	//		printf("%1.1f ",box[y][x]);
	//	printf("\n");
	//}
	for(y=1;y<bh;y++)
	{
		box2=box[y-1]; box1=box[y];
		for(x=1;x<bw;x++)
		{
			box1[x]+=box2[x]+box1[x-1]-box2[x-1];
		}
	}
	for(y=0;y<h;y++)
	{
		for(x=0;x<w;x++)
		{
			in[y][x]=(box[y+win_size][x+win_size]+box[y][x]-box[y+win_size][x]-box[y][x+win_size])*box_size_inv;
		}
	}
	//for(y=0;y<bh;y++)
	//{
	//	for(x=0;x<bw;x++)
	//		printf("%1.1f ",box[y][x]);
	//	printf("\n");
	//}
	qx_freef(box);
}
void img_boxcar_odd(double **in,int h,int w,int win_size)
{
	int half=win_size/2,half2=half*2,bh,bw,y,x; double box_size,box_size_inv,**box,*box1,*box2;
	bh=h+win_size; bw=w+win_size; box_size=(double)win_size*win_size; box_size_inv=1.0/box_size;

	box=qx_allocd(bh,bw);
	memset(box[0],0,sizeof(double)*bh*bw);
	for(y=0;y<h;y++) memcpy(&box[y+half+1][half+1],in[y],sizeof(double)*w);	
	for(y=1;y<bh;y++)
	{
		box2=box[y-1]; box1=box[y];
		for(x=1;x<bw;x++)
		{
			box1[x]+=box2[x]+box1[x-1]-box2[x-1];
		}
	}
	for(y=0;y<h;y++)
	{
		for(x=0;x<w;x++)
		{
			in[y][x]=(box[y+win_size][x+win_size]+box[y][x]-box[y+win_size][x]-box[y][x+win_size])*box_size_inv;
		}
	}
	qx_freed(box);
}
void img_boxcar_odd(int **in,int h,int w,int win_size)
{
	int half=(win_size>>1),half2=half*2,bh,bw,y,x; double box_size,box_size_inv,**box,*box1,*box2;
	bh=h+win_size; bw=w+win_size; box_size=(double)win_size*win_size; box_size_inv=1.0/box_size;

	box=qx_allocd(bh,bw);
	memset(box[0],0,sizeof(double)*bh*bw);
	for(y=0;y<h;y++) for(int x=0;x<w;x++) box[y+half+1][x+half+1]=(double)in[y][x];
	for(y=1;y<bh;y++)
	{
		box2=box[y-1]; box1=box[y];
		for(x=1;x<bw;x++)
		{
			box1[x]+=box2[x]+box1[x-1]-box2[x-1];
		}
	}
	for(y=0;y<h;y++)
	{
		for(x=0;x<w;x++)
		{
			in[y][x]=int((box[y+win_size][x+win_size]+box[y][x]-box[y+win_size][x]-box[y][x+win_size])*box_size_inv+0.5);
		}
	}
	qx_freed(box);
}
void img_boxcar_odd(unsigned char **in,double **box,int h,int w,int win_size)
{
	int half=(win_size>>1),half2=half*2,bh,bw,y,x; double box_size,box_size_inv,*box1,*box2;
	bh=h+win_size; bw=w+win_size; box_size=(double)win_size*win_size; box_size_inv=1.0/box_size;
	memset(box[0],0,sizeof(double)*bh*bw);
	for(y=0;y<h;y++) for(int x=0;x<w;x++)box[y+half+1][x+half+1]=(double)in[y][x];
	for(y=1;y<bh;y++)
	{
		box2=box[y-1]; box1=box[y];
		for(x=1;x<bw;x++)
		{
			box1[x]+=box2[x]+box1[x-1]-box2[x-1];
		}
	}
	for(y=0;y<h;y++)
	{
		for(x=0;x<w;x++)
		{
			in[y][x]=unsigned char((box[y+win_size][x+win_size]+box[y][x]-box[y+win_size][x]-box[y][x+win_size])*box_size_inv+0.5);
		}
	}
}
void img_boxcar_odd(float**in,double **box,int **nr_valid,int h,int w,int win_size)
{
	int half=(win_size>>1),half2=half*2,bh,bw,y,x; double box_size_inv,*box1,*box2; int *nr_valid1,*nr_valid2;
	bh=h+win_size; bw=w+win_size; box_size_inv=1.0/(win_size*win_size);
	memset(box[0],0,sizeof(double)*bh*bw);
	memset(nr_valid[0],0,sizeof(int)*bh*bw);
	for(y=0;y<h;y++) for(int x=0;x<w;x++) box[y+half+1][x+half+1]=(double)in[y][x];
	for(y=1;y<bh;y++)
	{
		box2=box[y-1]; box1=box[y];
		for(x=1;x<bw;x++)
		{
			box1[x]+=box2[x]+box1[x-1]-box2[x-1];
		}
	}	
	for(y=0;y<h;y++) for(int x=0;x<w;x++)
		if(in[y][x]==0) nr_valid[y+half+1][x+half+1]=0;
		else nr_valid[y+half+1][x+half+1]=1;
	for(y=1;y<bh;y++)
	{
		nr_valid2=nr_valid[y-1]; nr_valid1=nr_valid[y];
		for(x=1;x<bw;x++)
		{
			nr_valid1[x]+=nr_valid2[x]+nr_valid1[x-1]-nr_valid2[x-1];
		}
	}	
	for(y=0;y<h;y++)
	{
		for(x=0;x<w;x++)
		{
			int nr=nr_valid[y+win_size][x+win_size]+nr_valid[y][x]-nr_valid[y+win_size][x]-nr_valid[y][x+win_size];
			if(nr>1&&in[y][x]!=0)
			{
				in[y][x]=float(double(box[y+win_size][x+win_size]+box[y][x]-box[y+win_size][x]-box[y][x+win_size])/nr);
			}
		}
	}
}
void img_boxcar_odd(float **in,double **box,int h,int w,int win_size)
{
	int half=(win_size>>1),half2=half*2,bh,bw,y,x; double box_size,box_size_inv,*box1,*box2;
	bh=h+win_size; bw=w+win_size; box_size=(double)win_size*win_size; box_size_inv=1.0/box_size;

	//box=qx_allocd(bh,bw);
	memset(box[0],0,sizeof(double)*bh*bw);
	for(y=0;y<h;y++) for(int x=0;x<w;x++) box[y+half+1][x+half+1]=(double)in[y][x];
	for(y=1;y<bh;y++)
	{
		box2=box[y-1]; box1=box[y];
		for(x=1;x<bw;x++)
		{
			box1[x]+=box2[x]+box1[x-1]-box2[x-1];
		}
	}
	for(y=0;y<h;y++)
	{
		for(x=0;x<w;x++)
		{
			in[y][x]=float((box[y+win_size][x+win_size]+box[y][x]-box[y+win_size][x]-box[y][x+win_size])*box_size_inv);
		}
	}
	//qx_freed(box);
}
void img_boxcar_odd(double **in,double **box,int h,int w,int win_size)
{
	int half=(win_size>>1),half2=half*2,bh,bw,y,x; double box_size,box_size_inv,*box1,*box2;
	bh=h+win_size; bw=w+win_size; box_size=(double)win_size*win_size; box_size_inv=1.0/box_size;

	//box=qx_allocd(bh,bw);
	memset(box[0],0,sizeof(double)*bh*bw);
	for(y=0;y<h;y++) for(int x=0;x<w;x++) box[y+half+1][x+half+1]=(double)in[y][x];
	for(y=1;y<bh;y++)
	{
		box2=box[y-1]; box1=box[y];
		for(x=1;x<bw;x++)
		{
			box1[x]+=box2[x]+box1[x-1]-box2[x-1];
		}
	}
	for(y=0;y<h;y++)
	{
		for(x=0;x<w;x++)
		{
			in[y][x]=(box[y+win_size][x+win_size]+box[y][x]-box[y+win_size][x]-box[y][x+win_size])*box_size_inv;
		}
	}
	//qx_freed(box);
}
//image gradient
void img_grad(float **img_in, int h, int w)
{
	
	float mask_x[6]={1,-1,2,-2,1,-1}, mask_y[6]= {1,2,1,-1,-2,-1};
	float **img_x, **img_y;
	img_x= qx_allocf(h,w);
	img_y= qx_allocf(h,w);
	memset(img_x[0],0,h*w);
	memset(img_y[0],0,h*w);
	int i,j;


	for (i=1; i<h-1; i++)
	{
		for (j=1; j<w-1; j++)
		{
			img_x[i][j]= img_in[i-1][j-1]*mask_x[0]+img_in[i-1][j+1]*mask_x[1]
						+img_in[i][j-1]*mask_x[2]+img_in[i][j+1]*mask_x[3]
						+img_in[i+1][j-1]*mask_x[4]+img_in[i+1][j+1]*mask_x[5];
			img_x[i][j]*=0.25;

		}
	}

	for (i=1; i<h-1; i++)
	{
		for (j=1; j<w-1; j++)
		{
			img_y[i][j]= img_in[i-1][j-1]*mask_y[0]+img_in[i-1][j]*mask_y[1]+img_in[i-1][j+1]*mask_y[2]
						+img_in[i+1][j-1]*mask_y[3]+img_in[i+1][j]*mask_y[4]+img_in[i+1][j+1]*mask_y[5];
			img_y[i][j]*=0.25;
		}
	}
	
	for (i=0; i<h; i++)
	{
		img_x[i][0]		= img_in[i][0]-img_in[i][1];
		img_y[i][0]		= img_x[i][0];
		img_x[i][w-1]	= img_in[i][w-1]-img_in[i][w-2];
		img_y[i][w-1]	= img_x[i][w-1];
	}
	for (j=0; j<w; j++)
	{
		img_x[0][j]		= img_in[0][j]- img_in[1][j];
		img_x[h-1][j]	= img_in[h-1][j]- img_in[h-1][j];
		img_y[0][j]		= img_x[0][j];
		img_y[h-1][j]	= img_x[h-1][j];
	}
	for (i=0; i<h; i++)
		for (j=0; j<w; j++) 
		{
			img_in[i][j]= (float)int(sqrt(img_x[i][j]*img_x[i][j]+img_y[i][j]*img_y[i][j])*(0.707F));
		}
	qx_freef(img_x);
	qx_freef(img_y);
	
}
void qx_image_gradient_xy(unsigned char***gradients,unsigned char***image,int h,int w)
{
	int y,x; unsigned char dxr,dxg,dxb,dyr,dyg,dyb;
	unsigned char *rgb0,*rgb_down,*rgb_right;
	for (y=0; y<h-1; y++)
	{
		for (x=0; x<w-1; x++) 
		{
			rgb0=image[y][x]; rgb_down=image[y+1][x]; rgb_right=image[y][x+1];
			dxr=abs(rgb0[0]-rgb_right[0]); dxg=abs(rgb0[1]-rgb_right[1]); dxb=abs(rgb0[2]-rgb_right[2]);
			dyr=abs(rgb0[0]-rgb_down[0]); dyg=abs(rgb0[1]-rgb_down[1]); dyb=abs(rgb0[2]-rgb_down[2]);
			gradients[y][x][0]=max(max(dxr,dxg),dxb);
			gradients[y][x][1]=max(max(dyr,dyg),dyb);
		}
	}
}
void qx_image_gradient_xy(unsigned char***gradients,unsigned char**image,int h,int w)
{
	for(int y=0;y<h-1;y++)
	{
		for(int x=0;x<w-1;x++) 
		{
			gradients[y][x][0]=abs(image[y][x]-image[y][x+1]);
			gradients[y][x][1]=abs(image[y][x]-image[y+1][x]);
		}
	}
}
void untexture_search(unsigned char**untexture,unsigned char***gradients,unsigned char ***image,unsigned char max_grad,int h,int w)
{
	int y,x,d; unsigned char dr,dg,db;
	unsigned char *rgb0; int grad;
	unsigned char **rgb_xy= new unsigned char *[8];
	memset(untexture[0],0,sizeof(unsigned char)*h*w);
	for (y=1; y<h-1; y++)
	{
		for (x=1; x<w-1; x++) 
		{
			rgb_xy[0]=image[y-1][x-1]; rgb_xy[1]=image[y-1][x]; rgb_xy[2]=image[y-1][x+1];
			rgb_xy[3]=image[y][x-1]; rgb0=image[y][x]; rgb_xy[4]=image[y][x+1];
			rgb_xy[5]=image[y+1][x-1]; rgb_xy[6]=image[y+1][x]; rgb_xy[7]=image[y+1][x+1];
			grad=0;
			for(d=0;d<8;d++)
			{
				dr=abs(rgb_xy[d][0]-rgb0[0]); 
				dg=abs(rgb_xy[d][1]-rgb0[1]); 
				db=abs(rgb_xy[d][2]-rgb0[2]);
				gradients[y][x][d]=max(max(dr,dg),db);
				grad+=gradients[y][x][d];
			}
			grad/=8;
			if(grad<max_grad) untexture[y][x]=1;
		}
	}
	delete [] rgb_xy;
}

void qx_image_gradient_8_neighbor(unsigned char***gradients,unsigned char ***image,int h,int w)
{
	int y,x,d; unsigned char dr,dg,db;
	unsigned char *rgb0; int grad;
	unsigned char **rgb_xy= new unsigned char *[8];
	for (y=1; y<h-1; y++)
	{
		for (x=1; x<w-1; x++) 
		{
			rgb_xy[0]=image[y-1][x-1]; rgb_xy[1]=image[y-1][x]; rgb_xy[2]=image[y-1][x+1];
			rgb_xy[3]=image[y][x-1]; rgb0=image[y][x]; rgb_xy[4]=image[y][x+1];
			rgb_xy[5]=image[y+1][x-1]; rgb_xy[6]=image[y+1][x]; rgb_xy[7]=image[y+1][x+1];
			grad=0;
			for(d=0;d<8;d++)
			{
				dr=abs(rgb_xy[d][0]-rgb0[0]); 
				dg=abs(rgb_xy[d][1]-rgb0[1]); 
				db=abs(rgb_xy[d][2]-rgb0[2]);
				gradients[y][x][d]=max(max(dr,dg),db);
				grad+=gradients[y][x][d];
			}
			grad/=8;
		}
	}
	delete [] rgb_xy;
}
void image_gradient_back(float ***gradient,unsigned char ***image,int h,int w)
{
	float **gradient_y,*gradient_x; unsigned char **image_y,*image_x,**image_y1,*image_x1,*image_y1x;
	for(int y=0;y<h-1;y++) 
	{
		gradient_y=gradient[y]; image_y=image[y];
		image_y1=image[y+1];
		for(int x=0;x<w-1;x++)
		{
			gradient_x=gradient_y[x]; image_x=image_y[x];
			image_x1=image_y[x+1]; image_y1x=image_y1[x];
			gradient_x[0]=float(image_x1[0]-image_x[0]); gradient_x[1]=float(image_y1x[0]-image_x[0]);
			gradient_x[2]=float(image_x1[1]-image_x[1]); gradient_x[3]=float(image_y1x[1]-image_x[1]);
			gradient_x[4]=float(image_x1[2]-image_x[2]); gradient_x[5]=float(image_y1x[2]-image_x[2]);
		}
	}
}
void image_gradient_back(float ***gradient,float ***image,int h,int w)
{
	float **gradient_y,*gradient_x,**image_y,*image_x,**image_y1,*image_x1,*image_y1x;
	for(int y=0;y<h-1;y++) 
	{
		gradient_y=gradient[y]; image_y=image[y];
		image_y1=image[y+1];
		for(int x=0;x<w-1;x++)
		{
			gradient_x=gradient_y[x]; image_x=image_y[x];
			image_x1=image_y[x+1]; image_y1x=image_y1[x];
			gradient_x[0]=image_x1[0]-image_x[0]; gradient_x[1]=image_y1x[0]-image_x[0];
			gradient_x[2]=image_x1[1]-image_x[1]; gradient_x[3]=image_y1x[1]-image_x[1];
			gradient_x[4]=image_x1[2]-image_x[2]; gradient_x[5]=image_y1x[2]-image_x[2];
		}
	}
}
void image_divergence_forward(float ***image,float ***gradient,int h,int w,bool is_calc_gradient)
{
	float **image_y,*image_x,**gradient_y,*gradient_x,**gradient_y1,*gradient_x1,*gradient_y1x;
	memset(gradient[0][0],0,sizeof(float)*h*w*6);
	if(is_calc_gradient) image_gradient_back(gradient,image,h,w);	
	for(int y=1;y<h;y++) 
	{
		image_y=image[y]; gradient_y=gradient[y];
		gradient_y1=gradient[y-1];
		for(int x=1;x<w;x++)
		{
			image_x=image_y[x]; gradient_x=gradient_y[x]; gradient_x1=gradient_y[x-1]; gradient_y1x=gradient_y1[x];
			image_x[0]=gradient_x[0]-gradient_x1[0]+gradient_x[1]-gradient_y1x[1];
			image_x[1]=gradient_x[2]-gradient_x1[2]+gradient_x[3]-gradient_y1x[3];
			image_x[2]=gradient_x[4]-gradient_x1[4]+gradient_x[5]-gradient_y1x[5];
		}
	}
}
void image_divergence_forward(float ***div,float ***gradient,unsigned char ***image,int h,int w)
{
	float **gradient_y,*gradient_x,**gradient_y1,*gradient_x1,*gradient_y1x;
	float **div_y,*div_x;
	image_gradient_back(gradient,image,h,w);	
	for(int y=1;y<h;y++) 
	{
		div_y=div[y]; gradient_y=gradient[y];
		gradient_y1=gradient[y-1];
		for(int x=1;x<w;x++)
		{
			div_x=div_y[x]; gradient_x=gradient_y[x]; gradient_x1=gradient_y[x-1]; gradient_y1x=gradient_y1[x];
			div_x[0]=gradient_x[0]-gradient_x1[0]+gradient_x[1]-gradient_y1x[1];
			div_x[1]=gradient_x[2]-gradient_x1[2]+gradient_x[3]-gradient_y1x[3];
			div_x[2]=gradient_x[4]-gradient_x1[4]+gradient_x[5]-gradient_y1x[5];
		}
	}
}
void image_gradient_back(float ***gradient,float **image,int h,int w)
{
	float **gradient_y,*gradient_x,*image_y,image_x,*image_y1,image_x1,image_y1x;
	for(int y=0;y<h-1;y++) 
	{
		gradient_y=gradient[y]; image_y=image[y];
		image_y1=image[y+1];
		for(int x=0;x<w-1;x++)
		{
			gradient_x=gradient_y[x]; image_x=image_y[x];
			image_x1=image_y[x+1]; image_y1x=image_y1[x];
			gradient_x[0]=image_x1-image_x; gradient_x[1]=image_y1x-image_x;
		}
	}
}
void image_gradient_back(float ***gradient,unsigned char **image,int h,int w)
{
	float **gradient_y,*gradient_x; unsigned char *image_y,image_x,*image_y1,image_x1,image_y1x;
	for(int y=0;y<h-1;y++) 
	{
		gradient_y=gradient[y]; image_y=image[y];
		image_y1=image[y+1];
		for(int x=0;x<w-1;x++)
		{
			gradient_x=gradient_y[x]; image_x=image_y[x];
			image_x1=image_y[x+1]; image_y1x=image_y1[x];
			gradient_x[0]=float(image_x1-image_x); gradient_x[1]=float(image_y1x-image_x);
		}
	}
}
void image_divergence_forward(float **image,float ***gradient,int h,int w,bool is_calc_gradient)
{
	float *image_y,**gradient_y,*gradient_x,**gradient_y1,*gradient_x1,*gradient_y1x;
	if(is_calc_gradient) image_gradient_back(gradient,image,h,w);	
	for(int y=1;y<h;y++) 
	{
		image_y=image[y]; gradient_y=gradient[y];
		gradient_y1=gradient[y-1];
		for(int x=1;x<w;x++)
		{
			gradient_x=gradient_y[x]; gradient_x1=gradient_y[x-1]; gradient_y1x=gradient_y1[x];
			image_y[x]=gradient_x[0]-gradient_x1[0]+gradient_x[1]-gradient_y1x[1];
		}
	}
}
//void image_divergence_forward(unsigned char **image,float ***gradient,int h,int w,bool is_calc_gradient)
//{
//	unsigned char *image_y; float **gradient_y,*gradient_x,**gradient_y1,*gradient_x1,*gradient_y1x;
//	if(is_calc_gradient) image_gradient_back(gradient,image,h,w);	
//	for(int y=1;y<h;y++) 
//	{
//		image_y=image[y]; gradient_y=gradient[y];
//		gradient_y1=gradient[y-1];
//		for(int x=1;x<w;x++)
//		{
//			gradient_x=gradient_y[x]; gradient_x1=gradient_y[x-1]; gradient_y1x=gradient_y1[x];
//			image_y[x]=gradient_x[0]-gradient_x1[0]+gradient_x[1]-gradient_y1x[1];
//		}
//	}
//}
void image_divergence_forward_without_gradient(float **image,float ***gradient,int h,int w)
{
	float *image_y,**gradient_y,*gradient_x,**gradient_y1,*gradient_x1,*gradient_y1x;
	for(int y=1;y<h;y++) 
	{
		image_y=image[y]; gradient_y=gradient[y];
		gradient_y1=gradient[y-1];
		for(int x=1;x<w;x++)
		{
			gradient_x=gradient_y[x]; gradient_x1=gradient_y[x-1]; gradient_y1x=gradient_y1[x];
			image_y[x]=gradient_x[0]-gradient_x1[0]+gradient_x[1]-gradient_y1x[1];
		}
	}
}
void get_edges(unsigned char **out,float **in,int radius,float larger_equal,int h,int w)
{
	int y,x,ymin,ymax,xmin,xmax,yi,xi; float d1,d2,d3;
	memset(out[0],0,sizeof(unsigned char)*h*w);
	for(y=0;y<h-1;y++) 
	{
		ymin=max(0,y-radius); ymax=min(h-1,y+radius);
		for(x=0;x<w-1;x++)
		{
			d1=abs(in[y][x]-in[y][x+1]);
			d2=abs(in[y][x]-in[y+1][x]);
			d3=abs(in[y][x]-in[y+1][x+1]);
			if(d1>=larger_equal||d2>=larger_equal||d3>=larger_equal)
			{
				out[y][x]=1;
				xmin=max(0,x-radius); xmax=min(w-1,x+radius);
				for(yi=ymin;yi<=ymax;yi++) for(xi=xmin;xi<=xmax;xi++)
				{
					out[yi][xi]=255;
				}
			}
		}
	}
}
void get_edges(unsigned char **out,short**in,int radius,short larger_equal,int h,int w)
{
	int y,x,ymin,ymax,xmin,xmax,yi,xi; short d1,d2,d3;
	memset(out[0],0,sizeof(unsigned char)*h*w);
	for(y=0;y<h-1;y++) 
	{
		ymin=max(0,y-radius); ymax=min(h-1,y+radius);
		for(x=0;x<w-1;x++)
		{
			d1=abs(in[y][x]-in[y][x+1]);
			d2=abs(in[y][x]-in[y+1][x]);
			d3=abs(in[y][x]-in[y+1][x+1]);
			if(d1>=larger_equal||d2>=larger_equal||d3>=larger_equal)
			{
				out[y][x]=1;
				xmin=max(0,x-radius); xmax=min(w-1,x+radius);
				for(yi=ymin;yi<=ymax;yi++) for(xi=xmin;xi<=xmax;xi++)
				{
					out[yi][xi]=255;
				}
			}
		}
	}
}
void get_edges(unsigned char **out,int **in,int radius,int larger_equal,int h,int w)
{
	int y,x,ymin,ymax,xmin,xmax,yi,xi; int d1,d2,d3;
	memset(out[0],0,sizeof(unsigned char)*h*w);
	//image_display(out,h,w);
	for(y=0;y<h-1;y++) 
	{
		ymin=max(0,y-radius); ymax=min(h-1,y+radius);
		for(x=0;x<w-1;x++)
		{
			d1=abs(in[y][x]-in[y][x+1]);
			d2=abs(in[y][x]-in[y+1][x]);
			d3=abs(in[y][x]-in[y+1][x+1]);
			if(d1>=larger_equal||d2>=larger_equal||d3>=larger_equal)
			{
				out[y][x]=1;
				xmin=max(0,x-radius); xmax=min(w-1,x+radius);
				for(yi=ymin;yi<=ymax;yi++) for(xi=xmin;xi<=xmax;xi++)
				{
					out[yi][xi]=255;
				}
			}
		}
	}
	//image_display(out,h,w);
}
void get_edges(unsigned char **out,unsigned char **in,int radius,unsigned char larger_equal,int h,int w)
{
	int y,x,ymin,ymax,xmin,xmax,yi,xi; unsigned char d1,d2,d3;
	memset(out[0],0,sizeof(unsigned char)*h*w);
	//image_display(out,h,w);
	for(y=0;y<h-1;y++) 
	{
		ymin=max(0,y-radius); ymax=min(h-1,y+radius);
		for(x=0;x<w-1;x++)
		{
			d1=abs(in[y][x]-in[y][x+1]);
			d2=abs(in[y][x]-in[y+1][x]);
			d3=abs(in[y][x]-in[y+1][x+1]);
			if(d1>=larger_equal||d2>=larger_equal||d3>=larger_equal)
			{
				out[y][x]=1;
				xmin=max(0,x-radius); xmax=min(w-1,x+radius);
				for(yi=ymin;yi<=ymax;yi++) for(xi=xmin;xi<=xmax;xi++)
				{
					out[yi][xi]=255;
				}
			}
		}
	}
	//image_display(out,h,w);
}
void get_edges(unsigned char **out,unsigned char **in,unsigned char larger_equal,int h,int w)
{
	int y,x; unsigned char d1,d2,d3;
	memset(out[0],0,sizeof(unsigned char)*h*w);
	//image_display(out,h,w);
	for(y=0;y<h-1;y++) 
	{
		for(x=0;x<w-1;x++)
		{
			d1=abs(in[y][x]-in[y][x+1]);
			d2=abs(in[y][x]-in[y+1][x]);
			d3=abs(in[y][x]-in[y+1][x+1]);
			if(d1>=larger_equal||d2>=larger_equal||d3>=larger_equal)
			{
				out[y][x]=255;
			}
		}
	}
	//image_display(out,h,w);
}
void get_edges_inside_mask(unsigned char **edge,unsigned char **mask,int h,int w)
{
	int y,x;
	memset(edge[0],0,sizeof(unsigned char)*h*w);
	//image_display(out,h,w);
	for(y=1;y<h-1;y++) 
	{
		for(x=1;x<w-1;x++)
		{
			if(mask[y][x])
			{
				if     (!mask[y-1][x-1]) edge[y][x]=255;
				else if(!mask[y-1][ x ]) edge[y][x]=255;
				else if(!mask[y-1][x+1]) edge[y][x]=255;
				else if(!mask[ y ][x-1]) edge[y][x]=255;
				else if(!mask[ y ][x+1]) edge[y][x]=255;
				else if(!mask[y+1][x-1]) edge[y][x]=255;
				else if(!mask[y+1][ x ]) edge[y][x]=255;
				else if(!mask[y+1][x+1]) edge[y][x]=255;
			}
		}
	}
	for(y=0;y<h;y++) for(x=0;x<w;x+=(w-1)) if(mask[y][x]) edge[y][x]=255;
	for(x=0;x<w;x++) for(y=0;y<h;y+=(h-1)) if(mask[y][x]) edge[y][x]=255;
	//image_display(out,h,w);
}
//void untexture_search(unsigned char**untexture,unsigned char***gradients,unsigned char ***image,unsigned char max_grad,int h,int w)
//{
//	int y,x,d; unsigned char dr,dg,db;
//	unsigned char *rgb0; int grad;
//	unsigned char **rgb_xy= new unsigned char *[4];
//	memset(untexture[0],0,sizeof(unsigned char)*h*w);
//	for (y=1; y<h-1; y++)
//	{
//		for (x=1; x<w-1; x++) 
//		{
//			rgb0=image[y][x];
//			rgb_xy[0]=image[y-1][x];
//			rgb_xy[1]=image[y][x-1];
//			rgb_xy[2]=image[y+1][x];
//			rgb_xy[3]=image[y][x+1];
//			
//			grad=0;
//			for(d=0;d<4;d++)
//			{
//				dr=abs(rgb_xy[d][0]-rgb0[0]); 
//				dg=abs(rgb_xy[d][1]-rgb0[1]); 
//				db=abs(rgb_xy[d][2]-rgb0[2]);
//				gradients[y][x][d]=max(max(dr,dg),db);
//				grad+=gradients[y][x][d];
//			}
//			grad/=4;
//			if(grad<max_grad) untexture[y][x]=1;
//		}
//	}
//	delete [] rgb_xy;
//}
void down_sample_1(unsigned char ***out,unsigned char ***in,int h,int w,int downsample_rate,int id)
{
	int y,x; int ho,wo; unsigned char *out_y,**in_y,*in_x;
	ho=(h>>downsample_rate); wo=(w>>downsample_rate); 
	out_y=&out[0][0][0];
	for(y=0;y<ho;y++)
	{
		in_y=in[(y<<downsample_rate)+id];
		for(x=0;x<wo;x++)
		{
			in_x=in_y[(x<<downsample_rate)+id];
			*out_y++=*in_x++; *out_y++=*in_x++; *out_y++=*in_x++;
		}
	}
}
void down_sample_1(float***out,float***in,int h,int w,int downsample_rate)
{
	int y,x; int ho,wo; float *out_y,**in_y,*in_x;
	ho=(h>>downsample_rate); wo=(w>>downsample_rate); 
	out_y=&out[0][0][0];
	for(y=0;y<ho;y++)
	{
		in_y=in[y<<downsample_rate];
		for(x=0;x<wo;x++)
		{
			in_x=in_y[x<<downsample_rate];
			*out_y++=*in_x++; *out_y++=*in_x++; *out_y++=*in_x++;
		}
	}
}
void down_sample_1(double***out,double***in,int h,int w,int downsample_rate)
{
	int y,x; int ho,wo; double*out_y,**in_y,*in_x;
	ho=(h>>downsample_rate); wo=(w>>downsample_rate); 
	out_y=&out[0][0][0];
	for(y=0;y<ho;y++)
	{
		in_y=in[y<<downsample_rate];
		for(x=0;x<wo;x++)
		{
			in_x=in_y[x<<downsample_rate];
			*out_y++=*in_x++; *out_y++=*in_x++; *out_y++=*in_x++;
		}
	}
}
void down_sample_1(float**out,float**in,int h,int w,int downsample_rate)
{
	int y,x; int ho,wo; float *out_y,*in_x;
	ho=(h>>downsample_rate); wo=(w>>downsample_rate); 
	for(y=0;y<ho;y++)
	{
		out_y=&out[y][0]; in_x=in[y<<downsample_rate];
		for(x=0;x<wo;x++) *out_y++=in_x[x<<downsample_rate];
	}
}
void down_sample_1(float*out,float*in,int h,int w,int downsample_rate)
{
	int y,x; int ho,wo; float *out_y,*in_x;
	ho=(h>>downsample_rate); wo=(w>>downsample_rate); 
	for(y=0;y<ho;y++)
	{
		out_y=&out[y*wo]; in_x=&in[(y<<downsample_rate)*w];
		for(x=0;x<wo;x++) *out_y++=in_x[x<<downsample_rate];
	}
}
void down_sample_1(double**out,double**in,int h,int w,int downsample_rate)
{
	int y,x; int ho,wo; double *out_y,*in_x;
	ho=(h>>downsample_rate); wo=(w>>downsample_rate); 
	for(y=0;y<ho;y++)
	{
		out_y=&out[y][0]; in_x=in[y<<downsample_rate];
		for(x=0;x<wo;x++) *out_y++=in_x[x<<downsample_rate];
	}
}
void down_sample_1(unsigned char **out,unsigned char **in,int h,int w,int downsample_rate)
{
	int y,x; int ho,wo; unsigned char *out_y,*in_x;
	ho=(h>>downsample_rate); wo=(w>>downsample_rate); 
	for(y=0;y<ho;y++)
	{
		out_y=&out[y][0]; in_x=in[y<<downsample_rate];
		for(x=0;x<wo;x++) *out_y++=in_x[x<<downsample_rate];
	}
}
void down_sample_121(unsigned char ***out,unsigned char ***in,int h,int w,int downsample_rate)
{
	int y,x; int ho,wo; unsigned char *out_y,**in_y,*in_x;
	img_smooth_121(in,h,w);
	ho=(h>>downsample_rate); wo=(w>>downsample_rate); 
	for(y=0;y<ho;y++)
	{
		out_y=&out[y][0][0]; in_y=in[y<<downsample_rate];
		for(x=0;x<wo;x++)
		{
			in_x=in_y[x<<downsample_rate];
			*out_y++=*in_x++; *out_y++=*in_x++; *out_y++=*in_x++;
		}
	}
}
void down_sample_121(unsigned char **out,unsigned char **in,int h,int w,int downsample_rate)
{
	int y,x; int ho,wo; unsigned char *out_x,*in_x;
	img_smooth_121(in,h,w);
	ho=(h>>downsample_rate); wo=(w>>downsample_rate); 
	for(y=0;y<ho;y++)
	{
		out_x=&out[y][0]; in_x=in[y<<downsample_rate];
		for(x=0;x<wo;x++)
		{
			*out_x++=in_x[x<<downsample_rate]; 
		}
	}
}
void down_sample_14641(unsigned char ***out,unsigned char ***in,int h,int w,int downsample_rate)
{
	int y,x; int ho,wo; unsigned char *out_y,**in_y,*in_x;
	ho=(h>>downsample_rate); wo=(w>>downsample_rate); 
	memset(out[0][0],0,sizeof(unsigned char)*ho*wo*3);
	img_smooth_14641_shift(in,h,w);
	//img_smooth_121(in,h,w);
	for(y=1;y<ho;y++)
	{
		out_y=&out[y][1][0]; in_y=in[(y-1)<<downsample_rate];
		for(x=0;x<wo;x++)
		{
			in_x=in_y[x<<downsample_rate];
			*out_y++=*in_x++; *out_y++=*in_x++; *out_y++=*in_x++;
		}
	}
	for(y=1;y<ho;y++)
	{
		out_y=&out[y][0][0]; in_x=&out[y][1][0];
		*out_y++=*in_x++; *out_y++=*in_x++; *out_y++=*in_x++; 
	}
	out_y=&out[0][1][0]; in_x=&out[1][1][0];
	for(x=1;x<wo;x++)
	{
		*out_y++=*in_x++; *out_y++=*in_x++; *out_y++=*in_x++; 
	}
	out_y=&out[0][0][0]; in_x=&out[1][1][0]; *out_y++=*in_x++; *out_y++=*in_x++; *out_y++=*in_x++; 
}
void down_sample_14641_rgb(unsigned char*out,unsigned char*in,int h,int w,int downsample_rate)
{
	int y,x; int ho,wo; unsigned char *out_y,*in_y,*in_x;
	ho=(h>>downsample_rate); wo=(w>>downsample_rate); 
	memset(out,0,sizeof(unsigned char)*ho*wo*3);
	img_smooth_14641_shift_rgb(in,h,w);
	//img_smooth_121(in,h,w);
	for(y=1;y<ho;y++)
	{
		out_y=&out[(y*wo+1)*3]; in_y=&in[((y-1)<<downsample_rate)*w*3];
		for(x=0;x<wo;x++)
		{
			in_x=&in_y[(x<<downsample_rate)*3];
			*out_y++=*in_x++; *out_y++=*in_x++; *out_y++=*in_x++;
		}
	}
	for(y=1;y<ho;y++)
	{
		out_y=&out[y*wo*3]; in_x=&out[(y*wo+1)*3];
		*out_y++=*in_x++; *out_y++=*in_x++; *out_y++=*in_x++; 
	}
	out_y=&out[3]; in_x=&out[(wo+1)*3];
	for(x=1;x<wo;x++)
	{
		*out_y++=*in_x++; *out_y++=*in_x++; *out_y++=*in_x++; 
	}
	out_y=&out[0]; in_x=&out[(wo+1)*3]; *out_y++=*in_x++; *out_y++=*in_x++; *out_y++=*in_x++; 
}

void down_sample_14641(unsigned char ***out,unsigned char ***in,int ho,int wo,int h,int w)
{
	int y,x; double scale_y,scale_x; unsigned char *out_y,**in_y,*in_x;
	scale_y=double(h)/double(ho);
	scale_x=double(w)/double(wo);
	memset(out[0][0],0,sizeof(unsigned char)*ho*wo*3);
	img_smooth_14641_shift(in,h,w);
	//img_smooth_121(in,h,w);
	for(y=1;y<ho;y++)
	{
		out_y=&out[y][1][0]; in_y=in[int((y-1)*scale_y+0.5)];
		for(x=0;x<wo;x++)
		{
			in_x=in_y[int(x*scale_x+0.5)];
			*out_y++=*in_x++; *out_y++=*in_x++; *out_y++=*in_x++;
		}
	}
	for(y=1;y<ho;y++)
	{
		out_y=&out[y][0][0]; in_x=&out[y][1][0];
		*out_y++=*in_x++; *out_y++=*in_x++; *out_y++=*in_x++; 
	}
	out_y=&out[0][1][0]; in_x=&out[1][1][0];
	for(x=1;x<wo;x++)
	{
		*out_y++=*in_x++; *out_y++=*in_x++; *out_y++=*in_x++; 
	}
	out_y=&out[0][0][0]; in_x=&out[1][1][0]; *out_y++=*in_x++; *out_y++=*in_x++; *out_y++=*in_x++; 
}
void up_sample(float **out,float **in,int h,int w,int upsample_rate)
{
	int ho,wo,y,x; float *out_x;
	ho=(h<<upsample_rate); wo=(w<<upsample_rate);
	for(out_x=&out[0][0],y=0;y<ho;y++) for(x=0;x<wo;x++)
	{
		(*out_x++)=in[y>>upsample_rate][x>>upsample_rate];
	}
}
void up_sample(int **out,int**in,int h,int w,int upsample_rate)
{
	int ho,wo,y,x; int*out_x;
	ho=(h<<upsample_rate); wo=(w<<upsample_rate);
	for(out_x=&out[0][0],y=0;y<ho;y++) for(x=0;x<wo;x++)
	{
		(*out_x++)=in[y>>upsample_rate][x>>upsample_rate];
	}
}
void up_sample(short**out,short**in,int h,int w,int upsample_rate)
{
	int ho,wo,y,x; short*out_x=out[0];
	ho=(h<<upsample_rate); wo=(w<<upsample_rate);
	for(y=0;y<ho;y++) for(x=0;x<wo;x++)
	{
		//(*out_x++)=in[y>>upsample_rate][x>>upsample_rate];
		out[y][x]=in[y>>upsample_rate][x>>upsample_rate];
	}
}

void up_sample(unsigned char **out,unsigned char **in,int h,int w,int upsample_rate)
{
	int ho,wo,y,x; unsigned char *out_x;
	ho=(h<<upsample_rate); wo=(w<<upsample_rate);
	for(out_x=&out[0][0],y=0;y<ho;y++) for(x=0;x<wo;x++)
	{
		(*out_x++)=in[y>>upsample_rate][x>>upsample_rate];
	}
}
void up_sample(unsigned char***out,unsigned char***in,int h,int w,int nr_channel,int upsample_rate)
{
	int ho,wo,y,x; unsigned char *out_x;
	ho=(h<<upsample_rate); wo=(w<<upsample_rate);
	for(out_x=out[0][0],y=0;y<ho;y++) for(x=0;x<wo;x++) for(int c=0;c<nr_channel;c++) (*out_x++)=in[y>>upsample_rate][x>>upsample_rate][c];
}
double qx_cubic_interpolation(double y0,double y1,double y2,double y3,double mu)
{
	double a0,a1,a2,a3,mu2;
	mu2=mu*mu;
	a0=y3-y2-y0+y1;
	a1=y0-y1-a0;
	a2=y2-y0;
	a3=y1;
	return(a0*mu*mu2+a1*mu2+a2*mu+a3);
}

void segm_display(unsigned char***labels_ppm,int **labels,int nr_labels,int h,int w)
{
	div_t div1, div2;
	int y,x;
	int labes_nr_3  = (int)pow(double(nr_labels),1.0/3.0)+1;
	int labes_nr_2 = labes_nr_3*labes_nr_3;
	int curr_label;
	for(y=0;y<h;y++) for(x=0;x<w;x++)
	{
		curr_label=labels[y][x];
		div1= div(curr_label+((curr_label%2)*2-1)*100, labes_nr_2);
		div2= div(div1.rem, labes_nr_3);
		labels_ppm[y][x][0]=unsigned char(255*float(div1.quot)/float(labes_nr_3));
		labels_ppm[y][x][1]=unsigned char(255*float(div2.quot)/float(labes_nr_3));
		labels_ppm[y][x][2]=unsigned char(255*float(div2.rem) /float(labes_nr_3));
	}
	for(y=0;y<h;y++) 
	{
		labels_ppm[y][0][0]=labels_ppm[y][1][0]; 
		labels_ppm[y][0][1]=labels_ppm[y][1][1]; 
		labels_ppm[y][0][2]=labels_ppm[y][1][2]; 
		labels_ppm[y][w-1][0]=labels_ppm[y][w-2][0]; 
		labels_ppm[y][w-1][1]=labels_ppm[y][w-2][1]; 
		labels_ppm[y][w-1][2]=labels_ppm[y][w-2][2]; 
	}
	for(x=0;x<w;x++)
	{
		labels_ppm[0][x][0]=labels_ppm[1][x][0]; 
		labels_ppm[0][x][1]=labels_ppm[1][x][1]; 
		labels_ppm[0][x][2]=labels_ppm[1][x][2]; 
		labels_ppm[h-1][x][0]=labels_ppm[h-2][x][0]; 
		labels_ppm[h-1][x][1]=labels_ppm[h-2][x][1]; 
		labels_ppm[h-1][x][2]=labels_ppm[h-2][x][2]; 
	}
	imdebug("image *auto w=%d h=%d %p",w,h,&labels_ppm[0][0][0]);
}
void segm_display(int **labels,int nr_labels,int h,int w)
{
	div_t div1, div2;
	int y,x;
	int labes_nr_3  = (int)pow(double(nr_labels),1.0/3.0)+1;
	int labes_nr_2 = labes_nr_3*labes_nr_3;
	int curr_label;
	unsigned char ***labels_ppm=qx_allocu_3(h,w,3);

	for(y=0;y<h;y++) for(x=0;x<w;x++)
	{
		curr_label=labels[y][x];
		div1= div(curr_label+((curr_label%2)*2-1)*100, labes_nr_2);
		div2= div(div1.rem, labes_nr_3);
		labels_ppm[y][x][0]=unsigned char(255*float(div1.quot)/float(labes_nr_3));
		labels_ppm[y][x][1]=unsigned char(255*float(div2.quot)/float(labes_nr_3));
		labels_ppm[y][x][2]=unsigned char(255*float(div2.rem) /float(labes_nr_3));
	}
	for(y=0;y<h;y++) 
	{
		labels_ppm[y][0][0]=labels_ppm[y][1][0]; 
		labels_ppm[y][0][1]=labels_ppm[y][1][1]; 
		labels_ppm[y][0][2]=labels_ppm[y][1][2]; 
		labels_ppm[y][w-1][0]=labels_ppm[y][w-2][0]; 
		labels_ppm[y][w-1][1]=labels_ppm[y][w-2][1]; 
		labels_ppm[y][w-1][2]=labels_ppm[y][w-2][2]; 
	}
	for(x=0;x<w;x++)
	{
		labels_ppm[0][x][0]=labels_ppm[1][x][0]; 
		labels_ppm[0][x][1]=labels_ppm[1][x][1]; 
		labels_ppm[0][x][2]=labels_ppm[1][x][2]; 
		labels_ppm[h-1][x][0]=labels_ppm[h-2][x][0]; 
		labels_ppm[h-1][x][1]=labels_ppm[h-2][x][1]; 
		labels_ppm[h-1][x][2]=labels_ppm[h-2][x][2]; 
	}
	imdebug("image *auto w=%d h=%d %p",w,h,&labels_ppm[0][0][0]);
	qx_freeu_3(labels_ppm);
}
void label_2_segm(unsigned char ***segm,int **labels,int nr_labels,int h,int w)
{
	div_t div1, div2;
	int y,x;
	int labes_nr_3  = (int)pow(double(nr_labels),1.0/3.0)+1;
	int labes_nr_2 = labes_nr_3*labes_nr_3;
	int curr_label;
	for(y=0;y<h;y++) for(x=0;x<w;x++)
	{
		curr_label=labels[y][x];
		div1= div(curr_label+((curr_label%2)*2-1)*100, labes_nr_2);
		div2= div(div1.rem, labes_nr_3);
		segm[y][x][0]=unsigned char(255*float(div1.quot)/float(labes_nr_3));
		segm[y][x][1]=unsigned char(255*float(div2.quot)/float(labes_nr_3));
		segm[y][x][2]=unsigned char(255*float(div2.rem) /float(labes_nr_3));
	}
	for(y=0;y<h;y++) 
	{
		segm[y][0][0]=segm[y][1][0]; 
		segm[y][0][1]=segm[y][1][1]; 
		segm[y][0][2]=segm[y][1][2]; 
		segm[y][w-1][0]=segm[y][w-2][0]; 
		segm[y][w-1][1]=segm[y][w-2][1]; 
		segm[y][w-1][2]=segm[y][w-2][2]; 
	}
	for(x=0;x<w;x++)
	{
		segm[0][x][0]=segm[1][x][0]; 
		segm[0][x][1]=segm[1][x][1]; 
		segm[0][x][2]=segm[1][x][2]; 
		segm[h-1][x][0]=segm[h-2][x][0]; 
		segm[h-1][x][1]=segm[h-2][x][1]; 
		segm[h-1][x][2]=segm[h-2][x][2]; 
	}
}
bool elem_not_in_array(int elem,int *array,int len)
{	
	int i=0;
	while ( (array[i]!=elem)&(i<len) ) i++;
	if (i<len)		return false;
	else			return true;
}
int index_elem_in_array(int elem,int *array,int len)
{	
	int i=-1;
	while ( (array[++i]!=elem)&(i<len) );
	if (i<len)	return i;
	else		return -1;
}
void seek_8_neighbors(int neighbor_8[8],int &neighbor_8_nr,int p,int h,int w)
{
	int t0=p%w,hw= h*w,t1=hw-w,t2= w-1, t3= hw-1, r0= p/w, r1= h-1;
	if (t0==0)//when along the left colum
	{
		if (p==0)
		{
			neighbor_8_nr= 3;
			neighbor_8[0]= w; neighbor_8[1]= w+1; neighbor_8[2]= 1;
		}

		else if (p==t1)
		{
			neighbor_8_nr= 3;
			neighbor_8[0]= p+1; neighbor_8[1]= p-w+1; neighbor_8[2]= p-w;
		}
		else
		{
			neighbor_8_nr= 5;
			neighbor_8[0]= p+w; neighbor_8[1]= p+w+1; neighbor_8[2]= p+1; neighbor_8[3]= p-w+1; neighbor_8[4]= p-w;
		}
	}
	else if (t0==t2)//when along the rightest colum
	{
		if (p==t2)
		{
			neighbor_8_nr= 3;
			neighbor_8[0]= p-1; neighbor_8[1]= p+w-1; neighbor_8[2]= p+w;
		}
		else if (p==t3)
		{
			neighbor_8_nr= 3;
			neighbor_8[0]= p-w; neighbor_8[1]= p-w-1; neighbor_8[2]= p-1;
		}
		else
		{
			neighbor_8_nr= 5;
			neighbor_8[0]= p-w; neighbor_8[1]= p-w-1; neighbor_8[2]= p-1; neighbor_8[3]= p+w-1; neighbor_8[4]= p+w;
		}
	}
	else if (r0==0)
	{
		neighbor_8_nr= 5;
		neighbor_8[0]= p-1; neighbor_8[1]= p+1; neighbor_8[2]= p+w-1; neighbor_8[3]= p+w; neighbor_8[4]= p+w+1;
	}
	else if (r0==r1)
	{
		neighbor_8_nr= 5;
		neighbor_8[0]= p-1; neighbor_8[1]= p+1; neighbor_8[2]= p-w-1; neighbor_8[3]= p-w; neighbor_8[4]= p-w+1;
	}
	else
	{
		neighbor_8_nr= 8;
		neighbor_8[1]= p-w;	neighbor_8[0]= p-w-1; neighbor_8[2]= p-w+1; neighbor_8[3]= p-1;
		neighbor_8[4]= p+1;	neighbor_8[6]= p+w;	neighbor_8[5]= p+w-1; neighbor_8[7]= p+w+1;	
	}
}


int pyramic_accumulate_2x2_sub(int in)
{
	int out;
	out= in/2;
	return out;
}

void pyramic_accumulate_2x2(float *p,int h,int w,int d,int scales)
{
	int i,j,k,l,t,len,idx1,idx2;
	float *a,*b;
	int ah,aw,bh,bw;
	for (i=0;i<h*w*d;i++)
		p[i]=(float)pyramic_accumulate_2x2_sub(i); /*get the data for scale 1st*/

	t= 0;
	ah=h;
	aw=w;
	for (i=1;i<scales;i++)
	{
		ah=ah>>(i-1);
		aw=aw>>(i-1);
		bh=ah>>1;
		bw=aw>>1;
		a=&(p[t]);
		len= ah*aw*d;
		cout<<"nr: "<<bh*bw*d<<endl;
		t+=len;
		b=&(p[t]);
		for (j=0;j<ah;j++)
			for (k=0;k<aw;k++)
				for (l=0;l<d;l++)
				{					
					idx1= (j/2)*bw*d+(k/2)*d+l;
					idx2=j*aw*d+k*d+l;
					b[idx1]+=a[idx2];
					//cout<<"["<<idx1<<":"<<idx2<<"] ";
				}
		for (j=0;j<bh*bw*d;j++)
			cout<<b[j]<<" ";
		cout<<endl<<endl;

	}
}
void pyramic_alloc_2x2(float **p,int h,int w,int d,int scales)
{
	(*p)= (float*)malloc(sizeof(float)*int(h*w*d*1.5));
	memset((*p),0,sizeof(float)*int(h*w*d*1.5));
}
void pyramic_locate_2x2(float ***qqq,float **qq,float *p,int h,int w,int d,int scales_idx)
{
	int i,qh,qw,curr_pos;
	curr_pos=0;
	for (i=1;i<scales_idx;i++)
	{
		curr_pos+=(h>>(i-1))*(w>>(i-1))*d;
	}
	float *q=&(p[curr_pos]);
	qh=h>>(scales_idx-1);
	qw=w>>(scales_idx-1);
	for(i=0;i<qh*qw;i++)
		qq[i]= &(q[i*d]);
	for(i=0;i<qh;i++)
		qqq[i]= &(qq[i*qw]);
}


//void main()  //for the lu method
//{
//	int size,y,x,*exchange;
//	float **in,**in_cpy,**l,**u;
//	float *xx=new float [size],*yy=new float [size];
//	size=6;
//	in=qx_allocf(size,size);
//	in_cpy=qx_allocf(size,size);
//	l=qx_allocf(size,size);
//	u=qx_allocf(size,size);
//	exchange= new int [size];
//	int s=12;
//	qx_gaussian_2d(in,size,size,s);
//	for(y=0;y<size;y++)
//	{
//		for(x=0;x<size;x++)
//			printf("%1.5f ",in[y][x]);
//		cout<<endl;
//	}
//	memcpy(in_cpy[0],in[0],sizeof(float)*size*size);
//
//	for(y=0;y<size;y++)
//		yy[y]=y*10+111;
//	cout<<endl<<"yy: ";	for(y=0;y<size;y++)	cout<<yy[y]<<" ";
//	
//	lux_y(xx,yy,l,u,in,size);
//	
//	qx_matrix_product(in_cpy,xx,size,size,yy);
//	cout<<endl<<"result: ";
//	for(int d=0;d<size;d++)
//		printf("%2.2f, ",yy[d]);	
//	cout<<endl;
//}

/*camera parameter*/
void get_kinv(float kinvmat[3][3],float kmat[3][3])
{
	float a,b,c,d,e,aa,bb,cc,dd,ee;
	a=kmat[0][0]; b=kmat[0][1]; c=kmat[0][2]; d=kmat[1][1]; e=kmat[1][2];
	aa=1.0f/a; dd=1.0f/d; bb=-aa*b*dd; cc=-aa*c-bb*e; ee=-dd*e;
	kinvmat[0][0]=aa; kinvmat[0][1]=bb; kinvmat[0][2]=cc;
	kinvmat[1][0]=0; kinvmat[1][1]=dd; kinvmat[1][2]=ee;
	kinvmat[2][0]=0; kinvmat[2][1]=0; kinvmat[2][2]=1;
}
void get_kinv(double kinv[9],double kmat[9])
{
	double a,b,c,d,e,aa,bb,cc,dd,ee;
	a=kmat[0]; b=kmat[1]; c=kmat[2]; d=kmat[4]; e=kmat[5];
	if((a==0.0)||(d==0.0)) 
	{
		qx_eye_33(kinv);
	}
	else
	{
		aa=1.0f/a; dd=1.0f/d; bb=-aa*b*dd; cc=-aa*c-bb*e; ee=-dd*e;
		kinv[0]=aa; kinv[1]=bb; kinv[2]=cc;
		kinv[3]=0; kinv[4]=dd; kinv[5]=ee;
		kinv[6]=0; kinv[7]=0; kinv[8]=1;
	}
}
void kinv_xy(float***xy,double kinv[9],int h,int w)
{
	for(int y=0;y<h;y++) 
	{
		for(int x=0;x<w;x++)
		{
			xy[y][x][0]=float(kinv[0]*x+kinv[1]*y+kinv[2]);
			xy[y][x][1]=float(kinv[4]*y+kinv[5]);
		}
	}
}
void kinv_xy(float**xy,double kinv[9],int h,int w)
{
	float*xy_=xy[0];
	for(int y=0;y<h;y++) 
	{
		for(int x=0;x<w;x++)
		{
			*xy_++=float(kinv[0]*x+kinv[1]*y+kinv[2]);
			*xy_++=float(kinv[4]*y+kinv[5]);
		}
	}
}

void kmat_xy(float ***xy,double kmat[9],int h,int w)
{
	for(int y=0;y<h;y++) 
	{
		for(int x=0;x<w;x++)
		{
			xy[y][x][0]=float(kmat[0]*xy[y][x][0]+kmat[1]*xy[y][x][1]+kmat[2]);
			xy[y][x][1]=float(kmat[4]*xy[y][x][1]+kmat[5]);
		}
	}
}
void get_rinv(float rinvmat[3][3],float viewmat[3][4])
{
	int y,x;
	for(y=0;y<3;y++) for(x=0;x<3;x++) rinvmat[y][x]=viewmat[x][y];
}
void get_cop(float cop[3],float viewmat[3][4],float rinvmat[3][3])
{
	float a[3],*b;
	a[0]=viewmat[0][3]; a[1]=viewmat[1][3]; a[2]=viewmat[2][3]; 
	b=rinvmat[0]; cop[0]=-(b[0]*a[0]+b[1]*a[1]+b[2]*a[2]);
	b=rinvmat[1]; cop[1]=-(b[0]*a[0]+b[1]*a[1]+b[2]*a[2]);
	b=rinvmat[2]; cop[2]=-(b[0]*a[0]+b[1]*a[1]+b[2]*a[2]);
}
void qx_depth_2_zvalue(float **depth,double *kinv,int h,int w)
{
	float d; double xp,yp; int y,x;
	/*zp=sqrt(depth^2/(x'^2+y'^2+1))*/
	for(y=0;y<h;y++) for(x=0;x<w;x++)
	{
		xp=kinv[0]*x+kinv[1]*y+kinv[2];
		yp=kinv[4]*y+kinv[5];
		d=depth[y][x];
		depth[y][x]=(float)sqrt(d*d/(xp*xp+yp*yp+1));
	}
	//image_display(depth,m_depthmap_h,m_depthmap_w);
}
void qx_depth_2_disp(float **depth,int h,int w,int nr_planes,float depth_min,float depth_max,double *kinv)
{
	int y,x; float dmin,dmax; float f; double k1,k2;
	qx_depth_2_zvalue(depth,kinv,h,w);
	//image_display(depth,h,w);
	/*disp=(max-(min*max/f))*47.f/(max-min)*/
	dmin=depth_min; dmax=depth_max;
	k1=float(nr_planes-1)/(dmax-dmin); k2=dmin*dmax;
	for(y=0;y<h;y++) for(x=0;x<w;x++)
	{
		f=max(min(depth[y][x],depth_max),depth_min); 
		depth[y][x]=float((dmax-k2/f)*k1);
	}
}
double qx_disp_2_depth(int disparity,int nr_plane,double zmin,double zmax,bool use_zdepth_value,double *kinv,int h,int w)
{
	double k1,k2;
	/*f=1.0/(1.0/min-d*(1.0/min-1.0/max)/47)=1.0/(k1-d*k2)*/
	k1=1.0/zmin; k2=(k1-1.0/zmax)/(nr_plane-1);
	double zdepth=float(1.0/(k1-disparity*k2));
	if(!use_zdepth_value) qx_zvalue_2_depth(zdepth,kinv,h,w);
	return(zdepth);
}
void qx_disp_2_depth(float **depth,int h,int w,int nr_planes,float depth_min,float depth_max,double *kinv,bool use_zdepth_value)
{
	int y,x; float dmin,dmax; float d; double k1,k2;
	/*f=1.0/(1.0/min-d*(1.0/min-1.0/max)/47)=1.0/(k1-d*k2)*/
	dmin=depth_min; dmax=depth_max;
	k1=1.0/dmin; k2=(k1-1.0/dmax)/(nr_planes-1);
	for(y=0;y<h;y++) for(x=0;x<w;x++)
	{
		d=depth[y][x]; 
		depth[y][x]=float(1.0/(k1-d*k2));
	}
	//image_display(depth,h,w);
	if(!use_zdepth_value) qx_zvalue_2_depth(depth,kinv,h,w);
}
float qx_disp_2_depth(int disparity,double baseline_x_focal_length,double *kinv,int x,int y)
{
	double z,nx,ny;
	z=baseline_x_focal_length/disparity; 
	nx=kinv[0]*x+kinv[1]*y+kinv[2];
	ny=kinv[4]*y+kinv[5];
	return(float(z*sqrt(nx*nx+ny*ny+1)));
}
void qx_depth_2_disp(float **depth,float baseline,float focal_length,double *kinv,int h,int w)
{
	double bf=double(baseline*focal_length);
	double z,nx,ny;
	for(int y=0;y<h;y++) for(int x=0;x<w;x++)
	{
		if(depth[y][x]>0.1f)
		{
			nx=kinv[0]*x+kinv[1]*y+kinv[2];
			ny=kinv[4]*y+kinv[5];
			z=depth[y][x]/sqrt(nx*nx+ny*ny+1);
			if(z>0.01f) depth[y][x]=float(bf/z); 
		}
	}
}
void qx_disp_2_zdepth(float **depth,float baseline,float focal_length,int h,int w)
{
	double baseline_x_focal_length=baseline*focal_length;
	for(int y=0;y<h;y++) for(int x=0;x<w;x++) depth[y][x]=qx_disp_2_zdepth(depth[y][x],baseline_x_focal_length);
}
void qx_zdepth_2_disp(float **depth,float baseline,float focal_length,int h,int w)
{
	double baseline_x_focal_length=baseline*focal_length;
	for(int y=0;y<h;y++) for(int x=0;x<w;x++) depth[y][x]=qx_zdepth_2_disp(depth[y][x],baseline_x_focal_length);
}
void qx_disp_2_depth(float **depth,float baseline,float focal_length,double *kinv,int h,int w)
{
	double bf=double(baseline*focal_length);
	double z,nx,ny;
	for(int y=0;y<h;y++) for(int x=0;x<w;x++)
	{
		if(depth[y][x]>0.1f)
		{
			z=bf/depth[y][x]; 
			nx=kinv[0]*x+kinv[1]*y+kinv[2];
			ny=kinv[4]*y+kinv[5];
			depth[y][x]=float(z*sqrt(nx*nx+ny*ny+1));
		}
	}
	//image_display(depth,h,w);
	//qx_zvalue_2_depth(depth,h,w,kinv);
}
void qx_zvalue_2_depth(float **depth,double *kinv,int h,int w)
{
	float d; double xp,yp; int y,x;
	/*zp=sqrt(depth^2/(x'^2+y'^2+1))*/
	for(y=0;y<h;y++) for(x=0;x<w;x++)
	{
		xp=kinv[0]*x+kinv[1]*y+kinv[2];
		yp=kinv[4]*y+kinv[5];
		d=depth[y][x];
		xp*=d; yp*=d;
		depth[y][x]=(float)sqrt(d*d+xp*xp+yp*yp);
	}
	//image_display(depth,m_depthmap_h,m_depthmap_w);
}
float qx_disp_2_zvalue(float depth,int nr_planes,float depth_min,float depth_max,double *kinv)
{
	float dmin,dmax; double k1,k2;
	/*f=1.0/(1.0/min-d*(1.0/min-1.0/max)/47)=1.0/(k1-d*k2)*/
	dmin=depth_min; dmax=depth_max;
	k1=1.0/dmin; k2=(k1-1.0/dmax)/(nr_planes-1);
	depth=float(1.0/(k1-depth*k2));
	return(depth);
}
float qx_zvalue_2_depth(float depth,double *kinv,int y,int x)
{
	double xp,yp; 
	/*zp=sqrt(depth^2/(x'^2+y'^2+1))*/
	xp=kinv[0]*x+kinv[1]*y+kinv[2];
	yp=kinv[4]*y+kinv[5];
	xp*=depth; yp*=depth;
	depth=(float)sqrt(depth*depth+xp*xp+yp*yp);
	return(depth);
}
/*sphere calibration*/
double get_sphere_mask_center_and_radius(double center_sphere[2],unsigned char **mask,int h,int w)
{
	center_sphere[0]=center_sphere[1]=0; 
	int nr_sphere,nr_boundary;
	nr_sphere=0;
	for(int y=0;y<h;y++)
	{
		for(int x=0;x<w;x++)
		{
			if(mask[y][x])
			{
				center_sphere[0]+=(double)x;
				center_sphere[1]+=(double)y;
				nr_sphere++;
			}
		}
	}
	if(nr_sphere==0)
	{
		printf("nr_sphere=0!");
		getchar();
		exit(0);
	}
	center_sphere[0]/=nr_sphere;
	center_sphere[1]/=nr_sphere;
	nr_boundary=0;
	double radius=0;
	for(int y=1;y<h-1;y++)
	{
		for(int x=1;x<w-1;x++)
		{
			if(mask[y][x]&&(!mask[y-1][x-1]||!mask[y-1][x]||!mask[y-1][x+1]||!mask[y][x-1]||!mask[y][x+1]||!mask[y+1][x-1]||!mask[y+1][x]||!mask[y+1][x+1]))
			{
				double dx=center_sphere[0]-x;
				double dy=center_sphere[1]-y;
				radius+=sqrt(dx*dx+dy*dy);
				nr_boundary++;
			}
		}
	}
	if(nr_boundary==0)
	{
		printf("nr_boundary=0!");
		getchar();
		exit(0);
	}
	radius/=nr_boundary;
	return(radius);
}
void get_highlight_center(double center_highlight[2],unsigned char **image,unsigned char **mask,int h,int w)
{
	center_highlight[0]=center_highlight[1]=0; 
	int nr_highlight=0;
	unsigned char imax=0;
	for(int y=0;y<h;y++)
	{
		for(int x=0;x<w;x++)
		{
			if(mask[y][x])
			{
				imax=max(imax,image[y][x]);
			}
		}
	}
	printf("imax: %d\n",imax);
	for(int y=0;y<h;y++)
	{
		for(int x=0;x<w;x++)
		{
			if(mask[y][x]&&image[y][x]==imax)
			{
				center_highlight[0]+=(double)x;
				center_highlight[1]+=(double)y;
				nr_highlight++;
			}
		}
	}
	printf("nr_highlight: %d\n",nr_highlight);
	if(nr_highlight==0)
	{
		printf("nr_sphere=0!");
		getchar();
		exit(0);
	}
	center_highlight[0]/=nr_highlight;
	center_highlight[1]/=nr_highlight;
	printf("center_highlight: [%f,%f]\n",center_highlight[0],center_highlight[1]);
}
void normal_from_mirror_sphere(double normal[3],unsigned char **image,unsigned char **mask,int h,int w)
{
	double center_sphere[2],center_highlight[2],radius;
	radius=get_sphere_mask_center_and_radius(center_sphere,mask,h,w);
	get_highlight_center(center_highlight,image,mask,h,w);
	//printf("[%f,%f] [%f,%f] [%f]\n",center_sphere[0],center_sphere[1],center_highlight[0],center_highlight[1],radius);
	for(int c=0;c<2;c++) normal[c]=(center_highlight[c]-center_sphere[c])/radius;
	normal[2]=normal[0]*normal[0]+normal[1]*normal[1];
	normal[2]=-sqrt(1-normal[2]);
}

/*stereo */
void qx_occlusion_from_disparity(unsigned char**occl,unsigned char**disp,int h,int w)
{
	memset(occl[0],0,sizeof(char)*h*w);
	for(int y=0;y<h;y++)
	{
		int x=w-1;
		while(x>0)
		{
			int d=disp[y][x]-disp[y][x-1];
			if(d>1)
			{
				int xl=x-d;
				for(int xi=xl;xi<x;xi++) occl[y][xi]=255;
				x=xl-1;
			}
			else x--;
		}
		int d=disp[y][0];
		for(int x=0;x<d;x++) occl[y][x]=255;
	}
}
void depth_sub_pixel(float **depth_f,int **depth_i,float ***evidence,int h,int w,int nr_planes)
{
	int y,x,d0; float v0,v1,v2,dx,*local_evidence;
	for(y=0;y<h;y++) for(x=0;x<w;x++)
	{
		local_evidence=evidence[y][x];
		d0=depth_i[y][x];
		if(d0==0||d0==(nr_planes-1)) dx=0;
		else 
		{
			v0=local_evidence[d0];
			v1=local_evidence[d0-1];
			v2=local_evidence[d0+1];
			if(v0<v1&&v0<v2) dx=(v2+v1-v0-v0==0)?0:0.5f*(v2-v1)/(v2+v1-v0-v0);
			else dx=0;
		}
		depth_f[y][x]=float(d0)-dx;
	}
}
void depth_sub_pixel(float**depth_f,unsigned char**depth_i,double***evidence,int h,int w,int nr_planes)
{
	int y,x,d0; double v0,v1,v2,dx,*local_evidence;
	for(y=0;y<h;y++) for(x=0;x<w;x++)
	{
		local_evidence=evidence[y][x];
		d0=depth_i[y][x];
		if(d0==0||d0==(nr_planes-1)) dx=0;
		else 
		{
			v0=local_evidence[d0];
			v1=local_evidence[d0-1];
			v2=local_evidence[d0+1];
			if(v0<v1&&v0<v2) dx=(v2+v1-v0-v0==0)?0:0.5f*(v2-v1)/(v2+v1-v0-v0);
			else dx=0;
		}
		depth_f[y][x]=double(d0)-dx;
	}
}
void depth_sub_pixel(float **depth_f,float ***evidence,int h,int w,int nr_planes)
{
	int y,x,d0; float v0,v1,v2,dx,*local_evidence;
	for(y=0;y<h;y++) for(x=0;x<w;x++)
	{
		local_evidence=evidence[y][x];
		vec_min_pos(d0,local_evidence,nr_planes);
		if(d0==0||d0==(nr_planes-1)) dx=0;
		else 
		{
			v0=local_evidence[d0];
			v1=local_evidence[d0-1];
			v2=local_evidence[d0+1];
			dx=(v2+v1-v0-v0==0)?0:0.5f*(v2-v1)/(v2+v1-v0-v0);
		}
		depth_f[y][x]=float(d0)-dx;
	}
}
void depth_sub_pixel(float**depth_f,short***evidence,int h,int w,int nr_planes)
{
	int y,x,d0; float v0,v1,v2,dx; short*local_evidence;
	for(y=0;y<h;y++) for(x=0;x<w;x++)
	{
		local_evidence=evidence[y][x];
		vec_min_pos(d0,local_evidence,nr_planes);
		if(d0==0||d0==(nr_planes-1)) dx=0;
		else 
		{
			v0=(float)local_evidence[d0];
			v1=(float)local_evidence[d0-1];
			v2=(float)local_evidence[d0+1];
			dx=(v2+v1-v0-v0==0)?0:0.5f*(v2-v1)/(v2+v1-v0-v0);
		}
		depth_f[y][x]=float(d0)-dx;
	}
}
float depth_sub_pixel(float*evidence,int nr_planes)
{
	float depth,ypo,yno;
	int d,d0;
	vec_min_pos(d,evidence,nr_planes);
	depth=d;
	if(d==0) d0=1;
	else if(d==nr_planes-1) d0=nr_planes-2;
	else d0=d;
	ypo=evidence[d0-1]-evidence[d0];
	yno=evidence[d0+1]-evidence[d0];
	float dx=qx_div(ypo-yno,ypo+yno+ypo+yno);
	if(d==0&&dx>-1&&dx<0) depth=d0+dx;
	else if(d==nr_planes-1&&dx>0&&dx<1) depth=d0+dx;
	else if(d>0&&d<nr_planes-1) depth=d0+dx;
	return(depth);
}
double depth_sub_pixel(double*evidence,int nr_planes)
{
	double  depth,ypo,yno;
	int d,d0;
	vec_min_pos(d,evidence,nr_planes);
	depth=d;
	if(d==0) d0=1;
	else if(d==nr_planes-1) d0=nr_planes-2;
	else d0=d;
	ypo=evidence[d0-1]-evidence[d0];
	yno=evidence[d0+1]-evidence[d0];
	float dx=qx_div(ypo-yno,ypo+yno+ypo+yno);
	if(d==0&&dx>-1&&dx<0) depth=d0+dx;
	else if(d==nr_planes-1&&dx>0&&dx<1) depth=d0+dx;
	else if(d>0&&d<nr_planes-1) depth=d0+dx;
	return(depth);
}
double depth_sub_pixel(double*evidence,int d,int nr_planes)
{
	double  depth,ypo,yno;
	int d0;
	depth=d;
	if(d==0) d0=1;
	else if(d==nr_planes-1) d0=nr_planes-2;
	else d0=d;
	ypo=evidence[d0-1]-evidence[d0];
	yno=evidence[d0+1]-evidence[d0];
	float dx=qx_div(ypo-yno,ypo+yno+ypo+yno);
	if(d==0&&dx>-1&&dx<0) depth=d0+dx;
	else if(d==nr_planes-1&&dx>0&&dx<1) depth=d0+dx;
	else if(d>0&&d<nr_planes-1) depth=d0+dx;
	return(depth);
}
double depth_sub_pixel_linear(double*evidence,int nr_planes)
{
	double depth,yp,yn,yo;
	int d;
	vec_min_pos(d,evidence,nr_planes);
	if(d==0) depth=d;
	else if(d==nr_planes-1) depth=nr_planes-1;
	else 
	{
		yp=evidence[d-1];
		yo=evidence[d];
		yn=evidence[d+1];
		if(yp>yn) depth=qx_div(yn-yp,yo-yp+yo-yp)+d;
		else depth=qx_div(yp-yn,yn-yo+yn-yo)+d;
	}
	return(depth);
}
double depth_sub_pixel_max(double *evidence,int nr_planes)
{
	int d0; float v0,v1,v2,dx; double depth;
	vec_max_pos(d0,evidence,nr_planes);
	if(d0==0||d0==(nr_planes-1)) dx=0;
	else 
	{
		v0=(float)evidence[d0];
		v1=(float)evidence[d0-1];
		v2=(float)evidence[d0+1];
		dx=(v2+v1-v0-v0==0)?0:0.5f*(v2-v1)/(v2+v1-v0-v0);
	}
	depth=d0-dx;
	return(depth);
}
float depth_sub_pixel_max(float *evidence,int nr_planes)
{
	int d0; float v0,v1,v2,dx,depth;
	vec_max_pos(d0,evidence,nr_planes);
	if(d0==0||d0==(nr_planes-1)) dx=0;
	else 
	{
		v0=evidence[d0];
		v1=evidence[d0-1];
		v2=evidence[d0+1];
		dx=(v2+v1-v0-v0==0)?0:0.5f*(v2-v1)/(v2+v1-v0-v0);
	}
	depth=float(d0)-dx;
	return(depth);
}
void quantized_depth_2_sub_pixel(float **depth_f,int **depth,float ***evidence,int h,int w,int nr_planes)
{
	int y,x,d0; float v0,v1,v2,dx,*local_evidence;
	for(y=0;y<h;y++) for(x=0;x<w;x++)
	{
		d0=depth[y][x];
		local_evidence=evidence[y][x];
		if(d0==0||d0==(nr_planes-1)) dx=0;
		else 
		{
			v0=local_evidence[d0];
			v1=local_evidence[d0-1];
			v2=local_evidence[d0+1];
			if(v0<v1&&v0<v2) dx=(v2+v1-v0-v0==0)?0:0.5f*(v2-v1)/(v2+v1-v0-v0);
			else dx=0;
		}
		depth_f[y][x]=float(d0)-dx;
	}
}
void depth_best_cost(unsigned char**depth,double***evidence,int h,int w,int nr_planes)
{
	for(int y=0;y<h;y++) for(int x=0;x<w;x++) {int d; vec_min_pos(d,evidence[y][x],nr_planes); depth[y][x]=d;}
}
void depth_best_cost(int**depth,unsigned char***evidence,int h,int w,int nr_planes)
{
	for(int y=0;y<h;y++) for(int x=0;x<w;x++) {int d; vec_min_pos(d,evidence[y][x],nr_planes); depth[y][x]=d;}
}
void depth_best_cost(unsigned char**depth,unsigned char***evidence,int h,int w,int nr_planes)
{
	for(int y=0;y<h;y++) for(int x=0;x<w;x++) {int d; vec_min_pos(d,evidence[y][x],nr_planes); depth[y][x]=d;}
}
void depth_best_cost(unsigned char**depth,float ***evidence,int h,int w,int nr_planes)
{
	for(int y=0;y<h;y++) for(int x=0;x<w;x++) {int d; vec_min_pos(d,evidence[y][x],nr_planes); depth[y][x]=d;}
}
void depth_best_cost(unsigned char**depth,short***evidence,int h,int w,int nr_planes)
{
	for(int y=0;y<h;y++) for(int x=0;x<w;x++) {int d; vec_min_pos(d,evidence[y][x],nr_planes); depth[y][x]=d;}
}
void depth_best_cost(short**depth,short***evidence,int h,int w,int nr_planes)
{
	for(int y=0;y<h;y++) for(int x=0;x<w;x++) {int d; vec_min_pos(d,evidence[y][x],nr_planes); depth[y][x]=d;}
}
void depth_best_cost(int **depth,float ***evidence,int h,int w,int nr_planes)
{
	for(int y=0;y<h;y++) for(int x=0;x<w;x++) vec_min_pos(depth[y][x],evidence[y][x],nr_planes);
}
void depth_kth_cost(int **depth,float ***evidence,int h,int w,int nr_planes)
{
	int dk; float cmin;
	for(int y=0;y<h;y++) for(int x=0;x<w;x++) 
	{
		cmin=QX_DEF_FLOAT_MAX;
		for(int d=0;d<depth[y][x];d++)
		{
			if(cmin>evidence[y][x][d])
			{
				dk=d; cmin=evidence[y][x][d];
			}
		}
		for(int d=depth[y][x]+1;d<nr_planes;d++)
		{
			if(cmin>evidence[y][x][d])
			{
				dk=d; cmin=evidence[y][x][d];
			}
		}
		evidence[y][x][depth[y][x]]=QX_DEF_FLOAT_MAX; depth[y][x]=dk; 
	}
}
void depth_best_cost(float **depth,float ***evidence,int h,int w,int nr_planes)
{
	int depth_curr;
	for(int y=0;y<h;y++) for(int x=0;x<w;x++) 
	{
		vec_min_pos(depth_curr,evidence[y][x],nr_planes); depth[y][x]=(float)depth_curr;
	}
}
void depth_sub_pixel(float &depth_f,float *evidence,int nr_planes)
{
	int d0; float v0,v1,v2,dx;
	vec_min_pos(d0,evidence,nr_planes);
	if(d0==0||d0==(nr_planes-1)) dx=0;
	else 
	{
		v0=evidence[d0];
		v1=evidence[d0-1];
		v2=evidence[d0+1];
		dx=(v2+v1-v0-v0==0)?0:0.5f*(v2-v1)/(v2+v1-v0-v0);
	}
	depth_f=float(d0)-dx;
}
void depth_sub_pixel(float&depth_f,double*evidence,int nr_planes)
{
	int d0; double v0,v1,v2,dx;
	vec_min_pos(d0,evidence,nr_planes);
	if(d0==0||d0==(nr_planes-1)) dx=0;
	else 
	{
		v0=evidence[d0];
		v1=evidence[d0-1];
		v2=evidence[d0+1];
		dx=(v2+v1-v0-v0==0)?0:0.5f*(v2-v1)/(v2+v1-v0-v0);
	}
	depth_f=float(d0-dx);
}
bool plane_fit_3p(float para[3],float p0[3],float p1[3],float p2[3])
{
	float at[9],b[3],ata[9],ata_inv[9],atb[3],det; float p0xp1[3],p0xp1_prod_p2;
	qx_cross_product_f3(p0xp1,p0,p1);
	p0xp1_prod_p2=abs(p0xp1[0]*p2[0]+p0xp1[1]*p2[1]+p0xp1[2]*p2[2]);
	if(p0xp1_prod_p2<QX_DEF_THRESHOLD_ZERO)
	{
		//printf("3D points: [%f,%f,%f],[%f,%f,%f],[%f,%f,%f]\n",p0[0],p0[1],p0[2],p1[0],p1[1],p1[2],p2[0],p2[1],p2[2]);
		//
		//printf("3D points: [%f,%f,%f]\n",p0xp1[0],p0xp1[1],p0xp1[2]);
		//getchar();
		return(false);
	}
	else
	{
		b[0]=p0[2]; b[1]=p1[2]; b[2]=p2[2];
		at[0]=p0[0]; at[1]=p1[0]; at[2]=p2[0];
		at[3]=p0[1]; at[4]=p1[1]; at[5]=p2[1];
		//at[6]=p0[2]; at[7]=p1[2]; at[8]=p2[2];
		at[6]=at[7]=at[8]=1.f;
		qx_matrix_product_ata_3x3_at(ata,at);
		atb[0]=at[0]*b[0]+at[1]*b[1]+at[2]*b[2];
		atb[1]=at[3]*b[0]+at[4]*b[1]+at[5]*b[2];
		atb[2]=at[6]*b[0]+at[7]*b[1]+at[8]*b[2];
		inv_3x3(ata_inv,det,ata);
		para[0]=ata_inv[0]*atb[0]+ata_inv[1]*atb[1]+ata_inv[2]*atb[2];
		para[1]=ata_inv[3]*atb[0]+ata_inv[4]*atb[1]+ata_inv[5]*atb[2];
		para[2]=ata_inv[6]*atb[0]+ata_inv[7]*atb[1]+ata_inv[8]*atb[2];
	}
	return(true);
}

bool plane_fit_3p(double para[3],double p0[3],double p1[3],double p2[3])
{
	double at[9],b[3],ata[9],ata_inv[9],atb[3],det; double p0xp1[3],p0xp1_prod_p2;
	qx_cross_product_d3(p0xp1,p0,p1);
	p0xp1_prod_p2=abs(p0xp1[0]*p2[0]+p0xp1[1]*p2[1]+p0xp1[2]*p2[2]);
	if(p0xp1_prod_p2<QX_DEF_THRESHOLD_ZERO)
	{
		memset(para,0,sizeof(double)*3);
		return(false);
	}
	else
	{
		b[0]=p0[2]; b[1]=p1[2]; b[2]=p2[2];
		at[0]=p0[0]; at[1]=p1[0]; at[2]=p2[0];
		at[3]=p0[1]; at[4]=p1[1]; at[5]=p2[1];
		//at[6]=p0[2]; at[7]=p1[2]; at[8]=p2[2];
		at[6]=at[7]=at[8]=1.f;
		qx_matrix_product_ata_3x3_at(ata,at);
		atb[0]=at[0]*b[0]+at[1]*b[1]+at[2]*b[2];
		atb[1]=at[3]*b[0]+at[4]*b[1]+at[5]*b[2];
		atb[2]=at[6]*b[0]+at[7]*b[1]+at[8]*b[2];
		qx_inv_3x3(ata_inv,det,ata);
		para[0]=ata_inv[0]*atb[0]+ata_inv[1]*atb[1]+ata_inv[2]*atb[2];
		para[1]=ata_inv[3]*atb[0]+ata_inv[4]*atb[1]+ata_inv[5]*atb[2];
		para[2]=ata_inv[6]*atb[0]+ata_inv[7]*atb[1]+ata_inv[8]*atb[2];
	}
	return(true);
}
float confidence_from_corr_vol(float *cost,int depth,int nr_planes,float sigma)
{
	float sigma_div,cost_d0,sum_confidence; int d; float confidence;
	if(depth==0||depth==(nr_planes-1)) return(0.f);
	sigma_div=float(1.0/(sigma*sigma));
	cost_d0=cost[depth];
	sum_confidence=1.0;
	for(d=0;d<depth;d++)
	{
		sum_confidence+=exp(-(cost[d]-cost_d0)*(cost[d]-cost_d0)*sigma_div);
	}
	for(d=depth+1;d<nr_planes;d++)
	{
		sum_confidence+=exp(-(cost[d]-cost_d0)*(cost[d]-cost_d0)*sigma_div);
	}
	confidence=1.0f/sum_confidence;
	return(confidence);
}
float confidence_from_corr_vol(int *cost,int depth,int nr_planes,float sigma)
{
	float sigma_div,cost_d0,sum_confidence; int d; float confidence;
	if(depth==0||depth==(nr_planes-1)) return(0.f);
	sigma_div=float(1.0/(sigma*sigma));
	cost_d0=(float)cost[depth];
	sum_confidence=1.0;
	for(d=0;d<depth;d++)
	{
		sum_confidence+=exp(-float(cost[d]-cost_d0)*(cost[d]-cost_d0)*sigma_div);
	}
	for(d=depth+1;d<nr_planes;d++)
	{
		sum_confidence+=exp(-float(cost[d]-cost_d0)*(cost[d]-cost_d0)*sigma_div);
	}
	confidence=1.0f/sum_confidence;
	return(confidence);
}
void confidence_from_corr_vol(float **confidence,float ***cost,int **depth,int h,int w,int nr_planes)
{
	int y,x,d,d0; float cost_d0,sum_confidence; float **cost_y,*cost_yx;
	memset(confidence[0],0,sizeof(float)*h*w);
	for(y=0;y<h;y++) 
	{
		cost_y=cost[y];
		for(x=0;x<w;x++) 
		{
			cost_yx=cost_y[x];
			d0=depth[y][x]; 
			cost_d0=cost_yx[d0];
			sum_confidence=1.0;
			for(d=0;d<d0;d++)
			{
				sum_confidence+=exp(-(cost_yx[d]-cost_d0)*(cost_yx[d]-cost_d0));
			}
			for(d=d0+1;d<nr_planes;d++)
			{
				sum_confidence+=exp(-(cost_yx[d]-cost_d0)*(cost_yx[d]-cost_d0));
			}
			confidence[y][x]=1.0f/sum_confidence;
		}
	}
}
void confidence_from_corr_vol(float **confidence,float ***cost,float **depth,int h,int w,int nr_planes,float sigma)
{
	int y,x,d,d0; float cost_d0,sum_confidence; float **cost_y,*cost_yx;
	if(sigma<1e-6)
	{
		printf("|Sigma| should larger than 0!");
		getchar();
		exit(0);
	}
	float sigma_div=float(1.0/(sigma*sigma));
	memset(confidence[0],0,sizeof(float)*h*w);
	for(y=0;y<h;y++) 
	{
		cost_y=cost[y];
		for(x=0;x<w;x++) 
		{
			cost_yx=cost_y[x];
			d0=int(depth[y][x]+0.5); 
			cost_d0=cost_yx[d0];
			sum_confidence=1.0;
			for(d=0;d<d0;d++)
			{
				sum_confidence+=exp(-(cost_yx[d]-cost_d0)*(cost_yx[d]-cost_d0)*sigma_div);
			}
			for(d=d0+1;d<nr_planes;d++)
			{
				sum_confidence+=exp(-(cost_yx[d]-cost_d0)*(cost_yx[d]-cost_d0)*sigma_div);
			}
			confidence[y][x]=1.0f/sum_confidence;
		}
	}
}
void confidence_from_corr_vol(float **confidence,float ***cost,int **depth,int h,int w,int nr_planes,float sigma)
{
	int y,x,d,d0; float cost_d0,sum_confidence; float **cost_y,*cost_yx;
	if(sigma<1e-6)
	{
		printf("|Sigma| should larger than 0!");
		getchar();
		exit(0);
	}
	float sigma_div=float(1.0/(sigma*sigma));
	memset(confidence[0],0,sizeof(float)*h*w);
	for(y=0;y<h;y++) 
	{
		cost_y=cost[y];
		for(x=0;x<w;x++) 
		{
			cost_yx=cost_y[x];
			d0=depth[y][x]; 
			cost_d0=cost_yx[d0];
			sum_confidence=1.0;
			for(d=0;d<d0;d++)
			{
				sum_confidence+=exp(-(cost_yx[d]-cost_d0)*(cost_yx[d]-cost_d0)*sigma_div);
			}
			for(d=d0+1;d<nr_planes;d++)
			{
				sum_confidence+=exp(-(cost_yx[d]-cost_d0)*(cost_yx[d]-cost_d0)*sigma_div);
			}
			confidence[y][x]=1.0f/sum_confidence;
		}
	}
}
void confidence_from_corr_vol(float **confidence,float ***cost,int **depth,int h,int w,int nr_planes,int win_size,float sigma)
{
	int y,x,d,d0; float cost_d0,sum_confidence1,sum_confidence2; float **cost_y,*cost_yx;
	int half=(win_size>>1); int half_s;
	if(sigma<1e-6)
	{
		printf("|Sigma| should larger than 0!");
		getchar();
		exit(0);
	}
	float sigma_div=float(1.0/(sigma*sigma));
	memset(confidence[0],0,sizeof(float)*h*w);
	int dmax,dmin;
	for(y=0;y<h;y++) 
	{
		cost_y=cost[y];
		for(x=0;x<w;x++) 
		{
			cost_yx=cost_y[x];
			d0=depth[y][x]; 
			if(d0==0||d0==(nr_planes-1)) confidence[y][x]=0;
			else
			{
				cost_d0=cost_yx[d0];
				sum_confidence1=sum_confidence2=1.0;
				half_s=min(min((nr_planes-1)-d0,half),d0);
				dmax=d0+half_s;
				dmin=d0-half_s;
				for(d=dmin;d<d0;d++)
				{
					sum_confidence1+=exp(-(cost_yx[d]-cost_d0)*(cost_yx[d]-cost_d0)*sigma_div);
				}
				for(d=d0+1;d<dmax;d++)
				{
					sum_confidence2+=exp(-(cost_yx[d]-cost_d0)*(cost_yx[d]-cost_d0)*sigma_div);
				}
				confidence[y][x]=1.0f/max(sum_confidence1,sum_confidence2);
			}
		}
	}
}
void confidence_using_entropy(float **confidence,float ***cost,int h,int w,int nr_planes)
{
	int y,x,d; float **cost_y,*cost_x,*conf_y; 
	memset(confidence[0],0,sizeof(float)*h*w);
	for(y=0;y<h;y++) 
	{
		cost_y=cost[y];
		conf_y=confidence[y];
		for(x=0;x<w;x++) 
		{
			float csum,entropy;
			cost_x=cost_y[x];
			for(csum=0.f,d=0;d<nr_planes;d++) csum+=cost_x[d]+0.1f;
			if(csum>QX_DEF_THRESHOLD_ZERO)
			{
				entropy=0;
				float ed;
				for(d=0;d<nr_planes;d++) 
				{
					ed=(cost_x[d]+0.1f)/csum;
					entropy-=ed*log(ed);
				}
			}
			else
			{
				entropy=0;
				float ed=1.0f/nr_planes;
				for(d=0;d<nr_planes;d++) 
				{
					entropy-=ed*log(ed);
				}
			}
			conf_y[x]=entropy;
		}
	}
	float conf_min,conf_max;
	vec_min_val(conf_min,confidence[0],h*w);
	vec_max_val(conf_max,confidence[0],h*w);
	conf_max-=conf_min;
	for(y=0;y<h;y++)
	{
		conf_y=confidence[y];
		for(x=0;x<w;x++)
		{
			//conf_y[x]=1.0f-(conf_y[x]-conf_min)/conf_max;
			conf_y[x]=(conf_y[x]-conf_min)/conf_max;
			conf_y[x]=exp(-conf_y[x]*conf_y[x]/(0.95f*0.95f));
		}
	}
}
void qx_occlusion_solver_left_right(short**depth_left,short**depth_right,int h,int w,int nr_plane,bool solve_both,int downsample_rate)
{
	for(int y=0;y<h;y++) 
	{
		for(int x=0;x<w;x++) 
		{
			short dl=(depth_left[y][x]>>downsample_rate);
			int xr=x-dl;
			short dr=(depth_right[y][xr]>>downsample_rate);
			if(xr>=0)
			{
				if(abs(dl-dr)>=1) 
				{
					depth_left[y][x]=min(depth_left[y][x],depth_right[y][xr]);
				}
				else
				{
					depth_left[y][x]=(depth_left[y][x]+depth_right[y][xr])*0.5;
				}
			}
		}
		if(solve_both)
		{
			for(int x=0;x<w;x++) 
			{
				
				short dr=(depth_right[y][x]>>downsample_rate);
				int xl=x+dr;
				short dl=(depth_left[y][xl]>>downsample_rate);
				if(xl<w)
				{
					if(abs(dl-dr)>=1) 
					{
						depth_right[y][x]=min(depth_left[y][xl],depth_right[y][x]);
					}
					else depth_right[y][x]=(depth_left[y][xl]+depth_right[y][x])*0.5;
				}
			}
		}
	}
}
void qx_detect_occlusion_left_right(unsigned char**mask_left,unsigned char**depth_left,unsigned char**depth_right,int h,int w,int nr_plane)
{
	memset(mask_left[0],0,sizeof(char)*h*w);
	for(int y=0;y<h;y++) 
	{
		for(int x=0;x<w;x++) 
		{
			int d=depth_left[y][x];
			int xr=x-d;
			if(xr>=0)
			{
				if(d==0||abs(d-depth_right[y][xr])>=1)
				{
					//depth_left[y][x]=min(depth_left[y][x],depth_right[y][xr]);
					mask_left[y][x]=255;
				}
			}
			else mask_left[y][x]=255;
		}
	}
}
void qx_detect_occlusion_left_right(unsigned char**mask_left,unsigned char**mask_right,unsigned char**depth_left,unsigned char**depth_right,int h,int w,int nr_plane)
{
	memset(mask_left[0],0,sizeof(char)*h*w);
	memset(mask_right[0],0,sizeof(char)*h*w);
	for(int y=0;y<h;y++) 
	{
		for(int x=0;x<w;x++) 
		{
			int d=depth_left[y][x];
			int xr=x-d;
			if(xr>=0)
			{
				if(d==0||abs(d-depth_right[y][xr])>=1)
				{
					//depth_left[y][x]=min(depth_left[y][x],depth_right[y][xr]);
					mask_left[y][x]=255;
				}
			}
			else mask_left[y][x]=255;
			
			int dr=(depth_right[y][x]);
			int xl=x+dr;
			int dl=(depth_left[y][xl]);
			if(xl<w)
			{
				if(dr==0||abs(dl-dr)>=1) 
				{
					mask_right[y][x]=255;
				}
			}
			else mask_right[y][x]=255;
		}
	}
}
void qx_occlusion_solver_left_right(unsigned char**depth_left,unsigned char**depth_right,unsigned char**temp,int h,int w,int nr_plane)
{
	for(int y=0;y<h;y++) 
	{
		for(int x=0;x<w;x++) 
		{
			int xr=x-int(depth_left[y][x]+0.5);
			if(xr>=0)
			{
				if(depth_left[y][x]!=depth_right[y][xr]) depth_left[y][x]=0;
			}
		}
	}
	//image_display(depth_left,h,w);
	memcpy(temp[0],depth_left[0],sizeof(char)*h*w);
	for(int y=0;y<h;y++) for(int x=w-2;x>=0;x--)
	{
		if(!depth_left[y][x]&&depth_left[y][x+1])
		{
			depth_left[y][x]=depth_left[y][x+1];
		}
	}
	for(int y=0;y<h;y++) for(int x=nr_plane+1;x<w;x++)
	{
		if(!temp[y][x]&&temp[y][x-1])
		{
			temp[y][x]=temp[y][x-1];
		}
		if(depth_left[y][x]&&temp[y][x]) depth_left[y][x]=min(depth_left[y][x],temp[y][x]);
		else if(!depth_left[y][x]) depth_left[y][x]=temp[y][x];
	}
}
void qx_occlusion_solver_left_right(int**depth_left,int**depth_right,int h,int w,int nr_plane,bool solve_both)
{
	for(int y=0;y<h;y++) 
	{
		for(int x=0;x<w;x++) 
		{
			int xr=x-int(depth_left[y][x]+0.5);
			if(xr>=0)
			{
				if(abs(depth_left[y][x]-depth_right[y][xr])>=1) 
				{
					depth_left[y][x]=min(depth_left[y][x],depth_right[y][xr]);
				}
			}
		}
		if(solve_both)
		{
			for(int x=0;x<w;x++) 
			{
				int xl=x+int(depth_right[y][x]+0.5);
				if(xl<w)
				{
					if(abs(depth_left[y][xl]-depth_right[y][x])>=1) 
					{
						depth_right[y][x]=min(depth_left[y][xl],depth_right[y][x]);
					}
				}
			}
		}
	}
}

void qx_occlusion_solver_left_right(unsigned char**depth_left,unsigned char**depth_right,int h,int w,int nr_plane,bool solve_both)
{
	for(int y=0;y<h;y++) 
	{
		for(int x=0;x<w;x++) 
		{
			int xr=x-int(depth_left[y][x]+0.5);
			if(xr>=0)
			{
				if(abs(depth_left[y][x]-depth_right[y][xr])>=1) 
				{
					depth_left[y][x]=min(depth_left[y][x],depth_right[y][xr]);
				}
			}
			else depth_left[y][x]=depth_right[y][0];
		}
		if(solve_both)
		{
			for(int x=0;x<w;x++) 
			{
				int xl=x+int(depth_right[y][x]+0.5);
				if(xl<w)
				{
					if(abs(depth_left[y][xl]-depth_right[y][x])>=1) 
					{
						depth_right[y][x]=min(depth_left[y][xl],depth_right[y][x]);
					}
				}
				else depth_right[y][x]=depth_left[y][w-1];
			}
		}
	}
}

void qx_occlusion_solver_left_right(float**depth_left,float**depth_right,int h,int w,int nr_plane,bool solve_both)
{
	for(int y=0;y<h;y++) 
	{
		for(int x=0;x<w;x++) 
		{
			int xr=x-int(depth_left[y][x]+0.5);
			if(xr>=0)
			{
				if(abs(depth_left[y][x]-depth_right[y][xr])>=1) 
				{
					depth_left[y][x]=min(depth_left[y][x],depth_right[y][xr]);
				}
			}
		}
		if(solve_both)
		{
			for(int x=0;x<w;x++) 
			{
				int xl=x+int(depth_right[y][x]+0.5);
				if(xl<w)
				{
					if(abs(depth_left[y][xl]-depth_right[y][x])>=1) 
					{
						depth_right[y][x]=min(depth_left[y][xl],depth_right[y][x]);
					}
				}
			}
		}
	}
}

void qx_stereo_flip_corr_vol(short***corr_vol_right,short***corr_vol,int h,int w,int nr_plane)
{	
	for(int y=0;y<h;y++)
	{
		for(int x=0;x<w-nr_plane;x++) for(int d=0;d<nr_plane;d++) corr_vol_right[y][x][d]=corr_vol[y][x+d][d];
		for(int x=w-nr_plane;x<w;x++) for(int d=0;d<nr_plane;d++)
		{
			if((x+d)<w) corr_vol_right[y][x][d]=corr_vol[y][x+d][d];
			else corr_vol_right[y][x][d]=corr_vol_right[y][x][d-1];
		}
	}
}
void qx_stereo_flip_corr_vol(double***corr_vol_right,double***corr_vol,int h,int w,int nr_plane)
{	
	for(int y=0;y<h;y++)
	{
		for(int x=0;x<w-nr_plane;x++) for(int d=0;d<nr_plane;d++) corr_vol_right[y][x][d]=corr_vol[y][x+d][d];
		for(int x=w-nr_plane;x<w;x++) for(int d=0;d<nr_plane;d++)
		{
			if((x+d)<w) corr_vol_right[y][x][d]=corr_vol[y][x+d][d];
			else corr_vol_right[y][x][d]=corr_vol_right[y][x][d-1];
		}
	}
}
void qx_stereo_flip_corr_vol(float***corr_vol_right,float***corr_vol,int h,int w,int nr_plane)
{	
	for(int y=0;y<h;y++)
	{
		for(int x=0;x<w-nr_plane;x++) for(int d=0;d<nr_plane;d++) corr_vol_right[y][x][d]=corr_vol[y][x+d][d];
		for(int x=w-nr_plane;x<w;x++) for(int d=0;d<nr_plane;d++)
		{
			if((x+d)<w) corr_vol_right[y][x][d]=corr_vol[y][x+d][d];
			else corr_vol_right[y][x][d]=corr_vol_right[y][x][d-1];
		}
	}
}
void qx_stereo_evaluation_middlebury(float error[3],unsigned char**disparity,unsigned char**disparity_gt,unsigned char***mask,int h,int w,int scalar,float error_threshold)
{
	error_threshold*=scalar;
	int nr_valid[3]={0,0,0};
	int nr_outlier[3]={0,0,0};
	for(int y=0;y<h;y++) for(int x=0;x<w;x++)
	{
		for(int i=0;i<3;i++)
		{
			if(mask[i][y][x]>200)
			{
				nr_valid[i]++;
				if(abs(disparity[y][x]-disparity_gt[y][x])>error_threshold) nr_outlier[i]++;
			}
		}
	}
	for(int i=0;i<3;i++) error[i]=float(nr_outlier[i]*100)/nr_valid[i];
}
double qx_stereo_evaluation_middlebury(unsigned char**disparity,unsigned char**disparity_gt,int h,int w,int scalar,float error_threshold)
{
	error_threshold*=scalar;
	int nr_valid=0;
	int nr_outlier=0;
	for(int y=0;y<h;y++) for(int x=0;x<w;x++)
	{
		if(disparity_gt[y][x]>0)
		{
			nr_valid++;
			if(abs(disparity[y][x]-disparity_gt[y][x])>error_threshold) nr_outlier++;
		}
	}
	return(nr_outlier*100.0/nr_valid);
}
double qx_stereo_evaluation_middlebury(unsigned char**disparity,unsigned char**disparity_gt,unsigned char**mask,int h,int w,int scalar,float error_threshold)
{
	error_threshold*=scalar;
	int nr_valid=0;
	int nr_outlier=0;
	for(int y=0;y<h;y++) for(int x=0;x<w;x++)
	{
		if(mask[y][x]>200)
		{
			nr_valid++;
			if(abs(disparity[y][x]-disparity_gt[y][x])>error_threshold) nr_outlier++;
		}
	}
	return(nr_outlier*100.0/nr_valid);
}
/*plot*/
void plot_2d(float *ys,float *xs,int len,float ymin,float ymax,int h,float xmin,float xmax,int w)
{
	int y,x,i; float ydelta,xdelta;unsigned char **image=qx_allocu(h,w);
	ydelta=(ymax-ymin)/(h-1); xdelta=(xmax-xmin)/(w-1);
	memset(image[0],0,sizeof(unsigned char)*h*w);
	for(i=0;i<len;i++)
	{
		ys[i]=min(max(ys[i],ymin),ymax);
		xs[i]=min(max(xs[i],xmin),xmax);
		y=int((ys[i]-ymin)/ydelta);
		x=int((xs[i]-xmin)/xdelta);
		image[y][x]=255;
	}
	image_display(image,h,w);
	qx_freeu(image);
}
void plot_2d(float *ys,float ymin,float ymax,int h,float xmin,float xmax,float xdelta,int w)
{
	int y,x; float ydelta;unsigned char **image=qx_allocu(h,w);
	ydelta=(ymax-ymin)/(h-1);
	memset(image[0],0,sizeof(unsigned char)*h*w);
	for(x=0;x<w;x++)
	{
		ys[x]=min(max(ys[x],ymin),ymax);
		y=int((ys[x]-ymin)/ydelta);
		image[y][x]=255;
	}
	image_display(image,h,w);
	qx_freeu(image);
}
void plot_hist(int *hist,int h,int w)
{
	int imin,imax,y,x; unsigned char **image;
	image=qx_allocu(h,w);
	memset(image[0],0,sizeof(unsigned char)*h*w);
	vec_max_val(imax,hist,w);
	vec_min_val(imin,hist,w);
	for(x=0;x<w;x++)
	{
		double scale=double(hist[x]-imin)/(imax-imin);
		int height=int(scale*h);
		for(y=h-height;y<h;y++)
			image[y][x]=255;
	}
	image_display(image,h,w);
	qx_freeu(image);
}
void plot_hist(unsigned char **image,int *hist,int h,int w)
{
	int imin,imax,y,x;
	memset(image[0],0,sizeof(unsigned char)*h*w);
	vec_max_val(imax,hist,w);
	vec_min_val(imin,hist,w);
	for(x=0;x<w;x++)
	{
		double scale=double(hist[x]-imin)/(imax-imin);
		int height=int(scale*h);
		for(y=h-height;y<h;y++)
			image[y][x]=255;
	}
}
void plot_hist(double *hist,int h,int w)
{
	double imin,imax; int y,x; unsigned char **image;
	image=qx_allocu(h,w);
	memset(image[0],0,sizeof(unsigned char)*h*w);
	vec_max_val(imax,hist,w);
	vec_min_val(imin,hist,w);
	double im=max(QX_DEF_THRESHOLD_ZERO,(imax-imin));
	for(x=0;x<w;x++)
	{
		double scale=double(hist[x]-imin)/im;
		int height=int(scale*h);
		for(y=h-height;y<h;y++)
			image[y][x]=255;
	}
	image_display(image,h,w);
	qx_freeu(image);
}
void plot_hist(float *hist,int h,int w)
{
	float imin,imax; int y,x; unsigned char **image;
	image=qx_allocu(h,w);
	memset(image[0],0,sizeof(unsigned char)*h*w);
	vec_max_val(imax,hist,w);
	vec_min_val(imin,hist,w);
	for(x=0;x<w;x++)
	{
		double scale=double(hist[x]-imin)/(imax-imin);
		int height=int(scale*h);
		for(y=h-height;y<h;y++)
			image[y][x]=255;
	}
	image_display(image,h,w);
	qx_freeu(image);
}
/*timer*/
void qx_timer::start()
{
	//m_begin=clock();
	
    LARGE_INTEGER li;
    if(!QueryPerformanceFrequency(&li))
        cout << "QueryPerformanceFrequency failed!\n";

    m_pc_frequency = double(li.QuadPart);///1000.0;

    QueryPerformanceCounter(&li);
    m_counter_start = li.QuadPart;
}
double qx_timer::stop()
{
	//m_end=clock(); return ( double(m_end-m_begin)/CLOCKS_PER_SEC );
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return double(li.QuadPart-m_counter_start)/m_pc_frequency;
}
void qx_timer::time_display(char *disp,int nr_frame){ printf("Running time (%s) is: %5.5f Seconds.\n",disp,stop()/nr_frame);}
void qx_timer::fps_display(char *disp,int nr_frame){ printf("Running time (%s) is: %5.5f frame per second.\n",disp,(double)nr_frame/stop());}
void qx_split(int &h,int &w,int len)
{
	int root;
	root=(int)sqrt(double(len));
	for(int i=root;i>0;i++)
	{
		if((len%i)==0)
		{
			w=i;
			h=len/w;
			break;
			i=0;
		}
	}
}
void compute_hypothesis_array(float *hypo,float hmin,float hmax,int len)
{
	float delta=(hmax-hmin)/(len-1);
	hypo[0]=hmin;
	for(int i=1;i<len;i++) hypo[i]=hypo[i-1]+delta;
}
void qx_bounding_box_from_mask(int &y0,int &x0,int &ho,int &wo,unsigned char**mask,int h,int w)
{
	y0=h; x0=w; int yt,xt; yt=xt=-1;
	for(int y=0;y<h;y++) for(int x=0;x<w;x++)
	{
		if(mask[y][x])
		{
			y0=min(y0,y); yt=max(yt,y);
			x0=min(x0,x); xt=max(xt,x);
		}
	}
	ho=yt-y0+1;
	wo=xt-x0+1;
}


//mmx
inline void qx_mmx_compute_max_abs_gradient_sub(unsigned char*Gx,unsigned char*I,unsigned char*Ix)//out=max_abs_difference
//I={I_r,I_g,I_b},Ix={Ix_r,Ix_g,Ix_b},Iy={Iy_r,Iy_g,Iy_b}
{
	_asm
	{
		mov ecx,Gx
		mov eax,I
		mov ebx,Ix
		//pxor mm7,mm7      //Set mm7 (=out) to zero

		//mm0,mm1,mm2: store absolution difference of r,g,b channcel
		//mm6: value of the next pixel(In_r,In_g,In_b); mm7: temp buffer;

		movq mm0,[eax]//I_r
		movq mm6,[ebx]//Ix_r
		movq mm7,mm0
		psubusb mm0,mm6//abs diff of mm0 and mm6
		psubusb mm6,mm7
		por mm0,mm6//get abs diff of mm0 and mm6 (and put it in mm0)

		movq mm1,[eax+8]//I_g
		movq mm6,[ebx+8]//Ix_g
		movq mm7,mm1
		psubusb mm1,mm6//abs diff of mm1 and mm6
		psubusb mm6,mm7
		por mm1,mm6//get abs diff of mm1 and mm6 (and put it in mm1)
		
		movq mm2,[eax+16]//I_b
		movq mm6,[ebx+16]//Ix_b
		movq mm7,mm2
		psubusb mm2,mm6//abs diff of mm2 and mm6
		psubusb mm6,mm7
		por mm2,mm6//get abs diff of mm2 and mm6 (and put it in mm2)

		pmaxub mm0,mm1//compare (find maximum) of the two and store in mm0
		pmaxub mm0,mm2//compare (find maximum) of the two and store in mm0
		movq [ecx],mm0//move mm0 to Gx

		emms
	}
}

void qx_mmx_compute_max_abs_gradient(unsigned char*texture,unsigned char*gradient_x,unsigned char*gradient_y,int h,int w)
{
	int y,x;
	unsigned char I[24],Ix[24],Iy[24],Gx[8],Gy[8];
	for(y=0;y<h-1;y++)
	{
		unsigned char*texture_y=&texture[y*w*3];
		unsigned char*texture_xn;
		unsigned char*texture_yn=&texture[(y+1)*w*3];
		unsigned char*Gx=&gradient_x[y*w];
		unsigned char*Gy=&gradient_y[y*w];
		int yn=y+1;
		for(x=0;x<w-1;x+=8)
		{
			for(int i=0;i<8;i++)
			{
				I[0+i]=*texture_y++;//R
				I[8+i]=*texture_y++;//G
				I[16+i]=*texture_y++;//B
				Iy[0+i]=*texture_yn++;//R
				Iy[8+i]=*texture_yn++;//G
				Iy[16+i]=*texture_yn++;//B
			}
			texture_xn=texture_y;
			for(int i=0;i<7;i++)
			{
				Ix[i]=I[i+1];
				Ix[8+i]=I[9+i];
				Ix[16+i]=I[17+i];
			}
			Ix[7]=*texture_xn++;//R
			Ix[15]=*texture_xn++;//G
			Ix[23]=*texture_xn++;//B
			qx_mmx_compute_max_abs_gradient_sub(Gx,I,Ix);
			qx_mmx_compute_max_abs_gradient_sub(Gy,I,Iy);
			Gx+=8;
			Gy+=8;
		}
		int x0=((w>>3)<<3);
		int xt=x0+w%8;
		for(x=x0;x<=xt;x++)
		{
			int xn=x+1;
			int id=(y*w+x);
			gradient_x[id]=qx_compute_RGB_distance_max(texture,(y*w+xn),id);
			gradient_y[id]=qx_compute_RGB_distance_max(texture,(yn*w+x),id);
		}
		int id=(y*w+w-1);
		gradient_x[id]=gradient_x[id-1];
		gradient_y[id]=qx_compute_RGB_distance_max(texture,(yn*w+w-1),id);
	}
	memcpy(&gradient_y[(h-1)*w],&gradient_y[(h-2)*w],sizeof(char)*w);
	for(x=0;x<w-1;x++)
	{
		int xn=x+1;
		int id=(y*w+x);
		gradient_x[id]=qx_compute_RGB_distance_max(texture,(y*w+xn),id);
	}
	int id=(y*w+w-1);
	gradient_x[id]=gradient_x[id-1];
}



inline void qx_mmx_compute_abs_of_2_gray_image_sub(unsigned char*out,unsigned char*out2,unsigned char*a,unsigned char*b)//out=max_abs_difference
//a={a0,a1,a2,a3,a4,a5,a6,a7}
{
	_asm
	{
		mov ecx,out
		mov edx,out2
		mov eax,a
		mov ebx,b
		movq mm0,[eax]//a
		movq mm6,[ebx]//b
		movq mm7,mm0
		psubusb mm0,mm6//abs diff of mm0 and mm6
		psubusb mm6,mm7
		por mm0,mm6//get abs diff of mm0 and mm6 (and put it in mm0)

		movq [ecx],mm0//move mm0 to Gx


		movq mm1,[eax+8]//a
		movq mm2,[ebx+8]//b
		movq mm3,mm1
		psubusb mm1,mm2//abs diff of mm0 and mm6
		psubusb mm2,mm3
		por mm1,mm2//get abs diff of mm0 and mm6 (and put it in mm0)

		movq [edx],mm1//move mm0 to Gx


		emms
	}
}

void qx_mmx_compute_abs_of_2_gray_image(unsigned char*out,unsigned char*a,unsigned char*b,int h,int w)
{
	int y,x;
	for(y=0;y<h;y++)
	{
		unsigned char*out_y=&out[y*w];
		unsigned char*out_y2=&out[y*w+8];
		unsigned char*a_=&a[y*w];
		unsigned char*b_=&b[y*w];
		for(x=0;x<w;x+=16)
		{
			qx_mmx_compute_abs_of_2_gray_image_sub(out_y,out_y2,a_,b_);
			out_y+=16;
			out_y2+=16;
			a_+=16;
			b_+=16;
		}
		int x0=((w>>4)<<4);
		int xt=x0+w%16;
		for(x=x0;x<=xt;x++)
		{
			int id=(y*w+x);
			out[id]=abs((double)a[id]-(double)b[id]);
		}
	}
}