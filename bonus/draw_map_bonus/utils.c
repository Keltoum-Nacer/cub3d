#include "../../include_files/cub3d_bonus.h"


double    normalize_angle(double alpha)
{
    if (alpha < 0)
        alpha += 2 * PI;
    if (alpha > 2 * PI)
        alpha -= 2* PI;
    return(alpha);
}