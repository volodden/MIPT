#ifndef Reader_h_included
#define Reader_h_included

#include <iostream>
#include <fstream>
#include "TypeList.h"

//Start.
//For test.
//
template <typename T>
void printType() {
    std::cout << "[" << typeid(T).name() << "]\n";
}

template<typename TList>
void printTypeList(TList tl) {
    printType<typename TList::Head>();
    printTypeList(typename TList::Tail());
}

template <>
void printTypeList<Loki::NullType>(Loki::NullType) {}
//
//For test.
//End.


//Start.
//Length of read data.
//
template<class TList>
struct LengthOfLine;

template<>
struct LengthOfLine<Loki::NullType>
{
    enum { value = 0 };
};

template<class Head, class Tail>
struct LengthOfLine<Loki::Typelist<Head, Tail> >
{
    enum { value = sizeof(Head) + LengthOfLine<Tail>::value };
};
//
//Length of read data.
//End.

//Start.
//For read.
//
template<typename InnerTL>
void readData(void* data, std::ifstream& in) {
    //printType<InnerTL>();
    //printType<typename InnerTL::Head>();
    typename InnerTL::Head valueToRead;
    in >> valueToRead;
    memcpy(data, &valueToRead, sizeof(typename InnerTL::Head));
    data = (typename InnerTL::Head*)data + sizeof(typename InnerTL::Head);
    readData<typename InnerTL::Tail>(data, in);
}

template<>
void readData<Loki::NullType>(void* data, std::ifstream& in) {}
//
//For read.
//End.


//Start.
//For print
//
template<typename InnerTL>
void printData(void* data) {
    std::cout << '[' << *((typename InnerTL::Head*)data) << ']';
    data = (typename InnerTL::Head*)data + sizeof(typename InnerTL::Head);
    printData<typename InnerTL::Tail>(data);
}

template<>
void printData<Loki::NullType>(void* data) {}
//
//For print.
//End.

template<typename CTypeList>
class Reader {
    
public:
    
    Reader(const char* path) {
        fin.open(path);
        //currentLine = 0;
        sizeOfLine = LengthOfLine<CTypeList>::value;
    }
    
    ~Reader() {
        fin.close();
        //currentLine = 0;
    }
    
    void* getNextLine() {
        
        void* data = (void*) malloc(sizeOfLine);
        
        //Тут было много кода, но я невнимательно прочитал задание.
        //
        //
        //typedef CTypeList remainingTypes;
        //
        //printType<remainingTypes>();
        //
        //std::cout << "LENGTH: " << Loki::TL::Length<CTypeList>::value << "\n";
        //printTypeList(CTypeList());
        //
        //for( int i = 0; i < Loki::TL::Length<CTypeList>::value; ++i ) {
        //    std::cout << "Index: " << i << "\n";
        //    printType<typename remainingTypes::Head>();
        //    typename remainingTypes::Head value;
        //    fin >> value;
        //    //std::cout << value << "\n";
        //    memcpy(data, &value, sizeof(typename remainingTypes::Head));
        //    data = (typename remainingTypes::Head*)data + sizeof(typename remainingTypes::Head);
        //
        //    //Но эта строчка не работает, и всё очень плохо.
        //    typedef typename CTypeList::Tail remainingTypes;
        //}
        //
        //++currentLine;
        
        //////////
        //
        //
        readData<CTypeList>(data, fin);
        //
        //
        //////////
        
        return data;
    }
    
    void printLineWithSeparators(void* data) {
        std::cout << '{';
        printData<CTypeList>(data);
        std::cout << '}' << '\n';
    }
    
    bool isNextLineExist() {
        char c;
        fin.get(c);
        return ((int)c != 0);
        //return currentLine != Loki::TL::Length<CTypeList>::value;
    }
    
private:
    
    std::ifstream fin;
    //int currentLine;
    int sizeOfLine;
};

#endif /* Reader_h_included */
