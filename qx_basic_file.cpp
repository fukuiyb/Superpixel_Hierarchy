/*$Id: basic.cpp,v 1.43 2007/04/04 02:15:14 liiton Exp $*/
#include "basic.h"
#include "sys/stat.h"
#include "qx_basic_file.h"

bool qx_set_registry_key(HKEY basekey,LPCWSTR subkey,LPCWSTR subsubkey,WCHAR*wkeyvalue)
{
	HKEY   hkey;
#ifdef UNICODE
	LONG lResult=RegOpenKeyEx(basekey,subkey,0,KEY_SET_VALUE,&hkey);
#else
	char subkey_[512]={0};
	WideCharToMultiByte(CP_ACP,0,subkey,wcslen(subkey)+1,subkey_,512,NULL,NULL);
	LONG lResult=RegOpenKeyEx(basekey,subkey_,0,KEY_SET_VALUE,&hkey);
#endif
	if(lResult==ERROR_SUCCESS)
	{
		WCHAR value[512]={0}; DWORD size=512;
#ifdef UNICODE
		lResult=RegSetValueEx(hkey,subsubkey,NULL,REG_SZ,(LPBYTE)wkeyvalue,wcslen(wkeyvalue)*2);
#else
		char wkeyvalue_[512]={0}; WideCharToMultiByte(CP_ACP,0,wkeyvalue,wcslen(wkeyvalue)+1,wkeyvalue_,512,NULL,NULL);
		if(subsubkey!=NULL)
		{
			char subsubkey_[512]={0};
			WideCharToMultiByte(CP_ACP,0,subsubkey,wcslen(subsubkey)+1,subsubkey_,512,NULL,NULL);
			lResult=RegSetValueEx(hkey,subsubkey_,NULL,REG_SZ,(LPBYTE)wkeyvalue_,strlen(wkeyvalue_));
		}
		else
		{
			lResult=RegSetValueEx(hkey,NULL,NULL,REG_SZ,(LPBYTE)wkeyvalue_,strlen(wkeyvalue_));
		}
#endif
		RegCloseKey(hkey);
		if(lResult==ERROR_SUCCESS)
		{
			return(true);
		}
	}
	return(false);
}
WCHAR*qx_get_registry_key(HKEY basekey,LPCWSTR subkey,LPCWSTR subsubkey)
{
	HKEY   hkey;
#ifdef UNICODE
	LONG lResult=RegOpenKeyEx(basekey,subkey,0,KEY_READ,&hkey);
#else
	char subkey_[512]={0};
	WideCharToMultiByte(CP_ACP,0,subkey,wcslen(subkey)+1,subkey_,512,NULL,NULL);
	LONG lResult=RegOpenKeyEx(basekey,subkey_,0,KEY_READ,&hkey);
#endif
	if(lResult==ERROR_SUCCESS)
	{
		WCHAR value[512]={0}; DWORD size=512;
#ifdef UNICODE
		lResult=RegQueryValueEx(hkey,subsubkey,NULL,NULL,(LPBYTE)value,&size);//REG_SZ
#else
		char value_[512]={0};
		if(subsubkey!=NULL)
		{
			char subsubkey_[512]={0};
			WideCharToMultiByte(CP_ACP,0,subsubkey,wcslen(subsubkey)+1,subsubkey_,512,NULL,NULL);
			lResult=RegQueryValueEx(hkey,subsubkey_,NULL,NULL,(BYTE*)value_,&size);//REG_SZ
		}
		else 
		{
			lResult=RegQueryValueEx(hkey,NULL,NULL,NULL,(BYTE*)value_,&size);//REG_SZ
		}
		MultiByteToWideChar(CP_ACP,0,value_,strlen(value_),value,512);
#endif
		RegCloseKey(hkey);
		if(lResult==ERROR_SUCCESS)
		{
			return(value);
		}
	}
	return(NULL);
}
struct tm*qx_file_time(char*filename,int time_type)//0:create, 1:modify, 2: access
{
	struct stat attrib;			// create a file attribute structure
	stat(filename,&attrib);
	struct tm*clock;
	switch (time_type)
	{
	case 0:
		clock=gmtime(&(attrib.st_ctime));
		break;
	case 1:
		clock=gmtime(&(attrib.st_mtime));
		break;
	case 2:
		clock=gmtime(&(attrib.st_atime));
		break;
	default:
		clock=NULL;
		break;
	}
	//printf("Year: [%d],Month: [%d], Day: [%d], Hour: [%d], Min: [%d], Sec: [%d]\n",clock->tm_year,clock->tm_mon,clock->tm_mday,clock->tm_hour,clock->tm_min,clock->tm_sec);
	return(clock);
}
int qx_current_system_gmtime_2_minute()
{
	time_t rawtime;
	struct tm *clock;
	time (&rawtime);
	clock = gmtime(&rawtime);
	//printf("Year: [%d],Month: [%d], Day: [%d], Hour: [%d], Min: [%d], Sec: [%d]\n",clock->tm_year,clock->tm_mon,clock->tm_mday,clock->tm_hour,clock->tm_min,clock->tm_sec);
	return((((clock->tm_year-100)*365+clock->tm_yday)*24+clock->tm_hour)*60+clock->tm_min);
}
int qx_current_system_gmtime_2_second()
{
	time_t rawtime;
	struct tm *clock;
	time (&rawtime);
	clock = gmtime(&rawtime);
	//printf("Year: [%d],Month: [%d], Day: [%d], Hour: [%d], Min: [%d], Sec: [%d]\n",clock->tm_year,clock->tm_mon,clock->tm_mday,clock->tm_hour,clock->tm_min,clock->tm_sec);
	return(((((clock->tm_year-100)*365+clock->tm_yday)*24+clock->tm_hour)*60+clock->tm_min)*60+clock->tm_sec);
}

int qx_argv0_2_folder(char*folder,char*argv0)
{
	char*folder_=folder;
	int folder_len=0;
	for(int i=strlen(argv0);i>=0;i--)
	{
		if(argv0[i]=='\\')
		{
			folder_len=i+1;
			i=-1;
		}
	}
	for(int i=0;i<folder_len;i++)
	{
		if(argv0[i]=='\\')
		{
			*folder_++='/';
		}
		else *folder_++=argv0[i];
	}
	*folder_++='\0';
	return(folder_len);
}
int qx_getcwd(char*folder)
{
	char str[900];
	getcwd(str,900);
	char*folder_=folder;
	int str_len=strlen(str);
	for(int i=0;i<str_len;i++)
	{
		if(str[i]=='\\')
		{
			*folder_++='/';
		}
		else *folder_++=str[i];
	}
	*folder_++='\0';
	return(strlen(folder));
}
int qx_string_2_words(char*string,char**words,int max_nr_word,char separator)/*return # of words*/
{
	int str_len=strlen(string);
	int nr_word=0;
	char*str=words[nr_word];
	int i=0;
	while(i<str_len)
	{
		if(string[i]!=separator)
		{
			*str++=string[i];
			i++;
		}
		else
		{
			//*str++=' ';
			*str++='\0';
			str=words[++nr_word];
			if(nr_word>=max_nr_word)
			{
				i=str_len;
			}
			else
			{
				while(string[i]==' ') i++;
			}
		}
	}
	return(nr_word);
}
bool qx_is_file_exist(char*filename)
{
	ifstream d_file;
	d_file.open(filename);
	if (!d_file.is_open())
	{
		return(false);
	}
	else
	{
		d_file.close();
		return(true);
	}
}
int qx_get_nr_of_lines(char *filename)
{
	ifstream d_file;
	d_file.open(filename);
	int lineCount=0;
	if (!d_file.is_open())
	{
		cout << "File " << filename << " does not exist in the client's current directory" << endl;
	}
	else
	{
		string t;
		while(getline(d_file, t, '\n'))
		++lineCount;
		d_file.close();
	}
	return(lineCount);
}
int qx_open_file_c(char *filename,char **out,int w)
{
	ifstream d_file;
	d_file.open(filename);
	int counter=0;
	if (!d_file.is_open())
	{
		cout << "File " << filename << " does not exist in the client's current directory" << endl;
	}
	else
	{
		string t;
		while(getline(d_file, t, '\n'))
		{
			sprintf_s(out[counter++],w,"%s",t.data());
		}
		d_file.close();
	}
	return(counter);
}
int get_nr_file(char *file_folder,char *file_format,bool display_files)
{	
	int nr_file=0;
	struct _finddata_t pgm_file;
	intptr_t hFile;
	_chdir(file_folder);
	if((hFile=_findfirst(file_format,&pgm_file))!=-1)
	{
		if(display_files) printf("%s\n",pgm_file.name);
		nr_file++;
		while(_findnext(hFile,&pgm_file)==0)
		{
			if(display_files) printf("%s\n",pgm_file.name);
			nr_file++;
		}
	}
	_findclose(hFile);
	return(nr_file);
}
int get_files(char **files,char *file_folder,char *file_format,int str_length,int max_nr_file)
{	
	int nr_file=0;
	if(max_nr_file<=0) max_nr_file=get_nr_file(file_folder,file_format,false);
	struct _finddata_t pgm_file;
	//long hFile;
	intptr_t hFile;
	_chdir(file_folder);
	if((hFile=_findfirst(file_format,&pgm_file))!=-1)
	{
		sprintf_s(files[nr_file++],str_length,"%s",pgm_file.name);
		while(_findnext(hFile,&pgm_file)==0&&nr_file<max_nr_file)
		{
			//printf("%s\n",pgm_file.name);
			//nr_file++;
			sprintf_s(files[nr_file++],str_length,"%s",pgm_file.name);
		}
	}
	_findclose(hFile);
	return(nr_file);
}
int delete_files(char *file_folder,char *file_format)
{	
	int nr_file=0; char str[200];
	struct _finddata_t pgm_file;
	//long hFile;
	intptr_t hFile;
	_chdir(file_folder);
	if((hFile=_findfirst(file_format,&pgm_file))!=-1)
	{
		sprintf_s(str,200,"%s/%s",file_folder,pgm_file.name);
		remove(str);
		nr_file++;
		while(_findnext(hFile,&pgm_file)==0)
		{
			sprintf_s(str,200,"%s/%s",file_folder,pgm_file.name);
			remove(str);
			nr_file++;
			printf("[%d]: %s\n",nr_file,pgm_file.name);
			//nr_file++;
			//sprintf_s(files[nr_file++],str_length,"%s",pgm_file.name);
		}
	}
	_findclose(hFile);
	return(nr_file);
}
bool qx_copy_file_replace(char*filename_out,char*filename_in)
{
	//if(qx_is_file_exist(filename_out)) delete(filename_out);
	//fstream f(filename_in,fstream::in|fstream::binary);
	//f<<noskipws;
	//istream_iterator<unsigned char> begin(f);
	//istream_iterator<unsigned char> end;

	//fstream f2(filename_out,fstream::out|fstream::trunc|fstream::binary);
	//ostream_iterator<char> begin2(f2);
	//copy(begin,end,begin2);

	std::ifstream src; // the source file
    std::ofstream dest; // the destination file
    src.open(filename_in,std::ios::binary); // open in binary to prevent jargon at the end of the buffer
    dest.open(filename_out,std::ios::binary); // same again, binary
    if (!src.is_open() || !dest.is_open())
        return false; // could not be copied
    dest << src.rdbuf (); // copy the content
    dest.close (); // close destination file
    src.close (); // close source file
    return true; // file copied successfully

}
int qx_copy_file(char*filename_out,char*filename_in,bool replace)
{
	if(replace) {qx_copy_file_replace(filename_out,filename_in); return(1);}
	else if(!qx_is_file_exist(filename_out)){qx_copy_file_replace(filename_out,filename_in); return(1);}
	return(0);
}
int qx_copy_folder(char*folder_out,char*folder_in,bool replace,char*file_format)
{
	if((_chdir(folder_in))==0)
	{
		qx_create_director(folder_out);
		int nr_file,nr_file_copy; char filename_out[300],filename_in[300];
		struct _finddata_t file_name;
		//long hFile;
		intptr_t hFile;
		_chdir(folder_in);
		nr_file=nr_file_copy=0;
		if((hFile=_findfirst(file_format,&file_name))!=-1)
		{
			sprintf_s(filename_in,300,"%s/%s",folder_in,file_name.name);
			sprintf_s(filename_out,300,"%s/%s",folder_out,file_name.name);
			nr_file_copy+=qx_copy_file(filename_out,filename_in,replace);
			nr_file++;
			printf("[%d,%d]: %s\n",nr_file_copy,nr_file,file_name.name);
			_chdir(folder_in);
			while(_findnext(hFile,&file_name)==0)
			{
				sprintf_s(filename_in,300,"%s/%s",folder_in,file_name.name);
				sprintf_s(filename_out,300,"%s/%s",folder_out,file_name.name);
				nr_file_copy+=qx_copy_file(filename_out,filename_in,replace);
				nr_file++;
				printf("[%d,%d]: %s\n",nr_file_copy,nr_file,file_name.name);
				_chdir(folder_in);
			}
		}
		_findclose(hFile);
		printf("[%d]/[%d] files are copied.\n",nr_file_copy,nr_file);
		return(nr_file_copy);
	}
	else
	{
		printf("Folder [%s] does not EXIST!\n",folder_in);
		getchar();
		return(-1);
	}
}

