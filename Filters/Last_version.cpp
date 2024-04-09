#include <bits/stdc++.h>
#include "Image_Class.h"
using namespace std;

// Pointer to the current iamge
Image *img_ptr;
// Pointer to the name of image
Image *img_name_ptr;

// Flag to check if the user save the iamge or not
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
void Merge(Image &img, Image &img2) {
    // Read Image
    // Image img = Read_Img(User_img);
    // Image img2 = Read_Img(User_img2);
    Image *curr_img = new Image(img.width, img.height); // Dynamically allocate memory

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

    img_ptr = curr_img; // Assign the pointer to the dynamically allocated object

}

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
void Resize_Image(Image &img) {
    int newWidth, newHeight;

    // Get the new dimensions from the user
    cout << "Enter new width: ";
    cin >> newWidth;
    cout << "Enter new height: ";
    cin >> newHeight;

    // Create a new image with the specified dimensions
    Image *curr_img = new Image(newWidth, newHeight); // Dynamically allocate memory

    float sr = static_cast<float>(img.width) / newWidth;
    float sc = static_cast<float>(img.height) / newHeight;

    // Resize the image
    for (int i = 0; i < newWidth; i++) {
        for (int j = 0; j < newHeight; j++) {
            for (int k = 0; k < 3; ++k) {
                (*curr_img)(i, j, k) = img(round(i * sr), round(j * sc), k);
            }
        }
    }

    // Assign the pointer to the dynamically allocated object
    img_ptr = curr_img;
}


void Crop(Image &img) {

    int x, y, width, height;
    cout << "Enter starting point (x, y) of the area to keep: ";
    cin >> x >> y;
    cout << "Enter dimensions (width x height) of the area to cut: ";
    cin >> width >> height;
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
    cout << "Choose a wonderful filter to be applied on your image : \n";
    cout << "1) Gray Scale Filter\n";
    cout << "2) Black & White Filter\n";
    cout << "3) Invert Filter\n";
    cout << "4) Merge\n";
    cout << "5) Flip Filter\n";
    cout << "6) Rotate Filter\n";
    cout << "7) Darken and Lighten Filter\n";
    cout << "8) Crop Filter\n";
    cout << "9) Adding a Frame Filter\n";
    cout << "10)Detect Image Edges Filter\n";
    cout << "11)Resize Image Filter\n";
    cout << "12)Blur Images Filter\n";
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
        else if(ch == "5") {
            Flip(*img_name_ptr);
            break;
        }
        else if(ch == "4") {
            string image2;
            cout << "Enter the second image to merge it\n";
            cin >> image2;
            Image User_img2 = Read_Img(image2);
            cin.ignore();
            Merge(*img_name_ptr, User_img2);
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
        else if (ch == "11")
        {
            Resize_Image(*img_name_ptr);
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

void Many_Filters(){

    string ch, image_name;
    cout << "Choose a wonderful filter to be applied on your image : \n";
    cout << "1) Gray Scale Filter\n";
    cout << "2) Black & White Filter\n";
    cout << "3) Invert Filter\n";
    cout << "4) Merge\n";
    cout << "5) Flip Filter\n";
    cout << "6) Rotate Filter\n";
    cout << "7) Darken and Lighten Filter\n";
    cout << "8) Crop Filter\n";
    cout << "9) Adding a Frame Filter\n";
    cout << "10)Detect Image Edges Filter\n";
    cout << "11)Resize Image Filter\n";
    cout << "12)Blur Images Filter\n";
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
            string image2;
            cout << "Enter the second image to merge it: ";
            cin >> image2;
            Image User_img2 = Read_Img(image2);
            cin.ignore();
            Merge(*img_ptr, User_img2);
            break;
        }
        else if(ch == "5") {
            Flip(*img_ptr);
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
        else if (ch == "11")
        {
            Resize_Image(*img_ptr);
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
