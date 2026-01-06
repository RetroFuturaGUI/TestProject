import RetroFuturaGuiBinding
import MainWindow

if __name__ == "__main__":
    binding = RetroFuturaGuiBinding.RetroFuturaGuiBinding()
    binding.InitRetroFuturaGUI();
    mainWindow = MainWindow.MainWindow(binding);
    binding.DrawWindow();


'''

os.chdir(os.path.dirname(os.path.abspath(__file__)));

try:
    RetroFuturaGUI = CDLL("./TestProjectNative.dll")
    #print("DLL loaded successfully.")
except Exception as e:
    print(f"Error loading DLL: {e}")
    exit(1)

RetroFuturaGUI.SetWorkingDirectory.argtypes = [c_char_p]
RetroFuturaGUI.SetWorkingDirectory.restype = None

resource_path = os.getcwd().encode("utf-8")
#print(f"Setting working directory to: {resource_path}")

try:
    RetroFuturaGUI.SetWorkingDirectory(resource_path);
    #print("Working directory set successfully.")
except Exception as e:
    print(f"Error setting working directory: {e}")

RetroFuturaGUI.InitRetroFuturaGUI.argtypes = []
RetroFuturaGUI.InitRetroFuturaGUI.restype = None

try:
    RetroFuturaGUI.InitRetroFuturaGUI();
    print("Python initialized RetroFuturaGUI")
except Exception as e:
    print(f"Error initializing DLL: {e}")

try:
    RetroFuturaGUI.Draw();
    print("Window Terminated")
except Exception as e:
    print(f"Error drawing window: {e}")

    '''