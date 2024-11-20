PlatoonInsideFoyer_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, PlatoonInsideFoyer_OnLoad
	.byte 0

PlatoonInsideFoyer_OnLoad:
	call_if_set FLAG_HP_UNLOCKED_MUSEUM, PlatoonInsideFoyer_EventScript_OpenMountainHole
	end

PlatoonInsideFoyer_EventScript_OpenMountainHole::
	setmetatile 24, 5, METATILE_TrainerHill_WithoutDoor, FALSE
	special DrawWholeMapView
	return
