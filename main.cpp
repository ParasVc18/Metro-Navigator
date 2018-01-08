#include <iostream>
#include<stdio.h>
#include "conio2.h"
#include<string.h>
#include<process.h>
#include<stdlib.h>
#include<unordered_map>
#include<vector>
#include<math.h>
#include<queue>
#include <fstream>
#define max 50
using namespace std;

class cust_node
{
    public:
    char c_name[30];
    char ph_no[30];
    int rating;
    vector<cust_node *> refred;
    string ref_no;
    cust_node *parent;
    cust_node()
    {
       rating  = 0;
    }
     cust_node(char name [],char no[],string ref_id)
    {
        //c_name = new char[30];
       //ph_no = new char[30];
        strcpy(c_name,name);
        strcpy(ph_no,no);
       ref_no = ref_id;
        rating  = 100;
        parent = NULL;
//        level = 1;
    }
    cust_node(cust_node *customer)
    {
        strcpy(c_name,customer->c_name);
        strcpy(ph_no,customer->ph_no);
        ref_no = customer->ref_no;
        rating  = customer->rating;
        parent = NULL;
    }
    friend ostream& operator<<(ostream& os, const cust_node& s)
	{
		// write out individual members of s with an end of line between each one
		os << s.c_name << '\n';
		os << s.ph_no << '\n';
		os << s.ref_no << '\n';
		os << s.rating << '\n';
		//os << s.parent;
		return os;
	}
	friend istream& operator>>(istream& is, cust_node& s)
	{
		// read in individual members of s
		is >> s.c_name >> s.ph_no >> s.ref_no >> s.rating;
		return is;
	}
};
unordered_map<string,cust_node*> cust_map;
queue<string> que_ref_id;
unordered_map<string,bool> current_map;
void inc_rating(cust_node * refferer)
{
    int count = 1;
    float inc_percentage = 1;
    int value = 100;
    while(count <= 4 && refferer != NULL)
    {
        refferer->rating += inc_percentage*value; /*inceasing ratings of parent*/
        refferer = refferer->parent;
        inc_percentage = (float)inc_percentage/2;
        count++;
    }
}
string convert_to_string(char *s)
{
    string str;
    int l = 0;
    while(s[l]!='\0')
    {
        str.push_back(s[l]);
        l++;
    }
    return str;
}

void add_to_graph(char *name,char *ph_no,string ref_id)
{
  cust_node *customer = new cust_node(name,ph_no,ref_id);
    string s_ph_no = convert_to_string(ph_no);

    //string s_ref_id = convert_to_string(ref_id);
                            /*making a customer in a k array tree*/
cust_map[s_ph_no] = customer;
                          // ph_no is ref_id
        //cout << strcmp(ref_id,"none") <<endl;
  if(ref_id.compare("none")!=0 && cust_map.count(ref_id) == 1)
  {

      cust_node *refferer = cust_map[ref_id];
      inc_rating(refferer);
      customer->parent = refferer;
      refferer->refred.push_back(customer);
      return;
  }
  else if(ref_id.compare("none") == 0)
  {
      return;
  }
  else
  {
      clrscr();
        gotoxy(66,14);
      cout << "ref_id_does_not_exist" <<endl;
       gotoxy(66,16);
      cout << "Enter refferer_id again:-";
       cin >> ref_id;
      add_to_graph(name,ph_no,ref_id);
  }
}

 struct cust
  {
    char name[50];
	char phno[50];
}c,q[max],a;

int front=0,rear=-1;

