# SandStorm

The goal of this project is to create a way to utilize (userland) Sandbox checks
into offensive workflow in a flexible, robust and opsec safe manner. 
Mainly, to address the decision making process of payload detonation in
destination environment.

## Initial Concepts
TBD . Userland only for now. 

## Initial work
It is loosely initially based on Pafish (https://github.com/a0rtega/pafish). 
This project has a decent set of the initial sandbox check set. 
Unfortunately, the design and API interface, as well as the absence of opsec features 
makes it somewhat limiting to the red teams in its current form.
Sandstorm will attempt to improve on that.

From Pafish it gains the following checks:

## Desired features

[X]  - Already implemented.

- [X] Decouple checks from Pafish monolithic program into a native (C99) DLL.
- [X] Group checks into runtime modules. Be able to run groups of checks indepenently.
  For example, run only VMWare and Bochs.
- [X] Within groups of checks, introduce granular delays between tasks to be able to counter
behavioral analytics of sandboxes and attempt to programmatically stall execution.
This is and ongoing effort with 2 types of delays (Time and Compute) initially
implemented (XOR and Sleep) both with per-task iteration delay.
- [X] Fully expose relevant checks to P/INvoke to be able to drive the SandStorm from
managed code.
- [X] Remove File Logging and Console notifications from tasks. The API should be fully clean 
of any interation other than API. 
- [X] Create per-check callback framework to check conditions for a check run (both contextual and opsec)
- [X] Written sample program (`Driver.c`) to showcase the checks. Created and exposed client headers 
to facilitate other native client implementation.

## TODO
- Introduce Opsec warnings to alert Operator of unsafe operations/checks.
- Introduce conditional build 
- Obfuscation.
- The library does not communciate out. Need to decide if a fully functional
stage 0 needs ro be built or the library is used only from another driver whcih 
collects sandbox check data and ships them to the base. Both may be needed.
- Add native EDR and AV Checks to the list of features.
- Scoring system (ML maybe).
- !!! finding other lists of sandbox/ EDR checks. !!!
- Decide to support MSVC. Currently the project take from pafish by using Mingw64 nd MSYS2 on windows
- Migrate Makefiles to CMake (also Pafish remnant).
 
## USAGE

See `Driver.c`

Sample rune:

```$xslt
Driver.exe
[X] GETTING CONTEXT [X]
[X] RUNNING GROUP CHECKS [X]
-- Group: Debuggers --
-- Group: CPU --
-- Group: Generic Sandbox --
-- Group: Hooks --
-- Group: Sandboxie --
-- Group: VBox --
-- Group: VMware --
-- Group: Quemu --
-- Group: Bochs --
-- Group: Cuckoo --


[X] PRINTING GROUP CHECKS RESULTS [X]
Disposition:
[*] Windows version: 10.0 build 18362
[*] CPU: GenuineIntel
    Hypervisor: VMwareVMware
    CPU brand: Intel(R) Core(TM) i7-4578U CPU @ 3.00GHz
CPU: GenuineIntel (HV: VMwareVMware) Intel(R) Core(TM) i7-4578U CPU @ 3.00GHz
IsDebuggerPresent(): 0
OutputDebugString(): 0 Guard check did not pass
hi_CPU_VM_rdtsc: 0
hi_CPU_VM_rdtsc_force_vm_exit: 1
hi_CPU_VM_hypervisor_bit: 1
hi_CPU_VM_hv_vendor_name: 1
hi_sandbox_mouse_act: 0
hi_sandbox_username: 0
hi_sandbox_path: 0
hi_sandbox_common_names: 0
hi_sandbox_drive_size: 0
hi_sandbox_drive_size2: 0
hi_sandbox_sleep_gettickcount: 0
hi_sandbox_NumberOfProcessors_less_2_raw: 0
hi_sandbox_NumberOfProcessors_less_2_GetSystemInfo: 0
hi_sandbox_pysicalmemory_less_1Gb: 0
hi_sandbox_uptime: 0
hi_sandbox_IsNativeVhdBoot: 0
hi_hooks_shellexecuteexw_m1: 1
hi_hooks_createprocessa_m1: 1
hi_sandboxie: 0
hi_wine: 0
hi_virtualbox1: 0
hi_virtualbox2: 0
hi_virtualbox3: 0
hi_virtualbox4: 0
hi_virtualbox5: 0
hi_virtualbox7: 0
hi_virtualbox8: 0
hi_virtualbox9: 0
hi_virtualbox10: 0
hi_virtualbox_sysf1: 0
hi_virtualbox_sysf2: 0
hi_virtualbox_mac: 0
hi_virtualbox14: 0
hi_virtualbox15: 0
hi_virtualbox_net_shares: 0
hi_virtualbox_proc: 0
hi_virtualbox_wmi_dev: 0
hi_vmware1: 1
hi_vmware2: 1
hi_vmware_sysf1: 1
hi_vmware_sysf2: 1
hi_vmware_mac: 1
hi_vmware_ser: 1
hi_vmware_adapter: 0
hi_vmware_dev: 1
hi_qemu1: 0
hi_qemu2: 0
hi_qemu_cpu: 0
hi_bochs1: 0
hi_bochs_amd: 0
hi_bochs_intel: 0
hi_cuckoo_tls: 0

```
## API 

see `pfdriver.h`:

```c
__declspec(dllexport) void __cdecl checkGroupDebuggers(struct execCheckState * eState, DelayType dType, int tMin, int tMax, int iter);
__declspec(dllexport) void __cdecl checkGroupCPU(struct execCheckState * eState, DelayType dType, int tMin, int tMax, int iter);
__declspec(dllexport) void __cdecl checkGroupGenericSandbox(struct execCheckState * eState, DelayType dType, int tMin, int tMax, int iter);
__declspec(dllexport) void __cdecl checkGroupHooks(struct execCheckState * eState, DelayType dType, int tMin, int tMax, int iter);
__declspec(dllexport) void __cdecl checkGroupSandboxie(struct execCheckState * eState, DelayType dType, int tMin, int tMax, int iter);
__declspec(dllexport) void __cdecl checkGroupVBox(struct execCheckState * eState, DelayType dType, int tMin, int tMax, int iter);
__declspec(dllexport) void __cdecl checkGroupVMware(struct execCheckState * eState, DelayType dType, int tMin, int tMax, int iter);
__declspec(dllexport) void __cdecl checkGroupQuemu(struct execCheckState * eState, DelayType dType, int tMin, int tMax, int iter);
__declspec(dllexport) void __cdecl checkGroupBochs(struct execCheckState * eState, DelayType dType, int tMin, int tMax, int iter);
__declspec(dllexport) void __cdecl checkGroupCu(struct execCheckState * eState, DelayType dType, int tMin, int tMax, int iter);
__declspec(dllexport) void __cdecl getContextType(struct contextType * conType);
```


