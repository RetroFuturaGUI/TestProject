#include "TabScene.hpp"
#include "TabScene_p.hpp"
#include "Window.hpp"
#include <print>

void TestProject::TabScene::on_windowTab_selectionChanged(RetroFuturaGUI::Window* window)
{
    if(!window)
    {
        std::println("WindowTab: no tab left");
        return;
    }

    std::println("WindowTab: \"{}\" selected", window->GetWindowTitle());
}

void TestProject::TabScene::on_scene_update()
{
    if(!_members)
        return;

    if(!_members->_window)
        return;

    if(!_members->_windowTab)
        return;

    //The WindowTab fills the window down to its bottom corners, so it rounds its own like the window's. Each frame, since
    //docking squares them any time.
    const glm::vec4 windowRadii { _members->_window->GetDrawnCornerRadii() };
    const glm::vec4 bottomRadii { 0.0f, 0.0f, windowRadii.z, windowRadii.w };
    _members->_windowTab->SetCornerRadii(bottomRadii);
    _members->_windowTab->SetContentCornerRadii(bottomRadii);
}
