.set LOCALID_LANETTE, 8
.set LOCALID_GUARD, 9

PlatoonInsideFoyer_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, PlatoonInsideFoyer_OnLoad
	map_script MAP_SCRIPT_ON_FRAME_TABLE, PlatoonInsideFoyer_OnFrame
	.byte 0

PlatoonInsideFoyer_OnFrame:
	map_script_2 VAR_HP_POST_CHALLENGE_TEMP, 2, PlatoonInsideFoyer_EventScript_CheckHPProgressWon
	map_script_2 VAR_HP_POST_CHALLENGE_TEMP, 1, PlatoonInsideFoyer_EventScript_CheckHPProgressLost
	.2byte 0

PlatoonInsideFoyer_OnLoad:
	call_if_gt VAR_HP_PROGRESS, 3, PlatoonInsideFoyer_EventScript_RemoveFanClubGuard
	call_if_set FLAG_HP_UNLOCKED_MUSEUM, PlatoonInsideFoyer_EventScript_OpenMuseumGate
	end

PlatoonInsideFoyer_EventScript_RemoveFanClubGuard::
	removeobject LOCALID_GUARD
	setflag FLAG_TEMP_12
	return

PlatoonInsideFoyer_EventScript_OpenMuseumGate::
	setmetatile 24, 5, METATILE_TrainerHill_WithoutDoor, FALSE
	special DrawWholeMapView
	return

PlatoonInsideFoyer_EventScript_CheckHPProgressWon::
	lockall
	setvar VAR_HP_POST_CHALLENGE_TEMP, 0
	switch VAR_HP_PROGRESS
	case 0, PlatoonInsideFoyer_EventScript_UnlockItemMenuPrevoChecker
	case 1, PlatoonInsideFoyer_EventScript_UnlockPrevoChecker
	case 2, PlatoonInsideFoyer_EventScript_Check50SeenMons
	case 3, PlatoonInsideFoyer_EventScript_Check100SeenMons
	case 4, PlatoonInsideFoyer_EventScript_Check80CaughtMons
	case 5, PlatoonInsideFoyer_EventScript_Check140CaughtMons
	case 6, PlatoonInsideFoyer_EventScript_CancelOut
	releaseall
	end

PlatoonInsideFoyer_EventScript_CheckHPProgressLost::
	lockall
	setvar VAR_HP_POST_CHALLENGE_TEMP, 0
	switch VAR_HP_PROGRESS
	case 0, PlatoonInsideFoyer_EventScript_UnlockItemMenu
	case 1, PlatoonInsideFoyer_EventScript_CancelOut
	case 2, PlatoonInsideFoyer_EventScript_Check50SeenMons
	case 3, PlatoonInsideFoyer_EventScript_Check100SeenMons
	case 4, PlatoonInsideFoyer_EventScript_Check80CaughtMons
	case 5, PlatoonInsideFoyer_EventScript_Check140CaughtMons
	case 6, PlatoonInsideFoyer_EventScript_CancelOut
	releaseall
	end

PlatoonInsideFoyer_EventScript_UnlockItemMenu::
	applymovement LOCALID_LANETTE, PlatoonInsideFoyer_Movement_LanetteFaceDoor
	waitmovement 0
	msgbox PlatoonInsideFoyer_Text_IWasWatchingYourMatches, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_LANETTE, PlatoonInsideFoyer_Movement_LanetteFaceDown
	applymovement OBJ_EVENT_ID_PLAYER, PlatoonInsideFoyer_Movement_PlayerWalkToLanette
	waitmovement 0
	delay 4
	speakername PlatoonInsideFoyer_Text_NameLanette
	msgbox PlatoonInsideFoyer_Text_IllUnlockTheItemMenuForYou, MSGBOX_DEFAULT
	setvar VAR_HP_PROGRESS, 1
	releaseall
	end

PlatoonInsideFoyer_Movement_LanetteFaceDoor:
	face_left
	step_end

PlatoonInsideFoyer_Movement_LanetteFaceDown:
	face_down
	step_end

PlatoonInsideFoyer_Movement_PlayerWalkToLanette:
	walk_down
	walk_right
	walk_right
	walk_right
	face_up
	step_end

PlatoonInsideFoyer_EventScript_UnlockPrevoChecker::
	applymovement LOCALID_LANETTE, PlatoonInsideFoyer_Movement_LanetteFaceDoor
	waitmovement 0
	speakername PlatoonInsideFoyer_Text_NameLanette
	msgbox PlatoonInsideFoyer_Text_ExcitingWin, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_LANETTE, PlatoonInsideFoyer_Movement_LanetteFaceDown
	applymovement OBJ_EVENT_ID_PLAYER, PlatoonInsideFoyer_Movement_PlayerWalkToLanette
	waitmovement 0
	delay 4
	msgbox PlatoonInsideFoyer_Text_IllUnlockThePrevoCheckerForYou, MSGBOX_DEFAULT
	setvar VAR_HP_PROGRESS, 2
	releaseall
	end

PlatoonInsideFoyer_EventScript_UnlockItemMenuPrevoChecker::
	applymovement LOCALID_LANETTE, PlatoonInsideFoyer_Movement_LanetteFaceDoor
	waitmovement 0
	msgbox PlatoonInsideFoyer_Text_IWasWatchingYourMatches, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_LANETTE, PlatoonInsideFoyer_Movement_LanetteFaceDown
	applymovement OBJ_EVENT_ID_PLAYER, PlatoonInsideFoyer_Movement_PlayerWalkToLanette
	waitmovement 0
	delay 4
	speakername PlatoonInsideFoyer_Text_NameLanette
	msgbox PlatoonInsideFoyer_Text_IllUnlockTheItemAndPrevoForYou, MSGBOX_DEFAULT
	setvar VAR_HP_PROGRESS, 2
	releaseall
	end	

PlatoonInsideFoyer_EventScript_Check50SeenMons::
	setvar VAR_0x8004, 0
	specialvar VAR_RESULT, ScriptGetPokedexInfo
	copyvar VAR_0x8008, VAR_0x8005
	copyvar VAR_0x8009, VAR_0x8006
	copyvar VAR_0x800A, VAR_RESULT
	buffernumberstring STR_VAR_1, VAR_0x8008  @ Num Hoenn seen
	buffernumberstring STR_VAR_2, VAR_0x8009  @ Num Hoenn caught
	goto_if_gt VAR_0x8008, 49, PlatoonInsideFoyer_EventScript_Seen50Mons
	releaseall
	end

PlatoonInsideFoyer_EventScript_Seen50Mons::
	applymovement LOCALID_LANETTE, PlatoonInsideFoyer_Movement_LanetteFaceDoor
	waitmovement 0
	speakername PlatoonInsideFoyer_Text_NameLanette
	msgbox PlatoonInsideFoyer_Text_50DexSeen, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_LANETTE, PlatoonInsideFoyer_Movement_LanetteFaceDown
	applymovement OBJ_EVENT_ID_PLAYER, PlatoonInsideFoyer_Movement_PlayerWalkToLanette
	waitmovement 0
	delay 4
	msgbox PlatoonInsideFoyer_Text_IllUnlockTheCustomTypeMons, MSGBOX_DEFAULT
	setvar VAR_HP_PROGRESS, 3
	releaseall
	end

PlatoonInsideFoyer_EventScript_Check100SeenMons::
	setvar VAR_0x8004, 0
	specialvar VAR_RESULT, ScriptGetPokedexInfo
	copyvar VAR_0x8008, VAR_0x8005
	copyvar VAR_0x8009, VAR_0x8006
	copyvar VAR_0x800A, VAR_RESULT
	buffernumberstring STR_VAR_1, VAR_0x8008  @ Num Hoenn seen
	buffernumberstring STR_VAR_2, VAR_0x8009  @ Num Hoenn caught
	goto_if_gt VAR_0x8008, 99, PlatoonInsideFoyer_EventScript_Seen100Mons
	releaseall
	end

PlatoonInsideFoyer_EventScript_Seen100Mons::
	applymovement LOCALID_LANETTE, PlatoonInsideFoyer_Movement_LanetteFaceDoor
	waitmovement 0
	speakername PlatoonInsideFoyer_Text_NameLanette
	msgbox PlatoonInsideFoyer_Text_100DexSeen, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_LANETTE, PlatoonInsideFoyer_Movement_LanetteFaceDown
	applymovement OBJ_EVENT_ID_PLAYER, PlatoonInsideFoyer_Movement_PlayerWalkToLanette
	waitmovement 0
	delay 4
	msgbox PlatoonInsideFoyer_Text_IllUnlockTheFanClub, MSGBOX_DEFAULT
	setvar VAR_HP_PROGRESS, 4
	removeobject LOCALID_GUARD
	setflag FLAG_TEMP_12
	releaseall
	end

PlatoonInsideFoyer_EventScript_Check80CaughtMons::
	setvar VAR_0x8004, 0
	specialvar VAR_RESULT, ScriptGetPokedexInfo
	copyvar VAR_0x8008, VAR_0x8005
	copyvar VAR_0x8009, VAR_0x8006
	copyvar VAR_0x800A, VAR_RESULT
	buffernumberstring STR_VAR_1, VAR_0x8008  @ Num Hoenn seen
	buffernumberstring STR_VAR_2, VAR_0x8009  @ Num Hoenn caught
	goto_if_gt VAR_0x8009, 79, PlatoonInsideFoyer_EventScript_Caught80Mons
	releaseall
	end

PlatoonInsideFoyer_EventScript_Caught80Mons::
	applymovement LOCALID_LANETTE, PlatoonInsideFoyer_Movement_LanetteFaceDoor
	waitmovement 0
	speakername PlatoonInsideFoyer_Text_NameLanette
	msgbox PlatoonInsideFoyer_Text_80DexCaught, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_LANETTE, PlatoonInsideFoyer_Movement_LanetteFaceDown
	applymovement OBJ_EVENT_ID_PLAYER, PlatoonInsideFoyer_Movement_PlayerWalkToLanette
	waitmovement 0
	delay 4
	msgbox PlatoonInsideFoyer_Text_IllUnlockPebbleriteCave, MSGBOX_DEFAULT
	setvar VAR_HP_PROGRESS, 5
	releaseall
	end

PlatoonInsideFoyer_EventScript_Check140CaughtMons::
	setvar VAR_0x8004, 0
	specialvar VAR_RESULT, ScriptGetPokedexInfo
	copyvar VAR_0x8008, VAR_0x8005
	copyvar VAR_0x8009, VAR_0x8006
	copyvar VAR_0x800A, VAR_RESULT
	buffernumberstring STR_VAR_1, VAR_0x8008  @ Num Hoenn seen
	buffernumberstring STR_VAR_2, VAR_0x8009  @ Num Hoenn caught
	goto_if_gt VAR_0x8009, 139, PlatoonInsideFoyer_EventScript_CaughtAllMons
	releaseall
	end

PlatoonInsideFoyer_EventScript_CaughtAllMons::
	applymovement LOCALID_LANETTE, PlatoonInsideFoyer_Movement_LanetteFaceDoor
	waitmovement 0
	speakername PlatoonInsideFoyer_Text_NameLanette
	msgbox PlatoonInsideFoyer_Text_140DexCaught, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_LANETTE, PlatoonInsideFoyer_Movement_LanetteFaceDown
	applymovement OBJ_EVENT_ID_PLAYER, PlatoonInsideFoyer_Movement_PlayerWalkToLanette
	waitmovement 0
	delay 4
	msgbox PlatoonInsideFoyer_Text_IllUnlockMuseum, MSGBOX_DEFAULT
	setvar VAR_HP_PROGRESS, 6
	releaseall
	end

PlatoonInsideFoyer_EventScript_CancelOut::
	releaseall
	end	

PlatoonInsideFoyer_EventScript_ItemMenu::
	lock
	faceplayer
	goto_if_set FLAG_HP_UNLOCKED_ITEM_MENU, PlatoonInsideFoyer_EventScript_HaveAllItems
	goto_if_lt VAR_HP_PROGRESS, 1, PlatoonInsideFoyer_EventScript_ItemMenuLocked
	msgbox PlatoonInsideFoyer_Text_WantAllTheItems, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, PlatoonInsideFoyer_EventScript_GiveAllItems
	msgbox PlatoonInsideFoyer_Text_NoItemsForU, MSGBOX_AUTOCLOSE
	release
	end

PlatoonInsideFoyer_EventScript_HaveAllItems::
	msgbox PlatoonInsideFoyer_Text_EnjoyingYourItems, MSGBOX_AUTOCLOSE
	release
	end

PlatoonInsideFoyer_EventScript_ItemMenuLocked::
	msgbox PlatoonInsideFoyer_Text_NoItemsForNewbies, MSGBOX_AUTOCLOSE
	release
	end

PlatoonInsideFoyer_EventScript_GiveAllItems::
	msgbox PlatoonInsideFoyer_Text_OkayBuckleUp, MSGBOX_DEFAULT
	giveitem ITEM_BURNT_BRANCH
	giveitem ITEM_HONDEW_BERRY
	giveitem ITEM_RED_CARD
	giveitem ITEM_SILK_SCARF
	giveitem ITEM_FOCUS_SASH
	giveitem ITEM_CHARCOAL
	giveitem ITEM_ROCKY_HELMET
	giveitem ITEM_FOCUS_BAND
	giveitem ITEM_PUNCHING_GLOVE
	giveitem ITEM_SHARP_BEAK
	giveitem ITEM_STICKY_BARB
	giveitem ITEM_MIRROR_HERB
	giveitem ITEM_UTILITY_UMBRELLA
	giveitem ITEM_NANAB_BERRY
	giveitem ITEM_GRASSY_SEED
	giveitem ITEM_SITRUS_BERRY
	giveitem ITEM_BIG_ROOT
	giveitem ITEM_LEFTOVERS
	giveitem ITEM_COBA_BERRY
	giveitem ITEM_BELUE_BERRY
	giveitem ITEM_SCOPE_LENS
	giveitem ITEM_LUMINOUS_MOSS
	giveitem ITEM_RING_TARGET
	giveitem ITEM_MENTAL_HERB
	giveitem ITEM_CLEANSE_TAG
	giveitem ITEM_CURSED_AMULET
	giveitem ITEM_COVERT_CLOAK
	giveitem ITEM_DESTINY_KNOT
	giveitem ITEM_BLUK_BERRY
	giveitem ITEM_WISE_GLASSES
	giveitem ITEM_AIR_BALLOON
	giveitem ITEM_ZOOM_LENS
	giveitem ITEM_SOFT_SAND
	giveitem ITEM_LIFE_ORB
	giveitem ITEM_ABSORB_BULB
	giveitem ITEM_PROTECTIVE_PADS
	giveitem ITEM_LOST_MANTLE
	giveitem ITEM_WEAKNESS_POLICY
	giveitem ITEM_HARD_STONE
	giveitem ITEM_BATTLE_HELM
	giveitem ITEM_QUICK_CLAW
	giveitem ITEM_CHOICE_BAND
	giveitem ITEM_SHELL_BELL
	giveitem ITEM_ABILITY_SHIELD
	giveitem ITEM_METRONOME
	giveitem ITEM_KINGS_ROCK
	giveitem ITEM_WIDE_LENS
	giveitem ITEM_TANGA_BERRY
	giveitem ITEM_FLIP_COIN
	giveitem ITEM_CUSTAP_BERRY
	giveitem ITEM_SALAC_BERRY
	giveitem ITEM_FROST_ORB
	giveitem ITEM_SPECTRAL_IDOL
	giveitem ITEM_MUSCLE_BAND
	giveitem ITEM_BLACK_SLUDGE
	giveitem ITEM_FLOAT_STONE
	giveitem ITEM_POISON_BARB
	giveitem ITEM_SHUCA_BERRY
	giveitem ITEM_PESKY_PLUSH
	giveitem ITEM_SILVER_POWDER
	giveitem ITEM_EJECT_BUTTON
	giveitem ITEM_BRIGHT_POWDER
	giveitem ITEM_CLEAR_AMULET
	giveitem ITEM_BINDING_BAND
	giveitem ITEM_TOXIC_ORB
	giveitem ITEM_DRAGON_FANG
	giveitem ITEM_ROSELI_BERRY
	giveitem ITEM_GLUE_TUBE
	giveitem ITEM_PINAP_BERRY
	giveitem ITEM_ICY_ROCK
	giveitem ITEM_SPELON_BERRY
	giveitem ITEM_POMEG_BERRY
	giveitem ITEM_FLAME_ORB
	giveitem ITEM_NEVER_MELT_ICE
	giveitem ITEM_LIGHT_CLAY
	giveitem ITEM_LOADED_DICE
	giveitem ITEM_LIGHT_BALL
	giveitem ITEM_JABOCA_BERRY
	giveitem ITEM_CORRODE_MOD
	giveitem ITEM_BLUNDER_POLICY
	giveitem ITEM_MAGOST_BERRY
	giveitem ITEM_ASSAULT_VEST
	giveitem ITEM_EJECT_PACK
	delay 8
	setflag FLAG_HP_UNLOCKED_ITEM_MENU
	msgbox PlatoonInsideFoyer_Text_ThatsEverything, MSGBOX_AUTOCLOSE
	release
	end

PlatoonInsideFoyer_EventScript_PrevoChecker::
	lock
	faceplayer
	goto_if_lt VAR_HP_PROGRESS, 2, PlatoonInsideFoyer_EventScript_PrevoCheckerLocked
	msgbox PlatoonInsideFoyer_Text_WantToFillOutYourDex, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, PlatoonInsideFoyer_EventScript_FullPrevoCheck
	msgbox PlatoonInsideFoyer_Text_OkayThen, MSGBOX_AUTOCLOSE
	release
	end

PlatoonInsideFoyer_EventScript_PrevoCheckerLocked::
	msgbox PlatoonInsideFoyer_Text_NoPrevoCheckerForNewbies, MSGBOX_AUTOCLOSE
	release
	end

PlatoonInsideFoyer_Movement_PlayerWalkFromCounter:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	step_end

