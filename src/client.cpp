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


  SeriesInt x111({1, 2, 3, 4});
  SeriesInt y111({1, 2, 3, 4});

  Series* xp = &x111;
  Series* yp = &y111;

  Series* xaaa = x111+yp;
  xaaa -> show();
  return 0;
}
