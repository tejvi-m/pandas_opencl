#include <vector>
#include <string>
#include <variant>
#include <unordered_map>

using Row = std::vector<std::variant<int, std::string, float>>;
using vTypes = std::variant<int, std::string, float>;

class Series{
public:
  virtual ~Series(){}
  virtual std::vector<int>& getVec(int){}
  virtual std::vector<std::string>& getVec(std::string){}
  virtual std::vector<float>& getVec(float){}

  virtual long int size(){}
  virtual void Index(){}
  virtual void show(){}

  virtual vTypes operator[](int){}
  virtual int index(int){}

  virtual Series* operator+(Series*){}
  virtual void add(Series*, Series*){}
  virtual void add(Series*){}

  virtual Series* operator-(Series*){}
  virtual void sub(Series*, Series*){}
  virtual void sub(Series*){}

  virtual Series* operator*(Series*){}
  virtual void mul(Series*, Series*){}
  virtual void mul(Series*){}

  virtual Series* operator/(Series*){}
  virtual void div(Series*, Series*){}
  virtual void div(Series*){}

  virtual Series* copy(){}

  virtual void map(std::unordered_map<std::string, std::string>){}
  virtual void map(std::unordered_map<int, int>){}
  virtual void map(std::unordered_map<float, float>){}

  virtual bool isArithmetic(){}
  // all of these are in place
  // template<typename T>
  // virtual Series* operator+(T val){}
  // virtual Series* operator-(T val){}
  // virtual Series* operator*(T val){}
  // virtual Series* operator/(T val){}
  // virtual Series* operator%(T val){}

  virtual Series* append(int){}
  virtual Series* append(std::string){}
  virtual Series* append(float){}
};

class SeriesInt : public Series{
private:
  std::vector<int> series_;
  int size_;
  std::unordered_map<int, int> index_;
public:
  SeriesInt();
  SeriesInt(std::vector<int> data);
  virtual std::vector<int>& getVec(int);
  virtual long int size();
  virtual void show();
  virtual void Index();
  virtual vTypes operator[](int i);


  virtual Series* operator*(Series* src2);
  virtual void mul(Series* src2, Series* dst);
  virtual void mul(Series* src2);

  virtual void div(Series*);

  virtual void sub(Series*);

  virtual void map(std::unordered_map<int, int>);

  virtual Series* operator+(Series* src2);
  SeriesInt operator+(Series& src2);
  void add(Series& src2);
  virtual void add(Series* src2);
  virtual Series* append(int ele);
  virtual int index(int i);

  virtual bool isArithmetic();

  virtual Series* copy();
};

class SeriesStr : public Series{
private:
  std::vector<std::string> series_;
  int size_;
  std::unordered_map<float, int> index_;
public:
  SeriesStr();
  SeriesStr(std::vector<std::string> data);
  virtual std::vector<std::string>& getVec(std::string);
  virtual long int size();
  virtual void show();
  virtual vTypes operator[](int i);
  virtual Series* copy();
  virtual void map(std::unordered_map<std::string, std::string>);
  virtual Series* append(std::string);
  virtual bool isArithmetic();

};

class SeriesFloat : public Series{
private:
  std::vector<float> series_;
  int size_;
  std::unordered_map<float, int> index_;
public:
  SeriesFloat();
  SeriesFloat(std::vector<float> data);
  virtual std::vector<float>& getVec(float);
  virtual long int size();
  virtual void show();
  virtual void Index();
  virtual vTypes operator[](int i);
  virtual int index(float i);

virtual void map(std::unordered_map<float, float>);

    virtual Series* operator+(Series*);
    // virtual void add(Series*, Series*);
    // virtual void add(Series*);

    // virtual Series* operator-(Series*);
    // virtual void sub(Series*, Series*);
    virtual void sub(Series*);

    virtual void add(Series*);

    virtual Series* operator*(Series*);
    virtual void mul(Series*, Series*);
    virtual void mul(Series*);

    // virtual Series* operator/(Series*);
    // virtual void div(Series*, Series*);
    virtual void div(Series*);

    virtual Series* copy();
  virtual Series* append(float);

  virtual bool isArithmetic();
};
