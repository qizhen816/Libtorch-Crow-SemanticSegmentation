# Libtorch-Crow-SemanticSegmentation
A C++ web micro server processing image from Json and return results.

# Environment
1. Download [libtorch](https://pytorch.org/get-started/locally/) from PyTorch Website
 or using wget https://download.pytorch.org/libtorch/cpu/libtorch-shared-with-deps-latest.zip.
```bash
unzip libtorch-shared-with-deps-latest.zip 
```

2. Opencv and Boost. We recommed a [docker image with opencv](https://www.learnopencv.com/install-opencv-docker-image-ubuntu-macos-windows/).
```bash
sudo apt-get install libboost-all-dev
```

3. A pytorch model file end with "*.pt". This can be easily get by follow the [Tutorial](https://pytorch.org/tutorials/advanced/cpp_export.html#loading-a-pytorch-model-in-c) 

Attention: this repository uses a semantic segmentation model and returns a CV::Mat format matrix,
remember to modify the postprocess code in [model.cpp](model.cpp)

4. Modify the [CMakeLists](CMakeLists.txt) file according to your need.

5. Run the build code and start server:
```bash
cd build 
cmake ..
make
```
You can test using the [python code](test_port.py).
Remember to set the port right or the port mapping if using docker.