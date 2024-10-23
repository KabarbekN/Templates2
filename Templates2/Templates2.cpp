#include <iostream>
#include <vector>
#include <initializer_list>
using namespace std;

template<class T>
class List
{
    vector<T> list;
public:
    void add(T item)
    {
        list.push_back(item);
    }

    void remove(int index)
    {
        list.erase(list.begin() + index);
    }

    auto getMin()
    {
        auto pMin = list.begin();
        for (auto it = list.begin(); it < list.end(); it++)
        {
            if (*it < *pMin)
            {
                pMin = it;
            }
        }
        return *pMin;
    }

    auto getMax()
    {
        auto pMax = list.begin();
        for (auto it = list.begin(); it < list.end(); it++)
        {
            if (*it > *pMax)
            {
                pMax = it;
            }
        }
        return *pMax;
    }
};

template<>
class List<const char *>
{
    vector<const char*> list;
public:
    void add(const char* item)
    {
        list.push_back(item);
    }

    void remove(int index)
    {
        list.erase(list.begin() + index);
    }

    auto getMin()
    {
        auto pMin = list.begin();
        for (auto it = list.begin(); it < list.end(); it++)
        {
            //if (*it < *pMin)
            if (strcmp(*it, *pMin) < 0)
            {
                pMin = it;
            }
        }
        return *pMin;
    }

    auto getMax()
    {
        auto pMax = list.begin();
        for (auto it = list.begin(); it < list.end(); it++)
        {
            //if (*it > *pMax)
            if (strcmp(*it, *pMax) > 0)
            {
                pMax = it;
            }
        }
        return *pMax;
    }
};

//template <class T, int height, int width>
//class Matrix
//{
//    T m[height][width];
//public:
//    const auto & operator()(int j, int i) const
//    {
//        return m[j][i]; // const T&
//    }
//};


//template <int height, int width>
//class Matrix<const char*, height, width>
//{
//
//    const char* m[height][width];
//};

template<typename T1, typename T2>
struct Pair
{
    T1 first;
    T2 second;

    Pair() : first{ T1() }, second{ T2() } {}
    Pair(const T1& x, const T2& y) : first{ x }, second{ y } {}

    void display() const
    {
        cout << "(" << first << ", " << second << ")" << endl;
    }

    bool operator==(const Pair& pair)
    {
        return this->first == pair.first && this->second == pair.second;
    }

    bool operator!=(const Pair& pair)
    {
        auto a = this;
        auto b = *this;
        cout << &a << " " << endl;
        cout << &b << " " <<  endl;
        cout << this << endl;
        cout << &(*this) << endl;
        cout << &pair << endl;
        cout << &(*(&pair)) << endl;

        return !(*this == pair);
    }

};

#pragma once
#include <iostream>
void stopProgram(std::string message) {
    cout << "stop";
}

template <class T>
class Matrix
{
public:
    int height;
    int width;
    T** m;
private:
    bool allocate(int height, int width)
    {
        if (height <= 0 && width <= 0)
        {
            return false;
        }
        this->height = height;
        this->width = width;
        m = new T * [height];
        for (int j = 0; j < height; j++)
        {
            m[j] = new T[width];
            for (int i = 0; i < width; i++)
            {
                m[j][i] = T();
            }
        }
        return true;
    }
    void clear()
    {
        if (m != nullptr)
        {
            for (int j = 0; j < height; j++)
            {
                delete[] m[j];
            }
            delete[] m;
        }
        m = nullptr;
    }
    void copyTo(T** from)
    {
        for (int j = 0; j < height; j++)
        {
            for (int i = 0; i < width; i++)
            {
                m[j][i] = from[j][i];
            }
        }
    }
public:
    Matrix(int height, int width)
    {
        if (height <= 0 || width <= 0)
        {
            stopProgram("Wrong sizes!");
        }
        if (!allocate(height, width))
        {
            stopProgram("Wrong sizes!");
        }
    }
    Matrix(int size) : Matrix(size, size)
    {}
    Matrix()
    {
        height = width = 0;
        m = nullptr;
    }
    Matrix(const Matrix& matrix)
    {
        clear();
        allocate(matrix.height, matrix.width);
        copyTo(matrix.m);
    }
    ~Matrix()
    {
        clear();
    }
    auto& operator()(int j, int i)
    {
        if (j < 0 || j >= height
            || i < 0 || i >= width)
        {
            stopProgram("Matrix index error!");
        }
        return m[j][i];
    }
    Matrix<T>& operator=(const Matrix<T>& matrix)
    {
        if (&matrix == this)
        {
            return *this;
        }
        clear();
        allocate(matrix.height, matrix.width);
        copyTo(matrix.m);
        return *this;
    }
    friend std::ostream& operator<<(std::ostream& output,
        const Matrix& matrix)
    {
        if (matrix.m == nullptr)
        {
            output << "Empty matrix" << std::endl;
        }
        for (int j = 0; j < matrix.height; j++)
        {
            for (int i = 0; i < matrix.width; i++)
            {
                output << " " << matrix.m[j][i];
            }
            output << std::endl;
        }
        return output;
    }
};

