#include "../includes/miniRT.h"

/*

    Vou passar a linked list que tenho para array
*/

t_sphere *linked_list_to_sphere_array(t_sphere *sphere_list, int size_array)
{
    t_sphere *array;
    t_sphere *current;
    int i;

    array = calloc(sizeof(t_sphere),size_array);
    if(!array)
        return NULL;
    
    current = sphere_list;
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
    return array;
}
t_scene_objects *init_scene_objects(t_control_panel *panel)
{
    t_scene_objects *scene;
    
    scene = malloc(sizeof(t_scene_objects));
    if (!scene)
        return NULL;
    
    
    scene->spheres = NULL;
    scene->sphere_count = 0;
    
    // Converte listas ligadas para arrays
    scene->spheres = linked_list_to_sphere_array(panel->sphere, &scene->sphere_count);
    
    
    return scene;
}

void free_scene_objects(t_scene_objects *scene)
{
    if (scene) {
        free(scene->spheres);
        free(scene);
    }
}
