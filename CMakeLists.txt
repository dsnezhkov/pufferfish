cmake_minimum_required(VERSION 3.15)
project(pufferfish)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(PAFISH ${PROJECT_SOURCE_DIR}/pafish)
include_directories(pafish)


# Objects for checks
add_library(cpu OBJECT ${PAFISH}/cpu.c )
add_library(debuggers OBJECT ${PAFISH}/debuggers.c )
add_library(gensandbox OBJECT ${PAFISH}/gensandbox.c )
add_library(hooks OBJECT ${PAFISH}/hooks.c )
add_library(sandboxie OBJECT ${PAFISH}/sandboxie.c )
add_library(vbox OBJECT ${PAFISH}/vbox.c )
add_library(vmware OBJECT ${PAFISH}/vmware.c )
add_library(wine OBJECT ${PAFISH}/wine.c )
add_library(qemu OBJECT ${PAFISH}/qemu.c )
add_library(bochs OBJECT ${PAFISH}/bochs.c )
add_library(cuckoo OBJECT ${PAFISH}/cuckoo.c )

# Shared Library
add_library(pufferfish SHARED ${PAFISH}/chutil.c ${PAFISH}/common.c ${PAFISH}/utils.c)

# Objects for checks
target_link_libraries(pufferfish PRIVATE
        cpu debuggers gensandbox hooks sandboxie vbox vmware wine qemu bochs cuckoo )

# External libs
target_link_libraries(pufferfish PRIVATE wsock32 iphlpapi mpr ole32 wbemuuid oleaut32 ws2_32 )
# Compiler flags
target_compile_options(pufferfish PRIVATE  -Wall -Wextra -Wpedantic -O0)

# Test Driver
add_executable(Driver ${PAFISH}/Driver.c)
target_compile_options(Driver PRIVATE  -Wall -Wextra -Wpedantic)