void file_create(char *file_path)
{
	FILE * file_in;
	//file_in= fopen(file_path, "w+");
	fopen_s(&file_in,file_path, "w+");
	fclose(file_in);
}
int file_open(char *file_path,char *out,int len)
{
	FILE * file_in;
	//file_in= fopen(file_path, "rb");
	fopen_s(&file_in,file_path, "rb");
	if(file_in==NULL)
	{
		printf("qx_basic_file: The file %s does NOT EXIST!!\n",file_path);
		exit(-1);
	}
	fread(out,sizeof(char),len,file_in);
	fclose(file_in);
	return(0);
}
void file_save(char *file_path,char *out,int len)
{
	FILE * file_out;
	//file_out= fopen(file_path, "wb");
	fopen_s(&file_out,file_path, "wb");
	if(file_out==NULL)
	{
		printf("qx_basic_file: The file %s does NOT EXIST!!\n",file_path);;
		exit(1);
	}
	fwrite(out,sizeof(char),len,file_out);
	fclose(file_out);
}
int file_open(char *file_path,unsigned char *out,int len)
{
	FILE * file_in;
	//file_in= fopen(file_path, "rb");
	fopen_s(&file_in,file_path, "rb");
	if(file_in!=NULL)
	{
		fread(out,sizeof(unsigned char),len,file_in);
		fclose(file_in);
	}
	else
	{
		printf("qx_basic_file: Can not open file: %s\n",file_path);
		getchar();
		exit(-1);
	}
	return(0);
}
void file_save(char *file_path,unsigned char *out,int len)
{
	FILE * file_out;
	fopen_s(&file_out,file_path, "wb");
	fwrite(out,sizeof(unsigned char),len,file_out);
	fclose(file_out);
}
int file_open(char *file_path,int *out,int len)
{
	FILE * file_in;
	//file_in= fopen(file_path, "rb");
	fopen_s(&file_in,file_path, "rb");
	if(file_in!=NULL)
	{
		fread(out,sizeof(int),len,file_in);
		fclose(file_in);
	}
	else
	{
		printf("qx_basic_file: Can not open file: %s\n",file_path);
		getchar();
		exit(-1);
	}
	return(0);
}
void file_save(char *file_path,int *out,int len)
{
	FILE * file_out;
	//file_out= fopen(file_path, "wb");
	fopen_s(&file_out,file_path, "wb");
	//for (int i=0; i<len; i++)    
	//	fprintf(StreamSave,FormatStr,out[i]);	
	fwrite(out,sizeof(int),len,file_out);
	fclose(file_out);
}
int file_open(char *file_path,float *out,int len)
{
	FILE * file_in;
	//file_in= fopen(file_path, "rb");
	fopen_s(&file_in,file_path, "rb");
	if(file_in!=NULL)
	{
		fread(out,sizeof(float),len,file_in);
		fclose(file_in);
	}
	else
	{
		printf("qx_basic_file: Can not open file: %s\n",file_path);
		getchar();
		exit(-1);
	}
	return(0);
}
void file_save(char *file_path,float *out,int len)
{
	FILE * file_out;
	//file_out= fopen(file_path, "wb");
	fopen_s(&file_out,file_path, "wb");
	//for (int i=0; i<len; i++)    
	//	fprintf(StreamSave,FormatStr,out[i]);	
	fwrite(out,sizeof(float),len,file_out);
	fclose(file_out);
}
int file_open(char *file_path,double *out,int len)
{
	FILE * file_in;
	//file_in= fopen(file_path, "rb");
	fopen_s(&file_in,file_path, "rb");
	if(file_in!=NULL)
	{
		fread(out,sizeof(double),len,file_in);
		fclose(file_in);
	}
	else
	{
		printf("qx_basic_file: Can not open file: %s\n",file_path);
		getchar();
		exit(-1);
	}
	return(0);
}
void file_save(char *file_path,double *out,int len)
{
	FILE * file_out;
	//file_out= fopen(file_path, "wb");
	fopen_s(&file_out,file_path, "wb");
	fwrite(out,sizeof(double),len,file_out);
	fclose(file_out);
}
int file_open_ascii(char *file_path,int*out,int len)
{
	FILE *file_in; char str[65]; int i;
	//file_in=fopen(file_path,"r");
	fopen_s(&file_in,file_path,"r");
	if(file_in!=NULL)
	{
		fseek(file_in,0,SEEK_SET);	
		for(i=0;i<len;i++ )
		{ 
			//fscanf(file_in,"%s",str); 
			fscanf_s(file_in,"%s",str,65); 
			out[i]=atoi(str);
		}
		fclose(file_in);
	}
	else
	{
		printf("qx_basic_file: Can not open file: %s\n",file_path);
		getchar();
		exit(-1);
	}
	return(0);
}

