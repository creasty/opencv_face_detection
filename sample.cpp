#include <iostream>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv/cxcore.h>

#define WIN_NAME "Image"

#define HEIGHT 500
#define WIDTH  500


int main(int argc, char **argv)
{
  CvHaarClassifierCascade* cascade = (CvHaarClassifierCascade *)cvLoad("data/haarcascade_frontalface_default.xml");

  if (!cascade) {
    return -1;
  }

  CvMemStorage* storage = cvCreateMemStorage(0);

  CvSeq* faces;
  CvRect *face;
  IplImage *frame;

  CvCapture *capture = cvCreateCameraCapture(0);
  cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH, WIDTH);
  cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT, HEIGHT);

  int i;

  cvNamedWindow(WIN_NAME, CV_WINDOW_AUTOSIZE);

  while (1) {
    frame = cvQueryFrame(capture);

    faces = cvHaarDetectObjects(
      frame,
      cascade,
      storage,
      1.1,
      3,
      0
    );

    for (i = 0; i < faces->total; ++i) {
      face = (CvRect *)cvGetSeqElem(faces, i);

      cvRectangle(
        frame,
        cvPoint(face->x, face->y),
        cvPoint(face->x + face->width, face->y + face->height),
        CV_RGB(255, 0, 0),
        3
      );
    }

    cvShowImage(WIN_NAME, frame);

    if ('q' == cvWaitKey(10)) {
      break;
    }
  }

  cvReleaseImage(&frame);
  cvReleaseMemStorage(&storage);
  cvReleaseHaarClassifierCascade(&cascade);

  cvDestroyWindow(WIN_NAME);

  return 0;
}
