#include "DataFrame/DataFrame.cpp"
#include "DataFrame/helpers.cpp"
#include "DataFrame/SeriesInt.cpp"
#include "DataFrame/SeriesFloat.cpp"
#include "DataFrame/SeriesStr.cpp"

int main(){
  DataFrame x({new SeriesInt({1, 2, 3}), new SeriesStr({"11", "22", "22"}), new SeriesInt({0, 0, 0})}, {"a", "b", "c"}, "a");
  x.printDF();

  // x.drop("c");


  x.printDF();

  x.rename("a", "i");

  x.drop("i");
  x.printDF();

  std::cout  << "lookup" << std::endl;
  Series* y = x["c"];
  y -> show();

  std::cout  << "--" << std::endl;
  x.add(new SeriesInt({1, 2, 2,2,2}), "d");

  x.printDF();


  std::vector<std::string> colsToAdd{"b", "d"};
  DataFrame ss = x[colsToAdd];
  std::cout  << "--" << std::endl;
  ss.printDF();

  Row z = ss.iloc(1);
  // std::cout << z;
  printRow(z);


  SeriesFloat x111({1, 2.2, 2.3, 4});
  SeriesFloat y111({1, 2, 3, 2.4});


  Series* xcp = (&x111)->copy();
  Series* xp = &x111;
  Series* yp = &y111;

  Series* xaaa = x111+yp;
  xaaa -> show();

  Series* xmaaa = x111 * yp;
  std::cout << "++++++++++++++++++++" << std::endl;
  xmaaa -> show();
  std::cout << "++++++++++++++++++++" << std::endl;


  SeriesInt x111111({1, 2, 3, 4, 5, 6});
  SeriesInt y111111({1, 2, 3, 4, 5, 6});

  SeriesInt z1111111 = x111111 + y111111;
  z1111111.show();

  x111.div(yp);
  std::cout << "++++++++++++++++++++" << std::endl;
  x111.show();
  std::cout << "-----" << std::endl;
// need a function to that works on Series*, Series* - inplace update, though
  (*xp).sub(yp);
  (*xp).show();
  std::cout << "---" << std::endl;
  std::cout << "++++++++++++++++++++" << std::endl;

  (*xcp).map(std::unordered_map<float, float>({{1, 0.2}, {4, 0.1}}));
  xcp -> show();

  return 0;
}
