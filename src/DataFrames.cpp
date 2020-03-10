#include <iostream>
#include <unordered_map>
#include <vector>
#include <variant>
#include <string>
#include <algorithm>

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

struct print
{
   template <class T>
   void operator()(T&& _in){std::cout << _in;}
};



using vTypes = std::variant<int, std::string, char, float>;

template<typename T1>
class DataFrame{
private:
  std::unordered_map<T1, std::vector<vTypes>> dataFrame_;
public:
  DataFrame(){
    dataFrame_ = {};
  };

  DataFrame(std::vector<std::vector<vTypes>> data, std::vector<std::string> columns, std::string index){

    // what intermediate representation do we get this from
    // initializing with index specified and all that

    auto indexIt = std::find(columns.begin(), columns.end(), index);
    int indexCol = std::distance(columns.begin(), indexIt);

    for(int i = 0; i < data.size(); i++){

        // dimension checking
        // seeing if the column specified as index actually exists



        // need to be more fnacy to get this to happen
        // dataFrame_[data[i][indexCol]] = data[i];


        // just printing, as a sanity check of sorts
        for (const auto& nextVariant : data[i])
            {
                std::visit(print{}, nextVariant);
                std::cout << " ";
            }
        std::cout << std::endl;
    }

  };

  template <typename T>
  void drop(std::vector<T>, int axis);
    // depending on axis and columns given, drop rows/columns

  template <typename T>
  void rename(std::vector<T>, std::vector<T>, int axis);



};


// running small sanity checks
int main(){
  std::vector<std::vector<vTypes>> v{{1, 2, "a"},{2, 2, "b"}, {3, 2, "c"} };
  DataFrame<int> df(v, {"1", "2", "3"}, "1");
  return 0;
}