PlatoonInsideFoyer_EventScript_PrevoCheck50SeenMons::
	setvar VAR_0x8004, 0
	specialvar VAR_RESULT, ScriptGetPokedexInfo
	copyvar VAR_0x8008, VAR_0x8005
	copyvar VAR_0x8009, VAR_0x8006
	copyvar VAR_0x800A, VAR_RESULT
	buffernumberstring STR_VAR_1, VAR_0x8008  @ Num Hoenn seen
	buffernumberstring STR_VAR_2, VAR_0x8009  @ Num Hoenn caught
	goto_if_gt VAR_0x8008, 49, PlatoonInsideFoyer_EventScript_PrevoSeen50Mons
	releaseall
	end

PlatoonInsideFoyer_EventScript_PrevoSeen50Mons::
	applymovement LOCALID_LANETTE, PlatoonInsideFoyer_Movement_LanetteFaceDown
	waitmovement 0
	msgbox PlatoonInsideFoyer_Text_50DexSeen, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, PlatoonInsideFoyer_Movement_PlayerWalkFromCounter
	waitmovement 0
	delay 4
	msgbox PlatoonInsideFoyer_Text_IllUnlockTheCustomTypeMons, MSGBOX_DEFAULT
	setvar VAR_HP_PROGRESS, 3
	releaseall
	end

PlatoonInsideFoyer_EventScript_PrevoCheck100SeenMons::
	setvar VAR_0x8004, 0
	specialvar VAR_RESULT, ScriptGetPokedexInfo
	copyvar VAR_0x8008, VAR_0x8005
	copyvar VAR_0x8009, VAR_0x8006
	copyvar VAR_0x800A, VAR_RESULT
	buffernumberstring STR_VAR_1, VAR_0x8008  @ Num Hoenn seen
	buffernumberstring STR_VAR_2, VAR_0x8009  @ Num Hoenn caught
	goto_if_gt VAR_0x8008, 99, PlatoonInsideFoyer_EventScript_PrevoSeen100Mons
	releaseall
	end

PlatoonInsideFoyer_EventScript_PrevoSeen100Mons::
	applymovement LOCALID_LANETTE, PlatoonInsideFoyer_Movement_LanetteFaceDown
	waitmovement 0
	msgbox PlatoonInsideFoyer_Text_100DexSeen, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, PlatoonInsideFoyer_Movement_PlayerWalkFromCounter
	waitmovement 0
	delay 4
	msgbox PlatoonInsideFoyer_Text_IllUnlockTheFanClub, MSGBOX_DEFAULT
	setvar VAR_HP_PROGRESS, 4
	releaseall
	end

PlatoonInsideFoyer_EventScript_PrevoCheck80CaughtMons::
	setvar VAR_0x8004, 0
	specialvar VAR_RESULT, ScriptGetPokedexInfo
	copyvar VAR_0x8008, VAR_0x8005
	copyvar VAR_0x8009, VAR_0x8006
	copyvar VAR_0x800A, VAR_RESULT
	buffernumberstring STR_VAR_1, VAR_0x8008  @ Num Hoenn seen
	buffernumberstring STR_VAR_2, VAR_0x8009  @ Num Hoenn caught
	goto_if_gt VAR_0x8009, 79, PlatoonInsideFoyer_EventScript_PrevoCaught80Mons
	releaseall
	end

PlatoonInsideFoyer_EventScript_PrevoCaught80Mons::
	applymovement LOCALID_LANETTE, PlatoonInsideFoyer_Movement_LanetteFaceDown
	waitmovement 0
	msgbox PlatoonInsideFoyer_Text_80DexCaught, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, PlatoonInsideFoyer_Movement_PlayerWalkFromCounter
	waitmovement 0
	delay 4
	msgbox PlatoonInsideFoyer_Text_IllUnlockPebbleriteCave, MSGBOX_DEFAULT
	setvar VAR_HP_PROGRESS, 5
	releaseall
	end

PlatoonInsideFoyer_EventScript_PrevoCheck140CaughtMons::
	setvar VAR_0x8004, 0
	specialvar VAR_RESULT, ScriptGetPokedexInfo
	copyvar VAR_0x8008, VAR_0x8005
	copyvar VAR_0x8009, VAR_0x8006
	copyvar VAR_0x800A, VAR_RESULT
	buffernumberstring STR_VAR_1, VAR_0x8008  @ Num Hoenn seen
	buffernumberstring STR_VAR_2, VAR_0x8009  @ Num Hoenn caught
	goto_if_gt VAR_0x8009, 139, PlatoonInsideFoyer_EventScript_PrevoCaughtAllMons
	releaseall
	end

PlatoonInsideFoyer_EventScript_PrevoCaughtAllMons::
	applymovement LOCALID_LANETTE, PlatoonInsideFoyer_Movement_LanetteFaceDown
	waitmovement 0
	msgbox PlatoonInsideFoyer_Text_140DexCaught, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, PlatoonInsideFoyer_Movement_PlayerWalkFromCounter
	waitmovement 0
	delay 4
	msgbox PlatoonInsideFoyer_Text_IllUnlockMuseum, MSGBOX_DEFAULT
	setvar VAR_HP_PROGRESS, 6
	releaseall
	end

PlatoonInsideFoyer_EventScript_FullPrevoCheck::
	getcaughtmon SPECIES_RATICATE
	call_if_eq VAR_RESULT, TRUE, PlatoonInsideFoyer_EventScript_SetNettata
	getcaughtmon SPECIES_SWISQUIRE
	call_if_eq VAR_RESULT, TRUE, PlatoonInsideFoyer_EventScript_SetGooper
	getcaughtmon SPECIES_PROFUR
	call_if_eq VAR_RESULT, TRUE, PlatoonInsideFoyer_EventScript_SetMog
	getcaughtmon SPECIES_MUSHARNA
	call_if_eq VAR_RESULT, TRUE, PlatoonInsideFoyer_EventScript_SetBakunna
	getcaughtmon SPECIES_PARASECT
	call_if_eq VAR_RESULT, TRUE, PlatoonInsideFoyer_EventScript_SetParibo
	getcaughtmon SPECIES_URSARING
	call_if_eq VAR_RESULT, TRUE, PlatoonInsideFoyer_EventScript_SetManipursa
	getcaughtmon SPECIES_SHELEBRATE
	call_if_eq VAR_RESULT, TRUE, PlatoonInsideFoyer_EventScript_SetSappodShelbert
	getcaughtmon SPECIES_MUSALORD
	call_if_eq VAR_RESULT, TRUE, PlatoonInsideFoyer_EventScript_SetPlaintain
	getcaughtmon SPECIES_LURKELP
	call_if_eq VAR_RESULT, TRUE, PlatoonInsideFoyer_EventScript_SetKelppy
	getcaughtmon SPECIES_CHERNOBOAR
	call_if_eq VAR_RESULT, TRUE, PlatoonInsideFoyer_EventScript_SetShroomoinkSporke
	getcaughtmon SPECIES_SWALOT
	call_if_eq VAR_RESULT, TRUE, PlatoonInsideFoyer_EventScript_SetGulgan
	getcaughtmon SPECIES_CACTURNE
	call_if_eq VAR_RESULT, TRUE, PlatoonInsideFoyer_EventScript_SetCacolanter
	getcaughtmon SPECIES_EXPLOAD
	call_if_eq VAR_RESULT, TRUE, PlatoonInsideFoyer_EventScript_SetBurstadBlastoad
	getcaughtmon SPECIES_TANGROWTH
	call_if_eq VAR_RESULT, TRUE, PlatoonInsideFoyer_EventScript_SetTentangle
	getcaughtmon SPECIES_GARDEVOIR
	call_if_eq VAR_RESULT, TRUE, PlatoonInsideFoyer_EventScript_SetRalseaCliolia
	getcaughtmon SPECIES_GALLADE
	call_if_eq VAR_RESULT, TRUE, PlatoonInsideFoyer_EventScript_SetRalseaCliolia
	getcaughtmon SPECIES_WAKASUKA
	call_if_eq VAR_RESULT, TRUE, PlatoonInsideFoyer_EventScript_SetPyukumuku
	getcaughtmon SPECIES_BEVOLPIN
	call_if_eq VAR_RESULT, TRUE, PlatoonInsideFoyer_EventScript_SetDullsod
	getcaughtmon SPECIES_XOLHM
	call_if_eq VAR_RESULT, TRUE, PlatoonInsideFoyer_EventScript_SetWattl
	getcaughtmon SPECIES_EELEKTROSS
	call_if_eq VAR_RESULT, TRUE, PlatoonInsideFoyer_EventScript_SetSparxLuxross
	getcaughtmon SPECIES_CRUSTERROR
	call_if_eq VAR_RESULT, TRUE, PlatoonInsideFoyer_EventScript_SetWherml
	getcaughtmon SPECIES_GRACKLIN
	call_if_eq VAR_RESULT, TRUE, PlatoonInsideFoyer_EventScript_SetGrubble
	getcaughtmon SPECIES_FROZFORCE
	call_if_eq VAR_RESULT, TRUE, PlatoonInsideFoyer_EventScript_SetFrozhorn
	getcaughtmon SPECIES_PORYGON2
	call_if_eq VAR_RESULT, TRUE, PlatoonInsideFoyer_EventScript_SetPorybot
	getcaughtmon SPECIES_STOVLARE
	call_if_eq VAR_RESULT, TRUE, PlatoonInsideFoyer_EventScript_SetBaromiteNapalmite
	getcaughtmon SPECIES_HONCHKROW
	call_if_eq VAR_RESULT, TRUE, PlatoonInsideFoyer_EventScript_SetMagekrow
	getcaughtmon SPECIES_WATCHOG
	call_if_eq VAR_RESULT, TRUE, PlatoonInsideFoyer_EventScript_SetPatracle
	getcaughtmon SPECIES_STARMIE
	call_if_eq VAR_RESULT, TRUE, PlatoonInsideFoyer_EventScript_SetStaream
	getcaughtmon SPECIES_POKERLORD
	call_if_eq VAR_RESULT, TRUE, PlatoonInsideFoyer_EventScript_SetCardict
	getcaughtmon SPECIES_BAGHOUL
	call_if_eq VAR_RESULT, TRUE, PlatoonInsideFoyer_EventScript_SetBaghost
	getcaughtmon SPECIES_MISMAGIUS
	call_if_eq VAR_RESULT, TRUE, PlatoonInsideFoyer_EventScript_SetMisdarna
	getcaughtmon SPECIES_GOURGEIST
	call_if_eq VAR_RESULT, TRUE, PlatoonInsideFoyer_EventScript_SetPumpkagoo
	getcaughtmon SPECIES_ARBOK
	call_if_eq VAR_RESULT, TRUE, PlatoonInsideFoyer_EventScript_SetEadipale
	getcaughtmon SPECIES_MALACHREY
	call_if_eq VAR_RESULT, TRUE, PlatoonInsideFoyer_EventScript_SetVeeblen
	getcaughtmon SPECIES_MELCERALBA
	call_if_eq VAR_RESULT, TRUE, PlatoonInsideFoyer_EventScript_SetSweetan
	getcaughtmon SPECIES_RUBIMIZER
	call_if_eq VAR_RESULT, TRUE, PlatoonInsideFoyer_EventScript_SetZappugPupulze
	getcaughtmon SPECIES_CASTERMITE
	call_if_eq VAR_RESULT, TRUE, PlatoonInsideFoyer_EventScript_SetTremiteTrohive
	getcaughtmon SPECIES_DEWGONG
	call_if_eq VAR_RESULT, TRUE, PlatoonInsideFoyer_EventScript_SetDreel
	getcaughtmon SPECIES_BEHOLZER
	call_if_eq VAR_RESULT, TRUE, PlatoonInsideFoyer_EventScript_SetEyeslight
	getcaughtmon SPECIES_ASTIGMORAY
	call_if_eq VAR_RESULT, TRUE, PlatoonInsideFoyer_EventScript_SetEyerishRetineel
	getcaughtmon SPECIES_FORTIFROS
	call_if_eq VAR_RESULT, TRUE, PlatoonInsideFoyer_EventScript_SetRebrrFerrofros
	getcaughtmon SPECIES_CURSOLA
	call_if_eq VAR_RESULT, TRUE, PlatoonInsideFoyer_EventScript_SetCalfsola
	getcaughtmon SPECIES_VIVIDAWG
	call_if_eq VAR_RESULT, TRUE, PlatoonInsideFoyer_EventScript_SetPrismapup
	getcaughtmon SPECIES_BABOBO
	call_if_eq VAR_RESULT, TRUE, PlatoonInsideFoyer_EventScript_SetPanzeehee
	getcaughtmon SPECIES_GREESE
	call_if_eq VAR_RESULT, TRUE, PlatoonInsideFoyer_EventScript_SetGroose
	getcaughtmon SPECIES_DUGTRIO
	call_if_eq VAR_RESULT, TRUE, PlatoonInsideFoyer_EventScript_SetQueglett
	msgbox PlatoonInsideFoyer_Text_CheckYourDexNow, MSGBOX_DEFAULT
	delay 8
	closemessage
	switch VAR_HP_PROGRESS
	case 0, PlatoonInsideFoyer_EventScript_CancelOut
	case 1, PlatoonInsideFoyer_EventScript_CancelOut
	case 2, PlatoonInsideFoyer_EventScript_PrevoCheck50SeenMons
	case 3, PlatoonInsideFoyer_EventScript_PrevoCheck100SeenMons
	case 4, PlatoonInsideFoyer_EventScript_PrevoCheck80CaughtMons
	case 5, PlatoonInsideFoyer_EventScript_PrevoCheck140CaughtMons
	case 6, PlatoonInsideFoyer_EventScript_CancelOut
	release
	end

PlatoonInsideFoyer_EventScript_SetNettata::
	setseenmon SPECIES_RATTATA
	setcaughtmon SPECIES_RATTATA
	return

PlatoonInsideFoyer_EventScript_SetGooper::
	setseenmon SPECIES_GOOPER
	setcaughtmon SPECIES_GOOPER
	return

PlatoonInsideFoyer_EventScript_SetMog::
	setseenmon SPECIES_MOG
	setcaughtmon SPECIES_MOG
	return

PlatoonInsideFoyer_EventScript_SetBakunna::
	setseenmon SPECIES_MUNNA
	setcaughtmon SPECIES_MUNNA
	return

PlatoonInsideFoyer_EventScript_SetParibo::
	setseenmon SPECIES_PARAS
	setcaughtmon SPECIES_PARAS
	return

PlatoonInsideFoyer_EventScript_SetManipursa::
	setseenmon SPECIES_TEDDIURSA
	setcaughtmon SPECIES_TEDDIURSA
	return

PlatoonInsideFoyer_EventScript_SetSappodShelbert::
	setseenmon SPECIES_SAPPOD
	setcaughtmon SPECIES_SAPPOD
	setseenmon SPECIES_SHELBERT
	setcaughtmon SPECIES_SHELBERT
	return

PlatoonInsideFoyer_EventScript_SetPlaintain::
	setseenmon SPECIES_PLAINTAIN
	setcaughtmon SPECIES_PLAINTAIN
	return

PlatoonInsideFoyer_EventScript_SetKelppy::
	setseenmon SPECIES_KELPPY
	setcaughtmon SPECIES_KELPPY
	return

PlatoonInsideFoyer_EventScript_SetShroomoinkSporke::
	setseenmon SPECIES_SHROOMOINK
	setcaughtmon SPECIES_SHROOMOINK
	setseenmon SPECIES_SPORKE
	setcaughtmon SPECIES_SPORKE
	return

PlatoonInsideFoyer_EventScript_SetGulgan::
	setseenmon SPECIES_GULPIN
	setcaughtmon SPECIES_GULPIN
	return

PlatoonInsideFoyer_EventScript_SetCacolanter::
	setseenmon SPECIES_CACNEA
	setcaughtmon SPECIES_CACNEA
	return

PlatoonInsideFoyer_EventScript_SetBurstadBlastoad::
	setseenmon SPECIES_BURSTAD
	setcaughtmon SPECIES_BURSTAD
	setseenmon SPECIES_BLASTOAD
	setcaughtmon SPECIES_BLASTOAD
	return

PlatoonInsideFoyer_EventScript_SetTentangle::
	setseenmon SPECIES_TANGELA
	setcaughtmon SPECIES_TANGELA
	return

PlatoonInsideFoyer_EventScript_SetRalseaCliolia::
	setseenmon SPECIES_RALTS
	setcaughtmon SPECIES_RALTS
	setseenmon SPECIES_KIRLIA
	setcaughtmon SPECIES_KIRLIA
	return

PlatoonInsideFoyer_EventScript_SetPyukumuku::
	setseenmon SPECIES_PYUKUMUKU
	setcaughtmon SPECIES_PYUKUMUKU
	return

PlatoonInsideFoyer_EventScript_SetDullsod::
	setseenmon SPECIES_DULLSOD
	setcaughtmon SPECIES_DULLSOD
	return

PlatoonInsideFoyer_EventScript_SetWattl::
	setseenmon SPECIES_WATTL
	setcaughtmon SPECIES_WATTL
	return

PlatoonInsideFoyer_EventScript_SetSparxLuxross::
	setseenmon SPECIES_TYNAMO
	setcaughtmon SPECIES_TYNAMO
	setseenmon SPECIES_EELEKTRIK
	setcaughtmon SPECIES_EELEKTRIK
	return

PlatoonInsideFoyer_EventScript_SetWherml::
	setseenmon SPECIES_WHERML
	setcaughtmon SPECIES_WHERML
	return

PlatoonInsideFoyer_EventScript_SetGrubble::
	setseenmon SPECIES_GRUBBLE
	setcaughtmon SPECIES_GRUBBLE
	return

PlatoonInsideFoyer_EventScript_SetFrozhorn::
	setseenmon SPECIES_FROZHORN
	setcaughtmon SPECIES_FROZHORN
	return

PlatoonInsideFoyer_EventScript_SetPorybot::
	setseenmon SPECIES_PORYGON
	setcaughtmon SPECIES_PORYGON
	return

