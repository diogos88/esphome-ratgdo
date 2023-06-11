#include "ratgdo_cover.h"
#include "../ratgdo_state.h"
#include "esphome/core/log.h"

namespace esphome {
namespace ratgdo {

    using namespace esphome::cover;

    static const char* const TAG = "ratgdo.cover";

    void RATGDOCover::dump_config()
    {
        LOG_COVER("", "RATGDO Cover", this);
    }
    void RATGDOCover::on_door_state(DoorState state)
    {
        switch (state) {
        case DoorState::DOOR_STATE_OPEN:
            this->position = COVER_OPEN;
            this->current_operation = COVER_OPERATION_IDLE;
            break;
        case DoorState::DOOR_STATE_CLOSED:
            this->position = COVER_CLOSED;
            this->current_operation = COVER_OPERATION_IDLE;
            break;
        case DoorState::DOOR_STATE_OPENING:
            this->current_operation = COVER_OPERATION_OPENING;
            break;
        case DoorState::DOOR_STATE_CLOSING:
            this->current_operation = COVER_OPERATION_CLOSING;
            break;
        case DoorState::DOOR_STATE_STOPPED:
            this->position = COVER_OPEN;
        default:
            this->current_operation = COVER_OPERATION_IDLE;

            break;
        }

        this->publish_state();
    }

    CoverTraits RATGDOCover::get_traits()
    {
        auto traits = CoverTraits();
        traits.set_supports_stop(true);
        return traits;
    }
    void RATGDOCover::control(const CoverCall& call)
    {
        if (call.get_stop()) {
            this->parent_->stopDoor();
        }
        if (call.get_position().has_value()) {
            auto pos = *call.get_position();
            if (pos == COVER_OPEN) {
                this->parent_->openDoor();
            } else if (pos == COVER_CLOSED) {
                this->parent_->closeDoor();
            }
        }
    }

} // namespace ratgdo
} // namespace esphome
