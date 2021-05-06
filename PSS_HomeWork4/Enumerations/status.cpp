#include "status.h"

std::string Status::enumToStr(Status::StatusName name){
    switch(name){
        case StatusName::Free: return "Free";
        case StatusName::Busy: return "Busy";
    }
}

Status::StatusName Status::intToEnum(int val){
    switch(val){
        case 0: return StatusName::Free;
        case 1: return StatusName::Busy;
    }
    return StatusName::Free;
}

std::ostream& operator<<(std::ostream &out, const Status &S){
    return out<<Status::enumToStr(S.status);
}
