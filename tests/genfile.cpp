#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <ctime>
#include <cmath>
#include <algorithm>

using namespace std;

int main(int argc, char const *argv[])
{
    vector<float> v1(atoi(argv[1]) * 2);
    std::generate(v1.begin(), v1.end(), std::rand);

    ofstream myfile;
    myfile.open ("test.csv");
    for(auto i = v1.begin(); i!=v1.end(); i++)
    {
       myfile << *i << endl;
    }
    myfile.close();

    return 0;
}
