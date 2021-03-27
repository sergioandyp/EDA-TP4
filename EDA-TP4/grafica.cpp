#include "grafica.h"
#include "Worm.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <iostream>

using namespace std;

static ALLEGRO_DISPLAY* display;

// Retorna 1 si hay error, 0 si no lo hay
bool initAllegro(void)
{
    if (!al_init())
    {
        cout << "failed to initialize allegro!\n" << endl;
        return 1;
    }

    if (!al_init_image_addon())
    {
        cout << "failed to initialize images addon!\n" << endl;
        return 1;
    }

    if (!al_install_keyboard())
    {
        cout << "failed to initialize keyboard!\n" << endl;
        return 1;
    }

    display = al_create_display(DISPLAYWIDTH, DISPLAYHEIGHT);

    return 0;
}

void shutdownAllegro(void) {

    al_destroy_display(display);
    al_destroy_event_queue(queue);
    al_destroy_timer(timer);
    al_destroy_bitmap(bitmapBackground);

    al_shutdown_image_addon();
    al_uninstall_keyboard();
    al_uninstall_mouse();
}

void redraw()
{
}
