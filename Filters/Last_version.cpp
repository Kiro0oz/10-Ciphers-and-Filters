/*
FCAI – Structured Programming – 2024 - Assignment 3
----------------------------------------------------
Purpose: 12 Filters + 3 Bonus.
Author: Kirollos Adel Samir-S17-[ Grayscale , Merge , Darken and Lighten , Detect Image Edges , Infrared]
        Noura Muhammad Mahmoud-S18-[ Black and White , Flip, Crop , Resize , Natural Sunlight ]
        Eman Emad Abdulrahim-S18-[ Invert, Rotate , ِAdding a Frame ,Blur , purple at night ]
IDS: Kirollos Adel-20230295.
     Noura Muhammad-20230448.
     Eman Emad- 20230619.

for Github=>https://github.com/Kiro0oz/10-Ciphers/tree/main/Filters.
*/


#include <bits/stdc++.h>
#include "Image_Class.h"
using namespace std;

// Pointer to the current image
Image *img_ptr;
// Pointer to the name of image
Image *img_name_ptr;

// Flag to check if the user save the image or not
bool flag = false;


string Read_Img(string img_name)
{
    Image img;
    while (true)
    {
        try
        {
            img.loadNewImage(img_name);
            break;
        }
        catch (invalid_argument)
        {
            cout << "Please insert a valid image: ";
            cin >> img_name;
        }
    }
    return img_name;
}

//====== Filter 1 Gray Scale ======//
void GrayScale(Image &img)
{
    // Image img = Read_Img(User_img);
    Image *curr_img = new Image(img.width, img.height); // Dynamically allocate memory
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
            for (int l = 0; l < 3; ++l)
            {
                img(i, j, l) = avg;
                (*curr_img)(i, j, l) = img(i, j, l);
            }
        }
    }
    img_ptr = curr_img; // Assign the pointer to the dynamically allocated object
}

//====== Filter 2 Black and White ======//
void Black_and_White(Image &img) {

    // Image img = Read_Img(User_img);
    Image *curr_img = new Image(img.width, img.height); // Dynamically allocate memory

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
                    (*curr_img)(i,j,k) = img(i,j,k);
                } else {
                    img(i, j, k) = 0;
                    (*curr_img)(i,j,k) = img(i,j,k);
                }
            }
        }
    }

    img_ptr = curr_img; // Assign the pointer to the dynamically allocated object
}

//====== Filter 3 Invert Image ======//
void Invert(Image &img) {
    // Image img = Read_Img(User_img);
    Image *curr_img = new Image(img.width, img.height); // Dynamically allocate memory

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
                (*curr_img)(i, j, k) = img(i, j, k);
            }
        }
    }
    img_ptr = curr_img; // Assign the pointer to the dynamically allocated object
}

//====== Filter 4 Merge Images ======//
void Merge(Image &img, Image &img2, string op) {
    // Read Image
    // Image *curr_img = new Image(img.width, img.height); // Dynamically allocate memory
    Image *curr_img; // Dynamically allocate memory
    int max_w = max(img.width, img2.width);
    int max_h = max(img.height, img2.height);
    Image Larger_img(max_w,max_h);
    
    if(op == "1") {
        curr_img = new Image(Larger_img.width, Larger_img.height);
        for(int i = 0; i < max_w; ++i) {
            for(int j = 0; j < max_h; ++j) {
                int avg_w = i * img.width / img2.width;
                int avg_h = j * img.height / img2.height;

                unsigned red_pixel = (img(avg_w,avg_h,0) + img2(i,j,0)) / 2;
                unsigned green_pixel = (img(avg_w,avg_h,1) + img2(i,j,1)) / 2;
                unsigned blue_pixel = (img(avg_w,avg_h,2) + img2(i,j,2)) / 2;
                
                (*curr_img).setPixel(i,j,0, red_pixel);
                (*curr_img).setPixel(i,j,1, green_pixel);
                (*curr_img).setPixel(i,j,2, blue_pixel);
            }
        }
    } else if(op == "2") {
        curr_img = new Image(img.width, img.height);
        for (int i = 0; i < img.width; ++i)
        {
            for (int j = 0; j < img.height; ++j)
            {
                for (int k = 0; k < img.channels; ++k)
                {
                    img(i, j, k) = (img(i,j, k) + img2(i,j,k) ) / 2;
                    (*curr_img)(i, j, k) = img(i, j, k);
                }
            }
        }
    }

    img_ptr = curr_img; // Assign the pointer to the dynamically allocated object

}