int file_open_ascii(char*file_path,unsigned int*out,int len)
{
	FILE *file_in; char str[65]; int i;
	//file_in=fopen(file_path,"r");
	fopen_s(&file_in,file_path,"r");
	if(file_in!=NULL)
	{
		fseek(file_in,0,SEEK_SET);	
		for(i=0;i<len;i++ )
		{ 
			//fscanf(file_in,"%s",str); 
			fscanf_s(file_in,"%s",str,65); 
			out[i]=atoi(str);
		}
		fclose(file_in);
	}
	else
	{
		printf("qx_basic_file: Can not open file: %s\n",file_path);
		getchar();
		exit(-1);
	}
	return(0);
}
int file_open_ascii(char *file_path,unsigned char *out,int len)
{
	FILE *file_in; char str[65]; int i;
	//file_in=fopen(file_path,"r");
	fopen_s(&file_in,file_path,"r");
	if(file_in!=NULL)
	{
		fseek(file_in,0,SEEK_SET);	
		for(i=0;i<len;i++ )
		{ 
			//fscanf(file_in,"%s",str); 
			fscanf_s(file_in,"%s",str,65); 
			out[i]=atoi(str);
		}
		fclose(file_in);
	}
	else
	{
		printf("qx_basic_file: Can not open file: %s\n",file_path);
		getchar();
		exit(-1);
	}
	return(0);
}
int file_open_ascii(char *file_path,char *out,int len)
{
	FILE *file_in; int i;
	//file_in=fopen(file_path,"r");
	fopen_s(&file_in,file_path,"r");
	if(file_in!=NULL)
	{
		fseek(file_in,0,SEEK_SET);	
		fscanf_s(file_in,"%s",out,len); 
		fclose(file_in);
	}
	else
	{
		printf("qx_basic_file: Can not open file: %s\n",file_path);
		getchar();
		exit(-1);
	}
	return(0);
}
int file_open_ascii(char *file_path,double *out,int len)
{
	FILE *file_in; char str[65]; int i;
	//file_in=fopen(file_path, "r");
	fopen_s(&file_in,file_path,"r");
	if(file_in!=NULL)
	{
		fseek(file_in,0,SEEK_SET);	
		for(i=0;i<len;i++ )
		{ 
			//fscanf(file_in,"%s",str); 
			fscanf_s(file_in,"%s",str,65); 
			out[i]=atof(str);
		}
		fclose(file_in);
	}
	else
	{
		printf("qx_basic_file: Can not open file: %s\n",file_path);
		getchar();
		exit(-1);
	}
	return(0);
}
int file_open_ascii(char *file_path,float *out,int len,int nr_escape)
{
	FILE * file_in; char str[65]; int i;
	//file_in= fopen(file_path, "r");
	if(fopen_s(&file_in,file_path,"r")==0)
	{
		fseek(file_in, 0, SEEK_SET);
		for(i=0;i<nr_escape;i++) 
			//fscanf(file_in,"%s",str);
			fscanf_s(file_in,"%s",str,65);
		for(i=0;i<len;i++)
		{ 
			//fscanf(file_in,"%s",str); 
			fscanf_s(file_in,"%s",str,65); 
			out[i]=(float)atof(str);
		}
		fclose(file_in);
	}
	else
	{
		printf("qx_basic_file: Can not open file: %s\n",file_path);
		getchar();
		exit(-1);
	}
	return(0);
}
void file_save_ascii(char *file_path,double *out,int len,char *str)
{
	FILE * fileout; int i;
	//fileout= fopen(file_path,"w");
	if(fopen_s(&fileout,file_path,"w")==0)
	{
		for(i=0;i<len;i++)    
		{	
			if(str==NULL) 
			{
				if(abs(out[i])>1) fprintf(fileout,"%10.20f ",out[i]);
				else fprintf(fileout,"%1.29f ",out[i]);
			}
			else 
			{
				fprintf(fileout,str,out[i]);
			}
		}
		fclose(fileout);
	}
	else
	{
		printf("qx_basic_file: Can not open file: %s\n",file_path);
		getchar();
		exit(-1);
	}
}
void file_save_ascii(char *file_path,float *out,int len)
{
	FILE * fileout; int i;
	//fileout= fopen(file_path,"w");
	fopen_s(&fileout,file_path,"w");
	for(i=0;i<len;i++)    
	{	
		fprintf(fileout,"%f ",out[i]);	
	}
	fclose(fileout);
}
void file_save_ascii(char *file_path,unsigned char *out,int len)
{
	FILE * fileout; int i;
	//fileout= fopen(file_path,"w");
	fopen_s(&fileout,file_path,"w");
	for(i=0;i<len;i++)    
	{	
		fprintf(fileout,"%d ",out[i]);	
	}
	fclose(fileout);
}
void file_save_ascii(char *file_path,int *out,int len)
{
	FILE * fileout; int i;
	//fileout= fopen(file_path,"w");
	fopen_s(&fileout,file_path,"w");
	for(i=0;i<len;i++)    
	{	
		fprintf(fileout,"%d ",out[i]);	
	}
	fclose(fileout);
}
void file_save_ascii(char *file_path,char *out)
{
	FILE * fileout; int i; int len;
	//fileout= fopen(file_path,"w");
	fopen_s(&fileout,file_path,"w");
	//len=(int)strlen(out);
	//for(i=0;i<len;i++) fprintf(fileout,"%c",out[i]);
	fprintf(fileout,"%s",out);
	//printf("%s",file_path);
	//printf("%s",out);
	fclose(fileout);
}
void file_save_ascii_2d(char *file_path,float **out,int h,int w,char *str)
{
	FILE * fileout; int y,x; char str_format[10];
	if(str) sprintf_s(str_format,10,"%s ",str);
	//fileout= fopen(file_path,"w");
	fopen_s(&fileout,file_path,"w");
	for(y=0;y<h;y++)
	{	
		for(x=0;x<w;x++)
		{
			if(str==NULL) fprintf(fileout,"%10.10f ",out[y][x]);
			else fprintf(fileout,str_format,out[y][x]);
		}
		fprintf(fileout,"\n");	
	}
	fclose(fileout);
}
void file_save_ascii_2d(char *file_path,double **out,int h,int w,char *str)
{
	FILE * fileout; int y,x; 
	char*str_format="%e ";
	//char str_format[10];
	//if(str) sprintf_s(str_format,10,"%s ",str);
	//else  sprintf_s(str_format,10,"%e ");
	//fileout= fopen(file_path,"w");
	fopen_s(&fileout,file_path,"w");
	for(y=0;y<h;y++)
	{	
		for(x=0;x<w;x++)
		{
			fprintf(fileout,str_format,out[y][x]);	
		}
		fprintf(fileout,"\n");	
	}
	fclose(fileout);
}
void file_save_ascii_2d(char*file_path,double*out,int h,int w,char*str)
{
	FILE * fileout; int y,x; 
	char*str_format="%e ";
	//char str_format[10];
	//if(str) sprintf_s(str_format,10,"%s ",str);
	//else  sprintf_s(str_format,10,"%e ");
	//fileout= fopen(file_path,"w");
	fopen_s(&fileout,file_path,"w");
	for(y=0;y<h;y++)
	{	
		for(x=0;x<w;x++)
		{
			fprintf(fileout,str_format,out[y*w+x]);	
		}
		fprintf(fileout,"\n");	
	}
	fclose(fileout);
}
void file_save_ascii_2d(char *file_path,unsigned char **out,int h,int w)
{
	FILE * fileout; int y,x;
	//fileout= fopen(file_path,"w");
	fopen_s(&fileout,file_path,"w");
	for(y=0;y<h;y++)
	{	
		for(x=0;x<w;x++)
		{
			fprintf(fileout,"%i ",out[y][x]);	
		}
		fprintf(fileout,"\n");	
	}
	fclose(fileout);
}
void file_save_ascii_2d(char *file_path,unsigned int **out,int h,int w)
{
	FILE * fileout; int y,x;
	//fileout= fopen(file_path,"w");
	fopen_s(&fileout,file_path,"w");
	for(y=0;y<h;y++)
	{	
		for(x=0;x<w;x++)
		{
			fprintf(fileout,"%i ",out[y][x]);	
		}
		fprintf(fileout,"\n");	
	}
	fclose(fileout);
}
void file_save_ascii_2d(char *file_path,int **out,int h,int w)
{
	FILE * fileout; int y,x;
	//fileout= fopen(file_path,"w");
	fopen_s(&fileout,file_path,"w");
	for(y=0;y<h;y++)
	{	
		for(x=0;x<w;x++)
		{
			fprintf(fileout,"%i ",out[y][x]);	
		}
		fprintf(fileout,"\n");	
	}
	fclose(fileout);
}
void file_save_ascii_2d(char *file_path,char **out,int h,int w)
{
	FILE * fileout; int y,x;
	//fileout= fopen(file_path,"w");
	fopen_s(&fileout,file_path,"w");
	for(y=0;y<h;y++)
	{	
		x=0;
		while(out[y][x]!=0&&x<w)
		{
			fprintf(fileout,"%c",out[y][x++]);
		}
		fprintf(fileout,"\n");
	}
	fclose(fileout);
}
int file_open_ascii_2d(char*file_path,char**out,int h,int w)
{
	FILE * file_in; int i;
	if(fopen_s(&file_in,file_path,"r")==0)
	{
		fseek(file_in,0,SEEK_SET);
		for(i=0;i<h;i++)
		{ 
			//fscanf_s(file_in,"%s",out[i],w+1); 
			fgets(out[i],w,file_in);
			int len=strlen(out[i]);
			if(out[i][len-1]=='\n') out[i][len-1] = '\0';
		}
		fclose(file_in);
	}
	else
	{
		printf("Can not open file: %s\n",file_path);
		getchar();
		return(-1);
	}
	return(0);
}

void file_update(char *file_path,float *out,int len)
{
	FILE * file_out;
	//file_out= fopen(file_path, "wb");
	if((fopen_s(&file_out,file_path, "ab"))!=0) 
	{
		fopen_s(&file_out,file_path, "wb");
	}
	//for (int i=0; i<len; i++)    
	//	fprintf(StreamSave,FormatStr,out[i]);
	fwrite(out,sizeof(float),len,file_out);
	fclose(file_out);
}

void file_update(char *file_path,int *out,int len)
{
	FILE * file_out;
	//file_out= fopen(file_path, "wb");
	if((fopen_s(&file_out,file_path, "ab"))!=0) 
	{
		fopen_s(&file_out,file_path, "wb");
	}
	//for (int i=0; i<len; i++)    
	//	fprintf(StreamSave,FormatStr,out[i]);
	fwrite(out,sizeof(int),len,file_out);
	fclose(file_out);
}

void file_update_ascii(char *file_path,int *out,int len)
{
	FILE * file_out;
	//file_out= fopen(file_path, "wb");
	if((fopen_s(&file_out,file_path, "a"))!=0) 
	{
		fopen_s(&file_out,file_path, "w");
	}
	for(int i=0;i<len;i++)    
	{	
		fprintf(file_out,"%d ",out[i]);	
	}
	fclose(file_out);
}
void file_update_ascii(char *file_path,float *out,int len)
{
	FILE * file_out;
	//file_out= fopen(file_path, "wb");
	if((fopen_s(&file_out,file_path, "a"))!=0) 
	{
		fopen_s(&file_out,file_path, "w");
	}
	for(int i=0;i<len;i++)    
	{	
		fprintf(file_out,"%f ",out[i]);	
	}
	fprintf(file_out,"\n");	
	fclose(file_out);
}
void file_update_ascii(char *file_path,char *out)
{
	FILE * file_out; bool is_open=false;
	if((fopen_s(&file_out,file_path, "a"))!=0) 
	{
		if((fopen_s(&file_out,file_path, "w"))!=0)
		{
			printf("Can't open [%s];",file_path);
			//getchar();
		}
		else is_open=true;
	}
	else is_open=true;
	if(is_open)
	{
		fprintf(file_out,"%s",out);
		fclose(file_out);
	}
}

