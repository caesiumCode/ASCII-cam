//
//  Program.hpp
//  ASCII-cam
//
//  Created by Stephen Jaud on 12/3/2022.
//

#ifndef Program_hpp
#define Program_hpp

#include <iostream>
#include <SFML/Graphics.hpp>

#include "ASCIICam.hpp"

class Program {
public:
    Program(uint32_t);
    
    void run();
    
private:
    const float WINDOW_WIDTH = 1500;
    
    sf::RenderWindow    m_window;
    ASCIICam            m_ascii_cam;
    
    std::string m_ascii_frame;
    sf::Text    m_ascii_drawable;
    
    sf::Font m_ascii_font;
    
    void message(std::string);
};

#endif /* Program_hpp */
