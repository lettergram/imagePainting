#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdlib.h>
#include <stdio.h>

// To Execute: ./paint ../images/test.jpg 0 - 9 merge

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
       **/
      
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
      
      
      /**
       *  Paints little boxes, should change to make a bit better
       **/
      for(int k = 0; k < step; k++){
        for(int s = 0; s < step; s++){
          if((*img.ptr<Point3_<uchar> >(i + k, j + s)).x == 0){
            (*img.ptr<Point3_<uchar> >(i + k, j + s)).x = r;
            (*img.ptr<Point3_<uchar> >(i + k, j + s)).y = g;
            (*img.ptr<Point3_<uchar> >(i + k, j + s)).z = b;
          }else{
            (*img.ptr<Point3_<uchar> >(i + k, j + s)).x = ((*img.ptr<Point3_<uchar> >(i + k, j + s)).x);//*2+ r) / 3;
            (*img.ptr<Point3_<uchar> >(i + k, j + s)).y = ((*img.ptr<Point3_<uchar> >(i + k, j + s)).y);//*2+ g) / 3;
            (*img.ptr<Point3_<uchar> >(i + k, j + s)).z = ((*img.ptr<Point3_<uchar> >(i + k, j + s)).z);//*2+ b) / 3;
          }
        }
      }
    }
  }
  
  return paintImg;
}

/** @function main */
int main( int argc, char** argv )
{
  /// Load an image
  src = imread( argv[1] );
  int overlay = 10;
  if(argc > 1){
    overlay = *argv[2] - '0';
  }
  
  if( !src.data )
  { return -1; }
  
  /// Create a matrix of the same type and size as src (for dst)
  dst.create( src.size(), src.type() );
  
  /// Convert the image to grayscale
  cvtColor( src, src_gray, CV_BGR2GRAY );
  
  /// Reduce noise with a kernel 3x3
  blur( src_gray, detected_edges, Size(3,3) );
  
  /// Canny detector
  Canny( detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size );
  
  /// Using Canny's output as
  dst = Scalar::all(0);
  
  src.copyTo( dst, detected_edges);
  
  wait(0);
  
  imwrite("../images/edges.jpg", dst);
  imwrite("../images/painted.jpg", paintBetweenEdges(dst, overlay));
  
  return 0;
}
