//
//  Translator.cpp
//  VMFN
//
//  Created by Денис Володин on 04/03/2017.
//  Copyright © 2017 Денис Володин. All rights reserved.
//

#include "Translator.h"

const unsigned int TABLE_SIZE = 16;
const unsigned int COUNT_COLUMN = 5;

void Translator::work( const std::string& file_in, const std::string& file_out ) {
    
    prepare();
    
    analyze( file_in );
    
    std::ifstream in(file_in);
    
    while( true ) {
        std::string s;
        in >> s;
        
        switch( chooseCommand(s) ) {
            case Codes::INP: {
                translateINP( in );
                break;
            }
            case Codes::OUT: {
                translateOUT( in );
                break;
            }
            case Codes::OUS: {
                translateOUS( in );
                break;
            }
            case Codes::STP: {
                translateSTP();
                break;
            }
            case Codes::MVP: {
                translateMVP( in );
                break;
            }
            case Codes::MVV: {
                translateMVV( in );
                break;
            }
            case Codes::MSV: {
                //translateMSV( in );
                break;
            }
            case Codes::VAR: {
                translateVAR( in );
                break;
            }
            case Codes::ADD: {
                translateADD( in );
                break;
            }
            case Codes::DIF: {
                translateDIF( in );
                break;
            }
            case Codes::MUL: {
                translateMUL( in );
                break;
            }
            case Codes::PRP: {
                translatePRP( in );
                break;
            }
            case Codes::FMV: {
                translateFMV( in );
                break;
            }
            case Codes::CAL: {
                translateCAL( in );
                break;
            }
            case Codes::FUN: {
                translateFUN( in );
                break;
            }
            case Codes::FAV: {
                translateFAV( in );
                break;
            }
            case Codes::RET: {
                translateRET( in );
                break;
            }
            case Codes::LAB: {
                translateLAB( in );
                break;
            }
            case Codes::LQJ: {
                translateNER( in, Codes::LQJ );
                break;
            }
            case Codes::MQJ: {
                translateNER( in, Codes::MQJ );
                break;
            }
            case Codes::EQJ: {
                translateNER( in, Codes::EQJ );
                break;
            }
            case Codes::NEJ: {
                translateNER( in, Codes::NEJ );
                break;
            }
            case Codes::LEJ: {
                translateNER( in, Codes::LEJ );
                break;
            }
            case Codes::MOJ: {
                translateNER( in, Codes::MOJ );
                break;
            }
        }
        
        if( in.eof() ) {
            break;
        }
    }
    
    in.close();
    
    checkLabels();
    
    std::ofstream out( file_out );
    
    for( unsigned int i = 0; i < bcode.size(); ++i ) {
        for( unsigned int j = 1; j < bcode[i].size(); ++j ) {
            out << bcode[i][j] << ( j + 1 == bcode[i].size() ? '\n' : ' ' );
        }
    }
    
    out.close();
}

void Translator::prepare() {
    addressVar = 1;
    addressLastVar = 0;
    addressCom = TABLE_SIZE * TABLE_SIZE;
    bcode.resize( addressCom );
    for( unsigned int i = 0; i < bcode.size(); ++i ) {
        bcode[i].resize( COUNT_COLUMN );
        bcode[i][0] = "";
        for( unsigned int j = 1; j < bcode[i].size(); ++j ) {
            bcode[i][j] = "000";
        }
    }
    --addressCom;
    bcode[0][4] = correctToStr( addressCom );
}

void Translator::analyze( const std::string& file_in ) {
    std::ifstream in( file_in );
    
    while( true ) {
        std::string s;
        
        in >> s;
        
        switch( chooseCommand(s) ) {
            case Codes::VAR: {
                analyzeVAR( in );
                break;
            }
            case Codes::MSV: {
                analyzeMSV( in );
                break;
            }
        }
        
        if( in.eof() ) {
            break;
        }
    }
    
    in.close();
}