void file_update_ascii_2d(char *file_path,double **out,int h,int w,char *str)
{
	FILE * fileout; int y,x; char str_format[10];
	if(str) sprintf_s(str_format,10,"%s ",str);
	else  sprintf_s(str_format,10,"%e ",str);
	//fileout= fopen(file_path,"w");
	if((fopen_s(&fileout,file_path, "a"))!=0) 
	{
		fopen_s(&fileout,file_path, "w");
	}

	for(y=0;y<h;y++)
	{	
		for(x=0;x<w;x++)
		{
			fprintf(fileout,str_format,out[y][x]);	
		}
		fprintf(fileout,"\n");	
	}
	fclose(fileout);
}

int qx_save_wrl(char*filename,float*color_in,float*point_in,int nr_point)
{
	/*begin*/
	FILE *file_curr_frame;
	if(fopen_s(&file_curr_frame,filename,"w")==0)
	{
		fprintf(file_curr_frame,"#VRML V2.0 utf8\n");
	}
	else
	{
		printf("qx_basic_file, qx_save_wrl: Failed to open %s!\n",filename);
		getchar();
		return(-1);
	}

	/*insert*/
	float*color=color_in; 
	float*point=point_in;
	fprintf(file_curr_frame,"Shape{\n geometry PointSet{\n  color Color{\n   color[\n");
	for(int i=0;i<nr_point;i++) 
	{
		float r=(*color++);
		float g=(*color++);
		float b=(*color++);
		fprintf(file_curr_frame,"    %f %f %f,\n",r,g,b);
	}
	fprintf(file_curr_frame,"   ]\n  }\n");
	fprintf(file_curr_frame,"  coord Coordinate{\n   point[\n");
	for(int i=0;i<nr_point;i++) 
	{
		float r,g,b;
		r=(*point++);
		g=(*point++);
		b=(*point++);
		fprintf(file_curr_frame,"    %f %f %f,\n",r,g,b);
	}
	fprintf(file_curr_frame,"   ]\n  }\n }\n}\n");
	fclose(file_curr_frame);
	return(0);
}
int qx_save_wrl(char*filename,float**color_in,float**point_in,int nr_point)
{
	return(qx_save_wrl(filename,color_in[0],point_in[0],nr_point));
}
int qx_save_wrl(char*filename,float***color_in,float***point_in,int nr_point)
{
	return(qx_save_wrl(filename,color_in[0][0],point_in[0][0],nr_point));
}

int qx_save_wrl_triangle(char*filename,float**color_in,float**point_in,int nr_point,int**triangle_index,int nr_triangle)
{
	/*begin*/
	FILE *file_curr_frame;
	if(fopen_s(&file_curr_frame,filename,"w")==0)
	{
		fprintf(file_curr_frame,"#VRML V2.0 utf8\n");
	}
	else
	{
		printf("qx_basic_file, qx_save_wrl: Failed to open %s!\n",filename);
		getchar();
		return(-1);
	}

	/*insert*/
	float*color=color_in[0]; 
	float*point=point_in[0];
	fprintf(file_curr_frame,"Shape{\n");
	fprintf(file_curr_frame," appearance Appearance{\n  material Material{\n  }\n }\n");
	fprintf(file_curr_frame," geometry IndexedFaceSet{\n  creaseAngle	3.14\n  solid FALSE\n  color Color{\n   color[\n");
	for(int i=0;i<nr_point;i++) 
	{
		float r=(*color++);
		float g=(*color++);
		float b=(*color++);
		fprintf(file_curr_frame,"    %f %f %f,\n",r,g,b);
	}
	fprintf(file_curr_frame,"   ]\n  }\n");
	fprintf(file_curr_frame,"  coord Coordinate{\n   point[\n");
	for(int i=0;i<nr_point;i++) 
	{
		float r,g,b;
		r=(*point++);
		g=(*point++);
		b=(*point++);
		fprintf(file_curr_frame,"    %f %f %f,\n",r,g,b);
	}
	fprintf(file_curr_frame,"   ]\n  }\n");

	fprintf(file_curr_frame,"   coordIndex [ # direction of triangles\n");
	for(int i=0;i<nr_triangle;i++) 
	{
		fprintf(file_curr_frame,"    %d",triangle_index[i][0]);
		fprintf(file_curr_frame," %d",triangle_index[i][1]);
		fprintf(file_curr_frame," %d -1,\n",triangle_index[i][2]);
	}
	fprintf(file_curr_frame,"   ]\n");

	fprintf(file_curr_frame," }\n}\n");
	fclose(file_curr_frame);
	return(0);
}
int qx_save_wrl(char*filename,double**color_in,double**point_in,int nr_point)
{
	/*begin*/
	FILE *file_curr_frame;
	if(fopen_s(&file_curr_frame,filename,"w")==0)
	{
		fprintf(file_curr_frame,"#VRML V2.0 utf8\n");
	}
	else
	{
		printf("qx_basic_file, qx_save_wrl: Failed to open %s!\n",filename);
		getchar();
		return(-1);
	}

	/*insert*/
	double *color=color_in[0]; 
	double *point=point_in[0];
	fprintf(file_curr_frame,"Shape{\n geometry PointSet{\n  color Color{\n   color[\n");
	for(int i=0;i<nr_point;i++) 
	{
		float r=(*color++);
		float g=(*color++);
		float b=(*color++);
		fprintf(file_curr_frame,"    %f %f %f,\n",r,g,b);
	}
	fprintf(file_curr_frame,"   ]\n  }\n");
	fprintf(file_curr_frame,"  coord Coordinate{\n   point[\n");
	for(int i=0;i<nr_point;i++) 
	{
		double r,g,b;
		r=(*point++);
		g=(*point++);
		b=(*point++);
		fprintf(file_curr_frame,"    %lf %lf %lf,\n",r,g,b);
	}
	fprintf(file_curr_frame,"   ]\n  }\n }\n}\n");
	fclose(file_curr_frame);
	return(0);
}

int qx_save_wrl_triangle(char*filename,double**color_in,double**point_in,int nr_point,int**triangle_index,int nr_triangle)
{
	/*begin*/
	FILE *file_curr_frame;
	if(fopen_s(&file_curr_frame,filename,"w")==0)
	{
		fprintf(file_curr_frame,"#VRML V2.0 utf8\n");
	}
	else
	{
		printf("qx_basic_file, qx_save_wrl: Failed to open %s!\n",filename);
		getchar();
		return(-1);
	}

	/*insert*/
	double*color=color_in[0]; 
	double*point=point_in[0];
	fprintf(file_curr_frame,"Shape{\n");
	fprintf(file_curr_frame," appearance Appearance{\n  material Material{\n  }\n }\n");
	fprintf(file_curr_frame," geometry IndexedFaceSet{\n  creaseAngle	3.14\n  solid FALSE\n  color Color{\n   color[\n");
	for(int i=0;i<nr_point;i++) 
	{
		float r=(*color++);
		float g=(*color++);
		float b=(*color++);
		fprintf(file_curr_frame,"    %f %f %f,\n",r,g,b);
	}
	fprintf(file_curr_frame,"   ]\n  }\n");
	fprintf(file_curr_frame,"  coord Coordinate{\n   point[\n");
	for(int i=0;i<nr_point;i++) 
	{
		float r,g,b;
		r=(*point++);
		g=(*point++);
		b=(*point++);
		fprintf(file_curr_frame,"    %f %f %f,\n",r,g,b);
	}
	fprintf(file_curr_frame,"   ]\n  }\n");

	fprintf(file_curr_frame,"   coordIndex [ # direction of triangles\n");
	for(int i=0;i<nr_triangle;i++) 
	{
		fprintf(file_curr_frame,"    %d",triangle_index[i][0]);
		fprintf(file_curr_frame," %d",triangle_index[i][1]);
		fprintf(file_curr_frame," %d -1,\n",triangle_index[i][2]);
	}
	fprintf(file_curr_frame,"   ]\n");

	fprintf(file_curr_frame," }\n}\n");
	fclose(file_curr_frame);
	return(0);
}

void qx_save_ply(char* file_name,float ***points,float ***normal,unsigned char ***image,unsigned char **mask,int **index,int h,int w)
{
	FILE * stream; int y,x,nr_points,nr_faces,counter; int h1,w1;
	//nr_points=h*w;
	nr_points=nr_faces=0;
	h1=h-1; w1=w-1;
	for(y=0;y<h;y++)
	{
		for(x=0;x<w;x++)
		{
			if(mask[y][x])
			{
				nr_points++;
				if(y<h1&&x<w1&&y>0&&x>0)
				{
					if(mask[y-1][x]&&mask[y][x-1]) nr_faces++;
					if(mask[y+1][x]&&mask[y][x+1]) nr_faces++;
				}
			}
		}
	}
	fopen_s(&stream,file_name,"w");
	//*write header*/
	fprintf(stream,"ply\n nformat binary_little_endian 1.0\n");
	fprintf(stream,"comment Author: Qingxiong Yang (liiton)\n");
	fprintf(stream,"element vertex %d\n",nr_points);
	fprintf(stream,"property float x\n");
	fprintf(stream,"property float y\n");
	fprintf(stream,"property float z\n");
	if(normal!=NULL)
	{
		fprintf(stream,"property float nx\n");
		fprintf(stream,"property float ny\n");
		fprintf(stream,"property float nz\n");
	}
	if(image!=NULL)
	{
		fprintf(stream,"property uchar red\n");
		fprintf(stream,"property uchar green\n");
		fprintf(stream,"property uchar blue\n");
	}
	fprintf(stream,"element face %d\n",nr_faces);
	fprintf(stream,"property list uint int vertex_indices\n");
	fprintf(stream,"end_header\n");

	//*write vertices*/
	for(counter=0,y=0;y<h;y++)
	{
		for(x=0;x<w;x++)
		{
			if(mask[y][x])
			{
				index[y][x]=counter++;
				fwrite(points[y][x],sizeof(float),3,stream);
				if(normal!=NULL)
				{
					fwrite(normal[y][x],sizeof(float),3,stream);
				}
				if(image!=NULL)
				{
					fwrite(image[y][x],sizeof(unsigned char),3,stream);
				}
			}
		}
	}
	//*write faces*/
	int faces_index[4]; 
	for(y=0;y<h;y++)
	{
		for(x=0;x<w;x++)
		{
			if(mask[y][x])
			{
				if(y<h1&&x<w1&&y>0&&x>0)
				{
					if(mask[y-1][x]&&mask[y][x-1])
					{
						faces_index[0]=3;
						faces_index[1]=index[y][x];
						faces_index[2]=index[y-1][x];
						faces_index[3]=index[y][x-1];
						fwrite(faces_index,sizeof(int),4,stream);
					}
					if(mask[y+1][x]&&mask[y][x+1])
					{
						faces_index[0]=3;
						faces_index[1]=index[y][x];
						faces_index[2]=index[y+1][x];
						faces_index[3]=index[y][x+1];
						fwrite(faces_index,sizeof(int),4,stream);
					}
				}
			}
		}
	}
	fclose(stream);
}

