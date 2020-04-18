#include <vector>
#include <variant>
#include <unordered_map>
#include <string>
#include "gpu/gpu.h"

using Row = std::vector<std::variant<int, std::string, float>>;


void printRow(Row data);

template <typename T>
void Add(std::vector<T>& src1, std::vector<T>& src2, std::vector<T>& dst);

template <typename T>
void print(std::vector<T>& data);

template <typename T>
void make_map(std::vector<T>& data, std::unordered_map<T, int>& umap);

template<typename T>
void Mul(std::vector<T>& src1, std::vector<T>& src2, std::vector<T>& dst);

template<typename T>
void Div(std::vector<T>& src1, std::vector<T>& src2, std::vector<T>& dst);

template<typename T>
void Sub(std::vector<T>& src1, std::vector<T>& src2, std::vector<T>& dst);

template<typename T>
void MapOp(std::vector<T>&, std::unordered_map<T, T>&);

template<typename T>
void redirectToGPU(std::string, std::vector<T>&, std::vector<T>&, std::vector<T>&, int);
