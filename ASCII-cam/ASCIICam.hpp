//
//  ASCIICam.hpp
//  ASCII-cam
//
//  Created by Stephen Jaud on 12/3/2022.
//

#ifndef ASCIICam_hpp
#define ASCIICam_hpp

#include <iostream>

#include <opencv2/videoio.hpp>
#include <opencv2/imgproc.hpp>

class ASCIICam {
public:
    ASCIICam();
    
    void setDimension(uint32_t);
    void increaseThreshold();
    void decreaseThreshold();
    void grab(std::string &);
    void close();
    
private:
    std::string palette = "@#W$9876543210?!abc;:+=-,._ ";
    int threshold;
    
    cv::VideoCapture m_vc;
    
    uint32_t m_source_width, m_source_height;
    uint32_t m_target_width, m_target_height;
    float m_scale, m_ratio;
    
    float linearInterpolation(float, float, float, float, float);
};

#endif /* ASCIICam_hpp */
