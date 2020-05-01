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


using namespace std;

int main(){
    DataFrame x("./example.csv");
    setup();
    //
    auto  y = x.copy();
    x.printDF();
    //


    // std::cout << "addition\n";
    // y.add(x);
    // y.printDF();
    // std::cout << "done\n";

    // vector<float> y1(9 * 2), x1(9 * 2);
    // std::generate(y1.begin(), y1.end(), std::rand);
    // std::generate(x1.begin(), x1.end(), std::rand);
    //
    // DataFrame x({new SeriesFloat(x1)}, {"a"});
    // DataFrame y({new SeriesFloat(y1)}, {"a"});

    Session Session;
    // Session.addDF(&x);
    // Session.addDF(&y);
    // std::cout << Session.getGenName(&x) << std::endl;
    // std::cout << Session.getGenName(&y) << std::endl;
    //
    // Session.insertOperation("add", &x, 3);
    // Session.insertOperation("mul", &x, 4);
    // Session.insertOperation("mul", &x, &y);
    // Session.insertOperation("mul", &x, &y);
    // Session.insertOperation("mul", &y, &x);
    // Session.insertOperation("mul", &y, &x);
    //
    // Session.insertOperation("mul", &x, 3);
    // Session.insertOperation("mul", &x, 3);
    // Session.insertOperation("mul", &x, 3);
    // Session.insertOperation("sub", &x, 3);

    // x.printDF();
    // y.printDF();

    // x.mul(y);
    std::string op = "x * x + 2 - x";
    // x.transform(op);
    x.mul(x);
    // x.mul(x);
    // x.div(2);
    // x.sub(0 + 2);
    // x.add(2);
    // x.mul(0);
    // x.mul(y);
    // x.sub(y);
    // if(_Session != nullptr){
    //   std::cout << "Session detected" << endl;
    // }
    // else std::cout << "Session not detected" << endl;
    auto clock1 = clock();
    // runGeneratedKernel(Session.getKernel("int"), std::vector<int*>({&((x[0]) -> getVec(0))[0], &((y[0]) -> getVec(0))[0]}),
    //  std::vector<int*>({&((x[0]) -> getVec(0))[0], &((y[0]) -> getVec(0))[0]}), (y[0] -> getVec(0)).size(),
    //  vector<int*>({NULL, NULL, NULL, NULL}));
    std::cout << Session.getKernel("int") << std::endl;
    Session.compute();
    auto clock2 = clock();
    std::cout << "time: " << (float)(clock2 - clock1)/CLOCKS_PER_SEC << std::endl;
    x.printDF();

    auto res = x.sum();
    for(auto x: res){
      std::cout << x.first << x.second << std::endl;
    }

     res = x.mean();
    for(auto x: res){
      std::cout << x.first << x.second << std::endl;
    }

    res = x.max();
   for(auto x: res){
     std::cout << x.first << x.second << std::endl;
   }



   res = x.min();
  for(auto x: res){
    std::cout << x.first << x.second << std::endl;
  }



    // x.dropNA();
    x.fillNA(2);
    x.printDF();
    // y.printDF();

    return 0;
}
