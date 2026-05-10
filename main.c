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


node* new_node(char *state, int path_cost, GPtrArray* path_history){
    node* n = malloc(sizeof(node));
    n->state = state;
    n->path_cost = path_cost;
    n->path_history = g_ptr_array_copy(path_history, NULL, NULL);
    return n;
}

action* new_action(char *source, char *destinaton, int path_cost){
    action* c = malloc(sizeof(action));
    c->source = source;
    c->destination = destinaton;
    c->path_cost = path_cost;
    return c;
}

gint match_nodes(gconstpointer a, gconstpointer b){
    const node *node_a = a;
    const char *search_name = (char*)b;

    return g_strcmp0(node_a->state, search_name);

}

gint compare_path_cost(gconstpointer a, gconstpointer b, gpointer user_data){
    const node *node_a = a;
    const node *node_b = b;

    if(node_a->path_cost < node_b->path_cost) return -1;
    if(node_a->path_cost > node_b->path_cost) return 1;
    return 0;  
}

GPtrArray* get_actions(node* node, GPtrArray* all_actions, GHashTable* explored){
    GPtrArray* returned_actions = g_ptr_array_new();
    action* tmp_action = NULL;
    for(int i = 0; i < all_actions->len; i++){
        tmp_action = g_ptr_array_index(all_actions, i);
        if(strcmp(tmp_action->source, node->state) == 0){
            if(!(g_hash_table_contains(explored, tmp_action->destination))){
                //printf("Actions = %s %s %d\n", tmp_action->source, tmp_action->destination, tmp_action->path_cost);
                g_ptr_array_add(returned_actions, tmp_action);
            }
        }

    }
    return returned_actions;
}

void print_path_history(GPtrArray* path_history){

    for(int i = 0; i < path_history->len; i++){

        action* tmp_action = g_ptr_array_index(path_history, i);

        if(i==0){
            printf("%s", tmp_action->source);
        }

        printf(" ---%d---> %s", tmp_action->path_cost, tmp_action->destination);

    }

    printf("\n");

}


//for debuggin print frontier
void print_frontier(GQueue* frontier){
    for(GList *l = frontier->head; l != NULL; l = l->next){
        node *n = (node *)l->data;

        printf("Frontier: %s, Cost = %d\n", n->state, n->path_cost);
    }
}

//for debugging print explored
void print_explored(GHashTable* explored){

    GHashTableIter iter;
    gpointer key;

    g_hash_table_iter_init(&iter, explored);

    while(g_hash_table_iter_next(&iter, &key, NULL)){
        printf("Explored: %s\n", (char*)key);
    }

}

int main(void){
    //create actions
    GPtrArray* actions = g_ptr_array_new();
    action* tmp_action = NULL;

    //Sibiu
    tmp_action = new_action("Sibiu", "Fagaras", 99);
    g_ptr_array_add(actions, tmp_action);
    tmp_action = new_action("Sibiu", "Ramnicu Valcea", 80);
    g_ptr_array_add(actions, tmp_action);

    //Fagaras
    tmp_action = new_action("Fagaras", "Sibiu", 99);
    g_ptr_array_add(actions, tmp_action);
    tmp_action = new_action("Fagaras", "Bucharest", 211);
    g_ptr_array_add(actions, tmp_action);

    //Ramnicu Valcea
    tmp_action = new_action("Ramnicu Valcea", "Sibiu", 80);
    g_ptr_array_add(actions, tmp_action);
    tmp_action = new_action("Ramnicu Valcea", "Pitesti", 97);
    g_ptr_array_add(actions, tmp_action);

    //Pitesti
    tmp_action = new_action("Pitesti", "Ramnicu Valcea", 97);
    g_ptr_array_add(actions, tmp_action);
    tmp_action = new_action("Pitesti", "Bucharest", 101);
    g_ptr_array_add(actions, tmp_action);

    //Bucharest
    tmp_action = new_action("Bucharest", "Fagaras", 211);
    g_ptr_array_add(actions, tmp_action);
    tmp_action = new_action("Bucharest", "Pitesti", 101);
    g_ptr_array_add(actions, tmp_action);

    //----------------------
    //initial state
    node* current_node = new_node("Sibiu", 0, g_ptr_array_new());
    char goal_state[] = "Bucharest";

    //frontier
    GQueue* frontier = g_queue_new();

    //explored
    GHashTable* explored = g_hash_table_new(g_str_hash, g_str_equal);

    

    //uniform cost search
    g_queue_insert_sorted(frontier, current_node, compare_path_cost, NULL);
    while(1){
        if(g_queue_is_empty(frontier)){
            printf("FAIL: frontier empty!\n");
            return -1;
        } 
        current_node = g_queue_pop_head(frontier);
        //printf("Current node = %s\n", current_node->state);
        if(strcmp(current_node->state, goal_state) == 0){
            printf("SUCCESS!\n");
            printf("Best path is:\n");
            print_path_history(current_node->path_history);
            printf("Total path cost: %d\n", current_node->path_cost);


            return 0;
        }
        g_hash_table_insert(explored, g_strdup(current_node->state), current_node);
        GPtrArray* current_actions = get_actions(current_node, actions, explored);
        for(int i = 0; i < current_actions->len; i++){
            action* tmp_action = g_ptr_array_index(current_actions, i);
            node* tmp_node = new_node(tmp_action->destination, current_node->path_cost + tmp_action->path_cost, current_node->path_history);
            g_ptr_array_add(tmp_node->path_history, tmp_action);
        

            //printf("child = %s\n", tmp_node->state);
            //print_frontier(frontier);
            //print_explored(explored);
            //printf("not in explored? = %d\n", !(g_hash_table_contains(explored, tmp_node->state)));
            //printf("not in frontier? = %d\n", g_queue_find_custom(frontier, tmp_node->state, match_nodes) == NULL);


            if((!(g_hash_table_contains(explored, tmp_node->state))) && g_queue_find_custom(frontier, tmp_node->state, match_nodes) == NULL){
                g_queue_insert_sorted(frontier, tmp_node, compare_path_cost, NULL);
            }else if(g_queue_find_custom(frontier, tmp_node->state, match_nodes)){
                
                GList *link_to_frontier_node = g_queue_find_custom(frontier, tmp_node->state, match_nodes);
                
                node *my_node = (node *)link_to_frontier_node->data;
                if(tmp_node->path_cost < my_node->path_cost){
                    g_queue_remove(frontier, my_node);
                    g_queue_insert_sorted(frontier, tmp_node, compare_path_cost, NULL);
                }
            }

        }

   



    }






    

    

    return 0;
}