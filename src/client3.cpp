#include "DataFrame/DataFrame.cpp"
#include "DataFrame/helpers.cpp"
#include "DataFrame/SeriesInt.cpp"
#include "DataFrame/SeriesFloat.cpp"
#include "DataFrame/SeriesStr.cpp"
#include "DataFrame/Graph.cpp"
#include <numeric>



int main(){
    DataFrame x("./src/example.csv");
    setup();

    auto  y = x.copy();
    x.printDF();



    // std::cout << "addition\n";
    // y.add(x);
    // y.printDF();
    // std::cout << "done\n";

    Graph graph;
    graph.addDF(&x);
    graph.addDF(&y);
    std::cout << graph.getGenName(&x) << std::endl;
    std::cout << graph.getGenName(&y) << std::endl;

    graph.insertOperation("add", &x, &y);
    // graph.insertOperation("mul", &x, &y);
    // graph.insertOperation("div", &x, 3);


    runGeneratedKernel(graph.getKernel("int"), &((x[0]) -> getVec(0))[0], &((y[0]) -> getVec(0))[0], &((x[0]) -> getVec(0))[0], &((y[0]) -> getVec(0))[0], (y[0] -> getVec(0)).size());
    std::cout << graph.getKernel("int") << std::endl;
    x.printDF();
    y.printDF();
    return 0;
}
