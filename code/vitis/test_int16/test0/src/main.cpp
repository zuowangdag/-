#include <bits/types/FILE.h>
#include <cstdio>
#include <iostream>
#include "utils.h"
#include "ps.h"
#include <string>
#include <cstring>
// #include <opencv2/core/core.hpp>
int main(int argc, char** argv) {
    std::cout << "Hello, World!" << std::endl;
    int row = 640,col = 640;
    char im_name[100];
    if (argc > 1) {
        strcpy(im_name,argv[1]);
    } else {
        strcpy(im_name, "kite.jpg");
    }


    int w=640,h=640,c=3;
    image im = load_image_stb(im_name, 3);
    image resized = letterbox(im, h,w);
    save_image(resized, "resized");
    std::cout << resized.h << " " << resized.w << std::endl;

    // // load weights and bias
    // std::string weight_name("../data/weights/weights_reorg_32_4.bin");
    // // std::string weight_name("../data/weights/weights.bin");
    // std::string bias_name("../data/weights/bias.bin");
    // uint32_t weights_num = get_file_size(weight_name);
    // std::cout << weights_num << std::endl;
    // uint32_t bias_num = get_file_size(bias_name);
    // std::cout << bias_num << std::endl;
    // auto weights = new float[weights_num/(sizeof(float))];
    // auto bias = new float[bias_num/(sizeof(float))];
    // load_bin_file(weight_name,weights_num,weights);
    // load_bin_file(bias_name, bias_num, bias);

    int net_output_num = 255 * 21 * (resized.h >> 5) * (resized.w >> 5);


    network *net = new network;
    std::string cfg_file = "yolov5s.cfg";
    parse_network_cfg(net, cfg_file.c_str(),(resized.h >> 1), (resized.w >> 1));

    float *inputs = new float [resized.h * resized.w * resized.c];
    float *output = new float [net_output_num];

    focus_processing(resized, inputs);
    // FILE *fin = fopen("focus_process.bin", "wb");
    // fwrite(inputs, resized.h * resized.w * resized.c, sizeof(float), fin);
    // fclose(fin);
    // printf("save done\n");
    net_ps(net,inputs, output);
    
    float * nms_res;
    int nms_num;
    
    nms_res = nms(output, &nms_num, net_output_num);

    // FILE *fi = fopen("nms.txt","w");
    // for (int i = 0; i < nms_num; i++) {
    //     fprintf(fi, "index=%2d %f %f %f %f %f %f\n",i, nms_res[i*6 + 0], nms_res[i*6 + 1], nms_res[i*6 + 2], nms_res[i*6 + 3], nms_res[i*6 + 4], nms_res[i*6 + 5]);
    // }
    // fclose(fi);
    image** alphabet = load_alphabet();
    int names_num;
    char** names = get_labels_custom((char*)"coco.names", &names_num);

    scale_coords(im.w,im.h,resized.w,resized.h,nms_res,nms_num);

    draw_detections(im,nms_res,nms_num,alphabet,names,names_num);

    save_image(im,"pred");



    delete [] inputs;
    delete [] output;
    // delete [] weights;
    // delete [] bias;
//    delete net;
    for (int i=0;i < names_num; i++) {
        // free_list((list*)names[i]);
    }
    // for (int i = 0; i < 8; i++) {
    //     for (int j = 0; j < 127; j++) {
    //         free_image(alphabet[i][j]);
    //     }
    //     free_image(*(alphabet[i]));
    // }
    // free(alphabet);
    return 0;
}
