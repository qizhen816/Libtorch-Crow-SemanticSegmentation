#include "model.h"
   
std::tuple<std::string, std::string> infer(cv::Mat image, torch::jit::script::Module module)
	{
		//cv::Mat image = cv::imread(filedir);
		cv::resize(image,image, cv::Size(512,512));
		std::cout << image.rows <<" " << image.cols <<" " << image.channels() << std::endl;
		torch::Tensor img_tensor = torch::from_blob(image.data, {1, image.rows, image.cols, 3}, torch::kByte);
		img_tensor = img_tensor.permute({0, 3, 1, 2});
		img_tensor = img_tensor.toType(torch::kFloat);
		img_tensor = img_tensor.div(255);
		torch::Tensor output = module.forward({img_tensor}).toTuple()->elements()[0].toTensor();     		   
		auto out_tensor = output.argmax(1).squeeze();        
		out_tensor = out_tensor.mul(126).to(torch::kU8);
		cv::Mat resultImg(512, 512, CV_8U);//CV_8U);
		std::memcpy((void *) resultImg.data, out_tensor.data_ptr(), sizeof(torch::kU8) * out_tensor.numel());           
		//cv::imshow("result",resultImg);
		//cv::imwrite("result.jpg",resultImg);
			
		//resultImg = (resultImg.reshape(0, 1));
		//std::cout<<sizeof(resultImg.data);		
		std::vector<unsigned char> data_encode; 	
		int res = cv::imencode(".jpg", resultImg , data_encode); 	
		std::string str_encode(data_encode.begin(), data_encode.end()); 	
		//const char* c = str_encode.c_str();
		//std::string resu(resultImg.begin<unsigned char>(), resultImg.end<unsigned char>());
		
		std::string ok = "OK";     
		return std::make_tuple(str_encode, ok);
	}	



