#pragma once

#include <iostream>
#include <string>
#include <setjmp.h>
#include <stdlib.h>
#include <cassert>
#include <memory>

//#define DEBUG_MODE

void printText( std::string message ) {
    
#ifdef DEBUG_MODE
    std::cout << message << '\n';
#endif
    
}

class Exception {
public:
    Exception( std::string initMessage ) : message(initMessage) {}
    
    virtual ~Exception() {}
    
    std::string getMessage() {
        return message;
    }
    
private:
    
    std::string message;
};

class ExceptionT1 : public Exception {
public:
    ExceptionT1( std::string initMessage ) : Exception(initMessage) {}
};
 
class ExceptionT2 : public Exception {
public:
    ExceptionT2( std::string initMessage ) : Exception(initMessage) {}
};

class ExceptionData {
public:
    
    void setException( std::shared_ptr<Exception> exptn ) {
        exception = exptn;
    }
    
    std::shared_ptr<Exception> getException() {
        return exception;
    }
    
    void setData( ExceptionData* data ) {
        lastData = data;
    }
    
    ExceptionData* getData() {
        return lastData;
    }
    
    jmp_buf* getBuf() {
        return &buf;
    }
    
private:
    
    std::shared_ptr<Exception> exception;
    ExceptionData* lastData;
    jmp_buf buf;
};

bool isCatched = false;
bool isOutCatchBlocks = false;
ExceptionData* exceptionData;
ExceptionData* temp;
int jmp_value;

#define TRY( CODE )                                                                                         \
    printText("\n__TRY__BEGIN__\n");                                                                        \
    if( isCatched == false && jmp_value != 0 ) {                                                            \
        std::cerr << "Not catched exception: " << exceptionData->getException()->getMessage() << '\n';      \
        exit(1);                                                                                            \
    }                                                                                                       \
    isCatched = false;                                                                                      \
    temp = new ExceptionData();                                                                             \
    temp->setData( exceptionData );                                                                         \
    exceptionData = temp;                                                                                   \
    isOutCatchBlocks = false;                                                                               \
    jmp_value = setjmp(*exceptionData->getBuf());                                                           \
    if( jmp_value == 0 ) {                                                                                  \
                                                                                                            \
        CODE;                                                                                               \
                                                                                                            \
    }                                                                                                       \
    printText("\n__TRY__END__\n");

#define CATCH( TYPE, ERROR, CODE )                                                                          \
    printText("\n__CATCH__BEGIN__\n");                                                                      \
    if( ( jmp_value != 0 ) && ( isCatched == false ) &&                                                     \
        std::dynamic_pointer_cast<TYPE>( exceptionData->getException() ) ) {                                \
        isCatched = true;                                                                                   \
        std::shared_ptr<TYPE> ERROR = std::dynamic_pointer_cast<TYPE>( exceptionData->getException() );     \
        exceptionData = exceptionData->getData();                                                           \
                                                                                                            \
        CODE;                                                                                               \
                                                                                                            \
    } else {                                                                                                \
        printText("\n__CATCH__NO__\n");                                                                     \
    }                                                                                                       \
    isOutCatchBlocks = true;                                                                                \
    printText("\n__CATCH__END__\n");

#define THROW( EXCEPTION )                                                                                  \
    printText("\n__THROW__BEGIN__\n");                                                                      \
    if( exceptionData == NULL ) {                                                                           \
        std::cerr << "EXCEPTION!\n";                                                                        \
        exit(1);                                                                                            \
    }                                                                                                       \
    if( isOutCatchBlocks && isCatched == false) {                                                           \
        exceptionData = exceptionData->getData();                                                           \
    }                                                                                                       \
    isCatched = false;                                                                                      \
    exceptionData->setException( std::shared_ptr<Exception>(EXCEPTION) );                                   \
    printText("\n__THROW__END__\n");                                                                        \
    longjmp( *exceptionData->getBuf(), 1 );                                                                 \
