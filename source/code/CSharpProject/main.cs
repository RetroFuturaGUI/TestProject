using System;
using System.Runtime.InteropServices;

public class NativeMethods
{
    // Replace "YourCppDll" with the name of your C++ DLL
    const string dllName = "TestProjectNative";

    [DllImport(dllName, CallingConvention = CallingConvention.Cdecl)]
    public static extern void InitRetroFuturaGUI();

    [DllImport(dllName, CallingConvention = CallingConvention.Cdecl)]
    public static extern void Draw();
}

class Program
{
    static void Main()
    {
        NativeMethods.InitRetroFuturaGUI();
        NativeMethods.Draw(); //this calls the loop
    }
}