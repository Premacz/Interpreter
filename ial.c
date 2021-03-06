///////////////////////////////////////////////////////////////////////////////
/* ---------- IMPLEMENTACE INTERPRETU IMPERATIVNÍHO JAZYKA IFJ15 ----------- */
///////////////////////////////////////////////////////////////////////////////
//
//	AUTOŘI:
//
//	xbedna57 	ADAM BEDNÁRIK
//	xmacha63 	ERIK MACHÁČEK
//	xmalar02 	MARTIN MALÁRIK
//	xlengu00 	MANH LE NGUYEN
//
///////////////////////////////////////////////////////////////////////////////

#include "ial.h"

//////////////////////////////////////////////////
// void treeInit(nodePtr *Root)
// *Root - root of the binary tree
////////////////////
// Tree inicialization 
//////////////////////////////////////////////////
void treeInit (nodePtr *Root)
{
	*Root = NULL;
}

//////////////////////////////////////////////////
// nodePtr searchNodeBySymbol (nodePtr *Root, symbolPackagePtr symbol)
// *Root - root of the binary tree
// symbol - symbol from symbolPackagePtr
////////////////////
// Search node by symbol
//////////////////////////////////////////////////
nodePtr searchNodeBySymbol (nodePtr *Root, symbolPackagePtr symbol)
{

	if(Root != NULL)
	{
		int i = ST_Compare((*Root)->data, symbol);
		if(i == 0)
			return *Root;
		else if(i < 0)
			return searchNodeBySymbol(&(*Root)->lChild, symbol);
		else
			return searchNodeBySymbol(&(*Root)->rChild, symbol);
	}
	else
		return NULL;
}

//////////////////////////////////////////////////
// nodePtr searchNodeByKey (nodePtr *Root, string key)
// *Root - root of the binary tree
// key - key of the node
////////////////////
// Search node by its key
//////////////////////////////////////////////////
nodePtr searchNodeByKey (nodePtr *Root, string key)
{
	if(*Root != NULL)
	{
		int i = strCompare((*Root)->data->key, key);
		if(i == 0)
			return *Root;
		else if(i < 0)
			return searchNodeByKey(&(*Root)->lChild, key);
		else
			return searchNodeByKey(&(*Root)->rChild, key);
	}
	else
		return NULL;
}

//////////////////////////////////////////////////
// nodePtr nodeInsert (nodePtr* Root, symbolPackagePtr symbol)
// *Root - root of the binary tree
// symbol - symbol from symbolPackagePtr
////////////////////
// Insert node into tree
//////////////////////////////////////////////////
nodePtr nodeInsert (nodePtr* Root, symbolPackagePtr symbol)
{
	if(*Root == NULL)
	{
		nodePtr node = MM_Malloc(sizeof(struct binaryTree));
		node->data = symbol;
		node->lChild = NULL;
		node->rChild = NULL;

		*Root = node;

        return *Root;
	}
	else
	{
		int i = ST_Compare((*Root)->data, symbol);
		if(i < 0)
		{
			return nodeInsert(&(*Root)->lChild, symbol);
		}
		else if(i > 0)
		{
			return nodeInsert(&(*Root)->rChild,symbol);
		}
		else
		{
			(*Root)->data = symbol;
			return *Root;
		}
	}
}

//////////////////////////////////////////////////
// void deleteTree (nodePtr *RootPtr)
// *RootPtr - pointer of root of the binary tree
////////////////////
// Delete whole binary tree
//////////////////////////////////////////////////
void deleteTree (nodePtr *RootPtr)
{
	if(*RootPtr != NULL)
	{
		deleteTree (&(*RootPtr)->lChild);
		deleteTree (&(*RootPtr)->rChild);
		MM_Free(*RootPtr);
		*RootPtr = NULL;
	}
}

