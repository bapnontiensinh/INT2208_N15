#include<bits/stdc++.h>
using namespace std;

//chon chieu cua cay
const int k = 2; //cay 2-chieu -> k=2


struct Node 
{
    double point[k];
    Node *left, *right; 
};
struct Node* newNode(double arr[]) 
{ 
    struct Node* temp = new Node;
    for (int i=0; i<k; i++) 
       temp->point[i] = arr[i];

    temp->left = temp->right = NULL; 
    return temp;
}

/*phep toan tim kiem*/
//so sanh diem 2 diem, = tra ve true, != tra ve false
bool arePointsSame(double point1[], double point2[])
{ 
    for (int i = 0; i < k; ++i)
        if (point1[i] != point2[i]) 
            return false;
    return true; 
}
//tim kiem 1 diem point[] trong cay, co tra ve true , ko co tra ve false
bool searchRec(Node* root, double point[], unsigned depth)
{
    if (root == NULL)
        return false; 
    if (arePointsSame(root->point, point))
        return true; 
    unsigned c = depth % k; //c : stt chieu (ko gian)
    if (point[c] < root->point[c]) 
        return searchRec(root->left, point, depth + 1);
    return searchRec(root->right, point, depth + 1);
}
bool search(Node* root, double point[])
{
    return searchRec(root, point, 0); 
}

/*phep toan xen tra ve node*/
//xen 1 node moi va tra ve goc cua cay
Node *insertRec(Node *root, double point[], unsigned depth) 
{
    if (root == NULL)
       return newNode(point);
    unsigned cd = depth % k;
    if (point[cd] < (root->point[cd]))
        root->left  = insertRec(root->left, point, depth + 1);
    else
        root->right = insertRec(root->right, point, depth + 1);
    return root;
} 
Node* insert(Node *root, double point[])
{
    return insertRec(root, point, 0);
}

/* phep toan loai (delete)*/
//tim va tra ve node co point[d] nho nhat trong x,y,z
Node *minNode(Node *x, Node *y, Node *z, int d) 
{ 
    Node *temp = x; 
    if (y != NULL && y->point[d] < temp->point[d]) 
       temp = y; 
    if (z != NULL && z->point[d] < temp->point[d]) 
       temp = z; 
    return temp; 
}
//
Node *findMinRec(Node* root, int d, unsigned depth) 
{ 
    if (root == NULL) 
        return NULL; 
  
    unsigned cd = depth % k; 
  
    if (cd == d) 
    { 
        if (root->left == NULL) 
            return root; 
        return findMinRec(root->left, d, depth+1); 
    } 
    return minNode(root, 
               findMinRec(root->left, d, depth+1), 
               findMinRec(root->right, d, depth+1), d); 
} 
Node *findMin(Node* root, int d) 
{ 
    return findMinRec(root, d, 0); 
} 
void copyPoint(double p1[], double p2[]) 
{ 
   for (int i=0; i<k; i++) 
       p1[i] = p2[i]; 
}
Node *deleteNodeRec(Node *root, double point[], int depth) 
{
    if (root == NULL) 
        return NULL;
    int cd = depth % k;
    if (arePointsSame(root->point, point)) 
    {
        if (root->right != NULL) 
        {
            Node *min = findMin(root->right, cd);
            copyPoint(root->point, min->point);
            root->right = deleteNodeRec(root->right, min->point, depth+1); 
        } 
        else if (root->left != NULL)
        { 
            Node *min = findMin(root->left, cd); 
            copyPoint(root->point, min->point); 
            root->right = deleteNodeRec(root->left, min->point, depth+1); 
        } 
        else
        { 
            delete root;
            return NULL; 
        }
        return root; 
    }
    if (point[cd] < root->point[cd]) 
        root->left = deleteNodeRec(root->left, point, depth+1); 
    else
        root->right = deleteNodeRec(root->right, point, depth+1); 
    return root; 
}
 Node* deleteNode(Node *root, double point[]) 
{
   return deleteNodeRec(root, point, 0); 
}

/*phep toan tim kiem pham vi cay */
void RangeSearchRec(Node *root, double opoint[], double r,unsigned depth)
{
	if (root != NULL)
	{
		
		double s=0;
		unsigned c=depth%k;
		for(int i=0;i<k;i++)
		{
			s=s+pow((opoint[i]-root->point[i]),2);
		}
		if(pow(r,2)>=s)
		{
			cout<<"(";
			for(int i=0;i<k;i++)
			{
				cout<<root->point[i];
				if(i<k-1)	cout<<", ";
			}
			cout<<") ";
		}
		
		//diem thuoc cay chieu c, point[c]<opoint[c]-r ko xet left
		if(root->point[c]>=opoint[c]+r)
			RangeSearchRec(root->left, opoint, r, depth + 1);
		//diem thuoc cay chieu c, point[c]>opoint[c]+r ko xet right
		if(root->point[c]<=opoint[c]+r)
			RangeSearchRec(root->right, opoint, r, depth + 1);
	}
}
void RangeSearch(Node *root, double opoint[], double r)
{
	RangeSearchRec(root, opoint, r, 0);
}

//in diem 
void NLR(Node *root)
{
	if (root != NULL)
	{
		cout<<"(";
		for(int i=0;i<k;i++)
		{
			cout<<root->point[i];
			if(i<k-1)	cout<<", ";
			
		}
		cout<<") ";
		NLR(root->left);
		NLR(root->right);
	}
}

int main() 
{ 
	//khoi tao cay rong
    struct Node *root = NULL;
    //tao mang chua cac phan tu se nhap vao cay
    double points[][k] = {{15, 31}, {24,45 }, {20, 26}, {8, 12}};
    int n = sizeof(points)/sizeof(points[0]);//n : so phan tu mang
    
    /* xen lan luot tung phan tu trong mang points[][k] vao de tao cay */
	for (int i=0; i<n; i++)
       root = insert(root, points[i]);
    NLR(root);
    cout<<"\n";
    
	/*tim kiem node point1[] , co in "Success!\n", ko co in "Unsuccessful! */
    double searchpoint[] = {10, 19};
    cout<<"Search (10,19), Result : ";
    (search(root, searchpoint))? cout << "Success!": cout << "Unsuccessful!"; 
	cout<<"\n";

	/*loai(delete) */
	double deletepoint[] = {15,31};//diem muon xoa
    root = deleteNode(root, deletepoint);
    cout<<"Delete (15, 31), Result : ";
    NLR(root);
    cout<<"\n";
    
    /*Phep toan tim kiem pham vi*/
    double opoint[] = {8,11};
    double r=2;
	cout<<"the points are in the circle , center O(8,11), r=2 : ";
	RangeSearch(root, opoint, r);
    
    return 0; 
}