//void qx_save_ply(char* file_name,float ***points,float ***normal,unsigned char ***image,unsigned char **mask,int **index,int h,int w)
//{
//	FILE * stream; int y,x,nr_points,nr_faces,counter; int h1,w1; int faces_index[4]; int grid_index[2];
//	//nr_points=h*w;
//	nr_points=nr_faces=0;
//	h1=h-1; w1=w-1;
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
//	fopen_s(&stream,file_name,"wb");
//	fprintf(stream,"ply\nformat binary_little_endian 1.0\n");
//	fprintf(stream,"obj_info num_cols %d\n",w);
//	fprintf(stream,"obj_info num_rows %d\n",h);
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
//	//fprintf(stream,"element face %d\n",nr_faces);
//	//fprintf(stream,"property list uint int vertex_indices\n");
//	fprintf(stream,"element range_grid %d\n",h*w);
//	fprintf(stream,"property list uchar int vertex_indices\n");
//	fprintf(stream,"end_header\n");
//
//	//*write vertices*/
//	for(counter=0,y=0;y<h;y++)
//	{
//		for(x=0;x<w;x++)
//		{
//			if(mask[y][x])
//			{
//				index[y][x]=counter++;
//				fwrite(points[y][x],sizeof(float),3,stream);
//				if(normal!=NULL)
//				{
//					fwrite(normal[y][x],sizeof(float),3,stream);
//				}
//				if(image!=NULL)
//				{
//					fwrite(image[y][x],sizeof(unsigned char),3,stream);
//				}
//				//fwrite("\n",sizeof("%s"),1,stream);
//				//fprintf(stream,"\n");
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
//				unsigned char nr=1;
//				int id=index[y][x];
//				fwrite(&nr,sizeof(unsigned char),1,stream);
//				fwrite(&id,sizeof(int),1,stream);
//				//if(y<h1&&x<w1&&y>0&&x>0)
//				//{
//				//	if(mask[y-1][x]&&mask[y][x-1])
//				//	{
//				//		faces_index[0]=3;
//				//		faces_index[1]=index[y][x];
//				//		faces_index[2]=index[y-1][x];
//				//		faces_index[3]=index[y][x-1];
//				//		fwrite(faces_index,sizeof(int),4,stream);
//				//		//fwrite("\n",sizeof("%s"),1,stream);
//				//	}
//				//	if(mask[y+1][x]&&mask[y][x+1])
//				//	{
//				//		faces_index[0]=3;
//				//		faces_index[1]=index[y][x];
//				//		faces_index[2]=index[y+1][x];
//				//		faces_index[3]=index[y][x+1];
//				//		fwrite(faces_index,sizeof(int),4,stream);
//				//		//fwrite("\n",sizeof("%s"),1,stream);
//				//	}
//				//}
//			}
//			else
//			{
//				unsigned char nr=0;
//				fwrite(&nr,sizeof(unsigned char),1,stream);
//			}
//		}
//	}
//	fclose(stream);
//}
void qx_save_ply_ascii(char* file_name,float ***points,float ***normal,unsigned char ***image,unsigned char **mask,int **index,int h,int w)
{
	FILE * stream; int y,x,nr_points,nr_faces,counter; int h1,w1;
	//nr_points=h*w;
	nr_points=nr_faces=0;
	h1=h-1; w1=w-1;
	for(y=0;y<h;y++)
	{
		for(x=0;x<w;x++)
		{
			if(mask[y][x])
			{
				nr_points++;
				if(y<h1&&x<w1&&y>0&&x>0)
				{
					if(mask[y-1][x]&&mask[y][x-1]) nr_faces++;
					if(mask[y+1][x]&&mask[y][x+1]) nr_faces++;
				}
			}
		}
	}
	fopen_s(&stream,file_name,"w");
	//*write header*/
	fprintf(stream,"ply\n format ascii 1.0\n");
	fprintf(stream,"comment Author: Qingxiong Yang (liiton)\n");
	fprintf(stream,"element vertex %d\n",nr_points);
	fprintf(stream,"property float x\n");
	fprintf(stream,"property float y\n");
	fprintf(stream,"property float z\n");
	if(normal!=NULL)
	{
		fprintf(stream,"property float nx\n");
		fprintf(stream,"property float ny\n");
		fprintf(stream,"property float nz\n");
	}
	if(image!=NULL)
	{
		fprintf(stream,"property uchar red\n");
		fprintf(stream,"property uchar green\n");
		fprintf(stream,"property uchar blue\n");
	}
	fprintf(stream,"element face %d\n",nr_faces);
	fprintf(stream,"property list uchar int vertex_indices\n");
	fprintf(stream,"end_header\n");
	//*write vertices*/
	for(counter=0,y=0;y<h;y++)
	{
		for(x=0;x<w;x++)
		{
			if(mask[y][x])
			{
				index[y][x]=counter++;
				fprintf(stream,"%f %f %f ",points[y][x][0],points[y][x][1],points[y][x][2]);
				if(normal!=NULL)
				{
					fprintf(stream,"%f %f %f ",normal[y][x][0],normal[y][x][1],normal[y][x][2]);
				}
				if(image!=NULL)
				{
					fprintf(stream,"%d %d %d",image[y][x][0],image[y][x][1],image[y][x][2]);
				}
				fprintf(stream,"\n");
			}
		}
	}
	//*write faces*/
	for(y=0;y<h;y++)
	{
		for(x=0;x<w;x++)
		{
			if(mask[y][x])
			{
				if(y<h1&&x<w1&&y>0&&x>0)
				{
					if(mask[y-1][x]&&mask[y][x-1])
					{
						fprintf(stream,"3 %d %d %d\n",index[y][x],index[y-1][x],index[y][x-1]);
					}
					if(mask[y+1][x]&&mask[y][x+1])
					{
						fprintf(stream,"3 %d %d %d\n",index[y][x],index[y+1][x],index[y][x+1]);
					}
				}
			}
		}
	}
	fclose(stream);
}