//////////////////////////////////////////////////
// int find(string s, string search)
// s - string in which we are finding
// search - string which we are finding
////////////////////
// Finding string search in string s
//////////////////////////////////////////////////
int find(string s, string search)
{
	int i	, k = -1, tsize = s->length , psize = search->length ;
	int *pi = prefix_to_FIND(search);
	if (!pi)
		{				//chyba v pridelovaní pamete v compute_prefix_function
    mistake (ERR_INTERN,"couldn`t get memory for prefix_to_FIND");
		}
		if ( search == NULL || search->length == 0 ) return 0;

	for (i = 0; i < tsize; i++)
	{
		while (k > -1 && search->str[k+1] != s->str[i]) k = pi[k];
		if ( s->str[i] == search->str[k+1]) k++;
		if (k == psize - 1)
			{
				MM_Free(pi);		//kontrola
				return i-k;			//true ak nasel
			}

	}
	MM_Free(pi);				//kontrola
	return -1;
}

//////////////////////////////////////////////////
// string sort (string s)
// s - string which we get from deque
////////////////////
// sort strings returns the sorted string
//////////////////////////////////////////////////
string sort (string s) {
	Deque List_Deque = NULL;
	Deque item_L_Deque = NULL;
	Deque List_0 = NULL;
	Deque List_1 = NULL;
	Deque List_new = NULL;

	//seznam zacatku
	List_Deque = D_Init();

	char *curr, *prev;

	for (int i = 0; i < (int)s->length; i++) {
		curr = &s->str[i];
		if (i == 0) {	//prvni polozka ve stringu se stane zacatkem prvniho listu
			item_L_Deque = D_Init();	//inicializace polozek pro jednotlive listy

			D_PushBack(item_L_Deque, curr);
			D_PushBack(List_Deque, item_L_Deque);
		}
		else {
			if (*curr < *prev) {	//pokud soucasna polozka je vetsi nez predchozi stane se zacatkem noveho listu
				item_L_Deque = D_Init();

				D_PushBack(item_L_Deque, curr);
				D_PushBack(List_Deque, item_L_Deque);
			}
			else {
				D_PushBack(item_L_Deque, curr);
			}
		}
		prev = curr;
	}

	//--------------------------------------------------------------------------------------------------
	//--sorting string--
	char *L0, *L1;

	while (TRUE) {
		List_0 = D_PopFront(List_Deque);	//popovani prvniho horniho listu

		if (D_Empty(List_Deque)) {	//pokud seznam ma jen jeden list
			break;
		}
		else {	//jinak popuji dalsi list v seznamu
			List_1 = D_PopFront(List_Deque);
			List_new = D_Init();
		}

		while (TRUE) {
			int em_0 = 0, em_1 = 0;

			if (D_Empty(List_0))
				em_0 = 1;

			if (D_Empty(List_1))
				em_1 = 1;

			if (em_0 && em_1)	//oba seznamy jsou prazdne
				break;
			else if (em_0){	//pokud prvni uz neobsahuje dalsi prvky pushuji zbytek z 2. listu
				L1 = D_PopFront(List_1);
				D_PushBack(List_new, L1);
			}
			else if (em_1){	//pokud druhy uz neobsahuje dalsi prvky pushuji zbytek z 1. listu
				L0 = D_PopFront(List_0);
				D_PushBack(List_new, L0);
			}
			else {	//jinak pokracuji v porovnavani
				L0 = D_TopFront(List_0);
				L1 = D_TopFront(List_1);

				if (*L0 > *L1)
				{
					L1 = D_PopFront(List_1);
					D_PushBack(List_new, L1);
				}
				else
				{
					L0 = D_PopFront(List_0);
					D_PushBack(List_new, L0);
				}
			}
		}

		//terminatuji prvni 2 listy
		D_Terminate(List_0);
		D_Terminate(List_1);

		//spojeny list vlozim na konec seznamu
		D_PushBack(List_Deque, List_new);
	}

	D_Terminate(List_Deque);	//v seznamu zustal jen jeden list

	char str_s[s->length + 1];

	//vytahnu sortovany string a vratim ho
	int i = 0;
	while (!D_Empty(List_0)) {
		L0 = D_PopFront(List_0);

		str_s[i] = (char)*L0;
		i++;
	}
	str_s[i] = '\0';

	string sorted_str = charToStr(str_s);

	return sorted_str;

}
