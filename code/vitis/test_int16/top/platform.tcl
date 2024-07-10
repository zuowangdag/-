# 
# Usage: To re-create this platform project launch xsct with below options.
# xsct /home/y/works/sdk/test_int16/top/platform.tcl
# 
# OR launch xsct and run below command.
# source /home/y/works/sdk/test_int16/top/platform.tcl
# 
# To create the platform in a different location, modify the -out option of "platform create" command.
# -out option specifies the output directory of the platform project.

platform create -name {top}\
-hw {/home/y/works/vivado/project_1_int16_pp/top_wrapper.xsa}\
-fsbl-target {psu_cortexa53_0} -out {/home/y/works/sdk/test_int16}

platform write
domain create -name {linux_ps7_cortexa9} -display-name {linux_ps7_cortexa9} -os {linux} -proc {ps7_cortexa9} -runtime {cpp} -arch {32-bit} -support-app {empty_application}
platform active {top}
domain active {zynq_fsbl}
domain active {linux_ps7_cortexa9}
platform generate -quick
platform generate
domain config -bif {}
domain config -boot {}
domain config -image {}
platform write
