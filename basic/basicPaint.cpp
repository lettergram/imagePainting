#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdlib.h>
#include <stdio.h>

using namespace cv;

/// Global variables

Mat src, src_gray;
Mat dst, detected_edges;

int edgeThresh = 1;
int lowThreshold;
int const max_lowThreshold = 100;
int ratio = 3;
int kernel_size = 3;
char* window_name = "Edge Map";

/**
 * @function Paint between edges
 *
 */
Mat paintBetweenEdges(Mat &img, int step){

  Mat paintImg(img);
  
  for( int i = 0; i < img.rows - step/2 + 1; i += step - step/2 + 1){
    for(int j = 0; j < img.cols - step/2; j += step - step/2 + 1){
      
      int r = 130;
      int g = 130;
      int b = 130;
      
      int rcount = 1;
      int gcount = 1;
      int bcount = 1;
      
      /**
       * Should check if lines are vertical or horizontal and paint
       * similar to those lines.
       */
      
      /* Find average colors of step */
      for(int k = 0; k < step; k++){
        for(int s = 0; s < step; s++){
          
          if((*img.ptr<Point3_<uchar> >(i + k, j + s)).x > 0){
            r += (*img.ptr<Point3_<uchar> >(i + k, j + s)).x;
            rcount++;
          }
          if((*img.ptr<Point3_<uchar> >(i + k, j + s)).y > 0){
            g += (*img.ptr<Point3_<uchar> >(i + k, j + s)).y;
            gcount++;
          }
          if((*img.ptr<Point3_<uchar> >(i + k, j + s)).z > 0){
            b += (*img.ptr<Point3_<uchar> >(i + k, j + s)).z;
            bcount++;
          }
        }
        
      }
      
      r = r / rcount;
      g = g / gcount;
      b = b / bcount;
      
      for(int k = 0; k < step; k++){
        for(int s = 0; s < step; s++){
          if((*img.ptr<Point3_<uchar> >(i + k, j + s)).x == 0){
            (*img.ptr<Point3_<uchar> >(i + k, j + s)).x = r;
            (*img.ptr<Point3_<uchar> >(i + k, j + s)).y = g;
            (*img.ptr<Point3_<uchar> >(i + k, j + s)).z = b;
          }else{
            (*img.ptr<Point3_<uchar> >(i + k, j + s)).x = (r + (*img.ptr<Point3_<uchar> >(i + k, j + s)).x) / 2;
            (*img.ptr<Point3_<uchar> >(i + k, j + s)).y = (g + (*img.ptr<Point3_<uchar> >(i + k, j + s)).y) / 2;
            (*img.ptr<Point3_<uchar> >(i + k, j + s)).z = (b + (*img.ptr<Point3_<uchar> >(i + k, j + s)).z) / 2;
          }
        }
      }
    }
  }
  
  return paintImg;
}

/**
 * @function CannyThreshold
 * @brief Trackbar callback - Canny thresholds input with a ratio 1:3
 */
void CannyThreshold(int, void*)
{
  /// Reduce noise with a kernel 3x3
  blur( src_gray, detected_edges, Size(3,3) );
  
  /// Canny detector
  Canny( detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size );
  
  /// Using Canny's output as a mask, we display our result
  dst = Scalar::all(0);
  
  src.copyTo( dst, detected_edges);
  imshow( window_name, dst );
}


/** @function main */
int main( int argc, char** argv )
{
  /// Load an image
  src = imread( argv[1] );
  
  if( !src.data )
  { return -1; }
  
  /// Create a matrix of the same type and size as src (for dst)
  dst.create( src.size(), src.type() );
  
  /// Convert the image to grayscale
  cvtColor( src, src_gray, CV_BGR2GRAY );
  
  /// Create a window
  namedWindow( window_name, CV_WINDOW_OPENGL);
  resizeWindow( window_name, 500,500);
  
  
  /// Create a Trackbar for user to enter threshold
  createTrackbar( "Min Threshold:", window_name, &lowThreshold, max_lowThreshold, CannyThreshold );
  
  /// Show the image
  CannyThreshold(0, 0);
  
  /// Wait until user exit program by pressing a key
  waitKey(0);
  
  imwrite("../images/edges.jpg", dst);
  imwrite("../images/painted.jpg", paintBetweenEdges(dst, 10));
  
  return 0;
}
