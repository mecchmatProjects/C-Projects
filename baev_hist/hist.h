#ifndef HIST_H_INCLUDED
#define HIST_H_INCLUDED


struct Histogram
{
    double min_hist; // Minimalne znach v structure
    double max_hist; // MAximalne znach v structure
    unsigned M; // Kilcist stovbtsiv v histogrammi(rivnomirno na [min_hist, max_hist])
    unsigned *frequency; // Chastota - kilkist elementiv v kojnomu stovbtsi
};
struct Histogram hist;
void InputFromTxtFile(); // Zchituvannya histogrammi z txt failu
void setMax(double m); // max znach

void setMin(double m); // min znach

void setM(unsigned m); // kilkist stovbtsiv na intervali[min_hist, max_hist]

void addNumber_1(double x); // dodavannya chisel sho ne vhodyyat v interval [min_hist, max_hist] ne dodayutsya

void addNumber_2(double x); //odavannya chisel sho ne vhodyyat v interval [min_hist, max_hist]  dodayutsya do krainih intervaliv

void addNumber_3(double x);

void addbatch_1(double data[], size_t dataSize);

void addbatch_2(double data[], size_t dataSize);

void addbatch_3(double data[], size_t dataSize);


unsigned num(); // kilkist el v histogramme


double mean(); // Vidnoshennya kilkosti elementiv do kilkosti stovbtsiv

double median(); // mediana


double variance(); // variatsiya

double dev(); // seredne vidhilennya

void asymmetry(); // assymetriya




#endif // HIST_H_INCLUDED
