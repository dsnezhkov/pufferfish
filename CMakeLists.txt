cmake_minimum_required(VERSION 3.15)
project(pafish)

set(CMAKE_CXX_STANDARD 14)

include_directories(pafish)

add_executable(pafish
        pafish/bochs.c
        pafish/bochs.h
        pafish/common.c
        pafish/common.h
        pafish/config.h
        pafish/cpu.c
        pafish/cpu.h
        pafish/cuckoo.c
        pafish/cuckoo.h
        pafish/debuggers.c
        pafish/debuggers.h
        pafish/gensandbox.c
        pafish/gensandbox.h
        pafish/hi_CPU_VM_hv_vendor_name
        pafish/hi_CPU_VM_hypervisor_bit
        pafish/hi_CPU_VM_rdtsc_force_vm_exit
        pafish/hi_sandbox_mouse_act
        pafish/hooks.c
        pafish/hooks.h
        pafish/chutil.c
        pafish/Makefile.linux
        pafish/Makefile.win
        pafish/qemu.c
        pafish/qemu.h
        pafish/sandboxie.c
        pafish/sandboxie.h
        pafish/types.h
        pafish/utils.c
        pafish/utils.h
        pafish/vbox.c
        pafish/vbox.h
        pafish/vmware.c
        pafish/vmware.h
        pafish/wine.c
        pafish/wine.h
        .gitignore
        README.md pafish/Driver.c pafish/pfdriver.h)
