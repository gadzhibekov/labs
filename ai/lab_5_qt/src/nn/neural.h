#ifndef NEURAL
#define NEURAL

#include <opencv2/opencv.hpp>
#include <opencv2/ml.hpp>
#include <arpa/inet.h>

using namespace cv;
using namespace cv::ml;
using namespace std;

struct Neural
{
    static void load_data_from_mnist(const std::string& images_path, const std::string& labels_path, Mat& images, Mat& labels);
    static void train_neural_network(const Mat& images, const Mat& labels);
    static void begin_training();
    static Mat  preprocess_image(const Mat& image);
    static Mat  vector_to_mat(const std::vector<std::vector<int>>& inputVector);
};

#endif // NEURAL