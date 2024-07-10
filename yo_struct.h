//
// Created by admin on 2022/11/9.
//

#ifndef YOLOV5_SFT_YO_STRUCT_H
#define YOLOV5_SFT_YO_STRUCT_H

#include <cstdint>
#include <cstddef>
typedef struct image {
    int c, h, w;
    float *data;
} image;
typedef enum {
    PNG, BMP, TGA, JPG
} IMTYPE;

typedef struct node {
    void *val;
    struct node *next;
    struct node *prev;
} node;
typedef struct list {
    int size;
    node *front;
    node *back;
} list;
typedef struct {
    char *type;
    list *options;
} section;
typedef struct {
    char *key;
    char *val;
    int used;
} kvp;
typedef enum {
    CONVOLUTIONAL,
    SPP,
    Add,
    CONCAT,
    ROUTE,
    MAXPOOL,
    SHORTCUT,
    YOLO,
    UPSAMPLE,
    COST,
    NETWORK,
    EMPTY
} LAYER_TYPE;
typedef enum {
    SILU, LOGISTIC, LEAKY_RELU, NONE
} ACTIVATION;
typedef enum {
    IOU, GIOU, MSE, DIOU, CIOU
} IOU_LOSS;
typedef enum {
    DEFAULT_NMS, GREEDY_NMS, DIOU_NMS, CORNERS_NMS
} NMS_KIND;
typedef struct layer layer;

struct layer {
    LAYER_TYPE type;
    ACTIVATION activation;
    ACTIVATION lstm_activation;

    // COST_TYPE cost_type;
    void (*forward)(struct layer, struct network_state);

    void (*backward)(struct layer, struct network_state);

    void (*update)(struct layer, int, float, float, float);

    void (*forward_gpu)(struct layer, struct network_state);

    void (*backward_gpu)(struct layer, struct network_state);

    void (*update_gpu)(struct layer, int, float, float, float, float);

    layer *share_layer;
    int train;
    int avgpool;
    int batch_normalize;
    int shortcut;
    int batch;
    int dynamic_minibatch;
    int forced;
    int flipped;
    int inputs;
    int outputs;
    float mean_alpha;
    int nweights;
    int nbiases;
    int extra;
    int truths;
    int h, w, c;
    int out_h, out_w, out_c;
    int n;
    int max_boxes;
    int truth_size;
    int groups;
    int group_id;
    int size;
    int side;
    int stride;
    int stride_x;
    int stride_y;
    int dilation;
    int antialiasing;
    int maxpool_depth;
    int maxpool_zero_nonmax;
    int out_channels;
    float reverse;
    int coordconv;
    int flatten;
    int spatial;
    int pad;
    int sqrt;
    int flip;
    int index;
    int scale_wh;
    int binary;
    int xnor;
    int peephole;
    int use_bin_output;
    int keep_delta_gpu;
    int optimized_memory;
    int steps;
    int history_size;
    int bottleneck;
    float time_normalizer;
    int state_constrain;
    int hidden;
    int truth;
    float smooth;
    float dot;
    int deform;
    int grad_centr;
    int sway;
    int rotate;
    int stretch;
    int stretch_sway;
    float angle;
    float jitter;
    float resize;
    float saturation;
    float exposure;
    float shift;
    float ratio;
    float learning_rate_scale;
    float clip;
    int focal_loss;
    float *classes_multipliers;
    float label_smooth_eps;
    int noloss;
    int softmax;
    int classes;
    int detection;
    int embedding_layer_id;
    float *embedding_output;
    int embedding_size;
    float sim_thresh;
    int track_history_size;
    int dets_for_track;
    int dets_for_show;
    float track_ciou_norm;
    int coords;
    int background;
    int rescore;
    int objectness;
    int does_cost;
    int joint;
    int noadjust;
    int reorg;
    int log;
    int tanh;
    int *mask;
    int total;
    float bflops;

    int adam;
    float B1;
    float B2;
    float eps;

    int t;

    float alpha;
    float beta;
    float kappa;

    float coord_scale;
    float object_scale;
    float noobject_scale;
    float mask_scale;
    float class_scale;
    int bias_match;
    float random;
    float ignore_thresh;
    float truth_thresh;
    float iou_thresh;
    float thresh;
    float focus;
    int classfix;
    int absolute;
    int assisted_excitation;

    int onlyforward;
    int stopbackward;
    int train_only_bn;
    int dont_update;
    int burnin_update;
    int dontload;
    int dontsave;
    int dontloadscales;
    int numload;

    float temperature;
    float probability;
    float dropblock_size_rel;
    int dropblock_size_abs;
    int dropblock;
    float scale;

    int receptive_w;
    int receptive_h;
    int receptive_w_scale;
    int receptive_h_scale;

