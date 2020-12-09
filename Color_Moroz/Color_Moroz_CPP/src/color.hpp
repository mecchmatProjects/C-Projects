#ifndef COLOR_HPP_INCLUDED
#define COLOR_HPP_INCLUDED

#include <ostream>

using namespace std;

class ColorRGBA;
class ColorCMYK;
class ColorHSB;

class Color
{
protected:
    //utility function for print colors
    virtual ostream& print(ostream& out) = 0;
public:
    //convert methods
    virtual ColorRGBA toRGBA() = 0;
    virtual ColorCMYK toCMYK() = 0;
    virtual ColorHSB toHSB() = 0;
    //convert to int and float methods
    virtual operator int() = 0;
    virtual operator float() = 0;
    //virtual destructor for safety
    virtual ~Color(){}
    //friend output operator
    friend ostream& operator << (ostream& out, Color& clr){
        return clr.print(out);
    }
};

#endif // COLOR_HPP_INCLUDED
