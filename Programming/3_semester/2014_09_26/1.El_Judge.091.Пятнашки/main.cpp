#include <iostream>
#include <map>
#include <vector>

#define u (std::cout << "u")
#define l (std::cout << "l")
#define r (std::cout << "r")
#define d (std::cout << "d")

short abs(short A)
{
    return A > 0 ? A : -A;
}

class matrix
{
private:

    int current;
    int ST;
    short matr[12];

public:

    matrix()
    {
    }

    matrix(short temp[9])
    {
        matr[9] = 0;
        for (short i = 0; i < 9; ++i)
        {
            matr[i] = temp[i];
            matr[9] += abs(i / 3 - ((matr[i] + 8) % 9) / 3);
            matr[9] += abs(i % 3 - ((matr[i] + 8) % 9) % 3);
        }
        matr[10] = -1;
        matr[11] = -1;
        current = 0;
        ST = 0;
    }

    matrix(const matrix& other)
    {
        for (short i = 0; i < 12; ++i)
        {
            matr[i] = other.matr[i];
        }
        current = other.current;
        ST = other.ST;
    }

    ~matrix()
    {
    }

    void shift(short i, short n)
    {
        matr[10] = i;
        matr[11] = n;
        n *= 2;
        ++n;
        matr[9] -= abs(i / 3 - ((matr[i] + 8) % 9) / 3)
                 + abs(i % 3 - ((matr[i] + 8) % 9) % 3)
                 + abs((i + n) / 3 - ((matr[i + n] + 8) % 9) / 3)
                 + abs((i + n) % 3 - ((matr[i + n] + 8) % 9) % 3);

        short k = matr[i];
        matr[i] = matr[i + n];
        matr[i + n] = k;

        matr[9] += abs(i / 3 - ((matr[i] + 8) % 9) / 3)
                 + abs(i % 3 - ((matr[i] + 8) % 9) % 3)
                 + abs((i + n) / 3 - ((matr[i + n] + 8) % 9) / 3)
                 + abs((i + n) % 3 - ((matr[i + n] + 8) % 9) % 3);
        ++ST;
    }

    matrix getParent()
    {
        if ((this->matr[10] == -1) || (this->matr[11] == -1))
        {
            return *this;
        }
        matrix temp(*this);
        temp.shift(this->matr[10], this->matr[11]);
        return temp;
    }

public:

    friend std::istream& operator >> (std::istream& in, matrix& m)
    {
        m.matr[9] = 0;
        for (short i = 0; i < 9; ++i)
        {
            in >> m.matr[i];
            m.matr[9] += abs(i / 3 - ((m.matr[i] + 8) % 9) / 3);
            m.matr[9] += abs(i % 3 - ((m.matr[i] + 8) % 9) % 3);
        }
        m.matr[10] = -1;
        m.matr[11] = -1;
        m.current = 0;
        m.ST = 0;
        return in;
    }

    friend std::ostream& operator << (std::ostream& out, const matrix& m)
    {
        for (short i = 0; i < 9; ++i)
        {
            out << m.matr[i] << (i % 3 == 2 ? "\n" : " ");
        }
        out << "\n";
        return out;
    }

    friend bool operator== (const matrix& left, const matrix& right)
    {
        for (short i = 0; i < 9; ++i)
        {
            if (left.matr[i] != right.matr[i])
            {
                return false;
            }
        }
        return true;
    }

    friend bool operator!= (const matrix& left, const matrix& right)
    {
        return !(left == right);
    }

    short h() const
    {
        return matr[9];
    }

    short find_zero() const
    {
        for (short i = 0; i < 9; ++i)
        {
            if (matr[i] == 0)
            {
                return i;
            }
        }
    }

    int steps() const
    {
        return ST;
    }

    int getCurrentNumber() const
    {
        return current;
    }

    void setCurrentNumber(int c)
    {
        current = c;
    }
};

matrix make_matrix(short temp[9])
{
    return matrix(temp);
}

class Vosm
{
private:

    matrix start;
    std::multimap < int, matrix > table; // h(x) + steps; matrix
    std::vector < std::pair < int , char > > memory;

public:

    Vosm(short temp[16])
    {
        short temp2[9];
        for (short i = 0; i < 3; ++i)
        {
            for (short j = 0; j < 3; ++j)
            {
                temp2[3*i + j] = bijection(temp[4*(i+1) + (j+1)]);
            }
        }
        start = make_matrix(temp2);
    }

