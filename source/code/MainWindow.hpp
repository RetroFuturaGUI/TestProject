#pragma once
#include "Window.hpp"
#include "MainWindow_p.hpp"
#include <chrono>
#include <string>
#define privateSlots private

namespace TestProject
{
    class MainWindow
    {
    public:
        /// @brief Constructs the main window and sets up its widgets via setup().
        MainWindow(std::string_view windowTitle, const i32 width, const i32 height)
        {
            setup(windowTitle, width, height);
        }

        /// @brief Runs the main loop, drawing the window each frame and capping the frame rate to 60 FPS.
        void Draw()
        {
            constexpr double targetFrameTime { 1.0 / 60.0 };
	        auto lastFrameTime = std::chrono::high_resolution_clock::now();

            while(!WindowShouldClose())
            {
                auto now = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> elapsed = now - lastFrameTime;
                lastFrameTime = now;
                _members->_window->Draw();

                std::chrono::duration<double> frameTime =
                std::chrono::high_resolution_clock::now() - now;

                if (frameTime.count() < targetFrameTime)
                {
                    std::this_thread::sleep_for(
                        std::chrono::duration<double>(targetFrameTime - frameTime.count()));
                }
            }
        }

        /// @brief Returns whether the main window has been requested to close.
        bool WindowShouldClose()
        {
            return _members->_window->WindowShouldClose();
        }


    privateSlots:


        void on_testButton_clicked()
        {
            //static bool checkRef = false;
            std::println("testButton Clicked!");
            //glm::vec3 currentRotation = _members->_testModel->GetRotation();
            //_members->_testModel->SetRotation(currentRotation += glm::vec3(4.0f, 6.0f, 7.0f));
            //_members->_testCheckBox->SetInheritValueReference(&checkRef);
            //_members->_testCheckBox->UseInherietedValue(true);
            _members->_testTextBox->SetValue<f64>(0.33333333333333333333333333333333333333333333333333333333333333333333, false);
            _members->_testTable->SetValue<f64>(0.33333333333333333333333333333333333333333333333333333333333333333333, { ._Row = 0, ._Column = 0 }, false);

        }

        void on_testTextBox_textChange()
        {
            /*static std::string valueStr;
            valueStr =  _members->_testTextBox->GetText();
            std::println("testTextBox current Text: {}", valueStr);

            if(valueStr.empty())
                return;

            static u32 value;

            static bool validNumber;
            validNumber = true;

            for (char c : valueStr)
            {
                if (!isdigit(c))
                {
                    validNumber = false;
                    break;
                }
            }

            if(!validNumber)
                return;
            
            value = std::stoi(valueStr);
            _members->_testSlider->SetValue<u32>(value, false);*/

            std::println("bool: {}\ni8: {}\ni16: {}\ni32: {}\ni64: {}\nu8: {}\nu16: {}\nu32: {}\nu64: {}\nf32: {}\nf64: {}", 
                _members->_testTextBox->GetValue<bool>(),
                _members->_testTextBox->GetValue<i8>(),
                _members->_testTextBox->GetValue<i16>(),
                _members->_testTextBox->GetValue<i32>(),
                _members->_testTextBox->GetValue<i64>(),
                _members->_testTextBox->GetValue<u8>(),
                _members->_testTextBox->GetValue<u16>(),
                _members->_testTextBox->GetValue<u32>(),
                _members->_testTextBox->GetValue<u64>(),
                _members->_testTextBox->GetValue<f32>(),
                _members->_testTextBox->GetValue<f64>()
            );
        }

        void on_testTableTextChange()
        {
            std::println("bool: {}\ni8: {}\ni16: {}\ni32: {}\ni64: {}\nu8: {}\nu16: {}\nu32: {}\nu64: {}\nf32: {}\nf64: {}", 
                _members->_testTable->GetValue<bool>({ ._Row = 0, ._Column = 0 }),
                _members->_testTable->GetValue<i8>({ ._Row = 0, ._Column = 0 }),
                _members->_testTable->GetValue<i16>({ ._Row = 0, ._Column = 0 }),
                _members->_testTable->GetValue<i32>({ ._Row = 0, ._Column = 0 }),
                _members->_testTable->GetValue<i64>({ ._Row = 0, ._Column = 0 }),
                _members->_testTable->GetValue<u8>({ ._Row = 0, ._Column = 0 }),
                _members->_testTable->GetValue<u16>({ ._Row = 0, ._Column = 0 }),
                _members->_testTable->GetValue<u32>({ ._Row = 0, ._Column = 0 }),
                _members->_testTable->GetValue<u64>({ ._Row = 0, ._Column = 0 }),
                _members->_testTable->GetValue<f32>({ ._Row = 0, ._Column = 0 }),
                _members->_testTable->GetValue<f64>({ ._Row = 0, ._Column = 0 })
            );
        }

        void on_testTextBox_enterPressed()
        {
            std::println("Enter Pressed");
        }

        void on_testTextBox_enterReleased()
        {
            std::println("Enter Released");
        }

        void on_testTextBox_copy()
        {
            std::println("Text copied: {}", _members->_testTextBox->GetCopiedText());
        }

        void on_testTextBox_paste()
        {
            std::println("Text pasted:");
        }

        void on_testSlider_valueChanged()
        {
        /*    static std::string _valueStr;
            static u32 value;
            value = _members->_testSlider->GetValue<u32>();
            _valueStr = std::to_string(value);
            _members->_testTextBox->SetText(_valueStr, false);
            _members->_testProgressBar->SetValue<u32>(value, false);

*/
            _members->_testTable->SetVerticalScrollPosition(_members->_testSlider->GetValue<f32>());
        }

        std::unique_ptr<MainWindow_p> _members { nullptr };
        void setup(std::string_view windowTitle, const i32 width, const i32 height);
    };
}