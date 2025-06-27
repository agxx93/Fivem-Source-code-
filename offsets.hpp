#define OFFSET_LOCAL_PLAYER 0x08
#define OFFSET_HEALTH 0x280
#define OFFSET_ARMOR 0x14C
#define OFFSET_GODMODE 0x189
#define OFFSET_WEAPON_MANAGER 0x10D8
#define OFFSET_CURRENT_WEAPON 0x20
#define OFFSET_WEAPON_HASH 0x10
#define OFFSET_INFINITE_AMMO 0x74
#define OFFSET_DAMAGE_MULTIPLIER 0xB0
#define OFFSET_ENTITY_LIST 0x18
#define OFFSET_ENTITY_HEALTH 0x280

// Ajouts pour correspondre aux usages du code
#define OFFSET_ENTITY_COUNT 0x1C
#define OFFSET_PLAYER_LIST 0x30
#define OFFSET_BLIP_LIST 0x40
#define OFFSET_CAMERA_PTR 0x50
#define OFFSET_STAMINA 0x1E0
#define OFFSET_MELEE_DAMAGE 0x1F0
#define OFFSET_NO_RAGDOLL 0x200
#define OFFSET_NO_COLLISION 0x210
#define OFFSET_NOVISIBLE 0x220
#define OFFSET_RUN_SPEED 0x230
#define OFFSET_SWIM_SPEED 0x240
#define OFFSET_JUMP_BOOST 0x250
#define OFFSET_WANTED_LEVEL 0x260
#define OFFSET_DAMAGE_REDUCTION 0x270
#define OFFSET_VEHICLE_PTR 0x300
#define OFFSET_VEHICLE_GODMODE 0x310
#define OFFSET_VEHICLE_DAMAGE_REDUCTION 0x320
#define OFFSET_EXPLODE_FLAG 0x330
#define OFFSET_REPAIR_FLAG 0x340
#define OFFSET_TURBO_FLAG 0x350
#define OFFSET_ROCKET_FLAG 0x360
#define OFFSET_STEAL_PLATE_FLAG 0x370
#define OFFSET_RAIN_FLAG 0x380
#define OFFSET_EVENT_MANAGER 0x400
#define OFFSET_TIME_OF_DAY 0x410
#define OFFSET_WEATHER_TYPE 0x420

// Offsets supplémentaires pour les features avancées
#define OFFSET_NO_RECOIL 0x430
#define OFFSET_NO_SPREAD 0x440
#define OFFSET_EXPLOSIVE_AMMO 0x450
#define OFFSET_AMMO_COUNT 0x460
#define OFFSET_RANGE_MULTIPLIER 0x470
#define OFFSET_ADD_WEAPON 0x480
#define OFFSET_EQUIP_NOW 0x490
#define OFFSET_GIVE_WEAPON_TO_PED 0x4A0
#define OFFSET_CLONE_PED 0x4B0
#define OFFSET_FORCE_ACTION 0x4C0
#define OFFSET_ARMOR_OVERRIDE 0x4D0
#define OFFSET_HP_OVERRIDE 0x4E0
#define OFFSET_MENU_COLOR 0x4F0
#define OFFSET_CROSSHAIR_COLOR 0x500
#define OFFSET_RADAR_SIZE 0x510
#define OFFSET_RADAR_COLOR 0x520
#define OFFSET_ENTITY_POS 0x530
#define OFFSET_ENTITY_NAME 0x540
#define OFFSET_ENTITY_WEAPON 0x550
#define OFFSET_ENTITY_ARMOR 0x560
#define OFFSET_ENTITY_DISTANCE 0x570
#define OFFSET_ENTITY_SNAPLINE 0x580
#define OFFSET_ENTITY_CAMERA_DIR 0x590

// Les offsets ci-dessous sont des exemples génériques. Pour obtenir les offsets exacts et à jour pour FiveM, tu dois les dumper sur TA version/serveur avec un outil comme Cheat Engine, IDA, ou un dumper FiveM.
// Voici comment tu peux les trouver :
// - OFFSET_LOCAL_PLAYER : Cherche le pointeur du joueur local dans la structure du jeu (souvent dans le replayInterface ou worldPtr).
// - OFFSET_ENTITY_LIST et OFFSET_ENTITY_COUNT : Cherche la liste des entités et le nombre d'entités dans la mémoire du jeu.
// - OFFSET_WEAPON_MANAGER, OFFSET_CURRENT_WEAPON, OFFSET_WEAPON_HASH, etc. : Navigue dans la structure du joueur local pour trouver la structure d'arme et ses champs.
// - Pour chaque feature, vérifie l'offset en mémoire sur la version/serveur cible.

// Exemple de dump d'offsets (à adapter) :
// OFFSET_LOCAL_PLAYER      = *(uintptr_t*)(replayInterface + 0x08);
// OFFSET_ENTITY_LIST       = *(uintptr_t*)(worldPtr + 0x18);
// OFFSET_WEAPON_MANAGER    = *(uintptr_t*)(localPlayer + 0x10D8);
// OFFSET_CURRENT_WEAPON    = *(uintptr_t*)(weaponManager + 0x20);
// OFFSET_WEAPON_HASH       = *(uint32_t*)(currentWeapon + 0x10);
// OFFSET_HEALTH            = *(int*)(entity + 0x280);
// OFFSET_ARMOR             = *(int*)(entity + 0x14C);
// OFFSET_GODMODE           = *(bool*)(entity + 0x189);
// OFFSET_INFINITE_AMMO     = *(int*)(weaponData + 0x74);
// OFFSET_DAMAGE_MULTIPLIER = *(float*)(weaponData + 0xB0);

// Pour chaque offset : vérifie-le sur TA version, car ils changent souvent sur FiveM.
// Si tu veux des offsets à jour, utilise un dumper d'offsets FiveM ou fais-le à la main avec Cheat Engine/ReClass.