    std::vector < char > findSolve()
    {
        std::vector < char > result;
        short q = start.h();
        if (q == 0)
        {
            result.push_back('q');
            return result;
        }
        table.insert(std::make_pair(0, start));
        memory.push_back(std::make_pair(-1, 'q'));
        result =  AStar();
        for (unsigned int i = 0; i < result.size() / 2; ++i)
        {
            char c = result[i];
            result[i] = result[result.size()-1-i];
            result[result.size()-1-i] = c;
        }
        return result;
    }

private:

    short bijection(short n) const
    {
        short T[16] = {0, -1, -1, -1, -1, -1, 1, 2, 3, -1, 4, 5, 6, -1, 7, 8};
        if ((n >= 0) && (n <= 16))
        {
            return T[n];
        }
        return -1;
    }

    void addV(matrix M, short i, short n)
    {
        char symbol;
        switch (n)
        {
            case 0: symbol = 'r'; break;
            case 1: symbol = 'd'; break;
            case 2: symbol = 'l'; break;
            case 3: symbol = 'u'; break;
        }
        n %= 2;
        matrix temp(M);
        temp.shift(i, n);

        if (temp != M.getParent())
        {
            temp.setCurrentNumber(memory.size());
            table.insert(std::make_pair(temp.h() + temp.steps(), temp));
            memory.push_back(std::make_pair(M.getCurrentNumber(), symbol));
        }
    }

    std::vector < char > AStar()
    {
        std::vector < char > reverseResult;
        while(true)
        {
            matrix M = table.begin()->second;
            table.erase(table.begin());

            short Z = M.find_zero();
            if (Z % 3 < 2) //right
            {
                addV(M, Z, 0);
            }
            if (Z % 3 > 0) //left
            {
                addV(M, Z - 1, 2);
            }
            if (Z / 3 < 2) //down
            {
                addV(M, Z, 1);
            }
            if (Z / 3 > 0) //up
            {
                addV(M, Z - 3, 3);
            }
            int q = table.begin()->second.h();

            if (q == 0)
            {
                int s = table.begin()->second.getCurrentNumber();
                while (memory[s].second != 'q')
                {
                    reverseResult.push_back(memory[s].second);
                    s = memory[s].first;
                }
                return reverseResult;
            }
        }
    }
};

class Pyatn
{
private:

    short doska[16];
    static const short mod = 4;
    short zero;

public:

    Pyatn()
    {
        for (short i = 0; i < 16; ++i)
        {
            std::cin >> doska[i];
        }
    }

    friend std::ostream& operator << (std::ostream& out, const Pyatn& p)
    {
        for (short i = 0; i < 16; ++i)
        {
            out << p.doska[i] << (i % mod == 3 ? "\n" : " ");
        }
        out << "\n";
        return out;
    }

    void findSolve()
    {
        if (!check())
        {
            std::cout << "NO\n";
            return;
        }
        std::cout << "YES\n";

        if (doska[3] != 4)
        {
            fourGoesToThePlace();
        }
        if (doska[2] != 3)
        {
            threeGoesToThePlace();
        }
        if (doska[1] != 2)
        {
            twoGoesToThePlace();
        }
        if (doska[0] != 1)
        {
            oneGoesToThePlace();
        }
        if (doska[4] != 5)
        {
            fiveGoesToThePlace();
        }
        if (doska[8] != 9)
        {
            nineGoesToThePlace();
        }
        if (doska[12] != 13)
        {
            thirteenGoesToThePlace();
        }

        Vosm temp(doska);
        std::vector < char > result = temp.findSolve();
        if (result[0] != 'q')
        {
            for (unsigned int i = 0; i < result.size(); ++i)
            {
                std::cout << result[i];
            }
        }
    }

private:

    bool check()
    {
        bool sum = true;
        for (int i = 0; i < 15; ++i)
        {
            if (doska[i] == 0)
            {
                sum = ((i / mod) % 2 == 0) ? !sum : sum;
                continue;
            }
            for (int j = i + 1; j <= 15; ++j)
            {
                if ((doska[j] != 0) && (doska[i] > doska[j]))
                {
                    sum = !sum;
                }
            }
        }
        return sum;
    }

