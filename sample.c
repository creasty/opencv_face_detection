#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv/cxcore.h>

#define WIN_NAME "Image"

int main(int argc, char **argv)
{
  IplImage *src_img = cvLoadImage("images/lenna.png", CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_ANYCOLOR);

  if (!src_img) {
    return -1;
  }

  CvHaarClassifierCascade* cascade = (CvHaarClassifierCascade *)cvLoad("data/haarcascade_frontalface_default.xml", NULL, NULL, NULL);

  if (!cascade) {
    return -1;
  }

  CvMemStorage* storage = cvCreateMemStorage(0);
  CvSeq* faces = cvHaarDetectObjects(
    src_img,
    cascade,
    storage,
    1.1,
    3,
    0,
    cvSize(0, 0),
    cvSize(0, 0)
  );

  int i;
  CvRect *face;

  for (i = 0; i < faces->total; ++i) {
    face = (CvRect *)cvGetSeqElem(faces, i);

    cvRectangle(
      src_img,
      cvPoint(face->x, face->y),
      cvPoint(face->x + face->width, face->y + face->height),
      CV_RGB(255, 0, 0),
      3,
      8,
      0
    );
  }

  cvReleaseMemStorage(&storage);
  cvReleaseHaarClassifierCascade(&cascade);

  cvNamedWindow(WIN_NAME, CV_WINDOW_AUTOSIZE);
  cvShowImage(WIN_NAME, src_img);
  cvWaitKey(0);

  cvDestroyWindow(WIN_NAME);
  cvReleaseImage(&src_img);

  return 0;
}
