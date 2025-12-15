#include "gameengine.h"


Game::Game() : ppltk::Window()
{
    gfx = ppl7::grafix::GetGrafix();
    setWindowTitle("Patricks Company Game");
    setBackgroundColor(ppl7::grafix::Color(0, 0, 0, 0));
    setWindowIcon(gfx->Icons32.getDrawable(30));
    menue = NULL;
    fpsLabel = NULL;
    exitButton = NULL;
    layout_menue = NULL;
    Style.setStyle(ppltk::WidgetStyle::Dark);
    // Style.labelFont.setSize(20);
    wm = ppltk::GetWindowManager();
    wm->setWidgetStyle(Style);

    setWindowSize(1920, 1080);
    // enableFixedUiSize(true, width, height);
    setBackgroundColor(ppl7::grafix::Color(92, 92, 92, 92));

    int flags = ppltk::Window::DefaultWindow;
    flags |= ppltk::Window::Resizeable;
    //flags = ppltk::Window::DefaultFullscreen;

    setFlags(flags);
    ppltk::GetWindowManager()->createWindow(*this);

    menue = new ppltk::Frame(0, 0, this->width(), 32);
    addChild(menue);
    // ppl7::grafix::Size menueSize = menue->clientSize();

    layout_menue = new ppltk::HBoxLayout();
    menue->setLayout(layout_menue);

    ppltk::Label* label = new ppltk::Label(0, 0, 40, 30, "FPS:");
    ppl7::grafix::Size ss = label->sizeHint();
    ppl7::PrintDebug("FPS Label: %d x %d\n", ss.width, ss.height);
    layout_menue->addWidget(label);

    fpsLabel = new ppltk::Label(40, 0, 80, 30, "0", ppltk::Label::Inset);
    ss = fpsLabel->sizeHint();
    ppl7::PrintDebug("FPS: %d x %d\n", ss.width, ss.height);
    layout_menue->addWidget(fpsLabel);

    exitButton = new ppltk::Button(menue->width() - 100, 0, 100, 30, "Exit", wm->Toolbar.getDrawable(68));
    exitButton->setEventHandler(this);
    ss = exitButton->sizeHint();
    ppl7::PrintDebug("Button Size: %dx%d\n", ss.width, ss.height);
    layout_menue->addWidget(exitButton);


}

Game::~Game()
{
}

void Game::init()
{
}

void Game::init_grafix()
{
}

void Game::run()
{
    // Main game loop
    wm->startEventLoop();
}

void Game::loadSavegame(const ppl7::String& filename)
{
    // Load a savegame from file
}