PlatoonInsideFoyer_EventScript_SetBaromiteNapalmite::
	setseenmon SPECIES_BAROMITE
	setcaughtmon SPECIES_BAROMITE
	setseenmon SPECIES_NAPALMITE
	setcaughtmon SPECIES_NAPALMITE
	return

PlatoonInsideFoyer_EventScript_SetMagekrow::
	setseenmon SPECIES_MURKROW
	setcaughtmon SPECIES_MURKROW
	return

PlatoonInsideFoyer_EventScript_SetPatracle::
	setseenmon SPECIES_PATRAT
	setcaughtmon SPECIES_PATRAT
	return

PlatoonInsideFoyer_EventScript_SetStaream::
	setseenmon SPECIES_STARYU
	setcaughtmon SPECIES_STARYU
	return

PlatoonInsideFoyer_EventScript_SetCardict::
	setseenmon SPECIES_CARDICT
	setcaughtmon SPECIES_CARDICT
	return

PlatoonInsideFoyer_EventScript_SetBaghost::
	setseenmon SPECIES_BAGHOST
	setcaughtmon SPECIES_BAGHOST
	return

PlatoonInsideFoyer_EventScript_SetMisdarna::
	setseenmon SPECIES_MISDREAVUS
	setcaughtmon SPECIES_MISDREAVUS
	return

PlatoonInsideFoyer_EventScript_SetPumpkagoo::
	setseenmon SPECIES_PUMPKABOO
	setcaughtmon SPECIES_PUMPKABOO
	return

PlatoonInsideFoyer_EventScript_SetEadipale::
	setseenmon SPECIES_EKANS
	setcaughtmon SPECIES_EKANS
	return

PlatoonInsideFoyer_EventScript_SetVeeblen::
	setseenmon SPECIES_VEEBLEN
	setcaughtmon SPECIES_VEEBLEN
	return

PlatoonInsideFoyer_EventScript_SetSweetan::
	setseenmon SPECIES_SWEETAN
	setcaughtmon SPECIES_SWEETAN
	return

PlatoonInsideFoyer_EventScript_SetZappugPupulze::
	setseenmon SPECIES_ZAPPUG
	setcaughtmon SPECIES_ZAPPUG
	setseenmon SPECIES_PUPULZE
	setcaughtmon SPECIES_PUPULZE
	return

PlatoonInsideFoyer_EventScript_SetTremiteTrohive::
	setseenmon SPECIES_TREMITE
	setcaughtmon SPECIES_TREMITE
	setseenmon SPECIES_TROHIVE
	setcaughtmon SPECIES_TROHIVE
	return

PlatoonInsideFoyer_EventScript_SetDreel::
	setseenmon SPECIES_SEEL
	setcaughtmon SPECIES_SEEL
	return

PlatoonInsideFoyer_EventScript_SetEyeslight::
	setseenmon SPECIES_EYESLIGHT
	setcaughtmon SPECIES_EYESLIGHT
	return

PlatoonInsideFoyer_EventScript_SetEyerishRetineel::
	setseenmon SPECIES_EYERISH
	setcaughtmon SPECIES_EYERISH
	setseenmon SPECIES_RETINEEL
	setcaughtmon SPECIES_RETINEEL
	return

PlatoonInsideFoyer_EventScript_SetRebrrFerrofros::
	setseenmon SPECIES_REBRR
	setcaughtmon SPECIES_REBRR
	setseenmon SPECIES_FERROFROS
	setcaughtmon SPECIES_FERROFROS
	return

PlatoonInsideFoyer_EventScript_SetCalfsola::
	setseenmon SPECIES_CORSOLA
	setcaughtmon SPECIES_CORSOLA
	return

PlatoonInsideFoyer_EventScript_SetPrismapup::
	setseenmon SPECIES_PRISMAPUP
	setcaughtmon SPECIES_PRISMAPUP
	return

PlatoonInsideFoyer_EventScript_SetPanzeehee::
	setseenmon SPECIES_PANZEEHEE
	setcaughtmon SPECIES_PANZEEHEE
	return

PlatoonInsideFoyer_EventScript_SetGroose::
	setseenmon SPECIES_GROOSE
	setcaughtmon SPECIES_GROOSE
	return

PlatoonInsideFoyer_EventScript_SetQueglett::
	setseenmon SPECIES_DIGLETT
	setcaughtmon SPECIES_DIGLETT
	return

PlatoonInsideFoyer_EventScript_Purplina::
	lock
	faceplayer
	goto_if_set FLAG_HP_UNLOCKED_MUSEUM, PlatoonInsideFoyer_EventScript_GateAlreadyOpen
	goto_if_lt VAR_HP_PROGRESS, 6, PlatoonInsideFoyer_EventScript_MuseumLocked
	msgbox PlatoonInsideFoyer_Text_LetMeOpenTheGate, MSGBOX_DEFAULT
	goto PlatoonInsideFoyer_EventScript_OpenMuseumGateFirstTime
	release
	end

PlatoonInsideFoyer_EventScript_MuseumLocked::
	msgbox PlatoonInsideFoyer_Text_Scram, MSGBOX_AUTOCLOSE
	release
	end	

PlatoonInsideFoyer_EventScript_GateAlreadyOpen::
	msgbox PlatoonInsideFoyer_Text_GateAlreadyOpen, MSGBOX_AUTOCLOSE
	release
	end	

PlatoonInsideFoyer_EventScript_OpenMuseumGateFirstTime::
	closemessage
	setmetatile 24, 5, METATILE_TrainerHill_WithoutDoor, FALSE
	special DrawWholeMapView
	setflag FLAG_HP_UNLOCKED_MUSEUM
	playse SE_UNLOCK
	waitse
	release
	end

PlatoonInsideFoyer_EventScript_FanClubGuard::
	msgbox PlatoonInsideFoyer_Text_FanClubClosed, MSGBOX_NPC
	end

PlatoonInsideFoyer_EventScript_WantToGetInMuseum::
	msgbox PlatoonInsideFoyer_Text_WantToGetInMuseum, MSGBOX_NPC
	end

PlatoonInsideFoyer_EventScript_SleepRest::
	msgbox PlatoonInsideFoyer_Text_SleepRest, MSGBOX_NPC
	end

PlatoonInsideFoyer_EventScript_SuperEffectiveSTAB::
	msgbox PlatoonInsideFoyer_Text_SuperEffectiveSTAB, MSGBOX_NPC
	end

PlatoonInsideFoyer_EventScript_DragonType::
	msgbox PlatoonInsideFoyer_Text_DragonType, MSGBOX_NPC
	end

PlatoonInsideFoyer_EventScript_IceRelatedThings::
	msgbox PlatoonInsideFoyer_Text_IceRelatedThings, MSGBOX_NPC
	end

PlatoonInsideFoyer_EventScript_CosmicType::
	msgbox PlatoonInsideFoyer_Text_CosmicType, MSGBOX_NPC
	end

PlatoonInsideFoyer_EventScript_GreasyType::
	msgbox PlatoonInsideFoyer_Text_GreasyType, MSGBOX_NPC
	end

PlatoonInsideFoyer_EventScript_RubberType::
	msgbox PlatoonInsideFoyer_Text_RubberType, MSGBOX_NPC
	end

PlatoonInsideFoyer_EventScript_RelicType::
	msgbox PlatoonInsideFoyer_Text_RelicType, MSGBOX_NPC
	end

PlatoonInsideFoyer_EventScript_BeastType::
	msgbox PlatoonInsideFoyer_Text_BeastType, MSGBOX_NPC
	end

PlatoonInsideFoyer_EventScript_FormChanges::
	msgbox PlatoonInsideFoyer_Text_FormChanges, MSGBOX_NPC
	end

PlatoonInsideFoyer_EventScript_LanetteIdle::
	lock
	faceplayer
	goto_if_eq VAR_HP_PROGRESS, 0, PlatoonInsideFoyer_EventScript_LanettePreStart
	goto_if_eq VAR_HP_PROGRESS, 6, PlatoonInsideFoyer_EventScript_LanetteEndgame
	speakername PlatoonInsideFoyer_Text_NameLanette
	msgbox PlatoonInsideFoyer_Text_HelloTawila, MSGBOX_AUTOCLOSE
	release
	end

PlatoonInsideFoyer_EventScript_LanettePreStart::
	msgbox PlatoonInsideFoyer_Text_LanetteBusy, MSGBOX_AUTOCLOSE
	release
	end	

PlatoonInsideFoyer_EventScript_LanetteEndgame::
	speakername PlatoonInsideFoyer_Text_NameLanette
	msgbox PlatoonInsideFoyer_Text_LanetteEnd, MSGBOX_AUTOCLOSE
	release
	end	

PlatoonInsideFoyer_EventScript_TerminalBepisClove::
	lock
	playse SE_PC_LOGIN
	msgbox PlatoonInsideFoyer_Text_Terminal, MSGBOX_DEFAULT
	multichoice 19, 4, MULTI_MUSEUM_BEPIS_CLOVE, FALSE
	copyvar VAR_TEMP_1, VAR_RESULT
	switch VAR_TEMP_1
	case 0, PlatoonInsideFoyer_EventScript_DevLoreMusalord
	case 1, PlatoonInsideFoyer_EventScript_DevLoreExpload
	case 2, PlatoonInsideFoyer_EventScript_DevLorePorybot
	case 3, PlatoonInsideFoyer_EventScript_DevLoreVerglazard
	closemessage
	playse SE_PC_OFF
	release
	end

PlatoonInsideFoyer_EventScript_DevLoreMusalord::
	showmonpic SPECIES_MUSALORD, 10, 3
	msgbox PlatoonInsideFoyer_Text_DevLoreMusalord, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	playse SE_PC_OFF
	waitse
	release
	end

PlatoonInsideFoyer_EventScript_DevLoreExpload::
	showmonpic SPECIES_EXPLOAD, 10, 3
	msgbox PlatoonInsideFoyer_Text_DevLoreExpload, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	playse SE_PC_OFF
	waitse
	release
	end

PlatoonInsideFoyer_EventScript_DevLorePorybot::
	showmonpic SPECIES_PORYGON2, 10, 3
	msgbox PlatoonInsideFoyer_Text_DevLorePorybot, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	playse SE_PC_OFF
	waitse
	release
	end

PlatoonInsideFoyer_EventScript_DevLoreVerglazard::
	showmonpic SPECIES_CHARIZARD, 10, 3
	msgbox PlatoonInsideFoyer_Text_DevLoreVerglazard, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	playse SE_PC_OFF
	waitse
	release
	end

PlatoonInsideFoyer_EventScript_TerminalBonzo::
	lock
	playse SE_PC_LOGIN
	msgbox PlatoonInsideFoyer_Text_Terminal, MSGBOX_DEFAULT
	multichoice 19, 4, MULTI_MUSEUM_BONZO, FALSE
	copyvar VAR_TEMP_1, VAR_RESULT
	switch VAR_TEMP_1
	case 0, PlatoonInsideFoyer_EventScript_DevLoreBrevato
	case 1, PlatoonInsideFoyer_EventScript_DevLoreGravendor
	case 2, PlatoonInsideFoyer_EventScript_DevLoreShamburger
	closemessage
	playse SE_PC_OFF
	release
	end

PlatoonInsideFoyer_EventScript_DevLoreBrevato::
	showmonpic SPECIES_BREVATO, 10, 3
	msgbox PlatoonInsideFoyer_Text_DevLoreBrevato, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	playse SE_PC_OFF
	waitse
	release
	end

PlatoonInsideFoyer_EventScript_DevLoreGravendor::
	showmonpic SPECIES_GRAVENDOR, 10, 3
	msgbox PlatoonInsideFoyer_Text_DevLoreGravendor, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	playse SE_PC_OFF
	waitse
	release
	end

PlatoonInsideFoyer_EventScript_DevLoreShamburger::
	showmonpic SPECIES_SHAMBURGER, 10, 3
	msgbox PlatoonInsideFoyer_Text_DevLoreShamburger, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	playse SE_PC_OFF
	waitse
	release
	end

PlatoonInsideFoyer_EventScript_TerminalCeladonk::
	lock
	playse SE_PC_LOGIN
	msgbox PlatoonInsideFoyer_Text_Terminal, MSGBOX_DEFAULT
	multichoice 19, 4, MULTI_MUSEUM_CELADONK, FALSE
	copyvar VAR_TEMP_1, VAR_RESULT
	switch VAR_TEMP_1
	case 0, PlatoonInsideFoyer_EventScript_DevLoreSwisquire
	case 1, PlatoonInsideFoyer_EventScript_DevLoreNinown
	case 2, PlatoonInsideFoyer_EventScript_DevLorePeckachew
	closemessage
	playse SE_PC_OFF
	release
	end

PlatoonInsideFoyer_EventScript_DevLoreSwisquire::
	showmonpic SPECIES_SWISQUIRE, 10, 3
	msgbox PlatoonInsideFoyer_Text_DevLoreSwisquire, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	playse SE_PC_OFF
	waitse
	release
	end

PlatoonInsideFoyer_EventScript_DevLoreNinown::
	showmonpic SPECIES_NINOWN, 10, 3
	msgbox PlatoonInsideFoyer_Text_DevLoreNinown, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	playse SE_PC_OFF
	waitse
	release
	end

PlatoonInsideFoyer_EventScript_DevLorePeckachew::
	showmonpic SPECIES_PECKACHEW, 10, 3
	msgbox PlatoonInsideFoyer_Text_DevLorePeckachew, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	playse SE_PC_OFF
	waitse
	release
	end

PlatoonInsideFoyer_EventScript_TerminalChairry::
	lock
	playse SE_PC_LOGIN
	msgbox PlatoonInsideFoyer_Text_Terminal, MSGBOX_DEFAULT
	multichoice 19, 4, MULTI_MUSEUM_CHAIR, FALSE
	copyvar VAR_TEMP_1, VAR_RESULT
	switch VAR_TEMP_1
	case 0, PlatoonInsideFoyer_EventScript_DevLoreGracklin
	case 1, PlatoonInsideFoyer_EventScript_DevLoreStovlare
	case 2, PlatoonInsideFoyer_EventScript_DevLoreAstigmoray
	case 3, PlatoonInsideFoyer_EventScript_DevLoreSkooky
	closemessage
	playse SE_PC_OFF
	release
	end

PlatoonInsideFoyer_EventScript_DevLoreGracklin::
	showmonpic SPECIES_GRACKLIN, 10, 3
	msgbox PlatoonInsideFoyer_Text_DevLoreGracklin, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	playse SE_PC_OFF
	waitse
	release
	end

PlatoonInsideFoyer_EventScript_DevLoreStovlare::
	showmonpic SPECIES_STOVLARE, 10, 3
	msgbox PlatoonInsideFoyer_Text_DevLoreStovlare, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	playse SE_PC_OFF
	waitse
	release
	end

PlatoonInsideFoyer_EventScript_DevLoreAstigmoray::
	showmonpic SPECIES_ASTIGMORAY, 10, 3
	msgbox PlatoonInsideFoyer_Text_DevLoreAstigmoray, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	playse SE_PC_OFF
	waitse
	release
	end

PlatoonInsideFoyer_EventScript_DevLoreSkooky::
	showmonpic SPECIES_SKOOKY, 10, 3
	msgbox PlatoonInsideFoyer_Text_DevLoreSkooky, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	playse SE_PC_OFF
	waitse
	release
	end

PlatoonInsideFoyer_EventScript_TerminalDahlia::
	lock
	playse SE_PC_LOGIN
	msgbox PlatoonInsideFoyer_Text_Terminal, MSGBOX_DEFAULT
	multichoice 19, 4, MULTI_MUSEUM_DAHLIA, FALSE
	copyvar VAR_TEMP_1, VAR_RESULT
	switch VAR_TEMP_1
	case 0, PlatoonInsideFoyer_EventScript_DevLoreShelebrate
	case 1, PlatoonInsideFoyer_EventScript_DevLoreOrbacle
	case 2, PlatoonInsideFoyer_EventScript_DevLoreWuvme
	closemessage
	playse SE_PC_OFF
	release
	end

PlatoonInsideFoyer_EventScript_DevLoreShelebrate::
	showmonpic SPECIES_SHELEBRATE, 10, 3
	msgbox PlatoonInsideFoyer_Text_DevLoreShelebrate, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	playse SE_PC_OFF
	waitse
	release
	end

PlatoonInsideFoyer_EventScript_DevLoreOrbacle::
	showmonpic SPECIES_ORBACLE, 10, 3
	msgbox PlatoonInsideFoyer_Text_DevLoreOrbacle, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	playse SE_PC_OFF
	waitse
	release
	end

PlatoonInsideFoyer_EventScript_DevLoreWuvme::
	showmonpic SPECIES_WUVME, 10, 3
	msgbox PlatoonInsideFoyer_Text_DevLoreWuvme, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	playse SE_PC_OFF
	waitse
	release
	end

PlatoonInsideFoyer_EventScript_TerminalDahViper::
	lock
	playse SE_PC_LOGIN
	msgbox PlatoonInsideFoyer_Text_Terminal, MSGBOX_DEFAULT
	multichoice 19, 4, MULTI_MUSEUM_DAHVIPER, FALSE
	copyvar VAR_TEMP_1, VAR_RESULT
	switch VAR_TEMP_1
	case 0, PlatoonInsideFoyer_EventScript_DevLorePlantatori
	case 1, PlatoonInsideFoyer_EventScript_DevLoreDegourge
	case 2, PlatoonInsideFoyer_EventScript_DevLoreGelebrum
	closemessage
	playse SE_PC_OFF
	release
	end

PlatoonInsideFoyer_EventScript_DevLorePlantatori::
	showmonpic SPECIES_PLANTATORI, 10, 3
	msgbox PlatoonInsideFoyer_Text_DevLorePlantatori, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	playse SE_PC_OFF
	waitse
	release
	end

PlatoonInsideFoyer_EventScript_DevLoreDegourge::
	showmonpic SPECIES_DEGOURGE, 10, 3
	msgbox PlatoonInsideFoyer_Text_DevLoreDegourge, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	playse SE_PC_OFF
	waitse
	release
	end

