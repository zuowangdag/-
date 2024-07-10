project(int_new)
cmake_minimum_required(VERSION 3.10)
include_directories(/home/y/xilinx/Vitis_HLS/2020.2/include)
# aux_source_directory(./*.cpp srcs)
add_executable(detct acc_quan.cpp acc_quan.h
                            ps.cpp ps.h
                            utils.cpp utils.h
                            stb_image_write.h stb_image.h
                            yo_struct.h main.cpp)