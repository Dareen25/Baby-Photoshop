/*
 * Name the file: CS112_A3_Part1_S11,12_20220790_20231052_20231117.cpp.

 * explains the file :
 we have developed an image processing tool that can apply different filters
(changes) to a given image of any size and the four popular image formats.
like Grayscale Conversion that convert the colours of images to gray ,
Black and White that convert the colours of images to black and white,
Flip Image that Flip an image involves mirroring its contents horizontally or vertically ,
Invert Image that transforms the colors of
an image where light areas become dark and vice versa and
Rotate Image that rotate the image clockwise by 90º, 180º or 270º as the user chooses.

 * Team Members:
 * 1 - ID1: [ 20220790 ]
     Name student1: Fatima Ibrahim idris
     email: Fi049269@gmail.com
     filters :[ Grayscale Conversion ]
     Section: s
 * 2 - ID2: [20231052]
     Name student2: Dareen Elsayed Ragab
     email:dareenelsayed443@gmail.com
     filters:[ Black and White ,Flip Image ]
     Section: s11,12

 * 3 - ID3:  [20231117]
     Name student3: Anan Hamdi Ali
     email: ananhamdi2@gmail.com
     filters: [Invert Image , Rotate Image]
     Section: s11,12
      */
//system diagram
//https://docs.google.com/document/d/16L1-sO12kdtpVbeNnQ_C7WkjPZO9623g/edit?usp=drive_link&ouid=108668490554036929819&rtpof=true&sd=true
#include "Image_Class.h"
#include <string>
#include <iostream>
#include <regex>
#include <cctype>
#include <limits> // for numeric_limits

using namespace std;



bool validinput(const string &imagename) ;
bool validchoice(const string &choice) ;
bool valid_choice2(const string &choice);
void toGrayscale( Image& image);// function to apply filter 1
void  BlackandWhite(Image &image);//function to apply filter 2
void Invertimage(Image &image);//function to apply filter 3
void rotateimage(Image &image);//function to apply filter 6
void Flipimage(Image &image , int flip_choice);//function to apply filter 5

void displayMenu() {  //menu
    cout << "\nMenu:\n";
    cout << "1. Load a new image\n";
    cout << "2. Grayscale Conversion\n";
    cout << "3. Black and White\n";
    cout << "4. Invert image\n";
    cout << "5. Rotate image\n";
    cout << "6. Flip image\n";
    cout << "7. Save the image\n";
    cout << "8. Exit (to see the final image)\n";
}

void loadNewImage(string &imagename, Image &currentImage) { // load image
    while (true){
        try {
            cout << "Enter the image name with its extension (.jpg / .jpeg / .png / .bmp / .tga): ";
            cin >> imagename;

            currentImage.loadNewImage(imagename);


            break;// If the code reaches here, the image is successfully loaded
        } catch (const invalid_argument& e) {
            cout << e.what() << endl; // Output the error message
        }
    }
    if (currentImage.loadNewImage(imagename))
    {
        cout << "Image loaded successfully.\n";
    }

}

void applyFilter(const string &choice, Image &currentImage) { // apply all filters
    if (choice == "2") {
        toGrayscale(currentImage);
        cout << "Grayscale Conversion applied successfully.\n";
    } else if (choice == "3") {
        BlackandWhite(currentImage);
        cout << "Black and White filter applied successfully.\n";
    } else if (choice == "4") {
        Invertimage(currentImage);
        cout << "Invert image filter applied successfully.\n";
    } else if (choice == "5") {
        rotateimage(currentImage);
        cout << "Rotate image filter applied successfully.\n";
    } else if (choice == "6") {
        string flip_choice;
        while (true){ // verifiy valid input if the user enter 1 or 2 only
            cout << "Enter 1 for Flipped Horizontally or 2 for Flipped Vertical: ";
            cin >> flip_choice;
            if (!valid_choice2(flip_choice))
            {
                cout << "Enter (1/2) only.\n";
            }else break;
        }

        Flipimage(currentImage, stoi(flip_choice));
        cout << "Flip image filter applied successfully.\n";
    }
}

void saveImage( Image &image,string imagename) { // function to save the image
    string filename;
    string save;
    while (true)
    {
        cout << "Do you wants to save on the same file (1) or change file name (2)? : ";
        cin >> save ;
        if (!valid_choice2(save))
        {
            cout << "enter (1/2) only.\n";
        }else break;
    }

    if (save == "1")// if the user want to save in the same file
    {
        filename = imagename;
        cout << "The file name : "<< filename<< endl;
    }
    else if (save == "2")// if the user want to change the name of the file
    {
        while (true)
        {
            cout << "Enter the filename to save the image (with extension .jpg, .bmp, etc.) : ";
            cin >> filename;
            if (!validinput(filename)) // verfiy valid input
            {
                cout << "Input does not match the pattern!\n";
                continue;
            }else break;
        }

    }
    // Save the image
    if (image.saveImage(filename)){
        cout << "Image saved successfully.\n";
    }

}

