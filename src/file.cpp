#include <variant>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <vector>
#include <stdexcept> // std::runtime_error
#include <sstream> // std::stringstream
#include "DataFrame/DataFrame.cpp"
#include "DataFrame/helpers.cpp"
#include "DataFrame/SeriesInt.cpp"
#include "DataFrame/SeriesFloat.cpp"
#include "DataFrame/SeriesStr.cpp"

using vType = std::variant<std::string, float, int> ;

void create_Series(std::vector<Series *>& data, std::string col_type, std::vector<int>& dtypes)
{
    if(!(col_type.compare("INT")))
    {    
        data.push_back(new SeriesInt());
        dtypes.push_back(1);
    }
    else if(!(col_type.compare("FLOAT")))
    {
        data.push_back(new SeriesFloat());
        dtypes.push_back(0);
    }
    else if(!(col_type.compare("STRING")))
    {
        data.push_back(new SeriesStr());
        dtypes.push_back(2);
    }
    else 
        throw std::runtime_error("Invalid data type");
}

// std::stringstream& operator>>(std::stringstream& os, vType *v) 
// {
//   std::visit([&os](auto &e){ os >> e; }, *v);
//   return os;
// }

// std::ostream& operator<<(std::ostream& os, vType const& v) 
// {
//   std::visit([&os](auto &e){ os << e << "\t"; }, v);
//   return os;
// }

// void extend(Series* column, vType const& v)
// {
//   std::visit([&column](auto &e){ column->append(e); }, v);
// }

DataFrame read_csv(const std::string filename)
{
    std::ifstream myFile(filename);
    if(!myFile.is_open()) throw std::runtime_error("Could not open file");

    std::string line, col;
    std::string val;

    /*
    The first of line input contains the column name and type in the format:
    Col_Name : DType, Col_Name : DType, ...
    where DType = INT, FLOAT, STRING
    */
    if(myFile.good())
    {
        std::vector<Series *> data;
        std::vector<std::string> columns;
        std::vector<int> dtypes;

        // Extract the first line in the file
        std::getline(myFile, line);
        std::stringstream ss(line);

        while(std::getline(ss, col, ','))
        { 
            std::stringstream ss1(col);
            ss1 >> val; //Column Name
            columns.push_back(val);
            ss1 >> val; // ':' character
            ss1 >> val; //DType
            create_Series(data, val, dtypes);
        }

        int i;
        int ival;
        std::string sval;
        float fval;
        
        while(std::getline(myFile, line))
        {
            std::stringstream ss(line);
            i = 0;
            while(std::getline(ss, col, ','))
            { 
                //vType cell; //default is string(according to the order of variants), needs constant to be set
                std::stringstream ss1(col);
                //ss1 >> &cell;
                //std::cout << cell; //works
                //extend(data[i], cell); //doesnt work

                switch (dtypes[i])
                {
                    case 0:
                        ss1 >> fval;
                        data[i]->append(fval);
                        break;
                    case 1:
                        ss1 >> ival;
                        data[i]->append(ival);
                        break;
                    case 2:
                        ss1 >> sval;
                        data[i]->append(sval);
                        break;
                }
                i++;
            }
        }
        DataFrame df(data, columns);
        df.printDF();
        return df;
    }
    myFile.close();     
}

// int main() 
// {
//     read_csv("example.csv");
//     return 0;
// }