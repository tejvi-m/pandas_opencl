#include "./../src/DataFrame/DataFrame.cpp"
#include "./../src/DataFrame/helpers.cpp"
#include "./../src/DataFrame/SeriesInt.cpp"
#include "./../src/DataFrame/SeriesFloat.cpp"
#include "./../src/DataFrame/SeriesStr.cpp"
#include <random>
#include <ctime>
#include <cmath>
#include <iomanip>
#include <sys/time.h>

using namespace std;

int main(int argc, char *argv[]){
  vector<int> v1(atoi(argv[1]) * 2), v2(atoi(argv[1]) * 2);
  vector<int> v3(atoi(argv[1]) * 2), v4(atoi(argv[1]) * 2);
  vector<int> v5(atoi(argv[1]) * 2), v6(atoi(argv[1]) * 2);
  vector<int> v7(atoi(argv[1]) * 2), v8(atoi(argv[1]) * 2);

  int num = atoi(argv[2]);

  setup();
    struct timeval start, end; 
  std::generate(v1.begin(), v1.end(), std::rand);
  std::generate(v2.begin(), v2.end(), std::rand);
  std::generate(v3.begin(), v3.end(), std::rand);
  std::generate(v4.begin(), v4.end(), std::rand);

  std::generate(v5.begin(), v5.end(), std::rand);
  std::generate(v6.begin(), v6.end(), std::rand);
  std::generate(v7.begin(), v7.end(), std::rand);
  std::generate(v8.begin(), v8.end(), std::rand);

  DataFrame d1({new SeriesInt(v1), new SeriesInt(v3), new SeriesInt(v7), new SeriesInt(v5)}, {"a", "b", "c", "d"});
  DataFrame d2({new SeriesInt(v2), new SeriesInt(v4), new SeriesInt(v8), new SeriesInt(v6)}, {"a", "b", "c", "d"});
  
  Session session;
  // Session session;
  
  if(num == 1){
    d1.add(d2);

  }

  if(num == 2){
    d1.add(d2);
    d1.sub(d2);
  }

  if(num == 3){
    d1.add(d2);
    d1.sub(d2);
    d1.transform(std::string("x + 1"));
    }

  if(num == 4){
    d1.add(d2);
  d1.sub(d2);
d1.transform(std::string("x + 1"));
  d1.mul(d2);
  }  
  
  if(num == 5){
    d1.add(d2);
  d1.sub(d2);
  d1.transform(std::string("x + 1"));
  d1.mul(d2);
  d1.div(d2);

  }

  if(num == 6){
d1.add(d2);
  d1.sub(d2);
  d1.transform(std::string("x + 1"));
  d1.mul(d2);
  d1.div(d2);
  d1.sub(d2);

  }
  
  gettimeofday(&start, NULL);
  session.compute();
  // session.compute();
  gettimeofday(&end, NULL); 
  double time_taken; 
  
    time_taken = (end.tv_sec - start.tv_sec) * 1e6; 
    time_taken = (time_taken + (end.tv_usec -  
                              start.tv_usec)) * 1e-6; 
  
    cout<< fixed 
         << time_taken << setprecision(6); 
    // cout << " sec" << endl; 
//   cout << (Int)(clock2 - clock1)/CLOCKS_PER_SEC << endl;

  return 0;
}
