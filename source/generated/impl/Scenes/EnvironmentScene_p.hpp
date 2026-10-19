#pragma once
#include "Scene.hpp"
#include "Environment.hpp"
#include "Model.hpp"
#include <memory>

namespace TestProject
{
    class EnvironmentScene_p
    {
    public:
        std::unique_ptr<RetroFuturaGUI::Scene> _scene { nullptr };

        //Non-owning: the scene owns its root container and keeps it alive for as long as _scene lives.
        RetroFuturaGUI::Environment* _environment { nullptr };

        std::unique_ptr<RetroFuturaGUI::Model> _aeroLagoon { nullptr };
    };
}
