#include "./../src/DataFrame/DataFrame.cpp"
#include "./../src/DataFrame/helpers.cpp"
#include "./../src/DataFrame/SeriesInt.cpp"
#include "./../src/DataFrame/SeriesFloat.cpp"
#include "./../src/DataFrame/SeriesStr.cpp"
#include <random>
#include <ctime>
#include <cmath>


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


int main(){
  vector<int> v1(99999999 * 2), v2(99999999 * 2);
  std::generate(v1.begin(), v1.end(), std::rand);
  std::generate(v2.begin(), v2.end(), std::rand);
  std::replace(v2.begin(), v2.end(), 0.0, 0.1);


  DataFrame d1({new SeriesInt(v1)}, {"a"});
  DataFrame d2({new SeriesInt(v2)}, {"a"});

  auto clock1 = clock();
  d1.div(d2);
  auto clock2 = clock();
  cout << "division: " << (float)(clock2 - clock1)/CLOCKS_PER_SEC << endl;


  clock1 = clock();
  d1.add(d2);
  clock2 = clock();

  cout << "addition: " << (float)(clock2 - clock1)/CLOCKS_PER_SEC << endl;

  clock1 = clock();
  d1.sub(d2);
  clock2 = clock();

  cout << "subtraction" << (float)(clock2 - clock1)/CLOCKS_PER_SEC << endl;



  clock1 = clock();
  d1.mul(d2);
  clock2 = clock();
  cout << "multiply" << (float)(clock2 - clock1)/CLOCKS_PER_SEC << endl;

  d1.transform(d());

  clock1 = clock();
  d2.apply(v());
  clock2 = clock();
  cout << "apply" << (float)(clock2 - clock1)/CLOCKS_PER_SEC << endl;

  clock1 = clock();
  d2.transform(d());
  clock2 = clock();
  cout << "transform:" << (float)(clock2 - clock1)/CLOCKS_PER_SEC << endl;


  clock1 = clock();
  auto d3 = d1.copy();
  clock2 = clock();
  cout << "copy" << (float)(clock2 - clock1)/CLOCKS_PER_SEC << endl;

  return 0;
}
