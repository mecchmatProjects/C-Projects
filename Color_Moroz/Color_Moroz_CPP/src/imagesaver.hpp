#ifndef IMAGESAVER_HPP_INCLUDED
#define IMAGESAVER_HPP_INCLUDED

#include <string>
#include <iostream>
#include <fstream>
#include "image.hpp"

using namespace std;

//class for Save image. Using RAII for safe open and close
class ImageSaver
{
    ofstream out;
public:
    //open file in constructor
    explicit ImageSaver(const string& filename);
    //close file in destructor
    ~ImageSaver();
    //save function
    void save(const Image& image);
    //restrict copy and move semantic
    ImageSaver(const ImageSaver&) = delete;
    ImageSaver(ImageSaver&&) = delete;
    ImageSaver& operator=(const ImageSaver&) = delete;
    ImageSaver& operator=(ImageSaver&&) = delete;
};

#endif // IMAGESAVER_HPP_INCLUDED
