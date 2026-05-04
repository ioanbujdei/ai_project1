#include <stdio.h>
#include <string.h>
#include <glib.h>

typedef struct{
    char* name;
    int cost;
}node;

typedef struct{
    char* source;
    char* destination;
    int cost;
}connection;

node* new_node(const char *name, int cost){
    node* n = malloc(sizeof(node));
    n->name = name;
    n->cost = cost;
    return n;
}

connection* new_connection(const char *source, const char *destinaton, int cost){
    connection* c = malloc(sizeof(connection));
    c->source = source;
    c->destination = destinaton;
    c->cost = cost;
    return c;
}



int main(void){
    //create connections
    GPtrArray* connections = g_ptr_array_new();
    connection* tmp_connection = NULL;

    //arad
    tmp_connection = new_connection("Arad", "Zerind", 75);
    g_ptr_array_add(connections, tmp_connection);
    tmp_connection = new_connection("Arad", "Sibiu", 140);
    g_ptr_array_add(connections, tmp_connection);
    tmp_connection = new_connection("Arad", "Timisoara", 100);
    g_ptr_array_add(connections, tmp_connection);

    //zerind
    tmp_connection = new_connection("Zerind", "Arad", 75);
    g_ptr_array_add(connections, tmp_connection);
    tmp_connection = new_connection("Zerind", "Oradea", 71);
    g_ptr_array_add(connections, tmp_connection);
    tmp_connection = new_connection("Arad", "Timisoara", 100);
    g_ptr_array_add(connections, tmp_connection);


    //frontier
    GQueue* frontier = g_queue_new();

    //explored
    GHashTable* explored = g_hash_table_new(g_str_hash, g_str_equal);

    //initial state
    node* current_node = new_node("Arad", 0);

    //uniform cost search
    //g_queue_insert_sorted(frontier, );






    

    

    return 0;
}