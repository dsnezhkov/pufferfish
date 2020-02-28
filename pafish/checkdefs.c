//
// Created by dimas on 2/27/2020.
//

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
#include "checkdefs.h"

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



typedef int (*execCheckCallback)();

typedef struct execCheck{
   char * text;
   execCheckCallback callback;
   char * text_log;
   char * text_trace;
} execCheck;
execCheck execChecksGroupDebuggers[] = {
        {
                "Using IsDebuggerPresent()",
                &debug_isdebuggerpresent,
                "Debugger traced using IsDebuggerPresent()",
                "hi_debugger_isdebuggerpresent"
        },
};