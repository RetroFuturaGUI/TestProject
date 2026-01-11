import RetroFuturaGuiBinding
import MainWindow

if __name__ == "__main__":
    binding = RetroFuturaGuiBinding.RetroFuturaGuiBinding()
    binding.InitRetroFuturaGUI();
    mainWindow = MainWindow.MainWindow(binding);
    binding.DrawWindow();
