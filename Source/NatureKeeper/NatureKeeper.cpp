/*
1. Левелдизайн
2. Условия победы (восстановление родника в лесу для прохождения дальше)
3. Доделать разные препятствия(туман готов, надо сделать сгораемую лозу и разрушаемые стены)
4. Если будет время сделать механику со скверной на карте
(довольно сложная вещь в реализации, пока не знаю точно как делать, поэтому оставлю на потом т.к приоритетнее есть вещи)
 */

#include "NatureKeeper.h"
#include "Modules/ModuleManager.h"

IMPLEMENT_PRIMARY_GAME_MODULE( FDefaultGameModuleImpl, NatureKeeper, "NatureKeeper" );

DEFINE_LOG_CATEGORY(LogNatureKeeper)
 