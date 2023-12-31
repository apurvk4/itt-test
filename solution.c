#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
/**
 * @brief
 *
 * A Given city is divided in the Suburbs,town, corporation where corporation is the smallest unit.
 * Find whether two corporation shares common town ,  Suburbs, City
 * Example:
 * City: Bangalore:
 * Suburbs: Bangalore East, Bangalore West
 * Town: Bangalore East - > A, B, Bangalore West-> C, D
 * Corporations: A-> 56001, 56002 B-> 56003, 56004 , C-> 56005, 56006, d-> 56007, 56008
 * I/P:		 O/P
 * 56001, 56008 -> Bangalore
 * 56001, 56002 -> A, Bangalore East, Bangalore
 * 56008, 56005 -> Bangalore West, Bangalore
 *
 */

typedef struct Input
{
    int corp_code;
    char *city;
    char *suburbs;
    char *town;
    bool is_corp;
    bool is_city;
    bool is_suburb;
    bool is_town;
} Input_t;

typedef struct node
{
    Input_t value;
    struct node *list[10];
    int curr_len;
} node_t;
node_t *tree_root = NULL;
node_t *createNode(Input_t val)
{
    node_t *temp = (node_t *)malloc(sizeof(node_t));
    temp->value = val;
    for (int i = 0; i < 10; i++)
    {
        temp->list[i] = NULL;
    }
    temp->curr_len = 0;
    return temp;
}

Input_t add_suburbs(char *value)
{
    Input_t *temp = (Input_t *)malloc(sizeof(Input_t));
    temp->suburbs = value;
    temp->is_city = false;
    temp->is_corp = false;
    temp->is_suburb = true;
    temp->is_town = false;
    return *temp;
}
Input_t add_town(char *value)
{
    Input_t *temp = (Input_t *)malloc(sizeof(Input_t));
    temp->town = value;
    temp->is_city = false;
    temp->is_corp = false;
    temp->is_suburb = false;
    temp->is_town = true;
    return *temp;
}
Input_t add_corp(int val)
{
    Input_t *temp = (Input_t *)malloc(sizeof(Input_t));
    temp->corp_code = val;
    temp->is_city = false;
    temp->is_corp = true;
    temp->is_suburb = false;
    temp->is_town = false;
    return *temp;
}

typedef struct list_node
{
    node_t data;
    struct list_node *next;
} list_node_t;

typedef struct linked_list
{
    list_node_t *head, *tail;
} linked_list_t;
int list_insert(linked_list_t *list, node_t item)
{

    list_node_t *temp = (list_node_t *)malloc(sizeof(list_node_t));
    temp->data = item;
    temp->next = NULL;
    if (list->tail == NULL)
    {
        list->head = temp;
        list->tail = temp;
        return 0;
    }
    list->tail->next = temp;
    list->tail = temp;

    return 0;
}
int list_remove(linked_list_t *list)
{
    if (list->head == list->tail)
    {
        if (list->head != NULL)
        {
            free(list->head);
        }
        list->head = NULL;
        list->tail = NULL;
        return 0;
    }
    list_node_t *temp = list->head;
    while (temp->next != list->tail)
    {
        temp = temp->next;
    }
    free(list->tail);
    temp->next = NULL;
    list->tail = temp;
    return 0;
}
linked_list_t *ll_a = NULL;
linked_list_t *ll_b = NULL;
bool get_ancestors(node_t *root, int target, linked_list_t *ll)
{
    if (root == NULL)
    {
        return false;
    }
    if (root->value.is_corp && root->value.corp_code == target)
    {
        return true;
    }
    for (int i = 0; i < root->curr_len; i++)
    {
        if (get_ancestors(root->list[i], target, ll))
        {
            list_insert(ll, *root);
            return true;
        }
    }
    return false;
}
void list_display(linked_list_t *list)
{
    list_node_t *current = list->head;
    printf("List : ");
    while (current != NULL)
    {
        // printf("%d,",current->data);
        if (current->data.value.is_city)
        {
            printf("city : %s \t", current->data.value.city);
        }
        if (current->data.value.is_suburb)
        {
            printf("suburban : %s \t", current->data.value.suburbs);
        }
        if (current->data.value.is_town)
        {
            printf("town : %s \t", current->data.value.town);
        }
        if (current->data.value.is_corp)
        {
            printf("corporation : %d \t", current->data.value.corp_code);
        }
        current = current->next;
    }
    printf("\n");
}

