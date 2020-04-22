#include "DataFrame/DataFrame.cpp"
#include "DataFrame/helpers.cpp"
#include "DataFrame/Series.h"
#include "DataFrame/SeriesFloat.cpp"
#include "DataFrame/SeriesInt.cpp"
#include "DataFrame/SeriesStr.cpp"
#include "DataFrame/Graph.h"
#include "DataFrame/Graph.cpp"
#include <numeric>
#include <ctime>
#include <cmath>
#include <iomanip>
#include <random>
#include <string>
#include <boost/python.hpp>

// void add(DataFrame)

 BOOST_PYTHON_MODULE(DataFrame)  // Name here must match the name of the final shared library, i.e. mantid.dll or mantid.so
 {
    boost::python::def("setup", &setup);
    boost::python::class_<DataFrame>("DataFrame")
        .def(boost::python::init<std::string>())
        .def("showDF", &DataFrame::printDF)
        .def("add", (void(DataFrame::*)(DataFrame&))&DataFrame::add)
        // .def("")
      ;
 }
