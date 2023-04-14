#include<stdio.h>
#include<stdlib.h>

struct node{
    int data;
    struct node *link;
};
int add_at_end(struct node * head, int info){
    struct node* ptr,*temp;
    temp = malloc(sizeof(struct node));
    ptr=head;
    temp->data = info;
    temp->link = NULL;
    while(ptr->link !=NULL){
        ptr=ptr->link;
    }
    ptr->link = temp;
    return 0;
}
struct node* add_beg(struct node* head,int data){
    struct node*ptr=malloc(sizeof(struct node));
    ptr->data = data;
    ptr->link = NULL;
    ptr->link = head;
    head=ptr;
    return head;
}

void add_at_pos(struct node* head,int data,int pos){
    struct node* ptr=head;
    struct node * ptr2=malloc(sizeof(struct node));
    ptr2->data = data;
    ptr2->link = NULL;

    pos--;
    while(pos!=1){
        ptr=ptr->link;
        pos--;
    }
    ptr2->link = ptr->link;
    ptr->link = ptr2;
}

void del_pos(struct node**head,int position){
    struct node*current= *head;
    struct node*previous= *head;
    if(*head==NULL)
        printf("Linked list is empty");
    else if(position == 1){
        *head=current->link;
        free(current);
        current=NULL;
    }else{
        while(position!=1){
            previous=current;
            current=current->link;
            position--;
        }previous->link=current->link;
        free(current);
        current=NULL;
    }
}

void del_last(struct node*head){
    if(head==NULL)
        printf("linked list is empty");
    else if(head->link==NULL){
        free(head);
        head=NULL;
    }else{
        struct node*temp=head;
        while(temp->link->link!=NULL){
            temp=temp->link;
        }
        free(temp->link);
        temp->link=NULL;
    }
}

struct node* del_first(struct node* head){
    if(head==NULL){
        printf("list is empty");
    }else{struct node* temp=head;
    temp=temp->link;
    free(head);
    head=temp;
    temp=NULL;}
    return head;
}

struct node* del_list(struct node * head){
    struct node*temp=head;
    while(temp !=NULL){
        temp=temp->link;
        free(head);
        head=temp;
    }return head;

}

int create_list(){
    int no_of_data=3,first_data;
    printf("\nNo of data You want to insert?:\n");
    scanf("%d",&no_of_data);
    printf("Enter first data you want to insert:");
    scanf("%d",&first_data);
    struct node *head=malloc(sizeof(struct node));
    head->data=first_data;
    head->link=NULL;
    for (int i=1; i<no_of_data; i++){
        int data;
        printf("enter next data you want to insert:");
        scanf("%d",&data);
        add_at_end(head,data);
    }
    printf("\nLinked list created successfully\n");
    struct node *ptr = NULL;
    ptr=head;
    while(ptr!=NULL){
        printf("%d ",ptr->data);
        ptr=ptr->link;
    }
    return 0;

}
 
int insert_list(){
    printf("....First we create a linked list then we start insertion....\n");
    int no_of_data,first_data;
    printf("\nNo of data You want to insert?:");
    scanf("%d",&no_of_data);
    printf("\nEnter first data you want to insert:");
    scanf("%d",&first_data);
    struct node *head=malloc(sizeof(struct node));
    head->data=first_data;
    head->link=NULL;
    for (int i=1; i<no_of_data; i++){
        int data;
        printf("enter next data you want to insert:");
        scanf("%d",&data);
        add_at_end(head,data);
    }
    printf("\nlinked list created successfully\n");
    int insert_operation;
    printf("where u want to insert 1-Begin/2-End/3-At certain position:");
    scanf("%d",&insert_operation);
    switch(insert_operation){
        case 1: 
                printf("enter data:");
                int data;
                scanf("%d",&data);
                printf("\nbefore insertion our Linked List is:\n"); 
                struct node *ptr;
                ptr=head;
                while(ptr!=NULL){
                    printf("%d ",ptr->data);
                    ptr=ptr->link;
                }           
                head=add_beg(head,data);
                printf("\nafter insertion our Linked List is:\n");
                ptr=head;
                while(ptr!=NULL){
                    printf("%d ",ptr->data);
                    ptr=ptr->link;
                }  
                break;
        case 2: 
                printf("enter data");
                scanf("%d",&data);
                printf("\nbefore insertion our Linked List was:\n");
               // struct node *ptr;
                ptr=head;
                while(ptr!=NULL){
                    printf("%d ",ptr->data);
                    ptr=ptr->link;
                }  
                add_at_end(head,data);
                printf("\nafter insertion our Linked List is:\n");
                ptr=head;
                while(ptr!=NULL){
                    printf("%d ",ptr->data);
                    ptr=ptr->link;
                } 
                break;
        case 3:
                printf("enter data and position at which data is to inserted:\n");
                int position;
                scanf("%d",&data);
                scanf("%d",&position);
                printf("\nbefore insertion our Linked List was:\n");
               // struct node *ptr;
                ptr=head;
                while(ptr!=NULL){
                    printf("%d ",ptr->data);
                    ptr=ptr->link;
                }  
                add_at_pos(head,data,position);
                printf("\nafter insertion our Linked List is:\n");
                ptr=head;
                while(ptr!=NULL){
                    printf("%d ",ptr->data);
                    ptr=ptr->link;
                } 
    }
    return 0;

}

