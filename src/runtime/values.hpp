#pragma once

namespace runtime {
    class values {
    public:
        enum class ValueType {
            null,
            number
        };

        struct RuntimeVal {
            ValueType type;
        };

        struct NullVal : public RuntimeVal {
            NullVal() {
                type = ValueType::null;
            }
            int value = 0;
        };

        struct NumVal : public RuntimeVal {
            NumVal() {
                type = ValueType::number;
            }

            int value;
        };
    };
}