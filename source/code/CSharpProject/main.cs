using System;
using System.IO;
//using MainWindow;

class Program
{
    static void Main()
    {
        string workingDir = System.Environment.ProcessPath;
        workingDir = Path.GetDirectoryName(workingDir);
        RetroFuturaGuiBinding.SetWorkingDirectory(workingDir);
        RetroFuturaGuiBinding.InitRetroFuturaGUI();
        MainWindow mainWindow = new MainWindow();
        Console.WriteLine("C# initialized RetroFuturaGUI! Now Drawing the Window");
        RetroFuturaGuiBinding.Draw(); //this calls the loop
    }
}