#include "DataFrame/DataFrame.cpp"
#include "DataFrame/helpers.cpp"
#include "DataFrame/Series.h"
#include "DataFrame/SeriesFloat.cpp"
#include "DataFrame/SeriesInt.cpp"
#include "DataFrame/SeriesStr.cpp"
#include "DataFrame/Graph.h"
#include "DataFrame/Graph.cpp"
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
    Graph graph;

    x.transform("x + y * 2 - z + 3", {{"x", x}, {"y", y}, {"z", z}});


    std::cout << graph.getKernel("int");
    graph.compute();

    x.printDF();
    z.printDF();
    y.printDF();
    

    
    return 0;
}