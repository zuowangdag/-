//
// Created by admin on 2022/11/9.
//

#include "utils.h"
#include <bits/types/FILE.h>
#include <cassert>
#include <cstring>
#include <sys/stat.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#define MIN(x,y) (x < y) ? (x) : (y)
#define MAX(x,y) (x > y) ? (x) : (y)
float colors[6][3] = { {1,0,1}, {0,0,1},{0,1,1},{0,1,0},{1,1,0},{1,0,0} };

// image functions
image make_empty_image(int w, int h, int c)
{
    image out;
    out.data = 0;
    out.h = h;
    out.w = w;
    out.c = c;
    return out;
}
image make_image(int w, int h, int c)
{
    image out = make_empty_image(w, h, c);
    out.data = (float *)calloc(h * w * c, sizeof(float));
    return out;
}
image load_image_stb(char *filename, int channels)
{
    int w, h, c;
    unsigned char *data = stbi_load(filename, &w, &h, &c, channels);
    if (!data)
    {
        fprintf(stderr, "Cannot load image \"%s\"\nSTB Reason: %s\n", filename, stbi_failure_reason());
        exit(0);
    }
    if (channels)
        c = channels;
    int i, j, k;
    image im = make_image(w, h, c);
    for (k = 0; k < c; ++k)
    {
        for (j = 0; j < h; ++j)
        {
            for (i = 0; i < w; ++i)
            {
                int dst_index = i + w * j + w * h * k;
                int src_index = k + c * i + c * w * j;
                // im.data[dst_index] = (int)data[src_index];
                im.data[dst_index] = (float)data[src_index] / 255.;
            }
        }
    }
    free(data);
    return im;
}
float get_pixel(image m, int x, int y, int c)
{
    assert(x < m.w && y < m.h && c < m.c);
    return m.data[c * m.h * m.w + y * m.w + x];
}
void set_pixel(image m, int x, int y, int c, float val)
{
    if (x < 0 || y < 0 || c < 0 || x >= m.w || y >= m.h || c >= m.c)
        return;
    assert(x < m.w && y < m.h && c < m.c);
    m.data[c * m.h * m.w + y * m.w + x] = val;
}
void add_pixel(image m, int x, int y, int c, float val)
{
    assert(x < m.w && y < m.h && c < m.c);
    m.data[c * m.h * m.w + y * m.w + x] += val;
}
void free_image(image m)
{
    if (m.data)
    {
        free(m.data);
    }
}
image resize_image(image im, int w, int h)
{
    image resized = make_image(w, h, im.c);
    image part = make_image(w, im.h, im.c);
    int r, c, k;
    float w_scale = (float)(im.w - 1) / (w - 1);
    float h_scale = (float)(im.h - 1) / (h - 1);
    for (k = 0; k < im.c; ++k)
    {
        for (r = 0; r < im.h; ++r)
        {
            for (c = 0; c < w; ++c)
            {
                float val = 0;
                if (c == w - 1 || im.w == 1)
                {
                    val = get_pixel(im, im.w - 1, r, k);
                }
                else
                {
                    float sx = c * w_scale;
                    int ix = (int)sx;
                    float dx = sx - ix;
                    val = (1 - dx) * get_pixel(im, ix, r, k) + dx * get_pixel(im, ix + 1, r, k);
                }
                set_pixel(part, c, r, k, val);
            }
        }
    }
    for (k = 0; k < im.c; ++k)
    {
        for (r = 0; r < h; ++r)
        {
            float sy = r * h_scale;
            int iy = (int)sy;
            float dy = sy - iy;
            for (c = 0; c < w; ++c)
            {
                float val = (1 - dy) * get_pixel(part, c, iy, k);
                set_pixel(resized, c, r, k, val);
            }
            if (r == h - 1 || im.h == 1)
                continue;
            for (c = 0; c < w; ++c)
            {
                float val = dy * get_pixel(part, c, iy + 1, k);
                add_pixel(resized, c, r, k, val);
            }
        }
    }

    free_image(part);
    return resized;
}
void fill_image(image m, float s)
{
    int i;
    for (i = 0; i < m.h * m.w * m.c; ++i)
        m.data[i] = s;
}
void embed_image(image source, image dest, int dx, int dy)
{
    int x, y, k;
    for (k = 0; k < source.c; ++k)
    {
        for (y = 0; y < source.h; ++y)
        {
            for (x = 0; x < source.w; ++x)
            {
                float val = get_pixel(source, x, y, k);
                set_pixel(dest, dx + x, dy + y, k, val);
            }
        }
    }
}
image letterbox_image(image im, int w, int h)
{
    int new_w = im.w;
    int new_h = im.h;
    if (((float)w / im.w) < ((float)h / im.h))
    {
        new_w = w;
        new_h = (im.h * w) / im.w;
    }
    else
    {
        new_h = h;
        new_w = (im.w * h) / im.h;
    }
    image resized = resize_image(im, new_w, new_h);
    image boxed = make_image(w, h, im.c);
    fill_image(boxed, .5);
    embed_image(resized, boxed, (w - new_w) / 2, (h - new_h) / 2);
    free_image(resized);
    return boxed;
}
// #include<iostream>
image letterbox(image im, int h, int w,int stride)
{
    
    float r = MIN(((float)h/im.h), ((float)w/im.w));
    // std::cout << r << std::endl;
    int new_unpad_h = im.h * r;
    int new_unpad_w = im.w * r;
    int dw = w - new_unpad_w;
    int dh = h - new_unpad_h;
    dw = dw % stride;
    dh = dh % stride;

    dw /= 2;
    dh /= 2;
    // std::cout << "unpad_h = " << new_unpad_h << " unpad_w = " << new_unpad_w << std::endl;
    // std::cout << "unpad_h = " << dh << " unpad_w = " << dw << std::endl;
    // std::cout << "unpad_h = " << h << " unpad_w = " << w << std::endl;
    image resized = resize_image(im, new_unpad_w, new_unpad_h);
    image boxed = make_image(new_unpad_w + 2 * dw, new_unpad_h + 2 * dh, im.c);
    fill_image(boxed,0.5f);
    int top = int((dh - 0.1));
    int left = int((dw - 0.1));

    embed_image(resized, boxed, left, top);
    free_image(resized);
    return boxed;
}
void save_image_options(image im, const char *name, IMTYPE f, int quality)
{
    char buff[256];
    // sprintf(buff, "%s (%d)", name, windows);
    if (f == PNG)
        sprintf(buff, "%s.png", name);
    else if (f == BMP)
        sprintf(buff, "%s.bmp", name);
    else if (f == TGA)
        sprintf(buff, "%s.tga", name);
    else if (f == JPG)
        sprintf(buff, "%s.jpg", name);
    else
        sprintf(buff, "%s.png", name);
    unsigned char *data = (unsigned char *)calloc(im.w * im.h * im.c, sizeof(char));
    int i, k;
    for (k = 0; k < im.c; ++k)
    {
        for (i = 0; i < im.w * im.h; ++i)
        {
            data[i * im.c + k] = (unsigned char)(255 * im.data[i + k * im.w * im.h]);
        }
    }
    int success = 0;
    if (f == PNG)
        success = stbi_write_png(buff, im.w, im.h, im.c, data, im.w * im.c);
    else if (f == BMP)
        success = stbi_write_bmp(buff, im.w, im.h, im.c, data);
    else if (f == TGA)
        success = stbi_write_tga(buff, im.w, im.h, im.c, data);
    else if (f == JPG)
        success = stbi_write_jpg(buff, im.w, im.h, im.c, data, quality);
    free(data);
    if (!success)
        fprintf(stderr, "Failed to write image %s\n", buff);
}
void save_image(image im, const char *name)
{
    save_image_options(im, name, JPG, 80);
}
void focus_processing(image im, float *inputs)
{
    // fill_cpu(3*640*640,0,inputs,1);
    // int h = im.h / 2;
    // int w = im.w / 2;
    // for (int i = 0; i < im.c; i++)
    // {
    //     for (int j = 0; j < im.h; j += 2)
    //     {
    //         for (int k = 0; k < im.w; k += 2)
    //         {
    //             inputs[i * h * w + j * w/2 + k/2] = get_pixel(im, k, j, i);
    //             inputs[(i + im.c) * h * w + j * w/2 + k/2] = get_pixel(im, k, j + 1, i);
    //             inputs[(i + im.c * 2) * h * w + j * w/2 + k/2] = get_pixel(im, k + 1, j, i);
    //             inputs[(i + im.c * 3) * h * w + j * w/2 + k/2] = get_pixel(im, k + 1, j + 1, i);
    //             if(i==0 && j==0 && k==0)
    //             printf("%f\n",get_pixel(im, k, j, i));
    //         }
    //     }
    // }
    fill_cpu(im.c * im.h * im.w, 0, inputs, 1);
    int h = im.h >> 1;
    int w = im.w >> 1;
    for (int i = 0; i < im.c; i++) {
        for (int j = 0; j < im.h; j+=2) {
            for (int k = 0; k < im.w; k+=2) {
                inputs[i * h * w + j * w/2 + k/2] = get_pixel(im, k, j, i);
                inputs[(i + im.c) * h * w + j * w/2 + k/2] = get_pixel(im, k, j + 1, i);
                inputs[(i + im.c * 2) * h * w + j * w/2 + k/2] = get_pixel(im, k + 1, j, i);
                inputs[(i + im.c * 3) * h * w + j * w/2 + k/2] = get_pixel(im, k + 1, j + 1, i);
            }
        }
    }
}
image devide_into_4_pieces(image im)
{
    image img = make_image((int)im.w / 2, (int)im.h / 2, (int)im.c * 4);
    for (int channel = 0; channel < im.c; channel++)
    {
        for (int w = 0; w < im.w; w += 2)
        {
            for (int h = 0; h < im.h; h += 2)
            {
                set_pixel(img, w / 2, h / 2, channel, get_pixel(im, w, h, channel));
                set_pixel(img, w / 2, h / 2, channel + im.c, get_pixel(im, w, h + 1, channel));
                set_pixel(img, w / 2, h / 2, channel + im.c * 2, get_pixel(im, w + 1, h, channel));
                set_pixel(img, w / 2, h / 2, channel + im.c * 3, get_pixel(im, w + 1, h + 1, channel));
                if(channel==0 && w==0 && h==0)
                printf("%f\n",get_pixel(im, w, h, channel));
            }
        }
    }
    return img;
}

