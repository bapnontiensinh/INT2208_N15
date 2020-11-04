#include <iostream>
#include <cmath>

using namespace std;

//Cau truc cua mot node trong cay tu phan
struct Node
{
	int data;
	double x;
	double y;
	Node* NW;
	Node* NE;
	Node* SW;
	Node* SE;
};

//Ham tao Node moi
Node* CreateNode(double xPos, double yPos, int val)
{
	struct Node* newNode = new struct Node();
	newNode->data=val;
	newNode->x=xPos;
	newNode->y=yPos;
	newNode->NE=NULL;
	newNode->NW=NULL;
	newNode->SE=NULL;
	newNode->SW=NULL;
	return newNode;
}

//Ham Insert
Node* Insert(Node* root, double xPos, double yPos, int val)
{
	struct Node* newNode = CreateNode(xPos,yPos,val);       //Tao Node moi la newNode co gia tri nhu Node ta dinh chen vao
	struct Node* temp=root;                                 //Tao con tro Temp tro toi root
	if(temp==NULL)											//Neu root rong, tra ve newNode lam goc luon
		return newNode;
	while(true)												//Bat dau lap cho toi khi chen duoc Node
	{
		if(temp->x==newNode->x && temp->y==newNode->y)      						//Neu toa do Node can chen bang toa do luu trong temp, xep cau lenh duoi
		{
			if(temp->data != newNode->data)   										//Neu du lieu trong temp khac du lieu trong newNode, cap nhat lai du lieu moi cho toa do cu, roi break
			{
				temp->data=newNode->data;
				cout<<"Updated Node to contain data: "<<newNode->data<<endl;
				free(newNode);														//Giai phong newNode, do khong dung den
				break;
			}
			else																	//Neu khong, thong bao Node da co san trong 4D Tree, roi break
			{
				cout<<"This node already exist in this 4D tree!"<<endl;
				break;
			}
		}
		if(temp->x<=newNode->x && temp->y<=newNode->y){     //Neu vi tri node can chen vao nam o goc NE cua temp, chay lenh duoi
			if(temp->NE==NULL){
				temp->NE=newNode;                           //Neu con tro goc NE cua temp rong, chen newNode vao do luon, va ket thuc vong lap
				break;
			}
			else											//New khong, chinh cho temp tro toi mien NE cua no
				temp=temp->NE;								
		}
		else if(temp->x>=newNode->x && temp->y>=newNode->y){//Tuong tu truong hop goc NE
			if(temp->SW==NULL){
				temp->SW=newNode;
				break;
			}
			else
				temp=temp->SW;	
		}
		else if(temp->x<=newNode->x && temp->y>=newNode->y){//Tuong tu truong hop goc NE
			if(temp->SE==NULL){
				temp->SE=newNode;
				break;
			}
			else
				temp=temp->SE;
		}
		else if(temp->x>=newNode->x && temp->y<=newNode->y){//Tuong tu truong hop goc NE
			if(temp->NW==NULL){
				temp->NW=newNode;
				break;
			}
			else
				temp=temp->NW;
		}
	}
	return root;											//Tra ve con tro goc root
}

//Ham Search
Node* Search(Node* root, double xPos, double yPos)
{
	struct Node* temp=root;									//Tao con tro temp tro toi root
	while(true)												//Tao vong lap
	{
		if(temp->x==xPos && temp->y==yPos)					//Neu vi tri can tim trung voi vi tri luu trong temp, tra ve con tro temp roi ket thuc vong lap
			return temp;
		if(temp->x<=xPos && temp->y<=yPos)					//Neu vi tri diem can tim nam trong mien NE cua temp, chay lenh duoi
		{
			if(temp->NE==NULL)								//Neu con tro NE cua temp rong, tra ve NULL roi ket thuc
				return NULL;
			temp=temp->NE;									//Neu khong, cho temp = con tro mien NE cua chinh no
		}
		else if(temp->x>=xPos && temp->y>=yPos)             //Tuong tu truong hop mien NE
		{
			if(temp->SW==NULL)
				return NULL;
			temp=temp->SW;
		}
		else if(temp->x<=xPos && temp->y>=yPos)				//Tuong tu truong hop mien NE
		{
			if(temp->SE==NULL)
				return NULL;
			temp=temp->SE;
		}
		else if(temp->x>=xPos && temp->y<=yPos)				//Tuong tu truong hop mien NE
		{
			if(temp->NW==NULL)
				return NULL;
			temp=temp->NW;
		}
	}
}

