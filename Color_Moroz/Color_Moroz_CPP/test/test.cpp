#include "test.hpp"

//RGBA test
void testRGBA(){
    //tests print, convert to int and float
    ColorRGBA c1(144,40,25,0);
    cout << c1 << endl;
    cout << int(c1) << endl;
    cout << float(c1) << endl;

    ColorRGBA c2(15,266,0);
    cout << c2 << endl;
    cout << int(c2) << endl;
    cout << float(c2) << endl;
    //operator tests
    ColorRGBA c3 = c1 + c2;
    cout << c3 << endl;
    c3 = c1 & c2;
    cout << c3 << endl;
    c3 = c1 | c2;
    cout << c3 << endl;
    c3 = c1 ^ c2;
    cout << c3 << endl;
    //test creation from int
    ColorRGBA c4(static_cast<int>(c1));
    cout << c4 << endl;
    cout << int(c4) << endl;
}

//CMYK test
void testCMYK(){
    ColorCMYK c1(0.5f,0.5f,1.0f,0.9f);
    cout << c1 << endl;
    cout << int(c1) << endl;
    cout << float(c1) << endl;

    ColorCMYK c2(0.6f,1.2f,0.1f,0.2f);
    cout << c2 << endl;
    cout << int(c2) << endl;
    cout << float(c2) << endl;

    //operator tests
    ColorCMYK c3 = c1 + c2;
    cout << c3 << endl;
    c3 = c1 & c2;
    cout << c3 << endl;
    c3 = c1 | c2;
    cout << c3 << endl;
    c3 = c1 ^ c2;
    cout << c3 << endl;
}

//HSB test
void testHSB(){
    ColorHSB c1(148,0.7f,1.2f);
    cout << c1 << endl;
    cout << int(c1) << endl;
    cout << float(c1) << endl;

    ColorHSB c2(397,1.1f,2.1f);
    cout << c2 << endl;
    cout << int(c2) << endl;
    cout << float(c2) << endl;

    //operator tests
    ColorHSB c3 = c1 + c2;
    cout << c3 << endl;
    c3 = c1 & c2;
    cout << c3 << endl;
    c3 = c1 | c2;
    cout << c3 << endl;
    c3 = c1 ^ c2;
    cout << c3 << endl;
}

//Convert test
void testConvert(){
    ColorRGBA c_rgb1(10,213,3);
    ColorCMYK c_cmyk1 = c_rgb1.toCMYK();
    ColorHSB c_hsb1 = c_rgb1.toHSB();
    ColorRGBA c_rgb2 = c_cmyk1.toRGBA();
    ColorRGBA c_rgb3 = c_hsb1.toRGBA();
    ColorCMYK c_cmyk2 = c_hsb1.toCMYK();
    ColorHSB c_hsb2 = c_cmyk1.toHSB();

    cout << c_rgb1;
    cout << c_cmyk1;
    cout << c_hsb1;
    cout << c_rgb2;
    cout << c_rgb3;
    cout << c_cmyk2;
    cout << c_hsb2;
}

//Load and save image test
void testImageLoadSave(){
    Image img1(6,5);
    cout << "\nBefore Save\n" << endl;
    img1.setPixel(13,2,3);
    img1.show();
    img1.save("..//Color_Moroz_CPP//test//img.txt");
    cout << "\nAfter Load\n" << endl;
    Image img2 = Image::load("..//Color_Moroz_CPP//test//img.txt");
    img2.show();
}

//Image and Mask test
void testImageMask(){
    Image img = Image::load("..//Color_Moroz_CPP//test//img2.txt");
    cout << "\nIMAGE\n" << endl;
    img.show();
    Image mask = Image::load("..//Color_Moroz_CPP//test//mask2.txt");
    cout << "\nMASK\n" << endl;
    mask.show();

    Image result = img * mask;
    cout << "\nFiltered new image\n" << endl;
    result.show();

    img.applyFilter(mask);
    cout << "\nFiltered first image\n" << endl;
    img.show();
}
