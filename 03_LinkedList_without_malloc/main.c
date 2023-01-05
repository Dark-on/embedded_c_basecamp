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


void add_node(  node_t * head,
				node_t * node,
				char * title,
				float price,
				unsigned int num_pages,
				char * language,
				float weight,
				unsigned int year);


void print_books_info(node_t * head);


int main(void){
	node_t book1, book2, book3, book4, book5, book6, book7;

	/*The head of "Harry Potter" books list*/
	node_t * headHPList = &book1;

	add_node(NULL,       &book1, "Harry Potter and the Philosopher's Stone",  8.97,  342, "English", 9.7,   1998);
	add_node(headHPList, &book2, "Harry Potter and the Chamber of Secrets",   4.95,  341, "English", 8.8,   2000);
	add_node(headHPList, &book3, "Harry Potter and the Prisoner of Azkaban",  2.55,  448, "English", 11.2,  2001);
	add_node(headHPList, &book4, "Harry Potter and the Goblet of Fire",       11.99, 752, "English", 17.76, 2002);
	add_node(headHPList, &book5, "Harry Potter and the Order of the Phoenix", 3.89,  896, "English", 42.4,  2003);
	add_node(headHPList, &book6, "Harry Potter and the Half-Blood Prince",    7.65,  672, "English", 35.2,  2004);
	add_node(headHPList, &book7, "Harry Potter and the Deathly Hallows",      5.99,  784, "English", 18.4,  2009);

	print_books_info(&book1);
	return 1;
}


void add_node(  node_t * head,
				node_t * node,
				char * title,
				float price,
				unsigned int num_pages,
				char * language,
				float weight,
				unsigned int year){
	/* add and fill node (last_node) to the end of list (head) or just fill fist node if head=NULL*/
	if(head != NULL){
		/* if head = NULL it's first node */
		node_t * last_node = head;
		while (last_node->next != NULL) {
			last_node = last_node->next;
		}
		last_node->next = node;
	}
    node->title = title;
    node->price = price;
    node->num_pages = num_pages;
    node->language = language;
    node->weight = weight;
    node->year = year;
    node->next = NULL;

}

void print_books_info(node_t * head) {
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





