/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    if (curDim < 0 || curDim >= Dim) return false;  
    if(first[curDim]==second[curDim]) {
      return first<second;
    }  
    return (first[curDim] < second[curDim]);
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */

    double cur_dist = 0, pot_dist = 0;
    for(int i=0; i<Dim;i++){  // Add up squares of differences for each dimension
       	cur_dist += ((target[i]-currentBest[i])*(target[i]-currentBest[i]));
       	pot_dist += ((target[i]-potential[i])*(target[i]-potential[i]));
    }
    if(cur_dist==pot_dist) return potential < currentBest;  // Tiebreak
    return pot_dist<cur_dist;
}

template <int Dim>
unsigned KDTree<Dim>::quickSelect_position(vector<Point<Dim>>& list, int dimension, unsigned left, unsigned right, unsigned pivotIndex){
  	Point<Dim> pivotValue = list[pivotIndex];
  	
  	Point<Dim> temp = list[pivotIndex];
  	list[pivotIndex] = list[right];
  	list[right] = temp;
  	unsigned storeIndex = left;
  	
  	for(unsigned i = left;i<right;i++){
    	if(smallerDimVal(list[i],pivotValue,dimension)){
      		temp = list[storeIndex];
      		list[storeIndex] = list[i];
      		list[i] = temp;
      		storeIndex++;
    	}
  	}
  	temp = list[storeIndex];
  	list[storeIndex] = list[right];
  	list[right] = temp;
  	return storeIndex;
}

template <int Dim>
Point<Dim>& KDTree<Dim>::quickSelect(vector<Point<Dim>>& list, int dimension, unsigned left, unsigned right, unsigned i){
  	if(left==right) return list[left];
  	unsigned pivotIndex = i;
  	pivotIndex = quickSelect_position(list,dimension,left,right,pivotIndex); 
  	if(i==pivotIndex) return list[i];
  	else if(i<pivotIndex) return quickSelect(list, dimension, left, pivotIndex-1, i);
  	else return quickSelect(list, dimension, pivotIndex+1, right, i); 
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::ctorHelper(vector<Point<Dim>>& points_, int dimension, unsigned left, unsigned right){
  	if(points_.empty()||left<0||right>=points_.size()||right<0||left>=points_.size())
    	return NULL;  
  	if(left>right) return NULL;
  	unsigned median_idx = (left+right)/2;  
  	KDTreeNode* subroot_ = new KDTreeNode(quickSelect(points_,dimension%Dim,left,right,median_idx));
  	size+=1;
  	dimension++;
  	
  	subroot_->right = ctorHelper(points_,dimension,median_idx+1,right); 
    subroot_->left = ctorHelper(points_,dimension,left,median_idx-1);
 	  return subroot_;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    size = 0;
    vector<Point<Dim>> points_;
    points_.assign(newPoints.begin(), newPoints.end());
    root = ctorHelper(points_, 0, 0, points_.size()-1);
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
  copy(this->root, other.root);
	size = other.size;
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
  if (this != NULL) clear(root);
  copy(this->root, rhs.root);
  size = rhs.size;
  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
  clear(root);
}


template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */

    return findNearestNeighbor(root, query, 0);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(KDTreeNode * subroot, const Point<Dim>& query, int dimension) const {
	Point<Dim> currentBest = subroot->point;
	bool flag;
  //bound condition
	if (subroot->left == NULL && subroot->right == NULL) return subroot->point;
  //check left
	if (smallerDimVal(query, subroot->point, dimension)) {
		if (subroot->left == NULL)
			currentBest = findNearestNeighbor(subroot->right, query, (dimension + 1) % Dim);
		else  
			currentBest = findNearestNeighbor(subroot->left, query, (dimension + 1) % Dim);
		flag = true;
	}
  //check right
	else {
		if (subroot->right == NULL)
			currentBest = findNearestNeighbor(subroot->left, query, (dimension + 1) % Dim);
		else  // Traverse right
			currentBest = findNearestNeighbor(subroot->right, query, (dimension + 1) % Dim);
		flag = false;  // Set left flag to false
	}
	// If current node's point is closer to target, switch it
	if (shouldReplace(query, currentBest, subroot->point)) currentBest = subroot->point;
	
	// Calculate radius of closest point and then also split distance
	double radius = 0;
	for (int i = 0; i < Dim; i++) {
		radius += (query[i] - currentBest[i]) * (query[i] - currentBest[i]);
	}
	double split_distance = subroot->point[dimension] - query[dimension];
	split_distance = split_distance * split_distance;

	// Check if we need to traverse the other subtree or not
	if (split_distance <= radius) {
		KDTreeNode * need_to_check = flag ? subroot->right : subroot->left;
		if (need_to_check != NULL) {  // If we can traverse other subtree, then traverse
			Point<Dim> otherBest = findNearestNeighbor(need_to_check, query, (dimension + 1) % Dim);
			// Replace currentbest if need be
			if (shouldReplace(query, currentBest, otherBest)) currentBest = otherBest;
		}
	}
	return currentBest;
}

/*
helper function for the rule of three.
*/
template <int Dim>
void KDTree<Dim>::clear(KDTreeNode * subroot) {
	if (subroot == NULL) return;
	if (subroot->left != NULL) clear(subroot->left);
	if (subroot->right != NULL) clear(subroot->right);
	delete subroot;
	subroot = NULL;
}

template <int Dim>
void KDTree<Dim>::copy(KDTreeNode * subroot, KDTreeNode * thatSubroot) {
	subroot = new KDTreeNode();
	subroot->point = thatSubroot->point;
	copy(subroot->left, thatSubroot->left);
	copy(subroot->right, thatSubroot->right);
}

