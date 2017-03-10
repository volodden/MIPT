//
//  Translator.h
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

class Translator {
public:
    
    void work( const std::string& file_in, const std::string& file_out);
    
private:
    
    void prepare();
    
    void analyze( const std::string& file_in );
    
    void update( const unsigned int address,
                 const std::string s,
                 const std::string reg1,
                 const std::string reg2,
                 const std::string reg3,
                 const std::string reg4 );
    
    const unsigned int chooseCommand( const std::string s );
    
    const std::string correctToStr( const int number );
    
    int addNewVariable( const std::string s );
    int addNewString( const std::string s, const std::string str );
    int addNewCommand( const std::string s,
                       const std::string reg1,
                       const std::string reg2,
                       const std::string reg3,
                       const std::string reg4 );
    
    void analyzeVAR( std::ifstream& in );
    void analyzeMSV( std::ifstream& in );
    
    void translateINP( std::ifstream& in );
    void translateOUT( std::ifstream& in );
    void translateOUS( std::ifstream& in );
    void translateMVP( std::ifstream& in );
    void translateMVV( std::ifstream& in );
    void translateMSV( std::ifstream& in );
    void translateVAR( std::ifstream& in );
    void translateADD( std::ifstream& in );
    void translateDIF( std::ifstream& in );
    void translateMUL( std::ifstream& in );
    
    
    void translatePRP( std::ifstream& in );
    void translateFMV( std::ifstream& in );
    void translateCAL( std::ifstream& in );
    void translateFUN( std::ifstream& in );
    void translateFAV( std::ifstream& in );
    void translateRET( std::ifstream& in );
    
    
    void translateLAB( std::ifstream& in );
    void translateNER( std::ifstream& in, unsigned int typeCode );
    void translateSTP();
    
    void checkLabels();
    bool isNERCode( std::string );
    
    std::vector<std::vector<std::string>> bcode;
    unsigned int addressVar;
    unsigned int addressCom;
    unsigned int addressLastVar;
    
};

