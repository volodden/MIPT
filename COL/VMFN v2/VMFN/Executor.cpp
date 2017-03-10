//
//  Executor.cpp
//  VMFN
//
//  Created by Денис Володин on 04/03/2017.
//  Copyright © 2017 Денис Володин. All rights reserved.
//

#include "Executor.h"

void Executor::printTableRow( const unsigned int n ) {
    for( int i = 0; i < 4; ++i ) {
        std::cout << table[n][i] << (i == 3 ? '\n' : ' ');
    }
}

void Executor::printTable( std::string file ) {
    
    std::ofstream out( file );
    
    for( int n = 0; n < table.size(); ++n ) {
        for( int i = 0; i < 4; ++i ) {
            out << (table[n][i] < 10 ? "00" : (table[n][i] < 100 ? "0" : ""));
            out << table[n][i] << (i == 3 ? '\n' : ' ');
        }
    }
    
    out.close();
}

void Executor::work( const std::string& file_in ) {
    
    prepare( file_in );
    
    int current_address = table[0][3];
    bool finish = false;
    while( true ) {
        
        current_address = table[0][3];
        
        int reg1 = table[current_address][0];
        int reg2 = table[current_address][1];
        int reg3 = table[current_address][2];
        int reg4 = table[current_address][3];
        
        switch( reg1 ) {
            case Codes::INP: {
                std::cin >> table[table[reg4][3]][3];
                table[0][3] -= 1;
                break;
            }
            case Codes::OUT: {
                std::cout << table[table[reg4][3]][3] << '\n';
                table[0][3] -= 1;
                break;
            }
            case Codes::OUS: {
                std::cout << char( table[reg4][3] );
                table[0][3] -= 1;
                break;
            }
            case Codes::MVP: {
                table[table[reg2][3]][3] = table[table[reg4][3]][3];
                table[0][3] -= 1;
                break;
            }
            case Codes::MVV: {
                table[table[reg2][3]][3] = reg4;
                table[0][3] -= 1;
                break;
            }
            case Codes::MSV: {
                table[0][3] -= 1;
                break;
            }
            case Codes::VAR: {
                table[topStack][0] = Codes::ADN;
                table[topStack][1] = 0;
                table[topStack][2] = reg4;
                table[topStack][3] = 0;
                table[0][3] -= 1;
                break;
            }
            case Codes::VR2: {
                table[reg4][3] = topStack;
                table[0][3] -= 1;
                ++topStack;
                break;
            }
                
            case Codes::PRP: {
                table[topStack][0] = Codes::AEF;
                table[topStack][1] = topStack;
                table[topStack][2] = 0;
                table[topStack][3] = table[reg4][3];
                table[0][3] -= 1;
                ++topStack;
                break;
            }
            case Codes::FMV: {
                table[topStack][0] = Codes::ADN;
                table[topStack][1] = table[topStack-1][1];
                table[topStack][2] = 0;
                table[topStack][3] = table[table[reg4][3]][3];
                
                ++topStack;
                table[0][3] -= 1;
                break;
            }
            case Codes::CAL: {
                table[table[topStack-1][1]][2] = table[0][3];
                table[0][3] = reg4 - 1;
                break;
            }
            case Codes::FUN: {
                table[0][3] = reg4;
                break;
            }
            case Codes::FU2: {
                table[table[topStack-1][1]][1] += 1;
                table[0][3] -= 1;
                break;
            }
            case Codes::FAV: {
                table[table[table[topStack-1][1]][1]][2] = table[reg4][3];
                table[0][3] -= 1;
                break;
            }
            case Codes::FA2: {
                table[reg4][3] = table[table[topStack-1][1]][1];
                table[0][3] -= 1;
                break;
            }
            case Codes::RET: {
                --topStack;
                table[0][3] -= ( table[topStack][0] == Codes::AEF ) ? 1 : 0;
                //+         Найти метку начала функции.
                //+         Передать значение.
                //+         Вернуть прежнее значение ранее объявленным переменным.
                //+         Вернуться в нужное место в списке команд.
                break;
            }
            case Codes::RE2: {
                table[table[topStack][3]][3] = table[table[reg4][3]][3];
                table[0][3] -= 1;
                ++topStack;
                break;
            }
            case Codes::RE3: {
                if( table[topStack][0] != Codes::ADN || table[topStack][1] == 0 ) {
                    table[0][3] -= 2;
                    break;
                }
                table[topStack][1] = table[topStack][2];
                table[0][3] -= 1;
                break;
            }
            case Codes::RE4: {
                if( table[table[topStack][2]][0] == Codes::APN ) {
                    table[table[topStack][2]][3] = table[topStack][1];
                    table[0][3] += 1;
                    ++topStack;
                    break;
                }
                table[topStack][2] = table[table[topStack][2]][2];
                break;
            }
            case Codes::RE5: {
                table[0][3] = table[topStack][2] - 1;
                break;
            }
                
            case Codes::ADD: {
                table[table[reg2][3]][3] += table[table[reg4][3]][3];
                table[0][3] -= 1;
                break;
            }
            case Codes::DIF: {
                table[table[reg2][3]][3] -= table[table[reg4][3]][3];
                table[0][3] -= 1;
                break;
            }
            case Codes::MUL: {
                table[table[reg2][3]][3] *= table[table[reg4][3]][3];
                table[0][3] -= 1;
                break;
            }
            case Codes::LAB: {
                table[0][3] -= 1;
                break;
            }
            case Codes::LQJ: {
                table[0][3] = ( table[table[reg4][3]][3] <= 0 ) ? reg2 : table[0][3] - 1;
                break;
            }
            case Codes::MQJ: {
                table[0][3] = ( table[table[reg4][3]][3] >= 0 ) ? reg2 : table[0][3] - 1;
                break;
            }
            case Codes::EQJ: {
                table[0][3] = ( table[table[reg4][3]][3] == 0 ) ? reg2 : table[0][3] - 1;
                break;
            }
            case Codes::NEJ: {
                table[0][3] = ( table[table[reg4][3]][3] != 0 ) ? reg2 : table[0][3] - 1;
                break;
            }
            case Codes::LEJ: {
                table[0][3] = ( table[table[reg4][3]][3] < 0 ) ? reg2 : table[0][3] - 1;
                break;
            }
            case Codes::MOJ: {
                table[0][3] = ( table[reg4][3] > 0 ) ? reg2 : table[0][3] - 1;
                break;
            }
            case Codes::STP: {
                finish = true;
                break;
            }
            default: {
                std::cerr << "Command not found\n";
            }
        }
        
        //printTable( "//Users//volodden//Desktop//Study//VMFN v2//file.txt" );
        
        if( finish ) {
            printTable( "//Users//volodden//Desktop//Study//VMFN v2//byte-code-in-end.txt" );
            break;
        }
    }
}

void Executor::prepare( const std::string& file_in ) {
    
    std::ifstream in( file_in );
    
    topStack = 0;
    
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
    
    for( unsigned int i = 1; i < table.size(); ++i ) {
        if( table[i][0] == 0 ) {
            topStack = i;
            break;
        }
    }
    
    in.close();
}
