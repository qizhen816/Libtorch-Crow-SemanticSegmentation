#include <iostream>
#include <opencv2/opencv.hpp> 
#include <string>

#include "crow.h"
#include "model.h"
 
#include "base64.h"


int main() {
	torch::jit::script::Module module = torch::jit::load("/libtoorch/mm.pt");
	crow::SimpleApp app;

	CROW_ROUTE(app, "/predict").methods("POST"_method, "GET"_method)
	([&module](const crow::request& req){     
	crow::json::wvalue result;     
	result["Prediction"] = "0";     
	result["Confidence"] = "0";     
	result["Status"] = "Failed";     
	std::ostringstream os;      

	try {       
		auto args = crow::json::load(req.body);        
		// Get Image       
		std::string base64_image = args["image"].s(); 
		std::string decoded_image = base64_decode(base64_image);       
		
		std::vector<uchar> image_data(decoded_image.begin(), decoded_image.end());       
		cv::Mat image = cv::imdecode(image_data, cv::IMREAD_UNCHANGED);
		        
		// Predict       
		std::string pred, ok; 
		tie(pred, ok) = infer(image, module);
		
		const unsigned char* c = (const unsigned char*)(const_cast<char*>(pred.c_str()));        
		result["Prediction"] = base64_encode(c, pred.size());       
		result["Confidence"] = ok;
		       
		result["Status"] = "Success";        
		os << crow::json::dump(result);       
		return crow::response{os.str()};      
	} catch (std::exception& e){       
		os << crow::json::dump(result);       
		return crow::response(os.str());     
	}  
	});	
      
	app.port(5000).multithreaded().run(); 
}
