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

struct plusOne{
    float operator()(float x){
        return x + 1;
    }

    int operator()(int x){
        return x + 1;
    }
};

int main(int argc, char *argv[]){
  vector<float> v1(atoi(argv[1]) * 2), v2(atoi(argv[1]) * 2);
  vector<int> v3(atoi(argv[1]) * 2), v4(atoi(argv[1]) * 2);
  vector<float> v5(atoi(argv[1]) * 2), v6(atoi(argv[1]) * 2);
  vector<float> v7(atoi(argv[1]) * 2), v8(atoi(argv[1]) * 2);


  std::generate(v1.begin(), v1.end(), std::rand);
  std::generate(v2.begin(), v2.end(), std::rand);
  std::generate(v3.begin(), v3.end(), std::rand);
  std::generate(v4.begin(), v4.end(), std::rand);

  std::generate(v5.begin(), v5.end(), std::rand);
  std::generate(v6.begin(), v6.end(), std::rand);
  std::generate(v7.begin(), v7.end(), std::rand);
  std::generate(v8.begin(), v8.end(), std::rand);

  DataFrame d1({new SeriesFloat(v1), new SeriesInt(v3), new SeriesFloat(v7), new SeriesFloat(v5)}, {"a", "b", "c", "d"});
  DataFrame d2({new SeriesFloat(v2), new SeriesInt(v4), new SeriesFloat(v8), new SeriesFloat(v6)}, {"a", "b", "c", "d"});
  
  auto clock1 = clock();
  d1.add(d1);
  d1.add(d1);
  d1.transform(plusOne());
  d1.sub(2);
  d1.add(3);
  
  auto clock2 = clock();

  d2.add(d1);
  auto clock3 = clock();
  cout << (float)(clock3 - clock1)/CLOCKS_PER_SEC << endl;

  return 0;
}
