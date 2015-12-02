#include "prototypes.h"

/* Manette */
SDL_Joystick *joystick;
int DPADinUse = 0;


void gestionInputs(Input *input)
{
    /* On prend en compte les inputs */
    if(joystick != NULL)
    {
        /* On vérifie si le joystick est toujours connecté */
        if(SDL_NumJoysticks() > 0) getJoystick(input);

        /* Sinon on retourne au clavier */
        else
        {
            SDL_JoystickClose(joystick);
            joystick = NULL;
        }
    }

    /* S'il n'y a pas de manette on gère le clavier */
    else
    {
        /* On vérifie d'abord si une nouvelle manette a été branchée */
        if(SDL_NumJoysticks() > 0)
        {
            /* Si c'est le cas, on ouvre le joystick, qui sera opérationnel
            au prochain tour de boucle */
            joystick = SDL_JoystickOpen(0);

            if(!joystick) printf("Couldn't open Joystick 0\n");
        }

        /* On gère le clavier */
        getInput(input);
    }

}



void getInput(Input *input)
{
    SDL_Event event;

    /* Keymapping : gère les appuis sur les touches et les enregistre
    dans la structure input */
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            exit(0);
            break;

        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                exit(0);
                break;

            case SDLK_DELETE:
                input->erase = 1;
                break;

            case SDLK_c:
                input->useItem = 1;
                break;

            case SDLK_v:
                input->attack = 1;
                break;

            case SDLK_LEFT:
                if(input->left == 0) input->puched++;
                input->left = 1;
                break;

            case SDLK_RIGHT:
                if(input->right == 0) input->puched++;
                input->right = 1;
                break;

            case SDLK_DOWN:
                if(input->down == 0) input->puched++;
                input->down = 1;
                break;

            case SDLK_UP:
                if(input->up == 0) input->puched++;
                input->up = 1;
                break;

            case SDLK_RETURN:
                input->enter = 1;
                break;

            case SDLK_l:
                changeLevel();

            default:
                break;
            }
            break;

        case SDL_KEYUP:
            switch (event.key.keysym.sym)
            {
            case SDLK_DELETE:
                input->erase = 0;
                break;

            case SDLK_c:
                input->useItem = 0;
                break;

            case SDLK_v:
                input->attack = 0;
                break;

            case SDLK_LEFT:
                if(input->left == 1) input->puched--;
                input->left = 0;
                break;

            case SDLK_RIGHT:
                if(input->right == 1) input->puched--;
                input->right = 0;
                break;

            case SDLK_DOWN:
                if(input->down == 1) input->puched--;
                input->down = 0;
                break;

            case SDLK_UP:
                if(input->up == 1) input->puched--;
                input->up = 0;
                break;

            case SDLK_RETURN:
                input->enter = 0;
                break;

            default:
                break;
            }
            break;
        }
    }

}



void openJoystick(void)
{
    /* On ouvre le joystick */
    joystick = SDL_JoystickOpen(0);

    if(!joystick) printf("Le joystick 0 n'a pas pu être ouvert !\n");

}



void closeJoystick(void)
{
    /* Ferme la prise en charge du joystick */
    if(SDL_JoystickGetAttached(joystick)) SDL_JoystickClose(joystick);
}



