#pragma once
#include <stdexcept>

namespace sheet{
class AlreadyExist:public std::logic_error{
    using std::logic_error::logic_error;
};

class IncorrectName:public std::logic_error{
    using std::logic_error::logic_error;
};

}