image load_image(char *filename, int w, int h, int c)
{

    image out = load_image_stb(filename, c);

    if ((h && w) && (h != out.h || w != out.w))
    {
        image resized = resize_image(out, w, h);
        free_image(out);
        out = resized;
    }
    return out;
}

image copy_image(image p)
{
    image copy = p;
    copy.data = (float *)calloc(p.h * p.w * p.c, sizeof(float));
    memcpy(copy.data, p.data, p.h * p.w * p.c * sizeof(float));
    return copy;
}
static float get_pixel_extend(image m, int x, int y, int c)
{
    if (x < 0 || x >= m.w || y < 0 || y >= m.h)
        return 0;
    if (c < 0 || c >= m.c)
        return 0;
    return get_pixel(m, x, y, c);
}
void composite_image(image source, image dest, int dx, int dy)
{
    int x, y, k;
    for (k = 0; k < source.c; ++k)
    {
        for (y = 0; y < source.h; ++y)
        {
            for (x = 0; x < source.w; ++x)
            {
                float val = get_pixel(source, x, y, k);
                float val2 = get_pixel_extend(dest, dx + x, dy + y, k);
                set_pixel(dest, dx + x, dy + y, k, val * val2);
            }
        }
    }
}
image tile_images(image a, image b, int dx)
{
    if (a.w == 0)
        return copy_image(b);
    image c = make_image(a.w + b.w + dx, (a.h > b.h) ? a.h : b.h, (a.c > b.c) ? a.c : b.c);
    fill_cpu(c.w * c.h * c.c, 1, c.data, 1);
    embed_image(a, c, 0, 0);
    composite_image(b, c, a.w + dx, 0);
    return c;
}
image border_image(image a, int border)
{
    image b = make_image(a.w + 2 * border, a.h + 2 * border, a.c);
    int x, y, k;
    for (k = 0; k < b.c; ++k)
    {
        for (y = 0; y < b.h; ++y)
        {
            for (x = 0; x < b.w; ++x)
            {
                float val = get_pixel_extend(a, x - border, y - border, k);
                if (x - border < 0 || x - border >= a.w || y - border < 0 || y - border >= a.h)
                    val = 1;
                set_pixel(b, x, y, k, val);
            }
        }
    }
    return b;
}
void fill_cpu(int N, float ALPHA, float *X, int INCX)
{
    int i;
    for(i = 0; i < N; ++i) X[i*INCX] = ALPHA;
}



