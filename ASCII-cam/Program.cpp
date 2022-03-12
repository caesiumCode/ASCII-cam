//
//  Program.cpp
//  ASCII-cam
//
//  Created by Stephen Jaud on 12/3/2022.
//

#include "Program.hpp"

Program::Program(uint32_t w)
{
    m_ascii_cam.setDimension(w);
    m_ascii_cam.grab(m_ascii_frame);
    
    m_ascii_font.loadFromFile("SpaceMono-Regular.ttf");
    m_ascii_drawable.setFont(m_ascii_font);
    m_ascii_drawable.setLineSpacing(0.6f);
    m_ascii_drawable.setLetterSpacing(1.5f);
    m_ascii_drawable.setFillColor(sf::Color::White);
    m_ascii_drawable.setString(m_ascii_frame);
    sf::FloatRect ascii_frame_bounds = m_ascii_drawable.getGlobalBounds();
    
    
    float ratio_hw = ascii_frame_bounds.height / ascii_frame_bounds.width;
    m_window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_WIDTH * ratio_hw), "ASCII cam");
    
    float window_width = m_window.getSize().x, window_height = m_window.getSize().y;
    m_ascii_drawable.setScale(window_width/ascii_frame_bounds.width,
                              window_height/ascii_frame_bounds.height);
    m_ascii_drawable.setPosition(0, -ascii_frame_bounds.top);
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
