#include "ScrollViewScene.hpp"
#include "ScrollViewScene_p.hpp"
#include <print>

void TestProject::ScrollViewScene::on_testButton_clicked()
{
    if(!_members)
        return;

    if(!_members->_testVideo)
        return;

    std::println("testButton Clicked!");

    // first click opens and plays, every click after that pauses or carries on
    static bool opened { false };
    static bool playing { false };

    if(!opened)
    {
        opened = _members->_testVideo->OpenVideoFile(R"(C:\Users\Sophie\Videos\test.webm)");
        std::println("video open: {}", opened);

        if(!opened)
            return;
    }

    if(playing)
        _members->_testVideo->Pause();
    else
        _members->_testVideo->Play();

    playing = !playing;
}