//Ham Delete
void Delete(Node* root,double xPos, double yPos)
{
	struct Node* del=Search(root,xPos,yPos); 				//Tim vi tri can xoa
	if(del==NULL)											//Neu vi tri can xoa khong ton tai, thong bao roi ket thuc
	{
		cout<<"Can't delete a node if it doesn't exist"<<endl;
	}
	else
	{
		cout<<"This function is currently WIP. Sorry :(";//New co ton tai, tien hanh xoa. Doan nay minh khong biet cach lam, coi nhu WIP, mong ban thong cam :(
		cout<<". According to a certain book, you have to seperate a tree with the delete Node as root from the original tree, then insert all of its children Nodes, except the delete Node itself"<<endl;
		cout<<"It's extremely complicated. An MX quadtree would suit better"<<endl;
	}
}

//Ham RangeSearch: In ra cac diem can tim neu tim duoc, va tra ve 0 neu khong tim thay diem nao
int RangeSearch(Node* root,double x,double y,double r)
{
	//Tinh khoang cach tu tam hinh tron den root
	double tempDis=sqrt((root->y-y)*(root->y-y)+(root->x-x)*(root->x-x));     
	
	int notEmpty=0;  //Bien de luu tru trang thai tim kiem. Bang khong tuc la khong co diem nao thoa man, khac khong tuc la co it nhat mot diem thoa man dieu kien
	if(tempDis<=r)   //Neu khoang cach vua tinh nho hon ban kinh hinh tron, in ra data cua goc, cap nhat trang thai sang khac khong
	{
		cout<<root->x<<" "<<root->y<<" with data: "<<root->data<<endl;
		notEmpty++;
	}
	if(root->NE!=NULL)//New con tro NE cua root rong, chay de quy ham voi root->NE
		RangeSearch(root->NE,x,y,r);
	if(root->NW!=NULL)//Tuong tu truong hop mien NE
		RangeSearch(root->NW,x,y,r);
	if(root->SE!=NULL)//Tuong tu truong hop mien NE
		RangeSearch(root->SE,x,y,r);
	if(root->SW!=NULL)//Tuong tu truong hop mien NE
		RangeSearch(root->SW,x,y,r);
	return notEmpty;  //Tra ve trang thai tim kiem
}

//Chuong trinh chinh
int main()
{
	struct Node* tree=NULL;
	struct Node* findNode=NULL;
	double x,y;     //toa do nhap vao
	int data;		//du lieu nhap vao
	double r;		//ban kinh tim kiem
	int n,i,op;		//So luong phep toan, chi so chay va loai phep toan
	cin>>n;         //Nhap so luong phep toan can thuc hien
	for(i=0;i<n;i++)
	{
		cin>>op;    //Nhap loai phep toan can thuc hien. 1=Insert, 2=Search, 3=Delete(WIP), 4=RangeSearch
		if(op==1)   //Insert
		{
			cin>>x>>y>>data;
			tree=Insert(tree,x,y,data);
		}
		else if(op==2)//Search
		{
			cin>>x>>y;
			findNode=Search(tree,x,y);
			if(findNode!=NULL)                                      //findNode rong->Thong bao khong tim thay, nguoc lai in ra du lieu
			{
				cout<<"Success! Data is "<<findNode->data<<endl;
			}
			else
			{
				cout<<"Unsuccessful!"<<endl;
			}
		}
		else if(op==3)//Delete(WIP)
		{
			cin>>x>>y;
			Delete(tree,x,y);
		}
		else if(op==4)
		{
			cin>>x>>y>>r;
			cout<<"All points within "<<r<<" radius from "<<x<<" "<<y<<":"<<endl;
			if(RangeSearch(tree,x,y,r)==0)       	//Neu ham tra ve gia tri khac khong, ban than ham do se in ra tat ca gia tri can tim luon. New khong, thong bao khong tim thay
			{
				cout<<"No such point";
			}
		}
	}
	return 0;
}