list *get_paths(char *filename)
{
    char *path;
    FILE *file = fopen(filename, "r");
    if (!file)
        file_error(filename);
    list *lines = make_list();
    while (path = fgetl(file))
    {
        list_insert(lines, path);
    }
    fclose(file);
    return lines;
}
void **list_to_array(list *l)
{
    void **a = (void **)xcalloc(l->size, sizeof(void **));
    int count = 0;
    node *n = l->front;
    while (n)
    {
        a[count++] = n->val;
        n = n->next;
    }
    return a;
}
char **get_labels_custom(char *name_list, int *name_num)
{
    list *plist = get_paths(name_list);
    if (name_num)
        *name_num = plist->size;
    char **labels = (char **)list_to_array(plist);
    free_list(plist);
    return labels;
}
image **load_alphabet()
{
    int i, j;
    const int nsize = 8;
    image **alphabets = (image **)xcalloc(nsize, sizeof(image *));
    for (j = 0; j < nsize; j++)
    {
        alphabets[j] = (image *)xcalloc(128, sizeof(image));
        for (i = 32; i < 127; i++)
        {
            char buff[256];
            sprintf(buff, "labels/%d_%d.png", i, j);
            alphabets[j][i] = load_image(buff, 0, 0, 3);
        }
    }
    return alphabets;
}
// network
void file_error(char *s)
{
    fprintf(stderr, "Couldn't open file: %s\n", s);
    exit(EXIT_FAILURE);
}
void file_error(const char *s)
{
    fprintf(stderr, "Couldn't open file: %s\n", s);
    exit(EXIT_FAILURE);
}
void malloc_error()
{
    fprintf(stderr, "xMalloc error - possibly out of CPU RAM \n");
    exit(EXIT_FAILURE);
}
void *xmalloc(size_t size)
{
    void *ptr = malloc(size);
    if (!ptr)
    {
        malloc_error();
    }
    return ptr;
}
list *make_list()
{
    list *l = (list *)xmalloc(sizeof(list));
    l->size = 0;
    l->front = 0;
    l->back = 0;
    return l;
}
void realloc_error()
{
    fprintf(stderr, "Realloc error - possibly out of CPU RAM \n");
    exit(EXIT_FAILURE);
}
void *xrealloc(void *ptr, size_t size)
{
    ptr = realloc(ptr, size);
    if (!ptr)
    {
        realloc_error();
    }
    return ptr;
}
void error(const char *s)
{
    perror(s);
    assert(0);
    exit(EXIT_FAILURE);
}
void calloc_error()
{
    fprintf(stderr, "Calloc error - possibly out of CPU RAM \n");
    exit(EXIT_FAILURE);
}
void *xcalloc(size_t nmemb, size_t size)
{
    void *ptr = calloc(nmemb, size);
    if (!ptr)
    {
        calloc_error();
    }
    return ptr;
}
char *fgetl(FILE *fp)
{
    if (feof(fp))
        return 0;
    size_t size = 512;
    char *line = (char *)xmalloc(size * sizeof(char));
    if (!fgets(line, size, fp))
    {
        free(line);
        return 0;
    }

    size_t curr = strlen(line);

    while ((line[curr - 1] != '\n') && !feof(fp))
    {
        if (curr == size - 1)
        {
            size *= 2;
            line = (char *)xrealloc(line, size * sizeof(char));
        }
        size_t readsize = size - curr;
        if (readsize > INT_MAX)
            readsize = INT_MAX - 1;
        fgets(&line[curr], readsize, fp);
        curr = strlen(line);
    }
    if (curr >= 2)
        if (line[curr - 2] == 0x0d)
            line[curr - 2] = 0x00;

    if (curr >= 1)
        if (line[curr - 1] == 0x0a)
            line[curr - 1] = 0x00;

    return line;
}
void strip(char *s)
{
    size_t i;
    size_t len = strlen(s);
    size_t offset = 0;
    for(i = 0; i < len; ++i){
        char c = s[i];
        if(c==' '||c=='\t'||c=='\n'||c =='\r'||c==0x0d||c==0x0a) ++offset;
        else s[i-offset] = c;
    }
    s[len-offset] = '\0';
}
void list_insert(list *l, void *val)
{
    node *newnode = (node *)xmalloc(sizeof(node));
    newnode->val = val;
    newnode->next = 0;

    if (!l->back)
    {
        l->front = newnode;
        newnode->prev = 0;
    }
    else
    {
        l->back->next = newnode;
        newnode->prev = l->back;
    }
    l->back = newnode;
    ++l->size;
}
void option_insert(list *l, char *key, char *val)
{
    kvp* p = (kvp*)xmalloc(sizeof(kvp));
    p->key = key;
    p->val = val;
    p->used = 0;
    list_insert(l, p);
}
int read_option(char *s, list *options)
{
    size_t i;
    size_t len = strlen(s);
    char *val = 0;
    for(i = 0; i < len; ++i){
        if(s[i] == '='){
            s[i] = '\0';
            val = s+i+1;
            break;
        }
    }
    if(i == len-1) return 0;
    char *key = s;
    option_insert(options, key, val);
    return 1;
}
list *read_cfg(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if(file == 0) file_error(filename);
    char *line;
    int nu = 0;
    list *sections = make_list();
    section *current = 0;
    while((line=fgetl(file)) != 0){
        ++ nu;
        strip(line);
        switch(line[0]){
            case '[':
                current = (section*)xmalloc(sizeof(section));
                list_insert(sections, current);
                current->options = make_list();
                current->type = line;
                break;
            case '\0':
            case '#':
            case ';':
                free(line);
                break;
            default:
                if(!read_option(line, current->options)){
                    fprintf(stderr, "Config file error line %d, could parse: %s\n", nu, line);
                    free(line);
                }
                break;
        }
    }
    fclose(file);
    return sections;
}
network make_network(int n)
{
    network net={0};
    net.n=n;
    net.layers=(layer*)xcalloc(net.n,sizeof(layer));
    return net;
}
int is_network(section *s)
{
    return (strcmp(s->type, "[net]")==0
            || strcmp(s->type, "[network]")==0);
}
char* option_find(list *l,char *key)
{
    node *n = l->front;
    while(n){
        kvp *p = (kvp *)n->val;
        if(strcmp(p->key, key) == 0){
            p->used = 1;
            return p->val;
        }
        n = n->next;
    }
    return 0;
}
int option_find_int(list *l,char *key,int def)
{
    char *v = option_find(l, key);
    if(v) return atoi(v);
    fprintf(stderr, "%s: Using default '%d'\n", key, def);
    return def;
}
int option_find_int_quiet(list *l, char *key, int def)
{
    char *v = option_find(l, key);
    if(v) return atoi(v);
    return def;
}
void parse_net_options(list *options, network *net, int h, int w)
{
    net->batch = option_find_int(options, (char*)"batch",1);
    const int mini_batch = net->batch;

    int hh = option_find_int_quiet(options, (char*)"height", 0);
    int ww = option_find_int_quiet(options, (char*)"width", 0);
    int cc = option_find_int_quiet(options, (char*)"channels",3);
    if (hh != h) { hh = h;}
    if (ww != w) { ww = w;}
    if (cc != 12) { cc = 12;}
    net->h = hh;
    net->w = ww;
    net->c = cc;
    // net->h = option_find_int_quiet(options, (char*)"height",608);
    // net->w = option_find_int_quiet(options, (char*)"width",608);
    // net->c = option_find_int_quiet(options, (char*)"channels",3);
    net->inputs = option_find_int_quiet(options, (char*)"inputs", net->h * net->w * net->c);

    if(!net->inputs && !(net->h && net->w && net->c)) error("No input parameters supplied");
}
void free_section(section *s)
{
    free(s->type);
    node *n = s->options->front;
    while(n){
        kvp *pair = (kvp *)n->val;
        free(pair->key);
        free(pair);
        node *next = n->next;
        free(n);
        n = next;
    }
    free(s->options);
    free(s);
}
char *option_find_str(list *l, char *key, char *def)
{
    char *v = option_find(l, key);
    if(v) return v;
    if(def) fprintf(stderr, "%s: Using default '%s'\n", key, def);
    return def;
}
char *option_find_str_quiet(list *l, char *key, char *def)
{
    char *v = option_find(l, key);
    if (v) return v;
    return def;
}
void free_node(node *n)
{
    node *next;
    while (n)
    {
        next = n->next;
        free(n);
        n = next;
    }
}
void free_list(list *l)
{
    free_node(l->front);
    free(l);
}
LAYER_TYPE string_to_layer_type(char *type)
{
    if (strcmp(type, "[shortcut]")==0 || strcmp(type,"[Add]")==0)
        return SHORTCUT;
    if (strcmp(type,(char*)"[spp]")==0) return SPP;
    if (strcmp(type, "[yolo]") == 0) return YOLO;
    if (strcmp(type, "[conv]")==0
        || strcmp(type, "[convolutional]")==0) return CONVOLUTIONAL;
    if (strcmp(type, "[net]")==0
        || strcmp(type, "[network]")==0) return NETWORK;
    if (strcmp(type, "[max]")==0
        || strcmp(type, "[maxpool]")==0) return MAXPOOL;
    if (strcmp(type, "[route]")==0 ||strcmp(type,"[concat]")==0) return ROUTE;
    if (strcmp(type, "[upsample]") == 0) return UPSAMPLE;

    return EMPTY;
}
ACTIVATION get_activation(char *s)
{
    if(strcmp(s,"silu")==0) return SILU;
    if(strcmp(s,"logistic")==0) return LOGISTIC;

    fprintf(stderr, "Couldn't find activation function %s, going with logistic\n", s);
    return LOGISTIC;
}
int convolutional_out_height(convolutional_layer l)
{
    return (l.h + 2*l.pad - l.size) / l.stride_y + 1;
}
int convolutional_out_width(convolutional_layer l)
{
    return (l.w + 2*l.pad - l.size) / l.stride_x + 1;
}
convolutional_layer make_convolutional_layer(int batch, int steps, int h, int w, int c, int n, int size, int stride_x, int stride_y, int padding, ACTIVATION activation)
{
    int total_batch = batch*steps;
    int i;
    convolutional_layer l = { (LAYER_TYPE)0 };
    l.type = CONVOLUTIONAL;
    // l.train = train;
    const int blur_stride_x = stride_x;
    const int blur_stride_y = stride_y;
    // l.index = index;
    l.h = h;
    l.w = w;
    l.c = c;
    l.n = n;
    // l.batch = batch;
    // l.steps = steps;
    l.stride = stride_x;
    l.stride_x = stride_x;
    l.stride_y = stride_y;
    // l.dilation = dilation;
    l.size = size;
    l.pad = padding;
    int out_h = convolutional_out_height(l);
    int out_w = convolutional_out_width(l);
    l.out_h = out_h;
    l.out_w = out_w;
    l.out_c = n;
    l.outputs = l.out_h * l.out_w * l.out_c;
    l.inputs = l.w * l.h * l.c;
    l.activation = activation;
    // l.output = (float*)xcalloc(total_batch*l.outputs, sizeof(float));
    printf("conv  %4d      %d x %d / %d\t    ",l.out_c,l.size,l.size,l.stride);
    printf( "%4d x%4d x%4d -> %4d x%4d x%4d \n", w, h, c, l.out_w, l.out_h, l.out_c);
    return l;
}
convolutional_layer parse_convolutional(list *options,size_params params)
{
    int n = option_find_int(options, (char*)"filters",1);
    int size = option_find_int(options, (char*)"size",1);
    int stride = -1;
    int stride_x = option_find_int_quiet(options, (char*)"stride_x", -1);
    int stride_y = option_find_int_quiet(options, (char*)"stride_y", -1);
    if (stride_x < 1 || stride_y < 1) {
        stride = option_find_int(options, (char*)"stride", 1);
        if (stride_x < 1) stride_x = stride;
        if (stride_y < 1) stride_y = stride;
    }
    else {
        stride = option_find_int_quiet(options, (char*)"stride", 1);
    }
    int pad = option_find_int_quiet(options, (char*)"pad",0);
    int padding = option_find_int_quiet(options, (char*)"padding",0);
    // if(pad) padding = size/2;
    if(pad) padding=pad;

    char *activation_s = option_find_str(options, (char*)"activation", (char*)"logistic");
    ACTIVATION activation = get_activation(activation_s);
    int batch,h,w,c;
    h = params.h;
    w = params.w;
    c = params.c;
    batch=params.batch;
    if(!(h && w && c)) error("Layer before convolutional layer must output image.");
    convolutional_layer layer = make_convolutional_layer(batch,1,h,w,c,n,size,stride_x,stride_y,padding,activation);

    return layer;
}
int *parse_yolo_mask(char *a, int *num)
{
    int *mask = 0;
    if (a) {
        int len = strlen(a);
        int n = 1;
        int i;
        for (i = 0; i < len; ++i) {
            if (a[i] == '#') break;
            if (a[i] == ',') ++n;
        }
        mask = (int*)xcalloc(n, sizeof(int));
        for (i = 0; i < n; ++i) {
            int val = atoi(a);
            mask[i] = val;
            a = strchr(a, ',') + 1;
        }
        *num = n;
    }
    return mask;
}
layer make_yolo_layer(int batch,int w,int h,int n,int total,int *mask,int classes,int max_boxes)
{
    int i;
    layer l={(LAYER_TYPE)0};
    l.type=YOLO;
    l.n=n;
    // l.total=total;
    // l.batch=batch;
    l.h=h;
    l.w=w;
    l.c=n*(classes+4+1);
    l.out_w=l.w;
    l.out_c=l.c;
    l.out_h=l.h;
    l.classes=classes;
    l.biases=(float*)xcalloc(total*2,sizeof(float));
    if(mask) l.mask=mask;
    else{
        l.mask = (int*)xcalloc(n, sizeof(int));
        for(i = 0; i < n; ++i){
            l.mask[i] = i;
        }
    }
    l.outputs = h*w*n*(classes + 4 + 1);
    l.inputs = l.outputs;
    l.output = (float*)xcalloc(l.outputs, sizeof(float));
    // for(i = 0; i < total*2; ++i){
    //     l.biases[i] = .5;
    // }
    fprintf(stderr, "yolo  \n");
    return l;
}
layer parse_yolo(list *options,size_params params)
{
    int classes=option_find_int(options,(char*)"classes",80);
    int total=option_find_int(options,(char*)"num",1);
    int num=total;

    char *a = option_find_str(options, (char*)"mask", 0);
    int *mask = parse_yolo_mask(a, &num);
    int max_boxes = option_find_int_quiet(options, (char*)"max", 200);
    layer l = make_yolo_layer(params.batch, params.w, params.h, num, total, mask, classes, max_boxes);
    if (l.outputs != params.inputs) {
        printf("Error: l.outputs == params.inputs \n");
        printf("filters= in the [convolutional]-layer doesn't correspond to classes= or mask= in [yolo]-layer \n");
        exit(EXIT_FAILURE);
    }
    a = option_find_str(options, (char*)"anchors", 0);
    if (a) {
        int len = strlen(a);
        int n = 1;
        int i;
        for (i = 0; i < len; ++i) {
            if (a[i] == '#') break;
            if (a[i] == ',') ++n;
        }
        for (i = 0; i < n && i < total*2; ++i) {
            float bias = atof(a);
            l.biases[i] = bias;
            a = strchr(a, ',') + 1;
        }
    }
    l.stride=option_find_int_quiet(options,(char*)"stride",1);
    return l;
}
maxpool_layer make_maxpool_layer(int batch, int h, int w, int c, int size, int stride,int padding)
{
    maxpool_layer l = { (LAYER_TYPE)0 };
    l.type = MAXPOOL;
    l.h = h;
    l.w = w;
    l.c = c;
    l.pad = padding/2;
    l.stride_x = stride;
    l.stride_y = stride;
    l.stride=stride;

    l.out_w = (w + padding - size) / l.stride_x + 1;
    l.out_h = (h + padding - size) / l.stride_y + 1;
    l.out_c = c;

    l.outputs = l.out_h * l.out_w * l.out_c;
    l.inputs = h*w*c;
    l.size = size;

    int output_size = l.out_h * l.out_w * l.out_c * batch;
    printf( "max          %d x %d / %d  %4d x%4d x%4d   ->  %4d x%4d x%4d\n", size, size, stride, w, h, c, l.out_w, l.out_h, l.out_c);

    return l;
}
maxpool_layer parse_maxpool(list *options, size_params params)
{
    int stride = option_find_int(options, (char*)"stride",1);
    // int stride_x = option_find_int_quiet(options, "stride_x", stride);
    // int stride_y = option_find_int_quiet(options, "stride_y", stride);
    int size = option_find_int(options, (char*)"size",stride);
    int padding = option_find_int_quiet(options, (char*)"padding", size);
    // int maxpool_depth = option_find_int_quiet(options, "maxpool_depth", 0);
    // int out_channels = option_find_int_quiet(options, "out_channels", 1);
    // int antialiasing = option_find_int_quiet(options, "antialiasing", 0);
    // const int avgpool = 0;

    int batch,h,w,c;
    h = params.h;
    w = params.w;
    c = params.c;
    batch=params.batch;
    // if(!(h && w && c)) error("Layer before [maxpool] layer must output image.", DARKNET_LOC);

    maxpool_layer layer = make_maxpool_layer(batch, h, w, c, size, stride,padding);
    // layer.maxpool_zero_nonmax = option_find_int_quiet(options, "maxpool_zero_nonmax", 0);
    return layer;
}
layer make_route_layer(int batch,int n,int *layers,int *input_sizes)
{
    printf("route");
    layer l={(LAYER_TYPE)0};
    l.type=ROUTE;
    // l.batch=batch;
    l.n=n;
    l.input_layers=layers;
    l.input_sizes=input_sizes;
    int i=0;
    int outputs=0;
    for(i=0;i<n;i++){
        printf(" %d",layers[i]);
        outputs+=input_sizes[i];
    }
    l.outputs=outputs;
    l.inputs=outputs;
    // l.output=(float*)xcalloc(outputs,sizeof(float));
    return l;

}
layer parse_route(list *options,size_params params)
{
    char *l=option_find(options,(char*)"layers");
    if(!l) error("Route Layer must specify input layers\n");
    int len=strlen(l);
    int n=1;
    int i;
    for(i=0;i<len;i++){
        if(l[i]==',') ++n;
    }

    int *layers = (int*)xcalloc(n,sizeof(int));
    int *sizes = (int*)xcalloc(n,sizeof(int));
    for(i=0;i<n;i++){
        int index=atoi(l);
        l=strchr(l,',')+1;
        if(index<0) index=params.index+index;
        layers[i]=index;
        sizes[i]=params.net.layers[index].outputs;
    }
    int batch=params.batch;
    layer lay=make_route_layer(batch,n,layers,sizes);

    layer first=params.net.layers[layers[0]];
    lay.out_c=first.out_c;
    lay.out_h=first.out_h;
    lay.out_w=first.out_w;

    for(i=1;i<n;i++){
        int index=layers[i];
        layer next=params.net.layers[index];
        if(next.out_w==first.out_w&&next.out_h==first.out_h){
            lay.out_c+=next.out_c;
        }else{
            fprintf(stderr, " The width and height of the input layers are different. \n");
            lay.out_h = lay.out_w = lay.out_c = 0;
        }
    }
    lay.w=first.out_w;
    lay.h=first.out_h;
    lay.c=first.out_c;
    if (n > 3) printf( " \t    ");
    else if (n > 1) printf( " \t            ");
    else printf( " \t\t            ");

    printf( "    %4d x%4d x%4d ",lay.h,lay.w,lay.c);
    printf( " -> %4d x%4d x%4d \n", lay.out_w, lay.out_h, lay.out_c);

    return lay;
}
layer make_upsample_layer(int batch,int w,int h,int c,int stride)
{
    layer l={(LAYER_TYPE)0};
    l.type=UPSAMPLE;
    l.w=w;
    l.h=h;
    l.c=c;
    l.out_w=w*stride;
    l.out_h=h*stride;
    l.out_c=c;
    l.stride=stride;
    l.outputs=l.out_w*l.out_c*l.out_h;
    l.inputs=l.c*l.w*l.h;
    // l.output=(float*)xcalloc(l.outputs,sizeof(float));
    printf("upsample               %2dx   %4d x%4d x%4d -> %4d x%4d x%4d\n", stride, w, h, c, l.out_w, l.out_h, l.out_c);
    return l;
}
layer parse_upsample(list *options, size_params params, network net)
{

    int stride = option_find_int(options, (char*)"stride", 2);
    layer l = make_upsample_layer(params.batch, params.w, params.h, params.c, stride);
    // l.scale = option_find_float_quiet(options, (char*)"scale", 1);
    return l;
}
layer make_shortcut_layer(int batch,int n,int *input_layers,int *input_sizes,int w,int h,int c,float **layers_output)
{
    printf( "Shortcut ");
    int i;
    for(i = 0; i < n; ++i) printf( "%d, ", input_layers[i]);
    layer l = { (LAYER_TYPE)0 };
    // l.train = train;
    l.type = SHORTCUT;
    // l.batch = batch;
    l.n = n;
    l.input_layers = input_layers;
    // l.input_sizes = input_sizes;
    l.layers_output = layers_output;
    l.w = l.out_w = w;
    l.h = l.out_h = h;
    l.c = l.out_c = c;
    l.outputs = w*h*c;
    l.inputs = l.outputs;

    l.index = l.input_layers[0];

    // l.output = (float*)xcalloc(l.outputs * batch, sizeof(float));
    printf( "                           outputs:-> %4d x%4d x%4d \n", l.out_w, l.out_h, l.out_c);
    return l;
}
layer parse_shortcut(list *options,size_params params,network net)
{
    char *l = option_find(options, (char*)"from");
    int len = strlen(l);
    if (!l) error("Route Layer must specify input layers: from = ...");
    int n = 1;
    int i;
    for (i = 0; i < len; ++i) {
        if (l[i] == ',') ++n;
    }
    int* layers = (int*)calloc(n, sizeof(int));
    int* sizes = (int*)calloc(n, sizeof(int));
    float **layers_output = (float **)calloc(n, sizeof(float *));

    for (i = 0; i < n; ++i) {
        int index = atoi(l);
        l = strchr(l, ',') + 1;
        if (index < 0) index = params.index + index;
        layers[i] = index;
        sizes[i] = params.net.layers[index].outputs;
        layers_output[i] = params.net.layers[index].output;
        // layers_delta[i] = params.net.layers[index].delta;
    }

    layer s = make_shortcut_layer(params.batch, n, layers, sizes, params.w, params.h, params.c, layers_output);

    for (i = 0; i < n; ++i) {
        int index = layers[i];
        assert(params.w == net.layers[index].out_w && params.h == net.layers[index].out_h);

        if (params.w != net.layers[index].out_w || params.h != net.layers[index].out_h || params.c != net.layers[index].out_c)
            printf( " (%4d x%4d x%4d) + (%4d x%4d x%4d) \n",
                    params.w, params.h, params.c, net.layers[index].out_w, net.layers[index].out_h, params.net.layers[index].out_c);
    }

    return s;
}
network parse_network_cfg_custom(const char* cfg, int h, int w)
{
    list *sections = read_cfg(cfg);
    node *n = sections->front;
    if(!n) error("Config file has no sections");
    network net = make_network(sections->size - 1);
    // net.gpu_index = gpu_index;
    size_params params;
    section *s = (section *)n->val;
    list *options = s->options;
    if(!is_network(s)) error("First section must be [net] or [network]");
    parse_net_options(options, &net,h,w);
    params.h = net.h;
    params.w = net.w;
    params.c = net.c;
    params.inputs = net.inputs;
    if (net.batch < 1) net.batch = 1;
    params.batch = net.batch;
    params.net = net;

    n = n->next;
    int count = 0;
    free_section(s);

    printf( "   layer   filters  size/strd(dil)      input                output\n");
    while(n){
        params.index = count;
        printf( "%4d ", count);
        s = (section *)n->val;
        options = s->options;
        layer l = { (LAYER_TYPE)0 };
        LAYER_TYPE lt = string_to_layer_type(s->type);
        if(lt == CONVOLUTIONAL){
            l = parse_convolutional(options, params);
        }else if (lt == YOLO) {
            l = parse_yolo(options, params);
        }else if(lt == MAXPOOL){
            l = parse_maxpool(options, params);
        }else if(lt == ROUTE||lt==CONCAT){
            l = parse_route(options, params);
            // int k;
            // for (k = 0; k < l.n; ++k) {
            //     net.layers[l.input_layers[k]].use_bin_output = 0;
            //     if (count >= last_stop_backward)
            //         net.layers[l.input_layers[k]].keep_delta_gpu = 1;
            // }
        }else if (lt == UPSAMPLE) {
            l = parse_upsample(options, params, net);
        }else if (lt == SPP) {
            // l = parse_spp(options, params);
            ;
        }else if(lt == SHORTCUT||lt==Add){
            l = parse_shortcut(options, params, net);
            // net.layers[count - 1].use_bin_output = 0;
            // net.layers[l.index].use_bin_output = 0;
            // if (count >= last_stop_backward)
            //     net.layers[l.index].keep_delta_gpu = 1;
        }else if (lt == EMPTY) {
            layer empty_layer = {(LAYER_TYPE)0};
            l = empty_layer;
            l.type = EMPTY;
            l.w = l.out_w = params.w;
            l.h = l.out_h = params.h;
            l.c = l.out_c = params.c;
            // l.batch = params.batch;
            l.inputs = l.outputs = params.inputs;
            l.output = net.layers[count - 1].output;
            // l.delta = net.layers[count - 1].delta;
            printf( "empty \n");
        }
        net.layers[count] = l;
        free_section(s);
        n = n->next;
        ++count;
        // // 1 7 2 10 22 11 25 37 26 43 49 44 53 39 54 60 55 64 24 65 71 66 74 63 75 81 76 84 52 85 91 86 73 83 93
        params.h = l.out_h;
        params.w = l.out_w;
        params.c = l.out_c;
        params.inputs = l.outputs;

    }

    free_list(sections);
    // net.outputs=get_network_output_size(net);
    // net.output=get_network_output(net);
    return net;
}
void parse_network_cfg(network *net, const char* cfg, int h, int w)
{
    *net=parse_network_cfg_custom(cfg, h, w);
    printf("=====================\n");
}

