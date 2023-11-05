//
// Created by admin on 2023/10/7.
//

#ifndef PROBRANCH_YUV_COMPRESS_H
#define PROBRANCH_YUV_COMPRESS_H

#ifdef __cplusplus
namespace libyuv {
extern "C" {
#endif
void nv12ToI420(char *src_data, int width, int height, char *dst_data);
void i420ToNv21(char *src_data, int width, int height, char *dst_data);
void rotateI420(char *src_data, int width, int height, char *dst_data, int degree);
void scaleI420(char *src_data, int src_width, int src_height, char *dst_data, int dst_width, int dst_height, int mode);
void mirrorI420(char *src_data, int width, int height, char *dst_data);
bool cropI420(char *src_data, int src_width, int src_height, char *dst_data, int dst_width, int dst_height, int crop_x, int crop_y);
#ifdef __cplusplus
}  // extern "C"
}  // namespace libyuv
#endif

#endif //PROBRANCH_YUV_COMPRESS_H
