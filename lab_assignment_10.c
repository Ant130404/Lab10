#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{
    struct Trie* children[26];
    int count;
};

// Function prototypes
void insert(struct Trie *pTrie, char *word);
int numberOfOccurances(struct Trie *pTrie, char *word);
struct Trie *deallocateTrie(struct Trie *pTrie);
struct Trie *createTrie();
int readDictionary(char *filename, char **pInWords);

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
	int len = strlen(word);

	struct Trie* temp = pTrie;
	for(int i=0; i<len; i++)
	{
		if(temp->children[word[i]-'a'] == NULL)
			temp->children[word[i]-'a'] = createTrie();

		temp = temp->children[word[i]-'a'];	
	}
	temp->count++;
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
	if(pTrie == NULL)
		return 0;
	
	int len = strlen(word);

	struct Trie *temp = pTrie;
	for(int i=0; i<len; i++)
	{
		if(temp->children[word[i]-'a'] == NULL)
			return 0;
		temp = temp->children[word[i]-'a'];
	}

	return temp->count;
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
	if(pTrie == NULL)
		return NULL;

	for(int i=0; i<26; i++)
	{
		if(pTrie->children[i] != NULL)
			deallocateTrie(pTrie->children[i]);
	}

	free(pTrie);

	return NULL;
}

// Initializes a trie structure
struct Trie *createTrie()
{
	struct Trie *myTrie = malloc(sizeof(struct Trie));

	for(int i=0; i<26; i++)
		myTrie->children[i] = NULL;

	myTrie->count = 0;

	return myTrie;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
	FILE *fp = fopen(filename, "r");

	int numWords;
	fscanf(fp, "%d", &numWords);

    char buffer[256];
    for (int i = 0; i < numWords; i++)
    {
        fscanf(fp, "%s", buffer);
		int len = strlen(buffer)+1;
		pInWords[i] = malloc(sizeof(char)*len);
		strcpy(pInWords[i], buffer);
    }

    fclose(fp);
    return numWords;
}

int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}