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

int main(int argc, char *argv[]){
  if(argc == 3){
    setup();
  }
  vector<int> v1(atoi(argv[1]) * 2), v2(atoi(argv[1]) * 2);
  // setup();
  std::generate(v1.begin(), v1.end(), std::rand);
  std::generate(v2.begin(), v2.end(), std::rand);

  DataFrame d1({new SeriesInt(v1)}, {"a"});
  DataFrame d2({new SeriesInt(v2)}, {"a"});


  for(int &item: v1){
    cout << item << " " ;
  }
  cout << endl;
  for(int &item: v2){
    cout << item << " " ;
  }
  cout << endl;
  auto clock1 = clock();
  d1.add(d2);
  auto clock2 = clock();
  cout << (float)(clock2 - clock1)/CLOCKS_PER_SEC << endl;
  for(int &item: v1){
    cout << item << " " ;
  }

  return 0;
}