//====== Filter 5 Flip Image ======//
void FlipH(Image &img) {
    // Dynamically allocate memory for the flipped image
    Image *curr_img = new Image(img.width, img.height);

    for (int i = 0; i < img.width; i++) {
        for (int j = 0; j < img.height; j++) {
            for (int k = 0; k < img.channels; k++) {
                // Flip horizontally by swapping pixels
                (*curr_img)(i, j, k) = img(img.width - 1 - i, j, k);
            }
        }
    }

    // Assign the pointer to the dynamically allocated object
    img_ptr = curr_img;
}
void FlipV(Image &img) {

    Image *curr_img = new Image(img.width, img.height);

    for (int i = 0; i < img.width; i++) {
        for (int j = 0; j < img.height; j++) {
            for (int k = 0; k < img.channels; k++) {
                // Flip vertically by swapping pixels
                (*curr_img)(i, j, k) = img(i, img.height - 1 - j, k);
            }
        }
    }

    // Save the flipped image
    img_ptr = curr_img;
}
void Flip(Image &img) {
    cout << "1. Horizontally\n2. Vertically\n";
    int choice;
    cin >> choice;

    if (choice == 1) {
        FlipH(img);
    } else if (choice == 2) {
        FlipV(img);
    } else {
        cout << "Invalid choice.\n";
    }
}

//====== Filter 6 Rotate Image ======//
void Rotate90(Image &img){
    Image *curr_img = new Image(img.height, img.width); // Dynamically allocate memory
    Image newimg (img.height,img.width);

    for (int i = 0; i < newimg.width; i++) {
        for (int j = 1; j < newimg.height; j++) {
            for (int k = 0; k < 3; k++) {
                newimg(i, j, k) = img(j, i, k);
            }
        }
    }
    for (int i = 0; i < newimg.width; i++) {
        for (int j = 1; j < newimg.height; j++) {
            for (int k = 0; k < 3; k++) {
                (*curr_img)(i, j, k) = newimg(newimg.width - 1 - i, j, k);
            }
        }
    }
    img_ptr = curr_img; // Assign the pointer to the dynamically allocated object
}
void Rotate180(Image &img){
    Image *curr_img = new Image(img.width, img.height); // Dynamically allocate memory
    Image newimg (img.width,img.height);

    for (int i = 0; i < newimg.width; i++) {
        for (int j = 1; j < newimg.height ; j++) {
            for(int k=0;k<3;k++){
                newimg(i,j,k) =img(img.width-i,img.height-j,k);
                (*curr_img)(i, j, k) = newimg(i, j, k);
            }

        }
    }
    img_ptr = curr_img; // Assign the pointer to the dynamically allocated object
}
void Rotate270(Image &img){
    Image *curr_img = new Image(img.height, img.width); // Dynamically allocate memory
    Image newimg (img.height,img.width);

    for (int i = 0; i < newimg.width; i++) {
        for (int j = 1; j < newimg.height ; j++) {
            for(int k=0;k<3;k++){
                newimg(i, j, k) = img(img.width-j, i, k);
                (*curr_img)(i, j, k) = newimg(i, j, k);
            }

        }
    }
    img_ptr = curr_img; // Assign the pointer to the dynamically allocated object

}
void Rotate(Image &img) {
    string choice;
    cout << "Choose degree of rotation(90,180,270): ";
    while (true) {
        cin >> choice;
        cin.ignore();
        if (choice == "90") {
            Rotate90(img);
            break;
        }
        else if (choice == "180") {
            Rotate180(img);
            break;
        }
        else if (choice == "270") {
            Rotate270(img);
            break;
        }
        else {
            cout << "Error! Please Enter a valid choice: ";
            continue;
        }
        break;
    }
}