    char *cweights;
    int *indexes;
    int *input_layers;
    int *input_sizes;
    float **layers_output;
    float **layers_delta;
    // WEIGHTS_TYPE_T weights_type;
    // WEIGHTS_NORMALIZATION_T weights_normalization;
    int *map;
    int *counts;
    float **sums;
    float *rand;
    float *cost;
    int *labels;
    int *class_ids;
    int contrastive_neg_max;
    float *cos_sim;
    float *exp_cos_sim;
    float *p_constrastive;
    // contrastive_params *contrast_p_gpu;
    float *state;
    float *prev_state;
    float *forgot_state;
    float *forgot_delta;
    float *state_delta;
    float *combine_cpu;
    float *combine_delta_cpu;

    float *concat;
    float *concat_delta;

    float *binary_weights;

    float *biases;
    float *bias_updates;

    float *scales;
    float *scale_updates;

    float *weights_ema;
    float *biases_ema;
    float *scales_ema;

    float *weights;
    float *weight_updates;

    float scale_x_y;
    int objectness_smooth;
    int new_coords;
    int show_details;
    float max_delta;
    float uc_normalizer;
    float iou_normalizer;
    float obj_normalizer;
    float cls_normalizer;
    float delta_normalizer;
    IOU_LOSS iou_loss;
    IOU_LOSS iou_thresh_kind;
    NMS_KIND nms_kind;
    float beta_nms;
    // YOLO_POINT yolo_point;

    char *align_bit_weights_gpu;
    float *mean_arr_gpu;
    float *align_workspace_gpu;
    float *transposed_align_workspace_gpu;
    int align_workspace_size;

    char *align_bit_weights;
    float *mean_arr;
    int align_bit_weights_size;
    int lda_align;
    int new_lda;
    int bit_align;

    float *col_image;
    float *delta;
    float *output;
    float *activation_input;
    int delta_pinned;
    int output_pinned;
    float *loss;
    float *squared;
    float *norms;

    float *spatial_mean;
    float *mean;
    float *variance;

    float *mean_delta;
    float *variance_delta;

    float *rolling_mean;
    float *rolling_variance;

    float *x;
    float *x_norm;

    float *m;
    float *v;

    float *bias_m;
    float *bias_v;
    float *scale_m;
    float *scale_v;


    float *z_cpu;
    float *r_cpu;
    float *h_cpu;
    float *stored_h_cpu;
    float *prev_state_cpu;

    float *temp_cpu;
    float *temp2_cpu;
    float *temp3_cpu;

    float *dh_cpu;
    float *hh_cpu;
    float *prev_cell_cpu;
    float *cell_cpu;
    float *f_cpu;
    float *i_cpu;
    float *g_cpu;
    float *o_cpu;
    float *c_cpu;
    float *stored_c_cpu;
    float *dc_cpu;

    float *binary_input;
    uint32_t *bin_re_packed_input;
    char *t_bit_input;

    struct layer *input_layer;
    struct layer *self_layer;
    struct layer *output_layer;

    struct layer *reset_layer;
    struct layer *update_layer;
    struct layer *state_layer;

    struct layer *input_gate_layer;
    struct layer *state_gate_layer;
    struct layer *input_save_layer;
    struct layer *state_save_layer;
    struct layer *input_state_layer;
    struct layer *state_state_layer;

    struct layer *input_z_layer;
    struct layer *state_z_layer;

    struct layer *input_r_layer;
    struct layer *state_r_layer;

    struct layer *input_h_layer;
    struct layer *state_h_layer;

    struct layer *wz;
    struct layer *uz;
    struct layer *wr;
    struct layer *ur;
    struct layer *wh;
    struct layer *uh;
    struct layer *uo;
    struct layer *wo;
    struct layer *vo;
    struct layer *uf;
    struct layer *wf;
    struct layer *vf;
    struct layer *ui;
    struct layer *wi;
    struct layer *vi;
    struct layer *ug;
    struct layer *wg;

    // tree *softmax_tree;

    size_t workspace_size;

//#ifdef GPU
    int *indexes_gpu;

    int stream;
    int wait_stream_id;

    float *z_gpu;
    float *r_gpu;
    float *h_gpu;
    float *stored_h_gpu;
    float *bottelneck_hi_gpu;
    float *bottelneck_delta_gpu;

    float *temp_gpu;
    float *temp2_gpu;
    float *temp3_gpu;

    float *dh_gpu;
    float *hh_gpu;
    float *prev_cell_gpu;
    float *prev_state_gpu;
    float *last_prev_state_gpu;
    float *last_prev_cell_gpu;
    float *cell_gpu;
    float *f_gpu;
    float *i_gpu;
    float *g_gpu;
    float *o_gpu;
    float *c_gpu;
    float *stored_c_gpu;
    float *dc_gpu;

