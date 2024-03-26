/*
FCAI – Structured Programming – 2024 - Assignment 3
----------------------------------------------------
File: CS112_A3_Part(1)_S17,18_20230295_20230448_20230619
Author: Kirollos Adel Samir-S17
        Noura Muhammad Mahmoud-S18
        Eman Emad Abdulrahim-S18
Emails: Kiroadel113@gmail.com
        nouraarafa180@gmail.com
        emanemadfarghaly@gmail.com
ID 1: 20230295-[ 1, 4, 7, 10 ]
ID 2: 20230448-[ 2, 5, 8, 11 ]
ID 3: 20230619-[ 3, 6, 9, 12 ]

Last update: Kiro (3/26/2024)
*/

#include <iostream>
#include "Image_Class.h"
using namespace std;

//====== Filter 1 Gray Scale ======//
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

//====== Filter 2 Black and White ======//
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

//====== Filter 3 Invert Image ======//
void Invert() {
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
            for (int k = 0; k < 3; ++k)
            {
                int num;
                num=img(i,j,k);
                img(i,j,k)=255-num;
            }
        }
    }

    // Save Image
    cout << "Please Enter the name of the new filtered image\n";
    cout << "& specify extension .jpg, .bmp, .png, .tga : ";
    string new_fileName;
    cin >> new_fileName;
    img.saveImage(new_fileName);

//====== Filter 4 Merge Images ======//
void Merge() {
    // Read Image
    string filename1,filename2;
    cout << "Enter the name of the image one (with extensions) you want to apply filters on : ";
    cin >> filename1;
    cout << "Enter the name of the image two (with extensions) you want to apply filters on : ";
    cin >> filename2;
    Image img1(filename1);
    Image img2(filename2);

    for (int i = 0; i < img1.width; ++i)
    {
        for (int j = 0; j < img1.height; ++j)
        {
            for (int k = 0; k < img1.channels; ++k)
            {
                img1(i, j, k) = (img1(i,j, k) + img2(i,j,k) ) / 2;
            }
        }
    }

    // Save Image
    cout << "Please Enter the name of the new filtered image \n";
    cout << "& specify extension .jpg, .bmp, .png, .tga: ";
    string new_fileName;
    cin >> new_fileName;
    img1.saveImage(new_fileName);

}

//====== Filter 5 Flip Image ======//
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

//====== Filter 6 Rotate Image ======//

//====== Filter 7 Darken and Lighten Image ======//
void Dark_and_Light() {
    // Read Image
    cout << "Enter the name of the image(with extensions) you want to apply filters on : ";
    string filename , ch;
    cin >> filename;
    Image img(filename);
    Image new_img(img.width,img.height);
    cout << "1) Darker\n";
    cout << "2) Lighter\n";
    cout << "=> ";
    cin >> ch;
    // dark
    if(ch == "1") {
        for(int i = 0; i < img.width; i++) {
            for(int j = 0; j < img.height; j++) {
                for(int k = 0; k < 3; k++) {
                    new_img(i,j,k) = img(i,j,k) * 0.250;
                }
            }
        } 
    }
    // light 
    else if(ch == "2") {
        for(int i = 0; i < img.width; i++) {
            for(int j = 0; j < img.height; j++) {
                for(int k = 0; k < 3; k++) {
                    if(img(i,j,k) > img.width / 2 && img(i,j,k) > img.height / 2) {
                        new_img(i,j,k) = min(img(i,j,k) + 170, 255);
                    } else {
                        new_img(i,j,k) = min(img(i,j,k) + 70, 255);
                    }
                }
            }
        } 
    } else {
        cout << "Invalid operation";
    }

    // Save Image
    cout << "Please Enter the name of the new filtered image \n";
    cout << "& specify extension .jpg, .bmp, .png, .tga: ";
    string new_fileName;
    cin >> new_fileName;
    new_img.saveImage(new_fileName);

}

//====== Filter 8 Crop Image ======//

//====== Filter 9 Adding a Frame to the Picture Image ======//

//====== Filter 10 Detect Image Edges ======//
void Detect_Image() {
    // Read Image
    string filename;
    cout << "Enter the name of the image (with extensions) you want to apply filters on : ";
    cin >> filename;
    Image img(filename);
    Image new_img(img.width,img.height);

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

    for(int i = 0; i < img.width; i++) {
        for(int j = 0; j < img.height; j++){
            for(int k = 0; k < img.channels; k++) {
                if(img(i,j,k) == 0 && img(i++,j,k) == 0 && img(i--,j,k) == 0 && img(i,j + 1,k) == 0 && 
                img(i,j - 1,k) == 0) {
                    new_img(i,j,k) = 255;
                } else {
                    new_img(i,j,k) = img(i,j,k);
                }
            }
        }
    }

    // Save Image
    cout << "Please Enter the name of the new filtered image \n";
    cout << "& specify extension .jpg, .bmp, .png, .tga: ";
    string new_fileName;
    cin >> new_fileName;
    new_img.saveImage(new_fileName);

}

//====== Filter 11 Resizing Image ======//

//====== Filter 12 Blur Image ======//




// Filters options
void Filters() {
    string ch;
    cout << "1) Gray Scale Filter\n";
    cout << "2) Black & White Filter\n";
    cout << "3) Invert Filter\n";
    cout << "4) Merge Filter\n";
    cout << "5) Flip Filter\n";
    cout << "6) Rotate Filter\n";
    cout << "7) Darken and Lighten Filter\n";
    cout << "8) Crop Filter\n";
    cout << "9) Adding a Frame Filter\n";
    cout << "10) Detect Image Filter\n";
    cout << "11) Resizing Filter\n";
    cout << "12) Blur Filter\n";
    cout << "=> ";
    while(true) {
        cin >> ch;
        if(ch == "1") {
            GrayScale();
            break;
        } else if(ch == "2") {
            Black_and_White();
            break;
        }
        else if(ch == "3") {
            Invert();
            break;
        }
        else if(ch == "4") {
            Merge();
            break;
        } 
        else if (ch == "5"){
            Flip();
            break;
        }
        else if (ch == "7") {
            Dark_and_Light();
            break;
        }
        else if(ch == "10") {
            Detect_Image();
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
            cout << "Bye!!";
            break;
        } else {
            cout << "Error! Please insert a valid option\n";
            continue;
        }

    }

    return 0;
}
