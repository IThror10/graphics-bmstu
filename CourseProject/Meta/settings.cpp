#include "Meta/settings.h"

status change_settings(Settings& options, const Settings& new_options)
{
    status result = ok;
    if (new_options.fill_type == not_set)
        result = wrong_fill_type;
    else if (new_options.cylinder_faces < 5 || new_options.cylinder_faces > 100)
        result = wrong_settings;
    else if (new_options.sphere_faces < 3 || new_options.sphere_faces > 100)
        result = wrong_settings;
    else
    {
        options.fill_type = new_options.fill_type;
        options.cylinder_faces = new_options.cylinder_faces;
        options.sphere_faces = new_options.sphere_faces;
    }
    return result;
}
