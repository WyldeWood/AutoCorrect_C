#include "AutoCorrect.h"
#include "Trie2.h"
#include "Dlev.h"
#include "linkedlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <crtdbg.h>


int main() {
	char* FilePath = "C:\\Users\\aww50\\Desktop\\Coding_Projects\\Text_Files\\RandomWords.txt";
	Opaque_trie_t Test_Trie = trie_init();
	FileLoadIn(Test_Trie, FilePath);
	char* word = "Broke";
	completeWord(Test_Trie, word);


	trie_destroy(Test_Trie);
}
Linked_List_Opaque_Pointer completeWord(Opaque_trie_t test_Trie, char* word) {

	Linked_List_Opaque_Pointer ListOfWords = Create_LL();
	struct TrieNode* CurrentNode;
	CurrentNode = test_Trie->Root;
	
	for (int i = 0; i < strlen(word); i++) {
		CurrentNode = CurrentNode->Children[word[i] - 97];
	}
	for (int i = 0; i < 26; i++) {
		searchForCompletions(CurrentNode, word, ListOfWords);
	}
	
	return ListOfWords;
}
correctWord(const char* word, Opaque_trie_t trie) {

}
searchForCompletions(struct TrieNode* Node, char* foundword, Linked_List_Opaque_Pointer ListofWords) {
	for (int i = 0; i < 26; i++) {
		if (Node->Children[i] != NULL){
			if (Node->IsWord == true) {
				Priority_LL_Insert_(ListofWords, foundword ,Node->Frequency);
			}

			const int FoundWordLength = strlen(foundword)+1;
			char** newWord = malloc(sizeof(char*)*FoundWordLength);
			strcpy(newWord, foundword);
			strcat(foundword, Node->Children[i]->Letter);
			searchForCompletions(Node->Children[i], newWord, ListofWords);
			free(newWord);
		}
	}
}
/*
 start at root node
 section of searched word
 section of found word
 current node
 next node

main{
	currentNode = Root
	ExploreChildren(0, -1, 0, currentNode, enteredWord, NULL)

	display first five words in priority queue
	}
 }
        
 ExploreChildren(int editsMade, int layersDown, int wordIndex, node* currentNode, char* enteredWord, char* foundWord){
		layersDown++
		if layersDown > 0{
			add CurrentNode->Parent->letter to foundWord
		}
		if levinstien = 1{
			if found word is a word {
			add Foundword to priority queue based on its frequency
		}
		if editsMade > 1{
			stop searching this branch
		}
		else{
			for each of the current node's children{
				if currentNode->letter == enteredword[layersDown]{
					wordIndex++// if the letters at the same index it the enteredWord and the foundWord are the same we can ignore them when computing Dlev. moving word index up makes sure we dont check them in succesive Dlev calculations
					ExploreChildren(editsMade, layersDown, wordIndex, currentNode, enteredWord, foundWord)
				}
				else if wordIndex == length of searched word{ foundWord == enteredWord
					for each child of current node
						if childNode is a word{
							add childNode->letter to foundword
							add Foundword to priority queue based on its frequency   
						}
				}
				else{
					editsMade = call Dlev on the substrings of enteredWord and foundWord that go from wordIndex to layersDown
					ExploreChildren(editsMade, layersdown, wordIndex, currentNode, enteredWord, foundWord)  
				}
	 
 }
 
 */