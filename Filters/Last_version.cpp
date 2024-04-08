#include <bits/stdc++.h>
#include "Image_Class.h"
using namespace std;

// Pointer to the current iamge
Image *img_ptr;
// Pointer to the name of image
string *img_name_ptr;
// Pointer to the name of filtered image
string *filter_img_name_ptr;

bool flag = false;

string name_filtered = "filtered.jpg";

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
void GrayScale(string User_img)
{
    Image img = Read_Img(User_img);
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
    // img_ptr->loadNewImage(name_filtered);
}

//====== Filter 2 Black and White ======//
void Black_and_White(string User_img) {

    Image img = Read_Img(User_img);
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
void Invert(string User_img) {
    Image img = Read_Img(User_img);
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
void Merge(string User_img, string User_img2) {
    // Read Image
    Image img = Read_Img(User_img);
    Image img2 = Read_Img(User_img2);
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


void Dark_and_Light(string User_img)
{
    // Read Image
    string ch;
    Image img = Read_Img(User_img);
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
                cout << "Save Successfully!\n";
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
    cout << "Choose a wonderful filter on your iamge\n";
    cout << "1) Gray Scale Filter\n";
    cout << "2) Black & White Filter\n";
    cout << "3) Invert Filter\n";
    cout << "4) Merge\n";
    cout << "5) Darken and Lighten Filter\n";
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
            string image2;
            cout << "Enter the second iamge to merge it\n";
            cin >> image2;
            cin.ignore();
            Merge(*img_name_ptr, image2);
            break;
        }
        else if (ch == "5")
        {
            Dark_and_Light(*img_name_ptr);
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

// void Many_Filters(){
//      string ch, image_name;
//     cout << "Choose a wonderful filter on your iamge\n";
//     cout << "1) Gray Scale Filter\n";
//     cout << "2) Black & White Filter\n";
//     cout << "3) Invert Filter\n";
//     cout << "4) Flip Filter\n";
//     cout << "5) Darken and Lighten Filter\n";
//     cout << "=> ";
//     cin >> ch;
//     while (true)
//     {
//         if (ch == "1")
//         {
//             GrayScale(name_filtered);
//             break;
//         }
//         else if (ch == "5")
//         {
//             Dark_and_Light(name_filtered);
//             break;
//         }
//         else
//         {
//             cout << "Error! Please insert a valid option\n ";
//             break;
//         }
//     }

//     return;
// }

void Menu()
{
    while (true)
    {
        string ch, image_name;
        cout << "1) Insert a new iamge from your device (with extention)\n";
        cout << "2) Apply a filter on the currant image\n";
        cout << "3) Save Image\n";
        cout << "4) Exit the program!\n";
        cout << "=> ";
        cin >> ch;
        if (ch == "1")
        {
            cout << "Enter the name of the image(with extensions) you want to apply filters on : ";
            cin >> image_name;
            img_name_ptr = new string(image_name);
            cin.ignore();
            Filters();
        }
        else if (ch == "2")
        {
            if (img_name_ptr != nullptr)
            {
                Filters();
                // Many_Filters();
            }
            else
            {
                cout << "There is no iamge, please first insert a new iamge\n";
            }
        }
        else if (ch == "3")
        {
            string save_name;
            cout << "Please Enter the name of the new filtered image\n";
            cout << "& specify extension .jpg, .bmp, .png, .tga : ";
            cin >> save_name;
            // filter_img_name_ptr = new string(save_name);
            cin.ignore();
            Save(save_name);
        }
        else if (ch == "4")
        {
            if (flag == false) {
                string ch;
                cout << "Are you sure to exit without saving image\n";
                cout << "1) Save\n";
                cout << "2) Exit\n";
                cout << "=> ";
                cin >> ch;
                if(ch == "1") {
                    string save_name;
                    cout << "Please Enter the name of the new filtered image\n";
                    cout << "& specify extension .jpg, .bmp, .png, .tga : ";
                    cin >> save_name;
                    // filter_img_name_ptr = new string(save_name);
                    cin.ignore();
                    Save(save_name);
                } else if(ch == "2") {
                    cout << "Buy!!";
                    break;
                } else {
                    cout << "Error! Please insert a valid option\n";
                    continue;
                }
                
            } else {
                cout << "Buy!!";
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
