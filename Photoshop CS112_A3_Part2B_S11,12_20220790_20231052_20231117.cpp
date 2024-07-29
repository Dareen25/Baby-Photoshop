/*
 * Name the file: CS112_A3_Part2B_S11,12_20220790_20231052_20231117.cpp.

 * Team Members:
 * 1 - ID1: [ 20220790 ]
     Name student1: Fatima Ibrahim idris
     email: Fi049269@gmail.com
     filters :[ Grayscale Conversion(1), Merge Images(4), Darken and Lighten Image(7), Detect Image Edges(10), sunlight(13) ]
     Section: s
 * 2 - ID2: [20231052]
     Name student2: Dareen Elsayed Ragab
     email:dareenelsayed443@gmail.com
     filters:[ Black and White(2) ,Flip Image(5), Crop Images(8),Resizing Images(11), Luffy look purple(16) ]
     Section: s11,12

 * 3 - ID3:  [20231117]
     Name student3: Anan Hamdi Ali
     email: ananhamdi2@gmail.com
     filters: [Invert Image(3) , Rotate Image(6),öAdding a Frame to the Picture(9), Blur Images(12), Samurais (17)]
     Section: s11,12
      */
//system diagram
//https://drive.google.com/file/d/1mix6ganwUL2Gq5TyZ3XsQFcozmO258eo/view?usp=sharing
// github repo link
//https://github.com/dareen44/CS112_A3_S11-12_20231052_20231117_20220790-photoshop-
#include "Image_Class.h"
#include <string>
#include <iostream>
#include <regex>
#include <cctype>
#include <limits> // for numeric_limits
#include <cmath>
#include <cstdlib>
using namespace std;

bool validinput(const string &imagename) {
    regex reg("^[^.]+\\.(jpg|jpeg|png|bmp|tga)$");
    return regex_match(imagename, reg);
}

bool validchoice(int &choice) {
    return (choice >= 1 && choice <= 19);
}

bool valid_choice2(const string &choice) {
    return (choice.size() == 1 && isdigit(choice[0]) && choice[0] >= '1' && choice[0] <= '2');
}

