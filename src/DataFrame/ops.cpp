struct add{
  template<typename T>
  int operator()(T src, T val){
    return src + val;
  }
}

struct subtract{
  template<typename T>
  int operator()(T src, T val){
    return src - val;
  }
}

struct multiply{
  template<typename T>
  int operator()(T src, T val){
    return src * val;
  }
}

struct divide{
  template<typename T>
  int operator()(T src, T val){
    return src / val;
  }
}

struct add{
  template<typename T>
  int operator()(T src, T val){
    return src % val;
  }
}
