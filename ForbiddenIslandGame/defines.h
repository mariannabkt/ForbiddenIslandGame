#pragma once
#include <random>
#include <stdlib.h>

using namespace std;

#define WINDOW_WIDTH 1400
#define WINDOW_HEIGHT 800

#define CANVAS_WIDTH 28.0f
#define CANVAS_HEIGHT 16.0f

#define DEMO_PLAYER_SIZE 1.8f
#define PLAYER_SIZE 0.8f
#define TILE_SIZE 2.2f

#define SETCOLOR(c,r,g,b) { c[0]=r; c[1]=g; c[2]=b; }
#define RAND0TO1() ( rand() / (float)RAND_MAX )


enum game_state			{ INIT, LOADING, MAIN_MENU, HELP, CHOOSE_DIF, CHOOSE_PLAYER, PLAYING };
enum help_page			{ ONE, TWO, THREE, FOUR };
enum button_func		{ PLAY, EASY, MEDIUM, HARD, LEGENDARY, HOW_TO, EXIT, HOME, NEXT, PREV, OK };
enum player_role		{ DIVER, EXPLORER, PILOT };
enum tile_type			{ BASIC,TREASURE, LANDING };
enum treasure_type		{ FIRE, WATER, AIR, EARTH };


// ASSET FOLDERS
#define BACKGROUNDS_FOLDER	".\\assets\\backgrounds\\"
#define BUTTON_FOLDER		".\\assets\\buttons\\"
#define HELP_PAGES_FOLDER	".\\assets\\help_pages\\"
#define PLAYERS_FOLDER		".\\assets\\players\\"
#define PLAYING_FOLDER		".\\assets\\playing\\"
#define TREASURES_FOLDER	".\\assets\\treasures\\"
#define TILES_FOLDER		".\\assets\\tiles\\"


// BACKGROUNDS
#define MAIN_BACKGROUND					".\\assets\\backgrounds\\main_background.png"
#define CHOOSE_PLAYER_BACKGROUND		".\\assets\\backgrounds\\choose_player.png"
#define CHOOSE_DIFFICULTY_BACKGROUND	".\\assets\\backgrounds\\choose_difficulty.png"
#define PLAYING_BACKGROUND				".\\assets\\backgrounds\\playing_background.png"


// BUTTONS
#define PLAY_BUTTON        ".\\assets\\buttons\\play button.png"
#define OK_BUTTON          ".\\assets\\buttons\\ok button.png"
#define EXIT_BUTTON        ".\\assets\\buttons\\exit button.png"
#define HOME_BUTTON		   ".\\assets\\buttons\\home button.png"
#define NEXT_BUTTON        ".\\assets\\buttons\\next button.png"
#define PREV_BUTTON        ".\\assets\\buttons\\previous button.png"
#define EASY_BUTTON        ".\\assets\\buttons\\easy button.png"
#define MEDIUM_BUTTON      ".\\assets\\buttons\\medium button.png"
#define HARD_BUTTON        ".\\assets\\buttons\\hard button.png"
#define LEGENDARY_BUTTON   ".\\assets\\buttons\\legendary button.png"
#define HOW_TO_PLAY_BUTTON ".\\assets\\buttons\\how to play button.png"


// FONTS
#define SKYTREE_FONT      ".\\assets\\fonts\\Skytree.ttf"
#define IMMORTAL_FONT     ".\\assets\\fonts\\IMMORTAL.ttf"
#define FREESANS_FONT     ".\\assets\\fonts\\FreeSans.ttf"
#define BLKCHCRY_FONT     ".\\assets\\fonts\\BLKCHCRY.TTF"
#define SCRATCHED_FONT    ".\\assets\\fonts\\Scratched.ttf"
#define THEYPERISHED_FONT ".\\assets\\fonts\\TheyPerished.ttf"


// HELP PAGES
#define PAGE_ONE   ".\\assets\\help_pages\\1.png"
#define PAGE_TWO   ".\\assets\\help_pages\\2.png"
#define PAGE_THREE ".\\assets\\help_pages\\3.png"
#define PAGE_FOUR  ".\\assets\\help_pages\\4.png"


// PLAYER PAWNS
#define EXPLORER_PAWN ".\\assets\\players\\explorer_pawn.png"
#define DIVER_PAWN    ".\\assets\\players\\diver_pawn.png"
#define PILOT_PAWN    ".\\assets\\players\\pilot_pawn.png"
#define WHITE_PAWN    ".\\assets\\players\\white_pawn.png"


