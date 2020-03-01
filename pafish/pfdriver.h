//
// Created by dimas on 3/1/2020.
//

#ifndef PFDRIVER_H
#define PFDRIVER_H

typedef struct execCheckState {
    char text[256];
    unsigned int status;
    char statusMsg[256];
} execCheckState;

typedef enum  {
    Compute = 1, Time = 2
} DelayType;

#define  N_GP_DEBUGGERS 2
#define  N_GP_CPU 4
#define  N_GP_GEN_SANDBOX 12
#define  N_GP_HOOKS 2
#define  N_GP_SANDBOXIE 2
#define  N_GP_VBOX 17
#define  N_GP_VMWARE 8
#define  N_GP_QUEMU 3
#define  N_GP_BOCHS 3
#define  N_GP_CU 1

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


typedef void(__cdecl *checkGroupDebuggers_Ptr)(struct execCheckState *, int, int, int, int);
typedef int(__cdecl *checkGroupCPU_Ptr)(struct execCheckState *, int, int, int, int);
typedef int(__cdecl *checkGroupGenericSandbox_Ptr)(struct execCheckState *, int, int, int, int);
typedef int(__cdecl *checkGroupHooks_Ptr)(struct execCheckState *, int, int, int, int);
typedef int(__cdecl *checkGroupSandboxie_Ptr)(struct execCheckState *, int, int, int, int);
typedef int(__cdecl *checkGroupVBox_Ptr)(struct execCheckState *, int, int, int, int);
typedef int(__cdecl *checkGroupVMware_Ptr)(struct execCheckState *, int, int, int, int);
typedef int(__cdecl *checkGroupQuemu_Ptr)(struct execCheckState *, int, int, int, int);
typedef int(__cdecl *checkGroupBochs_Ptr)(struct execCheckState *, int, int, int, int);
typedef int(__cdecl *checkGroupCu_Ptr)(struct execCheckState *, int, int, int, int);

#endif //PFDRIVER_H
