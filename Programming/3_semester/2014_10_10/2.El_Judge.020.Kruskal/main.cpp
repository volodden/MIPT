#include <iostream>
#include <vector>
#include <map>
#include <set>

class Dot
{
private:

    int x, y;

public:

    Dot()
    {
    }

    Dot(const int _x, const int _y)
    {
        x = _x;
        y = _y;
    }

    Dot(const Dot& other)
    {
        x = other.x;
        y = other.y;
    }

    int getX() const
    {
        return x;
    }

    int getY() const
    {
        return y;
    }

    Dot& operator= (const Dot& other)
    {
        x = other.x;
        y = other.y;
        return *this;
    }

    friend std::istream& operator >> (std::istream& in, Dot& A)
    {
        in >> A.x >> A.y;
        return in;
    }
};

class Seg
{
private:

    Dot A, B;

public:

    Seg()
    {
    }

    Seg(const Dot& _A, const Dot& _B) : A(_A), B(_B)
    {
    }

    Seg(const Seg& other) : A(other.A), B(other.B)
    {
    }

    Dot getA() const
    {
        return A;
    }

    Dot getB() const
    {
        return B;
    }

    friend std::istream& operator >> (std::istream& in, Seg& AB)
    {
        in >> AB.A >> AB.B;
        return in;
    }

    int multy(const Dot& C) const
    {
        int S = (B.getX() - A.getX())*(C.getY() - A.getY())
              - (B.getY() - A.getY())*(C.getX() - A.getX());
        return (S < 0 ? -1 : (S > 0 ? 1 : 0));
    }

    bool intersection(const Seg& other) const
    {
        if ((multy(other.getA()) * multy(other.getB()) < 0)
         && (other.multy(A) * other.multy(B) < 0))
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    int lengthSquare() const
    {
        return (A.getX() - B.getX())*(A.getX() - B.getX()) + (A.getY() - B.getY())*(A.getY() - B.getY());
    }
};

class Solution
{
private:

    int N, M;
    std::vector < std::pair < std::string, Dot > > cities;
    std::vector < Seg > moats;
    std::multimap < int, std::pair < int, int > > allRoads;
    std::vector < std::set < int > > countries;
    std::vector < std::pair < int, int > > country;
    std::set < int > existingCountry;

public:

    Solution()
    {
        std::cin >> N >> M;
        cities.reserve(N);
        for (int i = 0; i < N; ++i)
        {
            std::string city;
            Dot K;
            std::cin >> city >> K;
            cities.push_back(std::make_pair(city, K));
        }
        moats.reserve(M);
        for (int i = 0; i < M; ++i)
        {
            Seg moat;
            std::cin >> moat;
            moats.push_back(moat);
        }
        buildAllRoads();
    }

    void solve()
    {
        if ((cities.size() < 2) || (allRoads.empty()))
        {
            std::cout << "NO\n";
            return;
        }
        for (std::map < int, std::pair < int, int > >::iterator it = allRoads.begin(); it != allRoads.end(); ++it)
        {
            if (existingCountry.empty())
            {
                countries.resize(1);
                countries[0].insert(it->second.first);
                countries[0].insert(it->second.second);
                existingCountry.insert(0);
                country.push_back(std::make_pair(it->second.first, it->second.second));
                continue;
            }
            std::set < int >::iterator first = existingCountry.end();
            std::set < int >::iterator second = existingCountry.end();
            for (std::set < int >::iterator it2 = existingCountry.begin(); it2 != existingCountry.end(); ++it2)
            {
                if (countries[*it2].find(it->second.first) != countries[*it2].end())
                {
                    first = it2;
                    break;
                }
            }
            for (std::set < int >::iterator it2 = existingCountry.begin(); it2 != existingCountry.end(); ++it2)
            {
                if (countries[*it2].find(it->second.second) != countries[*it2].end())
                {
                    second = it2;
                    break;
                }
            }
            if (first == existingCountry.end())
            {
                if (second == existingCountry.end())
                {
                    int t = 0;
                    for (std::set < int >::iterator it2 = existingCountry.begin(); it2 != existingCountry.end(); ++it2)
                    {
                        if (t == *it2)
                        {
                            ++t;
                            continue;
                        }
                        if (t < *it2)
                        {
                            break;
                        }
                    }
                    if (t >= countries.size())
                    {
                        countries.resize(2 * countries.size());
                    }
                    countries[t].insert(it->second.first);
                    countries[t].insert(it->second.second);
                    existingCountry.insert(t);
                }
                else
                {
                    countries[*second].insert(it->second.first);
                }
            }
            else
            {
                if (second == existingCountry.end())
                {
                    countries[*first].insert(it->second.second);
                }
                else
                {
                    if (first == second)
                    {
                        continue;
                    }
                    if (countries[*first].size() > countries[*second].size())
                    {
                        std::set < int >::iterator temp = first;
                        first = second;
                        second = temp;
                    }
                    for (std::set < int >::iterator it2 = countries[*first].begin(); it2 != countries[*first].end(); ++it2)
                    {
                        countries[*second].insert(*it2);
                    }
                    countries[*first].clear();
                    existingCountry.erase(first);
                }
            }
            country.push_back(std::make_pair(it->second.first, it->second.second));
        }
        if (existingCountry.size() != 1)
        {
            std::cout << "NO\n";
            return;
        }
        if (country.size() + 1 != cities.size())
        {
            std::cout << "NO\n";
            return;
        }
        std::cout << "YES\n" << cities.size() - 1 << "\n";
        for (unsigned int i = 0; i < country.size(); ++i)
        {
            std::cout << cities[country[i].first].first << " " << cities[country[i].second].first << "\n";
        }
    }

private:

    void buildAllRoads()
    {
        for (unsigned int i = 0; i + 1 < cities.size(); ++i)
        {
            for (unsigned int j = i + 1; j < cities.size(); ++j)
            {
                Seg road(cities[i].second, cities[j].second);
                bool flag = true;
                for (int k = 0; k < M; ++k)
                {
                    if (road.intersection(moats[k]))
                    {
                        flag = false;
                        break;
                    }
                }
                if (flag)
                {
                    allRoads.insert(std::make_pair(road.lengthSquare(), std::make_pair(i, j)));
                }
            }
        }
    }
};

int main()
{
    Solution my_new_solution;
    my_new_solution.solve();
    return 0;
}