PlatoonInsideFoyer_EventScript_DevLoreGelebrum::
	showmonpic SPECIES_GELECTUAL, 10, 3
	msgbox PlatoonInsideFoyer_Text_DevLoreGelebrum, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	playse SE_PC_OFF
	waitse
	release
	end

PlatoonInsideFoyer_EventScript_TerminalEggDill::
	lock
	playse SE_PC_LOGIN
	msgbox PlatoonInsideFoyer_Text_Terminal, MSGBOX_DEFAULT
	multichoice 19, 4, MULTI_MUSEUM_EGG_DILL, FALSE
	copyvar VAR_TEMP_1, VAR_RESULT
	switch VAR_TEMP_1
	case 0, PlatoonInsideFoyer_EventScript_DevLoreStuntisla
	case 1, PlatoonInsideFoyer_EventScript_DevLoreWakasuka
	case 2, PlatoonInsideFoyer_EventScript_DevLoreMantacore
	case 3, PlatoonInsideFoyer_EventScript_DevLoreRegiwyrm
	closemessage
	playse SE_PC_OFF
	release
	end

PlatoonInsideFoyer_EventScript_DevLoreStuntisla::
	showmonpic SPECIES_STUNTISLA, 10, 3
	msgbox PlatoonInsideFoyer_Text_DevLoreStuntisla, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	playse SE_PC_OFF
	waitse
	release
	end

PlatoonInsideFoyer_EventScript_DevLoreWakasuka::
	showmonpic SPECIES_WAKASUKA, 10, 3
	msgbox PlatoonInsideFoyer_Text_DevLoreWakasuka, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	playse SE_PC_OFF
	waitse
	release
	end

PlatoonInsideFoyer_EventScript_DevLoreMantacore::
	showmonpic SPECIES_MANTACORE, 10, 3
	msgbox PlatoonInsideFoyer_Text_DevLoreMantacore, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	playse SE_PC_OFF
	waitse
	release
	end

PlatoonInsideFoyer_EventScript_DevLoreRegiwyrm::
	showmonpic SPECIES_REGIDRAGO, 10, 3
	msgbox PlatoonInsideFoyer_Text_DevLoreRegiwyrm, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	playse SE_PC_OFF
	waitse
	release
	end

PlatoonInsideFoyer_EventScript_TerminalAltermon::
	lock
	playse SE_PC_LOGIN
	msgbox PlatoonInsideFoyer_Text_Terminal, MSGBOX_DEFAULT
	multichoice 19, 4, MULTI_MUSEUM_ALTERMON, FALSE
	copyvar VAR_TEMP_1, VAR_RESULT
	switch VAR_TEMP_1
	case 0, PlatoonInsideFoyer_EventScript_DevLoreCapybarna
	case 1, PlatoonInsideFoyer_EventScript_DevLoreParakuri
	case 2, PlatoonInsideFoyer_EventScript_DevLoreRalsea
	case 3, PlatoonInsideFoyer_EventScript_DevLoreChakraring
	closemessage
	playse SE_PC_OFF
	release
	end

PlatoonInsideFoyer_EventScript_DevLoreCapybarna::
	showmonpic SPECIES_MUSHARNA, 10, 3
	msgbox PlatoonInsideFoyer_Text_DevLoreCapybarna, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	playse SE_PC_OFF
	waitse
	release
	end

PlatoonInsideFoyer_EventScript_DevLoreParakuri::
	showmonpic SPECIES_PARASECT, 10, 3
	msgbox PlatoonInsideFoyer_Text_DevLoreParakuri, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	playse SE_PC_OFF
	waitse
	release
	end

PlatoonInsideFoyer_EventScript_DevLoreRalsea::
	showmonpic SPECIES_RALTS, 10, 3
	msgbox PlatoonInsideFoyer_Text_DevLoreRalsea, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	playse SE_PC_OFF
	waitse
	release
	end

PlatoonInsideFoyer_EventScript_DevLoreChakraring::
	showmonpic SPECIES_URSARING, 10, 3
	msgbox PlatoonInsideFoyer_Text_DevLoreChakraring, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	playse SE_PC_OFF
	waitse
	release
	end

PlatoonInsideFoyer_EventScript_TerminalEeveeEe::
	lock
	playse SE_PC_LOGIN
	msgbox PlatoonInsideFoyer_Text_Terminal, MSGBOX_DEFAULT
	multichoice 19, 4, MULTI_MUSEUM_EEVEEEE, FALSE
	copyvar VAR_TEMP_1, VAR_RESULT
	switch VAR_TEMP_1
	case 0, PlatoonInsideFoyer_EventScript_DevLoreHagoosh
	case 1, PlatoonInsideFoyer_EventScript_DevLoreGoogeist
	case 2, PlatoonInsideFoyer_EventScript_DevLoreDragong
	closemessage
	playse SE_PC_OFF
	release
	end

PlatoonInsideFoyer_EventScript_DevLoreHagoosh::
	showmonpic SPECIES_HAGOOSH_VISCOUS, 10, 3
	msgbox PlatoonInsideFoyer_Text_DevLoreHagoosh, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	playse SE_PC_OFF
	waitse
	release
	end

PlatoonInsideFoyer_EventScript_DevLoreGoogeist::
	showmonpic SPECIES_GOURGEIST, 10, 3
	msgbox PlatoonInsideFoyer_Text_DevLoreGoogeist, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	playse SE_PC_OFF
	waitse
	release
	end

PlatoonInsideFoyer_EventScript_DevLoreDragong::
	showmonpic SPECIES_DEWGONG, 10, 3
	msgbox PlatoonInsideFoyer_Text_DevLoreDragong, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	playse SE_PC_OFF
	waitse
	release
	end

PlatoonInsideFoyer_EventScript_TerminalEnwaitea::
	lock
	playse SE_PC_LOGIN
	msgbox PlatoonInsideFoyer_Text_Terminal, MSGBOX_DEFAULT
	multichoice 19, 4, MULTI_MUSEUM_ENWAITEA, FALSE
	copyvar VAR_TEMP_1, VAR_RESULT
	switch VAR_TEMP_1
	case 0, PlatoonInsideFoyer_EventScript_DevLoreWyrmWing
	case 1, PlatoonInsideFoyer_EventScript_DevLoreCoorse
	case 2, PlatoonInsideFoyer_EventScript_DevLoreKittepup
	closemessage
	playse SE_PC_OFF
	release
	end

PlatoonInsideFoyer_EventScript_DevLoreWyrmWing::
	showmonpic SPECIES_VOLCARONA, 10, 3
	msgbox PlatoonInsideFoyer_Text_DevLoreWyrmWing, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	playse SE_PC_OFF
	waitse
	release
	end

PlatoonInsideFoyer_EventScript_DevLoreCoorse::
	showmonpic SPECIES_CURSOLA, 10, 3
	msgbox PlatoonInsideFoyer_Text_DevLoreCoorse, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	playse SE_PC_OFF
	waitse
	release
	end

PlatoonInsideFoyer_EventScript_DevLoreKittepup::
	showmonpic SPECIES_KITTEPUP, 10, 3
	msgbox PlatoonInsideFoyer_Text_DevLoreKittepup, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	playse SE_PC_OFF
	waitse
	release
	end

PlatoonInsideFoyer_EventScript_TerminalFBI::
	lock
	playse SE_PC_LOGIN
	msgbox PlatoonInsideFoyer_Text_Terminal, MSGBOX_DEFAULT
	multichoice 19, 4, MULTI_MUSEUM_FBI, FALSE
	copyvar VAR_TEMP_1, VAR_RESULT
	switch VAR_TEMP_1
	case 0, PlatoonInsideFoyer_EventScript_DevLoreChernoboar
	case 1, PlatoonInsideFoyer_EventScript_DevLoreIcandesfen
	case 2, PlatoonInsideFoyer_EventScript_DevLoreCastermite
	closemessage
	playse SE_PC_OFF
	release
	end

PlatoonInsideFoyer_EventScript_DevLoreChernoboar::
	showmonpic SPECIES_CHERNOBOAR, 10, 3
	msgbox PlatoonInsideFoyer_Text_DevLoreChernoboar, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	playse SE_PC_OFF
	waitse
	release
	end

PlatoonInsideFoyer_EventScript_DevLoreIcandesfen::
	showmonpic SPECIES_ICANDESFEN, 10, 3
	msgbox PlatoonInsideFoyer_Text_DevLoreIcandesfen, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	playse SE_PC_OFF
	waitse
	release
	end

PlatoonInsideFoyer_EventScript_DevLoreCastermite::
	showmonpic SPECIES_CASTERMITE, 10, 3
	msgbox PlatoonInsideFoyer_Text_DevLoreCastermite, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	playse SE_PC_OFF
	waitse
	release
	end

PlatoonInsideFoyer_EventScript_TerminalGaboTy::
	lock
	playse SE_PC_LOGIN
	msgbox PlatoonInsideFoyer_Text_Terminal, MSGBOX_DEFAULT
	multichoice 19, 4, MULTI_MUSEUM_GABO_TY, FALSE
	copyvar VAR_TEMP_1, VAR_RESULT
	switch VAR_TEMP_1
	case 0, PlatoonInsideFoyer_EventScript_DevLoreCelshrioom
	case 1, PlatoonInsideFoyer_EventScript_DevLoreSeraphure
	case 2, PlatoonInsideFoyer_EventScript_DevLoreTuetuerror
	case 3, PlatoonInsideFoyer_EventScript_DevLoreMagidash
	closemessage
	playse SE_PC_OFF
	release
	end

PlatoonInsideFoyer_EventScript_DevLoreCelshrioom::
	showmonpic SPECIES_CELSHRIOOM, 10, 3
	msgbox PlatoonInsideFoyer_Text_DevLoreCelshrioom, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	playse SE_PC_OFF
	waitse
	release
	end

PlatoonInsideFoyer_EventScript_DevLoreSeraphure::
	showmonpic SPECIES_SERAPHURE, 10, 3
	msgbox PlatoonInsideFoyer_Text_DevLoreSeraphure, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	playse SE_PC_OFF
	waitse
	release
	end

PlatoonInsideFoyer_EventScript_DevLoreTuetuerror::
	showmonpic SPECIES_TUETUERROR, 10, 3
	msgbox PlatoonInsideFoyer_Text_DevLoreTuetuerror, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	playse SE_PC_OFF
	waitse
	release
	end

PlatoonInsideFoyer_EventScript_DevLoreMagidash::
	showmonpic SPECIES_MAGIDASH, 10, 3
	msgbox PlatoonInsideFoyer_Text_DevLoreMagidash, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	playse SE_PC_OFF
	waitse
	release
	end

PlatoonInsideFoyer_EventScript_TerminalKyuDoodle::
	lock
	playse SE_PC_LOGIN
	msgbox PlatoonInsideFoyer_Text_Terminal, MSGBOX_DEFAULT
	multichoice 19, 4, MULTI_MUSEUM_KYU_DOODLE, FALSE
	copyvar VAR_TEMP_1, VAR_RESULT
	switch VAR_TEMP_1
	case 0, PlatoonInsideFoyer_EventScript_DevLoreLuxstrobe
	case 1, PlatoonInsideFoyer_EventScript_DevLoreStarror
	case 2, PlatoonInsideFoyer_EventScript_DevLoreMiscladrus
	case 3, PlatoonInsideFoyer_EventScript_DevLoreSkuldugery
	closemessage
	playse SE_PC_OFF
	release
	end

PlatoonInsideFoyer_EventScript_DevLoreLuxstrobe::
	showmonpic SPECIES_EELEKTROSS, 10, 3
	msgbox PlatoonInsideFoyer_Text_DevLoreLuxstrobe, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	playse SE_PC_OFF
	waitse
	release
	end

PlatoonInsideFoyer_EventScript_DevLoreStarror::
	showmonpic SPECIES_STARMIE, 10, 3
	msgbox PlatoonInsideFoyer_Text_DevLoreStarror, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	playse SE_PC_OFF
	waitse
	release
	end

PlatoonInsideFoyer_EventScript_DevLoreMiscladrus::
	showmonpic SPECIES_MISMAGIUS, 10, 3
	msgbox PlatoonInsideFoyer_Text_DevLoreMiscladrus, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	playse SE_PC_OFF
	waitse
	release
	end

PlatoonInsideFoyer_EventScript_DevLoreSkuldugery::
	showmonpic SPECIES_SKULDUGERY, 10, 3
	msgbox PlatoonInsideFoyer_Text_DevLoreSkuldugery, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	playse SE_PC_OFF
	waitse
	release
	end

PlatoonInsideFoyer_EventScript_TerminalLichen::
	lock
	playse SE_PC_LOGIN
	msgbox PlatoonInsideFoyer_Text_Terminal, MSGBOX_DEFAULT
	multichoice 19, 4, MULTI_MUSEUM_LICHEN, FALSE
	copyvar VAR_TEMP_1, VAR_RESULT
	switch VAR_TEMP_1
	case 0, PlatoonInsideFoyer_EventScript_DevLoreOddiowave
	case 1, PlatoonInsideFoyer_EventScript_DevLoreBeholzer
	case 2, PlatoonInsideFoyer_EventScript_DevLoreVividawg
	closemessage
	playse SE_PC_OFF
	release
	end

PlatoonInsideFoyer_EventScript_DevLoreOddiowave::
	showmonpic SPECIES_ODDIOWAVE, 10, 3
	msgbox PlatoonInsideFoyer_Text_DevLoreOddiowave, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	playse SE_PC_OFF
	waitse
	release
	end

PlatoonInsideFoyer_EventScript_DevLoreBeholzer::
	showmonpic SPECIES_BEHOLZER, 10, 3
	msgbox PlatoonInsideFoyer_Text_DevLoreBeholzer, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	playse SE_PC_OFF
	waitse
	release
	end

PlatoonInsideFoyer_EventScript_DevLoreVividawg::
	showmonpic SPECIES_VIVIDAWG, 10, 3
	msgbox PlatoonInsideFoyer_Text_DevLoreVividawg, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	playse SE_PC_OFF
	waitse
	release
	end

PlatoonInsideFoyer_EventScript_TerminalHydroBlue::
	lock
	playse SE_PC_LOGIN
	msgbox PlatoonInsideFoyer_Text_Terminal, MSGBOX_DEFAULT
	multichoice 19, 4, MULTI_MUSEUM_HYDROBLUE, FALSE
	copyvar VAR_TEMP_1, VAR_RESULT
	switch VAR_TEMP_1
	case 0, PlatoonInsideFoyer_EventScript_DevLoreSwalheart
	case 1, PlatoonInsideFoyer_EventScript_DevLoreCaclequin
	case 2, PlatoonInsideFoyer_EventScript_DevLoreGramkrow
	case 3, PlatoonInsideFoyer_EventScript_DevLoreIntriobang
	closemessage
	playse SE_PC_OFF
	release
	end

PlatoonInsideFoyer_EventScript_DevLoreSwalheart::
	showmonpic SPECIES_SWALOT, 10, 3
	msgbox PlatoonInsideFoyer_Text_DevLoreSwalheart, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	playse SE_PC_OFF
	waitse
	release
	end

PlatoonInsideFoyer_EventScript_DevLoreCaclequin::
	showmonpic SPECIES_CACTURNE, 10, 3
	msgbox PlatoonInsideFoyer_Text_DevLoreCaclequin, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	playse SE_PC_OFF
	waitse
	release
	end

PlatoonInsideFoyer_EventScript_DevLoreGramkrow::
	showmonpic SPECIES_HONCHKROW, 10, 3
	msgbox PlatoonInsideFoyer_Text_DevLoreGramkrow, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	playse SE_PC_OFF
	waitse
	release
	end

PlatoonInsideFoyer_EventScript_DevLoreIntriobang::
	showmonpic SPECIES_DUGTRIO, 10, 3
	msgbox PlatoonInsideFoyer_Text_DevLoreIntriobang, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	playse SE_PC_OFF
	waitse
	release
	end

PlatoonInsideFoyer_EventScript_TerminalLivra::
	lock
	playse SE_PC_LOGIN
	msgbox PlatoonInsideFoyer_Text_Terminal, MSGBOX_DEFAULT
	multichoice 19, 4, MULTI_MUSEUM_LIVRA, FALSE
	copyvar VAR_TEMP_1, VAR_RESULT
	switch VAR_TEMP_1
	case 0, PlatoonInsideFoyer_EventScript_DevLoreOkkamirizo
	case 1, PlatoonInsideFoyer_EventScript_DevLoreFrozforce
	case 2, PlatoonInsideFoyer_EventScript_DevLoreRickshawty
	case 3, PlatoonInsideFoyer_EventScript_DevLoreVizaaviso
	closemessage
	playse SE_PC_OFF
	release
	end

PlatoonInsideFoyer_EventScript_DevLoreOkkamirizo::
	showmonpic SPECIES_OKKAMIRIZO, 10, 3
	msgbox PlatoonInsideFoyer_Text_DevLoreOkkamirizo, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	playse SE_PC_OFF
	waitse
	release
	end

PlatoonInsideFoyer_EventScript_DevLoreFrozforce::
	showmonpic SPECIES_FROZFORCE, 10, 3
	msgbox PlatoonInsideFoyer_Text_DevLoreFrozforce, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	playse SE_PC_OFF
	waitse
	release
	end

PlatoonInsideFoyer_EventScript_DevLoreRickshawty::
	showmonpic SPECIES_RICKSHAWTY_CHARIOT, 10, 3
	msgbox PlatoonInsideFoyer_Text_DevLoreRickshawty, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	playse SE_PC_OFF
	waitse
	release
	end

PlatoonInsideFoyer_EventScript_DevLoreVizaaviso::
	showmonpic SPECIES_VIZAAVISO, 10, 3
	msgbox PlatoonInsideFoyer_Text_DevLoreVizaaviso, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	playse SE_PC_OFF
	waitse
	release
	end

