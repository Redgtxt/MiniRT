#include "../../includes/miniRT.h"

bool linked_list_to_light_array(t_light **light_list, int size_array)
{
    t_light *array;
    t_light *current;
    int i;

    array = ft_calloc(size_array, sizeof(t_plane));
    if (!array)
        return (false);

    current = *light_list;
    i = 0;
    while (current)
    {
        ft_memcpy(&array[i], current, sizeof(t_light));
        array[i].next = NULL;
        array[i].prev = NULL;
        current = current->next;
        i++;
    }
    free_light(*light_list);
    *light_list = array;
    return (true);
}

bool linked_list_to_sphere_array(t_sphere **sphere_list, int size_array)
{
    t_sphere *array;
    t_sphere *current;
    int i;

    array = ft_calloc(size_array, sizeof(t_sphere));
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

    array = ft_calloc(size_array, sizeof(t_plane));
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

bool linked_list_to_cylinder_array(t_cylinder **cylinder_list, int size_array)
{
    t_cylinder *array;
    t_cylinder *current;
    int i;

    array = ft_calloc(size_array, sizeof(t_cylinder));
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

bool linked_list_to_cone_array(t_cone **cone_list, int size_array)
{
    t_cone *array;
    t_cone *current;
    int i;

    array = ft_calloc(size_array, sizeof(t_cone));
    if (!array)
        return (false);

    current = *cone_list;
    i = 0;
    while (current)
    {
        ft_memcpy(&array[i], current, sizeof(t_cone));
        array[i].next = NULL;
        array[i].prev = NULL;
        array[i].radius = array[i].d / 2;
        current = current->next;
        i++;
    }
    free_cone(*cone_list);
    *cone_list = array;
    return (true);
}