void Translator::analyzeVAR( std::ifstream& in ) {
    std::string s;
    in >> s;
    int av = addressVar - 1;
    while( true ) {
        if( av == 0 ) {
            addressLastVar = addNewVariable( s );
            break;
        }
        if( bcode[av][0] == s ) {
            std::cerr << "ERROR\n";
            break;
        }
        --av;
    }
}

void Translator::analyzeMSV( std::ifstream& in ) {
    std::string s;
    in >> s;
    int av = addressVar - 1;
    while( true ) {
        if( av == 0 ) {
            std::string str;
            in >> str;
            addressLastVar = addNewString( s, str );
            break;
        }
        if( bcode[av][0] == s ) {
            std::cerr << "ERROR\n";
            break;
        }
        --av;
    }
}

void Translator::update( const unsigned int address,
             const std::string s,
             const std::string reg1,
             const std::string reg2,
             const std::string reg3,
             const std::string reg4 ) {
    bcode[address][0] = s;
    bcode[address][1] = reg1;
    bcode[address][2] = reg2;
    bcode[address][3] = reg3;
    bcode[address][4] = reg4;
}

const unsigned int Translator::chooseCommand( const std::string s ) {
    if( s == "INP" ) {
        return Codes::INP;
    }
    if( s == "OUT" ) {
        return Codes::OUT;
    }
    if( s == "OUS" ) {
        return Codes::OUS;
    }
    if( s == "MVV" ) {
        return Codes::MVV;
    }
    if( s == "MVP" ) {
        return Codes::MVP;
    }
    if( s == "MSV" ) {
        return Codes::MSV;
    }
    if( s == "VAR" ) {
        return Codes::VAR;
    }
    if( s == "ADD" ) {
        return Codes::ADD;
    }
    if( s == "DIF" ) {
        return Codes::DIF;
    }
    if( s == "MUL" ) {
        return Codes::MUL;
    }
    if( s == "PRP" ) {
        return Codes::PRP;
    }
    if( s == "FMV" ) {
        return Codes::FMV;
    }
    if( s == "CAL" ) {
        return Codes::CAL;
    }
    if( s == "FUN" ) {
        return Codes::FUN;
    }
    if( s == "FAV" ) {
        return Codes::FAV;
    }
    if( s == "RET" ) {
        return Codes::RET;
    }
    if( s == "LAB" ) {
        return Codes::LAB;
    }
    if( s == "LQJ" ) {
        return Codes::LQJ;
    }
    if( s == "MQJ" ) {
        return Codes::MQJ;
    }
    if( s == "EQJ" ) {
        return Codes::EQJ;
    }
    if( s == "NEJ" ) {
        return Codes::NEJ;
    }
    if( s == "LEJ" ) {
        return Codes::LEJ;
    }
    if( s == "MOJ" ) {
        return Codes::MOJ;
    }
    if( s == "STP" ) {
        return Codes::STP;
    }
    return 0;
}

const std::string Translator::correctToStr( const int number ) {
    if( number >= 0 && number < 10 ) {
        return ("00" + std::to_string(number));
    }
    if( number > -10 && number < 100 ) {
        return ("0" + std::to_string(number));
    }
    return std::to_string(number);
}

int Translator::addNewVariable( const std::string s ) {
    update( addressVar, s, correctToStr( Codes::APN ), "000", "000", "000" );
    addressLastVar = addressVar;
    ++addressVar;
    return addressLastVar;
}

int Translator::addNewString( const std::string s, const std::string str ) {
    addressLastVar = addressVar;
    for( unsigned int i = 0; i < str.size(); ++i ) {
        update( addressVar, (i == 0) ? s : "", correctToStr( Codes::ADS ), "000", correctToStr( addressVar+1 ), correctToStr( int( str[i] ) ) );
        ++addressVar;
    }
    update( addressVar, "", correctToStr( Codes::ADS ), "000", "000", correctToStr(int('\n')) );
    ++addressVar;
    return addressLastVar;
}

