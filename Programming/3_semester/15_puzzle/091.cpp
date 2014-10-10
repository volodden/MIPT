#include <iostream>
#include <map>
#include <vector>
#include <stack>

short abs(short A)
{
	return A > 0 ? A : -A;
}

class matrix
{
private:

	int ST;
	int link;
	short matr[19];

public:

	matrix()
	{
	}

	matrix(short temp[16])
	{
		for (short i = 0; i < 16; ++i)
		{
			matr[i] = temp[i];
		}
	}

	matrix(const matrix& other)
	{
		for (short i = 0; i < 19; ++i)
		{
			matr[i] = other.matr[i];
		}
		ST = other.ST;
		link = other.link;
	}

	~matrix()
	{
	}

	void shift(const short i, short n)
	{
	    matr[17] = i;
	    matr[18] = n;
		n %= 2;
		n *= 3;
		++n;
		matr[16] -= abs(i / 4 - ((matr[i] + 15) % 16) / 4)
                  + abs(i % 4 - ((matr[i] + 15) % 16) % 4)
                  + abs((i + n) / 4 - ((matr[i + n] + 15) % 16) / 4)
                  + abs((i + n) % 4 - ((matr[i + n] + 15) % 16) % 4);

		short k = matr[i];
		matr[i] = matr[i + n];
		matr[i + n] = k;

		matr[16] += abs(i / 4 - ((matr[i] + 15) % 16) / 4)
                  + abs(i % 4 - ((matr[i] + 15) % 16) % 4)
                  + abs((i + n) / 4 - ((matr[i + n] + 15) % 16) / 4)
                  + abs((i + n) % 4 - ((matr[i + n] + 15) % 16) % 4);
		++ST;
	}

    matrix getParent() const
    {
        if ((this->matr[17] == -1) || (this->matr[18] == -1))
        {
            return *this;
        }
        matrix temp(*this);
        temp.shift(this->matr[17], this->matr[18]);
        return temp;
    }

	friend std::istream& operator >> (std::istream& in, matrix& m)
	{
		m.matr[16] = 0;
		for (short i = 0; i < 16; ++i)
		{

			in >> m.matr[i];
			m.matr[16] += abs(i / 4 - ((m.matr[i] + 15) % 16) / 4);
			m.matr[16] += abs(i % 4 - ((m.matr[i] + 15) % 16) % 4);
		}
		m.matr[17] = -1;
		m.matr[18] = -1;
		m.ST = 0;
		m.link = 0;
		return in;
	}

	friend std::ostream& operator << (std::ostream& out, const matrix& m)
	{
		for (short i = 0; i < 16; ++i)
		{
			out << (m.matr[i] < 10 ? " " : "") << m.matr[i] << (i % 4 == 3 ? "\n" : " ");
		}
		out << "\n";
		return out;
	}

	friend bool operator== (const matrix& left, const matrix& right)
	{
		for (short i = 0; i < 16; ++i)
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
		return matr[16];
	}

	int steps() const
	{
		return ST;
	}

	int getLink() const
	{
	    return link;
	}

	void setLink(const int l)
	{
	    link = l;
	}

	short find_zero() const
	{
		for (short i = 0; i < 16; ++i)
		{
			if (matr[i] == 0)
			{
				return i;
			}
		}
	}
};

matrix make_matrix(short temp[16])
{
	return matrix(temp);
}

class Vosm
{
private:

	matrix start;
	matrix finish;
	std::multimap < int, matrix > table; // h(x) + steps; matrix
	std::vector < std::pair < int, char > > vertex;
	std::stack < char > path;

public:

	Vosm()
	{
		vertex.resize(0);
//		vertex.reserve(128);
		std::cin >> start;
	}

	void findSolve()
	{
		short temp[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 15, 14, 0 };
		finish = make_matrix(temp);
		short q = start.h();
		if (q == 0)
		{
			std::cout << "YES\n";
			return;
		}
		vertex.push_back(std::make_pair(0, 's'));
		table.insert(std::make_pair(0, start));
		AStar();
	}

private:

	/**
	*   0 - right, 1 - down
	*/

	bool addV(const matrix* M, const short i, const short n)
	{
		matrix temp(*M);
		temp.shift(i, n);

		if (temp.h() == 2)
		{
			if (temp == finish)
			{
				return false;
			}
		}
		if (temp != M->getParent())
		{
            temp.setLink(vertex.size());
//			if (vertex.capacity() == vertex.size())
//            {
//                vertex.reserve(vertex.capacity() * 2);
//            }
            switch (n)
            {
            case 0: vertex.push_back(std::make_pair(M->getLink(), 'r')); break;
            case 1: vertex.push_back(std::make_pair(M->getLink(), 'd')); break;
            case 2: vertex.push_back(std::make_pair(M->getLink(), 'l')); break;
            case 3: vertex.push_back(std::make_pair(M->getLink(), 'u')); break;
            }
			table.insert(std::make_pair(temp.h() + temp.steps(), temp));
		}
		return true;
	}

	void AStar()
	{
		while (true)
		{
			matrix M = table.begin()->second;
			table.erase(table.begin());

			short Z = M.find_zero();
			if (Z % 4 < 3) //right
			{
				if (addV(&M, Z, 0) == false)
				{
					std::cout << "No\n";
					return;
				}
			}
			if (Z % 4 > 0) //left
			{
				if (addV(&M, Z - 1, 2/*0*/) == false)
				{
					std::cout << "No\n";
					return;
				}
			}
			if (Z / 4 < 3) //down
			{
				if (addV(&M, Z, 1) == false)
				{
					std::cout << "No\n";
					return;
				}
			}
			if (Z / 4 > 0) //up
			{
				if (addV(&M, Z - 4, 3/*1*/) == false)
				{
					std::cout << "No\n";
					return;
				}
			}
			//            std::cout << "-----------\n";
			int q = table.begin()->second.h();
			//            std::cout << table.begin()->second << table.begin()->second.h();

			if (q == 0)
			{
				std::cout << "YES\n";
				int k = table.begin()->second.getLink();
				while (k != 0)
				{
					path.push(vertex[k].second);
					k = vertex[k].first;
				}
				while (path.empty() == false)
				{
					std::cout << path.top();
					path.pop();
				}
				std::cout << "\n";
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
