#include <map>

struct Vertex
{
    char symbol;
    std::map<char, struct Vertex*> next;
};


class trie
{
private:
    struct Vertex* root;
    
    struct Vertex* initVertex();
    struct Vertex* initVertex(char c);

public:
    trie();
    ~trie();
};

Vertex *trie::initVertex()
{
    struct Vertex* result = new Vertex();
    result->symbol = 0;
    result->next = std::map<char, struct Vertex*>();

    return result;
}

Vertex *trie::initVertex(char c)
{
    struct Vertex* result = initVertex();
    result->symbol = c;

    return result;
}

trie::trie()
{
    
}

trie::~trie()
{

}
