#include <iostream>
#include <fstream>

#include <opencv2/opencv.hpp>
#include <opencv2/ml.hpp>
#include <arpa/inet.h>

using namespace cv;
using namespace cv::ml;
using namespace std;

void load_mnist(const std::string& images_path, const std::string& labels_path, Mat& images, Mat& labels) 
{
    ifstream imageFile(images_path, ios::binary);
    ifstream labelFile(labels_path, ios::binary);

    if (!imageFile.is_open() || !labelFile.is_open())
    {
        cerr << "Ошибка открытия файлов MNIST!" << endl;
        exit(1);
    }

    int magicNumber, numberOfImages, numberOfRows, numberOfCols;
    int labelMagicNumber, numberOfLabels;

    imageFile.read((char*)&magicNumber, sizeof(magicNumber));
    magicNumber = ntohl(magicNumber);
    
    imageFile.read((char*)&numberOfImages, sizeof(numberOfImages));
    numberOfImages = ntohl(numberOfImages);

    imageFile.read((char*)&numberOfRows, sizeof(numberOfRows));
    numberOfRows = ntohl(numberOfRows);

    imageFile.read((char*)&numberOfCols, sizeof(numberOfCols));
    numberOfCols = ntohl(numberOfCols);

    labelFile.read((char*)&labelMagicNumber, sizeof(labelMagicNumber));
    labelMagicNumber = ntohl(labelMagicNumber);

    labelFile.read((char*)&numberOfLabels, sizeof(numberOfLabels));
    numberOfLabels = ntohl(numberOfLabels);

    if (numberOfImages != numberOfLabels)
    {
        cerr << "Количество изображений и меток не совпадает!" << endl;
        exit(1);
    }

    images = Mat(numberOfImages, numberOfRows * numberOfCols, CV_32F);
    labels = Mat(numberOfImages, 1, CV_32SC1);

    for (int i = 0; i < numberOfImages; i++) 
    {
        unsigned char label;
        labelFile.read((char*)&label, sizeof(label));
        labels.at<int>(i, 0) = (int)label;

        for (int j = 0; j < numberOfRows * numberOfCols; j++) 
        {
            unsigned char pixel;
            imageFile.read((char*)&pixel, sizeof(pixel));
            images.at<float>(i, j) = (float)pixel / 255.0f;
        }
    }

    imageFile.close();
    labelFile.close();
}

void train_neural_network(const Mat& images, const Mat& labels) 
{
    Ptr<ANN_MLP> neural_net = ANN_MLP::create();
    Mat layerSizes = (Mat_<int>(1, 5) << images.cols, 256, 128, 64, 10);                            // Количество слоев и нейронов задаем здесь

    neural_net->setLayerSizes(layerSizes);
    neural_net->setActivationFunction(ANN_MLP::SIGMOID_SYM, 1.0, 1.0);
    neural_net->setTrainMethod(ANN_MLP::BACKPROP, 0.01, 0.1);

    Mat oneHotLabels = Mat::zeros(labels.rows, 10, CV_32F);
    for (int i = 0; i < labels.rows; i++) 
    {
        oneHotLabels.at<float>(i, labels.at<int>(i, 0)) = 1.0f;
    }

    Ptr<TrainData> trainData = TrainData::create(images, ROW_SAMPLE, oneHotLabels);

    int epochs = 100;                                                                               // Здесь задаем количество эпох

    for (int i = 0; i < epochs; i++) 
    {
        neural_net->train(trainData);
        cout << "Эпоха " << (i + 1) << " завершена!" << endl;
    }

    neural_net->save("increased_epochs_mnist_model.xml");                                           // Обученная модель сохраняется в указанном в аргументе файле

    cout << "Модель успешно обучена и сохранена в increased_epochs_mnist_model.xml!" << endl;
}

int main() 
{
    Mat trainingImages, trainingLabels;

    load_mnist("../models/train-images.idx3-ubyte", "../models/train-labels.idx1-ubyte", trainingImages, trainingLabels);

    cout << "Данные загружены, обучение запущено" << endl;

    train_neural_network(trainingImages, trainingLabels);

    cout << "Завершено обучение нейронной сети!" << endl;

    return 0;
}
