#include <stdio.h>
#include <string.h>
#include <glib.h>

typedef struct{
    char* name;
    GPtrArray* roads;
}node;

typedef struct{
    char* name;
    int cost;
}road;

node* node_new(char* name){
    node* n = malloc(sizeof(node));
    n->name = name;
    n->roads = g_ptr_array_new();
    return n;
}

road* road_new(char*name, int cost){
    road* r = malloc(sizeof(road));
    r->name = name;
    r->cost = cost;
    return r;
}

//helper function
node* find_node_by_name(GPtrArray *array, const char *name){
    for(int i = 0; i < array->len; i++){
        node *current_node = g_ptr_array_index(array, i);
        
        if (strcmp(name, current_node->name) == 0){
            return current_node;
        }
    }
    return NULL;
}

gint compare_roads(gconstpointer a, gconstpointer b, gpointer data){
    road *road_a = a;
    road *road_b = b;

    return road_a->cost - road_b->cost;
}

void uniform_cost_search(){

}

int main(void){
    //map
    GPtrArray* nodes = g_ptr_array_new();

    //add Arad
    node* tmp_node = node_new("Arad");
    road* tmp_road = road_new("Zerind", 75);
    g_ptr_array_add(tmp_node->roads, tmp_road);
    tmp_road = road_new("Sibiu", 140);
    g_ptr_array_add(tmp_node->roads, tmp_road);
    tmp_road = road_new("Timisoara", 100);
    g_ptr_array_add(tmp_node->roads, tmp_road);
    g_ptr_array_add(nodes, tmp_node);


    //add Zerind
    node* tmp_node = node_new("Zerind");
    road* tmp_road = road_new("Arad", 75);
    g_ptr_array_add(tmp_node->roads, tmp_road);
    tmp_road = road_new("Oradea", 71);
    g_ptr_array_add(tmp_node->roads, tmp_road);
    g_ptr_array_add(nodes, tmp_node);

/*
    //add Oradea
    tmp_node = node_new("Oradea");
    g_ptr_array_add(tmp_node->keys, "Zerind");
    g_ptr_array_add(tmp_node->values, GINT_TO_POINTER(71));
    g_ptr_array_add(tmp_node->keys, "Sibiu");
    g_ptr_array_add(tmp_node->values, GINT_TO_POINTER(151));
    g_ptr_array_add(nodes, tmp_node);

    //add Sibiu
    tmp_node = node_new("Sibiu");
    g_ptr_array_add(tmp_node->keys, "Arad");
    g_ptr_array_add(tmp_node->values, GINT_TO_POINTER(140));
    g_ptr_array_add(tmp_node->keys, "Oradea");
    g_ptr_array_add(tmp_node->values, GINT_TO_POINTER(151));
    g_ptr_array_add(nodes, tmp_node);
*/
    //frontier
    GQueue* frontier = g_queue_new();

    //explored
    GHashTable* explored = g_hash_table_new(g_str_hash, g_str_equal);

    //initial state
    node* current_node = find_node_by_name(nodes, "Arad");
    int path_cost = 0;

    //uniform cost search
    g_queue_insert_sorted(frontier, )






    

    

    return 0;
}