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
    layout_menue = new ppltk::HBoxLayout();
    layout_menue->setSpacing(1);
    menue->setLayout(layout_menue);

    ppltk::Label* label = new ppltk::Label("FPS:");
    layout_menue->addWidget(label);

    fpsLabel = new ppltk::Label("0", ppltk::Label::Inset);
    layout_menue->addWidget(fpsLabel);

    layout_menue->addWidget(new ppltk::Button("Button 1"));
    layout_menue->addWidget(new ppltk::Button("Button 2"));
    layout_menue->addWidget(new ppltk::Button("Button 3"));

    layout_menue->addSpacer(new ppltk::SpacerItem());


    exitButton = new ppltk::Button("Exit", wm->Toolbar.getDrawable(68));
    exitButton->setEventHandler(this);
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

