#ifndef GAME_H
#define GAME_H
#include <allegro5/allegro.h>

static const unsigned int BACKGROUND_COLOR = 0x2A2A2A;

static const int PLAYER_VELOCITY = 10;
static const int PLAYER_ROTATION_VELOCITY = 10;
static const float COOLDOWN = 2.0;
static const unsigned int MAX_POWER = 20;
static const int BULLET_VELOCITY = 20;
static const unsigned int MAX_BULLET_QUANTITY = 5;

struct Player
{
    char TranslationV;
    char RotationV;
    int PosX;
    int PosY;
    int Rotation;
    char WillFire;
    unsigned int Power;
    unsigned int Cooldown;
};

struct Bullet
{
    char Direction;
    int PosX;
    int PosY;
    unsigned int Power;
};

struct PLAYER_CONTROLLERS{
    unsigned char up;
    unsigned char down;
    unsigned char left;
    unsigned char right;
    unsigned char fire;
};

/**
 * Inicializa as variaveis de jogo.
**/
void G_Start();


/**
 * Processa os eventos de input e define as variaveis de intenção do player, para serem utilizadas no próximo frame.
 * 
 * @param key Código da tecla ALLEGRO_KEY_*
 * @param type Tipo de Evento. 0 para KeyDown e 1 para KeyUp
**/
void G_ProcessInput(unsigned char key, char type);

/**
 * Realiza o calculo e atualiza o estado de todas as posições e ações dos players. 
**/
void G_Update();

/**
 * Renderiza os gráficos na tela
**/
void G_Render();

#endif //GAME_H