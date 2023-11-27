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

int quick_search_aho(char* cstr, char* sub_cstr);
