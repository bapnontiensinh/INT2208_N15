#include <bits/stdc++.h>
using namespace std;
// k trong kich thuoc hinh vuong 2^k x 2^k
struct Node {
	int x, y;
	int data;
	Node* NW;
	Node* NE;
	Node* SE;
	Node* SW;
	Node* pre;
	Node (int i, int j){
		x = i;
		y = j;
		NW = NULL;
		NE = NULL;
		SE = NULL;
		SW = NULL;
		pre= NULL;
	}
	Node(int value, int i, int j){
		x = i;
		y = j;
		data = value;
		NW = NULL;
		NE = NULL;
		SE = NULL;
		SW = NULL;
		pre= NULL;	
	}
};

Node* inSert (Node *root, int k, int value, int a, int b){	
	if (a < 0 || b < 0 || b >= pow(2,k) || a >= pow(2,k)) {
		cout << "ko the chen";
		return root;
	}	
	Node *p = root;
	
	while (k > 0){
		int canh = pow(2,k);	

		k--;
		
		if ((a < p->x+canh/2)  && (b >= p->y+canh/2)){
			
			if(p->NW==NULL) p->NW = new Node(p->x,p->y+canh/2);
			p = p->NW;
		}
		else if ((a < p->x+canh/2) && (b < p->y+canh/2))  {
			if(p->SW==NULL) p->SW = new Node(p->x,p->y);
			p = p->SW;
		}
		else if ((a >= p->x+canh/2) && (b >= p->y+canh/2)) {
			if(p->NE==NULL) p->NE = new Node(p->x+canh/2,p->y+canh/2);
			p = p->NE;
		}
		else {	
			if(p->SE==NULL) p->SE = new Node(p->x+canh/2,p->y);
			p = p->SE;
		}												
	}
	p->data = value;
	return root;
}

bool Search (Node *root, int k, int a, int b){
	if (a < 0 || b < 0 || b >= pow(2,k) || a >= pow(2,k)) {
		return false;
	}
	Node *p = root;
	
	while (k > 0){
		int canh = pow(2,k);	

		k--;
		
		if ((a < p->x+canh/2)  && (b >= p->y+canh/2)){
			if(p->NW==NULL) return false;
			p = p->NW;
		}
		
		else if ((a < p->x+canh/2) && (b < p->y+canh/2))  {
			if(p->SW==NULL) return false;
			p = p->SW;
		}
		
		else if ((a >= p->x+canh/2) && (b >= p->y+canh/2)) {
			if(p->NE==NULL) return false;
			p = p->NE;
		}
		
		else {	
			if(p->SE==NULL) return false;
			p = p->SE;
		}												
	}
	return true;
}

int num_null (Node *root){
	int count = 0;
	if (root->NW == NULL) count++;
	if (root->NE == NULL) count++;
	if (root->SE == NULL) count++;
	if (root->SW == NULL) count++;
	
	return count;
}

bool del (Node* root, int k, int a, int b){
	if (Search(root,k,a,b) == false) return false;
	
	else{
			Node *p = root;
			
			while (k > 0){
			int canh = pow(2,k);	
			
			k--;
		
			if ((a < p->x+canh/2)  && (b >= p->y+canh/2)){
				Node *temp = p;
				p = p->NW;
				p->pre = temp;
			}
			else if ((a < p->x+canh/2) && (b < p->y+canh/2))  {				
				Node *temp = p;
				p = p->SW;
				p->pre = temp;
			}
			else if ((a >= p->x+canh/2) && (b >= p->y+canh/2)) {
				Node *temp = p;
				p = p->NE;
				p->pre = temp;
			}
			else {
				Node *temp = p;	
				p = p->SE;
				p->pre = temp;
			}												
		} 
		
		Node *temp1 = p->pre;
		delete(p);
		p = NULL;
		p = temp1;
		
		while (num_null(p)==4){
			temp1 = p->pre;
			delete(p);
			p = NULL;
			p = temp1;	
		}
		return true;
	}
}

bool isIntersect(Node *root, int k, int a, int b, int rad){
	int range_x1 = a-rad; int range_x2 = a+rad;
	int range_y1 = b-rad; int range_y2 = b+rad;
	
	if (a == pow(2,k) && b==pow(2,k) && rad == 1) return false;
	
	if (a<0 || a>=pow(2,k) || b<0 || b>=pow(2,k)) return false;
	else{
		if ((root->x <= a&&a<= root->x+pow(2,k) && root->y <= b&&b <= root->y+pow(2,k))
	|| (root->x <= range_x1&&range_x1 <= root->x+pow(2,k) && root->y <= b&&b <= root->y+pow(2,k))
	|| (root->x <= range_x2&&range_x2 <= root->x+pow(2,k) && root->y <= b&&b <= root->y+pow(2,k))
	|| (root->y <= range_y1&&range_y1 <= root->y+pow(2,k) && root->x <= a&&a <= root->x+pow(2,k))
	|| (root->y <= range_y2&&range_y2 <= root->y+pow(2,k) && root->x <= a&&a <= root->x+pow(2,k))) return true;
	}
}

void RangeSearch(Node* root, int k, int a, int b, int rad){
	if (isIntersect(root,k,a,b,rad) == false || root == NULL) return;
	else {
		while(k>0){

			k--;

			RangeSearch(root->NW,k,a,b,rad);
			RangeSearch(root->NE,k,a,b,rad);
			RangeSearch(root->SE,k,a,b,rad);
			RangeSearch(root->SW,k,a,b,rad);
			
			if(k==0){
				cout << "(" <<root->x<<","<<root->y<<")" <<endl;
			}	
		}		
	}			
}

int main(){
	Node *root = new Node(0,0);
	cout << "(" << root->x << "," << root->y << ")" <<endl;
	
	root = inSert (root,2,111,1,3); // k= 2
	cout << "(" << root->NW->NE->x << "," << root->NW->NE->y << ")";
	cout << root->NW->NE->data << endl;
	
	root = inSert (root,2,222,1,1);
	cout << "(" << root->SW->NE->x << "," << root->SW->NE->y << ")";
	cout << root->SW->NE->data << endl;
	
	if (Search(root,2,1,1) == true) cout << "\nfound";
	else cout << "\nnot found";
	
	if (Search(root,2,1,2) == true) cout << "\nfound";
	else cout << "\nnot found";
	
	if (del(root,2,1,3) == true) cout << "\ndeleted\n";
	else cout << "\nerror\n";
	
	cout << "\n(" << root->NW->NE->x << "," << root->NW->NE->y << ") ";
	cout << root->NW->NE->data << endl;
	
	cout << "\n(" << root->NW->x << "," << root->NW->y << ")\n";
	
	
//	cout << "(" << root->SW->NE->x << "," << root->SW->NE->y << ")";
//	cout << root->SW->NE->data << endl;
	
//	cout <<"rangeSearch: "<<endl;
//	RangeSearch(root,2,2,2,3);	
	
	return 0;
}

