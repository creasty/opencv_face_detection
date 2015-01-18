#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv/cxcore.h>

#define WIN_NAME "Image"

int main(int argc, char **argv)
{
  IplImage *src_img = cvLoadImage("images/lenna.png", CV_LOAD_IMAGE_GRAYSCALE);

  if (src_img == 0) {
    return -1;
  }

  IplImage *edge_img = cvCreateImage(cvGetSize(src_img), IPL_DEPTH_8U, 1);
  cvCanny(src_img, edge_img, 64, 128, 3);

  cvNamedWindow(WIN_NAME, CV_WINDOW_AUTOSIZE);
  cvShowImage(WIN_NAME, edge_img);
  cvWaitKey(0);

  cvDestroyWindow(WIN_NAME);
  cvReleaseImage(&src_img);

  return 0;
}