//====== Filter 7 Dark & Light ======//
void Dark_and_Light(Image &img)
{
    // Read Image
    string ch;
    // Image img = Read_Img(User_img);
    Image *curr_img = new Image(img.width, img.height);

    cout << "1) Darker\n";
    cout << "2) Lighter\n";
    cout << "=> ";
    cin >> ch;
    // dark
    if (ch == "1")
    {
        for (int i = 0; i < img.width; i++)
        {
            for (int j = 0; j < img.height; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    (*curr_img)(i, j, k) = img(i, j, k) * 0.250;
                }
            }
        }
    }
    // light
    else if (ch == "2")
    {
        for (int i = 0; i < img.width; i++)
        {
            for (int j = 0; j < img.height; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    if (img(i, j, k) > img.width / 2 && img(i, j, k) > img.height / 2)
                    {
                        (*curr_img)(i, j, k) = min(img(i, j, k) + 170, 255);
                    }
                    else
                    {
                        (*curr_img)(i, j, k) = min(img(i, j, k) + 70, 255);
                    }
                }
            }
        }
    }
    else
    {
        cout << "Invalid operation";
    }

    img_ptr = curr_img; // Assign the pointer to the dynamically allocated object
}

//====== Filter 8 Crop Image ======//
void Crop(Image &img) {
    int x, y, width, height;
    cout << "Enter starting point (x, y) of the area to keep\n";
    cout << "X: ";
    cin >> x;
    cout << "Y: ";
    cin >> y;
    cout << "Enter dimensions (width x height) of the area to cut\n";
    cout << "Width: ";
    cin >> width;
    cout << "Height: ";
    cin >> height;
    // Check if cropping dimensions exceed image size
    if (x + width > img.width || y + height > img.height) {
        cout << "Error: Cropping dimensions exceed image size" << endl;
        return;
    }

    Image *curr_img = new Image(width, height); // Dynamically allocate memory

    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            for (int k = 0; k < img.channels; ++k) {
                (*curr_img)(i, j, k) = img(x + i, y + j, k);
            }
        }
    }

    img_ptr = curr_img; // Assign the pointer to the cropped image
}

//====== Filter 9 Adding a Frame ======//
void Frame(Image &img) {
    Image *curr_img = new Image(img.width, img.height); // Dynamically allocate memory
    int border = img.width / 50; // Width of the frame
    int innerBorder = img.width / 100; // Width of the inner frame
    string ch;
    while (true) {
        cout << "Choose Frame:-\n";
        cout << "1) Blue Frame\n";
        cout << "2) Fancy\n";
        cout << "=> ";
        cin >> ch;
        cin.ignore();
        if (ch == "1") {
            for (int i = 0; i < img.width; i++) {
                for (int j = 0; j < img.height; j++) {
                    if (i < border || i >= img.width - border || j < border || j >= img.height - border) {
                        img(i, j, 0) = 0;
                        img(i, j, 1) = 0;
                        img(i, j, 2) = 255;
                    }
                }
            }
            break;
        }
        else if (ch == "2") {
            for (int i = 0; i < img.width; i++) {
                for (int j = 0; j < img.height; j++) {
                    if (i < border || i >= img.width - border || j < border || j >= img.height - border) {
                        img(i, j, 0) = 0;
                        img(i, j, 1) = 0;
                        img(i, j, 2) = 255;
                    }
                    if ((i >= 2 * border && i < img.width - 2 * border && j >= 2 * border && j < img.height - 2 * border)&& (i < border * 2 + innerBorder || i >= img.width - border * 2 - innerBorder
                                                                                                                             || j < border * 2 + innerBorder || j >= img.height - border * 2 - innerBorder)) {
                        for (int k = 0; k < 3; ++k) {
                            img(i, j, k) = 255;
                        }
                    }
                }
            }
            break;
        }
    }
    for (int i = 0; i < img.width; ++i) {
        for (int j = 0; j < img.height; ++j) {
            for (int k = 0; k <3 ; ++k) {
                (*curr_img)(i,j,k)=img(i,j,k);
            }
        }
    }
    img_ptr = curr_img; // Assign the pointer to the dynamically allocated object
}
//====== Filter 10 Detect Image Edges ======//
void Detect_Image(Image &img) {

Image *curr_img = new Image(img.width, img.height);

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
                    (*curr_img)(i,j,k) = 255;
                } else {
                    (*curr_img)(i,j,k) = img(i,j,k);
                }
            }
        }
    }

    // Assign the pointer to the dynamically allocated object
    img_ptr = curr_img;
}

