using System;

public partial class MainWindow
{
    public MainWindow()
    {
        setup();
    }

    private static void onButtonClick()
    {
        Console.WriteLine("Hello from C#!");
        RetroFuturaGuiBinding.SetRotation("MainWindow/testButton", 45.0f);
    }
};