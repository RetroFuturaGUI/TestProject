using System;

public partial class MainWindow
{
    private void setup()
    {
        RetroFuturaGuiBinding.ConnectSlot("MainWindow/TestButton", onButtonClick, (int)RetroFuturaGuiBinding.WidgetAction.OnClick, false);
    }
};