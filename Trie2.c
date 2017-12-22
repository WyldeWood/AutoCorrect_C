// ConsoleApplication4.cpp : Defines the entry point for the console application.
//


#define _CRT_NONSTDC_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC
#define CHARS 1000
#define SIZEOFALPHABET 26
#include "Trie2.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <crtdbg.h>


struct TrieNode* NodeConstructor(char letter, struct TrieNode* Parent, int IsWord) {
	struct TrieNode* newNode = (struct TrieNode*)malloc(sizeof(struct TrieNode));//create a new node
	memset(newNode->Children, NULL, sizeof(newNode->Children));//initalize children to 0
	newNode->Letter = letter;
	newNode->Parent = Parent;
	newNode->Frequency = 0;
	newNode->IsWord = IsWord;
	return newNode;
}

Opaque_trie_t trie_init() {
	Opaque_trie_t NewTrie = (Opaque_trie_t)malloc(sizeof(Opaque_trie_t));
	NewTrie->Root = (struct TrieNode*)malloc(sizeof(struct TrieNode));
	memset(NewTrie->Root->Children, NULL, sizeof(NewTrie->Root->Children));
	NewTrie->Root->Letter = 0;
	NewTrie->Root->Frequency = 0;
	return NewTrie;
}
char* makeLowerCase(char* word) {
	int i = 0;
	while (word[i] != NULL) {
		word[i] = tolower(word[i]);
		i++;
	}
	return word;
}
int FileLoadIn(Opaque_trie_t trie, const char* fileName) {
	FILE * filePointer;
	char charString[CHARS];
	char* stringToken;
	filePointer = fopen(fileName, "r");
	if (filePointer == NULL) perror("Error opening file");
	else {
		while (fgets(charString, CHARS, filePointer) != NULL) {
			stringToken = strtok(charString, " .,\n+=-_)(1234567890!@#$%^&*;:\'\"\\/?><~`	");
			while (stringToken != 0 ) {
				trie_insert(trie, stringToken);
				stringToken = strtok(NULL, " .,\n+=-_)(12345	67890!@#$%^&*;:\'\"\\/?><~`");
			}
		}
		fclose(filePointer);
	}
}
struct TrieNode* findChild(struct TrieNode* Node, char letter) {// find the child node containing the searched letter
	struct Node* ReturnNode = NULL; 
  	if (Node->Children[((int)letter) - 97] != NULL) {
		ReturnNode = Node->Children[((int)letter) - 97];
	}
	return ReturnNode;
}
void FreeNode(struct TrieNode* Node) {
	if (Node != NULL) {
		for (int i = 0; i < SIZEOFALPHABET; i++) {
			FreeNode(Node->Children[i]);
		}
	}
	free(Node);
}
void trie_destroy(Opaque_trie_t trie) {
	struct Node* current = trie->Root;
	FreeNode(current);
	free(trie);
}
int trie_insert(Opaque_trie_t trie, char* word) {
	makeLowerCase(word);
	struct TrieNode* current = trie->Root;//start at top
	for (int i = 0; i < strlen(word); i++) {//for each letter in the word being inserted
		if (word[i] != 42) {
			struct TrieNode* child = findChild(current, word[i]);
			if (child != NULL) {//will the searched letter exists in trie
				current->Frequency++;
				current = child;
			}
			else {//word is not in trie already
				current->Children[word[i]-97] = NodeConstructor(word[i], current, false);
				current = current->Children[word[i] - 97];
			}
			if (i == strlen(word) - 1) {// if it is inserting last letter of word
				current->IsWord = true;//note that the string of nodes ending with this node is a word.
				current->Frequency++;
			}
		}
	}
	return 1;
}
int trie_contains(Opaque_trie_t trie, char* word) {
	struct TrieNode* current = trie->Root;
	while (current != NULL){ //while the word may still be in the trie
		for (int i = 0; i < strlen(word); i++) {
			struct TrieNode* next = findChild(current, word[i]);
			if (next == NULL) {//if word is not found
				return 0;
			}   
			current = next;
		}
		if (current->IsWord == true) {
			return 1;
		}
		else {
			return 0;
		}
	}
	return 0;
}
int getFrequency(Opaque_trie_t trie, char* word) {
	struct TrieNode* current = trie->Root;
	char* StrippedWord = strtok(word, " .,\n+=-_)(1234567890!@#$%^&*;:\'\"\\/?><~`	");
	StrippedWord = makeLowerCase(StrippedWord);
	for (int i = 0; i < strlen(word); i++) {
		current = findChild(current, word[i]);
	}
	return current->Frequency;
}