int Translator::addNewCommand( const std::string s,
                               const std::string reg1,
                               const std::string reg2,
                               const std::string reg3,
                               const std::string reg4 ) {
    update(addressCom, s, reg1, reg2, reg3, reg4 );
    --addressCom;
    return addressCom;
}

void Translator::translateINP( std::ifstream& in ) {
    std::string s;
    in >> s;
    int av = addressLastVar;
    while( true ) {
        if( av == 0 ) {
            std::cerr << "ERROR\n";
        }
        
        if( bcode[av][0] == s ) {
            addNewCommand( "", correctToStr( Codes::INP ), "000", "000", correctToStr( av ) );
            break;
        }
        --av;
    }
}

void Translator::translateOUT( std::ifstream& in ) {
    std::string s;
    in >> s;
    int av = addressLastVar;
    while( true ) {
        if( av == 0 ) {
            std::cerr << "ERROR\n";
            break;
        }
        
        if( bcode[av][0] == s ) {
            addNewCommand( "", correctToStr( Codes::OUT ), "000", "000", correctToStr( av ) );
            break;
        }
        --av;
    }
}

void Translator::translateOUS( std::ifstream& in ) {
    std::string s;
    in >> s;
    int av = addressLastVar;
    while( true ) {
        if( av == 0 ) {
            std::cerr << "ERROR\n";
            break;
        }
        
        if( bcode[av][0] == s ) {
            while( true ) {
                addNewCommand( "", correctToStr( Codes::OUS ), "000", "000", correctToStr( av ) );
                if( bcode[av][3] == "000" ) {
                    break;
                }
                av = std::stoi( bcode[av][3] );
            }
            break;
        }
        --av;
    }
}

void Translator::translateMVP( std::ifstream& in ) {
    std::string s;
    in >> s;
    int av1 = addressLastVar;
    while( true ) {
        if( av1 == 0 ) {
            std::cerr << "ERROR\n";
            break;
        }
        
        if( bcode[av1][0] == s ) {
            break;
        }
        --av1;
    }
    in >> s;
    int av2 = addressLastVar;
    while( true ) {
        if( av2 == 0 ) {
            std::cerr << "ERROR\n";
            break;
        }
        
        if( bcode[av2][0] == s ) {
            addNewCommand( "", correctToStr( Codes::MVP ), correctToStr( av1 ), "000", correctToStr( av2 ) );
            break;
        }
        --av2;
    }
}

void Translator::translateMVV( std::ifstream& in ) {
    std::string s;
    in >> s;
    int av = addressLastVar;
    while( true ) {
        if( av == 0 ) {
            std::cerr << "ERROR\n";
            break;
        }
        
        if( bcode[av][0] == s ) {
            break;
        }
        --av;
    }
    int n;
    in >> n;
    addNewCommand( "", correctToStr( Codes::MVV ), correctToStr( av ), "000", correctToStr( n ) );
}

void Translator::translateADD( std::ifstream& in ) {
    std::string s;
    in >> s;
    int av1 = addressLastVar;
    while( true ) {
        if( av1 == 0 ) {
            std::cerr << "ERROR\n";
            break;
        }
        
        if( bcode[av1][0] == s ) {
            break;
        }
        --av1;
    }
    in >> s;
    int av2 = addressLastVar;
    while( true ) {
        if( av2 == 0 ) {
            std::cerr << "ERROR\n";
            break;
        }
        
        if( bcode[av2][0] == s ) {
            addNewCommand( "", correctToStr( Codes::ADD ), correctToStr( av1 ), "000", correctToStr( av2 ) );
            break;
        }
        --av2;
    }
}

