#include <iostream>
#include <unordered_map>
#include <vector>
#include <variant>
#include <string>
#include <algorithm>
#include "Series.cpp"
/*
Implementation:
the dataframe should be able to support heterogenous data:
hence using std::variant
There are only some allowed types - int, float, string, char

hashmaps are used for indexing the data (using this insertion and deletion of data becomes O(1))
in case the indexing row is not specified, we have to generate IDs use that
as the default index.
...
*/


/*
Operations to be supported:
constructors: read from CSV

rename columns
drop rows
drop columns

lookup and retrieval

*/


/*
Column Major

Dataframe is a vector of Seriesa

*/

struct print
{
   template <class T>
   void operator()(T&& _in){std::cout << _in;}
};

template<typename T>
void print(Series<T> data){
  data.print();
}


using vTypes = std::variant<int, std::string, char, float>;

class DataFrame{
private:
    std::vector<Series<vTypes>> dataframe_;
    std::vector<std::string> columns_;
    std::string index_;

public:
  DataFrame(){
    dataframe_ = {};
  };

  DataFrame(std::vector<Series<vTypes>> data, std::vector<std::string> columns, std::string index): dataframe_(data), columns_(columns), index_(index){

    // what intermediate representation do we get this from
    // initializing with index specified and all that

    auto indexIt = std::find(columns.begin(), columns.end(), index);
    int indexCol = std::distance(columns.begin(), indexIt);

    std::cout << "indexCol" << indexCol << std::endl;

    auto x = dataframe_[0];

    print(dataframe_[0]);
    // for(int i = 0; i < data.size(); i++){
    //
    //     // dimension checking
    //     // seeing if the column specified as index actually exists
    //
    //
    //
    //     // need to be more fnacy to get this to happen
    //     // dataFrame_[data[i][indexCol]] = data[i];
    //
    //
    //     // just printing, as a sanity check of sorts
    //     for (const auto& nextVariant : data[i])
    //         {
    //             std::visit(print{}, nextVariant);
    //             std::cout << " ";
    //         }
    //     std::cout << std::endl;
    // }

  };
  //
  // template <typename T>
  // void drop(std::vector<T>, int axis);
  //   // depending on axis and columns given, drop rows/columns
  //
  // template <typename T>
  // void rename(std::vector<T>, std::vector<T>, int axis);



};


// running small sanity checks
int main(){
  Series<vTypes> v({1, 2, 3});
  std::vector<Series<vTypes>> x{v};
  std::vector<std::string> cols{"s"};

  DataFrame df(x, cols, "s");
  return 0;
}
