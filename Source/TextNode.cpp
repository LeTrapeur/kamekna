#include "textnode.h"

TextNode::TextNode(const FontHolder& fonts, const std::string& text)
{
    m_text.setFont(fonts.get(Fonts::Main));
    m_text.setCharacterSize(20);
    setString(text);
}

void TextNode::drawCurrent (sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_text, states);
}

void TextNode::setString(const std::string& text)
{
    m_text.setString(text);
    sf::FloatRect bounds = m_text.getLocalBounds();
    m_text.setOrigin(std::floor(bounds.width / 2.f), std::floor(bounds.height / 2.f));
}