template <class T>
class NumberMatrix : public Matrix<T>
{
public:
    NumberMatrix(int height, int width) : Matrix<T>(height, width) {}
    NumberMatrix(int size) : NumberMatrix(size) {}
    void func() {
        
        cout << this->heigth;
    }
};



//int getSum(int count, int first, ...)
//{
//    int sum = 0;
//    
//    int* p = &first;
//
//    while (count--)
//    {
//        sum += *p;
//        p++;
//        p++;
//    }
//    return sum;
//}

double getSum(double x) 
{
    return x;
}

template <class... Args>
double getSum(double x, Args... args)
{
    return x + getSum(args...); 
}



void print() // ничего не делает
{}


template <class First, class... Other>
void print(const First& first, const Other&... other)
{
    cout << first;
    print(other...);
}
template <class... Args>
void println(const Args&... args)
{
    print(args...);
    cout << endl;
}
struct Point
{
    int x;
    int y;
    friend std::ostream& operator<<(std::ostream& output,
        const Point& p)
    {
            output << "(" << p.x << "," << p.y << ")";
        return output;
    }
};
template <class T>
class IntArray
{
private:
    size_t length;
    T* data;
public:
    IntArray() : length(0), data(nullptr)
    {
    }
    IntArray(int length) : length(length)
    {
        data = new T[length];
    }
    ~IntArray()
    {
        delete[] data;
    }
        T& operator[](int index)
    {
        return data[index];
    }
    int getLength() const
    {
        return length;
    }

    IntArray(const initializer_list<T>& list) : IntArray( list.size() ) {
        int i = 0;
        for (auto& element : list)
        {
            data[i] = element;
            i++;
        }
    }

    T operator[](int index) const {
        return data[index];
    }
};


int main()
{

    IntArray<int> intArray{ 5, 1, 2, 3, 4, 5, 6, 7, 8, 9, 6, 8, 5 };
    for (int i = 0; i < 7; i ++)
    {
        cout << intArray[i] << " ";
    }
    cout << endl;
    //cout << getSum(5, 1, 2, 3, 4, 5, 6, 7, 8, 9, 6, 8, 5);
    println("Hello, world");
    println("Pi = ", 3.14, '\n', 2, " * ", 2, " = ", 2 * 2);
    Point point{ 12,2 };
    println("Point: ", point);








  /*  Pair<int, int> point1{ 0, 0 };
    Pair<int, int> point2{ 1, 1 };


    Pair<string, string> name{ "John", "smith" };
    Pair<Pair<string, string>, int> mark{ name, 8 };*/
    //cout << &point1 << endl;
    //cout << &point2 << endl;


    //Matrix<int> matrix{5};

    //NumberMatrix<int> numberMatrix{ 5, 5 };

    //numberMatrix.func();

    //cout << matrix(1, 1);
    
    //List<int> listInt;
    //listInt.add(5);
    //listInt.add(24);
    //listInt.add(-250);
    //cout << listInt.getMin() << endl;
    //cout << listInt.getMax() << endl;

    //List<const char *> listString;

    //listString.add("adsadsa");
    //listString.add("dadsa");
    //listString.add("cadsasadasddsa");
    //listString.add("scasaadsadsa");

    //cout << listString.getMax() << endl;
    //cout << listString.getMin() << endl;


}