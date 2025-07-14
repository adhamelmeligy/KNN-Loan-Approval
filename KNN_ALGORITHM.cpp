#include <iostream>
#include <fstream> // استخدمها لما احب اقرأ ملف
#include <sstream> // string استخدمها لما احب اقطع 
#include <cmath>
using namespace std;

struct point{
        double features[7]; //السبع عواميد
        int label; //target
};

double distance(double a[],double b[],int size){
    double sum = 0;
    for(int i = 0 ; i<size ; i++){
        sum += pow(a[i]-b[i],2);
    }
    return sqrt(sum);
}
int main() {
    const int numRows = 14;
    point data[numRows];

    ifstream file("loan_data_ready.csv");
    string line;
    getline(file, line); 

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

    //test
    double testPoint[7] = {35, 3, 8000, 36, 500, 1, 0};

    double distances[numRows];
    int labels[numRows];

    for (int i = 0; i < numRows; i++) {
        distances[i] = distance(data[i].features, testPoint, 7);
        labels[i] = data[i].label;
    }


    for (int i = 0; i < numRows - 1; i++) {
        for (int j = i + 1; j < numRows; j++) {
            if (distances[i] > distances[j]) {
                swap(distances[i], distances[j]);
                swap(labels[i], labels[j]);
            }
        }
    }

    int k = 3, countYes = 0, countNo = 0;
    for (int i = 0; i < k; i++) {
        if (labels[i] == 1) countYes++;
        else countNo++;
    }

    cout << (countYes > countNo ? "Prediction: 1 (Approved)" : "Prediction: 0 (Rejected)") << endl;

    return 0;
}