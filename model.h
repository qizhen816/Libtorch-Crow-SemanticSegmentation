#ifndef INFER_H // To make sure you don't declare the function more than once by including the header multiple times. 
#define INFER_H
#include <torch/torch.h> 
#include <torch/script.h> 

#include <iostream> 
#include <vector>
#include <string>

#include <opencv2/imgcodecs.hpp> 
#include <opencv2/highgui.hpp> 
#include <opencv2/core/core.hpp> 
#include <opencv2/opencv.hpp>


std::tuple<std::string, std::string> infer(
cv::Mat,
torch::jit::script::Module);

#endif