uint32_t get_file_size(char* filename)
{
    struct stat st{};
    if(stat(filename, &st) < 0) {
        return 0;
    }
    return st.st_size;
}
template <typename T>
void load_bins(const std::string &filename, const size_t &file_size, T *data) {
  FILE *fdata = fopen(filename.c_str(), "rb");
  if (!fdata) {
    error("open file failed\n");
  }
  int n = fread(data, sizeof(T), file_size / (sizeof(T)), fdata);
  if (n <= 0) {
    error("load data failed\n");
  }
  fclose(fdata);
}
void load_bin_file(const std::string &filename, const size_t & file_size, float* data)
{
    FILE* fdata = fopen(filename.c_str(), "rb");
    if(!fdata) {error("open file failed\n");}
    int n = fread(data, sizeof(float), file_size/(sizeof(float)), fdata);
    if (n <=0) {error("load data failed\n");}
    fclose(fdata);
}

float* nms(float *res,int* num,int net_num)
{
    int max_nms=300;
    int max_wh=4096;
    float conf_thresh=0.15;
    float iou_thresh=0.1;
    int nc=80+4+1;
   //  int input_index_num=255*(76*76+38*38+19*19)/nc;
   int input_index_num=net_num/nc;

    //choose the conf>0.25 then save the inedx into the array
    int count=0;
    int i,j;
    for(i=0;i<input_index_num;i++){
        if(res[i*nc+4]>conf_thresh){
            count++;
        }
    }

    //create the array to save index that conf>0.25
    // int result0[count];
    int *result0=(int*)malloc(sizeof(int)*count);
    count=0;
    for(i=0;i<input_index_num;i++){
        if(res[i*nc+4]>conf_thresh){
            result0[count++]=i;
        }
    }
    //process the class prob and change box value from xywh to xyxy
    int index=0;
    for(i=0;i<count;i++){
        index=result0[i];
        float tmp_conf=res[index*nc+4];
        for(j=5;j<nc;j++){
            res[index*nc+j]*=tmp_conf;
        }
    }

    //int max_cls_index[count];//the max class prob index
    //int sat_index[count];//new_conf>0.25 line index(index of result0)
    int *max_cls_index=(int*)malloc(sizeof(int)*count);
    int *sat_index=(int*)malloc(sizeof(int)*count);
    int cnt=0;//the num of second filted results
    for(i=0;i<count;i++){
        index=result0[i];
        float maxx=0;
        int indexx=-1;
        for(j=5;j<nc;j++){
            if(maxx<res[index*nc+j]){
                maxx=res[index*nc+j];
                indexx=j;
            }
        }
        if(maxx>conf_thresh){
            sat_index[cnt]=index;
            max_cls_index[cnt]=indexx;
            cnt++;
        }
    }
    free(result0);
    //recreate the matrix to save the results(bbox,conf,cls)
    float *res1=(float*)malloc(sizeof(float)*cnt*6);
    for(i=0;i<cnt;i++){
        index=sat_index[i];
        res1[i*6]=res[index*nc]-res[index*nc+2]/2;//x1  left top
        res1[i*6+1]=res[index*nc+1]-res[index*nc+3]/2;//y1 left top
        res1[i*6+2]=res[index*nc]+res[index*nc+2]/2;
        res1[i*6+3]=res[index*nc+1]+res[index*nc+3]/2;
        res1[i*6+4]=res[index*nc+max_cls_index[i]];//cls_index prob
        res1[i*6+5]=max_cls_index[i]-5;
    }
    free(res);
    free(max_cls_index);
    free(sat_index);
    //nms process -->iou process
    // float x1[cnt];
    // float x2[cnt];
    // float y1[cnt];
    // float y2[cnt];
    // float scores[cnt];
    // float areas[cnt];
    float *x1=(float*)malloc(sizeof(float)*cnt);
    float *x2=(float*)malloc(sizeof(float)*cnt);
    float *y1=(float*)malloc(sizeof(float)*cnt);
    float *y2=(float*)malloc(sizeof(float)*cnt);
    float *scores=(float*)malloc(sizeof(float)*cnt);
    float *areas=(float*)malloc(sizeof(float)*cnt);
    for(i=0;i<cnt;i++){
        int c=res1[i*6+5]*max_wh;
        x1[i]=res1[i*6]+c;
        y1[i]=res1[i*6+1]+c;
        x2[i]=res1[i*6+2]+c;
        y2[i]=res1[i*6+3]+c;
        scores[i]=res1[i*6+4];
        //cal areas
        areas[i]=(x2[i]-x1[i])*(y2[i]-y1[i]);
    }

    //sort by prob only get the order of index
    // int order[cnt];
    int *order=(int*)malloc(sizeof(int)*cnt);
    for(int i=0;i<cnt;i++){
        order[i]=i;
    }
    for(i=0;i<cnt;i++){
        for(j=cnt-1;j>i;j--){
            index=order[j];
            if(res1[index*6+4]>res1[(order[j-1])*6+4]){
                order[j]=order[j-1];
                order[j-1]=index;
            }
        }
    }
   //  std::cout<<"cnt:"<<cnt<<std::endl;

    //test sort result
   //  for(i=0;i<cnt;i++){
   //      // index=order[i];
   //      // std::cout<<"i:"<<i<<"\t"<<res1[index*6+4]<<std::endl;
   //      std::cout<<i<<"\t"<<x1[i]<<"\t"<<y1[i]<<"\t"
   //              <<x2[i]<<"\t"<<y2[i]<<"\t"
   //              <<areas[i]<<std::endl;
   //  }
    //iou process
    // int supressed[cnt];
    // int keep[cnt];
    int *supressed=(int*)malloc(sizeof(int)*cnt);
    int *keep=(int*)malloc(sizeof(int)*cnt);
    int n=0;//num to keep
    for(i=0;i<cnt;i++){
        index=order[i];
        if(supressed[index]==1){
            continue;
        }
        keep[n++]=index;
        float x11=x1[index];
        float x21=x2[index];
        float y11=y1[index];
        float y21=y2[index];
        float area=areas[index];
        for(j=i+1;j<cnt;j++){
            int index_j=order[j];
            if(supressed[index_j]==1){
                continue;
            }
            // float x12=(x11>x1[index_j])?x11:x1[index_j];
            // float x22=(x21<x2[index_j])?x21:x2[index_j];
            // float y12=(y11>y1[index_j])?y11:y1[index_j];
            // float y22=(y21<y2[index_j])?y21:y2[index_j];
            // float w=(x22-x12>0)?(x22-x12):(x12-x22);
            // float h=(y22-y12>0)?(y22-y12):(y12-y22);
            // float w=(x22-x12>0)?(x22-x12):0;
            // float h=(y22-y12>0)?(y22-y12):0;

            float x12=MAX(x11,x1[index_j]);
            float x22=MIN(x21,x2[index_j]);
            float y12=MAX(y11,y1[index_j]);
            float y22=MIN(y21,y2[index_j]);

            float w=MAX(0,x22-x12);
            float h=MAX(0,y22-y12);

            float inter=w*h;
            float ovr=inter/(area+areas[index_j]-inter);
            if(ovr>iou_thresh){
                supressed[index_j]=1;
            }
        }
    }
   //  std::cout<<"n:"<<n<<std::endl;
    *(num)=n;
    float *nms_res=(float*)malloc(sizeof(float)*n*6);
    for(i=0;i<n;i++){
        index=keep[i];
        nms_res[i*6]=res1[index*6];
        nms_res[i*6+1]=res1[index*6+1];
        nms_res[i*6+2]=res1[index*6+2];
        nms_res[i*6+3]=res1[index*6+3];
        nms_res[i*6+4]=res1[index*6+4];
        nms_res[i*6+5]=res1[index*6+5];
    }
    free(res1);
    free(x1);
    free(x2);
    free(y1);
    free(y2);
    free(scores);
    free(areas);
    free(order);
    free(supressed);
    free(keep);
    return nms_res;
    // return res1;
}

