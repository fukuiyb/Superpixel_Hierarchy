/*$Id: qx_basic_file.h,v 1.46 2007/04/04 02:15:14 liiton Exp $*/
/*******************************************************
\Author:	Qingxiong Yang (liiton)
\Function:	common functions.
********************************************************/
#ifndef QX_BASIC_FILE_H
#define QX_BASIC_FILE_H

bool qx_set_registry_key(HKEY basekey,LPCWSTR subkey,LPCWSTR subsubkey,WCHAR*wkeyvalue);
WCHAR*qx_get_registry_key(HKEY basekey,LPCWSTR subkey,LPCWSTR subsubkey);
struct tm*qx_file_time(char*filename,int time_type);//0:create, 1:modify, 2: access
inline int qx_file_time_2_minute(char*filename,int time_type){struct tm*clock=qx_file_time(filename,time_type); return((((clock->tm_year-100)*365+clock->tm_yday)*24+clock->tm_hour)*60+clock->tm_min);};
int qx_current_system_gmtime_2_minute();
int qx_current_system_gmtime_2_second();
int qx_argv0_2_folder(char*folder,char*argv0);
int qx_getcwd(char*folder);
inline void qx_get_suffix(char out[10],char*in){int str_len=strlen(in); char*in_=in+str_len; while(*(--in_)!='.'); sprintf_s(out,10,"%s",in_);}

inline void qx_remove_space_key(char *str){int j=strlen(str)-2; while(isspace(str[j])) str[j--]=NULL;}
int qx_string_2_words(char*string,char**words,int max_nr_word,char separator=' ');/*return # of words*/
inline void qx_remove_suffix(char*out,char*in,int suffix_length){int str_len=strlen(in)-suffix_length; memcpy(out,in,sizeof(char)*str_len); out[str_len]=0;}
inline void qx_remove_prefix(char*out,char*in,int prefix_length){int str_len=strlen(in)-prefix_length; memcpy(out,&(in[prefix_length]),sizeof(char)*str_len); out[str_len]=0;}
bool qx_is_file_exist(char*filename);
int qx_get_nr_of_lines(char *filename);
int qx_open_file_c(char *filename,char **out,int w);
int get_nr_file(char *file_folder,char *file_format,bool display_files=false);
int get_files(char **files,char *file_folder,char *file_format,int str_length,int max_nr_file=0);
int delete_files(char *file_folder,char *file_format);
bool qx_copy_file_replace(char*filename_out,char*filename_in);
int qx_copy_file(char*filename_out,char*filename_in,bool replace=false);
int qx_copy_folder(char*folder_out,char*folder_in,bool replace=false,char*file_format="*.*");//from one folder to another
void file_create(char *file_path);
int file_open(char *file_path,char *out,int len);
void file_save(char *file_path,char *out,int len);
int file_open(char *file_path,unsigned char *out,int len);
void file_save(char *file_path,unsigned char *out,int len);
int file_open(char *file_path,int *out,int len);
void file_save(char *file_path,int *out,int len);
int file_open(char *file_path,double *out,int len);
void file_save(char *file_path,double *out,int len);
int file_open(char *file_path,float *out,int len);
void file_save(char *file_path,float *out,int len);
int file_open_ascii(char *file_path,int *out,int len);
int file_open_ascii(char*file_path,unsigned int*out,int len);
int file_open_ascii(char *file_path,unsigned char *out,int len);
int file_open_ascii(char *file_path,char *out,int len);
int file_open_ascii(char *file_path,double *out,int len);
int file_open_ascii(char *file_path,float *out,int len,int nr_escape=0);
void file_save_ascii(char *file_path,unsigned char *out,int len);
void file_save_ascii(char *file_path,double *out,int len,char *str=NULL);
void file_save_ascii(char *file_path,float *out,int len);
void file_save_ascii(char *file_path,int *out,int len);
void file_save_ascii(char *file_path,char *out);
void file_save_ascii_2d(char*file_path,float**out,int h,int w,char*str=NULL);
void file_save_ascii_2d(char*file_path,double**out,int h,int w,char*str=NULL);
void file_save_ascii_2d(char*file_path,double*out,int h,int w,char*str=NULL);
void file_save_ascii_2d(char *file_path,unsigned char **out,int h,int w);
void file_save_ascii_2d(char *file_path,unsigned int **out,int h,int w);
void file_save_ascii_2d(char *file_path,int **out,int h,int w);
void file_save_ascii_2d(char *file_path,char **out,int h,int w);
int file_open_ascii_2d(char *file_path,char **out,int h,int w);
void file_update(char *file_path,float *out,int len);
void file_update(char *file_path,int *out,int len);
void file_update_ascii(char *file_path,int *out,int len);
void file_update_ascii(char *file_path,float *out,int len);
void file_update_ascii(char *file_path,char *out);
void file_update_ascii_2d(char *file_path,double **out,int h,int w,char *str=NULL);
int qx_save_wrl(char*filename,float*color_in,float*point_in,int nr_point);
int qx_save_wrl(char*filename,float**color_in,float**point_in,int nr_point);
int qx_save_wrl(char*filename,float***color_in,float***point_in,int nr_point);
int qx_save_wrl_triangle(char*filename,float**color_in,float**point_in,int nr_point,int**triangle_index,int nr_triangle);
int qx_save_wrl(char*filename,double**color_in,double**point_in,int nr_point);
int qx_save_wrl_triangle(char*filename,double**color_in,double**point_in,int nr_point,int**triangle_index,int nr_triangle);
//void qx_save_ply_special(char* file_name,float ***points,float ***normal,unsigned char ***image,unsigned char **mask,int **index,int h,int w);/*image can be NULL*/
void qx_save_ply(char* file_name,float ***points,float ***normal,unsigned char ***image,unsigned char **mask,int **index,int h,int w);/*image & normal can be NULL*/
void qx_save_ply_ascii(char* file_name,float ***points,float ***normal,unsigned char ***image,unsigned char **mask,int **index,int h,int w);/*image can be NULL*/
void save_ply(char* file_name,float **depth,float ***normal,unsigned char ***image,unsigned char **mask,int **index,int h,int w,float sx=1.0,float sy=1.0,float sz=1.0f,int y0=-1,int x0=-1);
void save_ply(char* file_name,float **depth,float ***normal,unsigned char ***image,int h,int w,float sx=1.0,float sy=1.0,float sz=1.0f,int y0=-1,int x0=-1);
int save_iv(char* file_name,float **depth,unsigned char ***image,int h,int w,int point_size,float depth_scale=1.0f);
int save_iv(char* file_name,float **depth,unsigned char ***image,int ymin,int ymax,int xmin,int xmax,int point_size,float depth_scale);
int save_iv_triangles(char* file_name,float **depth,unsigned char ***image,int ymin,int ymax,int xmin,int xmax,int point_size,float depth_scale,float xy_scale);
int save_iv(char* file_name,float **depth,unsigned char ***image,unsigned char **mask,int h,int w,int point_size,float depth_scale=1.0f);
int save_iv_triangles(char* file_name,float **depth,unsigned char ***image,unsigned char **mask,int h,int w,int point_size,float depth_scale,float xy_scale);
void matrix_save_ascii(char *file_path,double **in,int h,int w);