    short findCell(short n) const
    {
        for (int i = 0; i < 16; ++i)
        {
            if (doska[i] == n)
            {
                return i;
            }
        }
        return -1;
    }

    void up()
    {
        u;
        doska[zero] = doska[zero-4];
        zero -= 4;
        doska[zero] = 0;
    }

    void left()
    {
        l;
        doska[zero] = doska[zero-1];
        --zero;
        doska[zero] = 0;
    }

    void right()
    {
        r;
        doska[zero] = doska[zero+1];
        ++zero;
        doska[zero] = 0;
    }

    void down()
    {
        d;
        doska[zero] = doska[zero+4];
        zero += 4;
        doska[zero] = 0;
    }

    void fourGoesToThePlace()
    {
        zero = findCell(0);
        short number = 4;
        short place;
        while ((place = findCell(number)) % mod != 3)
        {
            if (zero % mod == place % mod)
            {
                while (zero / mod < (place = findCell(number)) / mod)
                {
                    down();
                }
                right();
            }
            if (zero % mod > place % mod)
            {
                while (zero / mod < place / mod)
                {
                    down();
                }
                while (zero / mod > place / mod)
                {
                    up();
                }
                while (zero % mod > (place = findCell(number)) % mod)
                {
                    left();
                }
                continue;
            }
            if (zero / mod == place / mod)
            {
                (zero / mod == 3) ? up() : down();
            }
            while (zero % mod <= place % mod)
            {
                right();
            }
        }
        place = findCell(number);
        if ((zero % mod == place % mod) && (zero / mod < place % mod))
        {
            while (zero / mod < (place = findCell(number)) / mod)
            {
                down();
            }
        }
        if (doska[3] == 4)
        {
            return;
        }
        while (zero % mod != 2)
        {
            (zero % mod < 2) ? right() : left();
        }
        while (zero / mod != place / mod)
        {
            (zero / mod < place / mod) ? down() : up();
        }
        while ((place = findCell(number)) / mod != 0)
        {
            up();
            right();
            down();
            left();
            up();
        }
    }

    void threeGoesToThePlace()
    {
        zero = findCell(0);
        short number = 3;
        short place;
        while ((place = findCell(number)) % mod != 2)
        {
            if (place / mod == 0)
            {
                if (place == 0)
                {
                    if (zero / mod != 0)
                    {
                        while (zero % mod < 1)
                        {
                            right();
                        }
                        while (zero % mod > 1)
                        {
                            left();
                        }
                        while (zero / mod > 0)
                        {
                            up();
                        }
                    }
                    left();
                }
                if (zero == 0)
                {
                    down();
                }
                if (zero / mod != 0)
                {
                    while (zero % mod < 2)
                    {
                        right();
                    }
                    while (zero % mod > 2)
                    {
                        left();
                    }
                    while (zero / mod > 0)
                    {
                        up();
                    }
                }
                left();
                continue;
            }
            if (place % mod == 3)
            {
                if (zero % mod == 3)
                {
                    while (zero / mod < (place = findCell(number)) / mod)
                    {
                        down();
                    }
                    left();
                }
                while (zero / mod != place / mod)
                {
                    (zero / mod < place / mod) ? down() : up();
                }
                while (zero % mod < 3)
                {
                    right();
                }
                continue;
            }
            if (zero % mod == place % mod)
            {
                while (zero / mod < (place = findCell(number)) / mod)
                {
                    down();
                }
                right();
            }
            if (zero % mod > place % mod)
            {
                while (zero / mod < place / mod)
                {
                    down();
                }
                while (zero / mod > place / mod)
                {
                    up();
                }
                while (zero % mod > (place = findCell(number)) % mod)
                {
                    left();
                }
                continue;
            }
            if (zero / mod == place / mod)
            {
                (zero / mod < 3) ? down() : up();
            }
            right();
        }
        place = findCell(number);
        if ((zero % mod == place % mod) && (zero / mod < place % mod))
        {
            while (zero / mod < (place = findCell(number)) / mod)
            {
                down();
            }
        }
        if (doska[2] == 3)
        {
            return;
        }
        while (zero % mod != 1)
        {
            if (zero % mod < 1)
            {
                right();
            }
            else
            {
                if (zero / mod == place / mod)
                {
                    (zero / mod == 3) ? up() : down();
                }
                left();
            }
        }
        while (zero / mod != place / mod)
        {
            (zero / mod < place / mod) ? down() : up();
        }
        while ((place = findCell(number)) / mod != 0)
        {
            up();
            right();
            down();
            left();
            up();
        }
    }

