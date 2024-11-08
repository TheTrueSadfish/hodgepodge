.set LOCALID_INTROMAN, 1

PlatoonOutside_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, PlatoonOutside_OnFrame
	.byte 0

PlatoonOutside_OnFrame:
	map_script_2 VAR_LITTLEROOT_INTRO_STATE, 0, PlatoonOutside_EventScript_PlatoonOpening
	.2byte 0

PlatoonOutside_EventScript_PlatoonOpening::
	lockall
	delay 16
	applymovement LOCALID_INTROMAN, PlatoonOutside_Movement_IntromanWalkToPlayer
	applymovement OBJ_EVENT_ID_PLAYER, PlatoonOutside_Movement_PlayerWalkToIntroman
	waitmovement 0
	setvar VAR_LITTLEROOT_INTRO_STATE, 1
	setflag FLAG_SYS_POKEMON_GET
	setflag FLAG_ADVENTURE_STARTED
	setflag FLAG_SYS_POKEDEX_GET
	special SetUnlockedPokedexFlags
	setflag FLAG_RECEIVED_POKEDEX_FROM_BIRCH
	setflag FLAG_SYS_B_DASH
	setflag FLAG_RECEIVED_RUNNING_SHOES
	msgbox PlatoonOutside_Text_WelcomeToThePlatoon, MSGBOX_DEFAULT
	givemon SPECIES_MUSTYBANE, 50, ITEM_FAVOR_SCARF
	call PlatoonOutside_EventScript_ReceivedMustybaneFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, PlatoonOutside_EventScript_EnjoyThePlatoon
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto PlatoonOutside_EventScript_EnjoyThePlatoon
	closemessage
	releaseall
	end

PlatoonOutside_Movement_IntromanWalkToPlayer:
	walk_down
	walk_down
	walk_down
	step_end

PlatoonOutside_Movement_PlayerWalkToIntroman:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	face_up
	step_end

PlatoonOutside_EventScript_ReceivedMustybaneFanfare::
	playfanfare MUS_OBTAIN_ITEM
	message PlatoonOutside_Text_PlayerReceivedMustybane
	waitmessage
	waitfanfare
	bufferspeciesname STR_VAR_1, SPECIES_MUSTYBANE
	return

PlatoonOutside_EventScript_EnjoyThePlatoon::
	msgbox PlatoonOutside_Text_EnjoyThePlatoon, MSGBOX_AUTOCLOSE
	applymovement LOCALID_INTROMAN, PlatoonOutside_Movement_IntromanAdjourn
	waitmovement 0
	playse SE_EXIT
	removeobject LOCALID_INTROMAN
	setflag FLAG_HIDE_INTRO_MAN_AFTER
	releaseall
	end

PlatoonOutside_Movement_IntromanAdjourn:
	walk_up
	walk_up
	walk_up
	step_end

PlatoonOutside_Text_WelcomeToThePlatoon:
	.string "welcome here have a mustybane$"

PlatoonOutside_Text_EnjoyThePlatoon:
	.string "kill urself$"

PlatoonOutside_Text_PlayerReceivedMustybane:
	.string "{PLAYER} received a Mustybane!$"