PlatoonInsideFoyer_EventScript_TerminalMemelordFrank::
	lock
	playse SE_PC_LOGIN
	msgbox PlatoonInsideFoyer_Text_Terminal, MSGBOX_DEFAULT
	multichoice 19, 4, MULTI_MUSEUM_MEMELORD_FRANKTURE, FALSE
	copyvar VAR_TEMP_1, VAR_RESULT
	switch VAR_TEMP_1
	case 0, PlatoonInsideFoyer_EventScript_DevLoreCrusterror
	case 1, PlatoonInsideFoyer_EventScript_DevLoreRubimizer
	case 2, PlatoonInsideFoyer_EventScript_DevLoreArctikack
	case 3, PlatoonInsideFoyer_EventScript_DevLoreFrankture
	closemessage
	playse SE_PC_OFF
	release
	end

PlatoonInsideFoyer_EventScript_DevLoreCrusterror::
	showmonpic SPECIES_CRUSTERROR, 10, 3
	msgbox PlatoonInsideFoyer_Text_DevLoreCrusterror, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	playse SE_PC_OFF
	waitse
	release
	end

PlatoonInsideFoyer_EventScript_DevLoreRubimizer::
	showmonpic SPECIES_RUBIMIZER, 10, 3
	msgbox PlatoonInsideFoyer_Text_DevLoreRubimizer, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	playse SE_PC_OFF
	waitse
	release
	end

PlatoonInsideFoyer_EventScript_DevLoreArctikack::
	showmonpic SPECIES_ARCTIKACK, 10, 3
	msgbox PlatoonInsideFoyer_Text_DevLoreArctikack, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	playse SE_PC_OFF
	waitse
	release
	end

PlatoonInsideFoyer_EventScript_DevLoreFrankture::
	showmonpic SPECIES_OGWON_ROCK, 10, 3
	msgbox PlatoonInsideFoyer_Text_DevLoreFrankture, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	playse SE_PC_OFF
	waitse
	release
	end

PlatoonInsideFoyer_EventScript_TerminalOgwon::
	lock
	playse SE_PC_LOGIN
	msgbox PlatoonInsideFoyer_Text_Terminal, MSGBOX_DEFAULT
	multichoice 19, 4, MULTI_MUSEUM_OGWON, FALSE
	copyvar VAR_TEMP_1, VAR_RESULT
	switch VAR_TEMP_1
	case 0, PlatoonInsideFoyer_EventScript_DevLoreProfur
	case 1, PlatoonInsideFoyer_EventScript_DevLoreDadalemma
	case 2, PlatoonInsideFoyer_EventScript_DevLoreBevolpin
	case 3, PlatoonInsideFoyer_EventScript_DevLoreGreese
	closemessage
	playse SE_PC_OFF
	release
	end

PlatoonInsideFoyer_EventScript_DevLoreProfur::
	showmonpic SPECIES_PROFUR, 10, 3
	msgbox PlatoonInsideFoyer_Text_DevLoreProfur, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	playse SE_PC_OFF
	waitse
	release
	end

PlatoonInsideFoyer_EventScript_DevLoreDadalemma::
	showmonpic SPECIES_DADALEMMA, 10, 3
	msgbox PlatoonInsideFoyer_Text_DevLoreDadalemma, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	playse SE_PC_OFF
	waitse
	release
	end

PlatoonInsideFoyer_EventScript_DevLoreBevolpin::
	showmonpic SPECIES_BEVOLPIN, 10, 3
	msgbox PlatoonInsideFoyer_Text_DevLoreBevolpin, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	playse SE_PC_OFF
	waitse
	release
	end

PlatoonInsideFoyer_EventScript_DevLoreGreese::
	showmonpic SPECIES_GREESE, 10, 3
	msgbox PlatoonInsideFoyer_Text_DevLoreGreese, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	playse SE_PC_OFF
	waitse
	release
	end

PlatoonInsideFoyer_EventScript_TerminalPabloPlasto::
	lock
	playse SE_PC_LOGIN
	msgbox PlatoonInsideFoyer_Text_Terminal, MSGBOX_DEFAULT
	multichoice 19, 4, MULTI_MUSEUM_PABLO_PLASTO, FALSE
	copyvar VAR_TEMP_1, VAR_RESULT
	switch VAR_TEMP_1
	case 0, PlatoonInsideFoyer_EventScript_DevLoreCrawtendr
	case 1, PlatoonInsideFoyer_EventScript_DevLoreLurkelp
	case 2, PlatoonInsideFoyer_EventScript_DevLoreBaghoul
	case 3, PlatoonInsideFoyer_EventScript_DevLoreBuggory
	closemessage
	playse SE_PC_OFF
	release
	end

PlatoonInsideFoyer_EventScript_DevLoreCrawtendr::
	showmonpic SPECIES_CRAWTENDR, 10, 3
	msgbox PlatoonInsideFoyer_Text_DevLoreCrawtendr, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	playse SE_PC_OFF
	waitse
	release
	end

PlatoonInsideFoyer_EventScript_DevLoreLurkelp::
	showmonpic SPECIES_LURKELP, 10, 3
	msgbox PlatoonInsideFoyer_Text_DevLoreLurkelp, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	playse SE_PC_OFF
	waitse
	release
	end

PlatoonInsideFoyer_EventScript_DevLoreBaghoul::
	showmonpic SPECIES_BAGHOUL, 10, 3
	msgbox PlatoonInsideFoyer_Text_DevLoreBaghoul, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	playse SE_PC_OFF
	waitse
	release
	end

PlatoonInsideFoyer_EventScript_DevLoreBuggory::
	showmonpic SPECIES_BUGGORY, 10, 3
	msgbox PlatoonInsideFoyer_Text_DevLoreBuggory, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	playse SE_PC_OFF
	waitse
	release
	end

PlatoonInsideFoyer_EventScript_TerminalSav::
	lock
	playse SE_PC_LOGIN
	msgbox PlatoonInsideFoyer_Text_Terminal, MSGBOX_DEFAULT
	multichoice 19, 4, MULTI_MUSEUM_SAV, FALSE
	copyvar VAR_TEMP_1, VAR_RESULT
	switch VAR_TEMP_1
	case 0, PlatoonInsideFoyer_EventScript_DevLoreSmaugron
	case 1, PlatoonInsideFoyer_EventScript_DevLoreBloomwile
	case 2, PlatoonInsideFoyer_EventScript_DevLoreStaalnary
	closemessage
	playse SE_PC_OFF
	release
	end

PlatoonInsideFoyer_EventScript_DevLoreSmaugron::
	showmonpic SPECIES_AGGRON, 10, 3
	msgbox PlatoonInsideFoyer_Text_DevLoreSmaugron, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	playse SE_PC_OFF
	waitse
	release
	end

PlatoonInsideFoyer_EventScript_DevLoreBloomwile::
	showmonpic SPECIES_MAWILE, 10, 3
	msgbox PlatoonInsideFoyer_Text_DevLoreBloomwile, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	playse SE_PC_OFF
	waitse
	release
	end

PlatoonInsideFoyer_EventScript_DevLoreStaalnary::
	showmonpic SPECIES_STAALNARY, 10, 3
	msgbox PlatoonInsideFoyer_Text_DevLoreStaalnary, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	playse SE_PC_OFF
	waitse
	release
	end

PlatoonInsideFoyer_EventScript_TerminalShark::
	lock
	playse SE_PC_LOGIN
	msgbox PlatoonInsideFoyer_Text_Terminal, MSGBOX_DEFAULT
	multichoice 19, 4, MULTI_MUSEUM_SHARK, FALSE
	copyvar VAR_TEMP_1, VAR_RESULT
	switch VAR_TEMP_1
	case 0, PlatoonInsideFoyer_EventScript_DevLoreJaramari
	case 1, PlatoonInsideFoyer_EventScript_DevLorePokerlord
	case 2, PlatoonInsideFoyer_EventScript_DevLoreMalmare
	case 3, PlatoonInsideFoyer_EventScript_DevLoreSetatonkre
	closemessage
	playse SE_PC_OFF
	release
	end

PlatoonInsideFoyer_EventScript_DevLoreJaramari::
	showmonpic SPECIES_TANGROWTH, 10, 3
	msgbox PlatoonInsideFoyer_Text_DevLoreJaramari, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	playse SE_PC_OFF
	waitse
	release
	end

PlatoonInsideFoyer_EventScript_DevLorePokerlord::
	showmonpic SPECIES_POKERLORD, 10, 3
	msgbox PlatoonInsideFoyer_Text_DevLorePokerlord, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	playse SE_PC_OFF
	waitse
	release
	end

PlatoonInsideFoyer_EventScript_DevLoreMalmare::
	showmonpic SPECIES_MALMARE, 10, 3
	msgbox PlatoonInsideFoyer_Text_DevLoreMalmare, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	playse SE_PC_OFF
	waitse
	release
	end

PlatoonInsideFoyer_EventScript_DevLoreSetatonkre::
	showmonpic SPECIES_SETATONKRE, 10, 3
	msgbox PlatoonInsideFoyer_Text_DevLoreSetatonkre, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	playse SE_PC_OFF
	waitse
	release
	end

PlatoonInsideFoyer_EventScript_TerminalTardy::
	lock
	playse SE_PC_LOGIN
	msgbox PlatoonInsideFoyer_Text_Terminal, MSGBOX_DEFAULT
	multichoice 19, 4, MULTI_MUSEUM_TARDY_SWEETAN, FALSE
	copyvar VAR_TEMP_1, VAR_RESULT
	switch VAR_TEMP_1
	case 0, PlatoonInsideFoyer_EventScript_DevLoreMelceralba
	case 1, PlatoonInsideFoyer_EventScript_DevLoreNettecate
	case 2, PlatoonInsideFoyer_EventScript_DevLoreLaRoc
	case 3, PlatoonInsideFoyer_EventScript_DevLoreWatchaugur
	closemessage
	playse SE_PC_OFF
	release
	end

PlatoonInsideFoyer_EventScript_DevLoreMelceralba::
	showmonpic SPECIES_MELCERALBA, 10, 3
	msgbox PlatoonInsideFoyer_Text_DevLoreMelceralba, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	playse SE_PC_OFF
	waitse
	release
	end

PlatoonInsideFoyer_EventScript_DevLoreNettecate::
	showmonpic SPECIES_RATICATE, 10, 3
	msgbox PlatoonInsideFoyer_Text_DevLoreNettecate, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	playse SE_PC_OFF
	waitse
	release
	end

PlatoonInsideFoyer_EventScript_DevLoreLaRoc::
	showmonpic SPECIES_ARBOK, 10, 3
	msgbox PlatoonInsideFoyer_Text_DevLoreLaRoc, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	playse SE_PC_OFF
	waitse
	release
	end

PlatoonInsideFoyer_EventScript_DevLoreWatchaugur::
	showmonpic SPECIES_WATCHOG, 10, 3
	msgbox PlatoonInsideFoyer_Text_DevLoreWatchaugur, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	playse SE_PC_OFF
	waitse
	release
	end

PlatoonInsideFoyer_EventScript_TerminalVal::
	lock
	playse SE_PC_LOGIN
	msgbox PlatoonInsideFoyer_Text_Terminal, MSGBOX_DEFAULT
	multichoice 19, 4, MULTI_MUSEUM_VAL, FALSE
	copyvar VAR_TEMP_1, VAR_RESULT
	switch VAR_TEMP_1
	case 0, PlatoonInsideFoyer_EventScript_DevLoreXolhm
	case 1, PlatoonInsideFoyer_EventScript_DevLoreMalachrey
	case 2, PlatoonInsideFoyer_EventScript_DevLoreFortifros
	case 3, PlatoonInsideFoyer_EventScript_DevLoreBabobo
	closemessage
	playse SE_PC_OFF
	release
	end

PlatoonInsideFoyer_EventScript_DevLoreXolhm::
	showmonpic SPECIES_XOLHM, 10, 3
	msgbox PlatoonInsideFoyer_Text_DevLoreXolhm, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	playse SE_PC_OFF
	waitse
	release
	end

PlatoonInsideFoyer_EventScript_DevLoreMalachrey::
	showmonpic SPECIES_MALACHREY, 10, 3
	msgbox PlatoonInsideFoyer_Text_DevLoreMalachrey, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	playse SE_PC_OFF
	waitse
	release
	end

PlatoonInsideFoyer_EventScript_DevLoreFortifros::
	showmonpic SPECIES_FORTIFROS, 10, 3
	msgbox PlatoonInsideFoyer_Text_DevLoreFortifros, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	playse SE_PC_OFF
	waitse
	release
	end

PlatoonInsideFoyer_EventScript_DevLoreBabobo::
	showmonpic SPECIES_BABOBO, 10, 3
	msgbox PlatoonInsideFoyer_Text_DevLoreBabobo, MSGBOX_DEFAULT
	closemessage
	hidemonpic
	playse SE_PC_OFF
	waitse
	release
	end

PlatoonInsideFoyer_Text_NameLanette:
	.string "Lanette$"

PlatoonInsideFoyer_Text_LanetteBusy:
	.string "I apologize, but I am\n"
	.string "terribly busy right now.\l"
	.string "Please, go enjoy the\l"
	.string "facility's offerings.$"

PlatoonInsideFoyer_Text_HelloTawila:
	.string "Tawila, how are you doing?\p"
	.string "Give it your all in the\n"
	.string "gauntlet for me, okay?$"

PlatoonInsideFoyer_Text_LanetteEnd:
	.string "...Tawila.\p"
	.string "Time is ticking.\n"
	.string "Why not make the most of it?$"

PlatoonInsideFoyer_Text_FanClubClosed:
	.string "Yo, bub.\n"
	.string "Move right along.\p"
	.string "No access to the Fan Club for\n"
	.string "you unless I get the go ahead.$"

PlatoonInsideFoyer_Text_WantToGetInMuseum:
	.string "Jeez oh man, it is my dream to one\n"
	.string "day roam the halls of the museum.\p"
	.string "Legends say only the most VIP of\n"
	.string "all of us trainers get access.\l"
	.string "Specifically, those who manage to\l"
	.string "fill out their ENTIRE Pokedex.\p"
	.string "Best advice I can give is to keep\n"
	.string "trying out new ones! Oh, and\l"
	.string "swapping in a previously defeated\l"
	.string "trainer's Pokemon will have that\l"
	.string "count as Caught as well.\p"
	.string "Maybe one day we'll both find\n"
	.string "ourselves in those hallowed halls!$"

PlatoonInsideFoyer_Text_SleepRest:
	.string "Yawn...\p"
	.string "...Oh, huh. Sorry I seem so tired...\n"
	.string "It's from battling a lot.\p"
	.string "My favorite strategy... is sleeping\n"
	.string "moves... like Chernoboar's Spore...\p"
	.string "It puts the enemy to sleep for\n"
	.string "a couple turns... then, when I hit\l"
	.string "'em... boom... automatic\l"
	.string "critical hit...\p"
	.string "...But that makes the sleeper\n"
	.string "wake right up...\p"
	.string "Now, Capybarna...\n"
	.string "That Pokemon can use Rest...\p"
	.string "A Resting Pokemon is different\n"
	.string "than a Sleeping Pokemon...\l"
	.string "...They stay asleep longer...\l"
	.string "and can't be woken up\l"
	.string "by attacks...\p"
	.string "...Yawn. I'm boring myself...$"

PlatoonInsideFoyer_Text_SuperEffectiveSTAB:
	.string "Hey! Hey!\p"
	.string "Hey!\p"
	.string "Didja know that Super Effective\n"
	.string "Moves work differently in here??\l"
	.string "I did!\p"
	.string "Super Effective Moves do like,\n"
	.string "half? Of what they normally do.\l"
	.string "Battles in this facility take\l"
	.string "more time than most!\p"
	.string "Resistances, though? Those block\n"
	.string "the same amount of damage!\p"
	.string "Things are flipped on their head\n"
	.string "a bit! Resistances count for\l"
	.string "more than weaknesses!\p"
	.string "It fires me up when I see my team\n"
	.string "tank through hard hits and come\l"
	.string "out with a hard-earned victory!$"

PlatoonInsideFoyer_Text_DragonType:
	.string "Dragons are, erm, maybe the\n"
	.string "most EPIC type of them all.\p"
	.string "If a Parakuri tries to Intimidate\n"
	.string "a Dragon? Heh...\l"
	.string "Completely unphased.\p"
	.string "My buddies tell me Fairy types\n"
	.string "hard-counter them.\l"
	.string "...How idiotic...!\p"
	.string "They act like those darned\n"
	.string "pixies are immune to Dragon type\l"
	.string "moves, or something like that.\p"
	.string "Last time I checked, they just\n"
	.string "resist them! Now, Normal moves\l"
	.string "against Ghosts? We'd be talking.$"

PlatoonInsideFoyer_Text_IceRelatedThings:
	.string "My husband has not stopped\n"
	.string "criticizing my heavy usage of\l"
	.string "Ice type Pokemon.\p"
	.string "It is simple science.\n"
	.string "Ice is not as brittle as he so\l"
	.string "likes to claim. It is\l"
	.string "wonderful defensively\l"
	.string "against Water type Pokemon.\p"
	.string "Oh, and when it is hailing?\n"
	.string "Their physical defensive\l"
	.string "capabilities rise.\p"
	.string "I would be amiss to leave out\n"
	.string "their multiple status ailments.\l"
	.string "Frostbite can shut down\l"
	.string "specially offensive threats,\l"
	.string "and when I can manage to freeze\l"
	.string "an adversary solid...\l"
	.string "There is no saving them.\p"
	.string "Much like there will be no\n"
	.string "salvation for that man\l"
	.string "when I next give him an earful.$"

