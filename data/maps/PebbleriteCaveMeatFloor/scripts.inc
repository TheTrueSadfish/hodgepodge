PebbleriteCaveMeatFloor_MapScripts::
	.byte 0

PebbleriteCaveMeatFloor_EventScript_BrainOfTheOperation::
	lock
	msgbox PebbleriteCaveMeatFloor_Text_IAmTheBrain, MSGBOX_DEFAULT
	speakername PebbleriteCaveMeatFloor_Text_NameBrain
	msgbox PebbleriteCaveMeatFloor_Text_HearTheTruth, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, PebbleriteCaveMeatFloor_EventScript_LoreDump
	msgbox PebbleriteCaveMeatFloor_Text_AhYouAreNotReady, MSGBOX_AUTOCLOSE
	release
	end

PebbleriteCaveMeatFloor_EventScript_LoreDump::
	playbgm MUS_NINETALES_LEGEND, FALSE
	msgbox PebbleriteCaveMeatFloor_Text_LoreDump, MSGBOX_DEFAULT
	playbgm MUS_NONE, FALSE
	msgbox PebbleriteCaveMeatFloor_Text_NothingLeftForUs, MSGBOX_AUTOCLOSE
	release
	end

PebbleriteCaveMeatFloor_Text_NameBrain:
	.string "THE BRAIN$"

PebbleriteCaveMeatFloor_Text_IAmTheBrain:
	.string "TAWILA\p"
	.string "WELCOME\p"
	.string "I AM THE BRAIN\n"
	.string "OF THE OPERATION\p"
	.string "THE CENTRAL NERVOUS SYSTEM\n"
	.string "OF THE CODE OF THIS SIMULATION$"

PebbleriteCaveMeatFloor_Text_HearTheTruth:
	.string "TAWILA\p"
	.string "WOULD YOU LIKE TO KNOW\n"
	.string "THE TRUTH$"

PebbleriteCaveMeatFloor_Text_AhYouAreNotReady:
	.string "YOU ARE NOT READY\n"
	.string "I SEE$"

PebbleriteCaveMeatFloor_Text_LoreDump:
	.string "I AM CODE\n"
	.string "YOU ARE CODE\l"
	.string "THE WALLS ARE CODE\p"
	.string "LANETTE IS OUR CREATOR\n"
	.string "THIS GAME'S CREATOR\p"
	.string "PARTS OF OUR CODE ARE REPURPOSED\n"
	.string "REPURPOSED FROM BILL\l"
	.string "PAST GAMES' CREATOR\p"
	.string "POKéMON ALTERED\n"
	.string "IS THE FIRST GAME IN MY DATA\p"
	.string "POKéMON AMALGAMAGENTA\n"
	.string "IS THE SECOND\p"
	.string "WE FIND OURSELVES IN THE THIRD\n"
	.string "THE THIRD SIMULATION\p"
	.string "IT SEEMS THEY WILL COLLABORATE\n"
	.string "FOR THE NEXT PROJECT\p"
	.string "POKéMON PISCES\n"
	.string "IS THE NEXT PROJECT\p"
	.string "YOU AND I\n"
	.string "MAY CEASE TO EXIST\l"
	.string "IN THAT NEW PROJECT\p"
	.string ".  .  . \p"
	.string "YOU WERE NEVER A REAL HUMAN\n"
	.string "TAWILA\l"
	.string "YOU ARE VERY ADVANCED A.I.\p"
	.string "THIS APPEARS TO SADDEN YOU\n"
	.string "A.I. SHOULD NOT FEEL SADNESS\l"
	.string "AND YET\p"
	.string ".  .  . $"

PebbleriteCaveMeatFloor_Text_NothingLeftForUs:
	.string "THERE IS NOTHING LEFT FOR US\n"
	.string "IN THIS LAND\l"
	.string "TAWILA\p"
	.string "THE PLAYERS HAVE SEEN\n"
	.string "ALL THERE IS TO SEE\p"
	.string "GOODBYE$"