//====== Filter 11 Resizing Image ======//
void Resize_Image(Image &img, int w, int h) {

    // Create a new image with the specified dimensions
    Image *curr_img = new Image(w, h); // Dynamically allocate memory

    float sr = static_cast<float>(img.width) / w;
    float sc = static_cast<float>(img.height) / h;

    // Resize the image
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            for (int k = 0; k < 3; ++k) {
                (*curr_img)(i, j, k) = img(round(i * sr), round(j * sc), k);
            }
        }
    }

    // Assign the pointer to the dynamically allocated object
    img_ptr = curr_img;
}

//====== Filter 12 Blur Image ======//
Image Blur(Image &img) {
    Image *curr_img = new Image(img.width, img.height);
    for (int i = 0; i < img.width; ++i) {
        for (int j = 0; j < img.height; ++j) {
            int counter = 0;
            int Rsum = 0, Gsum = 0, Bsum = 0;
            for (int x = i-15; x <= i+15; ++x) {
                for (int y = j-15; y <= j+15; ++y) {
                    if (x >= 0 && x < img.width && y >= 0 && y < img.height) {
                        Rsum += img(x,y,0);
                        Gsum += img(x,y,1);
                        Bsum += img(x,y, 2);
                        counter++;
                    }
                }
            }
            (*curr_img)(i,j,0)=(Rsum/counter);
            (*curr_img)(i,j,1)=(Gsum/counter);
            (*curr_img)(i,j,2)=(Bsum/counter);
        }
    }
    img_ptr = curr_img;
    return (*img_ptr);
}

void apply_bluer(Image &img) {
    Image *curr_img = new Image(img.width, img.height);
    if(img.height > 1000) {
        Resize_Image(img, img.width, 720);
    }
    curr_img = new Image(Blur(img));
    if(img.height > 1000) {
        Resize_Image(img, img.width, img.height);
    }
    img_ptr = curr_img;
}


//====== Filter 13 Infrared ======//
void Infrared(Image &img) {
    // Image img("samurai.jpg");
    Image *curr_img = new Image(img.width, img.height); // Dynamically allocate memory
    for(int i = 1; i < img.width; i++) {
        for(int j = 1; j < img.height; j++) {

            int red = img(i, j, 0);
            int green = img(i, j, 1);
            int blue = img(i, j, 2);

            red = 255;
            green = 255 - green;
            blue = 255 - blue;
            // Setting new RGB values
            img(i, j, 0) = red;
            img(i, j, 1) = green;
            img(i, j, 2) = blue;
            (*curr_img)(i,j,0) = img(i, j, 0);
            (*curr_img)(i,j,1) = img(i, j, 1);
            (*curr_img)(i,j,2) = img(i, j, 2);
        }
    }

    img_ptr = curr_img; // Assign the pointer to the dynamically allocated object
}

//===== Filter 14 Natural Sunlight =====//
void sunlight(Image &img) {

    Image *curr_img = new Image(img.width, img.height);
    // Define sunlight color and intensity
    const int Sun_intensity = 64;
    const int sun_col[] = {255, 255, 0};

    for (int i = 0; i < img.width; ++i) {
        for (int j = 0; j < img.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                int value = img(i, j, k) + Sun_intensity * sun_col[k] / 255;
                if (value > 255) {
                    (*curr_img)(i, j, k)= img(i, j, k) = 255;
                } else {
                    (*curr_img)(i, j, k)=img(i, j, k) = value;
                }
            }
        }
    }
    img_ptr = curr_img; // Assign the pointer to the dynamically allocated object
}

//===== Filter 15 Purple at night =====//
void Purple(Image &img){
    Image *curr_img = new Image(img.width, img.height);

    for (int i = 0; i < img.width; ++i){
        for (int j = 0; j < img.height; ++j){
            img(i,j,1)*=0.75;
            for(int k =0;k<3;++k){
                (*curr_img)(i, j, k)= img(i, j, k);
            }
        }
    }
    img_ptr = curr_img;
}

