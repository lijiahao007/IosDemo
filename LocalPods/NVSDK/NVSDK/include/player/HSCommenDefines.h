//
// Created by King on 2023-03-17.
//

#ifndef ANDROID_V380PRO_20230302_HSCOMMENDEFINES_H
#define ANDROID_V380PRO_20230302_HSCOMMENDEFINES_H

typedef enum {
    DMODE_UNKNOW = 0,
    DMODE_NORMAL_1X=1,
    DMODE_NORMAL_2X=2,
    DMODE_NORMAL_3X=3,
    DMODE_NORMAL_4X=4,
    DMODE_FISHEYE_PANO=5,
}HSDISPLAY_MODE;

#define DOUL_MODE_SEPARATE_VERTICAL 0  //单独上下显示
#define DOUL_MODE_SEPARATE_HORIZONTAL 1  //单独左右显示
#define DOUL_MODE_PICINPIC 2 //画中画
#define DOUL_MODE_SINGLE_SCREEN 3 //只显示单画面

#define THREE_CAM_MODE_SEPARATE_VERTICAL 10  //单独上下显示
#define THREE_CAM_MODE_SEPARATE_HORIZONTAL 11  //单独左右显示,右上下
#define THREE_CAM_MODE_PICINPIC 12 //画中画（单画面全屏）
#define THREE_CAM_MODE_PICINPIC_REVERSE 13 //画中画(两画面全屏)
#define THREE_CAM_MODE_SINGLE_SCREEN 14 //只显示单画面
#define THREE_CAM_MODE_SINGLE_SCREEN_REVERSE 15 //只显示单画面(两画面全屏)
#define THREE_CAM_MODE_SEPARATE_VERTICAL_REVERSE 17  //单独上下显示(上面双画面)

//数据拼接类型
#define HSCM_SINGLE   0 //单画面
#define HSCM_DOUL_VERTICAL   1//上下拼接双画面
#define HSCM_DOUL_HORIZONTAL   2//左右拼接双画面
#define HSCM_DOUL_VERTICAL_FOR_THREE   3//上下拼接双画面，第二路拆分为双画面（假三画面）

typedef enum {
    PICNPIC_SET_CUSTOM =0,//指定x，y坐标
    PICNPIC_LEFT_TOP =1,
    PICNPIC_LEFT_CENTER =2,
    PICNPIC_LEFT_BOTTOM =3,

    PICNPIC_CENTER_TOP =4,
    PICNPIC_CENTER =5,
    PICNPIC_CENTER_BOTTOM =6,

    PICNPIC_RIGHT_TOP =7,
    PICNPIC_RIGHT_CENTER =8,
    PICNPIC_RIGHT_BOTTOM =9,
}PICNPIC_POSITION;

typedef enum HSGLColorType{
    HSGLCT_RGB = 0,
    HSGLCT_YUV420P = 1,
}HSGL_COLOR_TYPE;

#define  VIEW_MODE_ORIGIN            0
#define  VIEW_MODE_PERS                1
#define  VIEW_MODE_PERS_LNGLAT        2
#define  VIEW_MODE_LNGLATCYLINDER    3
#define  VIEW_MODE_LNGLATHORI        4
#define  VIEW_MODE_LNGLATVERT        5
#define  VIEW_MODE_2xLNGLAT180        6
#define  VIEW_MODE_4xPERS            7
#define  VIEW_MODE_ORIGIN_3xPERS    8
#define  VIEW_MODE_ORIGIN_5xPERS    9
#define   VIEW_MODE_ORIGIN_1xPERS  10
#define   VIEW_MODE_ORIGIN_2xPERS_LNGLAT  11
#define   VIEW_MODE_LNGLAT_ONLY         12
#define  VIEW_MODE_RECT_ONLY           13
#define  VIEW_MODE_RECT_2xORIGIN            14
#define  VIEW_MODE_RECT_2_PANO           15
#define  VIEW_MODE_RECT_4xNORMAL            16
#define  VIEW_MODE_RECT_3xNORMAL            17

#endif //ANDROID_V380PRO_20230302_HSCOMMENDEFINES_H

