#include "DataFrame/DataFrame.cpp"
#include "DataFrame/helpers.cpp"
#include "DataFrame/SeriesInt.cpp"
#include "DataFrame/SeriesFloat.cpp"
#include "DataFrame/SeriesStr.cpp"
#include <random>
#include <ctime>
#include <cmath>

using namespace std;

int main(){
  vector<int> v1(99999999), v2(99999999), v3(99999999);
  std::generate(v1.begin(), v1.end(), std::rand);
  std::generate(v2.begin(), v2.end(), std::rand);


  SeriesInt x(v1), y(v2), z(v3);

  auto clock1 = clock();
  x.add(y, z);
  auto clock2 = clock();

  cout << (float)(clock2 - clock1)/CLOCKS_PER_SEC << endl;

  clock1 = clock();
  z = x + y;
  clock2 = clock();

  cout << (float)(clock2 - clock1)/CLOCKS_PER_SEC << endl;
  // z.show()

  clock1 = clock();
  Series* z1 = &z;
  x.mul((Series *) &z);
  clock2 = clock();

  cout << (float)(clock2 - clock1)/CLOCKS_PER_SEC << endl;

  clock1 = clock();
  Series* z11 = &z;
  Series* y1 = &y;
  Series* l1 = z * y1;
  clock2 = clock();

  cout << (float)(clock2 - clock1)/CLOCKS_PER_SEC << endl;
}