    // adam
    float *m_gpu;
    float *v_gpu;
    float *bias_m_gpu;
    float *scale_m_gpu;
    float *bias_v_gpu;
    float *scale_v_gpu;

    float *combine_gpu;
    float *combine_delta_gpu;

    float *forgot_state_gpu;
    float *forgot_delta_gpu;
    float *state_gpu;
    float *state_delta_gpu;
    float *gate_gpu;
    float *gate_delta_gpu;
    float *save_gpu;
    float *save_delta_gpu;
    float *concat_gpu;
    float *concat_delta_gpu;

    float *binary_input_gpu;
    float *binary_weights_gpu;
    float *bin_conv_shortcut_in_gpu;
    float *bin_conv_shortcut_out_gpu;

    float *mean_gpu;
    float *variance_gpu;
    float *m_cbn_avg_gpu;
    float *v_cbn_avg_gpu;

    float *rolling_mean_gpu;
    float *rolling_variance_gpu;

    float *variance_delta_gpu;
    float *mean_delta_gpu;

    float *col_image_gpu;

    float *x_gpu;
    float *x_norm_gpu;
    float *weights_gpu;
    float *weight_updates_gpu;
    float *weight_deform_gpu;
    float *weight_change_gpu;

    float *weights_gpu16;
    float *weight_updates_gpu16;

    float *biases_gpu;
    float *bias_updates_gpu;
    float *bias_change_gpu;

    float *scales_gpu;
    float *scale_updates_gpu;
    float *scale_change_gpu;

    float *input_antialiasing_gpu;
    float *output_gpu;
    float *output_avg_gpu;
    float *activation_input_gpu;
    float *loss_gpu;
    float *delta_gpu;
    float *cos_sim_gpu;
    float *rand_gpu;
    float *drop_blocks_scale;
    float *drop_blocks_scale_gpu;
    float *squared_gpu;
    float *norms_gpu;

    float *gt_gpu;
    float *a_avg_gpu;

    int *input_sizes_gpu;
    float **layers_output_gpu;
    float **layers_delta_gpu;
// #ifdef CUDNN
//     cudnnTensorDescriptor_t srcTensorDesc, dstTensorDesc;
//     cudnnTensorDescriptor_t srcTensorDesc16, dstTensorDesc16;
//     cudnnTensorDescriptor_t dsrcTensorDesc, ddstTensorDesc;
//     cudnnTensorDescriptor_t dsrcTensorDesc16, ddstTensorDesc16;
//     cudnnTensorDescriptor_t normTensorDesc, normDstTensorDesc, normDstTensorDescF16;
//     cudnnFilterDescriptor_t weightDesc, weightDesc16;
//     cudnnFilterDescriptor_t dweightDesc, dweightDesc16;
//     cudnnConvolutionDescriptor_t convDesc;
//     cudnnConvolutionFwdAlgo_t fw_algo, fw_algo16;
//     cudnnConvolutionBwdDataAlgo_t bd_algo, bd_algo16;
//     cudnnConvolutionBwdFilterAlgo_t bf_algo, bf_algo16;
//     cudnnPoolingDescriptor_t poolingDesc;
// #else   // CUDNN
//     void* srcTensorDesc, *dstTensorDesc;
//     void* srcTensorDesc16, *dstTensorDesc16;
//     void* dsrcTensorDesc, *ddstTensorDesc;
//     void* dsrcTensorDesc16, *ddstTensorDesc16;
//     void* normTensorDesc, *normDstTensorDesc, *normDstTensorDescF16;
//     void* weightDesc, *weightDesc16;
//     void* dweightDesc, *dweightDesc16;
//     void* convDesc;
//     UNUSED_ENUM_TYPE fw_algo, fw_algo16;
//     UNUSED_ENUM_TYPE bd_algo, bd_algo16;
//     UNUSED_ENUM_TYPE bf_algo, bf_algo16;
    void *poolingDesc;
// #endif  // CUDNN
//#endif  // GPU
};

typedef struct network {

    int n;
    int batch;
    layer *layers;
    float *output;
    float *input;
    int inputs;
    int outputs;
    int h, w, c;
} network;
typedef struct size_params {
    int batch;
    int inputs;
    int h;
    int w;
    int c;
    int index;
    // int time_steps;
    // int train;
    network net;
} size_params;

typedef layer convolutional_layer;
typedef layer maxpool_layer;
typedef layer route_layer;
typedef layer shortcut_layer;
typedef layer yolo_layer;

#endif //YOLOV5_SFT_YO_STRUCT_H
