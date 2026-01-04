using System;
using System.Drawing;
using System.Runtime.InteropServices;

public partial class MainWindow
{
    public MainWindow()
    {
        setup();
    }

    private static float[] colors = { 0.9f, 6.0f, 0.8f, 1.0f, 
                               0.8f, 0.9f, 0.6f, 1.0f,
                               0.6f, 0.8f, 0.9f, 1.0f };

static bool enable = false;

    private static void onButtonClick()
    {
        Console.WriteLine("Hello from C#!");
        //RetroFuturaGuiBinding.SetRotation("MainWindow/testButton", 45.0f);
        //RetroFuturaGuiBinding.SetSize("MainWindow/testButton", 400.0f, 300.0f);
        
        RetroFuturaGuiBinding.SetEnabled("MainWindow/testButton", enable);
        enable = !enable;
        RetroFuturaGuiBinding.SetEnabled("MainWindow/testButton", enable);
       /* GCHandle handle = GCHandle.Alloc(colors, GCHandleType.Pinned);
        try
        {
            IntPtr ptr = handle.AddrOfPinnedObject();
            RetroFuturaGuiBinding.SetBorderColors("MainWindow/testButton", ptr, (uint)colors.Length / 4, (UInt32)RetroFuturaGuiBinding.ColorState.Enabled);
        }
        finally
        {
            handle.Free();
        }*/
    }
};