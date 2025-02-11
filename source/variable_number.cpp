#include "variable_number.h"


namespace pgp {

    /**
     *  Constructor
     *
     *  @param  parser  The decoder to parse the data
     */
    variable_number::variable_number(decoder &parser)
    {
        // read the first byte to determine the strategy
        if (parser.peek_number<uint8_t>() < 192) {
            // single-octet number only
            _value = parser.extract_number<uint8_t>();
        } else if (parser.peek_number<uint8_t>() < 224) {
            // it's a two-octet number, remove upper two bits
            // and append 192 to get to the correct number
            _value = (parser.extract_number<uint16_t>() & 0b0011111111111111) + 192;
        } else if (parser.peek_number<uint8_t>() == 255) {
            // skip the byte we just peeked
            parser.extract_number<uint8_t>();
            // simple four-octet number
            _value = parser.extract_number<uint32_t>();
        } else {
            // error: we don't support par
            throw std::runtime_error{ "Partial body length not implemented" };
        }
    }

    /**
     *  Constructor
     *
     *  @param  value   The value to hold
     */
    variable_number::variable_number(uint32_t value) noexcept :
        _value{ value }
    {}

    /**
     *  Assignment operator
     *
     *  @param  value   The value to assign
     *  @return self, for chaining
     */            
    variable_number &variable_number::operator=(uint32_t value) noexcept
    {              
        // update value
        _value = value;

        // allow chaining
        return *this;
    }

    /**
     *  Determine the size used in encoded format
     *
     *  @return The number of bytes used for encoded storage
     */
    size_t variable_number::size() const noexcept
    {
        // size depends on the stored value
        if (_value < 192) {
            // this can be done in a single octet
            return 1;
        } else if (_value < 8384) {
            // this will use two octets
            return 2;
        } else {
            // we will use five octets instead
            return 5;
        }
    }

    /**
     *  Extract the stored value
     *
     *  @return The stored value
     */
    variable_number::operator uint32_t() const noexcept
    {
        // return the stored value
        return _value;
    }

}
