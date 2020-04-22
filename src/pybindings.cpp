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
        .def("sub", (void(DataFrame::*)(DataFrame&))&DataFrame::sub)
        .def("div", (void(DataFrame::*)(DataFrame&))&DataFrame::div)
        .def("mul", (void(DataFrame::*)(DataFrame&))&DataFrame::mul)

        .def("add", (void(DataFrame::*)(float))&DataFrame::add)
        .def("sub", (void(DataFrame::*)(float))&DataFrame::sub)
        .def("div", (void(DataFrame::*)(float))&DataFrame::div)
        .def("mul", (void(DataFrame::*)(float))&DataFrame::mul)

        .def("add", (void(DataFrame::*)(int))&DataFrame::add)
        .def("sub", (void(DataFrame::*)(int))&DataFrame::sub)
        .def("div", (void(DataFrame::*)(int))&DataFrame::div)
        .def("mul", (void(DataFrame::*)(int))&DataFrame::mul)

        .def("copy", (DataFrame (DataFrame::*)())&DataFrame::copy)
        // .def("")
      ;
    boost::python::class_<Graph>("Graph")
      .def("compute", &Graph::compute);
 }