int delete_list(){
    printf("....First we create a linked list then we start deletion....\n");
    int no_of_data,first_data;
    printf("No of data You want to insert?:");
    scanf("%d",&no_of_data);
    printf("\nEnter first data you want to insert:");
    scanf("%d",&first_data);
    struct node *head=malloc(sizeof(struct node));
    head->data=first_data;
    head->link=NULL;
    for (int i=1; i<no_of_data; i++){
        int data;
        printf("enter next data you want to insert:");
        scanf("%d",&data);
        add_at_end(head,data);
    }
    
    while(1){
    printf("\nlinked list created successfully\n\n");
    printf("Where you want to delete your data from the linked list:\n\n");
    printf("1-Begin/2-End/3-At certain position/4-delete entire linked list:");
    int delete_operation;
    scanf("%d",&delete_operation);
    switch(delete_operation){
        case 1:
                printf("Before deletion\n");
                struct node*ptr;
                ptr=head;
                while(ptr!=NULL){
                    printf("%d ",ptr->data);
                    ptr=ptr->link;
                }
                head=del_first(head);
                printf("\nAfter deletion\n");
                ptr=head;
                while(ptr!=NULL){
                    printf("%d ",ptr->data);
                    ptr=ptr->link;
                }
                break;
        case 2:
                printf("Before deletion\n");
                ptr=head;
                while(ptr!=NULL){
                    printf("%d ",ptr->data);
                    ptr=ptr->link;
                }
                del_last(head);
                printf("\nAfter deletion\n");
                ptr=head;
                while(ptr!=NULL){
                    printf("%d ",ptr->data);
                    ptr=ptr->link;
                }
                break;
        case 3:
                printf("enter the position of particular data you want to delete\n");
                int position;
                scanf("%d",&position);
                printf("Before deletion\n");
                ptr=head;
                while(ptr!=NULL){
                    printf("%d ",ptr->data);
                    ptr=ptr->link;
                }
                del_pos(&head,position);
                printf("\nAfter deletion\n");
                ptr=head;
                while(ptr!=NULL){
                    printf("%d ",ptr->data);
                    ptr=ptr->link;
                }
                break;
        case 4:
                printf("Executing complete deletion\n");
                head=del_list(head);
                if(head!=NULL){
                    printf("\nLinked list deleted successfully");
                }
                break;
    }
    int choice;
    printf("\nEnter 1-again/0-exit:");
    scanf("%d",&choice);
    if (choice==0)
        break;
    }
    
}
int traversal_list(){
    printf("....First we create a linked list then we star Traversing....\n");
    int no_of_data,first_data;
    printf("No of data You want to insert?:");
    scanf("%d",&no_of_data);
    printf("\nEnter first data you want to insert:");
    scanf("%d",&first_data);
    struct node *head=malloc(sizeof(struct node));
    head->data=first_data;
    head->link=NULL;
    for (int i=1; i<no_of_data; i++){
        int data;
        printf("enter next data you want to insert:");
        scanf("%d",&data);
        add_at_end(head,data);
    }
    printf("\nlinked list created successfully\n");
    struct node* ptr=head;
    while(ptr!=NULL){
        printf("%d ",ptr->data);
        ptr=ptr->link;
    }
    return 0;

}

int main(){
    int operation;
    printf(" Enter 1-Creation/2-insertion/3-deletion/4-traversal of linked list:");
    scanf("%d",&operation);
    switch(operation){
        case 1: create_list(); break;
        case 2: insert_list(); break;
        case 3: delete_list(); break;
        case 4: traversal_list(); break;
    }
}