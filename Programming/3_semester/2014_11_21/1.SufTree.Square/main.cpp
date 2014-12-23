#include <iostream>
#include <map>

//This code was written in the classroom.

struct Edge;

struct Vertex
{
	std::map < char, Edge > edge;
	Vertex *link;
	int depth;
	Vertex()
	{
	    link = 0;
	};
};

struct Edge
{
	char* pBeg;
	char* pEnd;
	Vertex* v;
	Edge()
	{
		pBeg = 0;
		pEnd = 0;
		v = 0;
	}
};

void print(int skip, Vertex* v)
{
	for (std::map < char, Edge>::iterator it = v->edge.begin(); it != v->edge.end(); ++it)
    {
		for (int j = 0; j < skip; ++j)
        {
            std::cout << " ";
		}
		int count = 0;
		char* temp = it->second.pBeg;
		while ((*temp != 0) && (temp != it->second.pEnd))
        {
			std::cout << temp[0];
			++count;
			++temp;
		}
		if (it->second.pEnd)
		{
		    std::cout << "(" << it->second.v->depth << ")";
		}
		std::cout << '\n';

		if (it->second.pEnd)
        {
            print(skip + count, it->second.v);
        }
	}
}

int main()
{
	Edge* temp = new Edge;
	Vertex root;
	root.depth = 0;
	temp->v = &root;
	char* beg = "aaaaaabab ";
	char* end;
	char* start = beg;
	char* suf;
	Edge* e = temp;
	char* ep = 0;
	suf = start;
	Vertex* parentVertex = 0;
	Vertex* lastCreatedVertex = 0;
	for (end = beg; end[0] != 0; ++end)
    {
		while (suf < end)
		{
			if (ep == e->pEnd)
			{
				if ((lastCreatedVertex) && (lastCreatedVertex->depth == suf - start + 1))
				{
					lastCreatedVertex->link = e->v;
					lastCreatedVertex = NULL;
				}
				Edge* save = e;
				e = &(e->v->edge[*suf]);
				if (!e->pBeg)
				{
					e->pBeg = suf;
					++start;
					if (parentVertex && (parentVertex->link))
					{
						suf -= (ep - save->pBeg);
						parentVertex = parentVertex->link;
						e = &(parentVertex->edge[suf[0]]);
						ep = e->pBeg;
						parentVertex = save->v;
					}
					else {
						e = temp;
						ep = NULL;
						suf = start;
						parentVertex = 0;
					}
					continue;
				}
				parentVertex = save->v;
				ep = e->pBeg;
				continue;
			}
			if (*suf == *ep)
			{
				++suf;
				++ep;
				continue;
			}
			Vertex* nv;
			Edge* ne;
			nv = new Vertex;
			ne = &(nv->edge[*ep]);
			ne->pBeg = ep;
			ne->pEnd = e->pEnd;
			ne->v = e->v;
			e->pEnd = ep;
			e->v = nv;
			if (lastCreatedVertex && (lastCreatedVertex->depth == suf - start + 1))
			{
				lastCreatedVertex->link = nv;
				lastCreatedVertex = 0;
			}
			lastCreatedVertex = nv;
			lastCreatedVertex->depth = suf - start;
			continue;
		}
	}
	print(0, &root);
	return 0;
}
