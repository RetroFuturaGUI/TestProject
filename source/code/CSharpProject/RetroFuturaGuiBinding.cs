using System;
using System.Runtime.InteropServices;

public class RetroFuturaGuiBinding
{
    public enum WidgetAction : int
    {
        OnClick,
        OnRelease,
        OnMouseEnter,
        OnMouseLeave,
        WhileHover,
        Unknown = -1
    };   

    public delegate void Callback();

    const string dllName = "TestProjectNative";

    [DllImport(dllName, CallingConvention = CallingConvention.Cdecl)]
    public static extern void InitRetroFuturaGUI();

    [DllImport(dllName, CallingConvention = CallingConvention.Cdecl)]
    public static extern void Draw();

    [DllImport(dllName, CallingConvention = CallingConvention.Cdecl)]
    public static extern void ConnectSlot(
        [MarshalAs(UnmanagedType.LPStr)] string id,
        Callback callback,
        int action,
        bool async
    );

    [DllImport(dllName, CallingConvention = CallingConvention.Cdecl)]
    public static extern void DisconnectSlot(
        [MarshalAs(UnmanagedType.LPStr)] string id,
        Callback callback,
        int action
    );

    [DllImport(dllName, CallingConvention = CallingConvention.Cdecl)]
    public static extern void SetRotation(
        [MarshalAs(UnmanagedType.LPStr)] string id,
        float degree
    );

    [DllImport(dllName, CallingConvention = CallingConvention.Cdecl)]
    public static extern void SetSize(
        [MarshalAs(UnmanagedType.LPStr)] string id,
        float width,
        float height
    );
};