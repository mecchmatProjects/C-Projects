#ifndef TEST_HPP_INCLUDED
#define TEST_HPP_INCLUDED

#include <iostream>

#include "../src/colorrgba.hpp"
#include "../src/colorcmyk.hpp"
#include "../src/colorhsb.hpp"
#include "../src/image.hpp"
#include "../src/imageloader.hpp"
#include "../src/imagesaver.hpp"

using namespace std;

void testRGBA();

void testCMYK();

void testHSB();

void testConvert();

void testImageLoadSave();

void testImageMask();

#endif // TEST_HPP_INCLUDED
