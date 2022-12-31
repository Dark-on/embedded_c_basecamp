#include <stdio.h>
#include <stdlib.h>


typedef struct node{
	char * title;
	float price;
	unsigned int num_pages;
	char * language;
	float weight;
	unsigned int year;
	struct node * next;
}node_t;


node_t* create_first_node(  char * title,
							float price,
							unsigned int num_pages,
							char * language,
							float weight,
							unsigned int year);

void add_node(  node_t * head,
				char * title,
				float price,
				unsigned int num_pages,
				char * language,
				float weight,
				unsigned int year);

void print_book_info(node_t * head);


int main(void){
	node_t * headHPlist = NULL;
	headHPlist = create_first_node("Harry Potter and the Philosopher's Stone", 8.97,  342, "English", 9.7,   1998);
	add_node(headHPlist, "Harry Potter and the Chamber of Secrets",  4.95,  341, "English", 8.8,   2000);
	add_node(headHPlist, "Harry Potter and the Prisoner of Azkaban", 2.55,  448, "English", 11.2,  2001);
	add_node(headHPlist, "Harry Potter and the Chamber of Secrets",  4.95,  341, "English", 8.8,   2000);
	add_node(headHPlist, "Harry Potter and the Goblet of Fire",      11.99, 752, "English", 17.76, 2002);
	add_node(headHPlist, "Harry Potter and the Half-Blood Prince",   7.65,  672, "English", 35.2,  2004);
	add_node(headHPlist, "Harry Potter and the Deathly Hallows",     5.99,  784, "English", 18.4,  2009);

	print_book_info(headHPlist);
	return 1;
}


void add_node(  node_t * head,
				char * title,
				float price,
				unsigned int num_pages,
				char * language,
				float weight,
				unsigned int year)
{
	/*add an item to the end of the list*/
    node_t * current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    /*Add new variable*/
    current->next = (node_t *) malloc(sizeof(node_t));
    current->next->title = title;
    current->next->price = price;
    current->next->num_pages = num_pages;
    current->next->language = language;
    current->next->weight = weight;
    current->next->year = year;
    current->next->next = NULL;
}


node_t* create_first_node(  char * title,
							float price,
							unsigned int num_pages,
							char * language,
							float weight,
							unsigned int year){
	node_t * head = NULL;
	head = (node_t *) malloc(sizeof(node_t));
    head->title = title;
    head->price = price;
    head->num_pages = num_pages;
    head->language = language;
    head->weight = weight;
    head->year = year;
    head->next = NULL;
	return head;
}


void print_book_info(node_t * head) {
    node_t * current = head;
    unsigned int node_id = 1;
    while (current != NULL) {
    	printf("Book %u=====================\n", node_id++);
    	printf("Title: %s\n",  current->title);
    	printf("Price: $%.2f\n", current->price);
    	printf("Number of pages: %u\n", current->num_pages);
    	printf("Language: %s\n", current->language);
    	printf("Weight: %.2f ounces\n", current->weight);
    	printf("Year: %u\n\n", current->year);
        current = current->next;
    }
}