void insert()
{

    if(rear==max-1)
{gotoxy(80,13);
    printf("-*-*-*-*-*-*-*-*-");
 gotoxy(80,14);
 printf("Queue is overflow");
 gotoxy(80,15);
 printf("-*-*-*-*-*-*-*-*-");
 getch();
 }
    else
    {
        rear++;
        strcpy(q[rear].name,c.name);
        strcpy(q[rear].phno,c.phno);
        string ref_id;
        if(cust_map.count(q[rear].phno) == 0)
        {
         gotoxy(66,14);
        cout << "Enter ref_id (if_any):-";
        cin >> ref_id;
        add_to_graph(c.name,c.phno,ref_id);
        que_ref_id.push(ref_id);
        }
gotoxy(65,15);
   printf("-*-*-*-*-*-*-*-*-*-*-*-");
 gotoxy(67,16);
 printf("ADDED TO WAITING LIST");
 gotoxy(65,17);
 printf("-*-*-*-*-*-*-*-*-*-*-*-");
   getch(); }
}
void delet()
{

    if((front==0)&&(rear==-1))
    {gotoxy(80,13);
        printf("-*-*-*-*-*-*-*-*-");
 gotoxy(80,14);
 printf("Queue is underflow");
 gotoxy(80,15);
 printf("-*-*-*-*-*-*-*-*-");
        getch();

    }
    strcpy(a.name,q[front].name);
    strcpy(a.phno,q[front].phno);
    front++;

    if(front>rear)
    {
        front=0;
        rear=-1;
    }
}


void display()
{
    int i,j=1;
    if(front==0&&rear==-1)
    {gotoxy(80,13);
        printf("-*-*-*-*-*-*-*-*-");
 gotoxy(80,14);
 printf("Queue is overflow");
 gotoxy(80,15);
 printf("-*-*-*-*-*-*-*-*-");
        getch();

    }
    gotoxy(45,13) ;
		printf("SNo.");
		gotoxy(65,13);
		printf("Name");
		gotoxy(90,13);
		printf("Phone Number");
         int c=14;
    for(i=front;i<=rear;i++,j++)
        {   gotoxy(45,c) ;
			printf("%d",j);
		     gotoxy(65,c) ;
			printf("%s",q[i].name);
		      gotoxy(90,c) ;
			printf("%s",q[i].phno);
			c++;
        }



}
  struct node
  {int item;
	char food[50];
    int cost;
    struct node *next;
int quantity;
	};
struct details
{
char name[50];
char phno[50];
struct node *list;
}t[3];


struct Restuarant
{
  char food[50];
  int price;
} menu[] =
{
	{"Double Cheeseburger", 30},//0
	{"Onion Rings", 20},//1
	{"Veggie Burger", 50},//2
	{"Bottled Drink", 95},//3
	{"Ice Cream Cone", 65},//4
	{"Cold Drink", 50},//5
	{"Pizza", 250},//6
	{"Cream Rolls", 150},//7
	{"Paneer Rolls", 120},//8
	{"Cheese Burger ", 130},//9
	{"Lemonade", 40},//10
	{"Juice", 40}//11
};
void display_menu()
{
int i=12;int c=0;
    	clrscr();
		gotoxy(36,8) ;
		printf("ORDER MENU") ;
		gotoxy(15,11) ;
		printf("Item No.");
		gotoxy(35,11);
		printf("Item Name");
		gotoxy(65,11);
		printf("Item Price");
		while(c<12)
		{gotoxy(15,i) ;
			printf("%d",c);
		     gotoxy(35,i) ;
			printf("%s",menu[c].food);
		      gotoxy(65,i) ;
			printf("%d",menu[c].price);
			c++;
			i++;
		}

}
void removeDuplicates(struct node *start)
{
    struct node *ptr1, *ptr2, *dup;
    ptr1 = start;


    while (ptr1 != NULL && ptr1->next != NULL)
    {
        ptr2 = ptr1;


        while (ptr2->next != NULL)
        {

            if (ptr1->item == ptr2->next->item)
            {

                dup = ptr2->next;
                ptr1->quantity=ptr1->quantity+ptr2->next->quantity;
                ptr2->next = ptr2->next->next;
                delete (dup);
            }
            else
                ptr2 = ptr2->next;
        }
        ptr1 = ptr1->next;
    }
}
void cleartable(int p)
{
    int i=14;int c =0;
    string str = convert_to_string(t[p].phno);
    current_map[str] = false;
    	clrscr();
		gotoxy(70,5);
 printf(".----. .-..-.   .-.   ");
 gotoxy(70,6);
 printf("| {}  }| || |   | |   ");
 gotoxy(70,7);
 printf("| {}  }| || `--.| `--.");
 gotoxy(70,8);
 printf("`----' `-'`----'`----'");
		gotoxy(55,11);
		printf("Name:");
		gotoxy(61,11);
		printf("%s",t[p].name);
		gotoxy(84,11);
		printf("Phone No.:");
		gotoxy(95,11);
		printf("%s",t[p].phno);
		gotoxy(45,13) ;
		printf("Item No.");
		gotoxy(65,13);
		printf("Item Name");
		gotoxy(90,13);
		printf("Item Price");

		gotoxy(105,13);
		printf("Quantity");
        gotoxy(115,13);
		printf("Total");
removeDuplicates(t[p].list);
int q=0;
		while(t[p].list!=NULL)
    {
        gotoxy(45,i) ;
			printf("%d",t[p].list->item);
		     gotoxy(65,i) ;
			printf("%s",t[p].list->food);
		      gotoxy(90,i) ;
			printf("%d",t[p].list->cost);
			gotoxy(105,i);
		printf("%d",t[p].list->quantity);
        gotoxy(115,i);
		printf("%d",t[p].list->cost*t[p].list->quantity);
			q+=t[p].list->cost*t[p].list->quantity;
			i++;
		t[p].list=t[p].list->next;
		}
gotoxy(115,i);
printf("----------");
i=i+1;
gotoxy(118,i);
printf("%d",q);
i=i+1;
gotoxy(115,i);
printf("----------");

cust_node* customer = cust_map[str];
gotoxy(105,i+2);
cout << "Customer current MCOUPONS is: " << customer->rating;
int x;
gotoxy(105,i+4);
cout << "MCOUPONS to be used: ";
cin >> x;
while(x > customer->rating)
{
    gotoxy(105,i+3);
    cout << "MCOUPONS NOT VALID";
    gotoxy(105,i+4);
     cout << "MCOUPONS to be used: ";
     cin >>x;
}
int val = q-(.1*x) > 0? q-(.1*x):0;
gotoxy(105,i+5);
cout << "TOTAL AMOUNT PAYABLE: " << val;
if(val == 0)
{
    x = q*10;
}
customer->rating -= x;

(t[p].list)=NULL;
getch();
}