void Translator::translateDIF( std::ifstream& in ) {
    std::string s;
    in >> s;
    int av1 = addressLastVar;
    while( true ) {
        if( av1 == 0 ) {
            std::cerr << "ERROR\n";
            break;
        }
        
        if( bcode[av1][0] == s ) {
            break;
        }
        --av1;
    }
    in >> s;
    int av2 = addressLastVar;
    while( true ) {
        if( av2 == 0 ) {
            std::cerr << "ERROR\n";
            break;
        }
        
        if( bcode[av2][0] == s ) {
            addNewCommand( "", correctToStr( Codes::DIF ), correctToStr( av1 ), "000", correctToStr( av2 ) );
            break;
        }
        --av2;
    }
}

void Translator::translateMUL( std::ifstream& in ) {
    std::string s;
    in >> s;
    int av1 = addressLastVar;
    while( true ) {
        if( av1 == 0 ) {
            std::cerr << "ERROR\n";
            break;
        }
        
        if( bcode[av1][0] == s ) {
            break;
        }
        --av1;
    }
    in >> s;
    int av2 = addressLastVar;
    while( true ) {
        if( av2 == 0 ) {
            std::cerr << "ERROR\n";
            break;
        }
        
        if( bcode[av2][0] == s ) {
            addNewCommand( "", correctToStr( Codes::MUL ), correctToStr( av1 ), "000", correctToStr( av2 ) );
            break;
        }
        --av2;
    }
}

void Translator::translateVAR( std::ifstream& in ) {
    std::string s;
    in >> s;
    
    int av = addressLastVar;
    while( true ) {
        if( av == 0 ) {
            std::cerr << "ERROR\n";
            break;
        }
        
        if( bcode[av][0] == s ) {
            addNewCommand( "", correctToStr( Codes::VAR ), "000", "000", correctToStr( av ) );
            addNewCommand( "", correctToStr( Codes::VR2 ), "000", "000", correctToStr( av ) );
            break;
        }
        --av;
    }
}

void Translator::translatePRP( std::ifstream& in ) {
    std::string s;
    in >> s;

    int av = addressLastVar;
    while( true ) {
        if( av == 0 ) {
            std::cerr << "ERROR\n";
            break;
        }
        
        if( bcode[av][0] == s ) {
            addNewCommand( "", correctToStr( Codes::PRP ), "000", "000", correctToStr( av ) );
            break;
        }
        --av;
    }
}

void Translator::translateFMV( std::ifstream& in ) {
    std::string s;
    in >> s;
    
    int av = addressLastVar;
    while( true ) {
        if( av == 0 ) {
            std::cerr << "ERROR\n";
            break;
        }
        
        if( bcode[av][0] == s ) {
            addNewCommand( "", correctToStr( Codes::FMV ), "000", "000", correctToStr( av ) );
            break;
        }
        --av;
    }
}

void Translator::translateCAL( std::ifstream& in ) {
    std::string s;
    in >> s;
    
    bool functionsIsFound = false;
    unsigned int returnAddress = 0;
    for( unsigned int adV = addressCom + 1; adV < bcode.size(); ++adV ) {
        if( bcode[adV][1] == correctToStr( Codes::FUN ) ) {
            if( s == bcode[adV][0] ) {
                functionsIsFound = true;
                returnAddress = adV;
                break;
            }
        }
    }
    if( !functionsIsFound ) {
        std::cerr << "ERROR\n";
    }
    
    addNewCommand( s, correctToStr( Codes::CAL ), "000", "000", correctToStr( returnAddress ) );
}

void Translator::translateFUN( std::ifstream& in ) {
    std::string s;
    in >> s;
    for( unsigned int i = addressCom + 1; i < bcode.size(); ++i ) {
        if( bcode[i][0] == s && bcode[i][1] == correctToStr( Codes::FUN ) ) {
            std::cerr << "ERROR\n";
        }
    }
    addNewCommand( s, correctToStr( Codes::FUN ), "000", "000", "000" );
}

