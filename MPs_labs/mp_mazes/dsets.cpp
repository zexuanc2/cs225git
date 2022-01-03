/* Your code here! */
#include "dsets.h"
#include <iostream>
using namespace std;

void DisjointSets::addelements(int num) {
    for (int i = 0; i < num; i++) {
        elements.push_back(-1);
    }
}
int DisjointSets::find(int elem) {
	if (elements[elem] < 0) return elem; 
	else {
		int root = find(elements[elem]); 
		elements[elem] = root; 
		return root;
	}
}
void DisjointSets::setunion(int a, int b) {
	int rootA = find(a); 
	int rootB = find(b);
	if (rootA == rootB) return; 
	int newSize = elements[rootA] + elements[rootB];
	if (elements[rootA] <= elements[rootB]) { 
		elements[rootB] = rootA; 
		elements[rootA] = newSize; 
	} else { 
		elements[rootA] = rootB; 
		elements[rootB] = newSize; 
	}
}
int DisjointSets::size(int elem) {
	return -1 * elements[find(elem)]; 
}

