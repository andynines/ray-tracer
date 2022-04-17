#!/usr/bin/make

.PHONY: clean

ray-tracer: src/*.cpp include/*.hpp
	g++ main.cpp src/sceneBuilder.cpp src/htmlBuilder.cpp src/image.cpp src/fileTokenReader.cpp src/scene.cpp src/smfModel.cpp src/sphere.cpp \
	-DMAGICKCORE_QUANTUM_DEPTH=16 -DMAGICKCORE_HDRI_ENABLE=0 \
	-I include -I /usr/include/ImageMagick-6 -I /usr/include/x86_64-linux-gnu/ImageMagick-6 -I /usr/local/include \
	-lstdc++fs /usr/lib/x86_64-linux-gnu/libMagick++-6.Q16.so /usr/lib/x86_64-linux-gnu/libMagickCore-6.Q16.so /usr/lib/x86_64-linux-gnu/libMagickWand-6.Q16.so \
	-o ray-tracer \
	-O3
	
clean:
	rm -f ray-tracer
