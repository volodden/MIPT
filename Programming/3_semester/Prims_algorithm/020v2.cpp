#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <set>
#include <map>
#include <stdlib.h>

class Dot
{
public:

    int x, y;

    Dot()
    {
    }

    Dot(const int _x, const int _y)
    {
        x = _x;
        y = _y;
    }

    friend std::istream& operator >> (std::istream& in, Dot& A)
    {
        in >> A.x >> A.y;
        return in;
    }
};

class Seg
{
public:

    Dot A, B;

    Seg()
    {
    }

    Seg(const Dot& _A, const Dot& _B) : A(_A), B(_B)
    {
    }

    Seg(const Seg& other) : A(other.A), B(other.B)
    {
    }

    friend std::istream& operator >> (std::istream& in, Seg& AB)
    {
        in >> AB.A >> AB.B;
        return in;
    }

    int multy(const Dot& C) const
    {
        int S = (B.x - A.x)*(C.y - A.y) - (B.y - A.y)*(C.x - A.x);
        return (S < 0 ? -1 : (S > 0 ? 1 : 0));
    }

    bool intersection(const Seg& other) const
    {
        return ((multy(other.A) * multy(other.B) < 0) && (other.multy(A) * other.multy(B) < 0));
    }

    int lengthSquare() const
    {
        return (A.x - B.x)*(A.x - B.x) + (A.y - B.y)*(A.y - B.y);
    }
};

int N, M;
std::vector < std::pair < std::string, Dot > > citys;
std::vector < Seg > moats;
std::set < int > islands;
std::set < int > country;
std::vector < std::pair < int, int > > roads;
std::vector < std::map < int, int > > distance;

void add_new_roads(const int s)
{

}

void solve()
{
    std::cin >> N >> M;
    citys.reserve(N);
    distance.resize(N);
    for (int i = 0; i < N; ++i)
    {
        std::string City;
        Dot K;
        std::cin >> City >> K;
        citys.push_back(std::make_pair(City, K));
        islands.insert(i);
    }
    moats.reserve(M);
    for (int i = 0; i < M; ++i)
    {
        Seg moat;
        std::cin >> moat;
        moats.push_back(moat);
    }
    int s = *islands.begin();
    country.insert(s);
    islands.erase(islands.begin());

    for (int q = 1; q < N; ++q)
    {
        for (std::set < int >::iterator it = islands.begin(); it != islands.end(); ++it)
        {
            Seg road(citys[s].second, citys[*it].second);
            bool flag = true;
            for (int j = 0; j < M; ++j)
            {
                if (road.intersection(moats[j]))
                {
                    flag = false;
                    break;
                }
            }
            if (flag)
            {
                distance[s].insert(std::make_pair(*it, road.lengthSquare()));
            }
        }

        int k = -1;
        std::pair < int, int > min_road = std::make_pair(-1, -1);
        for (std::set < int >::iterator it = country.begin(); it != country.end(); ++it)
        {
            for (std::map < int, int >::iterator it2 = distance[*it].begin(); it2 != distance[*it].end(); ++it2)
            {
                if (min_road.first == -1)
                {
                    min_road = std::make_pair(it2->first, it2->second);
                    k = *it;
                    continue;
                }
                if (min_road.second > it2->second)
                {
                    k = *it;
                    min_road = std::make_pair(it2->first, it2->second);
                }
            }
        }
        if (min_road.first == -1)
        {
            std::cout << "NO";
            exit(0);
        }
        for (std::set < int >::iterator it = country.begin(); it != country.end(); ++it)
        {
            distance[*it].erase(min_road.first);
        }
        islands.erase(min_road.first);
        country.insert(min_road.first);
        roads.push_back(std::make_pair(k, min_road.first));

        s = min_road.first;;
    }

    std::cout << "YES\n" << roads.size() << "\n";
    for (int i = 0; i < roads.size(); ++i)
    {
        std::cout << citys[roads[i].first].first << " " << citys[roads[i].second].first << "\n";
    }
}

int main()
{
    solve();

    return 0;
}
