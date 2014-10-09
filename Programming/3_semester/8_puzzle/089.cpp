#include <iostream>
#include <map>

short abs(short A)
{
    return A > 0 ? A : -A;
}

class matrix
{
private:

    int ST;
    short matr[12];

public:

    matrix()
    {
    }

    matrix(short temp[9])
    {
        for (short i = 0; i < 9; ++i)
        {
            matr[i] = temp[i];
        }
    }

    matrix(const matrix& other)
    {
        for (short i = 0; i < 12; ++i)
        {
            matr[i] = other.matr[i];
        }
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
        ST += 1;
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

    short h()
    {
        return matr[9];
    }

    int steps()
    {
        return ST;
    }

    short find_zero()
    {
        for (short i = 0; i < 9; ++i)
        {
            if (matr[i] == 0)
            {
                return i;
            }
        }
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
    matrix finish;
    std::multimap < int, matrix > table; // h(x) + steps; matrix

public:

    Vosm()
    {
        std::cin >> start;
    }

    void findSolve()
    {
        short temp[9] = {1, 2, 3, 4, 5, 6, 8, 7, 0};
        finish = make_matrix(temp);
        short q = start.h();
        if (q == 0)
        {
            std::cout << "Yes\n0\n";
            return;
        }
        table.insert(std::make_pair(0, start));
        AStar();
    }

private:

    /**
    *   0 - right, 1 - down
    */

    bool addV(matrix M, short i, short n)
    {
        matrix temp(M);
        temp.shift(i, n);

        if (temp.h() == 2)
        {
            if (temp == finish)
            {
                return false;
            }
        }
        if (temp != M.getParent())
        {
            table.insert(std::make_pair(temp.h() + temp.steps(), temp));
        }
        return true;
    }

    void AStar()
    {
        while(true)
        {
            matrix M = table.begin()->second;
            table.erase(table.begin());

            short Z = M.find_zero();
            if (Z % 3 < 2) //right
            {
                if (addV(M, Z, 0) == false)
                {
                    std::cout << "No\n";
                    return;
                }
            }
            if (Z % 3 > 0) //left
            {
                if (addV(M, Z - 1, 0) == false)
                {
                    std::cout << "No\n";
                    return;
                }
            }
            if (Z / 3 < 2) //down
            {
                if (addV(M, Z, 1) == false)
                {
                    std::cout << "No\n";
                    return;
                }
            }
            if (Z / 3 > 0) //up
            {
                if (addV(M, Z - 3, 1) == false)
                {
                    std::cout << "No\n";
                    return;
                }
            }
            int q = table.begin()->second.h();

            if (q == 0)
            {
                std::cout << "Yes\n" << M.steps() + 1 << "\n";
                return;
            }
        }
    }
};

int main()
{
    Vosm doska;

    doska.findSolve();

    return 0;
}
