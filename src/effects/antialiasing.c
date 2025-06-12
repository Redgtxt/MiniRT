#include "../../includes/miniRT.h"

void sample_square(double out[3])
{
    out[0] = random_double_0_to_1() - 0.5;
    out[1] = random_double_0_to_1() - 0.5;
    out[2] = 0.0;
}

void setup_antialiasing(t_control_panel *control_panel)
{
	static bool first_time = true;

	  if(control_panel->camera.antialiasing)
        {
            control_panel->camera.samples_per_pixel = 100;
			printf("\n" HMAG "Antialiasing: APPLYING" reset "\n" );
        }
        else
        {
			if(!first_time)
				printf("\n" HMAG "Antialiasing: REMOVING" reset "\n" );
			else
				first_time = false;	
            control_panel->camera.samples_per_pixel = 1;
        }
        
        // Recalcular a escala de amostras
        control_panel->camera.pixel_samples_scale = 1.0 / control_panel->camera.samples_per_pixel;
}