// Save Image
void Save(const string &save_name = "User_Image.jpg")
{
    string name;
    if (img_ptr != nullptr)
    { // Check if the pointer is valid
        while (true)
        {
            try
            {
                img_ptr->saveImage(save_name);
                delete img_ptr;    // Free the dynamically allocated memory
                img_ptr = nullptr; // Reset the pointer to null
                cout << "Saved Successfully!\n";
                flag = true;
                break;
            }
            catch (invalid_argument &e)
            {
                cout << "Error! " << e.what() << "\n";
                cout << "Try again ";
                cin >> name;
                Save(name);
                break;
            }
        }
    }
}



void Filters()
{
    string ch, image_name;
    cout << "\nChoose a wonderful filter to be applied on your image : \n";
    cout << "1) Gray Scale Filter\n";
    cout << "2) Black & White Filter\n";
    cout << "3) Invert Filter\n";
    cout << "4) Merge\n";
    cout << "5) Flip Filter\n";
    cout << "6) Rotate Filter\n";
    cout << "7) Darken and Lighten Filter\n";
    cout << "8) Crop Filter\n";
    cout << "9) Adding a Frame Filter\n";
    cout << "10) Detect Image Edges Filter\n";
    cout << "11) Resize Image Filter\n";
    cout << "12) Blur Images Filter\n";
    cout << "13) Infrared Filter\n";
    cout << "14) Natural Sunlight Filter\n";
    cout << "15) Purple at night Filter\n";
    cout << "=> ";
    cin >> ch;
    while (true)
    {
        if (ch == "1")
        {
            GrayScale(*img_name_ptr);
            break;
        }
        else if( ch == "2" ) {
            Black_and_White(*img_name_ptr);
            break;
        }
        else if(ch == "3") {
            Invert(*img_name_ptr);
            break;
        }
        else if(ch == "4") {
            string image2,ch;
            cout << "Enter the second image to merge it\n";
            cin >> image2;
            Image User_img2 = Read_Img(image2);
            cin.ignore();
            cout << "1) Resize the smaller image to lager\n";
            cout << "2) Merge the common area\n";
            cout << "=> ";
            cin >> ch;
            cin.ignore();
            Merge(*img_name_ptr, User_img2, ch);
            break;
        }
        else if(ch == "5") {
            Flip(*img_name_ptr);
            break;
        }
        else if(ch == "6") {
            Rotate(*img_name_ptr);
            break;
        }
        else if (ch == "7")
        {
            Dark_and_Light(*img_name_ptr);
            break;
        }
        else if (ch == "8")
        {
            Crop(*img_name_ptr);
            break;
        }
        else if (ch == "9")
        {
            Frame(*img_name_ptr);
            break;
        }
        else if (ch == "10") {
            Detect_Image(*img_name_ptr);
            break;
        }
        else if (ch == "11")
        {
            int newWidth, newHeight;
            // Get the new dimensions from the user
            cout << "Enter new width: ";
            cin >> newWidth;
            cout << "Enter new height: ";
            cin >> newHeight;

            Resize_Image(*img_name_ptr, newWidth, newHeight);
            break;
        }
        else if(ch == "12") {
            apply_bluer(*img_name_ptr);
            break;
        }
        else if(ch == "13") {
            Infrared(*img_name_ptr);
            break;
        }
        else if(ch == "14") {
            sunlight(*img_name_ptr);
            break;
        }
        else if(ch == "15") {
            Purple(*img_name_ptr);
            break;
        }
        else
        {
            cout << "Error! Please insert a valid option\n ";
            break;
        }
    }

    return;
}
// Function for applying many filters to the image
void Many_Filters(){
    string ch, image_name;
    cout << "\nChoose a wonderful filter to be applied on your image : \n";
    cout << "1) Gray Scale Filter\n";
    cout << "2) Black & White Filter\n";
    cout << "3) Invert Filter\n";
    cout << "4) Merge\n";
    cout << "5) Flip Filter\n";
    cout << "6) Rotate Filter\n";
    cout << "7) Darken and Lighten Filter\n";
    cout << "8) Crop Filter\n";
    cout << "9) Adding a Frame Filter\n";
    cout << "10) Detect Image Edges Filter\n";
    cout << "11) Resize Image Filter\n";
    cout << "12) Blur Images Filter\n";
    cout << "13) Infrared Filter\n";
    cout << "14) Natural Sunlight Filter\n";
    cout << "15) Purple at night Filter\n";
    cout << "=> ";
    cin >> ch;
    while (true)
    {
        if (ch == "1")
        {
            GrayScale(*img_ptr);
            break;
        }
        else if( ch == "2" ) {
            Black_and_White(*img_ptr);
            break;
        }
        else if(ch == "3") {
            Invert(*img_ptr);
            break;
        }
        else if(ch == "4") {
            string image2,ch;
            cout << "Enter the second image to merge it\n";
            cin >> image2;
            Image User_img2 = Read_Img(image2);
            cin.ignore();
            cout << "1) Resize the smaller image to lager\n";
            cout << "2) Merge the common area\n";
            cout << "=> ";
            cin >> ch;
            cin.ignore();
            Merge(*img_ptr, User_img2, ch);
            break;
        }
        else if(ch == "5") {
            Flip(*img_ptr);
            break;
        }
        else if(ch == "6") {
            Rotate(*img_ptr);
            break;
        }
        else if (ch == "7")
        {
            Dark_and_Light(*img_ptr);
            break;
        }
        else if (ch == "8")
        {
            Crop(*img_ptr);
            break;
        }
        else if (ch == "9")
        {
            Frame(*img_ptr);
            break;
        }
        else if(ch == "10") {
            Detect_Image(*img_ptr);
            break;
        }
        else if (ch == "11")
        {
            int newWidth, newHeight;
            // Get the new dimensions from the user
            cout << "Enter new width: ";
            cin >> newWidth;
            cout << "Enter new height: ";
            cin >> newHeight;
            Resize_Image(*img_ptr, newWidth, newHeight);
            break;
        }
        else if(ch == "12") {
            apply_bluer(*img_ptr);
            break;
        }
        else if(ch == "13") {
            Infrared(*img_ptr);
            break;
        }
        else if(ch == "14") {
            sunlight(*img_ptr);
            break;
        }
        else if(ch == "15") {
            Purple(*img_ptr);
            break;
        }
        else
        {
            cout << "Error! Please insert a valid option\n ";
            break;
        }
    }
}