void add(struct node **q, int item,int quan,char *no)
{
	struct node *temp;
	temp=*q;
    string ph_no = convert_to_string(no);
    cust_node* customer = cust_map[ph_no];
    customer->rating += round(.2*(menu[item].price*quan));
    //cout << customer->rating <<endl;
	if(temp==NULL)
	{
		*q=new (struct node);
		temp=*q;

	}
	else
	{
	  while(temp->next!=NULL)
	  {

		  temp=temp->next;
	}

		temp->next=new (struct node);
		temp=temp->next;
	}

	temp->item=item;
	temp->cost=menu[item].price;
strcpy(temp->food,menu[item].food);
	temp->quantity=quan;
	temp->next=NULL;


}
void frame1()
  {
  int i,j;
  for(i=3,j=1;i<165;i++,j++)//
  {
  gotoxy(i,2);
  printf("%c",205);

  }

  for(i=3;i<47;i++,j++)
  {
  gotoxy(164,i);
  printf("%c",205);

  }

  for(i=164;i>2;i--,j--)//
  {
  gotoxy(i,47);
  printf("%c",205);

  }

  for(i=46;i>2;i--,j--)
  {gotoxy(3,i);
  printf("%c",205);

  }

  }





  void frame()
  {
  int i,j;
  for(i=3,j=1;i<165;i++,j++)//
  {
  gotoxy(i,2);
  printf("%c",205);

  delay(10);

  }

  for(i=3;i<47;i++,j++)
  {
  gotoxy(164,i);
  printf("%c",205);

  delay(10);

  }

  for(i=164;i>2;i--,j--)//
  {
  gotoxy(i,47);
  printf("%c",205);

  delay(10);

  }

  for(i=46;i>2;i--,j--)
  {gotoxy(3,i);
  printf("%c",205);

  delay(10);

  }

  }

  char mainmenu()
  { char chmain='a';

 textbackground(WHITE);
 textcolor(1);
 clrscr();
 frame1();
 gotoxy(50,14);
 printf(".-.  .-.  .--.  .-..-. .-.    .-.  .-..----..-. .-..-. .-. ");
 gotoxy(50,15);
 printf("}  \\/  { / {} \\ { ||  \\{ |    }  \\/  {} |__}|  \\{ || } { | ");
 gotoxy(50,16);
 printf("| {  } |/  /\\  \\| }| }\\  {    | {  } |} '__}| }\\  {\\ `-' / ");
 gotoxy(50,17);
 printf("`-'  `-'`-'  `-'`-'`-' `-'    `-'  `-'`----'`-' `-' `---'  ");

 gotoxy(65,20);
 printf("1---");
 gotoxy(70,20);
 printf("NEW  CUSTOMER ");
 gotoxy(65,22);
 printf("2---");
 gotoxy(70,22);
 printf("MODIFY EXISTING TABLE");
 gotoxy(65,24);
 printf("3---");
 gotoxy(70,24);
 printf("CLEAR TABLE AND GENERATE BILL");
 gotoxy(65,26);
 printf("4---");
 gotoxy(70,26);
 printf("CURRENT STATUS OF TABLE AVAILABILITY");
 gotoxy(65,28);
 printf("5---");
 gotoxy(70,28);
 printf("WAITING CUSTOMER");
 gotoxy(65,30);
 printf("6---");
 gotoxy(70,30);
 printf("EXIT");
 gotoxy(55,33);
 printf("\tPlease enter your choice:");
 chmain=getch();

 clrscr();
return chmain;


  }
  char addcustomer()
  {
    strcpy(c.name,"aman");
  strcpy(c.phno,"9811983274");

      textbackground(WHITE);
 textcolor(1);
 clrscr();
frame1();
 int i,count=0;
 for(i=0;i<3;i++)
    if(t[i].list==NULL)
    count++;

 gotoxy(145,4);
 printf("%d TABLE REMAINING",count);
 gotoxy(50,14);
 printf(".-. . . .-. .-. .-. .  . .-. .-.   .-. .-. .-. .-. .-. .   .-.");
 gotoxy(50,15);
 printf("|   | | `-.  |  | | |\\/| |-  |(    |  )|-   |  |-|  |  |   `-.");
 gotoxy(50,16);
 printf("`-' `-' `-'  '  `-' '  ` `-' ' '   `-' `-'  '  ` ' `-' `-' `-' ");

 gotoxy(65,18);
 printf("1---");
 gotoxy(70,18);
 printf("Name : ");
 gotoxy(65,21);
 printf("2---");
 gotoxy(70,21);
 printf("PHONE NO.:");

  gotoxy(20,25);
 printf("\tPRESS 0 TO RETURN");
gotoxy(77,18);
scanf("%s",c.name);
if(c.name[0]=='0')
 return c.name[0];
gotoxy(80,21);
scanf("%s",c.phno);
string s = convert_to_string(c.phno);
if(current_map.count(s) == 1)
{
    if(current_map[s])
    {
    clrscr();
    gotoxy(80,24);
    cout <<"CUSTOMER ALREADY EXIST";
    delay(900);
    return '0';
    }
}
current_map[s] = true;
return c.name[0];

}

