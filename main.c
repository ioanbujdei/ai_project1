#include <stdio.h>
#include <string.h>
#include <glib.h>

typedef struct{
    char* state;
    int path_cost;
    GPtrArray* path_history;

}node;

typedef struct{
    char* source;
    char* destination;
    int path_cost;
}action;

node* new_node(char *state, int path_cost){
    node* n = malloc(sizeof(node));
    n->state = state;
    n->path_cost = path_cost;
    n->path_history = g_ptr_array_new();
    return n;
}

action* new_action(char *source, char *destinaton, int path_cost){
    action* c = malloc(sizeof(action));
    c->source = source;
    c->destination = destinaton;
    c->path_cost = path_cost;
    return c;
}

gint compare_path_cost(gconstpointer a, gconstpointer b, gpointer user_data){
    const node *node_a = a;
    const node *node_b = b;

    if(node_a->path_cost < node_b->path_cost) return -1;
    if(node_a->path_cost > node_b->path_cost) return 1;
    return 0;  
}


int main(void){
    //create actions
    GPtrArray* actions = g_ptr_array_new();
    action* tmp_action = NULL;

    //arad
    tmp_action = new_action("Arad", "Zerind", 75);
    g_ptr_array_add(actions, tmp_action);
    tmp_action = new_action("Arad", "Sibiu", 140);
    g_ptr_array_add(actions, tmp_action);
    tmp_action = new_action("Arad", "Timisoara", 100);
    g_ptr_array_add(actions, tmp_action);

    //zerind
    tmp_action = new_action("Zerind", "Arad", 75);
    g_ptr_array_add(actions, tmp_action);
    tmp_action = new_action("Zerind", "Oradea", 71);
    g_ptr_array_add(actions, tmp_action);

    //frontier
    GQueue* frontier = g_queue_new();

    //explored
    GHashTable* explored = g_hash_table_new(g_str_hash, g_str_equal);

    //initial state
    node* current_node = new_node("Arad", 0);
    char goal_node_name[] = "Sibiu";

    //uniform cost search
    g_queue_insert_sorted(frontier, current_node, compare_path_cost, NULL);
    while(1){
        if(g_queue_is_empty(frontier)) return -1;
        current_node = g_queue_pop_head(frontier);
        if(strcmp(current_node->state, goal_node_name) == 0) return 0;
        g_hash_table_insert(explored, g_strdup(current_node->state), current_node);
        for(int i = 0; i < actions->len; i++){
            action* tmp_action = g_ptr_array_index(actions, i);
            if(strcmp(tmp_action->source, current_node->state) == 0){
                node* child_node = new_node(tmp_action->destination, current_node->path_cost + tmp_action->path_cost);
                
            }
        }


    }






    

    

    return 0;
}