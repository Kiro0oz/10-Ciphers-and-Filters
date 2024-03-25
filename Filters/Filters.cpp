
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
    cout << "Please Enter the name of the new filtered image \n";
    cout << "& specify extension .jpg, .bmp, .png, .tga: ";
    string new_fileName;
    cin >> new_fileName;
    img.saveImage(new_fileName);

}
void FlipH() {
    // Read Image
    cout << "Enter the name of the image (with extensions) you want to flip horizontally: ";
    string filename;
    cin >> filename;
    Image img(filename);

    for (int i = 0; i < img.width / 2; i++) { 
        for (int j = 0; j < img.height; j++) {
            for (int k = 0; k < img.channels; k++) {
                // Swap pixels horizontally
                unsigned int temp = img(i, j, k);
                img(i, j, k) = img(img.width - 1 - i, j, k);
                img(img.width - 1 - i, j, k) = temp;
            }
        }
    }

    // Save Image
    cout << "Please Enter the name of the new flipped image \n";
    cout << "& specify extension .jpg, .bmp, .png, .tga: ";
    string new_fileName;
    cin >> new_fileName;
    img.saveImage(new_fileName);
}

void FlipV() {
    // Read Image
    cout << "Enter the name of the image (with extensions) you want to flip vertically: ";
    string filename;
    cin >> filename;
    Image img(filename);

    for (int i = 0; i < img.width; i++) {
        for (int j = 0; j < img.height / 2; j++) {
            for (int k = 0; k < img.channels; k++) {
                // Swap pixels vertically
                unsigned int temp = img(i, j, k);
                img(i, j, k) = img(i, img.height - 1 - j, k);
                img(i, img.height - 1 - j, k) = temp;
            }
        }
    }

    // Save Image
    cout << "Please Enter the name of the new flipped image \n";
    cout << "& specify extension .jpg, .bmp, .png, .tga: ";
    string new_fileName;
    cin >> new_fileName;
    img.saveImage(new_fileName);
}
void Flip(){

    cout<<"1.Horizontally"<<endl<<"2.Vertically"<<endl;
    int n;
    cin>>n;
    if (n==1){
        FlipH();
    }
    else if (n==2){
        FlipV();
    }
    else{
        cout<<"Please Enter a valid choice..";
    }
}
// Filters options
void Filters() {
    char ch;
    cout << "1) Gray Scale Filter\n";
    cout << "2) Black & White Filter\n";
    cout << "3) Flip image Filter\n";
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
        else if (ch == '3'){
            Flip();
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
            cout << "Bye!!";
            break;
        } else {
            cout << "Error! Please insert a valid option\n";
            continue;
        }

    }

    return 0;
}
