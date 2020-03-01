//
// Created by dimas on 2/27/2020.
//

#ifndef CHECKDEFS_H
#define CHECKDEFS_H

#include "bochs.h"
#include "cuckoo.h"
#include "cpu.h"
#include "qemu.h"
#include "vmware.h"
#include "wine.h"
#include "vbox.h"
#include "hooks.h"
#include "gensandbox.h"
#include "sandboxie.h"
#include "debuggers.h"
#include "common.h"
#include "config.h"
#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "pfdriver.h"

#ifndef PF_SUCCESS
#define PF_SUCCESS 0
#endif

#ifndef PF_FAILURE
#define PF_FAILURE 127
#endif


typedef int (*execCheckCallback)();
typedef int (*execCheckCallbackGuard)();

typedef struct execCheckCall {
    execCheckCallback callback;
    execCheckCallbackGuard guardCheck;
} execCheckCall;

typedef struct execCheck {
    struct execCheckState state;
    struct execCheckCall call;
} execCheck;

int debug_outputdebugstringGuard(void);

int passGuard(void);
int pass(void);

void exec_check_guard(struct execCheck *);
void sleepRandom(int, int, int i);

execCheck execChecksGroupDebuggers[N_GP_DEBUGGERS] = {
        {
                "IsDebuggerPresent()",
                0,
                "",
                &debug_isdebuggerpresent,
                &passGuard
        },
        {
                "OutputDebugString()",
                0,
                "",
                &debug_outputdebugstring,
                &debug_outputdebugstringGuard
        }
};

execCheck execChecksGroupCPU[N_GP_CPU] = {
        {
                "hi_CPU_VM_rdtsc",
                0,
                "",
                &cpu_rdtsc,
                &passGuard
        },
        {
                "hi_CPU_VM_rdtsc_force_vm_exit",
                0,
                "",
                &cpu_rdtsc_force_vmexit,
                &passGuard
        },
        {
                "hi_CPU_VM_hypervisor_bit",
                0,
                "",
                &cpu_hv,
                &passGuard
        },
        {
                "hi_CPU_VM_hv_vendor_name",
                0,
                "",
                &cpu_known_vm_vendors,
                &passGuard
        }
};

execCheck execChecksGroupGenericSandbox[N_GP_GEN_SANDBOX] = {
        {
                "hi_sandbox_mouse_act",
                0,
                "",
                &gensandbox_mouse_act,
                &passGuard
        },
        {
                "hi_sandbox_username",
                0,
                "",
                &gensandbox_username,
                &passGuard
        },
        {
                "hi_sandbox_path",
                0,
                "",
                &gensandbox_path,
                &passGuard
        },
        {
                "hi_sandbox_common_names",
                0,
                "",
                &gensandbox_common_names,
                &passGuard
        },
        {
                "hi_sandbox_drive_size",
                0,
                "",
                &gensandbox_drive_size,
                &passGuard
        },
        {
                "hi_sandbox_drive_size2",
                0,
                "",
                &gensandbox_drive_size2,
                &passGuard
        },
        {
                "hi_sandbox_sleep_gettickcount",
                0,
                "",
                &gensandbox_sleep_patched,
                &passGuard
        },
        {
                "hi_sandbox_NumberOfProcessors_less_2_raw",
                0,
                "",
                /* &gensandbox_one_cpu, dies on this investigate */
                &pass,
                &passGuard
        },
        {
                "hi_sandbox_NumberOfProcessors_less_2_GetSystemInfo",
                0,
                "",
                &gensandbox_one_cpu_GetSystemInfo,
                &passGuard
        },
        {
                "hi_sandbox_pysicalmemory_less_1Gb",
                0,
                "",
                &gensandbox_less_than_onegb,
                &passGuard
        },
        {
                "hi_sandbox_uptime",
                0,
                "",
                &gensandbox_uptime,
                &passGuard
        },
        {
                "hi_sandbox_IsNativeVhdBoot",
                0,
                "",
                &gensandbox_IsNativeVhdBoot,
                &passGuard
        }
};

execCheck execChecksGroupHooks[N_GP_HOOKS] = {
        {
               "hi_hooks_shellexecuteexw_m1",
                0,
                "",
                &check_hook_ShellExecuteExW_m1,
                &passGuard
        },
        {
                "hi_hooks_createprocessa_m1",
                0,
                "",
                &check_hook_CreateProcessA_m1,
                &passGuard
        }
};


