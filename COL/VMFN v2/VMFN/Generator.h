//
//  Generator.h
//  VMFN
//
//  Created by Денис Володин on 08/03/2017.
//  Copyright © 2017 Денис Володин. All rights reserved.
//

#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <iostream>
#include <map>
#include "CommandCodes.h"

class Generator {
    
public:
    
    void work( const std::string file_in, const std::string file_out );
    
private:
    
    void prepare( const std::string file_in );
    
    std::vector<std::vector<int> > table;
    std::map<int, std::string> variablesNumbers;
    std::map<int, std::string> variablesStrings;
    std::map<int, std::string> functions;
    
};
