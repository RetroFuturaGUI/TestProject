#include "MainScene.hpp"
#include "MainScene_p.hpp"
#include <print>

void TestProject::MainScene::on_testButton_clicked()
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

void TestProject::MainScene::on_testTextBox_textChange()
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

void TestProject::MainScene::on_testTableTextChange()
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

void TestProject::MainScene::on_testTextBox_enterPressed()
{
    std::println("Enter Pressed");
}

void TestProject::MainScene::on_testTextBox_enterReleased()
{
    std::println("Enter Released");
}

void TestProject::MainScene::on_testTextBox_copy()
{
    std::println("Text copied: {}", _members->_testTextBox->GetCopiedText());
}

void TestProject::MainScene::on_testTextBox_paste()
{
    std::println("Text pasted:");
}

void TestProject::MainScene::on_testSlider_valueChanged()
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
