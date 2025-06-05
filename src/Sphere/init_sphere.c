#include "../../includes/miniRT.h"

/*

    Vou passar a linked list que tenho para array
*/

bool    linked_list_to_sphere_array(t_sphere **sphere_list, int size_array)
{
    t_sphere *array;
    t_sphere *current;
    int i;

    array = ft_calloc(sizeof(t_sphere),size_array);
    if(!array)
        return (false);
    
    current = *sphere_list;
    i = 0;
    while (current)
    {
        ft_memcpy(&array[i],current,sizeof(t_sphere));
        array[i].next = NULL;
        array[i].prev = NULL;
        array[i].radius = array[i].d / 2;  
        current = current->next;
        i++;
    }
    // free_linked list;
    *sphere_list = array;
    return (true);
}

