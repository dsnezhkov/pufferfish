
/*
   Pafish (Paranoid fish)

   All code from this project, including
   functions, procedures and the main program
   is licensed under GNU/GPL version 3.

   So, if you are going to use functions or
   procedures from this project to develop
   your malware, you have to release the
   source code as well :)

   - Alberto Ortega

   Blue fish icon thanks to http://www.fasticon.com/

 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>

#include "config.h"
#include "common.h"

#include "sandboxie.h"
#include "gensandbox.h"
#include "hooks.h"
#include "vbox.h"
#include "wine.h"
#include "vmware.h"
#include "qemu.h"
#include "cpu.h"
#include "cuckoo.h"
#include "bochs.h"

#include "checkdefs.h"



/** Guard Checks **/

/* Dummy (always pass) guard as a placeholder for future checks*/
int passGuard(void){return PF_SUCCESS;}
int pass(){return PF_SUCCESS;}

int debug_outputdebugstringGuard(void){
    /* This is only working on MS Windows systems prior to Vista */
    if (winver.dwMajorVersion < 6) {
        return PF_SUCCESS;
    }
    return PF_FAILURE;
}

void exec_check_guard(struct execCheck* check){

    if ( check->call.guardCheck() == PF_SUCCESS){
        if ( exec_check_silent(check->call.callback ) == TRUE ){
            check->state.status = TRUE;
        }
    }else{
        char * message = "Guard check did not pass";
        //char * buffer = malloc(strlen(message));
        sprintf(check->state.statusMsg, "%s", message);
    }
}

// Generate random numbers in the half-closed interval
// [range_min, range_max).
// range_min <= random number < range_max
unsigned int getRangedRand( unsigned int range_min, unsigned int range_max, unsigned int n )
{
    unsigned int i = 0;
    unsigned int u = 0;
    for ( i = 0; i < n; i++ )
    {
        u = (double)rand() / (RAND_MAX + 1) * (range_max - range_min) + range_min;
    }
    return u;
}

void delayRandom(DelayType dType, int tMin, int tMax, int iter){
    int l __attribute__((unused));
    if (dType == Compute){
        for ( int c=0; c < iter; c++ ){
            for (int i=0; i <10000; i++){
                int j = rand();
                int k  = rand();
                l = j ^ k;
            }
        }
    }else{
        sleepRandom(tMin, tMax, iter);
    }
}

void sleepRandom(int tMin, int tMax, int iter){
    unsigned int interval = getRangedRand(tMin,tMax,iter);
    Sleep(interval);
}

__declspec(dllexport) void __cdecl checkGroupDebuggers(struct execCheckState * eState, DelayType dType, int tMin, int tMax, int iter) {
    for (unsigned int i = 0; i < (unsigned int) (sizeof(execChecksGroupDebuggers) / sizeof(execCheck)); i++) {
        delayRandom(dType, tMin, tMax, iter);
        exec_check_guard(&execChecksGroupDebuggers[i]);
        eState[i] = execChecksGroupDebuggers[i].state;
    }
}

__declspec(dllexport) void __cdecl checkGroupCPU(struct execCheckState * eState, DelayType dType, int tMin, int tMax, int iter) {
    for ( unsigned int i = 0; i < (unsigned int)(sizeof(execChecksGroupCPU) / sizeof(execCheck)); i++  ) {
        delayRandom(dType, tMin, tMax, iter);
        exec_check_guard(&execChecksGroupCPU[i]);
        eState[i] = execChecksGroupCPU[i].state;
    }
}
__declspec(dllexport) void __cdecl checkGroupGenericSandbox(struct execCheckState * eState, DelayType dType, int tMin, int tMax, int iter) {
    for (unsigned int i = 0; i < (unsigned int) (sizeof(execChecksGroupGenericSandbox) / sizeof(execCheck)); i++) {
        delayRandom(dType, tMin, tMax, iter);
        exec_check_guard(&execChecksGroupGenericSandbox[i]);
        eState[i] = execChecksGroupGenericSandbox[i].state;
    }
}
__declspec(dllexport) void __cdecl checkGroupHooks(struct execCheckState * eState, DelayType dType, int tMin, int tMax, int iter){
    for (unsigned int i = 0; i < (unsigned int) (sizeof(execChecksGroupHooks) / sizeof(execCheck)); i++) {
        delayRandom(dType, tMin, tMax, iter);
        exec_check_guard(&execChecksGroupHooks[i]);
        eState[i] = execChecksGroupHooks[i].state;
    }
}

__declspec(dllexport) void __cdecl checkGroupSandboxie(struct execCheckState * eState, DelayType dType, int tMin, int tMax, int iter){
    for (unsigned int i = 0; i < (unsigned int) (sizeof(execChecksGroupSandboxie) / sizeof(execCheck)); i++) {
        delayRandom(dType, tMin, tMax, iter);
        exec_check_guard(&execChecksGroupSandboxie[i]);
        eState[i] = execChecksGroupSandboxie[i].state;
    }
}

__declspec(dllexport) void __cdecl checkGroupVBox(struct execCheckState * eState, DelayType dType, int tMin, int tMax, int iter){
    for (unsigned int i = 0; i < (unsigned int) (sizeof(execChecksGroupVBox) / sizeof(execCheck)); i++) {
        delayRandom(dType, tMin, tMax, iter);
        exec_check_guard(&execChecksGroupVBox[i]);
        eState[i] = execChecksGroupVBox[i].state;
    }
}

