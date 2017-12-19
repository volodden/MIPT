#include <iostream>
#include "reader.h"
#include "TypeList.h"

const char* PATH = "/Users/volodden/Desktop/Study/patterns.reader/input.txt";

int main(int argc, const char * argv[]) {
    
    //Оставлю закомментированный код как артефакты.
    //typedef Loki::Typelist<int, Loki::NullType> String_Int;
    //typedef LOKI_TYPELIST_3(int, char, int) String_IntCharInt;
    //typedef LOKI_TYPELIST_2(char, int) String_CharInt;
    //typedef LOKI_TYPELIST_4(String_IntCharInt, String_Int, String_CharInt, int) FinalType;
    //std::cout << Loki::TL::Length<FinalType>::value << "\n\n";
    
    typedef LOKI_TYPELIST_4(int, char, int, int) FinalType;
    
    Reader<FinalType> reader(PATH);
    
    while( true ) {
        void* data = reader.getNextLine();
        reader.printLineWithSeparators(data);
        //Новая строчка не может быть пустой!
        if( !reader.isNextLineExist() ) {
            break;
        }
    }
    
    return 0;
}
