/**
 *
 * Example showing how to read and write images
 * Taken and updated from: http://tilomitra.com/opencv-on-mac-osx/
 * Modified: 9/26/2014
 * Editor: Austin Walters
 *
 * Description:
 *    
 *    Used to test OpenCV is properly installed, to install OpenCV:
 *
 *      1. Installed CMake
 *      2. tar xjf OpenCV-2.v.v.tar.bz2
 *      3. cd OpenCV-2.v.v
 *      4. cmake -DCMAKE_INSTALL_PREFIX=/usr .
 *      5. make
 *      6. sudo make install
 *
 * To Compile:
 *     g++ -I/usr/include -L/usr/lib -lopencv_core.2.4.9 -lopencv_calib3d.2.4.9 -lopencv_imgproc.2.4.9 -lopencv_highgui.2.4.9 jpg2png.cpp -o jpg2png
 * 
 * To Execute:
 *     ./jpg2png
 *
 */
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

int main(int argc, char** argv)
{
  IplImage * pInpImg = 0;

  // Load an image from file - change this based on your image name
  pInpImg = cvLoadImage("images/test.jpg", CV_LOAD_IMAGE_UNCHANGED);
  if(!pInpImg)
    {
      fprintf(stderr, "failed to load input image\n");
      return -1;
    }

  // Write the image to a file with a different name,
  // using a different image format -- .png instead of .jpg
  if( !cvSaveImage("images/test_copy.png", pInpImg) )
    {
      fprintf(stderr, "failed to write image file\n");
    }

  // Remember to free image memory after using it!
  cvReleaseImage(&pInpImg);

  return 0;
}
