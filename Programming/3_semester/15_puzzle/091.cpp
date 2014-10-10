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
	int plink;
	short matr[17];
	char direction;

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
		for (short i = 0; i < 17; ++i)
		{
			matr[i] = other.matr[i];
		}
		ST = other.ST;
		link = other.link;
		plink = other.plink;
		direction = other.direction;
	}

	~matrix()
	{
	}

	void shift(const short i, short n)
	{
		switch (n)
		{
		case 0: direction = 'r'; break;
		case 1: direction = 'd'; break;
		case 2: direction = 'l'; break;
		case 3: direction = 'u'; break;
		}
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

	int getPLink() const
	{
		return plink;
	}

	void setPLink(const int pl)
	{
		plink = pl;
	}

	int getLink() const
	{
		return link;
	}

	void setLink(const int l)
	{
		link = l;
	}

	char getDirection() const
	{
		return direction;
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
		m.link = 0;
		m.plink = 0;
		m.ST = 0;
		m.direction = 's';
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
	std::multimap < int, matrix* > table; // h(x) + steps; matrix
	std::vector < matrix > vertex;
	std::stack < char > path;

public:

	Vosm()
	{
		vertex.resize(0);
		vertex.reserve(128);
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
		vertex.push_back(start);
		table.insert(std::make_pair(0, &(vertex[0])));
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
		if (temp != vertex[M->getPLink()])
		{
//            std::cout << temp << "H Q\n" << temp.h() << " " << temp.steps() << "\n";
			temp.setLink(vertex.size());
			temp.setPLink(M->getLink());
			if (vertex.capacity() == vertex.size())
            {
                vertex.reserve(vertex.capacity() * 2);
            }
			vertex.push_back(temp);
			table.insert(std::make_pair(temp.h() + temp.steps(), &(vertex[vertex.size() - 1])));
		}
		return true;
	}

	void AStar()
	{
		while (true)
		{
			matrix* M = table.begin()->second;
			table.erase(table.begin());

			short Z = M->find_zero();
			if (Z % 4 < 3) //right
			{
				if (addV(M, Z, 0) == false)
				{
					std::cout << "No\n";
					return;
				}
			}
			if (Z % 4 > 0) //left
			{
				if (addV(M, Z - 1, 2/*0*/) == false)
				{
					std::cout << "No\n";
					return;
				}
			}
			if (Z / 4 < 3) //down
			{
				if (addV(M, Z, 1) == false)
				{
					std::cout << "No\n";
					return;
				}
			}
			if (Z / 4 > 0) //up
			{
				if (addV(M, Z - 4, 3/*1*/) == false)
				{
					std::cout << "No\n";
					return;
				}
			}
			//            std::cout << "-----------\n";
			int q = table.begin()->second->h();
			//            std::cout << table.begin()->second << table.begin()->second.h();

			if (q == 0)
			{
				std::cout << "YES\n";
				path.push(table.begin()->second->getDirection());
				while (*M != start)
				{
					path.push(M->getDirection());
					M = &(vertex[M->getPLink()]);
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