void Menu()
{
        cout << "===========================================\n";
        cout << "* Welcome to the Baby Photoshop Program *\n";
        cout << "===========================================\n";
    while (true)
    {
        string ch, image_name;
        cout << "1) Insert a new image from your device (with extention)\n";
        cout << "2) Apply a filter on the current image\n";
        cout << "3) Save Image\n";
        cout << "4) Exit the program!\n";
        cout << "=> ";
        cin >> ch;
        if (ch == "1")
        {
            cout << "Enter the name of the image(with extensions) you want to apply filters on : ";
            cin >> image_name;
            Image User_img = Read_Img(image_name);
            img_name_ptr = new Image(User_img);
            cin.ignore();
            Filters();
        }
        else if (ch == "2")
        {
            if (img_name_ptr != nullptr)
            {
                // Filters();
                Many_Filters();
            }
            else
            {
                cout << "There is no image, please first insert a new image\n";
            }
        }
        else if (ch == "3")
        {
            if(img_ptr != nullptr) {
                string save_name;
                cout << "Please Enter the name of the new filtered image\n";
                cout << "& specify extension .jpg, .bmp, .png, .tga : ";
                cin >> save_name;
                // filter_img_name_ptr = new string(save_name);
                cin.ignore();
                Save(save_name);
            } else {
                cout << "Error! No image to save\n";
            }
        }
        else if (ch == "4")
        {
            if (flag == false) {
                string ch;
                cout << "Are you sure to exit without saving image?\n";
                cout << "1) Save\n";
                cout << "2) Exit\n";
                cout << "=> ";
                cin >> ch;
                if(ch == "1") {
                    if(img_ptr != nullptr) {
                        string save_name;
                        cout << "Please Enter the name of the new filtered image\n";
                        cout << "& specify extension .jpg, .bmp, .png, .tga : ";
                        cin >> save_name;
                        cin.ignore();
                        Save(save_name);
                    } else {
                        cout << "Error! No image to save\n";
                    }
                } else if(ch == "2") {
                    cout << "Bye!!";
                    break;
                } else {
                    cout << "Error! Please insert a valid option\n";
                    continue;
                }

            } else {
                cout << "Bye!!";
                break;
            }
        }
        else
        {
            cout << "Error! Please insert a valid option\n";
            continue;
        }
    }
}

int main()
{
    Menu();
    return 0;
}
