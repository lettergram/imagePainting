imagePainting
======

Converts an image into a painting

### Requirements 

* I highly recommend a computer with decent hardware, as these caluclations can take some time. 

* OpenCV: http://opencv.org/downloads.html
* To install (on OSX or Linux):
  1. Installed CMake
  2. tar xjf OpenCV-2.3.1a.tar.bz2
  3. cd OpenCV-2.3.1
  4. cmake -DCMAKE_INSTALL_PREFIX=/usr .
  5. make
  6. sudo make install

* Use jpg2png.cpp to test OpenCV install (review source if you have trouble with compiling/executing)

* To Compile: g++ -I/usr/include -L/usr/lib -lopencv_core.2.4.9 -lopencv_calib3d.2.4.9 -lopencv_imgproc.2.4.9 -lopencv_highgui.2.4.9 <File Name>.cpp -o <Executable>
