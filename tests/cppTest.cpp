#include "./../src/DataFrame/DataFrame.cpp"
#include "./../src/DataFrame/helpers.cpp"
#include "./../src/DataFrame/SeriesInt.cpp"
#include "./../src/DataFrame/SeriesFloat.cpp"
#include "./../src/DataFrame/SeriesStr.cpp"
#include <random>
#include <ctime>
#include <cmath>
#include <iomanip>

using namespace std;

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


int main(int argc, char *argv[]){
  vector<float> v1(atoi(argv[1]) * 2), v2(atoi(argv[1]) * 2);
  setup();
  std::generate(v1.begin(), v1.end(), std::rand);
  std::generate(v2.begin(), v2.end(), std::rand);
  // // std::replace(v2.begin(), v2.end(), 0.0, 0.1);
  //

  DataFrame d1({new SeriesFloat(v1)}, {"a"});
  DataFrame d2({new SeriesFloat(v2)}, {"a"});
  
  // Session session;
  
  // d1.add(d2);
  // d1.add(d2);
  // d1.add(d2);
  //
  auto clock1 = clock();
  // // d1.div(d2);
  d1.add(d2);
  d1.add(d2);
  // d1.add(d2);
  // session.compute();
  auto clock2 = clock();
  // cout << (float)(clock2 - clock1)/CLOCKS_PER_SEC;


  //
  cout << (float)(clock2 - clock1)/CLOCKS_PER_SEC << endl;
  // //
  // clock1 = clock();
  // d1.sub(d2);
  // clock2 = clock();
  //
  // cout << (float)(clock2 - clock1)/CLOCKS_PER_SEC << endl;

  //
  //
  // clock1 = clock();
  // d1.mul(d2);
  // clock2 = clock();
  // cout << (float)(clock2 - clock1)/CLOCKS_PER_SEC << endl;
  //
  // d1.transform(d());

  // clock1 = clock();
  // d2.apply(v());
  // clock2 = clock();
  // cout<< (float)(clock2 - clock1)/CLOCKS_PER_SEC << endl;
  //
  // clock1 = clock();
  // d2.transform(d());
  // clock2 = clock();
  // cout << (float)(clock2 - clock1)/CLOCKS_PER_SEC << endl;
  // clock1 = clock();
  // DataFrame df("./test.csv");
  // clock2 = clock();
  // std::cout << (float)(clock2 - clock1)/CLOCKS_PER_SEC << "\n";
  //
  //
  // clock1 = clock();
  // auto d3 = d1.copy();
  // clock2 = clock();
  // cout << "copy" << (float)(clock2 - clock1)/CLOCKS_PER_SEC << endl;

  return 0;
}
