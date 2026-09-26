#pragma once
#include "Scene.hpp"
#include "Lasagna.hpp"
#include "Button.hpp"
#include "Label.hpp"
#include "SeparatorLine.hpp"
#include "TextBox.hpp"
#include "Image.hpp"
#include "SvgImage.hpp"
#include "Model.hpp"
#include "CheckBox.hpp"
#include "RadioButton.hpp"
#include "RadioButtonGroup.hpp"
#include "Slider.hpp"
#include "ProgressBar.hpp"
#include "Table.hpp"
#include "Prefab.hpp"
#include "ComboBox.hpp"
#include "ExtendedComboBox.hpp"
#include <memory>

namespace TestProject
{
    class MainScene_p
    {
    public:
        std::unique_ptr<RetroFuturaGUI::Scene> _scene;
        std::unique_ptr<RetroFuturaGUI::Button> _testButton;
        std::unique_ptr<RetroFuturaGUI::Label> _testLabel;
        std::unique_ptr<RetroFuturaGUI::TextBox> _testTextBox;
        std::unique_ptr<RetroFuturaGUI::Image> _testImage;
        std::unique_ptr<RetroFuturaGUI::SvgImage> _testSvgImage;
        std::unique_ptr<RetroFuturaGUI::Model> _testModel;
        std::unique_ptr<RetroFuturaGUI::CheckBox> _testCheckBox;
        std::unique_ptr<RetroFuturaGUI::RadioButton> _testRadioButton;
        std::unique_ptr<RetroFuturaGUI::RadioButton> _testRadioButton2;
        std::unique_ptr<RetroFuturaGUI::RadioButtonGroup> _testRadioButtonGroup;
        std::unique_ptr<RetroFuturaGUI::Label> _testRadioButtonText;
        std::unique_ptr<RetroFuturaGUI::Label> _testRadioButtonText2;
        std::unique_ptr<RetroFuturaGUI::Slider> _testSlider;
        std::unique_ptr<RetroFuturaGUI::ProgressBar> _testProgressBar;
        std::unique_ptr<RetroFuturaGUI::Table> _testTable;
        std::unique_ptr<RetroFuturaGUI::Prefab> _testStepper;
        std::unique_ptr<RetroFuturaGUI::ComboBox> _testComboBox;
        std::unique_ptr<RetroFuturaGUI::ExtendedComboBox> _testExtendedComboBox;
        std::unique_ptr<RetroFuturaGUI::SeparatorLine> _testSeparatorLine;
    };
}
