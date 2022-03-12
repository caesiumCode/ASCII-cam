//
//  main.cpp
//  ASCII-cam
//
//  Created by Stephen Jaud on 12/3/2022.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/imgproc.hpp>
#include "Program.hpp"

int main(int argc, const char * argv[]) {
    Program program(80);
    
    program.run();
    
    return EXIT_SUCCESS;
}
