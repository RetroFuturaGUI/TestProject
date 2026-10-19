#include "EnvironmentScene.hpp"
#include "EnvironmentScene_p.hpp"
#include "IncludeHelper.hpp"
#include <cmath>

void TestProject::EnvironmentScene::on_scene_update()
{
    if(!_members)
        return;

    if(!_members->_environment)
        return;

    if(!_members->_aeroLagoon)
        return;

    //The lagoon bobs gently up and down, by 0.03 room units (about 10 px in a 1280x720 window) every six
    //seconds or so, so the island reads as floating. It moves through the Environment, because the
    //Environment overwrites any position set on the model directly the next time it refits.
    const f32 seconds { static_cast<f32>(glfwGetTime()) };

    _members->_environment->SetPlacement(&*_members->_aeroLagoon, RetroFuturaGUI::EnvironmentPlacement
    {
        ._Position = glm::vec3(0.0f, 0.03f * std::sin(seconds), 0.0f),
        ._Size = glm::vec3(1.0f),
        ._Rotation = glm::vec3(0.0f)
    });
}