int main()
{
    char city[100];
    printf("enter city name : \n");
    scanf("%[^\n]%*c", city);
    Input_t t;
    t.city = city;
    t.is_city = true;
    t.is_corp = false;
    t.is_suburb = false;
    t.is_town = false;
    tree_root = (node_t *)malloc(sizeof(node_t));
    tree_root->value = t;
    int s;
    printf("enter the number of suburbs : ");
    scanf("%d", &s);
    for (int i = 0; i < s && i < 10; i++)
    {
        char *sub = (char *)malloc(100 * sizeof(char));
        printf("enter the name of suburb : \n ");
        scanf("\n");
        scanf("%[^\n]%*c", sub);
        Input_t suburb = add_suburbs(sub);
        node_t *t = createNode(suburb);
        if (tree_root->curr_len < 10)
        {
            tree_root->list[tree_root->curr_len] = t;
            tree_root->curr_len += 1;
        }
    }
    // return 1;
    for (int i = 0; i < tree_root->curr_len; i++)
    {
        // temp->value
        printf("enter number of towns in %s suburb : ", tree_root->list[i]->value.suburbs);
        int n;
        scanf("%d", &n);
        for (int j = 0; j < n; j++)
        {
            char *town = (char *)malloc(100 * sizeof(char));
            printf("enter the name of town : \n");
            scanf("\n");
            scanf("%[^\n]%*c", town);
            Input_t t = add_town(town);
            node_t *tt = createNode(t);
            // list_insert(temp->value.list, *createNode(t));
            tree_root->list[i]->list[j] = tt;
            tree_root->list[i]->curr_len += 1;
        }
        for (int j = 0; j < tree_root->list[i]->curr_len; j++)
        {
            printf("enter number of corporations in %s town : ", tree_root->list[i]->list[j]->value.town);
            int n1;
            scanf("%d", &n1);
            for (int k = 0; k < n1; k++)
            {
                int corp;
                printf("enter the name of corp : \n");
                scanf("\n");
                scanf("%d", &corp);
                Input_t t = add_corp(corp);
                node_t *tt = createNode(t);
                tree_root->list[i]->list[j]->list[k] = tt;
                tree_root->list[i]->list[j]->curr_len += 1;
            }
        }
    }
    int corp_a, corp_b;
    printf("enter first corporation : \n");
    scanf("%d", &corp_a);
    printf("enter second corporation  : \n");
    scanf("%d", &corp_b);
    ll_a = malloc(sizeof(linked_list_t));
    ll_a->head = NULL;
    ll_a->tail = NULL;
    ll_b = malloc(sizeof(linked_list_t));
    ll_b->head = NULL;
    ll_b->tail = NULL;
    get_ancestors(tree_root, corp_a, ll_a);
    get_ancestors(tree_root, corp_b, ll_b);
    printf("%d , %d =>", corp_a, corp_b);
    if (strcmp(ll_a->head->data.value.town, ll_b->head->data.value.town) == 0)
    {
        printf(" %s,", ll_a->head->data.value.town);
    }
    if (strcmp(ll_a->head->next->data.value.suburbs, ll_b->head->next->data.value.suburbs) == 0)
    {
        printf(" %s,", ll_a->head->next->data.value.suburbs);
    }
    printf(" %s\n", tree_root->value.city);
    return 0;
}