// Main file project
// Noura => [ 2, 5, 8, 11 ]
// Eman => [ 3, 6, 9, 12 ]
// Kiro => [ 1, 4, 7, 10 ]

#include<bits/stdc++.h>
using namespace std;

void Black_and_White(Image& image) {
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {

            unsigned int avg = 0;
            for (int k = 0; k < image.channels; ++k) {
                avg += image(i, j, k);
            }
            avg = avg / 3;
            for (int k = 0; k < 3; ++k) {
                if (avg > 127) {
                    image(i, j, k) = 255;
                } else {
                    image(i, j, k) = 0;
                }
            }
        }
    }
}

int main() {
    Image image("mario.jpg");
    Black_and_White(image);
    image.saveImage("newMario.jpg");
}

