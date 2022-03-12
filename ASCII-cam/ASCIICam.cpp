//
//  ASCIICam.cpp
//  ASCII-cam
//
//  Created by Stephen Jaud on 12/3/2022.
//

#include "ASCIICam.hpp"

ASCIICam::ASCIICam()
{
    threshold = 0;
    
    m_vc.open(0);
    if (!m_vc.isOpened()) {
        std::cout << "[error] Impossible to open cam" << std::endl;
        exit(1);
    }
    
    m_source_width = static_cast<uint32_t>(m_vc.get(cv::CAP_PROP_FRAME_WIDTH));
    m_source_height = static_cast<uint32_t>(m_vc.get(cv::CAP_PROP_FRAME_HEIGHT));
    
    m_target_width  = m_source_width;
    m_target_height = m_source_height;
    
    m_scale = 1.0f;
    m_ratio = static_cast<float>(m_source_height) / static_cast<float>(m_source_width);
}

void ASCIICam::setDimension(uint32_t target_width)
{
    m_target_width  = target_width;
    m_target_height = m_ratio * target_width;
    
    m_scale = static_cast<float>(m_target_width) / static_cast<float>(m_source_width);
}

void ASCIICam::increaseThreshold() {
    threshold++;
    palette.push_back(' ');
}

void ASCIICam::decreaseThreshold() {
    if (threshold > 0)
    {
        threshold--;
        palette.pop_back();
    }
}

void ASCIICam::grab(std::string & str_frame)
{
    str_frame.clear();
    
    cv::Mat frame1, frame2;
    m_vc >> frame1;
    
    cv::cvtColor(frame1, frame2, cv::COLOR_RGB2GRAY);
    cv::resize(frame2, frame1, cv::Size(), m_scale, m_scale);
    cv::flip(frame1, frame2, 1);
    
    for (int i = 0; i < frame2.rows; i++) {
    for (int j = 0; j < frame2.cols; j++) {
        float pixel_value   = static_cast<float>(frame2.at<uchar>(i, j));
        int index           = static_cast<int>(linearInterpolation(0, palette.size()-1, 255.0f, .0f, pixel_value));
        
        str_frame.push_back(palette[index]);
    }
        str_frame.push_back('\n');
    }
    
    str_frame.pop_back();
}

void ASCIICam::close()
{
    m_vc.release();
}

float ASCIICam::linearInterpolation(float target_min, float target_max, float source_min, float source_max, float x)
{
    return target_min + (x - source_min)/(source_max - source_min) * (target_max - target_min);
}