void save_ply(char* file_name,float **depth,float ***normal,unsigned char ***image,unsigned char **mask,int **index,int h,int w,float sx,float sy,float sz,int y0,int x0)
{
	FILE * stream; int y,x,nr_points,nr_faces,counter; int h1,w1;
	//nr_points=h*w;
	nr_points=nr_faces=0;
	h1=h-1; w1=w-1;
	if(x0<0||x0>=w) x0=(w>>1);
	if(y0<0||y0>=h) y0=(h>>1);
	for(y=0;y<h;y++)
	{
		for(x=0;x<w;x++)
		{
			if(mask[y][x])
			{
				nr_points++;
				if(y<h1&&x<w1&&y>0&&x>0)
				{
					if(mask[y-1][x]&&mask[y][x-1]) nr_faces++;
					if(mask[y+1][x]&&mask[y][x+1]) nr_faces++;
				}
			}
		}
	}
	fopen_s(&stream,file_name,"w");
	//*write header*/
	fprintf(stream,"ply\n format ascii 1.0\n");
	fprintf(stream,"comment Author: Qingxiong Yang (liiton)\n");
	fprintf(stream,"element vertex %d\n",nr_points);
	fprintf(stream,"property float x\n");
	fprintf(stream,"property float y\n");
	fprintf(stream,"property float z\n");
	if(normal!=NULL)
	{
		fprintf(stream,"property float nx\n");
		fprintf(stream,"property float ny\n");
		fprintf(stream,"property float nz\n");
	}
	if(image!=NULL)
	{
		fprintf(stream,"property uchar red\n");
		fprintf(stream,"property uchar green\n");
		fprintf(stream,"property uchar blue\n");
	}
	fprintf(stream,"element face %d\n",nr_faces);
	fprintf(stream,"property list uchar int vertex_indices\n");
	fprintf(stream,"end_header\n");
	//*write vertices*/
	for(counter=0,y=0;y<h;y++)
	{
		for(x=0;x<w;x++)
		{
			if(mask[y][x])
			{
				index[y][x]=counter++;
				fprintf(stream,"%f %f %f ",(x-x0)*sx,(y-y0)*sy,depth[0][y*w+x]*sz);
				if(normal!=NULL)
				{
					fprintf(stream,"%f %f %f ",normal[y][x][0],normal[y][x][1],normal[y][x][2]);
				}
				if(image!=NULL)
				{
					fprintf(stream,"%d %d %d",image[y][x][0],image[y][x][1],image[y][x][2]);
				}
				fprintf(stream,"\n");
			}
		}
	}
	//*write faces*/
	for(y=0;y<h;y++)
	{
		for(x=0;x<w;x++)
		{
			if(mask[y][x])
			{
				if(y<h1&&x<w1&&y>0&&x>0)
				{
					if(mask[y-1][x]&&mask[y][x-1])
					{
						fprintf(stream,"3 %d %d %d\n",index[y][x],index[y-1][x],index[y][x-1]);
					}
					if(mask[y+1][x]&&mask[y][x+1])
					{
						fprintf(stream,"3 %d %d %d\n",index[y][x],index[y+1][x],index[y][x+1]);
					}
				}
			}
		}
	}
	fclose(stream);
}
void save_ply(char* file_name,float **depth,float ***normal,unsigned char ***image,int h,int w,float sx,float sy,float sz,int y0,int x0)
{
	FILE * stream; int y,x,nr_points,nr_faces,counter; int h1,w1;
	nr_points=h*w;
	h1=h-1; w1=w-1;
	nr_faces=2*h1*w1;
	if(x0<0||x0>=w) x0=(w>>1);
	if(y0<0||y0>=h) y0=(h>>1);

	fopen_s(&stream,file_name,"w");
	//*write header*/
	fprintf(stream,"ply\nformat ascii 1.0\n");
	fprintf(stream,"comment Author: Qingxiong Yang (liiton)\n");
	fprintf(stream,"element vertex %d\n",nr_points);
	fprintf(stream,"property float x\n");
	fprintf(stream,"property float y\n");
	fprintf(stream,"property float z\n");
	if(normal!=NULL)
	{
		fprintf(stream,"property float nx\n");
		fprintf(stream,"property float ny\n");
		fprintf(stream,"property float nz\n");
	}
	if(image!=NULL)
	{
		fprintf(stream,"property uchar red\n");
		fprintf(stream,"property uchar green\n");
		fprintf(stream,"property uchar blue\n");
	}
	fprintf(stream,"element face %d\n",nr_faces);
	fprintf(stream,"property list uchar int vertex_indices\n");
	fprintf(stream,"end_header\n");
	//*write vertices*/
	counter=0;
	for(y=0;y<h;y++)
	{
		for(x=0;x<w;x++)
		{
			fprintf(stream,"%5.5f %5.5f %5.5f ",(x-x0)*sx,(y-y0)*sy,depth[0][y*w+x]*sz);
			if(normal!=NULL)
			{
				fprintf(stream,"%f %f %f ",normal[y][x][0],normal[y][x][1],normal[y][x][2]);
			}
			if(image!=NULL)
			{
				fprintf(stream,"%d %d %d",image[y][x][0],image[y][x][1],image[y][x][2]);
			}
			fprintf(stream,"\n");
			counter++;
		}
	}
	printf("counter: %d\n",counter);
	//*write faces*/
	counter=0;
	for(y=0;y<h1;y++)
	{
		for(x=0;x<w1;x++)
		{
			int id1=y*w+x;
			int id2=(y+1)*w+x+1;
			fprintf(stream,"3 %d %d %d\n",id1,id1+1,id2-1);
			fprintf(stream,"3 %d %d %d\n",id2,id2-1,id1+1);
			counter+=2;
		}
	}
	printf("counter: %d\n",counter);	
	fclose(stream);
}

int save_iv(char* file_name,float **depth,unsigned char ***image,int h,int w,int point_size,float depth_scale)
{
	FILE * stream_iv; int y,x,nr_points;
	nr_points=h*w;
	//stream_iv=fopen(file_name,"w");
	fopen_s(&stream_iv,file_name,"w");
	fprintf(stream_iv,"#Inventor V2.1 ascii\n");
	fprintf(stream_iv,"Separator\n{\n");
	fprintf(stream_iv,"  DrawStyle\n  {\n");
	fprintf(stream_iv,"    pointSize %d\n  }\n",point_size);
	fprintf(stream_iv,"  Material\n  {\n");
	fprintf(stream_iv,"    diffuseColor\n    [\n");
	/*file in the color*/
	if(image==NULL)
	{
		for(y=0;y<h;y++) for(x=0;x<w;x++)
		{
			fprintf(stream_iv,"        %2.5f %2.5f %2.5f ,\n",1.0f,1.0f,1.0f);
		}
	}
	else
	{
		for(y=0;y<h;y++) for(x=0;x<w;x++)
		{
			fprintf(stream_iv,"        %3.5f %3.5f %3.5f ,\n",float(image[y][x][0])/255,float(image[y][x][1])/255,float(image[y][x][2])/255);
		}
	}
	fprintf(stream_iv,"\n    ]\n  }\n  Coordinate3\n  {\n    point\n    [\n");
	/*file in the coordinates*/
	for(y=0;y<h;y++) for(x=0;x<w;x++)
	{
		fprintf(stream_iv,"        %5.5f %5.5f %5.5f ,\n",-float(x),-float(y),-depth[y][x]*depth_scale);	
	}
	image_display(depth,h,w);
	fprintf(stream_iv,"\n    ]\n  }\n  MaterialBinding\n  {\n    value PER_VERTEX\n  }\n  PointSet\n  {\n    numPoints %d\n  }\n}\n",nr_points);
	fclose(stream_iv);
	return(0);
}
int save_iv(char* file_name,float **depth,unsigned char ***image,unsigned char **mask,int h,int w,int point_size,float depth_scale)
{
	FILE * stream_iv; int y,x,nr_points;
	nr_points=0;
	//stream_iv=fopen(file_name,"w");
	fopen_s(&stream_iv,file_name,"w");
	fprintf(stream_iv,"#Inventor V2.1 ascii\n");
	fprintf(stream_iv,"Separator\n{\n");
	fprintf(stream_iv,"  DrawStyle\n  {\n");
	fprintf(stream_iv,"    pointSize %d\n  }\n",point_size);
	fprintf(stream_iv,"  Material\n  {\n");
	fprintf(stream_iv,"    diffuseColor\n    [\n");
	/*file in the color*/
	if(image==NULL)
	{
		for(y=0;y<h;y++) for(x=0;x<w;x++)
		{
			if(mask[y][x])
			{
				fprintf(stream_iv,"        %2.5f %2.5f %2.5f ,\n",1.0f,1.0f,1.0f);
				nr_points++;
			}
		}
	}
	else
	{
		for(y=0;y<h;y++) for(x=0;x<w;x++)
		{
			if(mask[y][x])
			{
				fprintf(stream_iv,"        %3.5f %3.5f %3.5f ,\n",float(image[y][x][0])/255,float(image[y][x][1])/255,float(image[y][x][2])/255);
				nr_points++;
			}
		}
	}
	fprintf(stream_iv,"\n    ]\n  }\n  Coordinate3\n  {\n    point\n    [\n");
	/*file in the coordinates*/
	for(y=0;y<h;y++) for(x=0;x<w;x++)
	{
		if(mask[y][x])
		{
			fprintf(stream_iv,"        %5.5f %5.5f %5.5f ,\n",-float(x),-float(y),-depth[y][x]*depth_scale);	
		}
	}
	fprintf(stream_iv,"\n    ]\n  }\n  MaterialBinding\n  {\n    value PER_VERTEX\n  }\n  PointSet\n  {\n    numPoints %d\n  }\n}\n",nr_points);
	fclose(stream_iv);
	return(0);
}

int save_iv_triangles(char* file_name,float **depth,unsigned char ***image,unsigned char **mask,int h,int w,int point_size,float depth_scale,float xy_scale)
{
	FILE * stream_iv; int y,x,nr_points;
	nr_points=0;
	//stream_iv=fopen(file_name,"w");
	fopen_s(&stream_iv,file_name,"w");
	fprintf(stream_iv,"#Inventor V2.1 ascii\n");
	fprintf(stream_iv,"Separator\n{\n");
	fprintf(stream_iv,"  DrawStyle\n  {\n");
	fprintf(stream_iv,"    pointSize %d\n  }\n",point_size);
	fprintf(stream_iv,"  Material\n  {\n");
	/*file in the color*/
	fprintf(stream_iv,"    diffuseColor\n    [\n");
	if(image==NULL)
	{
		for(y=0;y<h;y++) for(x=0;x<w;x++)
			if(mask[y][x])
			{
				fprintf(stream_iv,"        %2.5f %2.5f %2.5f ,\n",1.0f,1.0f,1.0f);
				nr_points++;
			}
	}
	else
	{
		for(y=0;y<h;y++) for(x=0;x<w;x++)
		{
			if(mask[y][x])
			{
				fprintf(stream_iv,"        %2.5f %2.5f %2.5f ,\n",float(image[y][x][0])/255,float(image[y][x][1])/255,float(image[y][x][2])/255);
				nr_points++;
			}
		}
	}
	fprintf(stream_iv,"\n    ]\n  }\n");

	/*TextureCoordinate Bind*/
	fprintf(stream_iv,"  TextureCoordinateBinding\n  {\n    value PER_VERTEX_INDEXED\n  }\n");
	/*material Bind*/
	fprintf(stream_iv,"  MaterialBinding\n  {\n    value PER_VERTEX_INDEXED\n  }\n");
	/*ShapeHints*/
	fprintf(stream_iv,"ShapeHints\n  {\n");
	fprintf(stream_iv,"    vertexOrdering COUNTERCLOCKWISE\n");
	fprintf(stream_iv,"    shapeType UNKNOWN_SHAPE_TYPE\n");
	fprintf(stream_iv,"    faceType CONVEX\n");
	fprintf(stream_iv,"    creaseAngle 6.28319\n");
	fprintf(stream_iv,"  }\n");

	/*file in the coordinates*/
	fprintf(stream_iv,"  Coordinate3\n  {\n    point\n    [\n");
	for(y=0;y<h;y++) for(x=0;x<w;x++)
	{
		if(mask[y][x])
		{
			fprintf(stream_iv,"        %2.5f %2.5f %2.5f ,\n",float(x)*xy_scale,-float(y)*xy_scale,-depth[y][x]*depth_scale);	
		}
	}
	fprintf(stream_iv,"\n    ]\n  }\n");
	/*draw triangles*/
	fprintf(stream_iv,"  IndexedFaceSet\n  {\n");
	fprintf(stream_iv,"    coordIndex\n    [\n");
	for(y=0;y<h-1;y++) for(x=0;x<w-1;x++)
	{	
		if(mask[y][x])
		{
			fprintf(stream_iv,"        %d,%d,%d,%d,\n",((y+1)*w+x),(y*w+x+1),(y*w+x),-1);
			fprintf(stream_iv,"        %d,%d,%d,%d,\n",((y+1)*w+x),((y+1)*w+x+1),(y*w+x+1),-1);
		}
	}
	fprintf(stream_iv,"\n    ]\n");
	//fprintf(stream_iv,"    materialIndex \n    [\n");
	//for(y=0;y<h-1;y++) for(x=0;x<w-1;x++)
	//{	
	//	//fprintf(stream_iv,"        %d,%d,%d,%d,\n",((y+1)*w+x),(y*w+x+1),(y*w+x),-1);
	//	//fprintf(stream_iv,"        %d,%d,%d,%d,\n",((y+1)*w+x),((y+1)*w+x+1),(y*w+x+1),-1);
	//	fprintf(stream_iv,"        %d,%d,%d,%d,\n",y,y,y,-1);
	//	fprintf(stream_iv,"        %d,%d,%d,%d,\n",y,y,y,-1);
	//}
	//fprintf(stream_iv,"\n    ]\n");


	fprintf(stream_iv,"  }\n");

	fprintf(stream_iv,"  PointSet\n  {\n    numPoints %d\n  }\n}\n",nr_points);
	fclose(stream_iv);
	return(0);
}