    void twoGoesToThePlace()
    {
        zero = findCell(0);
        short number = 2;
        short place;
        while ((place = findCell(number)) % mod != 1)
        {
            if (place / mod == 0)
            {
                if (zero / mod != 0)
                {
                    while (zero % mod < 1)
                    {
                        right();
                    }
                    while (zero % mod > 1)
                    {
                        left();
                    }
                    while (zero / mod > 0)
                    {
                        up();
                    }
                }
                left();
                continue;
            }
            if (place % mod == 0)
            {
                if (zero % mod == 0)
                {
                    while (zero / mod < (place = findCell(number)) / mod)
                    {
                        down();
                    }
                    right();
                }
                while (zero / mod != place / mod)
                {
                    (zero / mod < place / mod) ? down() : up();
                }
                while (zero % mod > 0)
                {
                    left();
                }
                continue;
            }
            if (zero % mod == place % mod)
            {
                while (zero / mod < (place = findCell(number)) / mod)
                {
                    down();
                }
                left();
            }
            if (zero % mod < place % mod)
            {
                while (zero / mod < place / mod)
                {
                    down();
                }
                while (zero / mod > place / mod)
                {
                    up();
                }
                while (zero % mod < (place = findCell(number)) % mod)
                {
                    right();
                }
                continue;
            }
            if (zero / mod == place / mod)
            {
                (zero / mod < 3) ? down() : up();
            }
            left();
        }
        place = findCell(number);
        if ((zero % mod == place % mod) && (zero / mod < place % mod))
        {
            while (zero / mod < (place = findCell(number)) / mod)
            {
                down();
            }
        }
        if (doska[1] == 2)
        {
            return;
        }
        while (zero % mod != 0)
        {
            if (zero / mod == place / mod)
            {
                (zero / mod == 3) ? up() : down();
            }
            left();
        }
        while (zero / mod != place / mod)
        {
            (zero / mod < place / mod) ? down() : up();
        }
        while ((place = findCell(number)) / mod != 0)
        {
            up();
            right();
            down();
            left();
            up();
        }
    }

    void oneGoesToThePlace()
    {
        zero = findCell(0);
        short number = 1;
        short place;
        if (zero == 0)
        {
            down();
            if (doska[0] == 1)
            {
                return;
            }
        }
        while ((place = findCell(number)) % mod != 0)
        {
            if (zero % mod == place % mod)
            {
                while (zero / mod < (place = findCell(number)) / mod)
                {
                    down();
                }
                left();
            }
            if (zero % mod < place % mod)
            {
                while (zero / mod < place / mod)
                {
                    down();
                }
                while (zero / mod > place / mod)
                {
                    up();
                }
                while (zero % mod < (place = findCell(number)) % mod)
                {
                    right();
                }
                continue;
            }
            if (zero / mod == place / mod)
            {
                (zero / mod == 3) ? up() : down();
            }
            while (zero % mod >= place % mod)
            {
                left();
            }
        }
        place = findCell(number);
        if ((zero % mod == place % mod) && (zero / mod < place % mod))
        {
            while (zero / mod < (place = findCell(number)) / mod)
            {
                down();
            }
        }
        if (place / mod != 1)
        {
            if (place / mod == 3)
            {
                if (zero / mod != 2)
                {
                    (zero / mod < 2) ? down() : up();
                }
                while (zero % mod > 0)
                {
                    left();
                }
                down();
            }
            if (zero == 12)
            {
                right();
            }
            while (zero / mod != 1)
            {
                up();
            }
            while (zero % mod > 0)
            {
                left();
            }
            down();
        }
        while (zero % mod < 3)
        {
            right();
        }
        while (zero / mod > 0)
        {
            up();
        }
        while (zero % mod > 0)
        {
            left();
        }
        down();
        right();
        up();
        right();
        right();
        down();
    }

