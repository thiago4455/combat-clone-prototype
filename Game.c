#include "Game.h"
#include "Manager.h"

unsigned int MAX_COOLDOWN_FRAMES;

static const struct PLAYER_CONTROLLERS C_Player1 = {ALLEGRO_KEY_W, ALLEGRO_KEY_S, ALLEGRO_KEY_A, ALLEGRO_KEY_D, ALLEGRO_KEY_SPACE};
static const struct PLAYER_CONTROLLERS C_Player2 = {ALLEGRO_KEY_UP, ALLEGRO_KEY_DOWN, ALLEGRO_KEY_LEFT, ALLEGRO_KEY_RIGHT, ALLEGRO_KEY_ENTER};

struct Player Player1;
struct Player Player2;

void PlayerInputDown(struct Player *player, struct PLAYER_CONTROLLERS controller, unsigned char key){
    if (key == controller.up)
        player->TranslationV = 1;
    else if(key == controller.down)
        player->TranslationV = -1;
    else if(key == controller.left)
        player->RotationV = 1;
    else if(key == controller.right)
        player->RotationV = -1;
    else if(key == controller.fire)
        player->WillFire = 1;
}

void PlayerInputUp(struct Player *player, struct PLAYER_CONTROLLERS controller, unsigned char key){
    if ((key == controller.up && player->TranslationV == 1) || (key == controller.down && player->TranslationV == -1))
        player->TranslationV = 0;
    else if((key == controller.left && player->RotationV == 1) || (key == controller.right && player->RotationV == -1))
        player->RotationV = 0;
    else if(key == controller.fire)
        player->WillFire = 0;
}

void G_Start(){
    MAX_COOLDOWN_FRAMES = COOLDOWN * FPS;
    Player1 = (struct Player) { 0, 0, 10, WINDOW_HEIGHT/2, 0, 0, 0, MAX_COOLDOWN_FRAMES };
}

void G_ProcessInput(unsigned char key, char type){
    if(!type){
        PlayerInputDown(&Player1, C_Player1, key);
        PlayerInputDown(&Player2, C_Player2, key);
    }
    else{
        PlayerInputUp(&Player1, C_Player1, key);
        PlayerInputUp(&Player2, C_Player2, key);
    }
}

void G_Update(){

}

void G_Render(){

}