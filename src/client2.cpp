#include "DataFrame/DataFrame.cpp"
#include "DataFrame/helpers.cpp"
#include "DataFrame/SeriesInt.cpp"
#include "DataFrame/SeriesFloat.cpp"
#include "DataFrame/SeriesStr.cpp"
#include <numeric>

struct d{
  template<typename T>
  void operator()(T& x){
    x = -x;
  }
};

struct v{
  template<typename T>
  float operator()(std::vector<T>& data){
    float x = std::accumulate(data.begin(), data.end(), 0.0);
    return x;
  }
};

int main(){
    DataFrame x("./src/example.csv");
    x["a"] -> show();

    auto  y = x.copy();
    std::cout << x.shape().first;
    std::cout << x.shape().second<< std::endl;
    // x.drop("a");
    std::cout << x.shape().first;
    std::cout << x.shape().second << std::endl;
    std::cout << y.shape().first;
    std::cout << y.shape().second<< std::endl;

    x.printDF();

    auto z = y + x;
    z.printDF();

    std::cout << "addition\n";
    y.add(x);
    y.printDF();
    std::cout << "done\n";
    auto z1 = y - x;
    z1.printDF();

    z1.sub(y);
    z1.printDF();

    auto z2 = z * x;
    z2.printDF();

    z2.mul(x);
    z2.printDF();

    auto z3 = z / x;
    z3.printDF();

    z3.div(x);
    z3.printDF();

    DataFrame hell("./src/example.csv");
    hell.printDF();
    std::cout <<"tan" << std::endl;
    hell.transform(d());
    hell.printDF();

    std::cout << "application\n";
    auto res = hell.apply(v());
    for(auto x: res){
      std::cout << x.first << x.second << std::endl;
    }
    return 0;
}
