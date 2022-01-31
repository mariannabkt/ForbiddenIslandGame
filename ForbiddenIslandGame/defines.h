#pragma once
#include <random>
#include <stdlib.h>
#include <thread>
#include <chrono>


using namespace std;

#define WINDOW_WIDTH 1400
#define WINDOW_HEIGHT 800

#define CANVAS_WIDTH 28.0f
#define CANVAS_HEIGHT 16.0f

#define DEMO_PLAYER_SIZE 1.8f 
#define PLAYER_SIZE 0.8f

#define TILE_SIZE 2.2f
#define TILES_COUNT 24

#define LAYOUT_IMG_SIZE 3.0f
#define BUBBLE_SIZE 0.5f

#define SETCOLOR(c,r,g,b) { c[0]=r; c[1]=g; c[2]=b; }
#define RAND0TO1() ( rand() / (float)RAND_MAX )

inline void sleep(int ms) {
	this_thread::sleep_for(std::chrono::milliseconds(ms));
}


enum GAME_STATE		{ INIT, LOADING, MAIN_MENU, SHOW_HOW_TO, CHOOSE_ISLAND, CHOOSE_DIF, CHOOSE_PLAYER, PLAYING, RETRY, INFO };
enum HELP_PAGE		{ ONE, TWO, THREE, FOUR };
enum BUTTON_FUNC	{ EXIT, EASY, MEDIUM, HARD, LEGENDARY, PLAY, HOW_TO, ABOUT, HELP, HOME, NEXT, PREV, OK, PLAY_AGAIN };
enum PLAYER_ROLE	{ DIVER, EXPLORER, PILOT };
enum TILE_TYPE		{ BASIC,TREASURE, LANDING };
enum TREASURE_TYPE	{ FIRE, WATER, AIR, EARTH };


// ASSET FOLDERS
#define BACKGROUNDS_FOLDER	".\\assets\\backgrounds\\"
#define BUTTON_FOLDER		".\\assets\\buttons\\"
#define HELP_PAGES_FOLDER	".\\assets\\help_pages\\"
#define PLAYERS_FOLDER		".\\assets\\players\\"
#define PLAYING_FOLDER		".\\assets\\playing\\"
#define TREASURES_FOLDER	".\\assets\\treasures\\"
#define TILES_FOLDER		".\\assets\\tiles\\"
#define LAYOUTS_FOLDER		".\\assets\\layouts\\"
#define SEA_FRAMES_FOLDER	".\\assets\\sea frames\\"


// BACKGROUNDS
#define MAIN_BACKGROUND					".\\assets\\backgrounds\\main_background.png"
#define CHOOSE_ISLAND_BACKGROUND		".\\assets\\backgrounds\\choose_island.png"
#define CHOOSE_PLAYER_BACKGROUND		".\\assets\\backgrounds\\choose_player.png"
#define CHOOSE_DIFFICULTY_BACKGROUND	".\\assets\\backgrounds\\choose_difficulty.png"
#define PLAYING_BACKGROUND				".\\assets\\backgrounds\\sea.png"
#define VICTORY_BACKGROUND				".\\assets\\backgrounds\\victory_background.png"
#define LOOSERS_BACKGROUND				".\\assets\\backgrounds\\loosers_background.png"
#define ABOUT_BACKGROUND				".\\assets\\backgrounds\\about.png"


// BUTTONS
#define PLAY_BUTTON			".\\assets\\buttons\\play button.png"
#define OK_BUTTON			".\\assets\\buttons\\ok button.png"
#define HELP_BUTTON			".\\assets\\buttons\\help button.png"
#define EXIT_BUTTON			".\\assets\\buttons\\exit button.png"
#define HOME_BUTTON			".\\assets\\buttons\\home button.png"
#define NEXT_BUTTON			".\\assets\\buttons\\next button.png"
#define PREV_BUTTON			".\\assets\\buttons\\previous button.png"
#define EASY_BUTTON			".\\assets\\buttons\\easy button.png"
#define MEDIUM_BUTTON		".\\assets\\buttons\\medium button.png"
#define HARD_BUTTON			".\\assets\\buttons\\hard button.png"
#define LEGENDARY_BUTTON	".\\assets\\buttons\\legendary button.png"
#define ABOUT_BUTTON		".\\assets\\buttons\\about button.png"
#define HOW_TO_BUTTON		".\\assets\\buttons\\how to play button.png"
#define RETRY_BUTTON		".\\assets\\buttons\\play again button.png"


// FONTS
#define SKYTREE_FONT      ".\\assets\\fonts\\Skytree.ttf"
#define IMMORTAL_FONT     ".\\assets\\fonts\\IMMORTAL.ttf"
#define FREESANS_FONT     ".\\assets\\fonts\\FreeSans.ttf"
#define BLKCHCRY_FONT     ".\\assets\\fonts\\BLKCHCRY.TTF"
#define SCRATCHED_FONT    ".\\assets\\fonts\\Scratched.ttf"
#define THEYPERISHED_FONT ".\\assets\\fonts\\TheyPerished.ttf"


// LAYOUTS IMAGES
#define SKULL_IMAGE		".\\assets\\layouts\\skull island.png"
#define HARPOON_IMAGE	".\\assets\\layouts\\harpoon hideout.png"
#define ATOLL_IMAGE	".\\assets\\layouts\\atoll of decisions.png"
#define BAY_IMAGE	".\\assets\\layouts\\bay of gulls.png"
#define SHIPWRECK_IMAGE	".\\assets\\layouts\\shipwreck bay.png"
#define PALM_IMAGE	".\\assets\\layouts\\palm springs.png"
#define MUTINY_IMAGE	".\\assets\\layouts\\mutiny towers.png"
#define DAVY_IMAGE	".\\assets\\layouts\\davy jones.png"


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
#define BUBBLE_IMAGE	".\\assets\\playing\\bubble.png"
#define WATER_LEVEL		".\\assets\\playing\\water level bar.png"
#define WHIRLPOOL		".\\assets\\playing\\sea whirlpool.png"
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
#define FLIP_PAGE		".\\assets\\sounds\\page_flip.wav"
#define BUTTON_CLICK1	".\\assets\\sounds\\player-jumping-in-a-video-game.wav"
#define BUTTON_CLICK2	".\\assets\\sounds\\unlock-new-item-game-notification.wav"
#define START_PLAYING	".\\assets\\sounds\\horn-transition.wav"
#define VICTORY_SOUND	".\\assets\\sounds\\completion-of-a-level.wav"
#define GAME_OVER_SOUND	".\\assets\\sounds\\game-over-orchestra.wav"
#define FLOOD_SOUND		".\\assets\\sounds\\healing-water-spell-with-deep-hit.wav"
#define SINK_SOUND		".\\assets\\sounds\\jump-into-the-water.wav"
#define TREASURE_SOUND	".\\assets\\sounds\\magic-sweep-game-trophy.wav"
#define	TOUCH_SOUND		".\\assets\\sounds\\short-button-click.wav"



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