int save_iv(char* file_name,float **depth,unsigned char ***image,int ymin,int ymax,int xmin,int xmax,int point_size,float depth_scale)
{
	FILE * stream_iv; int y,x,nr_points;
	
	nr_points=(ymax-ymin+1)*(xmax-xmin+1);
	//stream_iv=fopen(file_name,"w");
	fopen_s(&stream_iv,file_name,"w");
	fprintf(stream_iv,"#Inventor V2.1 ascii\n");
	fprintf(stream_iv,"Separator\n{\n");
	fprintf(stream_iv,"  DrawStyle\n  {\n");
	fprintf(stream_iv,"    pointSize %d\n  }\n",point_size);
	fprintf(stream_iv,"  Material\n  {\n");
	fprintf(stream_iv,"    diffuseColor\n    [\n");
	/*file in the color*/
	if(image==NULL)
	{
		for(y=ymin;y<=ymax;y++) for(x=xmin;x<=xmax;x++)
			fprintf(stream_iv,"        %2.5f %2.5f %2.5f ,\n",1.0f,1.0f,1.0f);
	}
	else
	{
		for(y=ymin;y<=ymax;y++) for(x=xmin;x<=xmax;x++)
			fprintf(stream_iv,"        %2.5f %2.5f %2.5f ,\n",float(image[y][x][0])/255,float(image[y][x][1])/255,float(image[y][x][2])/255);
	}
	fprintf(stream_iv,"\n    ]\n  }\n  Coordinate3\n  {\n    point\n    [\n");
	/*file in the coordinates*/
	for(y=ymin;y<=ymax;y++) for(x=xmin;x<=xmax;x++)
	{
		fprintf(stream_iv,"        %2.5f %2.5f %2.5f ,\n",-float(x),-float(y),-depth[y][x]*depth_scale);	
	}
	fprintf(stream_iv,"\n    ]\n  }\n  MaterialBinding\n  {\n    value PER_VERTEX\n  }\n  PointSet\n  {\n    numPoints %d\n  }\n}\n",nr_points);
	fclose(stream_iv);
	return(0);
}

int save_iv_triangles(char* file_name,float **depth,unsigned char ***image,int ymin,int ymax,int xmin,int xmax,int point_size,float depth_scale,float xy_scale)
{
	FILE * stream_iv; int y,x,nr_points,h,w;
	
	nr_points=(ymax-ymin+1)*(xmax-xmin+1);
	//stream_iv=fopen(file_name,"w");
	fopen_s(&stream_iv,file_name,"w");
	fprintf(stream_iv,"#Inventor V2.1 ascii\n");
	fprintf(stream_iv,"Separator\n{\n");
	fprintf(stream_iv,"  DrawStyle\n  {\n");
	fprintf(stream_iv,"    pointSize %d\n  }\n",point_size);
	fprintf(stream_iv,"  Material\n  {\n");
	/*file in the color*/
	fprintf(stream_iv,"    diffuseColor\n    [\n");
	if(image==NULL)
	{
		for(y=ymin;y<=ymax;y++) for(x=xmin;x<=xmax;x++)
			fprintf(stream_iv,"        %2.5f %2.5f %2.5f ,\n",1.0f,1.0f,1.0f);
	}
	else
	{
		for(y=ymin;y<=ymax;y++) for(x=xmin;x<=xmax;x++)
			fprintf(stream_iv,"        %2.5f %2.5f %2.5f ,\n",float(image[y][x][0])/255,float(image[y][x][1])/255,float(image[y][x][2])/255);
	}
	fprintf(stream_iv,"\n    ]\n  }\n");

	/*TextureCoordinate Bind*/
	fprintf(stream_iv,"  TextureCoordinateBinding\n  {\n    value PER_VERTEX_INDEXED\n  }\n");
	/*material Bind*/
	fprintf(stream_iv,"  MaterialBinding\n  {\n    value PER_VERTEX_INDEXED\n  }\n");
	/*ShapeHints*/
	fprintf(stream_iv,"ShapeHints\n  {\n");
	fprintf(stream_iv,"    vertexOrdering COUNTERCLOCKWISE\n");
	fprintf(stream_iv,"    shapeType UNKNOWN_SHAPE_TYPE\n");
	fprintf(stream_iv,"    faceType CONVEX\n");
	fprintf(stream_iv,"    creaseAngle 6.28319\n");
	fprintf(stream_iv,"  }\n");

	/*file in the coordinates*/
	fprintf(stream_iv,"  Coordinate3\n  {\n    point\n    [\n");
	for(y=ymin;y<=ymax;y++) for(x=xmin;x<=xmax;x++)
	{
		fprintf(stream_iv,"        %2.5f %2.5f %2.5f ,\n",float(x)*xy_scale,-float(y)*xy_scale,-depth[y][x]*depth_scale);	
	}
	fprintf(stream_iv,"\n    ]\n  }\n");
	/*draw triangles*/
	fprintf(stream_iv,"  IndexedFaceSet\n  {\n");
	h=ymax-ymin+1; w=xmax-xmin+1;
	fprintf(stream_iv,"    coordIndex\n    [\n");
	for(y=0;y<h-1;y++) for(x=0;x<w-1;x++)
	{	
		fprintf(stream_iv,"        %d,%d,%d,%d,\n",((y+1)*w+x),(y*w+x+1),(y*w+x),-1);
		fprintf(stream_iv,"        %d,%d,%d,%d,\n",((y+1)*w+x),((y+1)*w+x+1),(y*w+x+1),-1);
	}
	fprintf(stream_iv,"\n    ]\n");
	//fprintf(stream_iv,"    materialIndex \n    [\n");
	//for(y=0;y<h-1;y++) for(x=0;x<w-1;x++)
	//{	
	//	//fprintf(stream_iv,"        %d,%d,%d,%d,\n",((y+1)*w+x),(y*w+x+1),(y*w+x),-1);
	//	//fprintf(stream_iv,"        %d,%d,%d,%d,\n",((y+1)*w+x),((y+1)*w+x+1),(y*w+x+1),-1);
	//	fprintf(stream_iv,"        %d,%d,%d,%d,\n",y,y,y,-1);
	//	fprintf(stream_iv,"        %d,%d,%d,%d,\n",y,y,y,-1);
	//}
	//fprintf(stream_iv,"\n    ]\n");


	fprintf(stream_iv,"  }\n");

	fprintf(stream_iv,"  PointSet\n  {\n    numPoints %d\n  }\n}\n",nr_points);
	fclose(stream_iv);
	return(0);
}
void matrix_save_ascii(char *file_path,double **in,int h,int w)
{
	FILE * file_in; int i,j;
	//file_in= fopen(file_path, "w");
	fopen_s(&file_in,file_path, "w");
	for (i=0;i<h;i++)    
	{	
		for(j=0;j<w;j++)
		{
			fprintf(file_in, "%e", in[i][j]);	
			fprintf(file_in, "%c",' ');
		}
		fprintf(file_in, "%c",'\n');
	}
	fclose(file_in);
}

int qx_file_save_sift_descriptor(char *file_path,float *desc,int nr_desc,int desc_size)
{
	FILE *fileout;
	fopen_s(&fileout,file_path,"wb");
	//fprintf(fileout,"%d ",nr_desc);
	//for(int i=0;i<nr_desc*desc_size;i++) fprintf(fileout,"%f ",desc[i]);
	fwrite(&nr_desc,sizeof(int),1,fileout);
	fwrite(desc,sizeof(float),nr_desc*desc_size,fileout);
	fclose(fileout);
	return(0);
}
int qx_file_open_sift_descriptor(char *file_path,float *desc,int desc_size)
{
	FILE *file_in; int nr_desc;
	//file_in= fopen(file_path, "rb");
	fopen_s(&file_in,file_path, "rb");
	if(file_in!=NULL)
	{
		fread(&nr_desc,sizeof(int),1,file_in);
		fread(desc,sizeof(float),desc_size*nr_desc,file_in);
		fclose(file_in);
		return(nr_desc);
	}
	else
	{
		printf("Can not open file: %s\n",file_path);
		getchar();
		return(0);
	}
}
int qx_file_save_sift_descriptor_ascii(char *file_path,float *desc,int nr_desc,int desc_size)
{
	FILE *fileout;
	fopen_s(&fileout,file_path,"w");
	fprintf(fileout,"%d ",nr_desc);
	for(int i=0;i<nr_desc*desc_size;i++) fprintf(fileout,"%f ",desc[i]);
	fclose(fileout);
	return(0);
}
int qx_file_open_sift_descriptor_ascii(char *file_path,float *desc,int desc_size)
{
	FILE *file_in; int i,nr_desc; char str[200];
	//file_in= fopen(file_path, "rb");
	fopen_s(&file_in,file_path, "r");
	if(file_in!=NULL)
	{
		fseek(file_in, 0, SEEK_SET);
		fscanf_s(file_in,"%s",str,200);
		nr_desc=atoi(str);
		for(i=0;i<desc_size*nr_desc;i++)
		{ 
			fscanf_s(file_in,"%s",str,200); 
			desc[i]=(float)atof(str);
		}
		fclose(file_in);
		return(nr_desc);
	}
	else
	{
		printf("Can not open file: %s\n",file_path);
		getchar();
		return(0);
	}
}

