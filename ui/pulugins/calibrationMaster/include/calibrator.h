#ifndef CALIBRATOR_H
#define CALIBRATOR_H

#include <opencv2/opencv.hpp>
#include <vector>

class Calibrator {
  public:
    enum ThreshodMethod { OTSU = 0, ADAPTED };
    Calibrator();
    virtual ~Calibrator();
    inline void emplace(const cv::Mat &img) { m_imgs.emplace_back(img); }
    inline void erase(const int index) { m_imgs.erase(m_imgs.begin() + index); }
    inline const std::vector<std::vector<cv::Point2f>> &imgPoints() {
        return m_imgPoints;
    }
    inline const std::vector<std::vector<cv::Point3f>> &worldPoints() {
        return m_worldPoints;
    }
    inline const std::vector<cv::Mat> &imgs() { return m_imgs; }
    inline cv::Size imgSize() {
        return m_imgs.empty() ? cv::Size(0, 0) : m_imgs[0].size();
    }
    virtual void setDistance(const float trueDistance) = 0;
    virtual void setRadius(const std::vector<float> &radius) = 0;
    virtual bool
    findFeaturePoints(const cv::Mat &img, const cv::Size &featureNums,
                      std::vector<cv::Point2f> &points,
                      const ThreshodMethod threshodType = ADAPTED) = 0;
    // TODO(@Liu Yunhuang):暂未用到blobBlack
    virtual double calibrate(const std::vector<cv::Mat> &imgs,
                             cv::Mat &intrinsic, cv::Mat &distort,
                             const cv::Size &featureNums, float &process,
                             const ThreshodMethod threshodType = ADAPTED,
                             const bool blobBlack = true) = 0;

  protected:
    std::vector<cv::Mat> m_imgs;
    std::vector<std::vector<cv::Point2f>> m_imgPoints;
    std::vector<std::vector<cv::Point3f>> m_worldPoints;

  private:
};

#endif
