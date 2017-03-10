//
//  main.cpp
//  VMFN
//
//  Created by Денис Володин on 04/03/2017.
//  Copyright © 2017 Денис Володин. All rights reserved.
//

#include <iostream>

#include "Translator.h"
#include "Executor.h"
#include "Generator.h"

int main(int argc, const char * argv[]) {

    Translator translator;
    
    const std::string from = "//Users//volodden//Desktop//Study//VMFN v2//code.txt";
    const std::string to = "//Users//volodden//Desktop//Study//VMFN v2//byte_code.txt";
    const std::string to_2 = "//Users//volodden//Desktop//Study//VMFN v2//code_dis.txt";
    
    translator.work( from, to );
    
    Executor executor;
    
    executor.work( to );
    
    std::cout << "\nDONE\n";
    
    Generator generator;
    
    generator.work( to, to_2 );
    
    return 0;
}
