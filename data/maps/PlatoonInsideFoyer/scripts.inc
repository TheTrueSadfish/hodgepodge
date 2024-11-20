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

PlatoonInsideFoyer_EventScript_PrevoChecker::
	lock
	faceplayer
	msgbox PlatoonInsideFoyer_Text_WantToFillOutYourDex, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, PlatoonInsideFoyer_EventScript_FullPrevoCheck
	msgbox PlatoonInsideFoyer_Text_OkayThen, MSGBOX_AUTOCLOSE
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

PlatoonInsideFoyer_Text_WantToFillOutYourDex:
	.string "wanna fill out that mf dex$"

PlatoonInsideFoyer_Text_OkayThen:
	.string "okie doke come back$"

PlatoonInsideFoyer_Text_CheckYourDexNow:
	.string "check that shit out$"
