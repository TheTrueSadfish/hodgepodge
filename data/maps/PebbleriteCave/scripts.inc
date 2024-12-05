PebbleriteCave_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, PebbleriteCave_OnLoad
	.byte 0

PebbleriteCave_OnLoad:
	call_if_gt VAR_HP_PROGRESS, 5, PebbleriteCave_EventScript_RemoveCaveBlocker
	end

PebbleriteCave_EventScript_RemoveCaveBlocker::
	setmetatile 22, 0, METATILE_Cave_SealedChamberEntrance_TopLeft, TRUE
	setmetatile 23, 0, METATILE_Cave_SealedChamberEntrance_TopMid, TRUE
	setmetatile 24, 0, METATILE_Cave_SealedChamberEntrance_TopRight, TRUE
	setmetatile 22, 1, METATILE_Cave_SealedChamberEntrance_BottomLeft, TRUE
	setmetatile 23, 1, METATILE_Cave_SealedChamberEntrance_BottomMid, FALSE
	setmetatile 24, 1, METATILE_Cave_SealedChamberEntrance_BottomRight, TRUE
	special DrawWholeMapView
	return

PebbleriteCave_EventScript_BinaryTablet::
	lock
	goto_if_eq VAR_HP_PROGRESS, 6, PebbleriteCave_EventScript_BinaryTabletRemoved
	msgbox PebbleriteCave_Text_BinaryTablet, MSGBOX_AUTOCLOSE
	release
	end

PebbleriteCave_EventScript_BinaryTabletRemoved::
	msgbox PebbleriteCave_Text_BinaryTabletRemoved, MSGBOX_AUTOCLOSE
	release
	end

PebbleriteCave_EventScript_CrikeyBinary::
	msgbox PebbleriteCave_Text_CrikeyBinary, MSGBOX_NPC
	end

PebbleriteCave_EventScript_SteppingOld::
	msgbox PebbleriteCave_Text_SteppingOld, MSGBOX_NPC
	end

PebbleriteCave_EventScript_WorthlessBlueGems::
	msgbox PebbleriteCave_Text_WorthlessBlueGems, MSGBOX_NPC
	end

PebbleriteCave_EventScript_ValuableRedGems::
	msgbox PebbleriteCave_Text_ValuableRedGems, MSGBOX_NPC
	end

PebbleriteCave_EventScript_AirRunsThin::
	msgbox PebbleriteCave_Text_AirRunsThin, MSGBOX_NPC
	end

PebbleriteCave_Text_CrikeyBinary:
	.string "Crikey! I can't believe my\n"
	.string "eyes, mate! A bona fide\l"
	.string "mystery tablet!\p"
	.string "Now, look, I've heard from\n"
	.string "a researchin' sheila that\l"
	.string "a buncha naughts n' ones\l"
	.string "means somethin' is right\l"
	.string "encoded in Binary!\p"
	.string "Whatever in the wallaby\n"
	.string "THAT means! Maybe you\l"
	.string "can figure it out, mate?$"

PebbleriteCave_Text_SteppingOld:
	.string "Even an old curmudgeon\n"
	.string "like me needs his 20k steps\l"
	.string "in a day!$"

PebbleriteCave_Text_WorthlessBlueGems:
	.string "I've been told those blue\n"
	.string "gems are worthless. But, I'm\l"
	.string "betting that's all propaganda!\l"
	.string "The elites just don't want\l"
	.string "us to even try selling them!$"

PebbleriteCave_Text_ValuableRedGems:
	.string "I've been told those red\n"
	.string "gems are valuable. Eh. Not\l"
	.string "buying it. That's just what\l"
	.string "they want you to think, when\l"
	.string "in actuality the little guys\l"
	.string "get ripped off. Somehow!$"

PebbleriteCave_Text_AirRunsThin:
	.string "Stay alert in the lower floors\n"
	.string "of the cave system.\l"
	.string "The air runs a bit thin.$"

PebbleriteCave_Text_BinaryTablet:
	.string "01010100 01001000 01000101 00100000\n"
	.string "01010111 01000001 01011001 00100000\l"
	.string "01010111 01001001 01001100 01001100\l"
	.string "00100000 01001111 01010000 01000101\l"
	.string "01001110 00001010 01001111 01001110\l"
	.string "01000011 01000101 00100000 01001111\l"
	.string "01001110 01000101 00100000 01001000\l"
	.string "01010101 01001110 01000100 01010010\l"
	.string "01000101 01000100 00100000 01000110\l"
	.string "01001111 01010010 01010100 01011001\l"
	.string "00001010 01001000 01000001 01010110\l"
	.string "01000101 00100000 01000010 01000101\l"
	.string "01000101 01001110 00100000 01000011\l"
	.string "01000001 01010101 01000111\l"
	.string "01001000 01010100$"

PebbleriteCave_Text_BinaryTabletRemoved:
	.string "(The text is unreadable due to\n"
	.string "the newly formed cave entrance.)$"