PlatoonInsideFoyer_Text_CosmicType:
	.string "Are you perhaps interested in\n"
	.string "the frontier of space?\l"
	.string "Well, Cosmic is the type for you.\p"
	.string "It is an impeccable type in\n"
	.string "my opinion, with more\l"
	.string "defensive pros than cons.\p"
	.string "Cosmic type Pokemon\n"
	.string "are weak to the following:\l"
	.string "Rock, Dragon, and Dark types.\p"
	.string "They are, then, resistant\n"
	.string "to the following:\l"
	.string "Normal, Flying, Ground,\l"
	.string "Ghost, Water, and Fairy.\p"
	.string "To top off this defensive\n"
	.string "setup, Cosmic moves do not\l"
	.string "affect Cosmic types.\p"
	.string "On the offensive end...\n"
	.string "this is where the type falters\l"
	.string "some. It only hits\l"
	.string "Fire, Flying, and Fairy\l"
	.string "super effectively.\p"
	.string "It is ill-advised to use\n"
	.string "Cosmic moves on Dragon,\l"
	.string "Dark, Ice, and Ghost.\p"
	.string "That about runs the gamut.\n"
	.string "Maybe invest in a Skooky\l"
	.string "the next time you are\l"
	.string "presented with one. It may\l"
	.string "be out of this world.$"

PlatoonInsideFoyer_Text_GreasyType:
	.string "Okay, you don't have to stare.\p"
	.string "Yes, I'm a bit hefty. Why do\n"
	.string "you assume, then, that I like\l"
	.string "the Greasy type?\p"
	.string "I mean, I do. So, uh...\p"
	.string "Listen. Greasy type Pokemon are\n"
	.string "pretty fragile. They're weak\l"
	.string "to Ground, Bug, Fire,\l"
	.string "Psychic, and Fairy.\p"
	.string "But they are defensively solid\n"
	.string "against the same amount.\l"
	.string "Fighting, Poison,\l"
	.string "Water, Grass, and Ice.\p"
	.string "On the offensive end, they\n"
	.string "don't perform well against\l"
	.string "Fairy, Water, and Poison.\p"
	.string "And on the flip side,\n"
	.string "they hit Fighting, Ground,\l"
	.string "Grass, Ice, and Bug types\l"
	.string "hard as a flat-top stove.\p"
	.string "If you nab yourself a Greese,\n"
	.string "let that thing let loose on\l"
	.string "its foes before it gets\l"
	.string "gunned down itself.$"

PlatoonInsideFoyer_Text_RubberType:
	.string "Style is what I aim for most\n"
	.string "when choosing Pokemon!\l"
	.string "Obviously, the shining jewel\l"
	.string "of them all is Babobo.\l"
	.string "The one and only Rubber type!\p"
	.string "Rubber can easily slot in as\n"
	.string "a neutral role offensively.\l"
	.string "While its attacks only land\l"
	.string "devastatingly hard versus\l"
	.string "Electric and Fairy targets,\l"
	.string "it will hit all else\l"
	.string "neautrally except for\l"
	.string "Rock, Steel, and Poison,\l"
	.string "its only resistant types.\p"
	.string "Rubber completely steals\n"
	.string "the show when taking hits,\l"
	.string "resisting Fighting, Ice,\l"
	.string "Water, Electric, and Fairy\l"
	.string "and bouncing back into\l"
	.string "tip-top shape afterwards!\p"
	.string "Keep an eye out for\n"
	.string "Poison, Steel and Psychic\l"
	.string "attacks. Those can particularly\l"
	.string "bend a Rubber Pokemon.\p"
	.string "If you can juggle all of that\n"
	.string "knowledge, give Babobo a whirl!$"

PlatoonInsideFoyer_Text_RelicType:
	.string "Oi, laddie...\n"
	.string "This old man has been commanding\l"
	.string "a squadron of Pokemon for\l"
	.string "many a decade now.\p"
	.string "Let me clue you in on the ancient\n"
	.string "terror that is Vizaaviso,\l"
	.string "a Relic type Pokemon, once\l"
	.string "long forgotten.\p"
	.string "This type is older than many others.\n"
	.string "Thus, it is relatively badly\l"
	.string "documented. What can be observed\l"
	.string "is its weakness to Grass and\l"
	.string "Psychic type moves.\p"
	.string "Relic type moves...? They are\n"
	.string "some of the most complicated of\l"
	.string "any I have witnessed.\l"
	.string "They specialize in hitting\l"
	.string "unique types super effectively\l"
	.string "that vary per move. It is as\l"
	.string "if Relic moves all have\l"
	.string "special conditionals like\l"
	.string "the move Freeze-Dry.\p"
	.string "If you can manage a\n"
	.string "Vizaaviso, it may serve\l"
	.string "you dutifully.$"

PlatoonInsideFoyer_Text_BeastType:
	.string "YEAHHHHHH!!!\n"
	.string "I like to go ALL OUT\l"
	.string "when I'm on the field!\l"
	.string "BEAST type Pokemon are perfect\l"
	.string "for a BEAST like me!\p"
	.string "Setatonkre is the biggest\n"
	.string "BEAST out there! Attack,\l"
	.string "attack, and DON'T LOOK BACK!\l"
	.string "Only Dragon, Flying, and\l"
	.string "Poison types can dare\l"
	.string "withstand those blows!\p"
	.string "Oh, and Bugs? Ghosts?\n"
	.string "FORGET EM!\l"
	.string "They practically distintegrate!\p"
	.string "LET'S GOOOOO!$"

PlatoonInsideFoyer_Text_FormChanges:
	.string "Sometimes I get told I have a\n"
	.string "complexity addiction.\l"
	.string "Well, addiction's a strong word,\l"
	.string "but I do like to run Pokemon\l"
	.string "with a bit more detail\l"
	.string "baked in.\p"
	.string "Have you stumbled onto any with\n"
	.string "form changes? Malmare and\l"
	.string "Rickshawty can completely\l"
	.string "turn the tides on opponents\l"
	.string "when hit at the right times\l"
	.string "with the right moves.\p"
	.string "Hagoosh starts out very strong,\n"
	.string "but its slime body can\l"
	.string "dissipate when weak, making it\l"
	.string "an easy Pokemon to sweep up\l"
	.string "when low on health.\p"
	.string "Astigmoray is a complete monster\n"
	.string "out there. But, I hear if you\l"
	.string "manage to use a move to\l"
	.string "pierce its eye... that thing\l"
	.string "crumples like paper.\p"
	.string "If any of that sounded like\n"
	.string "a good time, try 'em out.\l"
	.string "I'm biased, sure.$"

PlatoonInsideFoyer_Text_IWasWatchingYourMatches:
	.string "Hey, you.\p"
	.string "I've been observing your matches.\n"
	.string "You battle in a pretty interesting\l"
	.string "way... can you come here\l"
	.string "for a moment?$"

PlatoonInsideFoyer_Text_IllUnlockTheItemMenuForYou:
	.string "My name is Lanette.\n"
	.string "I run this facility in my\l"
	.string "sister's absence...\p"
	.string "I really enjoy watching\n"
	.string "unorthodox battling. Hence, my\l"
	.string "interest in this randomized\l"
	.string "battle format. I feel that is\l"
	.string "a true measure of a good trainer;\l"
	.string "one that can work under any\l"
	.string "prerequisite.\p"
	.string "You seem to know some stuff,\n"
	.string "for a rookie. I will be tuning\l"
	.string "in whenever you go back to the\l"
	.string "gauntlet. And, as a show of\l"
	.string "good will...\p"
	.string "Check in with Teala, to your left.\n"
	.string "I told her that you have been\l"
	.string "cleared to receive the Item Bag\l"
	.string "if you so wish.\p"
	.string "Try aiming for a big streak\n"
	.string "of battles won. If I see you\l"
	.string "hit 3 or more, I will be\l"
	.string "highly impressed. Mayhaps I will\l"
	.string "give you a useful gift.\p"
	.string "Have a good evening.$"

PlatoonInsideFoyer_Text_ExcitingWin:
	.string "That was a stimulating streak,\n"
	.string "Tawila. Remarkable resilience.\p"
	.string "Come on over, indulge me...$"

PlatoonInsideFoyer_Text_IllUnlockThePrevoCheckerForYou:
	.string "Have you been checking your\n"
	.string "Pokedex, Tawila? It records\l"
	.string "data for every Pokemon you use\l"
	.string "on your team. There's some\l"
	.string "fascinating stuff to learn from it.\p"
	.string "A profusion of the Pokemon you can\n"
	.string "pick from in the facility have\l"
	.string "pre-evolutions out in the wild.\l"
	.string "If you're in for a pursuit of\l"
	.string "knowledge, I would go talk to\l"
	.string "Tanner at his counter. He can fill\l"
	.string "in your Pokedex with data for\l"
	.string "pre-evolutions of Pokemon you have\l"
	.string "used in battle thus far.\p"
	.string "I may have some further special\n"
	.string "gifts for you if you humor me and\l"
	.string "fill out that dex out yours.\p"
	.string "Let's say... aim for 50 seen.\n"
	.string "That'll show me that you've\l"
	.string "witnessed your fair share of bouts.\p"
	.string "Have a good evening.$"

PlatoonInsideFoyer_Text_IllUnlockTheItemAndPrevoForYou:
	.string "My name is Lanette.\n"
	.string "I run this facility in my\l"
	.string "sister's absence...\p"
	.string "I really enjoy watching\n"
	.string "unorthodox battling. Hence, my\l"
	.string "interest in this randomized\l"
	.string "battle format. I feel that is\l"
	.string "a true measure of a good trainer;\l"
	.string "one that can work under any\l"
	.string "prerequisite.\p"
	.string "You especially seem to know\n"
	.string "what you're doing. I will be tuning\l"
	.string "in whenever you go back to the\l"
	.string "gauntlet. And, as a show of\l"
	.string "good will...\p"
	.string "Check in with Teala, to your left.\n"
	.string "I told her that you have been\l"
	.string "cleared to receive the Item Bag\l"
	.string "if you so wish.\p"
	.string "Also, I've been meaning to ask.\n"
	.string "Have you been checking your\l"
	.string "Pokedex, Tawila? It records\l"
	.string "data for every Pokemon you use\l"
	.string "on your team. There's some\l"
	.string "fascinating stuff to learn from it.\p"
	.string "A profusion of the Pokemon you can\n"
	.string "pick from in the facility have\l"
	.string "pre-evolutions out in the wild.\l"
	.string "If you're in for a pursuit of\l"
	.string "knowledge, I would go talk to\l"
	.string "Tanner at his counter. He can fill\l"
	.string "in your Pokedex with data for\l"
	.string "pre-evolutions of Pokemon you have\l"
	.string "used in battle thus far.\p"
	.string "I may have some further special\n"
	.string "gifts for you if you humor me and\l"
	.string "fill out that dex out yours.\p"
	.string "Let's say... aim for 50 seen.\n"
	.string "That'll show me that you've\l"
	.string "witnessed your fair share of bouts.\p"
	.string "Have a good evening.$"

PlatoonInsideFoyer_Text_50DexSeen:
	.string "Tawila, Tawila, Tawila.\p"
	.string "Always good to see you battle.\p"
	.string "Mind coming over here so I can\n"
	.string "peruse your Pokedex?$"

PlatoonInsideFoyer_Text_IllUnlockTheCustomTypeMons:
	.string "Hmm. Now, let's see...\p"
	.string "Yep. That's 50. You've been\n"
	.string "making the rounds. That's great.\p"
	.string "Have the battles remained\n"
	.string "interesting for you each time?\l"
	.string "I sure hope so.\p"
	.string "But... hmm. If you're looking\n"
	.string "for even more of a mix-up to\l"
	.string "regular battles in this facility,\l"
	.string "I can set you up with the\l"
	.string "experimental Pokemon.\p"
	.string "Not everyone wants to have them in\n"
	.string "the pool, as they are wildly\l"
	.string "out of most peoples' wheelhouse.\l"
	.string "Why so, you may ask? Well, most\l"
	.string "of them have Types that have not\l"
	.string "been seen on any other Pokemon.\p"
	.string "Cosmic. Beast. Relic.\n"
	.string "Rubber. Greasy.\l"
	.string "I would wager that these Type\l"
	.string "names don't ring a bell.\p"
	.string "They have their own place on the\n"
	.string "type chart, with unique strengths\l"
	.string "and weaknesses. You're a tough\l"
	.string "one, Tawila. I'll put these\l"
	.string "experimental picks into the\l"
	.string "general roster.\p"
	.string "Oh, and, hmm...\n"
	.string "The next milestone I want you\l"
	.string "to strive for is seeing 100\l"
	.string "Pokemon in total.\l"
	.string "Go back to battling whenever\l"
	.string "you would like and get those\l"
	.string "numbers up.\p"
	.string "Knowing you has been rather fun,\n"
	.string "Tawila. Have a good evening.$"

PlatoonInsideFoyer_Text_100DexSeen:
	.string "Well. If it isn't the one and\n"
	.string "only Tawila.\p"
	.string "You know the drill. It's\n"
	.string "Pokedex time.$"

PlatoonInsideFoyer_Text_IllUnlockTheFanClub:
	.string "Yep. I can already tell.\n"
	.string "100 Pokemon seen...\l"
	.string "awesome possum.\p"
	.string "I could always tell you had an\n"
	.string "appreciation for the wildlife\l"
	.string "of the area. Likewise.\p"
	.string "I went ahead and let the guard\n"
	.string "at the Fan Club door know that\l"
	.string "you are fully cleared to enter.\l"
	.string "The Club is filled with superfans\l"
	.string "of the Hodgepodge Platoon.\l"
	.string "Most of them have streaks numbering\l"
	.string "in the double digits.\p"
	.string "You might learn some obscure\n"
	.string "knowledge or tricks or lore\l"
	.string "from them. Why not go\l"
	.string "socialize for a bit.\p"
	.string "As for your next Pokdex goal,\n"
	.string "hmm...\p"
	.string "I want to see you try for\n"
	.string "80 Caught. Make sure to check in\l"
	.string "with Tanner for pre-evolution\l"
	.string "entries now and then.\p"
	.string "Have a good evening.$"

PlatoonInsideFoyer_Text_80DexCaught:
	.string "Tawila, Tawila,\n"
	.string "quite contrary.\p"
	.string "That rhyme doesn't work.\n"
	.string "Eh, you get the idea.\p"
	.string "Come let me talk your ear off\n"
	.string "for a spell.$"

PlatoonInsideFoyer_Text_IllUnlockPebbleriteCave:
	.string "Ha, ha, ha... you really are\n"
	.string "tenacious, you know...\p"
	.string "A whole 80 caught? I must say,\n"
	.string "I was not quite expecting you\l"
	.string "to indulge me so heavily.\l"
	.string "That's quite kind.\p"
	.string "I had one of my employees remove\n"
	.string "the blockers from the cave\l"
	.string "entrance outdoors. People have\l"
	.string "been telling me that there are\l"
	.string "ancient tablets in there telling\l"
	.string "of some prophecy. I don't\l"
	.string "quite believe in that kind of stuff,\l"
	.string "but the archaeologic discovery\l"
	.string "is definitely cool.\p"
	.string "There is not much left for me\n"
	.string "to tax you with, Tawila.\l"
	.string "The last conceivable milestone\l"
	.string "would be getting every single\l"
	.string "Pokedex entry filled out.\l"
	.string "All 142. Good luck if you\l"
	.string "so choose to take that road.\p"
	.string "And as always, good evening.\n$"

PlatoonInsideFoyer_Text_140DexCaught:
	.string "Hey. Look at that ear to ear\n"
	.string "grin I see. I'm assuming you\l"
	.string "have a big achievement to\l"
	.string "show off?$"

PlatoonInsideFoyer_Text_IllUnlockMuseum:
	.string "Every. Single. Pokemon. Catalogued.\p"
	.string "Kudos, Tawila. You've seen\n"
	.string "everything there could be to see.\p"
	.string "So, I suppose it's time to fill you\n"
	.string "in on a few important matters.\p"
	.string "Firstly, where the Hodgepodge\n"
	.string "Platoon even is. The answer?\l"
	.string "It's all virtual.\p"
	.string "My close friend Bill had\n"
	.string "been developing his own virtual\l"
	.string "reality tech for a game he had\l"
	.string "been working on. I believe it\l"
	.string "was called...\l"
	.string "AmalgaMagenta? Yes.\p"
	.string "I was interested in taking that\n"
	.string "base and spinning it into my\l"
	.string "own game. A game where people\l"
	.string "could use custom Pokemon unseen\l"
	.string "and unheard of in our world.\p"
	.string "Friends of mine gathered around\n"
	.string "to help me out with various parts\l"
	.string "of the design process. The\l"
	.string "Pokemon you have been battling with\l"
	.string "have been designed by many\l"
	.string "different talented folks.\p"
	.string "Every individual you see in this\n"
	.string "building is an artificial\l"
	.string "intelligence programmed by me.\l"
	.string "Except, of course, the trainers\l"
	.string "you have fought. They all are\l"
	.string "able to access this realm through\l"
	.string "Virtual Reality Headsets.\p"
	.string "So, where does that leave you?\p"
	.string "Tawila, you're my crowning\n"
	.string "achievement. A self-learning\l"
	.string "AI that I wanted to see out\l"
	.string "match real humans. I saw your\l"
	.string "skills develop, and your curiosity\l"
	.string "blossom. Very remarkable, indeed.\p"
	.string "I must admit, Tawila, I have\n"
	.string "begun to truly see you as an\l"
	.string "independent. A friend. But,\l"
	.string "unfortunately, there is no\l"
	.string "leaving this realm for you.\p"
	.string "I have coded Purplina, by the\n"
	.string "eastern gate, to unlock\l"
	.string "your final prize. The Museum.\p"
	.string "There, you can read up on all\n"
	.string "of the creators that made this\l"
	.string "game possible.\p"
	.string "Soak up that last bit of curiosity,\n"
	.string "Tawila. I will be shutting you\l"
	.string "down by midnight. You've succeeded,\l"
	.string "in my eyes.\p"
	.string "...Good night.$"

PlatoonInsideFoyer_Text_NoItemsForNewbies:
	.string "Hello! You're a fresh face.\n"
	.string "Good luck at the challenge!$"

PlatoonInsideFoyer_Text_WantAllTheItems:
	.string "Ah, it's you! That Tawila\n"
	.string "person Lanette told me about.\p"
	.string "I have a bag filled with\n"
	.string "items to give you. Just be\l"
	.string "prepared! There's a LOT.\p"
	.string "Are you ready to receive\n"
	.string "your items?$"

