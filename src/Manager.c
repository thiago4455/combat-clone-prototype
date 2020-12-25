#include "Manager.h"
#include "Utils.h"
#include "Game.h"

ALLEGRO_DISPLAY *display;
ALLEGRO_EVENT_QUEUE *queue;
ALLEGRO_TIMER *timer;

void M_Init(){
    al_init();
    al_init_image_addon();
    al_install_keyboard();

    display = al_create_display(WINDOW_WIDTH, WINDOW_HEIGHT);
    queue = al_create_event_queue();
    timer = al_create_timer(1.0/FPS);

    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_keyboard_event_source());

    al_clear_to_color(al_map_hex(BACKGROUND_COLOR));
    al_flip_display();
}

void M_Run(){
    bool shouldClose = false;
    bool render = true;
    al_start_timer(timer);

    G_Start();

    while(!shouldClose){
        ALLEGRO_EVENT event;
        al_wait_for_event(queue, &event);
        switch (event.type)
        {
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            shouldClose = true;
            break;

        case ALLEGRO_EVENT_KEY_DOWN:
            G_ProcessInput(event.keyboard.keycode, 0);
            break;
        case ALLEGRO_EVENT_KEY_UP:
            G_ProcessInput(event.keyboard.keycode, 1);
            break;

        case ALLEGRO_EVENT_TIMER:
            if(G_Update() == 0){
                al_clear_to_color(al_map_hex(BACKGROUND_COLOR));
                G_Render();
                al_flip_display();
            }
        
        default:
            break;
        }
    }
}

void M_Cleanup(){
    al_destroy_display(display);
    al_destroy_event_queue(queue);
}