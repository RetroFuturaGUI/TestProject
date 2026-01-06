import RetroFuturaGuiBinding

class MainWindow:
    def __init__(self, binding):
        self.binding = binding
        self.setup()

    def onButtonClick(self):
        print("This is a function written in Python!")

    def setup(self):
        # Wrap the instance method to accept the extra argument
        callback = lambda data: self.onButtonClick()
        self.binding.ConnectSlot("MainWindow/testButton", callback, self.binding.WidgetAction.OnClick, False)
