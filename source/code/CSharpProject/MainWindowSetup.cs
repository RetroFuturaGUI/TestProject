using System;
//using RetroFuturaGuiBinding;

public partial class MainWindow
{
    private void setup()
    {
        RetroFuturaGuiBinding.ConnectSlot("MainWindow/testButton", onButtonClick, (int)RetroFuturaGuiBinding.WidgetAction.OnClick, false);
    }
};