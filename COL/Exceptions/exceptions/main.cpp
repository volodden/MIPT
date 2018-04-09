#include <iostream>
#include "exception.h"

int main() {
    
#define EXAMPLE_N_6
    
#ifdef EXAMPLE_N_1 // Простой пример типизации
    TRY(
        std::cout << "TEST 1_1\n";
        THROW( new ExceptionT2("EXAMPLE 1") );
        std::cout << "TEST 1_2\n";
    );
    
    CATCH( ExceptionT1, excpt,
          std::cout << "CATCH 1_1\n";
          std::cout << excpt->getMessage() << '\n';
    );
    CATCH( ExceptionT2, excpt,
          std::cout << "CATCH 1_2\n";
          std::cout << excpt->getMessage() << '\n';
    );
    
    std::cout << '\n';
#endif // EXAMPLE_N_1
    
#ifdef EXAMPLE_N_2 // Одно исключение дважды не обрабатывается.
    TRY(
        std::cout << "TEST 2_1\n";
        THROW( new ExceptionT1("EXAMPLE 2") );
        std::cout << "TEST 2_2\n";
    );
    
    CATCH( ExceptionT1, excpt,
          std::cout << "CATCH 2_1\n";
          std::cout << excpt->getMessage() << '\n';
    );
    CATCH( ExceptionT1, excpt,
          std::cout << "CATCH 2_2\n";
          std::cout << excpt->getMessage() << '\n';
    );
    CATCH( Exception, excpt,
          std::cout << "CATCH 2_3\n";
          std::cout << excpt->getMessage() << '\n';
    );
    
    std::cout << '\n';
#endif // EXAMPLE_N_2
    
#ifdef EXAMPLE_N_3 // Что будет, когда не ловится исключение.
    THROW( new ExceptionT1("EXAMPLE 3") );
    
    std::cout << '\n';
#endif // EXAMPLE_N_3
    
#ifdef EXAMPLE_N_4 // Что будет, когда не ловится исключение. v2
    TRY(
        std::cout << "TEST 4_1\n";
        THROW( new Exception("EXAMPLE 4_1") );
        std::cout << "TEST 4_2\n";
    );
    
    CATCH( Exception, excpt,
          std::cout << "CATCH 4_1\n";
          std::cout << excpt->getMessage() << '\n';
    );
    
    THROW( new ExceptionT1("EXAMPLE 4_2") );
    
    std::cout << '\n';
#endif // EXAMPLE_N_4
    
#ifdef EXAMPLE_N_5 // Случай, когда нет подходящего catch-блока
    TRY(
        std::cout << "TEST 5_1\n";
        THROW( new Exception("EXAMPLE 5") );
        std::cout << "TEST 5_2\n";
    );
    
    CATCH( ExceptionT1, excpt,
          std::cout << "CATCH 5_1\n";
          std::cout << excpt->getMessage() << '\n';
    );
    
    std::cout << '\n';
#endif // Example_N_5
    
#ifdef EXAMPLE_N_6 // Вложенные исключения
    TRY(
        std::cout << "TEST 6_1\n";
        TRY(
            std::cout << "TEST 6_2\n";
            THROW( new Exception("EXAMPLE 6_1"));
            std::cout << "TEST 6_3\n";
        );
        CATCH( Exception, excpt,
              std::cout << "CATCH 6_1\n";
              std::cout << excpt->getMessage() << '\n';
        );
        std::cout << "TEST 6_4\n";
        THROW( new Exception("EXAMPLE 6_2"));
        std::cout << "TEST 6_5\n";
    );
    CATCH( Exception, excpt,
        std::cout << "CATCH 6_2\n";
        std::cout << excpt->getMessage() << '\n';
    );
#endif // EXAMPLE_N_6
    
#ifdef EXAMPLE_N_7 // Вложенные исключения v2
    TRY(
        std::cout << "TEST 7_1\n";
        TRY(
            std::cout << "TEST 7_2\n";
            //THROW( new Exception("EXAMPLE 7_1"));
            std::cout << "TEST 7_3\n";
            );
        CATCH( Exception, excpt,
              std::cout << "CATCH 7_1\n";
              std::cout << excpt->getMessage() << '\n';
              );
        std::cout << "TEST 7_4\n";
        THROW( new Exception("EXAMPLE 7_2"));
        std::cout << "TEST 7_5\n";
        );
    CATCH( Exception, excpt,
          std::cout << "CATCH 7_2\n";
          std::cout << excpt->getMessage() << '\n';
          );
#endif // EXAMPLE_N_7
    
#ifdef EXAMPLE_N_8 // Вложенные исключения v3
    TRY(
        std::cout << "TEST 8_1\n";
        TRY(
            std::cout << "TEST 8_2\n";
            THROW( new Exception("EXAMPLE 8_1"));
            std::cout << "TEST 8_3\n";
            );
        CATCH( Exception, excpt,
              std::cout << "CATCH 8_1\n";
              std::cout << excpt->getMessage() << '\n';
              );
        std::cout << "TEST 8_4\n";
        //THROW( new Exception("EXAMPLE 8_2"));
        std::cout << "TEST 8_5\n";
        );
    CATCH( Exception, excpt,
          std::cout << "CATCH 8_2\n";
          std::cout << excpt->getMessage() << '\n';
          );
#endif // EXAMPLE_N_8
    
#ifdef EXAMPLE_N_9 // Вложенные исключения v4
    TRY(
        std::cout << "TEST 9_1\n";
        TRY(
            std::cout << "TEST 9_2\n";
            //THROW( new Exception("EXAMPLE 9_1"));
            std::cout << "TEST 9_3\n";
            );
        CATCH( Exception, excpt,
              std::cout << "CATCH 9_1\n";
              std::cout << excpt->getMessage() << '\n';
              );
        std::cout << "TEST 9_4\n";
        //THROW( new Exception("EXAMPLE 9_2"));
        std::cout << "TEST 9_5\n";
        );
    CATCH( Exception, excpt,
          std::cout << "CATCH 9_2\n";
          std::cout << excpt->getMessage() << '\n';
          );
#endif // EXAMPLE_N_9
    
#ifdef EXAMPLE_N_10 // Исключение в CATCH
    TRY(
        std::cout << "TEST 10_1\n";
        THROW( new Exception("EXAMPLE 10_1"));
        std::cout << "TEST 10_2\n";
    );
    CATCH( Exception, excpt,
          std::cout << "CATCH 10_1\n";
          std::cout << excpt->getMessage() << '\n';
          THROW( new Exception("EXAMPLE 10_1"));
    );
#endif // EXAMPLE_N_10
    
#ifdef EXAMPLE_N_11 // Исключение в CATCH, а потом ещё один блок
    TRY(
        std::cout << "TEST 11_1\n";
        THROW( new Exception("EXAMPLE 11_1"));
        std::cout << "TEST 11_2\n";
    );
    CATCH( Exception, excpt,
        std::cout << "CATCH 11_1\n";
        std::cout << excpt->getMessage() << '\n';
        TRY(
            std::cout << "TEST 11_3\n";
            THROW( new Exception("EXAMPLE 11_2"));
            std::cout << "TEST 11_4\n";
        );
        CATCH( Exception, excpt,
            std::cout << "CATCH 11_2\n";
            std::cout << excpt->getMessage() << '\n';
        );
    );
    TRY(
        std::cout << "TEST 11_5\n";
        THROW( new Exception("EXAMPLE 11_3"));
        std::cout << "TEST 11_6\n";
    );
    CATCH( Exception, excpt,
          std::cout << "CATCH 10_3\n";
          std::cout << excpt->getMessage() << '\n';
    );
#endif // EXAMPLE_N_11
    
    std::cout << '\n';
    
    TRY();
    
	return 0;
}
