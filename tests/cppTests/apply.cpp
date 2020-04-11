#include "./../../src/DataFrame/DataFrame.cpp"
#include "./../../src/DataFrame/helpers.cpp"
#include "./../../src/DataFrame/SeriesInt.cpp"
#include "./../../src/DataFrame/SeriesFloat.cpp"
#include "./../../src/DataFrame/SeriesStr.cpp"
#include <random>
#include <ctime>
#include <cmath>
#include <iomanip>


using namespace std;

struct v{
  template<typename T>
  float operator()(std::vector<T>& data){
    float x = std::accumulate(data.begin(), data.end(), 0.0);
    return x;
  }
};


int main(int argc, char *argv[]){
  vector<float> v1(atoi(argv[1]) * 2), v2(atoi(argv[1]) * 2);

  std::generate(v1.begin(), v1.end(), std::rand);
  std::generate(v2.begin(), v2.end(), std::rand);

  DataFrame d1({new SeriesFloat(v1)}, {"a"});
  DataFrame d2({new SeriesFloat(v2)}, {"a"});

  auto clock1 = clock();
  d2.apply(v());
  auto clock2 = clock();
  cout<< (float)(clock2 - clock1)/CLOCKS_PER_SEC << endl;

  return 0;
}
