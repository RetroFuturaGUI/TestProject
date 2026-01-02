using System;
//using MainWindow;

class Program
{
    static void Main()
    {
        RetroFuturaGuiBinding.InitRetroFuturaGUI();
        MainWindow mainWindow = new MainWindow();
        Console.WriteLine("C# initialized RetroFuturaGUI! Now Drawing the Window");
        RetroFuturaGuiBinding.Draw(); //this calls the loop
    }
}