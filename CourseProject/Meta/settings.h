#ifndef SETTINGS_H
#define SETTINGS_H

#include "model/inc/status.h"

typedef enum
{
    not_set = 0,
    flat,
    gouraud,
    mono,
} fill_t;

struct Settings
{
    fill_t fill_type;
    int sphere_faces;
    int cylinder_faces;
};

status change_settings(Settings& options, const Settings& new_options);

#endif // SETTINGS_H
