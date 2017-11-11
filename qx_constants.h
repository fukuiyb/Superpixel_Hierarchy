/*$Id: qx_constant.h,v 1.3 2007/04/04 02:15:14 liiton Exp $*/
/*******************************************************
\Author:	Qingxiong Yang (liiton)
\Function:	Constants definition.
********************************************************/
#ifndef QX_CONSTANTS_H
#define QX_CONSTANTS_H

#define QX_DEF_INIT_OK				1
#define QX_DEF_INIT_ERROR			-1
#define QX_DEF_MAIN_OK				2
#define QX_DEF_MAIN_ERROR			-2

#ifndef NULL
    #define NULL 0
#endif

/*Maths*/
#define QX_PI		3.1415926535897932384626433832795
#define QX_2PI		6.283185307179586476925286766559
#define QX_PI_2		1.5707963267948966192313216916398
#define QX_ONEDEG	0.017453292519943295769236907684886
#define QX_ONERAD	57.295779513082320876798154814105	
#define QX_SQRT2	1.4142135623730950488016887242097
#define QX_SQRT3	1.7320508075688772935274463415059
#define QX_LN2		0.69314718055994530941723212145818
#define QX_REC_LN2	1.4426950408889634073599246810019

#define QX_MAX_LINE_LENGTH              400
#define QX_DEF_SEED                      42
#define QX_DEF_PADDING                  128
/*Iterative refinement*/
#define QX_DEF_MAX_IT				     25
#define QX_DEF_IMP_REQ                    0.001
/*RANSAC*/
#define QX_DEF_CHUNK_SIZE               200      /*100*/
#define QX_DEF_NR_HYP                   1000      /*500*/
#define QX_DEF_MAX_OBS                 1000      /*1000*/
/*Numerical differentiation*/
#define QX_DEF_NUM_DIFF_EPSI	     1.0e-5    /*1.0e-5*/
/*Feature standard deviation parameters*/
#define QX_DEF_SIGMA (1.0/((352.0+288.0)/2.0)) /*1 pixel for CIF (fraction of (image width+image height)/2)*/
#define QX_DEF_OUTLIER_THRESH           3.0      /*In number of sigma's*/
/*Feature detection parameters*/
#define QX_DEF_MAX_NR_FEATURES         5000      /*5000*/
#define QX_DEF_NR_FEATURE_BLOCKS         10      /*10*/
/*Harris threshold*/
#define QX_DEF_ABS_THRESHOLD       50000000.0    /*50000000.0*/
/*Pyramid*/
#define QX_DEF_MAX_OVERSAMPLOCT           3
#define QX_DEF_BILINEAR				      1
#define QX_DEF_PYRAMID_NR_POST_SMOOTHS    0 /*0*/
/*Feature tracking parameters*/
#define QX_DEF_MAX_DISPARITY              0.1    /*0.1*/
#define QX_DEF_MAX_TRACKLENGTH          300      /*300*/

#define QX_TRACK_CONTINUED                1
#define QX_TRACK_NEW                      2
#define QX_TRACK_EMPTY                    3
#endif /*QX_CONSTANTS_H*/