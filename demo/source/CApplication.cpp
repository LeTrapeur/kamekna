//
// Created by tklempka on 24/04/18.
//

#include <TitleState.hpp>
#include <MenuState.hpp>
#include <GameState.hpp>
#include <PauseState.hpp>
#include <GameoverState.hpp>

#include "CApplication.hpp"

CApplication::CApplication():
        IApplication()
{}

void CApplication::registerStates() {
    m_stateStack.registerState<TitleState>(States::Title);
    m_stateStack.registerState<MenuState>(States::Menu);
    m_stateStack.registerState<GameState>(States::Game);
    m_stateStack.registerState<PauseState>(States::Pause);
    m_stateStack.registerState<GameoverState>(States::Gameover);
    m_stateStack.pushState(States::Title);
}

void CApplication::loadContent() {
    // load basic resources
    m_fonts.load(Fonts::Main, "resources/fonts/arial.ttf");
    m_fonts.load(Fonts::Debug, "resources/fonts/arial.ttf");
    m_textures.load(Textures::TitleScreen, "resources/titlescreen.png");
}

void CApplication::loadSettings() {
    m_settings.load(Settings::Default, "resources/settings.txt");
    SettingsParser settings = m_settings.get(Settings::Default);
    std::string window_title;
    settings.get("window_title", window_title);
    m_window.setTitle(window_title);
}
