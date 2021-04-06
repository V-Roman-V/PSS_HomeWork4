#include "status.h"

std::string Status::enumToStr(Status::StatusName name){
    switch(name){
        case StatusName::Busy: return "Busy";
        case StatusName::Free: return "Free";
    }
}

Status::StatusName Status::intToEnum(int val){
    switch(val){
        case 0: return StatusName::Busy;
        case 1: return StatusName::Free;
    }
    return StatusName::Free;
}

std::ostream& operator<<(std::ostream &out, const Status &S){
    return out<<Status::enumToStr(S.status);
}
