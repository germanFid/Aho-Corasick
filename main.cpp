#include <map>

struct Vertex
{
    std::map<char, struct Vertex*> next;
    bool is_terminal;
    struct Vertex* parent;

    // for auto
    // struct Vertex* sufflink;
    // struct Vertex** go;

};


class Trie
{
private:
    struct Vertex* root;
    
    struct Vertex* initVertex(struct Vertex* parent);

public:
    Trie();
    ~Trie();

    void insert(char* cstr);
    void find();
};

//
// Check https://www.cs.usfca.edu/~galles/visualization/Trie.html
//
Vertex *Trie::initVertex(struct Vertex* parent)
{
    struct Vertex* result = new struct Vertex();

    result->next = std::map<char, struct Vertex*>();
    result->is_terminal = false;
    result->parent = parent;

    return result;
}

Trie::Trie()
{
    root = initVertex(nullptr);
}

Trie::~Trie()
{

}

void Trie::insert(char* cstr)
{
    struct Vertex* current = this->root;
    char* ptr = cstr;
    while (*ptr)
    {
        if (auto search = current->next.find(*ptr); search != current->next.end())
        {
            ptr++;
            current = search->second;
            continue;
        }

        current->next[*ptr] = initVertex(current);
        current = current->next[*ptr];
        ptr++;
    }

    current->is_terminal = true;
}

int main()
{
    Trie t;
    t.insert("abc");
    t.insert("ac");
    return 0;
}
