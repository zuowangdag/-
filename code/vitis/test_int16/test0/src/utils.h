//
// Created by admin on 2022/11/9.
//

#ifndef YOLOV5_SFT_UTILS_H
#define YOLOV5_SFT_UTILS_H
#include "yo_struct.h"
#include <cstdio>
#include <string>


image make_empty_image(int w, int h, int c);
image make_image(int w, int h, int c);
image load_image_stb(char *filename, int channels);
float get_pixel(image m, int x, int y, int c);
void set_pixel(image m, int x, int y, int c, float val);
void add_pixel(image m, int x, int y, int c, float val);
void free_image(image m);
image resize_image(image im, int w, int h);
void fill_image(image m, float s);
void embed_image(image source, image dest, int dx, int dy);
image letterbox_image(image im, int w, int h);
image letterbox(image im, int h, int w,int stride=32);
void save_image_options(image im, const char *name, IMTYPE f, int quality);
void save_image(image im, const char *name);
void focus_processing(image im, float *inputs);
image devide_into_4_pieces(image im);
image load_image(char *filename, int w, int h, int c);
image copy_image(image p);
static float get_pixel_extend(image m, int x, int y, int c);
void composite_image(image source, image dest, int dx, int dy);
image tile_images(image a, image b, int dx);
image border_image(image a, int border);
void fill_cpu(int N, float ALPHA, float *X, int INCX);



list *get_paths(char *filename);
void **list_to_array(list *l);
char **get_labels_custom(char *name_list, int *name_num);
image **load_alphabet();

// network cfgs
void file_error(char *s);
void file_error(const char *s);
void malloc_error();
void *xmalloc(size_t size);
list *make_list();
void realloc_error();
void *xrealloc(void *ptr, size_t size);
void error(const char *s);
void calloc_error();
void *xcalloc(size_t nmemb, size_t size);
void strip(char *s);
char *fgetl(FILE *fp);
void list_insert(list *l, void *val);
void option_insert(list *l, char *key, char *val);
int read_option(char *s, list *options);
list *read_cfg(const char *filename);
network make_network(int n);
int is_network(section *s);
char* option_find(list *l,char *key);
int option_find_int(list *l,char *key,int def);
int option_find_int_quiet(list *l, char *key, int def);
void parse_net_options(list *options, network *net, int h=640, int w = 640);
void free_section(section *s);
char *option_find_str(list *l, char *key, char *def);
char *option_find_str_quiet(list *l, char *key, char *def);
void free_node(node *n);
void free_list(list *l);
LAYER_TYPE string_to_layer_type(char *type);
ACTIVATION get_activation(char *s);
int convolutional_out_height(convolutional_layer l);
int convolutional_out_width(convolutional_layer l);
convolutional_layer make_convolutional_layer(int batch, int steps, int h, int w, int c, int n, int size, int stride_x, int stride_y, int padding, ACTIVATION activation);
convolutional_layer parse_convolutional(list *options,size_params params);
int *parse_yolo_mask(char *a, int *num);
layer make_yolo_layer(int batch,int w,int h,int n,int total,int *mask,int classes,int max_boxes);
layer parse_yolo(list *options,size_params params);
maxpool_layer make_maxpool_layer(int batch, int h, int w, int c, int size, int stride,int padding);
maxpool_layer parse_maxpool(list *options, size_params params);
layer make_route_layer(int batch,int n,int *layers,int *input_sizes);
layer parse_route(list *options,size_params params);
layer make_upsample_layer(int batch,int w,int h,int c,int stride);
layer parse_upsample(list *options, size_params params, network net);
layer make_shortcut_layer(int batch,int n,int *input_layers,int *input_sizes,int w,int h,int c,float **layers_output);
layer parse_shortcut(list *options,size_params params,network net);
network parse_network_cfg_custom(const char* cfg, int h=640, int w=640);
void parse_network_cfg(network *net, const char* cfg, int h=640, int w=640);
uint32_t get_file_size(char* filename);
template <typename T>
void load_bins(const std::string &filename, const size_t &file_size, T *data);

void load_bin_file(const std::string &filename, const size_t &file_size, float *data);
float* nms(float *res,int* num,int net_num);
void scale_coords(int org_w,int org_h,int new_w,int new_h,float* res,int num);
char* get_cls(int cls_index,char **names);
float get_color(int c, int x, int max);
void draw_box(image a, int x1, int y1, int x2, int y2, float r, float g, float b);
void draw_box_width(image a, int x1, int y1, int x2, int y2, int w, float r, float g, float b);
image get_label_new(image **characters, char *string, int size);
void draw_weighted_label(image a,int r,int c,image label,const float *rgb,const float alpha);
void draw_detections(image img,float *res,int n,image** alphabet,char** names,int classes);
#endif //YOLOV5_SFT_UTILS_H
