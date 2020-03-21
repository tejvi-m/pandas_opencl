#include "file.cpp"

int main(){
    DataFrame x = read_csv("./src/example.csv");
    x["a"] -> show();

    auto  y = x.copy();
    std::cout << x.shape().first;
    std::cout << x.shape().second<< std::endl;
    // x.drop("a");
    std::cout << x.shape().first;
    std::cout << x.shape().second << std::endl;
    std::cout << y.shape().first;
    std::cout << y.shape().second<< std::endl;

    x.printDF();

    auto z = y + x;
    z.printDF();

    y.add(x);
    y.printDF();

    auto z1 = y - x;
    z1.printDF();

    z1.sub(y);
    z1.printDF();

    auto z2 = z * x;
    z2.printDF();

    z2.mul(x);
    z2.printDF();

    auto z3 = z / x;
    z3.printDF();

    z3.div(x);
    z3.printDF();


    return 0;
}
