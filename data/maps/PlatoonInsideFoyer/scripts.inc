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
	case 0, PlatoonInsideFoyer_EventScript_UnlockItemMenu
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
	msgbox PlatoonInsideFoyer_Text_100DexSeen, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_LANETTE, PlatoonInsideFoyer_Movement_LanetteFaceDown
	applymovement OBJ_EVENT_ID_PLAYER, PlatoonInsideFoyer_Movement_PlayerWalkToLanette
	waitmovement 0
	delay 4
	msgbox PlatoonInsideFoyer_Text_IllUnlockTheFanClub, MSGBOX_DEFAULT
	setvar VAR_HP_PROGRESS, 4
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
	giveitem ITEM_KEE_BERRY
	giveitem ITEM_MUSCLE_BAND
	giveitem ITEM_BLACK_SLUDGE
	giveitem ITEM_FLOAT_STONE
	giveitem ITEM_POISON_BARB
	giveitem ITEM_MARANGA_BERRY
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
	.string "You especially seem to know\n"
	.string "what you're doing. I will be tuning\l"
	.string "in whenever you go back to the\l"
	.string "gauntlet. And, as a show of\l"
	.string "good will...\p"
	.string "Check in with Teala, to your left.\n"
	.string "I told her that you have been\l"
	.string "cleared to receive the Item Bag\l"
	.string "if you so wish.\p"
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