void toGrayscale(Image &image) {
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            unsigned int avg = 0; // Initialize average value
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

void BlackandWhite(Image &image) {
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            unsigned int avg = 0;
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

Image rotateimage(Image &image) {
    string degr;
    while (true) {
        cout << "Enter the angle (90, 180, 270): ";
        cin >> degr;

        if (degr == "90") {
            Image rotated(image.height, image.width);
            for (int i = 0; i < image.width; ++i) {
                for (int j = 0; j < image.height; ++j) {
                    for (int k = 0; k < image.channels; ++k) {
                      rotated(image.height - j, i , k) = image(i, j, k);

                    }
                }
            }

            return rotated;
            break;
        } else if (degr == "180") {
            Image rotated(image.width, image.height);
            for (int i = 0; i < image.height; ++i) {
                for (int j = 0; j < image.width; ++j) {
                    for (int k = 0; k < image.channels; ++k) {
                        rotated(image.width - 1 - j, image.height - 1 - i, k) = image(j, i, k);
                    }
                }
            }

            return rotated;

            break;
        } else if (degr == "270") {
            Image rotated(image.height, image.width);
            for (int i = 0; i < image.width; ++i) {
                for (int j = 0; j < image.height; ++j) {
                    for (int k = 0; k < image.channels; ++k) {
                        rotated(j, image.width - 1 - i , k) = image(i, j, k);                    }
                }
            }

            return rotated;

            break;
        } else if (degr == "90" || degr == "180" || degr == "270") {
            break;
        } else {
            cout << "Invalid input. Please enter 90, 180, or 270." << endl;
        }
    }
}

void Flipimage(Image &image, int flip_choice) {
    if (flip_choice == 1) {
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
    } else {
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

void cropimage(Image &currentImage) {
   cout << "The width of this image is --> " << currentImage.width << '\n';
    cout << "The height of this image is --> " << currentImage.height << '\n';
    cout << endl;

    int x, y, width, height;

    while (true) {
        cout << "Enter the x-coordinate of the top-left corner: ";
        if (!(cin >> x) || (x >= currentImage.width)|| (x<0)) {
            cout << "Error: invalid input, or The selected area is out of the image boundaries!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        } else break;
    }
    while (true) {
        cout << "Enter the y-coordinate of the top-left corner: ";
        if (!(cin >> y) || (y >= currentImage.height) || (y<0)) {
            cout << "Error: invalid input, or The selected area is out of the image boundaries!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }  else break;
    }
    while (true) {
        cout << "Enter the width of the cropped image : ";
        if (!(cin >> width) || (x + width > currentImage.width) || (width <0)) {
            cout << "Error: invalid input, or The selected area is out of the image boundaries!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }  else break;
    }
    while (true) {
        cout << "Enter the height of the cropped image : ";
        if (!(cin >> height) || (y + height > currentImage.height)|| (height <0)) {
            cout << "Error: invalid input, or The selected area is out of the image boundaries!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        } else break;
    }

    Image cropImage(width, height);

    for (int i = 0; i < cropImage.width; i++) {
        for (int j = 0; j < cropImage.height; j++) {
            for (int k = 0; k < 3; k++) {
                int imold = currentImage.getPixel(i + x, j + y, k);
                cropImage.setPixel(i, j, k, imold);
            }
        }
    }
    currentImage = cropImage;

}

Image resizeimage(Image& image) {
    int newWidth, newHeight, rchoice;
    cout << "The width of this image is --> " << image.width << '\n';
    cout << "The height of this image is --> " << image.height << '\n';
    cout << endl;
    while (true)
    {

    cout << "Enter the way to resize the image by ratio type (1) or by dimensions type(2): ";
    if (!(cin >> rchoice)) {
        cout << "Error: invalid input, enter 1/2 only!\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        continue;
    }
    if (rchoice == 1) {
        double ratioo;
        int x, y;
        while (true)
        {
        cout << "Enter ratio of reduction/increase (e.g., 0.5 for 50% reduction, 2 for double image) : ";
        if (!(cin >> ratioo) || (ratioo <=0) ) {
            cout << "Error: invalid input, enter a valid ratio!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }else break;

        }
        newWidth = static_cast<int>(image.width * ratioo);
        newHeight = static_cast<int>(image.height * ratioo);
        cout << "newWidth : "<< newWidth<<" , newHeight : "<<newHeight<<endl;
        Image resizedImage(newWidth, newHeight);

        double x_ratio = static_cast<double>(image.width) / newWidth;
        double y_ratio = static_cast<double>(image.height) / newHeight;

for (int i = 0; i < newWidth; ++i) {
        for (int j = 0; j < newHeight; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                int origX = static_cast<int>(i * x_ratio);
                int origY = static_cast<int>(j * y_ratio);

                // Ensure the original coordinates are within bounds
                origX = min(origX, image.width - 1);
                origY = min(origY, image.height - 1);

                resizedImage(i, j, k) = image(origX, origY, k);
            }
        }
    }


return resizedImage;
break;
    }
else if (rchoice == 2) {
        while (true)
        {
            cout << "Enter the width of the resized image: ";
            if (!(cin >> newWidth) || (newWidth <=0))
            {
            cout << "Error: invalid input, enter a valid width!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
            }else break;

        }
        while (true)
        {

            cout << "Enter the height of the resized image: ";
            if (!(cin >> newHeight) || (newHeight <= 0))
            {
            cout << "Error: invalid input, enter a valid height!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
            }else break;

        }
    Image resizedImage(newWidth, newHeight);

    double x_ratio = static_cast<double>(image.width) / newWidth;
    double y_ratio = static_cast<double>(image.height) / newHeight;

    for (int i = 0; i < newWidth; ++i) {
        for (int j = 0; j < newHeight; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                int origX = static_cast<int>(i * x_ratio);
                int origY = static_cast<int>(j * y_ratio);

                // Ensure the original coordinates are within bounds
                origX = min(origX, image.width - 1);
                origY = min(origY, image.height - 1);

                resizedImage(i, j, k) = image(origX, origY, k);
            }
        }
    }
return resizedImage;
break;
    } else {
        cout << "Error: invalid input, enter 1/2 only!\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        continue;
    }
    }
}

void darkenImageandlightenImage(Image& image, int percentage = 50) {
    int d_lchoice;
    while (true) {
        cout << "Enter your choice (1) to lighten the image or (2) to darken the image: ";
        if (!(cin >> d_lchoice)) {
            cout << "Invalid input. Please enter 1 or 2.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
if (d_lchoice == 1) {
            float factor = percentage / 100.0;
    int width = image.width;
    int height = image.height;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            for (int c = 0; c < image.channels; c++) {
                unsigned char& p = image(x, y, c);
                p = static_cast<unsigned char>(255 * pow((p / 255.0), factor)); // Increase brightness using dynamic range compression
            }
        }
    }
    cout << "Lighten image filter applied successfully.\n";
            break;
}else if (d_lchoice == 2) {
            float factor = percentage / 100.0;
    int width = image.width;
    int height = image.height;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            for (int c = 0; c < image.channels; c++) {
                unsigned char& p = image(x, y, c);
                p = static_cast<unsigned char>(p * (1.0 - factor)); // Decrease brightness by a factor
            }
        }
    }
    cout << "Darken image filter applied successfully.\n";
            break;
}else {
            cout << "Enter 1 or 2 only!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
    }
}
void detectEdges(Image& image, unsigned char threshold = 110) {

    Image tempImage(image.width, image.height);

    // Sobel operator kernels for horizontal and vertical edges
    int sobelX[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int sobelY[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // Apply the Sobel operator to each pixel in the image
    for (int y = 1; y < image.height - 1; ++y) {
        for (int x = 1; x < image.width - 1; ++x) {
            int gx = 0, gy = 0;

            // Compute gradients using Sobel operator
            for (int i = -1; i <= 1; ++i) {
                for (int j = -1; j <= 1; ++j) {
                    int pixelValue = image(x + i, y + j, 0);
                    gx += sobelX[i + 1][j + 1] * pixelValue;
                    gy += sobelY[i + 1][j + 1] * pixelValue;
                }
            }

            // Compute gradient magnitude and check against threshold
            int magnitude = sqrt(gx * gx + gy * gy);

            // Set edge pixels to black and non-edge pixels to white in the temporary image
            if (magnitude > threshold) {
                // Set edge pixels to black in the temporary image
                tempImage(x, y, 0) = 0;
                tempImage(x, y, 1) = 0;
                tempImage(x, y, 2) = 0;
            } else {
                // Set non-edge pixels to white in the temporary image
                tempImage(x, y, 0) = 255;
                tempImage(x, y, 1) = 255;
                tempImage(x, y, 2) = 255;
            }
        }
    }

    // Copy the edge-detected result back to the original image
    for (int y = 0; y < image.height; ++y) {
        for (int x = 0; x < image.width; ++x) {
            for (int c = 0; c < image.channels; ++c) {
                image(x, y, c) = tempImage(x, y, c);
            }
        }
    }
}

void ditherImage(Image& image) {
    // Define the dithering matrix
    int ditherMatrix[2][2] = {{0, 2},
                              {3, 1}};

    // Apply dithering to each pixel in the image
    for (int y = 0; y < image.height; ++y) {
        for (int x = 0; x < image.width; ++x) {
            for (int c = 0; c < image.channels; ++c) {
                int oldPixel = image(x, y, c);
                int newPixel = oldPixel + ditherMatrix[x % 2][y % 2] * 32;

                // Ensure the pixel value is within [0, 255] range
                newPixel = min(max(newPixel, 0), 255);

                // Update the image pixel with the dithered value
                image(x, y, c) = newPixel;
            }
        }
    }
}
// Function to resize an image to specified maximum dimensions
Image resizeImageToMax(const Image& image, int maxWidth, int maxHeight) {
    Image resizedImage(maxWidth, maxHeight);

    double x_ratio = static_cast<double>(image.width) / maxWidth;
    double y_ratio = static_cast<double>(image.height) / maxHeight;

    for (int i = 0; i < maxWidth; ++i) {
        for (int j = 0; j < maxHeight; ++j) {
            int x = static_cast<int>(i * x_ratio);
            int y = static_cast<int>(j * y_ratio);

            for (int k = 0; k < image.channels; ++k) {
                resizedImage(i, j, k) = image(x, y, k);
            }
        }
    }

    return resizedImage;
}

// Function to crop an image to specified dimensions
Image cropImage(const Image& image, int newWidth, int newHeight) {
    Image croppedImage(newWidth, newHeight);

    int startX = (image.width - newWidth) / 2;
    int startY = (image.height - newHeight) / 2;

    for (int i = 0; i < newWidth; ++i) {
        for (int j = 0; j < newHeight; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                croppedImage(i, j, k) = image(startX + i, startY + j, k);
            }
        }
    }

    return croppedImage;
}

// Function to merge two images based on specified dimensions, with optional crop and resize
Image mergeImagesWithSize(const Image& img1, const Image& img2, bool resizeSmaller, bool resizeLarger, bool cropSmaller, bool cropLarger, int choice) {
    int maxWidth, maxHeight;
    if (choice == 1) {
        maxWidth = min(img1.width, img2.width);
        maxHeight = min(img1.height, img2.height);
    } else if (choice == 2) {
        maxWidth = max(img1.width, img2.width);
        maxHeight = max(img1.height, img2.height);
    }

    // Perform crop and resize based on options
    Image resizedImg1, resizedImg2;

    if (cropSmaller && img1.width * img1.height < img2.width * img2.height) {
        resizedImg1 = cropImage(img1, img2.width, img2.height);
    } else {
        resizedImg1 = resizeSmaller ? resizeImageToMax(img1, maxWidth, maxHeight) : img1;
    }

    if (cropLarger && img1.width * img1.height >= img2.width * img2.height) {
        resizedImg2 = cropImage(img2, img1.width, img1.height);
    } else {
        resizedImg2 = resizeLarger ? resizeImageToMax(img2, maxWidth, maxHeight) : img2;
    }

    // Create the merged image with the maximum dimensions
    Image mergedImage(maxWidth, maxHeight);

    // Merge images pixel by pixel
    for (int y = 0; y < maxHeight; ++y) {
        for (int x = 0; x < maxWidth; ++x) {
            for (int c = 0; c < 3; ++c) {
                // Sum up pixel values from both images
                int pixelSum = static_cast<int>(resizedImg1(x, y, c)) + static_cast<int>(resizedImg2(x, y, c));
                // Average the pixel values
                unsigned char pixelValue = static_cast<unsigned char>(pixelSum / 2);
                mergedImage(x, y, c) = pixelValue;
            }
        }
    }

    return mergedImage;
}

Image blurimage(const Image &image)
{
    Image blur(image.width, image.height); // Create a new image for blurring

    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            int sum = 0;
            int count = 0;

            // Calculate sum of neighboring pixel values
            for (int x = -1; x <= 1; ++x) {
                for (int y = -1; y <= 1; ++y) {
                    int newX = i + x;
                    int newY = j + y;

                    // Check boundary conditions
                    if (newX >= 0 && newX < image.width && newY >= 0 && newY < image.height) {
                        for (int k = 0; k < image.channels; ++k) {
                            sum += image(newX, newY, k);
                        }
                        count++;
                    }
                }
            }

            // Calculate average pixel value
            if (count > 0) {
                int average = sum / count;
                // Assign average value to corresponding pixel in blur image
                for (int k = 0; k < image.channels; ++k) {
                    blur(i, j, k) = average;
                }
            }
        }
    }

    return blur;
}
void fancyframeimage(Image &image)
{


int frame = 20;
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < frame; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                if ((i + j) % 2 == 0) {
                    if (k == 0) {
                        image(i, j, k) = 0;
                    }
                    else if (k == 1) {
                        image(i, j, k) = 0;
                    }
                    else if (k == 2) {
                        image(i, j, k) = 0;
                    }
                }
                    else {
                        if (k == 0) {
                            image(i, j, k) = 0;
                        }
                        else if (k == 1) {
                            image(i, j, k) = 255;
                        }
                        else if (k == 2) {
                            image(i, j, k) = 0;
                        }
                    }
                }
            }

    }
    for (int i = 0; i < frame; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                if ((i + j) % 2 == 0) {
                    if (k == 0) {
                        image(i, j, k) = 255;
                    }
                    else if (k == 1) {
                        image(i, j, k) = 0;
                    }
                    else if (k == 2) {
                        image(i, j, k) =255;
                    }
                }
                    else {
                        if (k == 0) {
                            image(i, j, k) = 255;
                        }
                        else if (k == 1) {
                            image(i, j, k) = 255;
                        }
                        else if (k == 2) {
                            image(i, j, k) = 0;
                        }
                    }
                }

        }
    }
                for (int i = image.width - frame; i < image.width; ++i) {
                    for (int j = 0; j < image.height; ++j) {
                        for (int k = 0; k < image.channels; ++k) {
                            if ((i + j) % 2 == 0) {
                                if (k == 0) {
                                    image(i, j, k) = 0;
                                }
                                else if (k == 1) {
                                    image(i, j, k) = 0;
                                }
                                else if (k == 2) {
                                    image(i, j, k) = 255;
                                }
                            }
                            else {
                                if (k == 0) {

                                    image(i, j, k) = 255;
                                }
                                else if (k == 1) {
                                    image(i, j, k) = 255;
                                }
                                else if (k == 2) {
                                    image(i, j, k) = 255;
                                }
                            }
                        }
                    }
                }

                for (int i = 0; i < image.width; ++i) {
                    for (int j = image.height - frame; j < image.height; ++j) {
                        for (int k = 0; k < image.channels; ++k) {
                            if ((i + j) % 2 == 0) {
                                if (k == 0) {
                                    image(i, j, k) = 255;
                                }
                                else if (k == 1) {
                                    image(i, j, k) = 0;
                                }
                                else if (k == 2) {
                                    image(i, j, k) = 0;
                                }
                            }
                            else {
                                if (k == 0) {
                                    image(i, j, k) = 0;
                                }
                                else if (k == 1) {
                                    image(i, j, k) = 255;
                                }
                                else if (k == 2) {
                                    image(i, j, k) = 0;
                                }


                            }
                        }
                    }
                }



}
void sampleframeimage(Image& image, int i, int j, int k, int choice) {
    int color;
    if (choice == 1) {
        color = 0;
    }
    else if (choice == 2) {
        color = 255;
    }
    else if (choice == 3) {
        color = 124;
    }
    else if (choice == 4) {
        color = (k == 0) ? 0 : 255;
    }
    else if (choice == 5) {
        color = (k == 0) ? 255 : 0;
    }
    else if (choice == 6) {
        color = (k == 1) ? 255 : 0;
    }

    image(i, j, k) = color;
}
void sunlightimage(Image& image)
{
for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            int red = image(i, j, 0) * 1.3;
            int green = image(i, j, 1) * 1.3;
            int blue = image(i, j, 2) * 0.8;

            // Ensure the values stay within the valid range [0, 255]
            red = (red > 255) ? 255 : red;
            green = (green > 255) ? 255 : green;
            blue = (blue > 255) ? 255 : blue;

            image(i, j, 0) = red;
            image(i, j, 1) = green;
            image(i, j, 2) = blue;
        }
    }
}
void Infraredimage (Image &image)
{
 for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
                for (int k =0 ; k < image.channels; k ++){
                  image(i, j, 0) = 255;
                  image(i, j, 1) = 255 - image(i, j, 2);
                  image(i, j, 2) = image(i, j, 1);
                }
        }
 }
}
void purpleimage(Image &image)
{
    for (int i = 0; i < image.width; i++)
    {
        for (int j = 0; j < image.height; j++)
        {
            for (int k = 0; k < image.channels; k++)
            {
                if (k == 1) { // Green channel
                    if (image(i, j, k) < 0) {
                        image(i, j, k) = 0;
                    } else {
                        image(i, j, k) /= 1.5;
                    }
                }
            }
        }
    }
}

