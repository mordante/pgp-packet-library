#include "eddsa_secret_key.h"


namespace pgp {

    /**
     *  Constructor
     *
     *  @param  parser  The decoder to parse the data
     */
    eddsa_secret_key::eddsa_secret_key(decoder &parser) :
        _k{ parser }
    {}

    /**
     *  Constructor
     *
     *  @param  k       The secret scalar for the public point
     */
    eddsa_secret_key::eddsa_secret_key(multiprecision_integer k) noexcept :
        _k{ std::move(k) }
    {}

    /**
     *  Comparison operators
     *
     *  @param  other   The object to compare with
     */
    bool eddsa_secret_key::operator==(const eddsa_secret_key &other) const noexcept
    {
        return k() == other.k();
    }

    /**
     *  Comparison operators
     *
     *  @param  other   The object to compare with
     */
    bool eddsa_secret_key::operator!=(const eddsa_secret_key &other) const noexcept
    {
        return !operator==(other);
    }

    /**
     *  Determine the size used in encoded format
     *  @return The number of bytes used for encoded storage
     */
    size_t eddsa_secret_key::size() const noexcept
    {
        // we need to store the secret scalar
        return _k.size();
    }

    /**
     *  Retrieve the secret scalar
     *
     *  @return The secret scalar for the public point
     */
    const multiprecision_integer &eddsa_secret_key::k() const noexcept
    {
        // return the stored scalar
        return _k;
    }

}
