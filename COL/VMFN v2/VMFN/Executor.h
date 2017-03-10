//
//  Executor.h
//  VMFN
//
//  Created by Денис Володин on 04/03/2017.
//  Copyright © 2017 Денис Володин. All rights reserved.
//

#pragma once

#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include "CommandCodes.h"

class Executor {
public:
    
    void work( const std::string& file_in );

private:
    
    void prepare( const std::string& file_in );
    
    void printTableRow( const unsigned int n );
    void printTable( std::string file );
    
    std::vector<std::vector<int> > table;
    unsigned int topStack;
};