void read()
{

        //cust_node* customer = new cust_node(&obj);
         //string phno = convert_to_string(customer->ph_no);
        //cust_map[phno] = customer;*/
        cust_node s2;
        s2.parent = NULL;
        ifstream ifs("xyz2.dat");
        while(ifs >> s2)
	{
		cust_node* customer = new cust_node(&s2);
		string phno = convert_to_string(customer->ph_no);
		cust_map[phno] = customer;
	}
    for(auto it = cust_map.begin();it!=cust_map.end();it++)
    {
        cust_node*customer = it->second;
        string refid = customer->ref_no;
        if(refid.compare("none")!=0)
        {
        cust_node*p = cust_map[refid];
        customer->parent = p;
        }
        //cout << customer->ph_no;
    }
}
class paradise{
public :
    void m()
    {
    clrscr();
 int i,j,count=3;
 char ch='a';
 int l;
for(l=0;l<3;l++)
t[l].list=NULL;

textcolor(WHITE);

 char y1[]=".           .       ";

 char y3[]="|    _  _. _|*._  _ ";

 char y4[]="|___(_)(_](_]|[ )(_]";

 char y5[]="                 ._|";
 gotoxy(66,11);
 cputs(y1);
 gotoxy(66,12);
 cputs(y3);
 gotoxy(66,13);
 cputs(y4);
 gotoxy(66,14);
 cputs(y5);
 char y2='-';
 textcolor(12);
 for(i=0;i<2;i++)
 {
 for(j=66;j<86;j++)
 {
 gotoxy(j,16);
 clreol();
 putch(y2);
 delay(200);
 }
 clreol();
 delay(250);
 }
 textcolor(3);
 char z[]=".__ .__..__ .__..__ ._. __..___";
 char z1[]="[__)[__][__)[__]|  \\ | (__ [__ ";
 char z2[]="|   |  ||  \\|  ||__/_|_.__)[___";
 for(i=1;i<17;i++)
 {
 clrscr();
 gotoxy(66,i);
 cputs(z);
 gotoxy(66,i+1);
 cputs(z1);
gotoxy(66,i+2);
 cputs(z2);
 delay(150);
 }


 for(i=1;i<150;i=i+10)
 {

 delay(175);

 }

 clrscr();
    read();
 char pass[]=" ";
 char password[30];
 do{
 gotoxy(66,13);
 printf("Enter the Password");
 int i=0;
 char tp;
 while((tp=getch())!='\r')
 {
 printf("*");
 password[i]=tp;
 i++;
 }
 password[i]='\0';
 if(strcmp(password,pass)==0)
 break;
 else
 gotoxy(66,14);
 printf("Wrong Password");
 getch();
 clrscr();
 }while(1);


textbackground(WHITE);
 textcolor(1);
 clrscr();
frame();


int ctr=0;
do{
clrscr();
ch=mainmenu();
if (ch=='6')
{
 /*ofstream file_obj;
    file_obj.open("xyz2.dat", ios::app);
     for ( auto it = cust_map.begin(); it != cust_map.end(); ++it)
    {
      cust_node *customer = it->second;
      cust_node obj(customer);
      obj.parent = NULL;
     file_obj.write((char*)&obj, sizeof(cust_node));

     }*/
     ofstream ofs("xyz2.dat");
      for ( auto it = cust_map.begin(); it != cust_map.end(); ++it)
    {
      cust_node *customer = it->second;
      cust_node s1(customer);
      s1.parent = NULL;
	  ofs << s1;
    }
	ofs.close();
    gotoxy(80,13);
 printf("----------");
 gotoxy(80,14);
 printf(" Thank You");
 gotoxy(80,15);
 printf("----------");
}
if(ch == '6')
{
    exit(0);
}
if(ch=='1')
{
    char ch1=' ';
int z=100;
int t1;
for(t1=0;t1<3;t1++)
{
    if(t[t1].list==NULL)
    {
        z=t1;
        break;
    }

}
ctr=z;
g:
ch1=addcustomer();
if(ctr==100 && ch1!='0')
{
    clrscr();
    insert();
    continue;
}

if(ch1!='0')
{
strcpy(t[ctr].name,c.name);
strcpy(t[ctr].phno,c.phno);
if(cust_map.count(t[ctr].phno) == 0)
{
string ref_id;
clrscr();
 gotoxy(66,14);
cout << "Enter ref_id (if_any):-";
cin >> ref_id;
add_to_graph(t[ctr].name,t[ctr].phno,ref_id);
}
int no,quan1;
      while(ch1!='0')
    {
    clrscr();
    display_menu();
    gotoxy(34,30);
    printf("Enter Item No.:");
      scanf("%d",&no);//99 to break;
      if(no>=12)
        goto g;
      gotoxy(34,32);
      printf("Enter Quantity:");
      scanf("%d",&quan1);
      if(quan1==0)
        continue;

      add(&(t[ctr].list),no,quan1,t[ctr].phno);

      gotoxy(34,34);
      printf("Press any Key to Continue or Press 0 to Return:");
      scanf(" %c",&ch1);
      }
continue;
}
if(ch1=='0')
    {
        continue;
    }
}
if (ch=='2')//add more
{
    clrscr();
    int l;
gotoxy(66,13);
printf("Enter Table Number:");
scanf("%d",&l);
l--;
if(t[l].list==NULL)
{clrscr();
    gotoxy(66,13);
    printf("TABLE IS EMPTY!!!!!!");
    gotoxy(66,14);
    printf("Returning to Main Menu");
    gotoxy(66,15);
    printf("Press Enter to Continue");
getch();
continue;

}
else
{
char ch1=' ';
int no,quan1;
      while(ch1!='0')
      {
          clrscr();
    display_menu();
       gotoxy(34,30);
    printf("Enter Item No.:");
      scanf("%d",&no);//99 to break;
      if(no>=12)
        continue;
     gotoxy(34,32);
      printf("Enter Quantity:");
      scanf("%d",&quan1);
      if(quan1==0)
        continue;
      add(&(t[l].list),no,quan1,t[l].phno);

      gotoxy(34,34);
      printf("Press any Key to Continue or Press 0 to Return:");
      scanf(" %c",&ch1);
      }



continue;
}


}


if(ch=='3')
   {
       int tex=0;
        gotoxy(62,22);
    cout << "TABLE NO";
    gotoxy(78,22);
   cout <<"NAME";
   gotoxy(89,22);
    cout << "PHONE NO";
    gotoxy(60,23);
    cout << "----------------------------------------";
    for(int i = 0;i<3;i++)
    {
        gotoxy(62,i+24);
     cout  << i+1;
    gotoxy(78,i+24);
    if(t[i].list != NULL)
   cout  <<t[i].name;
   else
    cout << "empty";
   gotoxy(89,i+24);
   if(t[i].list != NULL)
    cout << t[i].phno;
    else
    cout << "empty";
    }
    int p;
    gotoxy(65,14);
    printf("Enter Table Number to be Cleared:");
    scanf("%d",&p);
    p--;
    if(t[p].list==NULL)
    {
        gotoxy(70,16);
        printf("Table is Already Empty!!!!");getch();
        continue;
        }
    cleartable(p);

    if(!(front==0&&rear==-1))
    {
        delet();
        tex=1;
        clrscr();
        gotoxy(55,11);
        printf("Allotting Table to Waiting list Customer");
    gotoxy(60,13);
		printf("Name:");
		gotoxy(66,13);
		printf("%s",a.name);
		gotoxy(89,13);
		printf("Phone No.:");
		gotoxy(100,13);
		printf("%s",a.phno);



strcpy(t[p].name,a.name);
strcpy(t[p].phno,a.phno);
gotoxy(55,15);
printf("Table Number:%d has been allotted to this Customer",p+1);
getch();
int no,quan1;
char ch1=' ';
      while(ch1!='0')
      {
          clrscr();
    display_menu();
    gotoxy(34,30);
    printf("Enter Item No.:");
      scanf("%d",&no);//99 to break;
      if(no>=12)
        continue;
     gotoxy(34,32);
      printf("Enter Quantity:");
      scanf("%d",&quan1);
      if(quan1==0)
        continue;
      add(&(t[l].list),no,quan1,t[l].phno);
      gotoxy(34,34);
      printf("Press any Key to Continue or Press 0 to Return:");
  scanf(" %c",&ch1);
      }

    }
    if(p>0&&p<=3&&(tex==0))
        count++;

   }
if(ch=='4')//table left
   {
int z=0;
    gotoxy(66,13);
    printf("Table Empty:");
gotoxy(78,13);
printf("%d    Table Numbers are: ",count);
for(l=0;l<3;l++)
if(t[l].list==NULL)

    {printf("%d ",l+1);
    z=1;

}
if(z==0)
    printf("0");

   getch();

   }
if(ch=='5')//display queue
{
    display();
    getch();
}


}while(1);



    }

};
int main()
{
   paradise p;
   p.m();

return 0;

}