void qx_save_image_list(char *file_path,char **out,int h,int w)
{
	FILE * fileout; int y,x;
	//fileout= fopen(file_path,"w");
	fopen_s(&fileout,file_path,"w");
	/*save nr_image*/
	fprintf(fileout,"%d \n",h);
	/*save the name of the files*/
	for(y=0;y<h;y++)
	{	
		x=0;
		while(out[y][x]!=0&&x<w)
		{
			fprintf(fileout,"%c",out[y][x++]);	
		}
		fprintf(fileout,"\n");	
	}
	fclose(fileout);
}
void qx_open_image_list(char *file_path,char **out,int h,int w)
{
	FILE * file_in; int i;
	//file_in= fopen(file_path, "r");
	fopen_s(&file_in,file_path,"r");
	if(file_in!=NULL)
	{
		fseek(file_in,0,SEEK_SET);
		fscanf_s(file_in,"%s",out[0],w+1); 
		for(i=0;i<h;i++)
		{ 
			fscanf_s(file_in,"%s",out[i],w+1); 
		}
		fclose(file_in);
	}
	else
	{
		printf("Can not open file: %s\n",file_path);
		getchar();
	}
}
int qx_open_image_list(char *file_path,char **out,int str_len)
{
	FILE * file_in; int nr_file,i;
	//file_in= fopen(file_path, "r");
	fopen_s(&file_in,file_path,"r");
	if(file_in!=NULL)
	{
		fseek(file_in,0,SEEK_SET);
		fscanf_s(file_in,"%s",out[0],str_len+1); 
		nr_file=atoi(out[0]);
		for(i=0;i<nr_file;i++)
		{ 
			fscanf_s(file_in,"%s",out[i],str_len+1); 
		}
		fclose(file_in);
		return(nr_file);
	}
	else
	{
		printf("Can not open file: %s\n",file_path);
		getchar();
		return(-1);
	}
}
int qx_file_open_acts(char*filename,float scale,int nr_camera,double **pmat,double **kmat)
{
	FILE *file; char str[300]; int str_len=300; double rmat[9],t[3];
	if(fopen_s(&file,filename,"r")==0)
	{
		fseek(file,0,SEEK_SET);
		for(int i=0;i<6;i++) fgets(str,str_len,file);
		if(atoi(str)!=nr_camera)
		{
			printf("[nr_camera_in != nr_camera_file]   [%05d != %05d]\n",nr_camera,atoi(str));
			return(-2);
		}
		for(int i=0;i<nr_camera;i++)
		{
			fgets(str,str_len,file);
			if(kmat)
			{
				for(int c=0;c<9;c++) {fscanf_s(file,"%s",str,str_len); kmat[i][c]=atof(str);}
			}
			else for(int j=0;j<3;j++) fgets(str,str_len,file);
			for(int j=0;j<3;j++) for(int k=0;k<3;k++) {fscanf_s(file,"%s",str,str_len); rmat[j*3+k]=atof(str);}
			for(int j=0;j<3;j++) {fscanf_s(file,"%s",str,str_len); t[j]=atof(str)*scale;}
			pmat[i][0]=rmat[0]; pmat[i][1]=rmat[3]; pmat[i][2 ]=rmat[6]; pmat[i][3 ]=-(rmat[0]*t[0]+rmat[3]*t[1]+rmat[6]*t[2]);
			pmat[i][4]=rmat[1]; pmat[i][5]=rmat[4]; pmat[i][6 ]=rmat[7]; pmat[i][7 ]=-(rmat[1]*t[0]+rmat[4]*t[1]+rmat[7]*t[2]);
			pmat[i][8]=rmat[2]; pmat[i][9]=rmat[5]; pmat[i][10]=rmat[8]; pmat[i][11]=-(rmat[2]*t[0]+rmat[5]*t[1]+rmat[8]*t[2]);
			fgets(str,str_len,file);
			fgets(str,str_len,file);
		}
	}
	else
	{
		printf("Can not open file: %s\n",filename);
		return(-1);
	}
	return(0);
}
int*qx_file_open_ascii_with_len(char*filename,int&len)
{
	int *index;
	FILE *file_in; char str[65]; int i;
	//file_in=fopen(file_path,"r");
	fopen_s(&file_in,filename,"r");
	if(file_in!=NULL)
	{
		fseek(file_in,0,SEEK_SET);
		fscanf_s(file_in,"%s",str,65); 
		len=atoi(str);
		index=new int [len];
		for(i=0;i<len;i++ )
		{ 
			//fscanf(file_in,"%s",str); 
			fscanf_s(file_in,"%s",str,65); 
			index[i]=atoi(str);
		}
		fclose(file_in);
	}
	else
	{
		printf("qx_basic_file: Can not open file: %s\n",filename);
		getchar();
		exit(-1);
	}
	return(index);
}
bool qx_file_save_ascii_with_len(char *filename,int *out,int len)
{
	FILE * fileout; int i;
	//fileout= fopen(file_path,"w");
	fopen_s(&fileout,filename,"w");
	if(fileout!=NULL)
	{
		fprintf(fileout,"%d ",len);	
		for(i=0;i<len;i++)    
		{	
			fprintf(fileout,"%d ",out[i]);	
		}
		fclose(fileout);
	}
	else
	{
		printf("qx_basic_file: Can not open file: %s\n",filename);
		getchar();
		exit(-1);
	}
	return(true);
}

double*qx_file_open_ascii_with_len_d(char*filename,int&len)
{
	double*index;
	FILE *file_in; char str[65]; int i;
	//file_in=fopen(file_path,"r");
	fopen_s(&file_in,filename,"r");
	if(file_in!=NULL)
	{
		fseek(file_in,0,SEEK_SET);
		fscanf_s(file_in,"%s",str,65); 
		len=atoi(str);
		index=new double [len];
		for(i=0;i<len;i++ )
		{ 
			//fscanf(file_in,"%s",str); 
			fscanf_s(file_in,"%s",str,65); 
			index[i]=atof(str);
		}
		fclose(file_in);
	}
	else
	{
		printf("qx_basic_file: Can not open file: %s\n",filename);
		getchar();
		exit(-1);
	}
	return(index);
}
bool qx_file_save_ascii_with_len_d(char *filename,double*out,int len)
{
	FILE * fileout; int i;
	//fileout= fopen(file_path,"w");
	fopen_s(&fileout,filename,"w");
	if(fileout!=NULL)
	{
		fprintf(fileout,"%d ",len);	
		for(i=0;i<len;i++)    
		{	
			fprintf(fileout,"%f ",out[i]);	
		}
		fclose(fileout);
	}
	else
	{
		printf("qx_basic_file: Can not open file: %s\n",filename);
		getchar();
		exit(-1);
	}
	return(true);
}
bool qx_file_save_ascii_2d_with_len(char *filename,double**out,int h,int w)
{
	FILE * fileout; int i;
	//fileout= fopen(file_path,"w");
	fopen_s(&fileout,filename,"w");
	if(fileout!=NULL)
	{
		fprintf(fileout,"%d %d\n",h,w);	
		for(i=0;i<h;i++)
		{	
			for(int j=0;j<w;j++) fprintf(fileout,"%f ",out[i][j]);
			fprintf(fileout,"\n");
		}
		fclose(fileout);
	}
	else
	{
		printf("qx_basic_file: Can not open file: %s\n",filename);
		getchar();
		exit(-1);
	}
	return(true);
}

double**qx_file_open_ascii_2d_with_len(char*filename,int&h,int&w)
{
	double**out;
	FILE *file_in; char str[300];
	//file_in=fopen(file_path,"r");
	fopen_s(&file_in,filename,"r");
	if(file_in!=NULL)
	{
		fseek(file_in,0,SEEK_SET);
		fscanf_s(file_in,"%s",str,300); 
		h=atoi(str);
		fscanf_s(file_in,"%s",str,300); 
		w=atoi(str);
		out=qx_allocd(h,w);
		for(int i=0;i<h;i++) for(int j=0;j<w;j++)
		{ 
			fscanf_s(file_in,"%s",str,300); 
			out[i][j]=atof(str);
		}
		fclose(file_in);
	}
	else
	{
		printf("qx_basic_file: Can not open file: %s\n",filename);
		getchar();
		exit(-1);
	}
	return(out);
}
void qx_file_open_ascii_2d_with_len(char*filename,double**out,int h,int w)
{
	FILE *file_in; char str[300];
	//file_in=fopen(file_path,"r");
	fopen_s(&file_in,filename,"r");
	if(file_in!=NULL)
	{
		fseek(file_in,0,SEEK_SET);
		fscanf_s(file_in,"%s",str,300); 
		int ho=atoi(str);
		fscanf_s(file_in,"%s",str,300); 
		int wo=atoi(str);
		if(ho!=h||wo!=w)
		{
			printf("[h,ho]: [%d,%d]\n",h,ho);
			printf("[w,wo]: [%d,%d]\n",w,wo);
			getchar();
			exit(-1);
		}
		for(int i=0;i<h;i++) for(int j=0;j<w;j++)
		{ 
			fscanf_s(file_in,"%s",str,300); 
			out[i][j]=atof(str);
		}
		fclose(file_in);
	}
	else
	{
		printf("qx_basic_file: Can not open file: %s\n",filename);
		getchar();
		exit(-1);
	}
}