void FileRead_binary(char *FileName, int N, int M, int L,float ***Mat);
void FileSave_binary(char *SavePath,float *SaveVec,int N,int M,int L,char * FormatStr);
void	FileRead		(char *FileName, int N, int M, double **Mat);
void	FileRead		(char *FileName, int N, int M, float **Mat);
void	FileRead		(char *FileName, int N, int M, int L,float ***Mat);
void	FileSave		(char *SavePath, float *SaveVec, int N, int M, int L, char * FormatStr);
void FileRead(char *FileName,float ****Mat);
void FileSave(char *SavePath,double *SaveVec,int N,int M,int L,int K);

int qx_file_save_sift_descriptor(char *file_path,float *desc,int nr_desc,int desc_size);
int qx_file_open_sift_descriptor(char *file_path,float *desc,int desc_size);/*return # of descriptors*/
int qx_file_save_sift_descriptor_ascii(char *file_path,float *desc,int nr_desc,int desc_size);
int qx_file_open_sift_descriptor_ascii(char *file_path,float *desc,int desc_size);/*return # of descriptors*/

inline void qx_create_director(char *str){if((_chdir(str))!=0) _mkdir(str);}
inline void qx_delete_director(char *str){_rmdir(str);}

void qx_save_image_list(char *file_path,char **out,int h,int w);
void qx_open_image_list(char *file_path,char **out,int h,int w);
int qx_open_image_list(char *file_path,char **out,int str_len);
int qx_file_open_acts(char*filename,float scale,int nr_camera,double **pmat,double **kmat);
int*qx_file_open_ascii_with_len(char*filename,int&len);
bool qx_file_save_ascii_with_len(char *filename,int *out,int len);
double*qx_file_open_ascii_with_len_d(char*filename,int&len);
bool qx_file_save_ascii_with_len_d(char *filename,double*out,int len);
double**qx_file_open_ascii_2d_with_len(char*filename,int&h,int&w);
void qx_file_open_ascii_2d_with_len(char*filename,double**out,int h,int w);
bool qx_file_save_ascii_2d_with_len(char *filename,double**out,int h,int w);
#endif /*QX_BASIC_FILE_H*/