#include "MenuState.h"
#include "ResourceHolder.h"
#include "MusicPlayer.h"
#include "Utility.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>


MenuState::MenuState(StateStack& stack, Context context):
    State(stack, context),
    m_gui(*context.window),
    m_options(),
    m_optionIndex(0),
    m_sounds(*context.sounds)
{
        sf::Texture& texture = context.textures->get(Textures::TitleScreen);
        sf::Font& font = context.fonts->get(Fonts::Main);

        m_backgroundSprite.setTexture(texture);

        // setup GUI
        m_gui.setFont(font);

        tgui::Button::Ptr playButton = tgui::Button::create();
        playButton->setSize(200, 50);
        playButton->setPosition(context.window->getView().getSize() / 2.f);
        playButton->setText("Start");
        playButton->connect("pressed", [&](){ requestStackPop(); requestStackPush(States::Game); });
        m_gui.add(playButton);

        tgui::Button::Ptr optionsButton = tgui::Button::create();
        optionsButton->setSize(200, 50);
        optionsButton->setPosition(context.window->getView().getSize() / 2.f + sf::Vector2f(0.f, 75.f));
        optionsButton->setText("Options");
        m_gui.add(optionsButton);

        tgui::Button::Ptr exitButton = tgui::Button::create();
        exitButton->setSize(200, 50);
        exitButton->setPosition(context.window->getView().getSize() / 2.f + sf::Vector2f(0.f, 150.f));
        exitButton->setText("Exit");
        exitButton->connect("pressed", [&](){ requestStackPop(); });
        m_gui.add(exitButton);

	/* TODO Title music
        context.music->setVolume(25.f);
        context.music->play(Music::MenuTheme);*/
}

void MenuState::draw()
{
    sf::RenderWindow& window = *getContext().window;

    window.setView(window.getDefaultView());
    window.draw(m_backgroundSprite);

    m_gui.draw();

    for(const sf::Text& text: m_options)
            window.draw(text);
}

bool MenuState::update(sf::Time)
{
    return true;
}

bool MenuState::handleEvent(const sf::Event& event)
{
    m_gui.handleEvent(event);
    // The demonstration menu logic
    if (event.type != sf::Event::KeyPressed)
            return false;

    if (event.key.code == sf::Keyboard::Return)
    {
      //m_sounds.play(SoundEffect::Button);
        if (m_optionIndex == Play)
        {

        }
        else if (m_optionIndex == Exit)
        {
            // The exit option was chosen, by removing itself, the stack will be empty, and the game will know it is time to close.
            
        }
    }

    else if (event.key.code == sf::Keyboard::Up)
    {
        // Decrement and wrap-around
        if (m_optionIndex > 0)
            m_optionIndex--;
        else
            m_optionIndex = m_options.size() - 1;

        updateOptionText();
    }

    else if (event.key.code == sf::Keyboard::Down)
    {
        // Increment and wrap-around
        if (m_optionIndex < m_options.size() - 1)
            m_optionIndex++;
        else
            m_optionIndex = 0;

        updateOptionText();
    }

    return true;
}

void MenuState::updateOptionText()
{
    if (m_options.empty())
            return;

    // White all texts
    for(sf::Text& text: m_options)
            text.setColor(sf::Color::White);

    // Red the selected text
    m_options[m_optionIndex].setColor(sf::Color::Red);
}
