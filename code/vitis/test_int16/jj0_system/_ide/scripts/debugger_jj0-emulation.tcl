# Usage with Vitis IDE:
# In Vitis IDE create a Single Application Debug launch configuration,
# change the debug type to 'Attach to running target' and provide this 
# tcl script in 'Execute Script' option.
# Path of this script: /home/y/works/sdk/test_int16/jj0_system/_ide/scripts/debugger_jj0-emulation.tcl
# 
# 
# Usage with xsct:
# To debug using xsct, launch xsct and run below command
# source /home/y/works/sdk/test_int16/jj0_system/_ide/scripts/debugger_jj0-emulation.tcl
# 
connect -url tcp:localhost:4354
targets 3
dow /home/y/works/sdk/test_int16/jj0/Debug/jj0.elf
targets 3
con