int main() {
    //welcome message
    cout << "##############################################\n";
    cout << "Welcome to Baby photoshop for image processing\n";
    cout << "##############################################\n\n";

    string imagename;
    Image currentImage;

    while (true) { // the user can use the program tell he choose exit
        displayMenu();

        string choice;
        cout << "Enter your choice (1-8): ";
        cin >> choice;

        if (!validchoice(choice)) { //verify valid input
            cout << "Invalid input. Please enter an integer number from 1 to 8 only.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (choice == "8") {
            // Exit the program
            cout << "Exiting...\n";
            return 0;
        }

        if (choice == "1") {
            try { // verify valid image
                loadNewImage(imagename, currentImage);
            } catch (const invalid_argument& e) {
                cout << e.what() << endl;
            }
        } else {
            try { // verify valid image
                applyFilter(choice, currentImage);
            } catch (const invalid_argument& e) {
                cout <<  e.what() << endl;
            }
        }

        if (choice == "7") {
            try { // save image
                saveImage(currentImage,imagename);
            } catch (const invalid_argument& e) {
                cout << e.what() << endl;
            }
        }
    }

    return 0;
}
// all data about all functions of filters
bool validinput(const string &imagename) {
    regex reg("^[^.]+\\.(jpg|jpeg|png|bmp|tga)$");
    return regex_match(imagename, reg);
}
bool validchoice(const string &choice) {
    if (choice.size() != 1 || !isdigit(choice[0])) {
        return false;
    }
    int numChoice = choice[0] - '0';
    return (numChoice >= 1 && numChoice <= 8);
}
bool valid_choice2(const string &choice)
{
    if (choice.size() != 1 || !isdigit(choice[0])) {
        return false;
    }
    int numChoice = choice[0] - '0';
    return (numChoice >= 1 && numChoice <= 2);
}
void toGrayscale(Image &image)
{
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            unsigned  int avg = 0; // Initialize average value

            for (int k = 0; k < 3; ++k) {
                avg += image(i, j, k); // Accumulate pixel values
            }

            avg /= 3; // Calculate average

            // Set all channels to the average value
            image(i, j, 0) = avg;
            image(i, j, 1) = avg;
            image(i, j, 2) = avg;
        }
    }
}
void  BlackandWhite (Image &image) {
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            unsigned avg = 0;
            for (int k = 0; k < 3; k++) {
                avg += image.getPixel(i, j, k);
            }
            avg /= 3;


            if (avg > 128) {
                for (int k = 0; k < 3; k++) {
                    image.setPixel(i, j, k, 255);
                }
            } else {
                for (int k = 0; k < 3; k++) {
                    image.setPixel(i, j, k, 0);
                }
            }
        }
    }
}
void Invertimage(Image &image) {
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; j++) {
            for (int k = 0; k < image.channels; ++k) {
                image(i, j, k) = 255 - image(i, j, k);
            }
        }
    }
}
void rotateimage(Image &image) {
    Image rotate(image.height, image.width);

    string degr;
    cout << "Enter the angle (90, 180, 270): ";
    cin >> degr;

    if (degr == "90") {
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                for (int k = 0; k < image.channels; ++k) {
                    rotate(j, image.width - i - 1, k) = image(i, j, k);
                }
            }
        }
    } else if (degr == "180") {
        for (int i = 0; i < image.height; ++i) {
            for (int j = 0; j < image.width; ++j) {
                for (int k = 0; k < image.channels; ++k) {
                    rotate(image.height - i - 1, image.width - j - 1, k) = image(i, j, k);
                }
            }
        }
    } else if (degr == "270") {
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                for (int k = 0; k < image.channels; ++k) {
                    rotate(image.width - j - 1, i, k) = image(i, j, k);
                }
            }
        }
    } else {
        cout << "Invalid input. Please enter 90, 180, or 270." << endl;
        return; // Exit function if input is invalid
    }

    // Copy rotated image back to the original image
    image = rotate;
}

void Flipimage(Image &image ,int flip_choice)
{
    if (flip_choice == 1)
    {
        int halfWidth = image.width / 2;
        for (int i = 0; i < halfWidth; i++) {
            for (int j = 0; j < image.height; j++) {
                for (int k = 0; k < image.channels; k++) {
                    int pixelValueLeft = image.getPixel(i, j, k);
                    int pixelValueRight = image.getPixel(image.width - 1 - i, j, k);
                    image.setPixel(i, j, k, pixelValueRight);
                    image.setPixel(image.width - 1 - i, j, k, pixelValueLeft);
                }
            }
        }
    }


    else
    {
        int halfheight = image.height / 2;
        for (int i = 0; i < image.width; i++) {
            for (int j = 0; j < halfheight; j++) {
                for (int k = 0; k < image.channels; k++) {
                    int pixelValueLeft = image.getPixel(i, j, k);
                    int pixelValueRight = image.getPixel(i, image.height - 1 - j, k);
                    image.setPixel(i, j, k, pixelValueRight);
                    image.setPixel(i, image.height - 1 - j, k, pixelValueLeft);
                }
            }
        }
    }
}