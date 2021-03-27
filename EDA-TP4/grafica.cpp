#include "grafica.h"
#include "Worm.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <iostream>

#define DISPLAYHEIGHT   470
#define DISPLAYWIDTH    900
#define FPS_ALLEGRO		50
#define CANT_WALK_IMG	15

#define ERROR   -1
#define OK      0

using namespace std;

static ALLEGRO_DISPLAY* display;
static ALLEGRO_EVENT_QUEUE* allegroQueue;
static ALLEGRO_TIMER* timer;
static ALLEGRO_BITMAP* bitmapBackground; //todo: Revisar. 

// Retorna 1 si hay error, 0 si no lo hay
bool initAllegro(void)
{
    if (!al_init())
    {
        cout << "failed to initialize allegro!\n" << endl;
        return ERROR;
    }

    if (!al_init_image_addon())
    {
        cout << "failed to initialize images addon!\n" << endl;
        return ERROR;
    }

    if (!al_install_keyboard())
    {
        cout << "failed to initialize keyboard!\n" << endl;
        return ERROR;
    }

    display = al_create_display(DISPLAYWIDTH, DISPLAYHEIGHT);
    
    timer = al_create_timer(1.0/FPS_ALLEGRO);

    allegroQueue = al_create_event_queue();
    al_register_event_source(allegroQueue, al_get_keyboard_event_source());
    al_register_event_source(allegroQueue, al_get_display_event_source(display));
    al_register_event_source(allegroQueue, al_get_timer_event_source(timer));

    return OK;
}

void shutdownAllegro(void) {

    al_destroy_display(display);
    al_destroy_event_queue(allegroQueue);
    al_destroy_timer(timer);
    al_destroy_bitmap(bitmapBackground);

    al_shutdown_image_addon();
    al_uninstall_keyboard();
    al_uninstall_mouse();
}

bool loadWalkImages() 
{
    static ALLEGRO_BITMAP* walkingImg[CANT_WALK_IMG];

    char ruta[30];

    for (int i = 0; i < CANT_WALK_IMG; i++)
    {
        sprintf_s(ruta, "/wwalking/wwalk-F%d", (i+1));
        walkingImg[i] = al_load_bitmap(ruta);

        if (walkingImg[i] == NULL)
        {
            // Si la carga falla, cargamos 1=TRUE en error.
            cout << "couldn't load" << ruta << endl;
            return ERROR;
        }
    }
    setWalkImages(walkingImg);
}

bool loadJumpImages()
{
}

void redraw()
{
}
