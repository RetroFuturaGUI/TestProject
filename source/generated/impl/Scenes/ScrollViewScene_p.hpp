#pragma once
#include "Scene.hpp"
#include "ScrollView.hpp"
#include "Button.hpp"
#include "Video.hpp"
#include "Histogram.hpp"
#include "ColorPicker.hpp"
#include <memory>

namespace TestProject
{
    class ScrollViewScene_p
    {
    public:
        std::unique_ptr<RetroFuturaGUI::Scene> _scene { nullptr };

        //Non-owning: the scene owns its root container and keeps it alive for as long as _scene lives.
        RetroFuturaGUI::ScrollView* _scrollView { nullptr };

        //Non-owning: the ScrollView constructs these four itself and owns them.
        RetroFuturaGUI::Video* _testVideo { nullptr };
        RetroFuturaGUI::Button* _testButton { nullptr };
        RetroFuturaGUI::Histogram* _testHistogram { nullptr };
        RetroFuturaGUI::ColorPicker* _testColorPicker { nullptr };
    };
}
