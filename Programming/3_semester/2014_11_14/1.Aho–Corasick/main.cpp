#include <iostream>
#include <fstream>
#include <map>
#include <vector>

class Aho
{
public:

    Aho()
    {
        nodes.resize(1);
        nodes[0] = Node();
        nodes[0].link = 0;
    }

    void add_string(const std::string& str)
    {
        patterns.push_back(str);
        int current = 0;
        for (unsigned int i = 0; i < str.length(); ++i)
        {
            char c = str[i];
            if (!nodes[current].children[c])
            {
                nodes.push_back(Node(current, c));
                nodes[current].children[c] = nodes.size() - 1;
            }
            current = nodes[current].children[c];
        }
        nodes[current].is_terminal = true;
        nodes[current].pattern = patterns.size()-1;
    }

    std::map < std::string, std::vector < int > > findAllPatterns(const std::string& haystack)
    {
        std::map < std::string, std::vector < int > > answers;
        int current = 0;
        int hlen = haystack.length();
        for (unsigned int i = 0; i < hlen; ++i)
        {
            current = go(current, haystack[i]);
            int temp = current;
            while (temp != 0)
            {
                if (nodes[temp].is_terminal)
                {
                    answers[patterns[nodes[temp].pattern]].push_back(i-patterns[nodes[temp].pattern].length());
                }
                temp = build_terminal_link(temp);
            }
        }
        return answers;
    }

    class Node
    {
    public:

        std::map < char, int > children;
        std::map < char, int > moves;
        int parent;
        char parent_char;
        int link;
        int terminal_link;
        bool is_terminal;
        int pattern;

        Node(int p = 0, char pc = (char)0, bool it = 0, int pat = -1)
        {
            parent = p;
            parent_char = pc;
            link = -1;
            terminal_link = -1;
            is_terminal = it;
            pattern = pat;
        }
    };

    std::vector < std::string > patterns;
    std::vector<Node> nodes;

    int go(int current, char c)
    {
        if (!nodes[current].moves[c])
        {
            if (nodes[current].children.find(c) != nodes[current].children.end())
            {
                nodes[current].moves[c] = nodes[current].children[c];
            }
            else
            {
                if (current == 0)
                {
                    nodes[current].moves[c] = 0;
                }
                else
                {
                    nodes[current].moves[c] = go(build_link(current), c);
                }
            }
        }
        return nodes[current].moves[c];
    }

    int build_link(int current)
    {
        if (nodes[current].link == -1)
        {
            if ((current == 0) || (nodes[current].parent == 0))
            {
                nodes[current].link = 0;
            }
            else
            {
                nodes[current].link = go(build_link(nodes[current].parent), nodes[current].parent_char);
            }
        }
        return nodes[current].link;
    }

    int build_terminal_link(int current)
    {
        if (nodes[current].terminal_link == -1)
        {
            int link = build_link(current);
            if (link == 0)
            {
                nodes[current].terminal_link = 0;
            }
            else
            {
                if (nodes[link].is_terminal)
                {
                    nodes[current].terminal_link = link;
                }
                else
                {
                    nodes[current].terminal_link = build_terminal_link(link);
                }
            }

        }
        return nodes[current].terminal_link;
    }
};

int main()
{
    std::string str;
    std::ifstream in("input.txt");
    while(!in.eof())
    {
        std::string buf;
        getline(in, buf);
        str += buf;
    };
    in.close();

    Aho a;
    a.add_string("aa");
    a.add_string("abb");
    a.add_string("abc");
    a.add_string("ab");
    std::map<std::string, std::vector < int > > answer = a.findAllPatterns(str);
    for (std::map<std::string, std::vector < int > >::iterator it = answer.begin(); it != answer.end(); it++)
    {
        std::cout << it->first << " " << it->second.size() << '\n';
    }
    return 0;
}
