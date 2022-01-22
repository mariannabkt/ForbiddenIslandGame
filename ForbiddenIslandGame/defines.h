#pragma once
#include <random>
#include <stdlib.h>
#include <chrono>
#include <thread>

using namespace std;

#define WINDOW_WIDTH 1400
#define WINDOW_HEIGHT 800

#define CANVAS_WIDTH 28.0f
#define CANVAS_HEIGHT 16.0f

enum game_state { INIT, MAIN_MENU, HELP, CHOOSE_PLAYER, PLAYING };
enum help_page { ONE, TWO, THREE, FOUR };
enum button_func { PLAY, HOW_TO, EXIT, NEXT, PREV, OK };
enum player_role { DIVER, EXPLORER, PILOT };
enum tile_type { BASIC, FIRE, WATER, AIR, EARTH, LANDING };

#define SETCOLOR(c,r,g,b) { c[0]=r; c[1]=g; c[2]=b; }
#define RAND0TO1() ( rand() / (float)RAND_MAX )

#define DEMO_PLAYER_SIZE 1.8f
#define PLAYER_SIZE 0.8f
#define PLAYER_MOTION_RANGE 2.0f

inline void sleep(int ms)
{
	this_thread::sleep_for(chrono::milliseconds(ms));
}

inline float distance(float x1, float y1, float x2, float y2)
{
	float dx = x1 - x2;
	float dy = y1 - y2;
	return sqrt(dx * dx + dy * dy);
}

#define ASSET_PATH ".\\assets\\"


// BACKGROUNDS
#define MAIN_BACKGROUND ".\\assets\\backgrounds\\main_background.png"
#define CHOOSE_PLAYER_BACKGROUND ".\\assets\\backgrounds\\choose_player_background.png"
#define PLAYING_BACKGROUND ".\\assets\\backgrounds\\playing_background.png"


// BUTTONS
#define PLAY_BUTTON ".\\assets\\buttons\\play button.png"
#define OK_BUTTON ".\\assets\\buttons\\ok button.png"
#define EXIT_BUTTON ".\\assets\\buttons\\exit button.png"
#define NEXT_BUTTON ".\\assets\\buttons\\next button.png"
#define PREV_BUTTON ".\\assets\\buttons\\previous button.png"
#define HOW_TO_PLAY_BUTTON ".\\assets\\buttons\\how to play button.png"


// FONTS
#define SKYTREE_FONT ".\\assets\\fonts\\Skytree.ttf"
#define IMMORTAL_FONT ".\\assets\\fonts\\IMMORTAL.ttf"
#define FREESANS_FONT ".\\assets\\fonts\\FreeSans.ttf"
#define BLKCHCRY_FONT ".\\assets\\fonts\\BLKCHCRY.TTF"
#define SCRATCHED_FONT ".\\assets\\fonts\\Scratched.ttf"
#define THEYPERISHED_FONT ".\\assets\\fonts\\TheyPerished.ttf"


// HELP PAGES
#define PAGE_ONE ".\\assets\\how-to-play\\1.png"
#define PAGE_TWO ".\\assets\\how-to-play\\2.png"
#define PAGE_THREE ".\\assets\\how-to-play\\3.png"
#define PAGE_FOUR ".\\assets\\how-to-play\\4.png"


// PLAYERS
#define WHITE_PAWN ".\\assets\\roles\\white_pawn.png"
#define DIVER_ROLE ".\\assets\\roles\\diver.png"
#define DIVER_PAWN ".\\assets\\roles\\diver_pawn.png"
#define PILOT_ROLE ".\\assets\\roles\\pilot.png"
#define PILOT_PAWN ".\\assets\\roles\\pilot_pawn.png"
#define EXPLORER_ROLE ".\\assets\\roles\\explorer.png"
#define EXPLORER_PAWN ".\\assets\\roles\\explorer_pawn.png"


// MUSIC
#define INTO_THE_WATER ".\\assets\\sounds\\Exploration Ambience.mp3"
#define FALLING_WATER ".\\assets\\sounds\\Water Temple.mp3"


// TILES
#define LIMNI ".\\assets\\tiles\\xameni_limni.png"
#define DASOS ".\\assets\\tiles\\porfiro_dasos.png"
#define PARATIRITIRIO ".\\assets\\tiles\\paratiritirio.png"
#define LAGADI ".\\assets\\tiles\\lagadi_toy_likofotos.png"
#define VALTOS ".\\assets\\tiles\\valtos_tis_omixlis.png"
#define VRAXOI ".\\assets\\tiles\\vraxoi_tis_egatalipsis.png"
#define AMMOLOFOI ".\\assets\\tiles\\ammolofoi_tis_paraplanisis.png"
#define ASTEROSKOPEIO ".\\assets\\tiles\\asteroskopeio.png"
#define VRAXOS ".\\assets\\tiles\\diavolikos_vraxos.png"
#define GEFIRA ".\\assets\\tiles\\gefira_tis_katastrofis.png"
#define KIPOS_PSI ".\\assets\\tiles\\kipos_tvn_psithirwvn.png"
#define KIPOS_KRA ".\\assets\\tiles\\kipos_twn_kravgwn.png"
#define NAOS_ILIOY ".\\assets\\tiles\\naos_tou_iliou.png"
#define NAOS_FEGGARIOY ".\\assets\\tiles\\naos_toy_feggariou.png"
#define PALATI_PAL ".\\assets\\tiles\\palati_tis_palirroias.png"
#define PALATI_KOR ".\\assets\\tiles\\palati_tou_koraliou.png"
#define SPILIA_LAVAS ".\\assets\\tiles\\spilia_tis_lavas.png"
#define SPILIA_SKIWN ".\\assets\\tiles\\spilia_twn_skiwn.png"
#define PILI_AGNOIAS ".\\assets\\tiles\\pili_tis_agnoias.png"
#define PILI_PROSMONIS ".\\assets\\tiles\\pili_tis_prosmonis.png"
#define XEFWTO ".\\assets\\tiles\\xefwto_twn_trelwn.png"