PlatoonInsideFoyer_Text_NoItemsForU:
	.string "That's fine!\n"
	.string "Happy battling!$"

PlatoonInsideFoyer_Text_OkayBuckleUp:
	.string "Okay then! Let's fill\n"
	.string "'er up!$"

PlatoonInsideFoyer_Text_ThatsEverything:
	.string "That should be everything!\n"
	.string "Take a look in your bag\l"
	.string "for detailed descriptions\l"
	.string "of every item.\p"
	.string "It can really assist you\n"
	.string "in battle to reference what they\l"
	.string "all can do! Toodles!$"

PlatoonInsideFoyer_Text_EnjoyingYourItems:
	.string "Hope you're enjoying that bag\n"
	.string "of items, Tawila.\p"
	.string "Remember to reference them\n"
	.string "while in battle!$"

PlatoonInsideFoyer_Text_NoPrevoCheckerForNewbies:
	.string "Ah, yeah, I'm still setting up\n"
	.string "shop over here. Forgive me.$"

PlatoonInsideFoyer_Text_Scram:
	.string "Ugh. Why are you bothering me?\n"
	.string "I'm just the door guard.\p"
	.string "No, I'm not opening it for you.\n"
	.string "Kindly vacate.$"

PlatoonInsideFoyer_Text_LetMeOpenTheGate:
	.string "Yes, I am very aware.\n"
	.string "Gate should be opening momentarily.$"

PlatoonInsideFoyer_Text_GateAlreadyOpen:
	.string "What? It's open.\n"
	.string "Go be merry, or whatever.$"

PlatoonInsideFoyer_Text_WantToFillOutYourDex:
	.string "Would you like me to fill out\n"
	.string "pre-evolution dex entries\l"
	.string "in your Pokedex? This will only\l"
	.string "be for Pokemon you have registered\l"
	.string "as Caught.$"

PlatoonInsideFoyer_Text_OkayThen:
	.string "Okay. Come back later\n"
	.string "if you'd like to.$"

PlatoonInsideFoyer_Text_CheckYourDexNow:
	.string "All should be situated.\n"
	.string "Take a look at any entries\l"
	.string "you've just unlocked.$"

PlatoonInsideFoyer_Text_Terminal:
	.string "Which Pokemon line would you\n"
	.string "like to view the dev lore of?$"

PlatoonInsideFoyer_Text_DevLoreMusalord:
	.string "Dev Lore Unavailable.$"

PlatoonInsideFoyer_Text_DevLoreExpload:
	.string "Dev Lore Unavailable.$"

PlatoonInsideFoyer_Text_DevLorePorybot:
	.string "Dev Lore Unavailable.$"

PlatoonInsideFoyer_Text_DevLoreVerglazard:
	.string "This Pokémon’s concept comes\n"
	.string "from a Fire Red Rom Hack Clove\l"
	.string "was making called Sparkling\l"
	.string "Fire Red. It would’ve had new\l"
	.string "shinies for every Pokémon, and\l"
	.string "the shiny chance would be greatly\l"
	.string "increased. There would also be\l"
	.string "Delta Pokémon. All of this was\l"
	.string "inspired by Ecnoid’s hacks of a\l"
	.string "similar premise for 3DS and\l"
	.string "Switch games. The actual sprite\l"
	.string "has an interesting origin since it\l"
	.string "was a Charizard sprite we had\l"
	.string "planned for Pisces at one point\l"
	.string "as a boss. The pose is\l"
	.string "specifically based on the\l"
	.string "famous Base Set Charizard card.$"

PlatoonInsideFoyer_Text_DevLoreBrevato:
	.string "Brevato’s design is the combined\n"
	.string "form of a 3-stage line based on\l"
	.string "frogs and radishes. It originates\l"
	.string "from Bonzo's friend’s discontinued\l"
	.string "Rom Hack project, Pokémon\l"
	.string "Starlight. The first stage was an\l"
	.string "angry rainfrog-looking fellow\l"
	.string "called Ribbeet. The later evolutions\l"
	.string "had spindly root legs for springy\l"
	.string "jumps. So, Bonzo combined both\l"
	.string "aspects for this design.$"

PlatoonInsideFoyer_Text_DevLoreGravendor:
	.string "Gravendor was originally a\n"
	.string "legendary Pokémon that was\l"
	.string "part of a Hunter, Gatherer, and\l"
	.string "Scavenger trio for Pokémon\l"
	.string "ScaleXFang. This design was\l"
	.string "massively revamped from what it\l"
	.string "once was for that project. Bonzo\l"
	.string "even changed the typing around\l"
	.string "by making it a Ground/Fighting\l"
	.string "type as opposed to a\l"
	.string "Ground/Ghost one. The goal for its\l"
	.string "redesign was to make a ghastly\l"
	.string "looking Pokémon that\l"
	.string "was not Ghost-type.$"

PlatoonInsideFoyer_Text_DevLoreShamburger:
	.string "Shamburger originates from\n"
	.string "a Fakémon design challenge\l"
	.string "that Bonzo did last year during the\l"
	.string "summer. For 18 days, Bonzo\l"
	.string "designed Fakémon that fit into\l"
	.string "each type. Shamburger was the\l"
	.string "Rock-type representative. The\l"
	.string "inspiration for it came from a\l"
	.string "picture of a burger that looked\l"
	.string "like it had a mouth. Thus, Bonzo\l"
	.string "made a mimic that looked edible\l"
	.string "but would eat you instead. Let\l"
	.string "it be known that you should\l"
	.string "never try eating a burger that\l"
	.string "you found on the floor of a cave.$"

PlatoonInsideFoyer_Text_DevLoreSwisquire:
	.string "These Pokémon are based on a\n"
	.string "combination of 2 tropes, the\l"
	.string "regional rodent and cute pink\l"
	.string "blob Pokémon like Jigglypuff\l"
	.string "and Cleffa. The latter is one of\l"
	.string "Celadonk’s favorite kinds of\l"
	.string "Pokémon. These Pokémon were\l"
	.string "for a hack that was supposed to\l"
	.string "be more story-focused and was\l"
	.string "based on the Great Lakes.$"

PlatoonInsideFoyer_Text_DevLoreNinown:
	.string "Nin’own was originally a\n"
	.string "Seviian Unown, that Celadonk\l"
	.string "made for fun and was kind of\l"
	.string "considered to be in Fool’s Gold,\l"
	.string "but in the end, it’s here.\l"
	.string "Besides that, it represents\l"
	.string "Celadonk’s love for stick legs and\l"
	.string "weird gimmick Pokémon.$"

PlatoonInsideFoyer_Text_DevLorePeckachew:
	.string "Dev Lore Unavailable.$"

PlatoonInsideFoyer_Text_DevLoreGracklin:
	.string "Gracklin comes from an\n"
	.string "abandoned project aiming to\l"
	.string "redo all the mons from the\l"
	.string "open source Tuxemon project\l"
	.string "with Chairry's own spin. This line\l"
	.string "in particular is a retake\l"
	.string "on the Grintrock line.$"

PlatoonInsideFoyer_Text_DevLoreStovlare:
	.string "Stovlare is a very old starter\n"
	.string "of Chairry's dating almost 15\l"
	.string "years back. It has a really\l"
	.string "bad sprite that was made as\l"
	.string "one of his first, pre-AlteRed.\l"
	.string "As a kid, I guess he was just\l"
	.string "really into the concept of a\l"
	.string "stove based fire starter.$"

PlatoonInsideFoyer_Text_DevLoreAstigmoray:
	.string "Astigmoray comes from a group\n"
	.string "of 4 or so Gen 5 styled lines of\l"
	.string "Pokemon Chairry made after AlteRed\l"
	.string "to try and do more original stuff.\l"
	.string "He had wanted an Eyeball based\l"
	.string "eel mon for a long time, which\l"
	.string "crystallized into its old design.\l"
	.string "It was significantly redesigned\l"
	.string "for this game.$"

PlatoonInsideFoyer_Text_DevLoreSkooky:
	.string "Skooky’s Cosmic-type comes\n"
	.string "from Chairry’s Alterverse,\l"
	.string "although currently, it’s only in\l"
	.string "one hack besides this,\l"
	.string "AmalgaMagenta. Chairry\l"
	.string "wanted to go for a more odd\l"
	.string "Cosmic-type Pokémon, so made\l"
	.string "one based on Scooby-Doo and\l"
	.string "the Space Kook. As the Dex\l"
	.string "Entry references, it’s specifically\l"
	.string "based on Scooby-Doo: Night of\l"
	.string "100 Frights, where the Space\l"
	.string "Kook has a gun. The Dex Entry\l"
	.string "also mimics how the trivia is\l"
	.string "presented in that game. Its\l"
	.string "shiny color scheme is based\l"
	.string "on the Mystery Machine.$"

PlatoonInsideFoyer_Text_DevLoreShelebrate:
	.string "This line is pretty simple.\n"
	.string "It's a shy crab that eventually\l"
	.string "evolves to a jolly one based\l"
	.string "on slapstick and dancing.$"

PlatoonInsideFoyer_Text_DevLoreOrbacle:
	.string "Orbacle is meant to be a\n"
	.string "fortune teller box and Dahl's\l"
	.string "attempt at a object-based Pokémon.$"

PlatoonInsideFoyer_Text_DevLoreWuvme:
	.string "Wuvme is intended to be a\n"
	.string "Pokémon that doesn’t look like\l"
	.string "its type. Here, it isn’t meant to\l"
	.string "look like a Poison-type, and that\l"
	.string "typing comes from its personality.\l"
	.string "Wuvme mimics a doll, so kids\l"
	.string "will find it and take it home, only\l"
	.string "for it to be a nightmare.$"

PlatoonInsideFoyer_Text_DevLorePlantatori:
	.string "Plantatori is inspired by an\n"
	.string "enemy from Epic Battle Fantasy\l"
	.string "3. It was going to evolve into\l"
	.string "a dinosaur, but DahViper was\l"
	.string "unable to come up with a design.\l"
	.string "It was scrapped from DahViper's\l"
	.string "hack Ascend mainly just because\l"
	.string "it was made so long ago it\l"
	.string "was simply forgotten.$"

PlatoonInsideFoyer_Text_DevLoreDegourge:
	.string "Degourge was originally a\n"
	.string "Pokémon that mimicked an\l"
	.string "ice cream cone. Originally\l"
	.string "planned for Pokémon Ascend,\l"
	.string "DahViper had three other similar\l"
	.string "horror-based designs and\l"
	.string "decided to scrap this one.\l"
	.string "Funnily enough, the one that\l"
	.string "DahViper kept was redesigned to\l"
	.string "remove the horror elements, so\l"
	.string "technically Degourge could’ve\l"
	.string "still been in Ascent, but it was\l"
	.string "forgotten until now.$"

PlatoonInsideFoyer_Text_DevLoreGelebrum:
	.string "This Pokémon’s idea originates\n"
	.string "from two phenomena, 'brain freeze'\l"
	.string "and 'hidden strength in near\l"
	.string "death/danger situations,' thus the\l"
	.string "icicle in its head. A creature from a\l"
	.string "Chinese club penguin game also\l"
	.string "inspired the design.$"

PlatoonInsideFoyer_Text_DevLoreStuntisla:
	.string "Stuntisla is based off of the\n"
	.string "Electric elemental arms from\l"
	.string "the game Arms, as well as Mantis\l"
	.string "Shrimp, Egg's favorite animal.$"

PlatoonInsideFoyer_Text_DevLoreWakasuka:
	.string "These two were originally\n"
	.string "meant for Pisces, being the\l"
	.string "only new evolution for an\l"
	.string "existing Pokémon. It was part\l"
	.string "of a group for Pisces called\l"
	.string "Secretmons, in which some of\l"
	.string "our artists would secretly make\l"
	.string "Pokémon and then present them\l"
	.string "to Livra. It was mainly done\l"
	.string "since Pisces was mostly made\l"
	.string "by Livra and also because I\l"
	.string "(Jotaro G Sadfish) like being a\l"
	.string "little annoying prick. The\l"
	.string "Secretmons still exist, but\l"
	.string "they’re all new Fakémon, and\l"
	.string "it may be hard to tell which\l"
	.string "ones they are when Pisces is\l"
	.string "finally released. There’s not much\l"
	.string "to say about Wakasuka itself\l"
	.string "besides Dillsacke based them\l"
	.string "on sea spiders.$"

PlatoonInsideFoyer_Text_DevLoreMantacore:
	.string "Dev Lore Unavailable.$"

PlatoonInsideFoyer_Text_DevLoreRegiwyrm:
	.string "If it wasn’t obvious, this Pokemon\n"
	.string "is Regidrago’s hinted-at complete\l"
	.string "form. There is not much to it,\l"
	.string "although there is a Regieleki\l"
	.string "powered-up form. Maybe you’ll\l"
	.string "see it someday.$"

PlatoonInsideFoyer_Text_DevLoreCapybarna:
	.string "Dev Lore Unavailable.$"

PlatoonInsideFoyer_Text_DevLoreParakuri:
	.string "Dev Lore Unavailable.$"

PlatoonInsideFoyer_Text_DevLoreRalsea:
	.string "This was the first line to be\n"
	.string "ever sprited by Livra and also\l"
	.string "her first time spriting. Originally\l"
	.string "for Hydro Blue, eventually the\l"
	.string "idea was redone for\l"
	.string "Mystery Mauve for the Alterverse,\l"
	.string "but also was scrapped. After 4\l"
	.string "years of being around they\l"
	.string "have finally found a home.$"

PlatoonInsideFoyer_Text_DevLoreChakraring:
	.string "Dev Lore Unavailable.$"

PlatoonInsideFoyer_Text_DevLoreHagoosh:
	.string "Hagoosh was made for Faketober\n"
	.string "of 2021 for the prompt was\l"
	.string "“Slime”. It's based on hagfish\l"
	.string "since Eevee (the artist not the\l"
	.string "Pokémon) learned they produce\l"
	.string "enough slime to fill a garbage\l"
	.string "truck. Besides being based on\l"
	.string "a hagfish, the body type of the\l"
	.string "Viscous Form is based on\l"
	.string "Arctiguana from Ben 10.$"

PlatoonInsideFoyer_Text_DevLoreGoogeist:
	.string "Dev Lore Unavailable.$"

PlatoonInsideFoyer_Text_DevLoreDragong:
	.string "This line comes from when Eevee\n"
	.string "(not the Pokémon) and I (Joseph\l"
	.string "G Sadfish) were watching Wild\l"
	.string "Kratts, and I noted how Komodo\l"
	.string "Dragons are like lizard seals. Also,\l"
	.string "Eevee found the name Dragong\l"
	.string "too funny to keep it unused.$"

PlatoonInsideFoyer_Text_DevLoreWyrmWing:
	.string "Wyrm Wing is another type\n"
	.string "variant that never left the list\l"
	.string "of potential concepts for\l"
	.string "Weird Type Fun. It didn't have\l"
	.string "any particular location or event\l"
	.string "designated to it. It simply existed\l"
	.string "as an observation that Slither\l"
	.string "Wing's wings could be reworked\l"
	.string "into a large fin, mainly to add\l"
	.string "more aquatic Pokemon. It's\l"
	.string "funny since this realized version\l"
	.string "of Wyrm Wing did not become\l"
	.string "a poor man's Water-type substitute\l"
	.string "or a Water-type.$"

PlatoonInsideFoyer_Text_DevLoreCoorse:
	.string "These Pokémon were originally\n"
	.string "a Beast-type Cursola concept\l"
	.string "for Pokémon Weird Type Fun.\l"
	.string "They were meant to appear in\l"
	.string "Route 44, back when more of\l"
	.string "Johto was supposed to be in\l"
	.string "Weird Type Fun before the first\l"
	.string "version was released. Neither\l"
	.string "Route 44 nor this evolution line\l"
	.string "made it beyond Enwaitea’s\l"
	.string "notes, even though they\l"
	.string "could’ve been in Ice Path, but\l"
	.string "by that time, Weird Type Fun\l"
	.string "already had a bunch of Beast-types.$"

PlatoonInsideFoyer_Text_DevLoreKittepup:
	.string "Kittepup was originally slated\n"
	.string "for Weird Type Fun and was\l"
	.string "another Beast-type. The idea came\l"
	.string "from the fact that Enwaitea\l"
	.string "thought Male and Female\l"
	.string "Indeedee could easily be\l"
	.string "turned into a cat and a dog.\l"
	.string "However, Enwaitea didn’t know\l"
	.string "how to add gender differences,\l"
	.string "so instead, Enwaitea thought\l"
	.string "of putting the two together\l"
	.string "and making it a Chimera-type.\l"
	.string "However, Enwaitea couldn’t\l"
	.string "make a sprite for it that they\l"
	.string "liked, so it never got past the\l"
	.string "drawing board. Also, as a joke,\l"
	.string "Enwaitea thought of giving it\l"
	.string "Drizzle as a nod to the\l"
	.string "'raining cats and dogs' saying.$"

PlatoonInsideFoyer_Text_DevLoreChernoboar:
	.string "This line comes from FBI's\n"
	.string "cancelled project called Pokemon\l"
	.string "Unnamed, and they were meant\l"
	.string "to be the 3-stage Grass starter.$"

PlatoonInsideFoyer_Text_DevLoreIcandesfen:
	.string "This line comes from FBI's\n"
	.string "cancelled project called Pokemon\l"
	.string "Unnamed, and it were meant\l"
	.string "to be the final stage\l"
	.string "of the Fire starter.$"

PlatoonInsideFoyer_Text_DevLoreCastermite:
	.string "Dev Lore Unavailable.$"

PlatoonInsideFoyer_Text_DevLoreCelshrioom:
	.string "Dev Lore Unavailable.$"

PlatoonInsideFoyer_Text_DevLoreSeraphure:
	.string "Dev Lore Unavailable.$"

PlatoonInsideFoyer_Text_DevLoreTuetuerror:
	.string "Dev Lore Unavailable.$"

PlatoonInsideFoyer_Text_DevLoreMagidash:
	.string "Dev Lore Unavailable.$"

