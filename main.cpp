#include<fstream>
#include<iostream>
#include<iomanip>
#include<string>
#include<cstring>
#include<cstdlib>
using namespace std;
namespace NameRecord
{
	struct friend_node
	{
		char last_name[20];
		char first_name[15];
		char phone_num[12];
		friend_node *next;
		friend_node *prior;
	};
		friend_node *head_ptr;
		friend_node *tail_ptr;
		friend_node *current_ptr;
		char pause;
		class record
		{
			public:
					void userchoice(int choice);
					void insertrecord();
					void insertnode(friend_node *new_tr);
					void insertnodehead(friend_node *new_tr);
					void insertnodeend(friend_node *new_tr);
					void showlist();
					void deleterecord();
					void deletenodehead();
					void deletenodeend();
					void deletenodemiddle();
					int verifydelete();
					void deletenode();
					void deletelist();
					void searchbylastname();
					void savefile();
					void loadfile();
					//void help();
					void modifyrecord();
					void userinput();	
		};	
} 
using namespace NameRecord;
int main()
{
	record myrecord;
	cout<<"Welcome to use the phone book\n";
	 cout<<"Press enter to continue\n";
	cin.get(pause);
	system("cls");
	int choice;
	head_ptr=NULL;
	tail_ptr=NULL;
	myrecord.loadfile();
	do
	{
		 cout<<"1_Add record\n";
		 cout<<"2_Show all records\n";
		 cout<<"3_Search records by last name\n";
		 cout<<"4_Delete Record\n";
		 cout<<"5_Modify record\n";
		 cout<<"6_Help\n";
		 cout<<"7_Quit the program\n";
		 cout<<"Enter your choice:";
		cin>>choice;
		myrecord.userchoice(choice);
	}while(choice!=7);
	return 0;
}
void record::userchoice(int choice)
{
	switch(choice)
	{
		case 1:
			insertrecord();
			break;
		case 2:
			showlist();
			break;
		case 3:
			searchbylastname();
			break;
		case 4:
			deleterecord();
			break;
		case 5:
			modifyrecord();
			break;
	//	case 6:
	//		help();
	//		break;
		case 7:
			savefile();
			if(head_ptr!=NULL)
			deletelist();
			break;
		default:
			 cout<<"invalid choice\n";
			break; 
	}
}
void record::insertrecord()
{
	friend_node *new_ptr;
	new_ptr=new friend_node;
	if(new_ptr!=NULL)
	{
		system("cls");
		cin.ignore(20,'\n');
		 cout<<"name";
		cin.getline(new_ptr->first_name,15);
		 cout<<"surname";
		cin.getline(new_ptr->last_name,20);
		 cout<<"telephone number";
		cin.getline(new_ptr->phone_num,15);
		insertnode(new_ptr);
	}
	else
	 cout<<"Warning: Failed to apply for storage space, cannot create new node.\n";
	system("cls");
}
void record::insertnode(friend_node *new_ptr)
{
	system("cls");
	friend_node *temp_ptr;
	 //Case 1: The doubly linked list is empty 
	if(head_ptr==NULL)
	{
		new_ptr->next=new_ptr;
		new_ptr->prior=new_ptr;
		head_ptr=new_ptr;
		tail_ptr=new_ptr;
	}
	 //The doubly linked list has only one node 
	if(head_ptr->next==head_ptr)
	{
		if(strcmp(new_ptr->last_name,head_ptr->last_name)<0)
		insertnodehead(new_ptr);
		else
		insertnodeend(new_ptr);
		return;
	 } 
	  //Case 3: If there is not only one node in the linked list
	 if(head_ptr->next!=head_ptr)
	 {
	 	current_ptr=head_ptr->next;
	 	while((strcmp(new_ptr->last_name,current_ptr->last_name)>0)&&(current_ptr!=head_ptr))
	 	current_ptr=current_ptr->next;
	 	if(current_ptr==head_ptr)
	 		insertnodeend(new_ptr);
	 	else
	 		{
	 			temp_ptr=current_ptr->prior;
				temp_ptr->next=new_ptr;
				new_ptr->prior=temp_ptr;
				current_ptr->prior=new_ptr;
				new_ptr->next=current_ptr;
			 }
		return;
	  } 
}
void record::insertnodehead(friend_node *new_ptr)
{
	new_ptr->next=head_ptr;
	new_ptr->prior=tail_ptr;
	head_ptr->prior=new_ptr;
	tail_ptr->next=new_ptr;
	head_ptr=new_ptr;
}
void record::insertnodeend(friend_node *new_ptr)
{
	new_ptr->next=head_ptr;
	tail_ptr->prior=new_ptr;
	new_ptr->prior=tail_ptr;
	head_ptr->next=new_ptr;
	tail_ptr=new_ptr;
}
void record::showlist() 
{
	system("cls");
	int n;
	 cout<<"Please enter the number displayed on each screen (not more than 20):\n";
	cin>>n;
	system("cls");
	int i;
	char fullname[36];
	current_ptr=head_ptr;
	do
	{
		i=1;
		cout<<setw(20)<<"Name"<<setw(20)<<"Phone Number\n";
		do
		{
			strcpy(fullname,current_ptr->last_name);
			strcat(fullname,",");
			strcat(fullname,current_ptr->first_name);
			cout<<setw(20)<<fullname<<setw(20)<<current_ptr->phone_num<<endl;
			current_ptr=current_ptr->next;
			i++;
		}while(current_ptr!=head_ptr&&i<=n);
		cin.get(pause);
		if(current_ptr!=head_ptr)
		{
			 cout<<"Please press enter to continue";
			cin.get(pause);
			system("cls");
		}
		else
			 cout<<"End of file!";
	}while(current_ptr!=head_ptr);
	cin.get(pause);
	cin.ignore(1,pause);
	system("cls");
}
void record::searchbylastname()
{
	system("cls");
	int nflag=0;
	char search_string[20];
	current_ptr=head_ptr;
	if(current_ptr==NULL)
	 cout<<"Phone record is empty";
	else
	{
		cin.ignore(20,'\n');
		 cout<<"Enter the last name of the record you want to search";
		cin.getline(search_string,20);
		if(strcmp(current_ptr->last_name,search_string)==0)
		{
			if(nflag==0)
			 cout<<"Found node\n";
			nflag=1;
			cout<<current_ptr->first_name<<' '<<current_ptr->last_name<<"\t\t";
			cout<<current_ptr->phone_num<<endl; 
		}
		current_ptr=current_ptr->next;
		while(current_ptr!=head_ptr)
		{
			if(strcmp(current_ptr->last_name,search_string)==0)
			{
				if(nflag==0)
				 cout<<"Record found\n";
				nflag=1;
				cout<<current_ptr->first_name<<' '<<current_ptr->last_name<<"\t\t";
				cout<<current_ptr->phone_num<<endl;
			}
			current_ptr=current_ptr->next;
		}
		if(nflag==0)
			{
				 cout<<"No record!";
				cin.get(pause);
				system("cls");
			}
	}
}
void record::deleterecord()
{
	system("cls");
	char search_string[20];
	friend_node *previous_ptr;
	previous_ptr=NULL;
	current_ptr=head_ptr;
	if(current_ptr==NULL)
	{
		 cout<<"No records to delete";
		return;
	}
	cin.ignore(20,'\n');
	int nflag=0;
	 cout<<"\nEnter the last name of the node you want to delete";
	cin.getline(search_string,20);
	while((strcmp(current_ptr->last_name,search_string)==0)&&head_ptr!=NULL)
	{
		nflag=1;
		 cout<<"\nFound record\n";
		cout<<current_ptr->first_name<<' '<<current_ptr->last_name<<"\t\t";
		cout<<current_ptr->phone_num<<endl;
		if(verifydelete())
		{
			deletenode();
			 cout<<"\nRecord deleted\n";
		}
		else
		{                        
            cout<<" "<<current_ptr->first_name<<","<<current_ptr->last_name<<"\t"<<current_ptr->phone_num<<" were not deleted\n";
			current_ptr=current_ptr->next;
		}
	 }
	 do{
	 	if(strcmp(current_ptr->last_name,search_string)==0)
	 	{
	 		nflag=1;
	 		 cout<<"\nFound record\n";
	 		cout<<current_ptr->first_name<<' '<<current_ptr->last_name<<"\t\t";
	 		cout<<current_ptr->phone_num<<endl;
	 		if(verifydelete())
	 		{
	 			deletenode();
	 			 cout<<"\nRecord deleted\n";
			 }
			 else
			 {
			 	  cout<<current_ptr->first_name<<','<<current_ptr->last_name<<"\t"<<current_ptr->phone_num<<" were not deleted\n";
			 }
		 }
		 current_ptr=current_ptr->next;
	 } while((current_ptr!=head_ptr||head_ptr==NULL));
	 if(nflag==0)
	  cout<<"\nNo matching records were found or deleted\n";
	 cin.get();
	 system("cls");
}
int record::verifydelete()
{
	char yesno;
	 cout<<"\nConfirm? (y/n)";
	cin>>yesno;
	cin.ignore(20,'\n');
	if((yesno=='Y')||(yesno=='y'))
	return(1);
	else
	return(0);
}
void record::deletenode()
{
	if(current_ptr=head_ptr)
	deletenodehead();
	else
		if(current_ptr->next==head_ptr)
		deletenodeend();
		else
		deletenodemiddle();
}
void record::deletenodehead()
{
	if(head_ptr->next!=head_ptr)
	{
		head_ptr=current_ptr->next;
		tail_ptr->next=head_ptr;
		head_ptr->prior=tail_ptr;
		delete current_ptr;
		current_ptr=head_ptr;
	}
	else
	{
		head_ptr=NULL;
		tail_ptr=NULL;
		delete current_ptr;
	}
}
void record::deletenodeend()
{
	friend_node *previous_ptr=current_ptr->prior;
	delete current_ptr;
	previous_ptr->next=head_ptr;
	head_ptr->prior=previous_ptr;
	tail_ptr=previous_ptr;
	current_ptr=tail_ptr;
}
void record::deletenodemiddle()
{
	friend_node *previous_ptr=current_ptr->prior;
	previous_ptr->next=current_ptr->next;
	current_ptr->next->prior=previous_ptr;
	delete current_ptr;
	current_ptr=previous_ptr;
}
void record::deletelist()
{
	friend_node *temp_ptr;
	current_ptr=head_ptr;
	do
	{
		temp_ptr=current_ptr->next;
		tail_ptr->prior=temp_ptr;
		temp_ptr->prior=tail_ptr;
		delete current_ptr;
		current_ptr=temp_ptr;
	}while(temp_ptr!=NULL&&temp_ptr!=tail_ptr);
	delete current_ptr;
}
void record::savefile()
{
	ofstream outfile;
	outfile.open("FRIENDS.dat",ios::out);
	if(outfile)
	{
		current_ptr=head_ptr;
		if(head_ptr!=NULL)
		{
			do{
				outfile<<current_ptr->last_name<<endl;
				outfile<<current_ptr->first_name<<endl;
				outfile<<current_ptr->phone_num<<endl;
				current_ptr=current_ptr->next;
			}while(current_ptr!=head_ptr);
		}
		 outfile<<"End of file"<<endl;
		outfile.close();
	}
	else
	 cout<<"Error opening file\n";
}
void record::loadfile()
{
	friend_node *new_ptr;
	ifstream infile;
	int end_lop=0;
	if(infile)
	{
		do{
			new_ptr=new friend_node;
			if(new_ptr!=NULL)
			{
				infile.get(new_ptr->last_name,20);
				infile.ignore(20,'\n');
				 if((strcmp(new_ptr->last_name,"")!=0)&&(strcmp(new_ptr->last_name,"End of File")!=0))
				{
					infile.get(new_ptr->first_name,15);
					infile.ignore(20,'\n');
					infile.get(new_ptr->phone_num,15);
					infile.ignore(20,'\n');
					insertnode(new_ptr);
				}
				else
				{
					delete new_ptr;
					end_lop=1;
				}
			}
			else{
				 cout<<"Warning: The file was not successfully imported from disk.\n";
				end_lop=1;
			}
		}while(end_lop==0);
		infile.close();
	}
	else 
	 cout<<"No data file is available, the record table is empty\n";
}
void record::modifyrecord()
{
	system("cls");
	char search_string[20];
	if(head_ptr==NULL)
	{
		 cout<<"No record can be modified\n";
		return;
	}
	int nflag=0;
	current_ptr=head_ptr;
	cin.ignore(20,'\n');
	 cout<<"\nEnter the last name of the record you want to modify";
	cin.getline(search_string,20);
	friend_node *new_ptr;
	while((strcmp(current_ptr->last_name,search_string)==0)&&head_ptr!=NULL)
	{
		new_ptr=new friend_node;
		nflag=1;
		 cout<<"\nFound record\n";
		cout<<current_ptr->first_name<<' '<<current_ptr->last_name<<"\t\t";
		cout<<current_ptr->phone_num<<endl;
		if(verifydelete())
		{
			 cout<<"Please enter the last name of the new record";
			cin.getline(new_ptr->last_name,20);
			 cout<<"Please enter the name of the new record";
			cin.getline(new_ptr->first_name,15);
			 cout<<"Please enter the new recorded phone";
			cin.getline(new_ptr->phone_num,12);
			if(verifydelete())
			{
				deletenode();
				insertnode(new_ptr);
				 cout<<"\nRecord has been modified\n";
				cout<<new_ptr->first_name<<' ';
				cout<<new_ptr->last_name<<endl;
				cout<<new_ptr->phone_num<<endl;
				current_ptr=head_ptr;
			}
		 }
		 else
		 {
		 	 cout<<current_ptr->first_name<<","<<current_ptr->last_name<<"\t"<<current_ptr->phone_num<<" record has not been modified\n";
		 	current_ptr=current_ptr->next;
		 	delete new_ptr;
		  } 
	}
	do{
		if(strcmp(current_ptr->last_name,search_string)==0)
		{
			nflag=1;
			new_ptr=new friend_node;
			 cout<<"\nFound record\n";
			cout<<current_ptr->first_name<<' '<<current_ptr->last_name<<"\t\t";
			cout<<current_ptr->phone_num<<endl;
			if(verifydelete())
			{
				 cout<<"Please enter the last name of the new record";
				cin.getline(new_ptr->last_name,20);
				 cout<<"Please enter the name of the new record";
				cin.getline(new_ptr->first_name,15);
				 cout<<"Please enter the new recorded phone";
				cin.getline(new_ptr->phone_num,12);
				if(verifydelete())
				{
					friend_node *temp_ptr=current_ptr->prior;
					deletenode();
					insertnode(new_ptr);
					current_ptr=temp_ptr;
					 cout<<"\nRecord has been modified\n";
					cout<<new_ptr->first_name<<' ';
					cout<<new_ptr->last_name<<endl;
					cout<<new_ptr->phone_num<<endl;
				}
			}
			else
			{
				 cout<<current_ptr->first_name<<","<<current_ptr->last_name<<"\t"<<current_ptr->phone_num<<" record has not been modified\n";
				delete new_ptr;
			}
		}
			current_ptr=current_ptr->next;
	}while(current_ptr!=head_ptr||head_ptr==NULL);
	if(nflag==0)
	{
		 cout<<"No matching record found";
		userinput();
	}
	system("cls");
 } 
 void record::userinput()
 {
 	char answer_y_n;
 	  cout<<"Try again? y/n";
 	cin.get(answer_y_n);
 	if(answer_y_n=='y'||answer_y_n=='y')
 		if(answer_y_n=='y')
 		modifyrecord();
 	else
 	{
 		  cout<<"Invalid input";
 		userinput();}
         
     }