__declspec(dllexport) void __cdecl checkGroupVMware(struct execCheckState * eState, DelayType dType, int tMin, int tMax, int iter){
    for (unsigned int i = 0; i < (unsigned int) (sizeof(execChecksGroupVMware) / sizeof(execCheck)); i++) {
        delayRandom(dType, tMin, tMax, iter);
        exec_check_guard(&execChecksGroupVMware[i]);
        eState[i] = execChecksGroupVMware[i].state;
    }
}
__declspec(dllexport) void __cdecl checkGroupQuemu(struct execCheckState * eState, DelayType dType, int tMin, int tMax, int iter){
    for (unsigned int i = 0; i < (unsigned int) (sizeof(execChecksGroupQuemu) / sizeof(execCheck)); i++) {
        delayRandom(dType, tMin, tMax, iter);
        exec_check_guard(&execChecksGroupQuemu[i]);
        eState[i] = execChecksGroupQuemu[i].state;
    }
}
__declspec(dllexport) void __cdecl checkGroupBochs(struct execCheckState * eState, DelayType dType, int tMin, int tMax, int iter){
    for (unsigned int i = 0; i < (unsigned int) (sizeof(execChecksGroupBochs) / sizeof(execCheck)); i++) {
        delayRandom(dType, tMin, tMax, iter);
        exec_check_guard(&execChecksGroupBochs[i]);
        eState[i] = execChecksGroupBochs[i].state;
    }
}
__declspec(dllexport) void __cdecl checkGroupCu(struct execCheckState * eState, DelayType dType, int tMin, int tMax, int iter){
    for (unsigned int i = 0; i < (unsigned int) (sizeof(execChecksGroupCu) / sizeof(execCheck)); i++) {
        delayRandom(dType, tMin, tMax, iter);
        exec_check_guard(&execChecksGroupCu[i]);
        eState[i] = execChecksGroupCu[i].state;
    }
}

void getWinVer(void){
    char winverstr[32], aux[1024];
    // Seed (predictable sleep). TODO: rework for entropy


    winver.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    GetVersionEx(&winver);
    snprintf(winverstr, sizeof(winverstr) - sizeof(winverstr[0]),
             "%lu.%lu build %lu", winver.dwMajorVersion,
             winver.dwMinorVersion, winver.dwBuildNumber);

    /* Get CPU vendor */
    cpu_write_vendor(cpu_vendor);
    cpu_write_hv_vendor(cpu_hv_vendor);
    cpu_write_brand(cpu_brand);

    printf("[*] Windows version: %s\n", winverstr);
    printf("[*] CPU: %s\n", cpu_vendor);
    if (strlen(cpu_hv_vendor))
        printf("    Hypervisor: %s\n", cpu_hv_vendor);

    printf("    CPU brand: %s\n", cpu_brand);
    snprintf(aux, sizeof(aux) - sizeof(aux[0]), "Windows version: %s",
             winverstr);
    printf("%s\n", aux);

    if (strlen(cpu_hv_vendor))
        snprintf(aux, sizeof(aux) - sizeof(aux[0]), "CPU: %s (HV: %s) %s", cpu_vendor,
                 cpu_hv_vendor, cpu_brand);
    else
        snprintf(aux, sizeof(aux) - sizeof(aux[0]), "CPU: %s %s", cpu_vendor,
                 cpu_brand);
    printf("%s\n", aux);

}
void seedRand(void) {
    srand( (unsigned)time( NULL ) );
}

BOOL WINAPI DllMain(
        __attribute__((unused)) HINSTANCE hinstDLL,
        DWORD fdwReason,
        __attribute__((unused)) LPVOID lpReserved )
{
    switch( fdwReason )
    {
        case DLL_PROCESS_ATTACH:
            seedRand();
            getWinVer();
            break;
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        case DLL_PROCESS_DETACH:
            break;
        default:
            break;
    }
    return TRUE;  // Successful DLL_PROCESS_ATTACH.
}
int main(void)
{


    /* printf("[*] GROUP: Debuggers detection\n");
    checkGroupDebuggers(Compute, 0, 0, 200);
    printf ("[*] GROUP: CPU information based detection\n");
    checkGroupCPU(Time, 1000, 2000, 5);
    printf ("[*] GROUP: Generic sandbox detection\n");
    checkGroupGenericSandbox(Time, 100, 500, 1);
    printf ("[*] GROUP: Hooks detection\n");
    checkGroupHooks(Compute, 0, 0, 2000);
    printf ("[*] GROUP: Sandboxie detection\n");
    checkGroupSandboxie(Compute, 0, 0, 2);
    printf ("[*] GROUP: VBox detection\n");
    checkGroupVBox(Time, 800, 1001, 17);
    printf ("[*] GROUP: VMware detection\n");
    checkGroupVMware(Compute, 0, 0, 16);
    printf ("[*] GROUP: Quemu detection\n");
    checkGroupQuemu(Compute, 0, 0, 200);
    printf ("[*] GROUP: Bochs detection\n");
    checkGroupBochs(Time, 5030, 6010, 10);
    printf ("[*] GROUP: Cuckoo detection\n");
    checkGroupCu(Time, 50, 1000, 4);
    */

	return 0;
}
