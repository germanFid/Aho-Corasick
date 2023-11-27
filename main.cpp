#include <map>
#include <string.h>
#include <iostream>

#define FIND_SUCCESS 100
#define FIND_FAIL -100
#define FIND_PREFIX_FAIL -200

struct Vertex
{
    std::map<char, struct Vertex*> next;
    bool is_terminal;
    struct Vertex* parent;
    char prev_char;

    struct Vertex* sufflink;
    std::map<char, struct Vertex*> go;

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

    struct Vertex* get_root() const;

    struct Vertex* get_link(struct Vertex* vertex);
    struct Vertex* go(struct Vertex* vertex, char c);
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
    result->go = std::map<char, struct Vertex*>();

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

Vertex* Trie::get_root() const
{
    return this->root;
}

Vertex *Trie::get_link(struct Vertex* vertex)
{
    if (vertex->sufflink == nullptr)
    {
        if(vertex == this->root || vertex->parent == this->root)
        {
            vertex->sufflink = this->root;
        }

        else
        {
            vertex->sufflink = this->go(this->get_link(vertex->parent), vertex->prev_char);
        }
    }

    return vertex->sufflink;
}

Vertex *Trie::go(Vertex *vertex, char c)
{
    if (auto search = vertex->go.find(c); search == vertex->go.end())
    {
        if (auto search_next = vertex->next.find(c); search_next != vertex->next.end())
        {
            vertex->go[c] = vertex->next[c];
        }

        else if (vertex == this->root)
        {
            vertex->go[c] = this->root;
        }

        else
        {
            vertex->go[c] = this->go(this->get_link(vertex), c);
        }
    }
    
    return vertex->go[c];
}

int main()
{
    Trie t;
    t.insert("amazing");

    int result = t.find("ac");
    int result2 = t.find("ab");

    char txt[] = "hello amazing world ac";
    struct Vertex* v = t.get_root();

    for (int i = 0; i < strlen(txt); i++)
    {
        v = t.go(v, txt[i]);
        if (v->is_terminal)
        {
            std::cout << "Found on index: " << i << std::endl;
        }
    }

    return 0;
}
