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

    public enum ColorSetState : UInt32
    {
        Enabled,
        Disabled,
        Clicked,
        Hover
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

    
    [DllImport(dllName, CallingConvention = CallingConvention.Cdecl)]
    public static extern void SetBackgroundColors(
        [MarshalAs(UnmanagedType.LPStr)] string id,
        IntPtr colors,
        UInt32 colorCount,
        UInt32 colorSetState
    );

    [DllImport(dllName, CallingConvention = CallingConvention.Cdecl)]
    public static extern void SetBorderColors(
        [MarshalAs(UnmanagedType.LPStr)] string id,
        IntPtr colors,
        UInt32 colorCount,
        UInt32 colorSetState
    );
};