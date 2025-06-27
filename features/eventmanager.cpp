#include "eventmanager.hpp"
#include "Offsets.hpp"
#include <Windows.h>
#include <cstdint>

namespace events {
    bool stopAll = false, logEvents = false, rerun = false, execute = false;
    char customEvent[128] = "";
}

void InitEventLogger() {}

void RunEventExecutor() {
    if (events::execute) {
        events::execute = false;
        // Exemple d'appel d'un event custom via offsets ou native
        // uintptr_t eventMgr = *reinterpret_cast<uintptr_t*>(Offsets::eventManager);
        // if (eventMgr) {
        //     // Appeler la fonction d'envoi d'event avec events::customEvent
        // }
    }
    // ...autres logiques pour stopAll, logEvents, rerun...
}
