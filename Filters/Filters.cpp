// Main file project
// Noura => [ 2, 5, 8, 11 ]
// Eman => [ 3, 6, 9, 12 ]
// Kiro => [ 1, 4, 7, 10 ]

#include <iostream>
#include "Image_Class.h"
using namespace std;


void GrayScale() {
    // Read Image
    cout << "Enter the name of the image(with extensions) you want to apply filters on : ";
    string filename;
    cin >> filename;
    Image img(filename);

    // Filter
    for (int i = 0; i < img.width; ++i)
    {
        for (int j = 0; j < img.height; ++j)
        {
            unsigned int avg = 0;
            for (int k = 0; k < img.channels; ++k)
            {
                avg += img(i, j, k);
            }
            avg /= 3;
            for (int l = 0; l < 3; ++l) {
                img(i,j,l) = avg;
            }

        }
    }

    // Save Image
    cout << "Please Enter the name of the new filtered image\n";
    cout << "& specify extension .jpg, .bmp, .png, .tga : ";
    string new_fileName;
    cin >> new_fileName;
    img.saveImage(new_fileName);
}

void Black_and_White() {
    // Read Image
    cout << "Enter the name of the image(with extensions) you want to apply filters on : ";
    string filename;
    cin >> filename;
    Image img(filename);

    // Filter
    for (int i = 0; i < img.width; ++i) {
        for (int j = 0; j < img.height; ++j) {

            unsigned int avg = 0;
            for (int k = 0; k < img.channels; ++k) {
                avg += img(i, j, k);
            }
            avg = avg / 3;
            for (int k = 0; k < 3; ++k) {
                if (avg > 127) {
                    img(i, j, k) = 255;
                } else {
                    img(i, j, k) = 0;
                }
            }
        }
    }

    // Save Image
    cout << "Please Enter the name of the new filtered image\n";
    cout << "& specify extension .jpg, .bmp, .png, .tga: ";
    string new_fileName;
    cin >> new_fileName;
    img.saveImage(new_fileName);

}

// Filters options
void Filters() {
    char ch;
    cout << "1) Gray Scale Filter\n";
    cout << "2) Black & White Filter\n";
    cout << "=> ";
    while(true) {
        cin >> ch;
        if(ch == '1') {
            GrayScale();
            break;
        } else if(ch == '2') {
            Black_and_White();
            break;
        }
        else {
            cout << "Error! Please insert a valid filter!\n";
            continue;
        }
    }

}

int main()
{
    // Menu
    cout << "=========================\n";
    cout << "Welcome to Baby Photoshop\n";
    cout << "=========================\n";
    cout << "Please choose the options: \n";
    cout << "1) Filter\n";
    cout << "2) Exit\n";
    cout << "=> ";
    char op;
    while(true) {
        cin >> op;
        if(op == '1') {
            Filters();
            break;
        } else if (op == '0') {
            cout << "Bey!!";
            break;
        } else {
            cout << "Error! Please insert a valid option\n";
            continue;
        }

    }

    return 0;
}
