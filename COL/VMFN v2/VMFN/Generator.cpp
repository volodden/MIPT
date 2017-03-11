//
//  Generator.cpp
//  VMFN
//
//  Created by Денис Володин on 08/03/2017.
//  Copyright © 2017 Денис Володин. All rights reserved.
//

#include "Generator.h"

void Generator::work( const std::string file_in, const std::string file_out ) {
    
    prepare( file_in );
    
    unsigned int i = 1;
    bool finish = false;
    
    std::ofstream out( file_out );
    
    while( true ) {
        switch( table[i][0] ) {
            case 0: {
                out << '\n';
                finish = true;
                break;
            }
            case Codes::ADN: {
                std::cerr << "ERROR\n";
                break;
            }
            case Codes::ADS: {
                std::string name = "str" + std::to_string( i );
                variablesStrings.insert( std::make_pair( i, name ) );
                out << "MSV " << name << ' ';
                while( table[i][2] != 0 ) {
                    out << char( table[i][3] );
                    ++i;
                }
                out << '\n';
                break;
            }
            case Codes::APN: {
                std::string name = "num" + std::to_string( i );
                variablesNumbers.insert( std::make_pair( i, name ) );
                out << "VAR " << name << '\n';
                break;
            }
            case Codes::AEF: {
                std::cerr << "ERROR\n";
                break;
            }
        }
        ++i;
        if( finish ) {
            finish = false;
            break;
        }
    }
    
    i = (unsigned int) table.size() - 1;
    while( true ) {
        --i;
        switch( table[i][0] ) {
            case 0: {
                finish = true;
                break;
            }
            case Codes::INP: {
                out << "INP " << variablesNumbers.find( table[i][3] )->second << '\n';
                break;
            }
            case Codes::OUT: {
                out << "OUT " << variablesNumbers.find( table[i][3] )->second << '\n';
                break;
            }
            case Codes::OUS: {
                out << "OUS " << variablesStrings.find( table[i][3] )->second << '\n';
                while( true ) {
                    if( table[table[i][3]][2] == 0 ) {
                        break;
                    }
                    --i;
                }
                break;
            }
            case Codes::MVP: {
                out << "MVP " << variablesNumbers.find( table[i][1] )->second << ' '
                << variablesNumbers.find( table[i][3] )->second << '\n';
                break;
            }
            case Codes::MVV: {
                out << "MVV " << variablesNumbers.find( table[i][1] )->second << ' '
                << table[i][3] << '\n';
                break;
            }
            case Codes::MSV:
            case Codes::VAR: {
                break;
            }
            case Codes::ADD: {
                out << "ADD " << variablesNumbers.find( table[i][1] )->second << ' '
                << variablesNumbers.find( table[i][3] )->second << '\n';
                break;
            }
            case Codes::DIF: {
                out << "DIF " << variablesNumbers.find( table[i][1] )->second << ' '
                << variablesNumbers.find( table[i][3] )->second << '\n';
                break;
            }
            case Codes::MUL: {
                out << "MUL " << variablesNumbers.find( table[i][1] )->second << ' '
                << variablesNumbers.find( table[i][3] )->second << '\n';
                break;
            }
            case Codes::PRP: {
                out << "PRP " << variablesNumbers.find( table[i][3] )->second << '\n';
                break;
            }
            case Codes::FMV: {
                out << "FMV " << variablesNumbers.find( table[i][3] )->second << '\n';
                break;
            }
            case Codes::CAL: {
                out << "CAL func" << table[i][3] << '\n';
                break;
            }
            case Codes::FUN: {
                out << "FUN func" << i << '\n';
                break;
            }
            case Codes::FU2: {
                break;
            }
            case Codes::FAV: {
                out << "FAV " << variablesNumbers.find( table[i][3] )->second << '\n';
                break;
            }
            case Codes::FA2: {
                break;
            }
            case  Codes::RET: {
                break;
            }
            case  Codes::RE2: {
                out << "RET " << variablesNumbers.find( table[i][3] )->second << '\n';
                break;
            }
            case  Codes::RE3:
            case  Codes::RE4:
            case  Codes::RE5: {
                break;
            }
            case Codes::LAB: {
                out << "LAB label" << i << '\n';
                break;
            }
            case Codes::LEJ: {
                out << "LEJ " << variablesNumbers.find( table[i][3] )->second << " label" << table[i][1] << '\n';
                break;
            }
            case Codes::MOJ: {
                out << "MOJ " << variablesNumbers.find( table[i][3] )->second << " label" << table[i][1] << '\n';
                break;
            }
            case Codes::LQJ: {
                out << "LQJ " << variablesNumbers.find( table[i][3] )->second << " label" << table[i][1] << '\n';
                break;
            }
            case Codes::MQJ: {
                out << "MQJ " << variablesNumbers.find( table[i][3] )->second << " label" << table[i][1] << '\n';
                break;
            }
            case Codes::EQJ: {
                out << "EQJ " << variablesNumbers.find( table[i][3] )->second << " label" << table[i][1] << '\n';
                break;
            }
            case Codes::NEJ: {
                out << "NEJ " << variablesNumbers.find( table[i][3] )->second << " label" << table[i][1] << '\n';
                break;
            }case Codes::STP: {
                out << "STP\n";
                break;
            }
        }
        
        if( finish ) {
            break;
        }
    }
    
    out.close();
}

void Generator::prepare( const std::string file_in ) {
    
    std::ifstream in( file_in );
    
    while( true ) {
        
        int s;
        
        table.push_back( std::vector<int>(0) );
        for( unsigned int i = 0; i < 4; ++i ) {
            in >> s;
            table[table.size()-1].push_back(s);
        }
        
        if( in.eof() ) {
            break;
        }
    }
    
    in.close();
}
