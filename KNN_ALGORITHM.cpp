#include <iostream>
#include <fstream> // استخدمها لما احب اقرأ ملف
#include <sstream> // string استخدمها لما احب اقطع 
#include <cmath>

using namespace std;

struct point{
    double features[7]; //السبع عواميد
    int label; //target
};

// دالة لحساب المسافة بين نقطتين
double distance(double a[], double b[], int size){
    double sum = 0;
    for(int i = 0; i < size; i++){
        sum += pow(a[i] - b[i], 2);
    }
    return sqrt(sum);
}

int main() {
    const int numRows = 14;
    point data[numRows];

    // قراءة البيانات من ملف CSV
    ifstream file("BankDataAfterEncoding.csv");
    string line;
    getline(file, line); // تخطي الصف الأول (رؤوس الأعمدة)
    int index = 0;

    while (getline(file, line) && index < numRows) {
        stringstream ss(line);
        string value;
        for (int j = 0; j < 7; j++) {
            getline(ss, value, ',');
            data[index].features[j] = stod(value);
        }
        getline(ss, value, ',');
        data[index].label = stoi(value);
        index++;
    }
    file.close();

    //normalization
    double min_values[7];
    double max_values[7];
    for (int j = 0; j < 7; j++) {
        min_values[j] = data[0].features[j];
        max_values[j] = data[0].features[j];
        for (int i = 1; i < numRows; i++) {
            if (data[i].features[j] < min_values[j]) min_values[j] = data[i].features[j];
            if (data[i].features[j] > max_values[j]) max_values[j] = data[i].features[j];
        }
    }


    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < 7; j++) {
            if (max_values[j] == min_values[j]) {
                data[i].features[j] = 0;
            } else {
                data[i].features[j] = (data[i].features[j] - min_values[j]) / (max_values[j] - min_values[j]);
            }
        }
    }

    // تعريف نقطة الاختبار
    double testPoint[7] = {35, 3, 8000, 36, 500, 1, 0};


    for (int j = 0; j < 7; j++) {
        if (max_values[j] == min_values[j]) {
            testPoint[j] = 0;
        } else {
            testPoint[j] = (testPoint[j] - min_values[j]) / (max_values[j] - min_values[j]);
        }
    }

    // حساب المسافات بين نقطة الاختبار وجميع نقاط البيانات
    double distances[numRows];
    int labels[numRows];
    for (int i = 0; i < numRows; i++) {
        distances[i] = distance(data[i].features, testPoint, 7);
        labels[i] = data[i].label;
    }

    // فرز المسافات والتسميات (باستخدام bubble sort)
    for (int i = 0; i < numRows - 1; i++) {
        for (int j = i + 1; j < numRows; j++) {
            if (distances[i] > distances[j]) {
                swap(distances[i], distances[j]);
                swap(labels[i], labels[j]);
            }
        }
    }


    int k = 3;
    int countYes = 0;
    int countNo = 0;
    for (int i = 0; i < k; i++) {
        if (labels[i] == 1) countYes++;
        else countNo++;
    }


    cout << (countYes > countNo ? "Prediction: 1 (Approved)" : "Prediction: 0 (Rejected)") << endl;

    return 0;
}