#include <map>

#define FIND_SUCCESS 100
#define FIND_FAIL -100
#define FIND_PREFIX_FAIL -200

struct Vertex
{
    std::map<char, struct Vertex*> next;
    bool is_terminal;
    struct Vertex* parent;
    char prev_char;

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
    int find(char* cstr);
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
    result->prev_char = '\0';

    result->sufflink = nullptr;
    // result->go = 

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
        current->next[*ptr]->prev_char = *ptr;
        current = current->next[*ptr];
        ptr++;
    }

    current->is_terminal = true;
}

int Trie::find(char* cstr)
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

        return FIND_FAIL;
    }

    if(current->is_terminal) 
        return FIND_SUCCESS;
   
    else 
        return FIND_PREFIX_FAIL;
}

int main()
{
    Trie t;
    t.insert("abc");
    t.insert("ac");

    int result = t.find("ac");
    int result2 = t.find("ab");
    return 0;
}
