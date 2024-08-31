#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    string videoPath = "/home/five/opencv_1/build/test.mp4"; // 定义视频文件的路径

    VideoCapture cap(videoPath); // 使用VideoCapture类打开视频文件

    if (!cap.isOpened()) { // 检查视频是否成功打开
        cout << "Error opening video file at path: " << videoPath << endl;
        return -1;
    }

    Mat frame, gray, binary;
    for (;;) { // 无限循环，直到视频结束或用户退出
        cap.read(frame); // 从视频流中读取下一帧

        if (frame.empty()) { // 如果读取的帧为空，说明视频已经结束
            break;
        }

        cvtColor(frame, gray, COLOR_BGR2GRAY); // 将当前帧转换为灰度图像
        threshold(gray, binary, 127, 255, THRESH_BINARY); // 对灰度图像进行二值化处理

        vector<vector<Point>> contours; // 用于存储轮廓点的向量
        findContours(binary, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE); // 寻找二值化图像中的轮廓

        for (auto& contour : contours) { // 遍历所有轮廓
            if (contourArea(contour) > 100) { // 过滤掉面积较小的轮廓
                RotatedRect rrect = minAreaRect(contour); // 对过滤后的轮廓，找到最小包围旋转矩形

                Point2f vertices[4];
                rrect.points(vertices); // 获取旋转矩形的四个顶点

                for (int i = 0; i < 4; i++) { // 绘制旋转矩形
                    line(frame, vertices[i], vertices[(i + 1) % 4], Scalar(0, 255, 0), 2);
                }
            }
        }

        imshow("Video Stream", frame); // 显示处理后的视频帧

        if (waitKey(10) == 'q') { // 等待10毫秒，如果按下'q'键，则退出循环
            break;
        }
    }

    cap.release(); // 释放视频流
    destroyAllWindows(); // 关闭所有OpenCV创建的窗口

    return 0; // 程序正常退出，返回0
}
