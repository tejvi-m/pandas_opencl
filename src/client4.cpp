#include "DataFrame/DataFrame.cpp"
#include "DataFrame/helpers.cpp"
#include "DataFrame/Series.h"
#include "DataFrame/SeriesFloat.cpp"
#include "DataFrame/SeriesInt.cpp"
#include "DataFrame/SeriesStr.cpp"
#include "DataFrame/Session.h"
#include "DataFrame/Session.cpp"
#include <numeric>
#include <ctime>
#include <cmath>
#include <iomanip>
#include <random>


int main(){

    setup();

    DataFrame x("example.csv");
    DataFrame y = x.copy();
    DataFrame z = x.copy();

    x.printDF();
    Session Session;

    x.transform("x + y * 2 - z + 3", {{"x", x}, {"y", y}, {"z", z}});

    Session.clear();
    std::cout << Session.getKernel("int");
    
    x.transform(std::string("x * 3"));
    Session.compute();

    x.printDF();
    z.printDF();
    y.printDF();
    

    
    return 0;
}