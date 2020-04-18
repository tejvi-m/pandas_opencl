// // #include "DataFrame/DataFrame.cpp"
// #include "DataFrame/helpers.h"
// // #include "DataFrame/SeriesInt.cpp"
// // #include "DataFrame/SeriesFloat.cpp"
// // #include "DataFrame/SeriesStr.cpp"
// // #include "DataFrame/Graph.h"
// // #include "DataFrame/Graph.cpp"
// // #include "DataFrame/gpu/gpu.h"
// #include "DataFrame/DataFrame.h"
// // #include "DataFrame/Series.h"
// #include "DataFrame/Graph.h"
// #include <iostream>
// #include <numeric>
// #include <ctime>
// #include <cmath>
// #include <iomanip>
// #include <random>
// #include <string>

#include "DataFrame/DataFrame.cpp"
#include "DataFrame/helpers.cpp"
#include "DataFrame/SeriesInt.cpp"
#include "DataFrame/SeriesFloat.cpp"
#include "DataFrame/SeriesStr.cpp"
#include "DataFrame/Graph.cpp"
#include <numeric>
#include <ctime>
#include <cmath>
#include <iomanip>
#include <random>

using namespace std;

int main(){
    // DataFrame x("./src/example.csv");
    setup();
    //
    // auto  y = x.copy();
    // x.printDF();
    //


    // std::cout << "addition\n";
    // y.add(x);
    // y.printDF();
    // std::cout << "done\n";

    vector<int> y1(9999999 * 2), x1(9999999 * 2);
    std::generate(y1.begin(), y1.end(), std::rand);
    std::generate(x1.begin(), x1.end(), std::rand);

    DataFrame x(vector<Series*>({new SeriesInt(x1)}), vector<string>({"a"}));
    DataFrame y(vector<Series*>({new SeriesInt(y1)}), vector<string>({"a"}));

    Graph graph;
    // graph.addDF(&x);
    // graph.addDF(&y);
    // std::cout << graph.getGenName(&x) << std::endl;
    // std::cout << graph.getGenName(&y) << std::endl;
    //
    graph.insertOperation("add", &x, 3);
    graph.insertOperation("mul", &x, 4);
    graph.insertOperation("mul", &x, &y);
    graph.insertOperation("mul", &x, &y);
    graph.insertOperation("mul", &y, &x);
    graph.insertOperation("mul", &y, &x);

    graph.insertOperation("mul", &x, 3);
    graph.insertOperation("mul", &x, 3);
    graph.insertOperation("mul", &x, 3);
    graph.insertOperation("sub", &x, 3);

    if(_graph != nullptr){
      std::cout << "graph detected" << endl;
    }
    else std::cout << "graph not detected" << endl;
    auto clock1 = clock();
    // runGeneratedKernel(graph.getKernel("int"), std::vector<int*>({&((x[0]) -> getVec(0))[0], &((y[0]) -> getVec(0))[0]}),
    //  std::vector<int*>({&((x[0]) -> getVec(0))[0], &((y[0]) -> getVec(0))[0]}), (y[0] -> getVec(0)).size(),
    //  vector<int*>({NULL, NULL, NULL, NULL}));
    graph.compute();
    auto clock2 = clock();
    std::cout << "time: " << (float)(clock2 - clock1)/CLOCKS_PER_SEC << std::endl;
    std::cout << graph.getKernel("int") << std::endl;
    // x.printDF();
    // y.printDF();
    return 0;
}
