# 
# Usage: To re-create this platform project launch xsct with below options.
# xsct /home/y/works/sdk/test_int16/zc702/platform.tcl
# 
# OR launch xsct and run below command.
# source /home/y/works/sdk/test_int16/zc702/platform.tcl
# 
# To create the platform in a different location, modify the -out option of "platform create" command.
# -out option specifies the output directory of the platform project.

platform create -name {zc702}\
-hw {/home/y/xilinx/Vitis/2020.2/data/embeddedsw/lib/fixed_hwplatforms/zc702.xsa}\
-fsbl-target {psu_cortexa53_0} -out {/home/y/works/sdk/test_int16}

platform write
domain create -name {standalone_ps7_cortexa9_0} -display-name {standalone_ps7_cortexa9_0} -os {standalone} -proc {ps7_cortexa9_0} -runtime {cpp} -arch {32-bit} -support-app {hello_world}
platform generate -domains 
platform active {zc702}
domain active {zynq_fsbl}
domain active {standalone_ps7_cortexa9_0}
platform generate -quick
platform generate
