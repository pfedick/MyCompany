#include "gameengine.h"



void Game::closeEvent(ppltk::Event* event)
{
    ppltk::WindowManager* wm = ppltk::GetWindowManager();
    wm->destroyWindow(*this);
    event->accept();
}

void Game::mouseClickEvent(ppltk::MouseEvent* event)
{
    Widget* w = event->widget();
    if (w == exitButton)
    {
        ppltk::WindowManager* wm = ppltk::GetWindowManager();
        wm->destroyWindow(*this);
        event->accept();
    }
}



