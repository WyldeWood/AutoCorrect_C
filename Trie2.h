#define _CRT_NONSTDC_NO_WARNINGS
#ifndef Trie
#define Trie
#define SIZEOFALPHABET 26

typedef struct trie_t {
	struct TrieNode* Root;
}* Opaque_trie_t;

struct TrieNode {//deez nuts
	char Letter;
	struct TrieNode* Parent;
	struct TrieNode* Children[SIZEOFALPHABET];
	int Frequency;
	int IsWord;
};

Opaque_trie_t trie_init();
struct TrieNode* NodeConstructor(char, struct TrieNode*, int);
void trie_destroy(Opaque_trie_t trie);
int FileLoadIn(Opaque_trie_t trie, const char *fileName);
int trie_insert(Opaque_trie_t trie, char* word);
int trie_contains(Opaque_trie_t trie, char* word);
int getFrequency(Opaque_trie_t trie, char* word);

#endif
