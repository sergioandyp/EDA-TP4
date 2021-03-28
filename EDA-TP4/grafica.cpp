#include "grafica.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <iostream>

/***************************************************************************
*                      Definiciones de constantes
***************************************************************************/
#define DISPLAYHEIGHT   696
#define DISPLAYWIDTH    1920
#define FPS_ALLEGRO		50
#define CANT_WALK_IMG	15
#define CANT_JUMP_IMG	10
#define CANT_WORMS      2
/**************************************************************************/

using namespace std;
/***************************************************************************
*                      Variables locales
***************************************************************************/
static ALLEGRO_BITMAP* walkingImg[CANT_WALK_IMG];
static ALLEGRO_BITMAP* jumpingImg[CANT_JUMP_IMG];
static ALLEGRO_BITMAP* mapImg;
static ALLEGRO_BITMAP* backgroundImg;
static ALLEGRO_DISPLAY* display;
static ALLEGRO_TIMER* timer; 
static ALLEGRO_EVENT_QUEUE* allegroQueue;
/**************************************************************************/

/***************************************************************************
*                      Prototipos funciones locales
***************************************************************************/
bool loadJumpImages(Worm worms[]);
bool loadWalkImages(Worm worms[]);
bool loadBackground();
/**************************************************************************/

bool initAllegro(void)
{
    // Inicializamos Allegro
    if (!al_init())     
    {
        cout << "failed to initialize allegro!\n" << endl;
        return ERROR;
    }

    // Inicializamos el addon de imagenes
    if (!al_init_image_addon())
    {
        cout << "failed to initialize images addon!\n" << endl;
        return ERROR;
    }
    // Inicializamos el teclado
    if (!al_install_keyboard())
    {
        cout << "failed to initialize keyboard!\n" << endl;
        return ERROR;
    }

    // Creamos un display
    display = al_create_display(DISPLAYWIDTH, DISPLAYHEIGHT);
    
    // Creamos e inicializamos el timer para dibujar.
    timer = al_create_timer(1.0/FPS_ALLEGRO);
    al_start_timer(timer);

    // Creamos la eventqueue.
    allegroQueue = al_create_event_queue();

    // Agregamos a la eventqueue los eventos del teclado, displa y timer.
    al_register_event_source(allegroQueue, al_get_keyboard_event_source());
    al_register_event_source(allegroQueue, al_get_display_event_source(display));
    al_register_event_source(allegroQueue, al_get_timer_event_source(timer));

    return OK;
}

void shutdownAllegro(void) {

    // Destruimos las variables de Allegro.
    al_destroy_display(display);
    al_destroy_event_queue(allegroQueue);
    al_destroy_timer(timer);
    al_destroy_bitmap(backgroundImg);
    al_destroy_bitmap(mapImg);

    // Destruimos los addons
    al_shutdown_image_addon();
    al_uninstall_keyboard();
    al_uninstall_mouse();
}

bool loadImages(Worm worms[])
{
    if (loadBackground())
    {
        return ERROR;
    }

    if (loadJumpImages(worms))
    {
        
        return  ERROR;
    }
    if (loadWalkImages(worms))
    {
        return  ERROR;
    }

    return OK;
}

void redraw(Worm worms[])
{
    // Dibujamos el fondo y el mapa.
    al_draw_bitmap(backgroundImg, 0.0, 0.0, 0);
    al_draw_bitmap(mapImg, 0.0, 0.0, 0);

    ALLEGRO_BITMAP* imagen;

    //Dibujamos cada worm en su posicion apropiada y la imagen apropiada.
    for (int i = 0; i < CANT_WORMS; i++)
    {
        imagen = (ALLEGRO_BITMAP*)worms[i].getImage(sizeof(ALLEGRO_BITMAP*));
        
        if (worms[i].getDirection() == LEFT)
            // Si el worm se mueve hacia la izquierda lo mostramos normal.
            al_draw_bitmap(imagen, (float) worms[i].getX(), (float)worms[i].getY(), 0);

        else if (worms[i].getDirection() == RIGHT)
            // Si el worm se mueve hacia la derecha lo mostramos espejada.
            al_draw_bitmap(imagen, (float)worms[i].getX(), (float)worms[i].getY(), ALLEGRO_FLIP_HORIZONTAL);
    }
    al_flip_display();
    al_rest(20);     
}

