using System;

public partial class MainWindow
{
    private void setup()
    {
        RetroFuturaGuiBinding.ConnectSlot("MainWindow/testButton", onButtonClick, (int)RetroFuturaGuiBinding.WidgetAction.OnClick, false);
    }
};