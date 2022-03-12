//
//  Program.cpp
//  ASCII-cam
//
//  Created by Stephen Jaud on 12/3/2022.
//

#include "Program.hpp"

Program::Program(uint32_t w)
{
    // setup cam
    m_ascii_cam.setDimension(w);
    m_ascii_cam.grab(m_ascii_frame, true);
    
    // setup ascii frame
    m_ascii_font.loadFromFile("SpaceMono-Regular.ttf");
    m_ascii_drawable.setFont(m_ascii_font);
    m_ascii_drawable.setLineSpacing(0.6f);
    m_ascii_drawable.setLetterSpacing(1.5f);
    m_ascii_drawable.setFillColor(sf::Color::White);
    m_ascii_drawable.setString(m_ascii_frame);
    
    sf::FloatRect ascii_frame_bounds = m_ascii_drawable.getLocalBounds();
    
    // Find the optimal character size
    int character_size = 1;
    m_ascii_drawable.setCharacterSize(character_size);
    ascii_frame_bounds = m_ascii_drawable.getLocalBounds();
    
    while (ascii_frame_bounds.width <= WINDOW_WIDTH) {
        character_size *= 2;
        m_ascii_drawable.setCharacterSize(character_size);
        ascii_frame_bounds = m_ascii_drawable.getLocalBounds();
    }
    character_size /= 2;
    m_ascii_drawable.setCharacterSize(character_size);
    ascii_frame_bounds = m_ascii_drawable.getLocalBounds();
    
    while (ascii_frame_bounds.width <= WINDOW_WIDTH) {
        character_size++;
        m_ascii_drawable.setCharacterSize(character_size);
        ascii_frame_bounds = m_ascii_drawable.getLocalBounds();
    }
    character_size--;
    m_ascii_drawable.setCharacterSize(character_size);
    ascii_frame_bounds = m_ascii_drawable.getLocalBounds();
    
    // setup window
    m_window.create(sf::VideoMode(ascii_frame_bounds.width, ascii_frame_bounds.height), "ASCII cam");
    
    // position the ascii frame
    m_ascii_drawable.setOrigin(ascii_frame_bounds.left + ascii_frame_bounds.width/2.0f,
                               ascii_frame_bounds.top + ascii_frame_bounds.height/2.0f);
    m_ascii_drawable.setPosition(0.5f * static_cast<sf::Vector2f>(m_window.getSize()));
}

void Program::run()
{
    while (m_window.isOpen())
    {
        sf::Event event;
        while (m_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) m_window.close();
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Up) m_ascii_cam.increaseThreshold();
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Down) m_ascii_cam.decreaseThreshold();
        }
        
        m_ascii_cam.grab(m_ascii_frame);
        m_ascii_drawable.setString(m_ascii_frame);
        
        m_window.clear(sf::Color::Black);
        
        m_window.draw(m_ascii_drawable);
        
        m_window.display();
    }
    
    m_ascii_cam.close();
}

void Program::message(std::string msg)
{
    std::cout << msg << std::endl;
}
