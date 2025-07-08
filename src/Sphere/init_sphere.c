#include "../../includes/miniRT.h"

/*

    Vou passar a linked list que tenho para array
*/

bool linked_list_to_sphere_array(t_sphere **sphere_list, int size_array)
{
    t_sphere *array;
    t_sphere *current;
    int i;

    array = ft_calloc(sizeof(t_sphere), size_array);
    if (!array)
        return (false);

    current = *sphere_list;
    i = 0;
    while (current)
    {
        ft_memcpy(&array[i], current, sizeof(t_sphere));
        array[i].next = NULL;
        array[i].prev = NULL;
        array[i].radius = array[i].d / 2;
        current = current->next;
        i++;
    }
    free_sphere(*sphere_list);
    *sphere_list = array;
    return (true);
}

bool linked_list_to_plane_array(t_plane **plane_list, int size_array)
{
    t_plane *array;
    t_plane *current;
    int i;

    array = ft_calloc(sizeof(t_plane), size_array);
    if (!array)
        return (false);

    current = *plane_list;
    i = 0;
    while (current)
    {
        ft_memcpy(&array[i], current, sizeof(t_plane));
        array[i].next = NULL;
        array[i].prev = NULL;
        current = current->next;
        i++;
    }
    free_plane(*plane_list);
    *plane_list = array;
    return (true);
}

bool linked_list_to_cylinder(t_cylinder **cylinder_list, int size_array)
{
    t_cylinder *array;
    t_cylinder *current;
    int i;

    array = ft_calloc(sizeof(t_cylinder), size_array);
    if (!array)
        return false;

    current = *cylinder_list;
    i = 0;
    while (current)
    {
        ft_memcpy(&array[i], current, sizeof(t_cylinder));
        array[i].next = NULL;
        array[i].prev = NULL;
        array[i].radius = array[i].d / 2;
        current = current->next;
        i++;
    }
    free_cylinder(*cylinder_list);
    *cylinder_list = array;
    return true;
}
