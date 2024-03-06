#ifndef IMAGE_H
#define IMAGE_H

#include "model/inc/atom.h"
#include "model/inc/sphere.h"
#include "model/inc/camera.h"
#include "model/inc/status.h"
#include "Meta/settings.h"

#include "model/instruction/moving.h"
#include "model/instruction/rotating.h"
#include "model/instruction/scaling.h"
#include "model/instruction/model_data.h"
#include "model/instruction/drawing.h"
#include "model/inc/connection.h"

typedef struct
{
    sphere_struct tmp_sphere;
    sphere_struct global_sphere;
    camera_struct camera;
    Settings settings;

    AtomArr atoms;
    ConnectionArr connect;

    SpaceCoords center;
    bool initialized;
} image_data;


status move_image(image_data &image, const moving& params);
status rotate_image(image_data &image, const rotating& params);
status zoom_camera(image_data &image, const scaling& params);
status create_image(image_data &image, const model_data& model);
status draw_image(image_data &image, drawing& params);

image_data image_init();
status apply_settings(image_data &image, const Settings& settings);
void image_free(image_data &image);

#endif // IMAGE_H
