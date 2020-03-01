using System;
using System.Threading;
using System.Runtime.InteropServices;
using System.Collections.Generic;
using System.Text;

// Delegate with function signature for the GetVersion function
[UnmanagedFunctionPointer(CallingConvention.Cdecl)]
[return: MarshalAs(UnmanagedType.U4)]
delegate UInt32 checkGroupDebuggers(
    [OutAttribute][InAttribute] StringBuilder versionString,
    [OutAttribute] UInt32 length);

    class Program
    {
        [DllImport("kernel32.dll")]
        static extern IntPtr LoadLibrary(string dllName);

        [DllImport("kernel32.dll")]
        static extern IntPtr GetProcAddress(IntPtr hModule, string procName);

        delegate int MessageBoxDelegate(IntPtr hwnd,
            [MarshalAs(UnmanagedType.LPWStr)]string text,
            [MarshalAs(UnmanagedType.LPWStr)]string caption,
            int type);

        static void Main(string[] args)
        {
            IntPtr pafishApi = LoadLibrary("pafish.dll");
            IntPtr debugAddress = GetProcAddress(pafishApi, "checkGroupDebuggers");
            MessageBoxDelegate mbd = (MessageBoxDelegate)Marshal.GetDelegateForFunctionPointer(msgBoxAddress,typeof(MessageBoxDelegate));
            mbd(IntPtr.Zero, "A", "B", 0);

            DoSomething(mbd);
        }

        static void DoSomething(MessageBoxDelegate mbd)
        {
            mbd(IntPtr.Zero, "Work completed.", "Work Progress", 0);
        }
    }