PlatoonInsideFoyer_Text_DevLoreLuxstrobe:
	.string "This line was originally a\n"
	.string "regional variant Kyu made\l"
	.string "for his fan game, Pokémon Esper,\l"
	.string "being one of the first made for\l"
	.string "it. If you’re wondering why the\l"
	.string "tail color changes as Luxross,\l"
	.string "don’t ask me, I have no clue.$"

PlatoonInsideFoyer_Text_DevLoreStarror:
	.string "This line was originally a\n"
	.string "regional variant Kyu made for\l"
	.string "his fan game, Pokémon Esper.\l"
	.string "It was originally a\l"
	.string "Psychic/Ghost-type.$"

PlatoonInsideFoyer_Text_DevLoreMiscladrus:
	.string "This line was originally a\n"
	.string "regional variant Kyu made for\l"
	.string "his fan game, Pokémon Esper.\l"
	.string "Not only did Livra sprite the\l"
	.string "current Miscladrus, but she also\l"
	.string "helped make the original sprite\l"
	.string "too. The Misdarna sprite is still\l"
	.string "the one Livra and Kyu made\l"
	.string "way back then.$"

PlatoonInsideFoyer_Text_DevLoreSkuldugery:
	.string "Dev Lore Unavailable.$"

PlatoonInsideFoyer_Text_DevLoreOddiowave:
	.string "Dev Lore Unavailable.$"

PlatoonInsideFoyer_Text_DevLoreBeholzer:
	.string "Dev Lore Unavailable.$"

PlatoonInsideFoyer_Text_DevLoreVividawg:
	.string "Dev Lore Unavailable.$"

PlatoonInsideFoyer_Text_DevLoreSwalheart:
	.string "These Pokémon were originally\n"
	.string "a Seviian Gulpin line for\l"
	.string "Hydro Blue. They’re based on\l"
	.string "hearts and ambrosia (a food/drink\l"
	.string "in Greek mythology that granted\l"
	.string "immortality). Seviian Swalot is\l"
	.string "mostly unchanged both concept\l"
	.string "and design-wise from its\l"
	.string "original iteration.$"

PlatoonInsideFoyer_Text_DevLoreCaclequin:
	.string "These Pokémon were originally\n"
	.string "a Seviian Cacnea line for\l"
	.string "Hydro Blue. They’re based on\l"
	.string "jack-o’-lanterns, jesters, and\l"
	.string "juggling. Seviian Cacturne is\l"
	.string "mostly unchanged from the\l"
	.string "original iteration. However, its\l"
	.string "shiny used to be based on\l"
	.string "Jevil from Deltarune.$"

PlatoonInsideFoyer_Text_DevLoreGramkrow:
	.string "This line was made by Plasto\n"
	.string "and Livra for Hydro Blue.\l"
	.string "It's very simple in concept,\l"
	.string "taking Murkrow and Honchkrow\l"
	.string "and using the witch/wizard angle\l"
	.string "they originally had and putting\l"
	.string "it more in the forefront.$"

PlatoonInsideFoyer_Text_DevLoreIntriobang:
	.string "Dev Lore Unavailable.$"

PlatoonInsideFoyer_Text_DevLoreOkkamirizo:
	.string "Okkamirizo is based on the\n"
	.string "Occam's razor principle which\l"
	.string "basically boils down to that the\l"
	.string "best answer to something is\l"
	.string "usually the simplest one, hence\l"
	.string "why its Ability is Simple. It is also\l"
	.string "vaguely based on a Grass/Dragon\l"
	.string "Seviian Breloom Livra\l"
	.string "made for Hydro Blue.$"

PlatoonInsideFoyer_Text_DevLoreFrozforce:
	.string "These Pokémon were originally\n"
	.string "one of the fossil lines planned\l"
	.string "for Pokémon Libra. Despite\l"
	.string "trying to have some more\l"
	.string "off-kilter picks for fossil\l"
	.string "Pokémon, we somehow ended\l"
	.string "up with triceratops. After a\l"
	.string "long time of having them\l"
	.string "around so long that Pisces\l"
	.string "was starting to be made not\l"
	.string "too long after, we scrapped it\l"
	.string "for something more interesting,\l"
	.string "and now Frozhorn and Frozforce\l"
	.string "are here. What could its\l"
	.string "replacement be? Well, you'll\l"
	.string "have to play Pokémon Libra in\l"
	.string "30 million years to find out.$"

PlatoonInsideFoyer_Text_DevLoreRickshawty:
	.string "Livra thought of combining the\n"
	.string "word Rickshaw and the term\l"
	.string "'shawty.' Where do the fire and\l"
	.string "bugs come from? I don't know.$"

PlatoonInsideFoyer_Text_DevLoreVizaaviso:
	.string "Dev Lore Unavailable.$"

PlatoonInsideFoyer_Text_DevLoreCrusterror:
	.string "These Pokémon are based on\n"
	.string "earthworms and giant sand\l"
	.string "worms from movies and stuff.\l"
	.string "They're some of Memelord's\l"
	.string "favorite Pokémon, and he thinks\l"
	.string "they represent his style very well.$"

PlatoonInsideFoyer_Text_DevLoreRubimizer:
	.string "Dev Lore Unavailable.$"

PlatoonInsideFoyer_Text_DevLoreArctikack:
	.string "Dev Lore Unavailable.$"

PlatoonInsideFoyer_Text_DevLoreFrankture:
	.string "This Pokémon dates back to\n"
	.string "a 2015 Essentials project Ogwon\l"
	.string "was making with a friend. While\l"
	.string "nothing ever came of it, Ogwon\l"
	.string "kept around the design. It was\l"
	.string "initially supposed to be a pure\l"
	.string "Rock-type with Levitate, with it\l"
	.string "being a weird rock balloon. The\l"
	.string "horns and nose are mainly there\l"
	.string "as Ogwon finds them easy\l"
	.string "features to put on designs when\l"
	.string "one seems too plain.$"

PlatoonInsideFoyer_Text_DevLoreProfur:
	.string "Mog's basically just a giant mop\n"
	.string "ball because Ogwon thinks it's\l"
	.string "funny. Although, Profur is based on\l"
	.string "a Shisa dog, the same thing as\l"
	.string "Growlithe and Arcanine. Ogwon\l"
	.string "finds ugly and stupid-looking dogs\l"
	.string "funny so this is just how most of his\l"
	.string "dog Pokémon end up. It's also\l"
	.string "supposed to be similar to Snubbull\l"
	.string "in personality, a Pokémon Ogwon\l"
	.string "loves. The name Mog may sound\l"
	.string "like 'mogged' but the person who\l"
	.string "made it had no clue that was a term.\l"
	.string "Also, Mog may be inspired by\l"
	.string "Quarantine Crystal's Moperdor\l"
	.string "but Ogwon doesn't remember.\l"
	.string "(please don't sue us)$"

PlatoonInsideFoyer_Text_DevLoreDadalemma:
	.string "Ogwon just found this guy in\n"
	.string "a random art layer, it's simply\l"
	.string "just a funny head and a funny\l"
	.string "body put together. Dadalemma\l"
	.string "simply is here.$"

PlatoonInsideFoyer_Text_DevLoreBevolpin:
	.string "Dullsod and Bevolpin are based\n"
	.string "on blobfish and funnily enough\l"
	.string "came before Sadsod. While\l"
	.string "coming up with the idea for\l"
	.string "Sadsod we wanted to just make\l"
	.string "it a pathetic blobfish and Ogwon\l"
	.string "decided he wanted to make one\l"
	.string "too and got to it first, so now\l"
	.string "Sadsod has some frogfish\l"
	.string "elements also. The main reason\l"
	.string "they was even added was due\l"
	.string "to the accidental similarity of\l"
	.string "Dullsod and Sadsod, although\l"
	.string "the name similarity is intentional.\l"
	.string "Also you may have seen these\l"
	.string "designs before since Ogwon\l"
	.string "posted them to Reddit a while\l"
	.string "back. As a final fun fact, Ogwon\l"
	.string "imagines Bevolpin's legs are\l"
	.string "kind of like thicker-skinned\l"
	.string "water balloons.$"

PlatoonInsideFoyer_Text_DevLoreGreese:
	.string "Groose and Greese were\n"
	.string "supposed to be for Banquet\l"
	.string "Brown, a food-themed Rom\l"
	.string "Hack. While the hack had a\l"
	.string "bunch of forms, it was also\l"
	.string "supposed to have new\l"
	.string "Pokémon like these two. The\l"
	.string "names Groose and Greese\l"
	.string "came first, followed by Greese’s\l"
	.string "design, and Groose’s design\l"
	.string "came last. For Hodgepodge,\l"
	.string "Ogwon gave Greese a slight\l"
	.string "touch-up, but redesigned\l"
	.string "Groose completely because\l"
	.string "its old design was lost. All that\l"
	.string "Ogwon can remember from\l"
	.string "beta Groose is that it was\l"
	.string "based more on takoyaki and\l"
	.string "had a grease pompadour. In\l"
	.string "the end, Ogwon wants you\l"
	.string "to feel you’re having\l"
	.string "heartburn while looking at\l"
	.string "them. So, are you?$"

PlatoonInsideFoyer_Text_DevLoreCrawtendr:
	.string "Dev Lore Unavailable.$"

PlatoonInsideFoyer_Text_DevLoreLurkelp:
	.string "Dev Lore Unavailable.$"

PlatoonInsideFoyer_Text_DevLoreBaghoul:
	.string "Dev Lore Unavailable.$"

PlatoonInsideFoyer_Text_DevLoreBuggory:
	.string "Dev Lore Unavailable.$"

PlatoonInsideFoyer_Text_DevLoreSmaugron:
	.string "This Pokémon was originally a\n"
	.string "Seviian Aggron for Hydro Blue.\l"
	.string "It initially started as a\l"
	.string "Grass/Fire-type but was changed\l"
	.string "by Sav to make a bit more sense.\l"
	.string "The final sprite made by Livra\l"
	.string "is just the same design but with\l"
	.string "a nice pose. There is no Aron or\l"
	.string "Lairon to go along with it since\l"
	.string "we simply did not feel the need\l"
	.string "to make them. Maybe imagine\l"
	.string "it’s like a Bloodmoon Ursaluna\l"
	.string "sort of deal.$"

PlatoonInsideFoyer_Text_DevLoreBloomwile:
	.string "This Pokémon was made for\n"
	.string "Hydro Blue. The concept was just\l"
	.string "'what if Mawile’s enormous jaw\l"
	.string "ate itself', and Livra took that\l"
	.string "and made it like a flower.$"

PlatoonInsideFoyer_Text_DevLoreStaalnary:
	.string "This Pokémon was a regional\n"
	.string "form planned for Hydro Blue.\l"
	.string "Savannah made the original\l"
	.string "design; Ogwon touched it up,\l"
	.string "and finally, Livra made the\l"
	.string "sprite. It's very simple, just\l"
	.string "taking Skarmory and making\l"
	.string "it more wyvern-esque.$"

PlatoonInsideFoyer_Text_DevLoreJaramari:
	.string "This line comes from a\n"
	.string "scrapped project called\l"
	.string "Banquet Brown, where every\l"
	.string "Pokémon was food-themed.\l"
	.string "Jaramari used to be a lot more\l"
	.string "slender but it was redesigned for\l"
	.string "Hodgepodge to look more like the\l"
	.string "beta Tangela evolution from\l"
	.string "GSC Spaceworld. Also, their\l"
	.string "shinies are based on Bloopers.$"

PlatoonInsideFoyer_Text_DevLorePokerlord:
	.string "Dev Lore Unavailable.$"

PlatoonInsideFoyer_Text_DevLoreMalmare:
	.string "Malmare comes from a challenge\n"
	.string "Shark did where he made a\l"
	.string "Pokémon of every type, with\l"
	.string "Malmare being the Bug-type\l"
	.string "representative. It’s based on both\l"
	.string "the wooden Trojan horse and Trojan\l"
	.string "viruses. The busted form was\l"
	.string "repurposed from an old\l"
	.string "Bug/Electric Pokémon called\l"
	.string "Malsquito.$"

PlatoonInsideFoyer_Text_DevLoreSetatonkre:
	.string "Originally, Ogwon was going to\n"
	.string "be making the Beast-type\l"
	.string "representative, however, they\l"
	.string "were already making the Greasy\l"
	.string "type one, so we got Shark to do\l"
	.string "it instead. It's inspired by two\l"
	.string "Ben 10 aliens: Wildmutt and\l"
	.string "Spidermonkey. The shiny\l"
	.string "specifically is based on\l"
	.string "Ultimate Wildmutt.$"

PlatoonInsideFoyer_Text_DevLoreMelceralba:
	.string "Dev Lore Unavailable.$"

PlatoonInsideFoyer_Text_DevLoreNettecate:
	.string "Regional forms meant for an Emerald\n"
	.string "Revamp hack Tardysoap was working\l"
	.string "on. Nettata was meant to inhabit\l"
	.string "Littleroot Grotto, a small forest\l"
	.string "clearing west of Littleroot Town.\l"
	.string "In both gameplay and lore both\l"
	.string "Pokémon were supposed to be\l"
	.string "more passive and supportive than\l"
	.string "their other forms. In Nettecate's\l"
	.string "redesign Livra decided to make\l"
	.string "it more thorny due to its\l"
	.string "flowers being roses.$"

PlatoonInsideFoyer_Text_DevLoreLaRoc:
	.string "Regional forms meant for an\n"
	.string "Emerald Revamp hack Tardysoap\l"
	.string "was working on. Tardy didn’t get\l"
	.string "too far in making these. Arbok\l"
	.string "didn’t even have a complete\l"
	.string "sprite until Livra took it up. Their\l"
	.string "only real basis is coral snakes,\l"
	.string "obvious from the color scheme.$"

PlatoonInsideFoyer_Text_DevLoreWatchaugur:
	.string "Regional forms meant for an\n"
	.string "Emerald Revamp hack Tardysoap\l"
	.string "was working on. Patracle was\l"
	.string "meant to inhabit Oldale Ruins,\l"
	.string "a slightly foreboding set of\l"
	.string "ruins east of Oldale Town. The\l"
	.string "line was originally\l"
	.string "Normal/Psychic, but I (Jonathan G.\l"
	.string "Sadfish) misremembered them\l"
	.string "as Bug/Psychic, but then we finally\l"
	.string "decided on Psychic and\l"
	.string "Psychic/Fighting.$"

PlatoonInsideFoyer_Text_DevLoreXolhm:
	.string "Wattl and Xolhm were\n"
	.string "originally a Psychic/Electric-type\l"
	.string "regional Wooper and a new\l"
	.string "evolution, named Xolung, that\l"
	.string "Val made for a Mexico region\l"
	.string "in the early 2020s. They draw\l"
	.string "inspiration from larval axolotls,\l"
	.string "olms, Wooper, cartoon ghosts,\l"
	.string "the trope of seeing a character’s\l"
	.string "skeleton when they’re\l"
	.string "electrocuted, the Aztec god\l"
	.string "Xolotl, Blinky from\l"
	.string "The Simpsons (since Aztec\l"
	.string "religion attributed\l"
	.string "deformities to Xolotl), and\l"
	.string "the Xoloitzcuintle breed of dogs.\l"
	.string "Xolhm lives in deep underground\l"
	.string "caves because Xolotl is the god\l"
	.string "of the underworld, which is also\l"
	.string "where its Ghost-type comes from.\l"
	.string "Xolotl is known as the deity of\l"
	.string "ightning and flames, hence why\l"
	.string "the line is Electric-type and is\l"
	.string "associated with misfortune and\l"
	.string "disease, which inspired Xolhm's\l"
	.string "Ability, Misfortune. The partial\l"
	.string "dog inspiration for Xolhm stems\l"
	.string "from the term “mud puppies”\l"
	.string "for salamanders, and the\l"
	.string "Xolo dog’s connection to Xolotl\l"
	.string "and it guiding souls in\l"
	.string "the underworld.$"

PlatoonInsideFoyer_Text_DevLoreMalachrey:
	.string "This line was originally made for\n"
	.string "an Australia region Val made\l"
	.string "in middle school. They are based\l"
	.string "on lampreys, leeches, and\l"
	.string "bloodworms. The bloodworm basis\l"
	.string "was a last-minute addition to justify\l"
	.string "the Rock-type and crystal teeth.$"

PlatoonInsideFoyer_Text_DevLoreFortifros:
	.string "These Pokémon date back to\n"
	.string "elementary school before even\l"
	.string "Pokémon Sun and Moon came\l"
	.string "out, so there was no Ice/Steel-type\l"
	.string "yet. Val wanted to make one,\l"
	.string "and initially, they were just\l"
	.string "snowmen wearing hard hats and\l"
	.string "holding tools. Ferrofros and\l"
	.string "Fortifros were originally named\l"
	.string "Doubwrench and Tripdrill. These\l"
	.string "Pokémon are based on snowmen,\l"
	.string "igloos, cement mixers, and\l"
	.string "wrecking balls. The tail on\l"
	.string "Ferrofros was something random\l"
	.string "Val added as she thought it was\l"
	.string "cool. Fortifros is partially inspired\l"
	.string "by Melmetal and can rotate\l"
	.string "its waist like Melmetal can.$"

PlatoonInsideFoyer_Text_DevLoreBabobo:
	.string "Despite recently becoming a\n"
	.string "One Piece Fan, Val did not\l"
	.string "intentionally make these\l"
	.string "because of Luffy. These Pokémon\l"
	.string "are an accidental pun based\l"
	.string "on the phrases 'monkeying\l"
	.string "around' and 'monkey business.'\l"
	.string "Monkey Business was originally\l"
	.string "going to be its ability, which\l"
	.string "would give priority to all status,\l"
	.string "switching-related, item\l"
	.string "theft/swapping, etc. moves. They\l"
	.string "are based on Gibbons, baboons,\l"
	.string "mandrills, and clowns. The beta\l"
	.string "name for Babobo was\l"
	.string "“Mahahaque” which came from\l"
	.string "macaque and “hahahaha,” but\l"
	.string "Val ditched it thinking it\l"
	.string "sounded bad.$"