execCheck execChecksGroupSandboxie[N_GP_SANDBOXIE] = {
        {
                "hi_sandboxie",
                0,
                "",
                &sboxie_detect_sbiedll,
                &passGuard
        },
        {
                "hi_wine",
                0,
                "",
                &wine_detect_get_unix_file_name,
                &passGuard
        }

};

execCheck execChecksGroupVBox[N_GP_VBOX] = {
        {
                "hi_virtualbox1",
                0,
                "",
                &vbox_reg_key1,
                &passGuard
        },
        {
                "hi_virtualbox2",
                0,
                "",
                &vbox_reg_key2,
                &passGuard
        },
        {
                "hi_virtualbox3",
                0,
                "",
                &vbox_reg_key3,
                &passGuard
        },
        {
                "hi_virtualbox4",
                0,
                "",
                &vbox_reg_key4,
                &passGuard
        },
        {
                "hi_virtualbox5",
                0,
                "",
                &vbox_reg_key5,
                &passGuard
        },
        {
                "hi_virtualbox7",
                0,
                "",
                &vbox_reg_key7,
                &passGuard
        },
        {
                "hi_virtualbox8",
                0,
                "",
                &vbox_reg_key8,
                &passGuard
        },
        {
                "hi_virtualbox9",
                0,
                "",
                &vbox_reg_key9,
                &passGuard
        },
        {
                "hi_virtualbox10",
                0,
                "",
                &vbox_reg_key10,
                &passGuard
        },
        {
                "hi_virtualbox_sysf1",
                0,
                "",
                &vbox_sysfile1,
                &passGuard
        },
        {
                "hi_virtualbox_sysf2",
                0,
                "",
                &vbox_sysfile2,
                &passGuard
        },
        {
                "hi_virtualbox_mac",
                0,
                "",
                &vbox_mac,
                &passGuard
        },
        {
                "hi_virtualbox14",
                0,
                "",
                &vbox_devices,
                &passGuard
        },
        {
                "hi_virtualbox15",
                0,
                "",
                &vbox_traywindow,
                &passGuard
        },
        {
                "hi_virtualbox_net_shares",
                0,
                "",
                &vbox_network_share,
                &passGuard
        },
        {
                "hi_virtualbox_proc",
                0,
                "",
                &vbox_processes,
                &passGuard
        },
        {
                "hi_virtualbox_wmi_dev",
                0,
                "",
                &vbox_wmi_devices,
                &passGuard
        }
};

execCheck execChecksGroupVMware[N_GP_VMWARE] = {
        {
                "hi_vmware1",
                0,
                "",
                &vmware_reg_key1,
                &passGuard
        },
        {
                "hi_vmware2",
                0,
                "",
                &vmware_reg_key2,
                &passGuard
        },
        {
                "hi_vmware_sysf1",
                0,
                "",
                &vmware_sysfile1,
                &passGuard
        },
        {
                "hi_vmware_sysf2",
                0,
                "",
                &vmware_sysfile2,
                &passGuard
        },
        {
                "hi_vmware_mac",
                0,
                "",
                &vmware_mac,
                &passGuard
        },
        {
                "hi_vmware_ser",
                0,
                "",
                &vmware_wmi_serial,
                &passGuard
        },
        {
                "hi_vmware_adapter",
                0,
                "",
                &vmware_adapter_name,
                &passGuard
        },
        {
                "hi_vmware_dev",
                0,
                "",
                &vmware_devices,
                &passGuard
        }
};

execCheck execChecksGroupQuemu[N_GP_QUEMU] = {
        {
                "hi_qemu1",
                0,
                "",
                &qemu_reg_key1,
                &passGuard
        },
        {
                "hi_qemu2",
                0,
                "",
                &qemu_reg_key2,
                &passGuard
        },
        {
                "hi_qemu_cpu",
                0,
                "",
                &qemu_cpu_name,
                &passGuard
        }
};

execCheck execChecksGroupBochs[N_GP_BOCHS] = {
        {
                "hi_bochs1",
                0,
                "",
                &bochs_reg_key1,
                &passGuard
        },
        {
                "hi_bochs_amd",
                0,
                "",
                &bochs_cpu_amd1,
                &passGuard
        },
        {
                "hi_bochs_intel",
                0,
                "",
                &bochs_cpu_intel1,
                &passGuard
        }
};

execCheck execChecksGroupCu[N_GP_CU] = {
        {
                "hi_cuckoo_tls",
                0,
                "",
                &cuckoo_check_tls,
                &passGuard
        }
};

char cpu_vendor[13], cpu_hv_vendor[13], cpu_brand[49];
OSVERSIONINFO winver;

#endif //CHECKDEFS_H