void Translator::translateFAV( std::ifstream& in ) {
    std::string s;
    in >> s;
    int av = addressLastVar;
    while( true ) {
        if( av == 0 ) {
            std::cerr << "ERROR\n";
            break;
        }
        
        if( bcode[av][0] == s ) {
            addNewCommand( "", correctToStr( Codes::FU2 ), "000", "000", "000" );
            addNewCommand( "", correctToStr( Codes::FAV ), "000", "000", correctToStr( av ) );
            addNewCommand( "", correctToStr( Codes::FA2 ), "000", "000", correctToStr( av ) );
            break;
        }
        --av;
    }
}

void Translator::translateRET( std::ifstream& in ) {
    std::string s;
    in >> s;
    int av = addressLastVar;
    while( true ) {
        if( av == 0 ) {
            std::cerr << "ERROR\n";
            break;
        }
        
        if( bcode[av][0] == s ) {
            addNewCommand( "", correctToStr( Codes::RET ), "000", "000", "000" );
            addNewCommand( "", correctToStr( Codes::RE2 ), "000", "000", correctToStr( av ) );
            addNewCommand( "", correctToStr( Codes::RE3 ), "000", "000", correctToStr( av ) );
            addNewCommand( "", correctToStr( Codes::RE4 ), "000", "000", correctToStr( av ) );
            addNewCommand( "", correctToStr( Codes::RET ), "000", "000", "000" );
            addNewCommand( "", correctToStr( Codes::RE5 ), "000", "000", "000" );
            break;
        }
        --av;
    }
    unsigned int ad = addressCom;
    while( true ) {
        ++ad;
        if( bcode[ad][1] == correctToStr( Codes::FUN ) ) {
            update( ad, bcode[ad][0], bcode[ad][1], bcode[ad][2], bcode[ad][3], correctToStr( addressCom ) );
            break;
        }
        if( ad == bcode.size() ) {
            std::cerr << "ERROR\n";
            break;
        }
    }
}

void Translator::translateLAB( std::ifstream& in ) {
    std::string s;
    in >> s;
    for( unsigned int i = addressCom + 1; i < bcode.size(); ++i ) {
        if( bcode[i][0] == s && bcode[i][1] == correctToStr( Codes::LAB ) ) {
            std::cerr << "ERROR\n";
        }
    }
    addNewCommand( s, correctToStr( Codes::LAB ), "000", "000", "000" );
}

void Translator::translateNER( std::ifstream& in, unsigned int typeCode ) {
    std::string s;
    in >> s;
    int av = addressLastVar;
    while( true ) {
        if( av == 0 ) {
            std::cerr << "ERROR\n";
            break;
        }
        if( bcode[av][0] == s ) {
            break;
        }
        --av;
    }
    in >> s;
    //Метки в байт-код ставятся потом
    addNewCommand( s, correctToStr( typeCode ), "000", "000", correctToStr( av ) );
}

void Translator::translateSTP() {
    addNewCommand( "", correctToStr( Codes::STP ), "000", "000", "000" );
}

void Translator::checkLabels() {
    for( unsigned int ad = addressCom + 1; ad < bcode.size(); ++ad ) {
        if( isNERCode( bcode[ad][1] ) ) {
            bool labelIsFound = false;
            for( unsigned int adL = addressCom + 1; adL < bcode.size(); ++adL ) {
                if( bcode[adL][1] == correctToStr( Codes::LAB ) ) {
                    if( bcode[ad][0] == bcode[adL][0] ) {
                        labelIsFound = true;
                        bcode[ad][2] = correctToStr(adL);
                        break;
                    }
                }
            }
            if( !labelIsFound ) {
                std::cerr << "ERROR\n";
            }
        }
    }
}

bool Translator::isNERCode( std::string s ) {
    return ( s == correctToStr(Codes::LQJ) ||
             s == correctToStr(Codes::MQJ) ||
             s == correctToStr(Codes::EQJ) ||
             s == correctToStr(Codes::NEJ) ||
             s == correctToStr(Codes::LEJ) ||
             s == correctToStr(Codes::MOJ) );
}