    void fiveGoesToThePlace()
    {
        zero = findCell(0);
        short number = 5;
        short place;
        while ((place = findCell(number)) % mod != 0)
        {
            if (zero % mod == place % mod)
            {
                while (zero / mod < (place = findCell(number)) / mod)
                {
                    down();
                }
                left();
            }
            if (zero % mod < place % mod)
            {
                while (zero / mod < place / mod)
                {
                    down();
                }
                while (zero / mod > place / mod)
                {
                    up();
                }
                while (zero % mod < (place = findCell(number)) % mod)
                {
                    right();
                }
                continue;
            }
            if (zero / mod == place / mod)
            {
                (zero / mod == 3) ? up() : down();
            }
            while (zero % mod >= place % mod)
            {
                left();
            }
        }
        place = findCell(number);
        if ((zero % mod == place % mod) && (zero / mod < place / mod))
        {
            while (zero / mod < (place = findCell(number)) / mod)
            {
                down();
            }
        }
        if (doska[4] == 5)
        {
            return;
        }
        if (place / mod == 3)
        {
            if (zero / mod != 2)
            {
                (zero / mod < 2) ? down() : up();
            }
            while (zero % mod > 0)
            {
                left();
            }
            down();
        }
        if (zero == 12)
        {
            right();
        }
        while (zero / mod != 1)
        {
            up();
        }
        while (zero % mod > 0)
        {
            left();
        }
        down();
    }

    void nineGoesToThePlace()
    {
        zero = findCell(0);
        short number = 9;
        short place;
        while ((place = findCell(number)) % mod != 0)
        {
            if (place / mod == 1)
            {
                if (zero / mod == 1)
                {
                    while (zero % mod < (place = findCell(number)) % mod)
                    {
                        right();
                    }
                    down();
                }
                while (zero % mod < place % mod)
                {
                    right();
                }
                while (zero % mod > place % mod)
                {
                    left();
                }
                while (zero / mod > 1)
                {
                    up();
                }
            }
            if (zero % mod == (place = findCell(number)) % mod)
            {
                if (zero == 5)
                {
                    if (place == 9)
                    {
                        right();
                        down();
                        down();
                        left();
                    }
                    else
                    {
                        down();
                    }
                }
                left();
            }
            if (zero % mod < place % mod)
            {
                while (zero / mod < place / mod)
                {
                    down();
                }
                while (zero / mod > place / mod)
                {
                    up();
                }
                while (zero % mod < (place = findCell(number)) % mod)
                {
                    right();
                }
                continue;
            }
            if (zero / mod == place / mod)
            {
                (zero / mod == 3) ? up() : down();
            }
            while (zero % mod > place % mod)
            {
                left();
            }
        }
        place = findCell(number);
        if ((zero == 8) && (place == 12))
        {
            down();
            return;
        }
        if (doska[8] == 9)
        {
            return;
        }
        if (zero / mod < 2)
        {
            down();
        }
        if (zero / mod > 2)
        {
            up();
        }
        while (zero % mod > 0)
        {
            left();
        }
        down();
    }

    void thirteenGoesToThePlace()
    {
        zero = findCell(0);
        short number = 13;
        short place;
        if (zero == 12)
        {
            right();
            if (doska[12] == 13)
            {
                return;
            }
        }
        while ((place = findCell(number)) % mod != 1)
        {
            if (zero % mod == place % mod)
            {
                left();
            }
            if (zero % mod < place % mod)
            {
                while (zero / mod < place / mod)
                {
                    down();
                }
                while (zero / mod > place / mod)
                {
                    up();
                }
                while (zero % mod < (place = findCell(number)) % mod)
                {
                    right();
                }
                continue;
            }
            if (zero / mod == place / mod)
            {
                (zero / mod == 3) ? up() : down();
            }
            while (zero % mod >= place % mod)
            {
                left();
            }
        }
        if (place / mod != 3)
        {
            if (place / mod == 1)
            {
                if (zero / mod != 2)
                {
                    (zero / mod < 2) ? down() : up();
                }
                while (zero % mod > 1)
                {
                    left();
                }
                up();
            }
            if (zero == 5)
            {
                right();
            }
            while (zero / mod != 3)
            {
                down();
            }
            while (zero % mod > 1)
            {
                left();
            }
            up();
        }
        while (zero / mod > 1)
        {
            up();
        }
        while (zero % mod > 0)
        {
            left();
        }
        while (zero / mod < 3)
        {
            down();
        }
        right();
        up();
        left();
        up();
        right();
    }
};

int main()
{
    Pyatn doska;
    doska.findSolve();
    return 0;
}
