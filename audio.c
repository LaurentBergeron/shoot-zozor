#include <stdlib.h>
#include <stdio.h>
#include <fmodex/fmod.h>
#include "struct.h"
#include "audio.h"

int initAudio(SHOOT_Audio *audio)
{
    audio->son = 1;

        //Crée un système nommé system.
    audio->result = FMOD_System_Create(&audio->system);  //Adresse de audio->system.
    if (testResult(audio->result) < 0)
        return -1;

        //Initialise le système system.
    audio->result = FMOD_System_Init(audio->system, 4, FMOD_INIT_NORMAL, NULL);
    if (testResult(audio->result) < 0)
        return -1;

        // Crée un pointeur vers le canal 0. Utile FMOD_Channel_GetSpectrum.
    audio->result = FMOD_System_GetChannel(audio->system, 1, &audio->channel_menu);
    if (testResult(audio->result) < 0)
        return -1;

    audio->result = FMOD_System_CreateSound(audio->system, "data\\audio\\gun_Menu.wav", FMOD_CREATESAMPLE, NULL, &audio->gunShoot);
    if (testResult(audio->result) < 0)
        return -1;

    audio->result = FMOD_System_CreateSound(audio->system, "data\\audio\\menu.wav", FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM | FMOD_LOOP_NORMAL, 0, &audio->music);
    if (testResult(audio->result) < 0)
        return -1;
    audio->result = FMOD_Sound_SetLoopCount(music, -1);
    if (testResult(audio->result) < 0)
        return -1;

    fprintf(stdout, "Initialisation audio réussie.\n");
    return 0;
}

int quitAudio(SHOOT_Audio *audio)
{
    FMOD_Sound_Release(audio->music);
    FMOD_Sound_Release(audio->gunShoot);
    FMOD_System_Close(audio->system);
    FMOD_System_Release(audio->system);
    return 0;
}

int testResult(FMOD_RESULT result)
{
    if (result == FMOD_OK)
        return 0;
    else
    {
        fprintf(stderr, "Erreur de FMOD: ");
        switch(result)
        {
            default:
                fprintf(stderr, "Manque de détails.");
                break;
            case FMOD_ERR_INITIALIZATION:
                fprintf(stderr, "FMOD s'est mal initialisé. FMOD_ERR_INITIALIZATION");
                break;
            case FMOD_ERR_INITIALIZED:
                fprintf(stderr, "Impossible d'utiliser cette fonction après l'initialisation. FMOD_ERR_INITIALIZED");
                break;
            case FMOD_ERR_FILE_BAD:
                fprintf(stderr, "Erreur lors de l'ouverture du fichier. FMOD_ERR_FILE_BAD");
                break;
            case FMOD_ERR_FILE_NOTFOUND:
                fprintf(stderr, "Fichier introuvable. FMOD_ERR_FILE_NOTFOUND");
                break;
            case FMOD_ERR_FORMAT:
                fprintf(stderr, "Format de fichier incompatible. FMOD_ERR_FORMAT");
                break;
            case FMOD_ERR_FILE_UNWANTED:
                fprintf(stderr, "Accès à un fichier non-désiré. FMOD_ERR_FILE_UNWANTED");
                break;
            case FMOD_ERR_MUSIC_NOTFOUND:
                fprintf(stderr, "L'entité de musique est introuvable. FMOD_ERR_MUSIC_NOTFOUND");
                break;
            case FMOD_ERR_CDDA_NOAUDIO:
                fprintf(stderr, "Le fichier audio est introuvable sur le disque. FMOD_ERR_CDDA_NOAUDIO");
                break;
            case FMOD_ERR_CDDA_INVALID_DEVICE:
                fprintf(stderr, "Le périphérique audio est introuvable. FMOD_ERR_CDDA_INVALID_DEVICE");
                break;
            case FMOD_ERR_CDDA_READ:
                fprintf(stderr, "Une erreur de type CDDA a eu lieu. FMOD_ERR_CDDA_READ");
                break;
            case FMOD_ERR_CHANNEL_ALLOC:
                fprintf(stderr, "Erreur concernant l'allocation d'un canal. FMOD_ERR_CHANNEL_ALLOC");
                break;
            case FMOD_ERR_CHANNEL_STOLEN:
                fprintf(stderr, "FMOD_ERR_CHANNEL_STOLEN");
                break;
            case FMOD_ERR_MEMORY:
                fprintf(stderr, "Pas assez de mémoire/ressources. FMOD_ERR_MEMORY");
                break;
            case FMOD_ERR_MUSIC_UNINITIALIZED:
                fprintf(stderr, "La musique du système n'est pas initialisée. FMOD_ERR_MUSIC_UNINITIALIZED");
                break;
        }
        fprintf(stderr, "\n");
        return -1;
    }
}