void getJoystick(Input *input)
{
    SDL_Event event;

    /*Si on ne touche pas au D-PAD, on le désactive (on teste les 4 boutons du D-PAD) */
    if(SDL_JoystickGetButton(joystick, UP_BUTTON) == 0
            && SDL_JoystickGetButton(joystick, DOWN_BUTTON) == 0
            && SDL_JoystickGetButton(joystick, RIGHT_BUTTON) == 0
            && SDL_JoystickGetButton(joystick, LEFT_BUTTON) == 0)
        DPADinUse = 0;

    /* On passe les events en revue */
    while(SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT) exit(0);
        else if(event.type == SDL_KEYDOWN)
        {
            switch(event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                exit(0);
                break;

            default:
                break;
            }
        }
        else if(event.type == SDL_JOYBUTTONDOWN)
        {
            if(event.jbutton.button == ITEM_BUTTON)
                input->useItem = 1;

            else if(event.jbutton.button == ATTACK_BUTTON)
                input->attack = 1;

            else if(event.jbutton.button == START_BUTTON)
                input->enter = 1;

            else if(event.jbutton.button == QUIT_BUTTON)
                exit(0);

            else if(event.jbutton.button == UP_BUTTON)
            {
                input->up = 1;
                DPADinUse = 1;
            }

            else if(event.jbutton.button == DOWN_BUTTON)
            {
                input->down = 1;
                DPADinUse = 1;
            }

            else if(event.jbutton.button == LEFT_BUTTON)
            {
                input->left = 1;
                DPADinUse = 1;
            }

            else if(event.jbutton.button == RIGHT_BUTTON)
            {
                input->right = 1;
                DPADinUse = 1;
            }
        }
        else if(event.type == SDL_JOYBUTTONUP)
        {
            if(event.jbutton.button == START_BUTTON)
                input->enter = 0;

            else if(event.jbutton.button == ATTACK_BUTTON)
                input->attack = 0;

            else if(event.jbutton.button == ITEM_BUTTON)
                input->useItem = 0;

            else if(event.jbutton.button == UP_BUTTON)
                input->up = 0;

            else if(event.jbutton.button == DOWN_BUTTON)
                input->down = 0;

            else if(event.jbutton.button == LEFT_BUTTON)
                input->left = 0;

            else if(event.jbutton.button == RIGHT_BUTTON)
                input->right = 0;
        }

        /* Gestion du thumbpad, seulement si on n'utilise pas déjà le D-PAD */
        else if(event.type == SDL_JOYAXISMOTION && DPADinUse == 0)
        {
            /* Si le joystick a détecté un mouvement */
            if(event.jaxis.which == 0)
            {
                /* Si le mouvement a eu lieu sur l'axe des X */
                if(event.jaxis.axis == 0)
                {
                    /* Si l'axe des X est neutre ou à l'intérieur de la "dead zone" */
                    if(event.jaxis.value > -DEAD_ZONE && event.jaxis.value < DEAD_ZONE)
                    {
                        input->right = 0;
                        input->left = 0;
                    }
                    /* Sinon, de quel côté va-t-on ? */
                    else
                    {
                        /* Si sa valeur est négative, on va à gauche */
                        if(event.jaxis.value < -DEAD_ZONE)
                        {
                            input->right = 0;
                            input->left = 1;
                        }
                        /* Sinon, on va à droite */
                        else if(event.jaxis.value > DEAD_ZONE)
                        {
                            input->right = 1;
                            input->left = 0;
                        }
                    }
                }
                /* Si le mouvement a eu lieu sur l'axe des Y */
                else if(event.jaxis.axis == 1)
                {
                    /* Si l'axe des Y est neutre ou à l'intérieur de la "dead zone" */
                    if(event.jaxis.value > -DEAD_ZONE && event.jaxis.value < DEAD_ZONE)
                    {
                        input->up = 0;
                        input->down = 0;
                    }
                    /* Sinon, de quel côté va-t-on ? */
                    else
                    {
                        /* Si sa valeur est négative, on va en haut */
                        if(event.jaxis.value < 0)
                        {
                            input->up = 1;
                            input->down = 0;
                        }
                        /* Sinon, on va en bas */
                        else
                        {
                            input->up = 0;
                            input->down = 1;
                        }
                    }
                }
            }
        }
    }
}



void resetInput(Input *input)
{

    /* Réinitialisation des inputs (je l'ai mettrai dans une foncion plus tard ^^) */
    if(input->input1 == INPUT_DOWN && !input->down) input->input1 = NONE;
    if(input->input1 == INPUT_LEFT && !input->left) input->input1 = NONE;
    if(input->input1 == INPUT_RIGHT && !input->right) input->input1 = NONE;
    if(input->input1 == INPUT_UP && !input->up) input->input1 = NONE;

    if(input->puched == 0 || input->puched > 2) input->input1 = input->input2 = NONE;
    else if(input->puched == 1)
    {
        if(input->input2 != NONE)
        {
            if(input->input1 == NONE) input->input1 = input->input2;
            input->input2 = NONE;
        }
    }

}