// PLAYER ICONS
#define EXPLORER_ICON ".\\assets\\players\\explorer.png"
#define DIVER_ICON    ".\\assets\\players\\diver.png"
#define PILOT_ICON    ".\\assets\\players\\pilot.png"


// PLAYING STATE BITMAPS
#define PLAYER_CARD		".\\assets\\playing\\old paper card.png"
#define WATER_LEVEL		".\\assets\\playing\\water-level.png"
#define ACTION_ONE		".\\assets\\playing\\action_one.png"
#define ACTION_TWO		".\\assets\\playing\\action_two.png"
#define ACTION_THREE	".\\assets\\playing\\action_three.png"


// TREASURE ICONS
#define AIR_TREASURE   ".\\assets\\treasures\\agalma_tou_anemou_nbg.PNG"
#define FIRE_TREASURE  ".\\assets\\treasures\\krystallos_tis_fotias_nbg.PNG"
#define WATER_TREASURE ".\\assets\\treasures\\diskopotiro_tou_wkeanou_nbg.PNG"
#define EARTH_TREASURE ".\\assets\\treasures\\lithos_tis_gis_nbg.PNG"


// MUSIC
#define ELEVATOR_MUSIC   ".\\assets\\sounds\\Elevator music.mp3"
#define NATURAL_AMBIENCE ".\\assets\\sounds\\natural-ambience-with-flowing-water-and-birds.wav"
#define INTO_THE_WATER   ".\\assets\\sounds\\Exploration Ambience.mp3"
#define FALLING_WATER    ".\\assets\\sounds\\Water Temple.mp3"


// SOUNDS
#define FLIP_PAGE	   ".\\assets\\sounds\\page_flip.wav"
#define BUTTON_CLICK   ".\\assets\\sounds\\player-jumping-in-a-video-game.wav"
#define START_PLAYING  ".\\assets\\sounds\\horn-transition.wav"


// TILES
#define LIMNI           ".\\assets\\tiles\\xameni_limni.png"
#define DASOS           ".\\assets\\tiles\\porfiro_dasos.png"
#define PARATIRITIRIO   ".\\assets\\tiles\\paratiritirio.png"
#define LAGADI          ".\\assets\\tiles\\lagadi_toy_likofotos.png"
#define VALTOS          ".\\assets\\tiles\\valtos_tis_omixlis.png"
#define VRAXOI          ".\\assets\\tiles\\vraxoi_tis_egatalipsis.png"
#define AMMOLOFOI       ".\\assets\\tiles\\ammolofoi_tis_paraplanisis.png"
#define ASTEROSKOPEIO   ".\\assets\\tiles\\asteroskopeio.png"
#define VRAXOS          ".\\assets\\tiles\\diavolikos_vraxos.png"
#define GEFIRA          ".\\assets\\tiles\\gefira_tis_katastrofis.png"
#define KIPOS_PSI       ".\\assets\\tiles\\kipos_twn_psithirwvn.png"
#define KIPOS_KRA       ".\\assets\\tiles\\kipos_twn_kravgwn.png"
#define NAOS_ILIOY      ".\\assets\\tiles\\naos_tou_iliou.png"
#define NAOS_FEGGARIOY  ".\\assets\\tiles\\naos_toy_feggariou.png"
#define PALATI_PAL      ".\\assets\\tiles\\palati_tis_palirroias.png"
#define PALATI_KOR      ".\\assets\\tiles\\palati_tou_koraliou.png"
#define SPILIA_LAVAS    ".\\assets\\tiles\\spilia_tis_lavas.png"
#define SPILIA_SKIWN    ".\\assets\\tiles\\spilia_twn_skiwn.png"
#define PILI_AGNOIAS    ".\\assets\\tiles\\pili_tis_agnoias.png"
#define PILI_PROSMONIS  ".\\assets\\tiles\\pili_tis_prosmonis.png"
#define PILI_APLISTIAS  ".\\assets\\tiles\\pili_tis_aplistias.png"
#define PILI_AXARISTIAS ".\\assets\\tiles\\pili_tis_axaristias.png"
#define PILI_LITHIS     ".\\assets\\tiles\\pili_tis_lithis.png"
#define XEFWTO          ".\\assets\\tiles\\xefwto_twn_trelwn.png"