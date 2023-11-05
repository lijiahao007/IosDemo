//
// Created by admin on 2023/10/7.
//

#include "yuv_compress.h"
#include "convert.h"
#include "video_common.h"

#ifdef __cplusplus
namespace libyuv {
extern "C" {
#endif

// 预览解码 --> i420
// ios 摄像头采集 nv12
//


// yuv nv21转i420
void nv12ToI420(char *src_data, int width, int height, char *dst_data) {
    int y_size = width * height;
    int u_size = (width >> 1) * (height >> 1);
    char *src_y_data = src_data;
    char *src_vu_data = src_data + y_size;
    char *dst_y_data = dst_data;
    char *dst_u_data = dst_data + y_size;
    char *dst_v_data = dst_data + y_size + u_size;
    libyuv::NV12ToI420(
            (const uint8_t *) src_y_data, width,
            (const uint8_t *) src_vu_data, width,
            (uint8_t *) dst_y_data, width,
            (uint8_t *) dst_u_data, width >> 1,
            (uint8_t *) dst_v_data, width >> 1,
            width, height);
}

// yuv i420转nv21
void i420ToNv21(char *src_data, int width, int height, char *dst_data) {
    int y_size = width * height;
    int u_size = (width >> 1) * (height >> 1);
    char *src_y_data = src_data;
    char *src_u_data = src_data + y_size;
    char *src_v_data = src_data + y_size + u_size;
    char *dst_y_data = dst_data;
    char *dst_vu_data = dst_data + y_size;
    libyuv::I420ToNV21(
            (const uint8_t *) src_y_data, width,
            (const uint8_t *) src_u_data, width >> 1,
            (const uint8_t *) src_v_data, width >> 1,
            (uint8_t *) dst_y_data, width,
            (uint8_t *) dst_vu_data, width,
            width, height);
}

// 旋转
void rotateI420(char *src_data, int width, int height, char *dst_data, int degree) {
    int y_size = width * height;
    int u_size = (width >> 1) * (height >> 1);
    char *src_y_data = src_data;
    char *src_u_data = src_data + y_size;
    char *src_v_data = src_data + y_size + u_size;
    char *dst_y_data = dst_data;
    char *dst_u_data = dst_data + y_size;
    char *dst_v_data = dst_data + y_size + u_size;

    int dst_stride_y;
    if (degree == libyuv::kRotate90 || degree == libyuv::kRotate270) { // width height 对调的
        dst_stride_y = height;
    } else {
        dst_stride_y = width;
    }
    libyuv::I420Rotate((const uint8_t *) src_y_data, width,
                       (const uint8_t *) src_u_data, width >> 1,
                       (const uint8_t *) src_v_data, width >> 1,
                       (uint8_t *) dst_y_data, dst_stride_y,
                       (uint8_t *) dst_u_data, dst_stride_y >> 1,
                       (uint8_t *) dst_v_data, dst_stride_y >> 1,
                       width, height,
                       (libyuv::RotationMode) degree);
}

// 缩放  mode 压缩模式 ，0~3，质量由低到高，一般传入0
void scaleI420(char *src_data, int src_width, int src_height, char *dst_data, int dst_width, int dst_height, int mode) {
    int src_y_size = src_width * src_height;
    int src_u_size = (src_width >> 1) * (src_height >> 1);
    char *src_y_data = src_data;
    char *src_u_data = src_data + src_y_size;
    char *src_v_data = src_data + src_y_size + src_u_size;

    int dst_y_size = dst_width * dst_height;
    int dst_u_size = (dst_width >> 1) * (dst_height >> 1);
    char *dst_y_data = dst_data;
    char *dst_u_data = dst_data + dst_y_size;
    char *dst_v_data = dst_data + dst_y_size + dst_u_size;

    libyuv::I420Scale((const uint8_t *) src_y_data, src_width,
                      (const uint8_t *) src_u_data, src_width >> 1,
                      (const uint8_t *) src_v_data, src_width >> 1,
                      src_width, src_height,
                      (uint8_t *) dst_y_data, dst_width,
                      (uint8_t *) dst_u_data, dst_width >> 1,
                      (uint8_t *) dst_v_data, dst_width >> 1,
                      dst_width, dst_height,
                      (libyuv::FilterMode) mode);
}

// 镜像
void mirrorI420(char *src_data, int width, int height, char *dst_data) {
    int y_size = width * height;
    int u_size = (width >> 1) * (height >> 1);
    char *src_y_data = src_data;
    char *src_u_data = src_data + y_size;
    char *src_v_data = src_data + y_size + u_size;
    char *dst_y_data = dst_data;
    char *dst_u_data = dst_data + y_size;
    char *dst_v_data = dst_data + y_size + u_size;
    libyuv::I420Mirror((const uint8_t *) src_y_data, width,
                       (const uint8_t *) src_u_data, width >> 1,
                       (const uint8_t *) src_v_data, width >> 1,
                       (uint8_t *) dst_y_data, width,
                       (uint8_t *) dst_u_data, width >> 1,
                       (uint8_t *) dst_v_data, width >> 1,
                       width, height);
}

// 裁剪
bool cropI420(char *src_data, int src_width, int src_height, char *dst_data, int dst_width, int dst_height, int crop_x, int crop_y) {
    if (crop_x + dst_width > src_width || crop_y + dst_height > src_height) { // 超出区域
        return false;
    }
    if (crop_x % 2 != 0 || crop_y % 2 != 0) { // 必须为偶数，不然有问题
        return false;
    }
    int src_yuv_size = src_width * src_height * 3 / 2;

    int dst_y_size = dst_width * dst_height;
    int dst_u_size = (dst_width >> 1) * (dst_height >> 1);
    char *dst_y_data = dst_data;
    char *dst_u_data = dst_data + dst_y_size;
    char *dst_v_data = dst_data + dst_y_size + dst_u_size;
    libyuv::ConvertToI420(
            (const uint8_t *) src_data, src_yuv_size,
            (uint8_t *) dst_y_data, dst_width,
            (uint8_t *) dst_u_data, dst_width >> 1,
            (uint8_t *) dst_v_data, dst_width >> 1,
            crop_x, crop_y,
            src_width, src_height,
            dst_width, dst_height,
            libyuv::kRotate0, libyuv::FOURCC_I420);
    return true;
}

#ifdef __cplusplus
}  // extern "C"
}  // namespace libyuv
#endif
