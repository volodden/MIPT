#define _CRT_SECURE_NO_WARNINGS

// It doesn't work in Code::Blocks and Qt (mingw), but work in Visual Studio (and gcc).

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdio>

struct SuffixTree
{
	const static int alphabetSize = 53;
	const static char terminationSymbol = '$';

	static int toCode(char symbol)
	{
		if ((symbol >= 'a') && (symbol <= 'z'))
		{
			return symbol - 'a';
		}
		if ((symbol >= 'A') && (symbol <= 'Z'))
		{
			return alphabetSize / 2 + symbol - 'A';
		}
		if (symbol == terminationSymbol)
		{
			return alphabetSize - 1;
		}
	}

	struct Node;
	struct Edge;

	struct InlineNode
	{
		InlineNode(int _parent = 0)
		{
			parent = _parent;
			length = 0;
			next.resize(alphabetSize);
			for (unsigned int i = 0; i < next.size(); ++i)
			{
				next[i] = -1;
			}
			start.resize(SuffixTree::alphabetSize);
			end.resize(SuffixTree::alphabetSize);
		}

		std::vector < int > next, start, end;
		int parent, length;

		void setForSymbol(char symbol, int newNext, int newStart, int newEnd)
		{
			int code = SuffixTree::toCode(symbol);
			next[code] = newNext;
			start[code] = newStart;
			end[code] = newEnd;
		}

		int lengthForSymbol(int code)
		{
			return end[code] - start[code];
		}
	};

	std::string s;
	std::vector < int > links;
	std::vector < InlineNode > tree;

	void addNode(int _parent)
	{
		tree.push_back(InlineNode(_parent));
		links.push_back(-1);
	}

	void addLeaf(int node, int symbol, int start) {
		addNode(node);
		tree[node].setForSymbol(symbol, tree.size() - 1, start, s.length());
		tree.back().length = s.length() - start - 1 + tree[node].length;
	}

	void next(int& node, int& length, int& code, int start, int end)
	{
		length = end - start - tree[node].length;
		while ((tree[node].next[code] != -1) && (length >= tree[node].lengthForSymbol(code)))
		{
			int newLength = tree[node].lengthForSymbol(code);
			node = tree[node].next[code];
			length -= newLength;
			code = SuffixTree::toCode(s[tree[node].length + start]);
		}
	}

	bool trySymbol(int node, int length, int start, int code)
	{
		if (!length)
		{
			return (tree[node].next[code] != -1);
		}
		return (toCode(s[tree[node].start[start] + length]) == code);
	}

	int split(int node, int length, int code)
	{
		if (!length)
		{
			return node;
		}
		if (length == tree[node].lengthForSymbol(code))
		{
			return tree[node].next[code];
		}
		addNode(node);
		char symbol = s[tree[node].start[code] + length];
		tree.back().setForSymbol(symbol, tree[node].next[code], tree[node].start[code] + length, tree[node].end[code]);
		tree[node].end[code] = tree[node].start[code] + length;
		tree[node].next[code] = tree.size() - 1;
		tree[tree.back().next[toCode(symbol)]].parent = tree.size() - 1;
		tree.back().length = tree[node].length + 1;
		return tree.size() - 1;
	}

	SuffixTree(std::string text)
	{
		s = text + SuffixTree::terminationSymbol;
		int start = 0;
		int end = 0;
		tree.push_back(InlineNode());
		links.push_back(0);
		int node = 0;
		int length = 0;
		int startSymbol = 0;
		int alone = -1;
		while ((unsigned int)std::max(start, end) < s.length())
		{
			int code = SuffixTree::toCode(s[end]);
			while (start <= end && !trySymbol(node, length, startSymbol, code))
			{
				int mid = split(node, length, startSymbol);
				if (alone != -1)
				{
					links[alone] = mid;
					alone = -1;
				}
				if (links[mid] == -1)
				{
					alone = mid;
				}
				addLeaf(mid, code, end);
				++start;
				node = links[node];
				startSymbol = toCode(s[start + tree[node].length]);
				if (start <= end)
				{
					next(node, length, startSymbol, start, end);
				}
			}
			if (alone > -1)
			{
				links[alone] = node;
				alone = -1;
			}
			++end;
			if (start != end)
			{
				next(node, length, startSymbol, start, end);
			}
		}
	}

	Node getRoot() const
	{
		return Node(const_cast<SuffixTree&>(*this), 0);
	}

	int getLength() const
	{
		return s.length();
	}

	struct Node
	{
		SuffixTree &suffixTree;
		int node;

		Node(SuffixTree &_suffixTree, int _node)
			: suffixTree(_suffixTree), node(_node)
		{
		}

		std::vector < Edge > getOutgoingEdges()
		{
			std::vector<Edge> listEdges;
			for (int i = 0; i < SuffixTree::alphabetSize; ++i)
			{
				if (suffixTree.tree[node].next[i] != -1)
				{
					listEdges.push_back(Edge(suffixTree, node, i));
				}
			}
			return listEdges;
		}

		Edge getBySymbol(char symbol)
		{
			return Edge(suffixTree, node, toCode(symbol));
		}

		bool hasEdge(char symbol)
		{
			return (suffixTree.tree[node].next[SuffixTree::toCode(symbol)] != -1);
		}

		Node& operator= (const Node & other)
		{
			this->suffixTree = other.suffixTree;
			this->node = other.node;
			return *this;
		}
	};

	struct Edge
	{
		SuffixTree &suffixTree;
		int node, symbol;

		Edge(SuffixTree &_suffixTree, int _node, int _symbol)
			: suffixTree(_suffixTree), node(_node), symbol(_symbol)
		{
		}

		char getCharAt(int index)
		{
			return suffixTree.s[suffixTree.tree[node].start[symbol] + index];
		}

		Node getNode()
		{
			return Node(suffixTree, suffixTree.tree[node].next[symbol]);
		}

		int getLen()
		{
			return suffixTree.tree[node].lengthForSymbol(symbol);
		}
	};
};

std::vector < std::pair < int, int > > findAllOccurences(const SuffixTree& suffixTree, std::string pattern)
{
	std::vector< std::pair<int, int> > occurences(pattern.length());
	bool flag = false;
	for (unsigned int st = 0; st < pattern.length(); ++st)
	{
		SuffixTree::Node currentNode = suffixTree.getRoot();
		int currentLength = 0;
		int startPosition = 0;
		while ((unsigned int)currentLength < pattern.size() - st)
		{
			if (!currentNode.hasEdge(pattern[currentLength + st]))
			{
				flag = true;
				break;
			}
			SuffixTree::Edge currentEdge = currentNode.getBySymbol(pattern[currentLength + st]);
			startPosition = currentEdge.suffixTree.tree[currentEdge.node].start[SuffixTree::toCode(currentEdge.getCharAt(0))] - currentLength;
			int curLen = currentLength;
			for (int i = 0; i < std::min(currentEdge.getLen(), (int)(pattern.length() - curLen - st)); ++i)
			{
				if (currentEdge.getCharAt(i) == pattern[currentLength + st])
				{
					++currentLength;
				}
				else
				{
					flag = true;
					break;
				}
			}
			if (flag)
			{
				break;
			}
			currentNode = currentEdge.getNode();
		}
		occurences[st].first = startPosition;
		occurences[st].second = currentLength;
	}
	return occurences;
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	std::string s, t;
	std::cin >> s >> t;
	std::vector< std::pair<int, int> > ans = findAllOccurences(SuffixTree(s), t);
	for (unsigned int i = 0; i < ans.size(); ++i)
		std::cout << ans[i].first << ' ' << ans[i].second << '\n';
}
