 g++ -Wall -Wextra -fPIC -shared -fpermissive -I /usr/include/python3.8/ -lboost_python3 pybindings.cpp -o DataFrame.so -std=c++17 -lOpenCL
