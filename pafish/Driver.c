//
// Created by dimas on 2/29/2020.
//

#include  <windows.h>
#include  <stdio.h>
#include  "pfdriver.h"

void dumpCheck(execCheckState * eState, int nMembers){

    for (int i = 0; i < nMembers; i++){
        printf("%s: %d %s\n", eState[i].text, eState[i].status, eState[i].statusMsg);
    }
}
void dumpContext(contextType * conType){

    printf("[*] Windows version: %s\n", conType->winverstr);
    printf("[*] CPU: %s\n", conType->cpu_vendor);
    if (strlen(conType->cpu_hv_vendor))
        printf("    Hypervisor: %s\n", conType->cpu_hv_vendor);
    printf("    CPU brand: %s\n", conType->cpu_brand);
    printf("%s\n", conType->aux);
}
int main() {

    struct execCheckState eStateDebuggers[N_GP_DEBUGGERS] = {{0}}, *eStateDebuggersPtr=NULL;
    struct execCheckState eStateCPU[N_GP_CPU] = {{0}}, *eStateCPUPtr=NULL;
    struct execCheckState eStateGenSandbox[N_GP_GEN_SANDBOX] = {{0}}, *eStateGenSandboxPtr=NULL;
    struct execCheckState eStateHooks[N_GP_HOOKS]  = {{0}}, *eStateHooksPtr=NULL;
    struct execCheckState eStateSandboxie[N_GP_HOOKS] = {{0}}, *eStateSandboxiePtr=NULL;
    struct execCheckState eStateVBox[N_GP_VBOX] = {{0}}, *eStateVBoxPtr=NULL;
    struct execCheckState eStateVMWare[N_GP_VMWARE] = {{0}}, *eStateVMwarePtr=NULL;
    struct execCheckState eStateQuemu[N_GP_QUEMU] = {{0}}, *eStateQuemuPtr=NULL;
    struct execCheckState eStateBochs[N_GP_BOCHS] = {{0}}, *eStateBochsPtr=NULL;
    struct execCheckState eStateCu[N_GP_CU] = {{0}}, *eStateCuPtr=NULL;
    struct contextType conType;

    eStateDebuggersPtr = eStateDebuggers;
    eStateCPUPtr = eStateCPU;
    eStateGenSandboxPtr = eStateGenSandbox;
    eStateHooksPtr = eStateHooks;
    eStateSandboxiePtr = eStateSandboxie;
    eStateVBoxPtr = eStateVBox;
    eStateVMwarePtr = eStateVMWare;
    eStateQuemuPtr = eStateQuemu;
    eStateBochsPtr = eStateBochs;
    eStateCuPtr = eStateCu;


    HMODULE hModule = LoadLibrary(TEXT("libpufferfish.dll"));

    if (hModule == NULL){
       printf("Error finding or loading the check DLL");
       exit(2);
    }
    getContextType_Ptr getContextType  =
            (getContextType_Ptr) GetProcAddress(hModule, "getContextType");

    checkGroupDebuggers_Ptr checkDebuggers  =
            (checkGroupDebuggers_Ptr) GetProcAddress(hModule, "checkGroupDebuggers");
    checkGroupCPU_Ptr checkCPU =
            (checkGroupCPU_Ptr) GetProcAddress(hModule, "checkGroupCPU");
    checkGroupGenericSandbox_Ptr checkGenSandbox =
            (checkGroupGenericSandbox_Ptr) GetProcAddress(hModule, "checkGroupGenericSandbox");
    checkGroupHooks_Ptr checkHooks =
            (checkGroupHooks_Ptr) GetProcAddress(hModule, "checkGroupHooks");
    checkGroupSandboxie_Ptr checkSandboxie  =
            (checkGroupSandboxie_Ptr) GetProcAddress(hModule, "checkGroupSandboxie");
    checkGroupVBox_Ptr checkVBox  =
            (checkGroupVBox_Ptr) GetProcAddress(hModule, "checkGroupVBox");
    checkGroupVMware_Ptr checkVMware  =
            (checkGroupVMware_Ptr) GetProcAddress(hModule, "checkGroupVMware");
    checkGroupQuemu_Ptr checkQuemu =
            (checkGroupQuemu_Ptr) GetProcAddress(hModule, "checkGroupQuemu");
    checkGroupBochs_Ptr checkBochs =
            (checkGroupBochs_Ptr) GetProcAddress(hModule, "checkGroupBochs");
    checkGroupCu_Ptr checkCu =
            (checkGroupCu_Ptr) GetProcAddress(hModule, "checkGroupCu");

    /*
     *  Run the groups
    */
    printf("[X] GETTING CONTEXT [X]\n");
    getContextType(&conType);

    printf("[X] RUNNING GROUP CHECKS [X]\n");
    printf("-- Group: Debuggers --\n");
    checkDebuggers(eStateDebuggersPtr, Time, 300, 700, 2);
    printf("-- Group: CPU --\n");
    checkCPU(eStateCPUPtr, Time, 10, 10, 1);
    printf("-- Group: Generic Sandbox --\n");
    checkGenSandbox(eStateGenSandboxPtr, Time, 50, 60, 2);
    printf("-- Group: Hooks --\n");
    checkHooks(eStateHooksPtr, Time, 50, 500, 2);
    printf("-- Group: Sandboxie --\n");
    checkSandboxie(eStateSandboxiePtr, Time, 10, 500, 4);
    printf("-- Group: VBox --\n");
    checkVBox(eStateVBoxPtr, Time, 10, 20, 2);
    printf("-- Group: VMware --\n");
    checkVMware(eStateVMwarePtr, Time, 10, 20, 2);
    printf("-- Group: Quemu --\n");
    checkQuemu(eStateQuemuPtr, Time, 10, 20, 2);
    printf("-- Group: Bochs --\n");
    checkBochs(eStateBochsPtr, Time, 10, 20, 2);
    printf("-- Group: Cuckoo --\n");
    checkCu(eStateCuPtr, Time, 100, 200, 1);


    /*
     * Dump the results
     */
    printf("\n\n[X] PRINTING GROUP CHECKS RESULTS [X]\n");
    printf("Disposition:\n");
    dumpContext(&conType);

    dumpCheck(eStateDebuggersPtr,N_GP_DEBUGGERS);
    dumpCheck(eStateCPUPtr,N_GP_CPU);
    dumpCheck(eStateGenSandboxPtr,N_GP_GEN_SANDBOX);
    dumpCheck(eStateHooksPtr,N_GP_HOOKS);
    dumpCheck(eStateSandboxiePtr,N_GP_SANDBOXIE);
    dumpCheck(eStateVBoxPtr,N_GP_VBOX);
    dumpCheck(eStateVMwarePtr,N_GP_VMWARE);
    dumpCheck(eStateQuemuPtr,N_GP_QUEMU);
    dumpCheck(eStateBochsPtr,N_GP_BOCHS);
    dumpCheck(eStateCuPtr,N_GP_CU);
    /*
     */


    FreeLibrary(hModule);
}

