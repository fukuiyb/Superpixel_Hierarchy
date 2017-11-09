#include "qx_basic.h"
#include "qx_ppm.h"
#include "qx_tree_upsampling.h"
#define QX_DEF_SIGMA							0.1//0.1
void stereo_for_middlebury(char*filename_out,char*filename_guidance_image,char*filename_ground_truth_disparity,int max_disparity,double sigma,int downsample_rate)
{
	int h,w; double scalar=255.0/max_disparity;
	unsigned char***guidance_image,**disparity_gt; double**disparity;
	qx_image_size(filename_guidance_image,h,w);
	guidance_image=qx_allocu_3(h,w,3);//allocate memory
	disparity=qx_allocd(h,w);
	disparity_gt=qx_allocu(h,w);

	qx_loadimage(filename_guidance_image,guidance_image[0][0],h,w);//load guidance image
	qx_loadimage(filename_ground_truth_disparity,disparity_gt[0],h,w);//load ground-truth disparity map

	memset(disparity[0],0,sizeof(double)*h*w);//compute sparse disparity map from the ground truth (as input)
	for(int yi=0;yi<(h>>downsample_rate);yi++) for(int xi=0;xi<(w>>downsample_rate);xi++)
	{
		int y=(yi<<downsample_rate);
		int x=(xi<<downsample_rate);
		disparity[y][x]=(double)disparity_gt[y][x]/scalar;
		if(disparity[y][x]<=2)//ignore invalid pixels (mainly for error pixels in Middlebury images)
		{
			disparity[y][x]=0;
		}
	}

	qx_tree_upsampling m_tree_upsampling;//upsampling class
	m_tree_upsampling.init(h,w,max_disparity,sigma);
	m_tree_upsampling.build_minimum_spanning_tree(guidance_image);
	qx_timer timer;
	timer.start();
	m_tree_upsampling.disparity_upsampling(disparity);//upsample sparse disparity map
	timer.fps_display("upsampling");
	//timer.time_display("nlca",nr_iter);
	

	for(int y=0;y<h;y++) for(int x=0;x<w;x++) disparity_gt[y][x]=unsigned char(disparity[y][x]*scalar+0.5);
	qx_saveimage(filename_out,disparity_gt[0],h,w,1);//save disparity map


	qx_freeu_3(guidance_image); guidance_image=NULL;//free memory
	qx_freeu(disparity_gt); disparity_gt=NULL;
	qx_freed(disparity); disparity=NULL;
}
void main(int argc,char*argv[])
{
	char*filename_out="disparity_upsampled.pgm";
	char*filename_guidance_image="left.ppm";
	char*filename_ground_truth_disparity="disparity_gt.pgm";
	int max_disparity=60;
	double sigma=QX_DEF_SIGMA;
	int downsample_rate=3;
	stereo_for_middlebury(filename_out,filename_guidance_image,filename_ground_truth_disparity,max_disparity,sigma,downsample_rate);
}
