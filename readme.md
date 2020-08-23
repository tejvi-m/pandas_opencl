# GPU acclerated Pandas-like data manipulation library (OpenCL)

Implemented in C++, used boost::python for python bindings.

supports execution in serial mode, eager GPU execution mode and delayed GPU execution mode.

GPU execution mode works best with larger datasets and larger number of continuous operations.


### Usage:
clients files in ```src``` have a few examples.

```src/example.csv``` has the expected csv file format.

#### usage in python:

run ```src/make_so.sh```, creating a file  ```DataFrame.so```.

one can ```import DataFrame``` from the folder containing the .so file.


additionally, one can use ```run.sh``` to convert any code written for eager GPU execution to delayed execution code.