bool loadWalkImages(Worm worms[])
{
    char ruta[30];      // Declaramos una variable auxiliar para cargar rutas  

    // Para cada frame, cargamos la imagen en un arreglo y 
    //verificamos que la carga sea exitosa.
    for (int i = 0; i < CANT_WALK_IMG; i++)
    {
        sprintf_s(ruta, "./wwalking/wwalk-F%d.png", (i+1));
        walkingImg[i] = al_load_bitmap(ruta);

        if (walkingImg[i] == NULL)
        {
            cout << "couldn't load" << ruta << endl;
            return ERROR;
        }
    }

    // Guardamos un puntero al arreglo de imagenes dentro
    //del worm y verificamos que no haya errores.
    for (int i = 0; i < CANT_WORMS; i++)
    {
        if (worms[i].setWalkImages(walkingImg))
        {
            return ERROR;
        }
    }

    // Si no hubo error, retorno que el proceso fue exitoso.
    return OK;

}

bool loadJumpImages(Worm worms[])
{
    char ruta[30];      // Declaramos una variable auxiliar para cargar rutas
        
    // Para cada frame, cargamos la imagen en un arreglo y 
    //verificamos que la carga sea exitosa.
    for (int i = 0; i < CANT_JUMP_IMG; i++)
    {
        sprintf_s(ruta, "./wjump/wjump-F%d.png", (i + 1));
        jumpingImg[i] = al_load_bitmap(ruta);

        if (jumpingImg[i] == NULL)
        {
            // Si la carga falla, cargamos 1=TRUE en error.
            cout << "couldn't load" << ruta << endl;
            return ERROR;
        }
    }

    // Guardamos un puntero al arreglo de imagenes dentro
    //del worm y verificamos que no haya errores.
    for (int i = 0; i < CANT_WORMS; i++)
    {
        if (worms[i].setJumpImages(jumpingImg))
        {
            return ERROR;
        }
    }

    return OK;
}

bool loadBackground()
{
    // Cargamos el fondo en una variable local del archivo.
    backgroundImg = al_load_bitmap("Background.jpg");

    // Cargamos el mapa en otra variable local del archivo.
    mapImg = al_load_bitmap("Scenario.png");

    // Si alguna de las cargas no resultó existosa
    //retornamos error.
    if (backgroundImg == NULL || mapImg == NULL)
    {
        return ERROR;
    }

    // Si no hubo error, retorno que el proceso fue exitoso.
    return OK;
}

EVENT getEvent()
{
    ALLEGRO_EVENT evento;
    
    // Si no hay un evento nuevo, retorno EMPTY
    if (!al_get_next_event(allegroQueue, &evento))
        return EMPTY;

    // Dependiendo el tipo de evento retorno cosas distintas
    switch (evento.type)
    {

    // Si apretaron la X del display, retorno que se desea salir.
    case ALLEGRO_EVENT_DISPLAY_CLOSE:
        return QUIT;
        
    // Si me llegra una señal del timer, lo retorno.
    case ALLEGRO_EVENT_TIMER:
        return  TICK;

    // Si se apretó alguna tecla del teclado, aviso què tecla se apretó.
    case ALLEGRO_EVENT_KEY_DOWN:
        switch (evento.keyboard.keycode)
        {
        case ALLEGRO_KEY_A:
            return DOWN_KEY_A;

        case ALLEGRO_KEY_W:
            return DOWN_KEY_W;

        case ALLEGRO_KEY_D:
            return DOWN_KEY_D;

        case ALLEGRO_KEY_UP:
            return DOWN_KEY_UP;

        case ALLEGRO_KEY_LEFT:
            return DOWN_KEY_LEFT;

        case ALLEGRO_KEY_RIGHT:
            return DOWN_KEY_RIGHT;

        case ALLEGRO_KEY_ESCAPE:
        case ALLEGRO_KEY_Q:
            return QUIT;

        //Si la tecla no está entre las admisibles, 
        // retorno que no se apretó nada.
        default:
            return EMPTY;
        }
        break;
    
    // Si se soltó alguna tecla del teclado, aviso què tecla se soltó.
    case ALLEGRO_EVENT_KEY_UP:
        switch (evento.keyboard.keycode)
        {
        case ALLEGRO_KEY_A:
            return UP_KEY_A;

        case ALLEGRO_KEY_W:
            return UP_KEY_W;

        case ALLEGRO_KEY_D:
            return UP_KEY_D;

        case ALLEGRO_KEY_UP:
            return UP_KEY_UP;

        case ALLEGRO_KEY_LEFT:
            return UP_KEY_LEFT;

        case ALLEGRO_KEY_RIGHT:
            return UP_KEY_RIGHT;

        //Si la tecla no está entre las admisibles, 
        // retorno que no se apretó nada.
        default:
            return EMPTY;
        }
        break;
    
    //Si el evento no está entre los admisibles, 
    // retorno que no hay nuevo evento.
    default:
        return EMPTY;
    }

   
}