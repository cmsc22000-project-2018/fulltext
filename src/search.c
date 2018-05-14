#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <gmodule.h>

int main()
{
    string arr[] = {"he", "she", "hers", "his"};
    string text = "ahishers";
    int k = sizeof(arr)/sizeof(arr[0]);
 
    searchWords(arr, k, text);
    return 1;
}

/*
 * Builds a trie, given an array of strings and number of elements in array
 *
 * Inputs:
 *  - char** words: array of words to put into trie
 *  -    int     k: number of elements in words
 *
 * Returns:
 *  an integer representing the number of states, 0 to k inclusive
 */
int buildTrie(char** words, int k)
{
    // TO-DO: trie implementation
    return 0;
}

/*
 * Finds the next state of trie
 *
 * Inputs:
 *  - int  currentState: int representing the current state
 *  - char    nextInput: char representing the next input
 *
 * Returns:
 *  an integer representing the next state, or -1 for failure
 */
int findNextState(int currentState, char nextInput)
{
    return 0;
}

/*
 * Inputs:
 *  - char** words: array of words to put into trie
 *  -    int     k: number of elements in words
 *  -  char*  text: string of text to search (input might change later)
 *
 */
void searchWords(char** words, int k, char* text)
{
    //build the trie
    buildTrie(words, k);
        
    //start search at 0th state
    int currentState = 0;
 
    //look through text for words
    for (int i = 0; i < strlen(text); ++i)
    {
        currentState = findNextState(currentState, text[i]);
 
        // if (match not found) continue;
 
        // printing all matches
        for (int j = 0; j < k; ++j)
        {
            printf("Word %s appears from %d to %d\n", words[j], i-arr[j].size()+1, i);
        }
    }
}