void scale_coords(int org_w,int org_h,int new_w,int new_h,float* res,int num)
{
    float gain=(((float)new_w)/org_w<((float)new_h)/org_h)?(((float)new_w)/org_w):((float)new_h)/org_w;
    
    int pad_w=(new_w-org_w*gain)/2;
    int pad_h=(new_h-org_h*gain)/2;

    int i;
    for(i=0;i<num;i++){
        res[i*6]-=pad_w;
        res[i*6+2]-=pad_w;
        res[i*6+1]-=pad_h;
        res[i*6+3]-=pad_h;

        res[i*6]/=gain;
        res[i*6+2]/=gain;
        res[i*6+1]/=gain;
        res[i*6+3]/=gain;

        if(res[i*6]<0){res[i*6]=0;}
        if(res[i*6]>org_w){res[i*6]=org_w;}
        if(res[i*6+1]<0){res[i*6+1]=0;}
        if(res[i*6+1]>org_h){res[i*6+1]=org_h;}
        if(res[i*6+2]<0){res[i*6+2]=0;}
        if(res[i*6+2]>org_w){res[i*6+2]=org_w;}
        if(res[i*6+3]<0){res[i*6+3]=0;}
        if(res[i*6+3]>org_h){res[i*6+3]=org_h;}
    }
}
char* get_cls(int cls_index,char **names)
{
    char* cls=(char*)names[cls_index];
    // switch(cls_index){
    //     case 0:{
    //         cls=(char*)"person";
    //         break;
    //     }
    //     case 33:{
    //         cls=(char*)"kite";
    //         break;
    //     }  
    // }
    return cls;
}
float get_color(int c, int x, int max)
{
    float ratio = ((float)x/max)*5;
    int i = floor(ratio);
    int j = ceil(ratio);
    ratio -= i;
    float r = (1-ratio) * colors[i][c] + ratio*colors[j][c];
    //printf("%f\n", r);
    return r;
}
void draw_box(image a, int x1, int y1, int x2, int y2, float r, float g, float b)
{
    //normalize_image(a);
    int i;
    if(x1 < 0) x1 = 0;
    if(x1 >= a.w) x1 = a.w-1;
    if(x2 < 0) x2 = 0;
    if(x2 >= a.w) x2 = a.w-1;

    if(y1 < 0) y1 = 0;
    if(y1 >= a.h) y1 = a.h-1;
    if(y2 < 0) y2 = 0;
    if(y2 >= a.h) y2 = a.h-1;

    for(i = x1; i <= x2; ++i){
        a.data[i + y1*a.w + 0*a.w*a.h] = r;
        a.data[i + y2*a.w + 0*a.w*a.h] = r;

        a.data[i + y1*a.w + 1*a.w*a.h] = g;
        a.data[i + y2*a.w + 1*a.w*a.h] = g;

        a.data[i + y1*a.w + 2*a.w*a.h] = b;
        a.data[i + y2*a.w + 2*a.w*a.h] = b;
    }
    for(i = y1; i <= y2; ++i){
        a.data[x1 + i*a.w + 0*a.w*a.h] = r;
        a.data[x2 + i*a.w + 0*a.w*a.h] = r;

        a.data[x1 + i*a.w + 1*a.w*a.h] = g;
        a.data[x2 + i*a.w + 1*a.w*a.h] = g;

        a.data[x1 + i*a.w + 2*a.w*a.h] = b;
        a.data[x2 + i*a.w + 2*a.w*a.h] = b;
    }
}
void draw_box_width(image a, int x1, int y1, int x2, int y2, int w, float r, float g, float b)
{
    int i;
    for(i = 0; i < w; ++i){
        draw_box(a, x1+i, y1+i, x2-i, y2-i, r, g, b);
    }
}
image get_label_new(image **characters, char *string, int size)
{
    size = size/10;
    if(size > 7) size = 7;
    image label = make_empty_image(0,0,0);
    while(*string){
        image l = characters[size][(int)*string];
        image n = tile_images(label, l, -size - 1 + (size+1)/2);
        free_image(label);
        label = n;
        ++string;
    }
    image b = border_image(label, label.h*.05);
    free_image(label);
    return b;
}
void draw_weighted_label(image a,int r,int c,image label,const float *rgb,const float alpha)
{
    int w=label.w;
    int h=label.h;
    if(r-h>0)   r=r-h;

    int i,j,k;
    for(j=0;j<h&&j+r<a.h;j++){
        for(i=0;i<w&&i+c<a.w;++i){
            for(k=0;k<label.c;++k){
                float val1=get_pixel(label,i,j,k);
                float val2=get_pixel(a,i+c,j+r,k);
                float val_dst=val1*rgb[k]*alpha+val2*(1-alpha);
                set_pixel(a,i+c,j+r,k,val_dst);
            }
        }
    }
}
void draw_detections(image img,float *res,int n,image** alphabet,char** names,int classes)
{
    int i;
    fprintf(stderr,"Found %2d objections!\n",n);
    for(i=0;i<n;i++){
        int cls_index=res[i*6+5];
        float prob=res[i*6+4];
        char* cls=get_cls(cls_index,names);
        fprintf(stderr,"%s:%3.2f\n",cls,prob);

        int offset=cls_index*123457%classes;
        float red=get_color(2,offset,classes);
        float green=get_color(1,offset,classes);
        float blue=get_color(0,offset,classes);
        float rgb[3];

        rgb[0]=red;
        rgb[1]=green;
        rgb[2]=blue;

        draw_box_width(img,res[i*6],res[i*6+1],res[i*6+2],res[i*6+3],1,red,green,blue);
        if(alphabet){
            char label_str[4096]={0};
            strcat(label_str,names[(int)(res[i*6+5])]);
            char prob_str[10];
            sprintf(prob_str,":%.2f",res[i*6+4]);
            strcat(label_str,prob_str);
            // int j;
            // for(j=0;j<classes;j++){
            //     if(j==int(res[i*6+5])){
            //         strcat(label_str,",");
            //         strcat(label_str,names[j]);
            //     }
            // }

            image label=get_label_new(alphabet,label_str,img.h*0.02);
            draw_weighted_label(img,(int)(res[i*6+1])+1,(int)(res[i*6]),label,rgb,0.7);
            free_image(label);
        }
    }
    //draw bbox to image

}