void saveimage(Image &currentImage, string &filename,  string &imagename) {
    string save;
    while (true) {
        cout << "Do you want to save on the same file (1) or change file name (2)? : ";
        cin >> save;
        if (!valid_choice2(save)) {
            cout << "Enter (1/2) only.\n";
        } else break;
    }

    if (save == "1") {
        cout << "The file name : " << filename << endl;
    } else if (save == "2") {
        while (true) {
            cout << "Enter the filename to save the image (with extension .jpg, .bmp, etc.): ";
            cin >> filename;
            if (!validinput(filename)) {
                cout << "Input does not match the pattern!\n";
                continue;
            } else break;
        }
    }
try {
    if (currentImage.saveImage(filename)) {
        cout << "Image saved successfully as " << filename << endl;
    }

}catch (...)
{

    cout << "error !";
}
}

int main() {
    cout << "##############################################\n";
    cout << "Welcome to Baby photoshop for image processing\n";
    cout << "##############################################\n\n";

    string imagename;
    string filename = imagename;
    Image currentImage;

    while (true) {
        try {
            cout << "Enter the image name with its extension (.jpg / .jpeg / .png / .bmp / .tga): ";
            cin >> imagename;
            currentImage.loadNewImage(imagename);
            filename = imagename;
            cout << "Image loaded successfully.\n";
            break;
        } catch (const invalid_argument &e) {
            cout << e.what() << endl;
        }
    }

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Load a new image\n";
        cout << "2. Grayscale Conversion\n";
        cout << "3. Black and White\n";
        cout << "4. Invert image\n";
        cout << "5. Rotate image\n";
        cout << "6. Flip image\n";
        cout << "7. Crop image\n";
        cout << "8. Resize image\n";
        cout << "9. Darken Image and lighten Image\n";
        cout << "10. Detect Edges\n";
        cout << "11. Infrared image\n";
        cout << "12. sunlight image\n";
        cout << "13. Purple image\n";
        cout << "14. Merge image\n";
        cout << "15. Blur image\n";
        cout << "16. Fancy frame image\n";
        cout << "17. sample frame image\n";
        cout << "18. Save the image\n";
        cout << "19. Exit (to see the final image)\n";
        cout << "Enter your choice (1-19): ";

        int choice;
        cin >> choice;

        if (!validchoice(choice)) {
            cout << "Invalid input. Please enter an integer number from 1 to 10 only.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (choice == 19) {
            cout << "Exiting...\n";
            system(filename.c_str());
            return 0;
        }

        if (choice == 1) {
            while (true) {
                try {
                    cout << "Enter the image name with its extension (.jpg / .jpeg / .png / .bmp / .tga): ";
                    cin >> imagename;
                    currentImage.loadNewImage(imagename);
                    cout << "Image loaded successfully.\n";
                    filename = imagename;
                    break;
                } catch (const invalid_argument &e) {
                    cout << e.what() << endl;
                }
            }
        } else {
            try {
   if (choice == 2) {
    toGrayscale(currentImage);
    cout << "Grayscale Conversion applied successfully.\n";
} else if (choice == 3) {
    BlackandWhite(currentImage);
    cout << "Black and White filter applied successfully.\n";
} else if (choice == 4) {
    Invertimage(currentImage);
    cout << "Invert image filter applied successfully.\n";
} else if (choice == 5) {
     currentImage= rotateimage(currentImage);

    cout << "Rotate image filter applied successfully.\n";
} else if (choice == 6) {
    int flip_choice;
    while (true)
    {

    cout << "Enter 1 for Flipped Horizontally or 2 for Flipped Vertical: ";
    if (!(cin >> flip_choice) || (flip_choice != 1 && flip_choice != 2)) {
            cout << "Error: invalid input, enter 1 or 2 only!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            break;
        }
    }
    Flipimage(currentImage, flip_choice);
    cout << "Flip image filter applied successfully.\n";
} else if (choice == 7) {
cropimage(currentImage);
    cout << "Crop image filter applied successfully.\n";
} else if (choice == 8) {
    currentImage = resizeimage(currentImage);
    cout << "Resize image filter applied successfully.\n";
}
else if (choice == 9)
{
    darkenImageandlightenImage(currentImage);
}
else if (choice == 10)
{
    // Apply edge detection filter
    detectEdges(currentImage);

    // Apply dithering to reduce black color intensity
    ditherImage(currentImage);
     cout << "Detect Edges image filter applied successfully.\n";
}
else if (choice == 11)
{
    Infraredimage(currentImage);
    cout << "Infrared image filter applied successfully.\n";

}
else if (choice == 12)
{
    sunlightimage(currentImage);
    cout << "Sunlight image filter applied successfully.\n";

}
else if (choice == 13)
{
    purpleimage(currentImage);
    cout << "purple image filter applied successfully.\n";

}
else if (choice == 14)
{
     Image image1,image2;
     string imagename2, imagename3, imagename4;
     while (true) {
                try {
                    cout << "Enter the first image name with it extension (.jpg / .jpeg / .png / .bmp / .tga): ";
                    cin >> imagename2;
                    image1.loadNewImage(imagename2);
                    cout << "Image loaded successfully.\n";
                    break;
                } catch (const invalid_argument &e) {
                    cout << e.what() << endl;
                }
            }
            while (true) {
                try {
                    cout << "Enter the second image name with it extension (.jpg / .jpeg / .png / .bmp / .tga): ";
                    cin >> imagename3;
                    image2.loadNewImage(imagename3);
                    cout << "Image loaded successfully.\n";
                    break;
                } catch (const invalid_argument &e) {
                    cout << e.what() << endl;
                }
            }

    // Determine if the smaller image should be resized to match the larger image dimensions
    bool resizeSmaller = (image1.width * image1.height < image2.width * image2.height);
    int choice3;
while (true)
{

    cout << "Choose the dimensions:\n";
    cout << "1. Smaller dimensions\n";
    cout << "2. Larger dimensions\n";
    cout << "Enter your choice (1 or 2): ";

   if (!(cin >> choice3) || (choice3 != 1 && choice3 != 2)) {
            cout << "Error: invalid input, enter 1 or 2 only!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            break;
        }
}

    bool resizeLarger = (choice3 == 2);

    // Determine if cropping is needed based on the choice
    bool cropSmaller = false;
    bool cropLarger = false;
    if (resizeSmaller && choice3 == 1) {
        cropLarger = true;
    } else if (!resizeSmaller && choice3 == 2) {
        cropSmaller = true;
    }

    int choice1;
    while (true) {
        cout << "Would you like to continue filtering on the merged image (1) or continue filtering on the first image (2)? ";
        if (!(cin >> choice1) || (choice1 != 1 && choice1 != 2)) {
            cout << "Enter 1 or 2 only!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            break;
        }
    }

     if (choice1 == 1)
     {
        currentImage = mergeImagesWithSize(image1, image2, resizeSmaller, resizeLarger, cropSmaller, cropLarger, choice3);
       while (true) {
            cout << "Enter the filename to the merge image (with extension .jpg, .bmp, etc.): ";
            cin >> imagename4;
            if (!validinput(imagename4)) {
                cout << "Input does not match the pattern!\n";
                continue;
            } else break;
        }
       filename = imagename4;
       cout << "Merge image filter applied successfully.\n";

     }
     else if (choice1 == 2)
     {
        Image mergedImage = mergeImagesWithSize(image1, image2, resizeSmaller, resizeLarger, cropSmaller, cropLarger, choice3);
        cout << "Merge image filter applied successfully.\n";
        string file = "mergeimage2.jpg";
        mergedImage.saveImage(file);
        system(file.c_str());
     }



}
else if (choice == 15)
{
    currentImage = blurimage(currentImage);
    cout << "Blur image filter applied successfully.\n";

}
else if (choice == 16)
{
    fancyframeimage(currentImage);
    cout << "Fancy Frame image filter applied successfully.\n";

}
else if (choice == 17)
{
    int choice2;
    cout << "1- black" << endl;
    cout << "2- white" << endl;
    cout << "3- gray" << endl;
    cout << "4- Baby blue " << endl;
    cout << "5- red" << endl;
    cout << "6- green" << endl;
    cout << "please enter the color : ";
    cin >> choice2;

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < currentImage.height; j++) {
            for (int k = 0; k < currentImage.channels; ++k) {
                sampleframeimage(currentImage, i, j, k, choice2);
            }
        }
    }

    for (int i = 0; i < currentImage.width; ++i) {
        for (int j = 0; j < 5; j++) {
            for (int k = 0; k < currentImage.channels; ++k) {
                sampleframeimage(currentImage, i, j, k, choice2);
            }
        }
    }

    for (int i = currentImage.width - 1; i > currentImage.width - 5; --i) {
        for (int j = 0; j < currentImage.height; j++) {
            for (int k = 0; k < currentImage.channels; ++k) {
                sampleframeimage(currentImage, i, j, k, choice2);
            }
        }
    }

    for (int i = 0; i < currentImage.width; ++i) {
        for (int j = currentImage.height - 1; j > currentImage.height - 5; j--) {
            for (int k = 0; k < currentImage.channels; ++k) {
                sampleframeimage(currentImage, i, j, k, choice2);
            }
        }
    }
    cout << "Sample Frame image filter applied successfully.\n";

}
else if (choice == 18) {
    saveimage(currentImage, filename, imagename);
} else {
    cout << "Invalid choice. Please enter a valid choice.\n";
}

            } catch (const invalid_argument &e) {
                cout << e.what() << endl;
            }
        }
string file = "finalimage.jpg";
currentImage.saveImage(file);
system(file.c_str());
    }

    return 0;
}

